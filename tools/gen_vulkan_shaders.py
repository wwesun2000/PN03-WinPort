#!/usr/bin/env python3
"""
Generate self-contained Vulkan 1.3 SPIR-V 1.0 shader binaries into
include/pn03_vulkan_shaders.hpp without requiring external Vulkan SDK tools.

Shaders emitted:
  - kGxTevVertSpv : Vertex shader matching kGxTevHlsl VSMain
  - kGxTevFragSpv : Fragment shader matching kGxTevHlsl PSMain (TEV 0..7 + Stage1 + alpha test)
  - kFxaaVertSpv  : Fullscreen triangle vertex shader matching VSFullscreenQuad
  - kBlitFragSpv  : Fullscreen grade/blit fragment shader matching PSBlitMain
  - kFxaaFragSpv  : Fullscreen FXAA 3.11 + display grade fragment shader matching PSFxaaMain
"""

from pathlib import Path
import struct

SPIRV_MAGIC = 0x07230203
SPIRV_VERSION_1_0 = 0x00010000

# Storage classes
SC_UNIFORM_CONSTANT = 0
SC_INPUT = 1
SC_UNIFORM = 2
SC_OUTPUT = 3
SC_FUNCTION = 7

# Decorations
DEC_BLOCK = 2
DEC_BUILTIN = 11
DEC_LOCATION = 30
DEC_BINDING = 33
DEC_DESCRIPTOR_SET = 34
DEC_OFFSET = 35

# BuiltIns
BUILTIN_POSITION = 0
BUILTIN_VERTEX_INDEX = 42

# Execution Models & Modes
EXEC_VERTEX = 0
EXEC_FRAGMENT = 4
MODE_ORIGIN_UPPER_LEFT = 7

# GLSL.std.450 extended instructions
GLSL_FABS = 4
GLSL_POW = 26
GLSL_FMIN = 37
GLSL_FMAX = 40
GLSL_FCLAMP = 43
GLSL_FMIX = 46


def encode_str_words(text: str) -> list[int]:
    raw = text.encode("utf-8") + b"\x00"
    while len(raw) % 4 != 0:
        raw += b"\x00"
    return [struct.unpack("<I", raw[i:i + 4])[0] for i in range(0, len(raw), 4)]


def inst(opcode: int, *operands: int) -> list[int]:
    return [((len(operands) + 1) << 16) | opcode, *operands]


class SpirvBuilder:
    def __init__(self, exec_model: int, entry_name: str = "main"):
        self.exec_model = exec_model
        self.entry_name = entry_name
        self._next_id = 1

        self.glsl_ext_id = self.new_id()
        self.entry_fn_id = self.new_id()

        self.interfaces: list[int] = []
        self.exec_modes: list[list[int]] = []
        self.decorations: list[list[int]] = []
        self.types_consts_globals: list[list[int]] = []
        self.func_locals: list[list[int]] = []
        self.func_body: list[list[int]] = []

        self._types: dict[tuple, int] = {}
        self._consts: dict[tuple, int] = {}

        if exec_model == EXEC_FRAGMENT:
            self.exec_modes.append(inst(16, self.entry_fn_id, MODE_ORIGIN_UPPER_LEFT))

    def new_id(self) -> int:
        rid = self._next_id
        self._next_id += 1
        return rid

    def t_void(self) -> int:
        k = ("void",)
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            self.types_consts_globals.append(inst(19, tid))
        return self._types[k]

    def t_bool(self) -> int:
        k = ("bool",)
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            self.types_consts_globals.append(inst(20, tid))
        return self._types[k]

    def t_int(self, width: int = 32, signed: int = 1) -> int:
        k = ("int", width, signed)
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            self.types_consts_globals.append(inst(21, tid, width, signed))
        return self._types[k]

    def t_uint(self) -> int:
        return self.t_int(32, 0)

    def t_sint(self) -> int:
        return self.t_int(32, 1)

    def t_float(self, width: int = 32) -> int:
        k = ("float", width)
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            self.types_consts_globals.append(inst(22, tid, width))
        return self._types[k]

    def t_vec(self, comp_ty: int, count: int) -> int:
        k = ("vec", comp_ty, count)
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            self.types_consts_globals.append(inst(23, tid, comp_ty, count))
        return self._types[k]

    def t_vec2(self) -> int:
        return self.t_vec(self.t_float(), 2)

    def t_vec3(self) -> int:
        return self.t_vec(self.t_float(), 3)

    def t_vec4(self) -> int:
        return self.t_vec(self.t_float(), 4)

    def t_bvec(self, count: int) -> int:
        return self.t_vec(self.t_bool(), count)

    def t_image2d(self) -> int:
        k = ("img2d",)
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            # OpTypeImage: SampledType=float, Dim=2D(1), Depth=0, Arrayed=0, MS=0, Sampled=1, Format=Unknown(0)
            self.types_consts_globals.append(inst(25, tid, self.t_float(), 1, 0, 0, 0, 1, 0))
        return self._types[k]

    def t_sampled_image2d(self) -> int:
        k = ("simg2d",)
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            self.types_consts_globals.append(inst(27, tid, self.t_image2d()))
        return self._types[k]

    def t_struct(self, members: list[int], tag: str) -> int:
        k = ("struct", tag, tuple(members))
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            self.types_consts_globals.append(inst(30, tid, *members))
        return self._types[k]

    def t_ptr(self, storage_class: int, pointee: int) -> int:
        k = ("ptr", storage_class, pointee)
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            self.types_consts_globals.append(inst(32, tid, storage_class, pointee))
        return self._types[k]

    def t_fn(self, ret_ty: int, *args: int) -> int:
        k = ("fn", ret_ty, args)
        if k not in self._types:
            tid = self.new_id()
            self._types[k] = tid
            self.types_consts_globals.append(inst(33, tid, ret_ty, *args))
        return self._types[k]

    def c_uint(self, val: int) -> int:
        u32 = val & 0xFFFFFFFF
        k = ("uint", u32)
        if k not in self._consts:
            cid = self.new_id()
            self._consts[k] = cid
            self.types_consts_globals.append(inst(43, self.t_uint(), cid, u32))
        return self._consts[k]

    def c_sint(self, val: int) -> int:
        u32 = struct.unpack("<I", struct.pack("<i", val))[0]
        k = ("sint", u32)
        if k not in self._consts:
            cid = self.new_id()
            self._consts[k] = cid
            self.types_consts_globals.append(inst(43, self.t_sint(), cid, u32))
        return self._consts[k]

    def c_float(self, val: float) -> int:
        u32 = struct.unpack("<I", struct.pack("<f", float(val)))[0]
        k = ("float", u32)
        if k not in self._consts:
            cid = self.new_id()
            self._consts[k] = cid
            self.types_consts_globals.append(inst(43, self.t_float(), cid, u32))
        return self._consts[k]

    def c_vec(self, vec_ty: int, *vals: float) -> int:
        cids = tuple(self.c_float(v) for v in vals)
        k = ("cvec", vec_ty, cids)
        if k not in self._consts:
            cid = self.new_id()
            self._consts[k] = cid
            self.types_consts_globals.append(inst(44, vec_ty, cid, *cids))
        return self._consts[k]

    def decorate(self, target: int, dec: int, *extra: int):
        self.decorations.append(inst(71, target, dec, *extra))

    def member_decorate(self, target: int, member: int, dec: int, *extra: int):
        self.decorations.append(inst(72, target, member, dec, *extra))

    def global_var(self, storage_class: int, pointee_ty: int, is_interface: bool = False) -> int:
        vid = self.new_id()
        self.types_consts_globals.append(inst(59, self.t_ptr(storage_class, pointee_ty), vid, storage_class))
        if is_interface:
            self.interfaces.append(vid)
        return vid

    def local_var(self, pointee_ty: int) -> int:
        vid = self.new_id()
        self.func_locals.append(inst(59, self.t_ptr(SC_FUNCTION, pointee_ty), vid, SC_FUNCTION))
        return vid

    def load(self, ty: int, ptr: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(61, ty, rid, ptr))
        return rid

    def store(self, ptr: int, val: int):
        self.func_body.append(inst(62, ptr, val))

    def access(self, pointee_ty: int, storage_class: int, base: int, *idxs: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(65, self.t_ptr(storage_class, pointee_ty), rid, base, *idxs))
        return rid

    def construct(self, ty: int, *elems: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(80, ty, rid, *elems))
        return rid

    def extract(self, ty: int, val: int, *idxs: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(81, ty, rid, val, *idxs))
        return rid

    def shuffle(self, ty: int, v1: int, v2: int, *comps: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(79, ty, rid, v1, v2, *comps))
        return rid

    def sample_implicit(self, simg_id: int, uv_id: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(87, self.t_vec4(), rid, simg_id, uv_id))
        return rid

    def sample_lod0(self, simg_id: int, uv_id: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(88, self.t_vec4(), rid, simg_id, uv_id, 0x2, self.c_float(0.0)))
        return rid

    def ext(self, ty: int, op: int, *args: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(12, ty, rid, self.glsl_ext_id, op, *args))
        return rid

    def fadd(self, ty: int, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(129, ty, rid, a, b))
        return rid

    def fsub(self, ty: int, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(131, ty, rid, a, b))
        return rid

    def fmul(self, ty: int, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(133, ty, rid, a, b))
        return rid

    def fdiv(self, ty: int, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(136, ty, rid, a, b))
        return rid

    def vec_scale(self, vec_ty: int, v: int, s: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(142, vec_ty, rid, v, s))
        return rid

    def dot(self, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(148, self.t_float(), rid, a, b))
        return rid

    def utof(self, ty: int, a: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(112, ty, rid, a))
        return rid

    def shl(self, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(196, self.t_uint(), rid, a, b))
        return rid

    def bitand(self, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(199, self.t_uint(), rid, a, b))
        return rid

    def ieq(self, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(170, self.t_bool(), rid, a, b))
        return rid

    def ine(self, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(171, self.t_bool(), rid, a, b))
        return rid

    def flt(self, ty: int, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(184, ty, rid, a, b))
        return rid

    def fgt(self, ty: int, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(186, ty, rid, a, b))
        return rid

    def logical_and(self, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(167, self.t_bool(), rid, a, b))
        return rid

    def logical_or(self, a: int, b: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(166, self.t_bool(), rid, a, b))
        return rid

    def select_scalar(self, ty: int, cond: int, tval: int, fval: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(169, ty, rid, cond, tval, fval))
        return rid

    def select_vec(self, vec_ty: int, n: int, scalar_cond: int, tval: int, fval: int) -> int:
        bvec_id = self.construct(self.t_bvec(n), *([scalar_cond] * n))
        rid = self.new_id()
        self.func_body.append(inst(169, vec_ty, rid, bvec_id, tval, fval))
        return rid

    def label(self, lbl_id: int):
        self.func_body.append(inst(248, lbl_id))

    def selection_merge(self, merge_lbl: int):
        self.func_body.append(inst(247, merge_lbl, 0))

    def branch(self, target_lbl: int):
        self.func_body.append(inst(249, target_lbl))

    def branch_cond(self, cond: int, t_lbl: int, f_lbl: int):
        self.func_body.append(inst(250, cond, t_lbl, f_lbl))

    def kill(self):
        self.func_body.append(inst(252))

    def emit_op_select_vec_mask(self, vec_ty: int, bvec: int, tval: int, fval: int) -> int:
        rid = self.new_id()
        self.func_body.append(inst(169, vec_ty, rid, bvec, tval, fval))
        return rid

    def build(self) -> list[int]:
        fn_ty = self.t_fn(self.t_void())
        entry_lbl = self.new_id()

        words: list[int] = [
            SPIRV_MAGIC,
            SPIRV_VERSION_1_0,
            0x00000000,
            self._next_id,
            0,
        ]
        # 1. Capability
        words.extend(inst(17, 1))  # Shader
        # 2. ExtInstImport
        words.extend(inst(11, self.glsl_ext_id, *encode_str_words("GLSL.std.450")))
        # 3. MemoryModel
        words.extend(inst(14, 0, 1))
        # 4. EntryPoint
        words.extend(inst(15, self.exec_model, self.entry_fn_id, *encode_str_words(self.entry_name), *self.interfaces))
        # 5. ExecutionModes
        for em in self.exec_modes:
            words.extend(em)
        # 6. Decorations
        for d in self.decorations:
            words.extend(d)
        # 7. Types, constants, global variables
        for item in self.types_consts_globals:
            words.extend(item)
        # 8. Entry function
        words.extend(inst(54, self.t_void(), self.entry_fn_id, 0, fn_ty))
        words.extend(inst(248, entry_lbl))
        for lv in self.func_locals:
            words.extend(lv)
        for bi in self.func_body:
            words.extend(bi)
        words.extend(inst(56))
        return words


def add_gx_scene_ubo(b: SpirvBuilder) -> tuple[int, int]:
    v4 = b.t_vec4()
    v2 = b.t_vec2()
    u32 = b.t_uint()
    f32 = b.t_float()
    members = [
        v4, v4, v4, v4,   # 0..3: uProjection rows (0..48)
        v4, v4, v4, v4,   # 4..7: uModelView rows (64..112)
        v4,               # 8: uTevColor0 (128)
        v4,               # 9: uKonstColor (144)
        v2,               # 10: uViewportSize (160)
        u32,              # 11: uEnableAlphaTest (168)
        f32,              # 12: uAlphaRef (172)
        u32,              # 13: uTevMode (176)
        f32,              # 14: uTevScale (180)
        u32,              # 15: uStage1Mode (184)
        f32,              # 16: uPad0 (188)
    ]
    offsets = [0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 168, 172, 176, 180, 184, 188]
    st = b.t_struct(members, "GXSceneConstants")
    b.decorate(st, DEC_BLOCK)
    for idx, off in enumerate(offsets):
        b.member_decorate(st, idx, DEC_OFFSET, off)
    var = b.global_var(SC_UNIFORM, st, is_interface=False)
    b.decorate(var, DEC_DESCRIPTOR_SET, 0)
    b.decorate(var, DEC_BINDING, 0)
    return var, st


def add_fxaa_ubo(b: SpirvBuilder) -> int:
    v2 = b.t_vec2()
    f32 = b.t_float()
    members = [
        v2,   # 0: uInvScreenSize (0)
        f32,  # 1: uSubpixQuality (8)
        f32,  # 2: uEdgeThreshold (12)
        f32,  # 3: uBrightness (16)
        f32,  # 4: uGamma (20)
        v2,   # 5: uPad (24)
    ]
    offsets = [0, 8, 12, 16, 20, 24]
    st = b.t_struct(members, "FxaaConstants")
    b.decorate(st, DEC_BLOCK)
    for idx, off in enumerate(offsets):
        b.member_decorate(st, idx, DEC_OFFSET, off)
    var = b.global_var(SC_UNIFORM, st, is_interface=False)
    b.decorate(var, DEC_DESCRIPTOR_SET, 0)
    b.decorate(var, DEC_BINDING, 0)
    return var


def build_gx_tev_vert() -> list[int]:
    b = SpirvBuilder(EXEC_VERTEX)
    ubo, _ = add_gx_scene_ubo(b)

    v2 = b.t_vec2()
    v3 = b.t_vec3()
    v4 = b.t_vec4()
    f32 = b.t_float()

    in_pos = b.global_var(SC_INPUT, v3, is_interface=True)
    b.decorate(in_pos, DEC_LOCATION, 0)
    in_clr = b.global_var(SC_INPUT, v4, is_interface=True)
    b.decorate(in_clr, DEC_LOCATION, 2)
    in_uv = b.global_var(SC_INPUT, v2, is_interface=True)
    b.decorate(in_uv, DEC_LOCATION, 3)

    per_vtx_st = b.t_struct([v4], "gl_PerVertex")
    b.decorate(per_vtx_st, DEC_BLOCK)
    b.member_decorate(per_vtx_st, 0, DEC_BUILTIN, BUILTIN_POSITION)
    out_per_vtx = b.global_var(SC_OUTPUT, per_vtx_st, is_interface=True)

    out_clr = b.global_var(SC_OUTPUT, v4, is_interface=True)
    b.decorate(out_clr, DEC_LOCATION, 0)
    out_uv = b.global_var(SC_OUTPUT, v2, is_interface=True)
    b.decorate(out_uv, DEC_LOCATION, 1)

    pos = b.load(v3, in_pos)
    px = b.extract(f32, pos, 0)
    py = b.extract(f32, pos, 1)
    pz = b.extract(f32, pos, 2)
    pos4 = b.construct(v4, px, py, pz, b.c_float(1.0))

    mv_rows = [b.load(v4, b.access(v4, SC_UNIFORM, ubo, b.c_sint(4 + i))) for i in range(4)]
    view_pos = b.construct(v4, *(b.dot(r, pos4) for r in mv_rows))

    proj_rows = [b.load(v4, b.access(v4, SC_UNIFORM, ubo, b.c_sint(i))) for i in range(4)]
    cx = b.dot(proj_rows[0], view_pos)
    cy = b.dot(proj_rows[1], view_pos)
    cz = b.dot(proj_rows[2], view_pos)
    cw = b.dot(proj_rows[3], view_pos)
    cz_d3d = b.fadd(f32, cz, cw)
    clip_pos = b.construct(v4, cx, cy, cz_d3d, cw)

    b.store(b.access(v4, SC_OUTPUT, out_per_vtx, b.c_sint(0)), clip_pos)
    b.store(out_clr, b.load(v4, in_clr))
    b.store(out_uv, b.load(v2, in_uv))
    b.func_body.append(inst(253))
    return b.build()


def build_gx_tev_frag() -> list[int]:
    b = SpirvBuilder(EXEC_FRAGMENT)
    ubo, _ = add_gx_scene_ubo(b)

    simg_ty = b.t_sampled_image2d()
    u_tex0 = b.global_var(SC_UNIFORM_CONSTANT, simg_ty)
    b.decorate(u_tex0, DEC_DESCRIPTOR_SET, 0)
    b.decorate(u_tex0, DEC_BINDING, 1)

    u_tex1 = b.global_var(SC_UNIFORM_CONSTANT, simg_ty)
    b.decorate(u_tex1, DEC_DESCRIPTOR_SET, 0)
    b.decorate(u_tex1, DEC_BINDING, 2)

    v2 = b.t_vec2()
    v3 = b.t_vec3()
    v4 = b.t_vec4()
    f32 = b.t_float()
    u32 = b.t_uint()

    in_clr = b.global_var(SC_INPUT, v4, is_interface=True)
    b.decorate(in_clr, DEC_LOCATION, 0)
    in_uv = b.global_var(SC_INPUT, v2, is_interface=True)
    b.decorate(in_uv, DEC_LOCATION, 1)

    out_frag = b.global_var(SC_OUTPUT, v4, is_interface=True)
    b.decorate(out_frag, DEC_LOCATION, 0)

    clr0 = b.load(v4, in_clr)
    uv0 = b.load(v2, in_uv)
    tev_color0 = b.load(v4, b.access(v4, SC_UNIFORM, ubo, b.c_sint(8)))
    en_alpha = b.load(u32, b.access(u32, SC_UNIFORM, ubo, b.c_sint(11)))
    alpha_ref = b.load(f32, b.access(f32, SC_UNIFORM, ubo, b.c_sint(12)))
    tev_mode = b.load(u32, b.access(u32, SC_UNIFORM, ubo, b.c_sint(13)))
    tev_scale = b.load(f32, b.access(f32, SC_UNIFORM, ubo, b.c_sint(14)))
    stage1_mode = b.load(u32, b.access(u32, SC_UNIFORM, ubo, b.c_sint(15)))

    tex0 = b.sample_implicit(b.load(simg_ty, u_tex0), uv0)
    tex1 = b.sample_implicit(b.load(simg_ty, u_tex1), uv0)

    clr0_rgb = b.shuffle(v3, clr0, clr0, 0, 1, 2)
    clr0_a = b.extract(f32, clr0, 3)
    tex0_rgb = b.shuffle(v3, tex0, tex0, 0, 1, 2)
    tex0_a = b.extract(f32, tex0, 3)
    tev0_rgb = b.shuffle(v3, tev_color0, tev_color0, 0, 1, 2)

    # Mode 0: texColor * clr0
    c_m0 = b.fmul(v4, tex0, clr0)
    # Mode 1: lerp(clr0.rgb, tex0.rgb, tex0.a), clr0.a
    m1_rgb = b.ext(v3, GLSL_FMIX, clr0_rgb, tex0_rgb, b.construct(v3, tex0_a, tex0_a, tex0_a))
    c_m1 = b.construct(v4, b.extract(f32, m1_rgb, 0), b.extract(f32, m1_rgb, 1), b.extract(f32, m1_rgb, 2), clr0_a)
    # Mode 2: lerp(clr0.rgb, 1, tex0.rgb), clr0.a * tex0.a
    m2_rgb = b.ext(v3, GLSL_FMIX, clr0_rgb, b.c_vec(v3, 1.0, 1.0, 1.0), tex0_rgb)
    c_m2 = b.construct(v4, b.extract(f32, m2_rgb, 0), b.extract(f32, m2_rgb, 1), b.extract(f32, m2_rgb, 2), b.fmul(f32, clr0_a, tex0_a))
    # Mode 3: tex0
    c_m3 = tex0
    # Mode 4: clr0
    c_m4 = clr0
    # Mode 5: tex0 * tev0
    c_m5 = b.fmul(v4, tex0, tev_color0)
    # Mode 6: lerp(clr0.rgb, tev0.rgb, tex0.rgb), clr0.a * tex0.a
    m6_rgb = b.ext(v3, GLSL_FMIX, clr0_rgb, tev0_rgb, tex0_rgb)
    c_m6 = b.construct(v4, b.extract(f32, m6_rgb, 0), b.extract(f32, m6_rgb, 1), b.extract(f32, m6_rgb, 2), b.fmul(f32, clr0_a, tex0_a))
    # Mode 7: tev0
    c_m7 = tev_color0

    out_c = c_m0
    for mode_idx, cand in [(1, c_m1), (2, c_m2), (3, c_m3), (4, c_m4), (5, c_m5), (6, c_m6), (7, c_m7)]:
        out_c = b.select_vec(v4, 4, b.ieq(tev_mode, b.c_uint(mode_idx)), cand, out_c)

    # Stage 1 ops (0=none, 1=mul alpha, 2=mul rgba, else=mul rgb)
    tex1_a = b.extract(f32, tex1, 3)
    s1_m1 = b.construct(v4, b.extract(f32, out_c, 0), b.extract(f32, out_c, 1), b.extract(f32, out_c, 2),
                        b.fmul(f32, b.extract(f32, out_c, 3), tex1_a))
    s1_m2 = b.fmul(v4, out_c, tex1)
    out_rgb_t1 = b.fmul(v3, b.shuffle(v3, out_c, out_c, 0, 1, 2), b.shuffle(v3, tex1, tex1, 0, 1, 2))
    s1_m3 = b.construct(v4, b.extract(f32, out_rgb_t1, 0), b.extract(f32, out_rgb_t1, 1), b.extract(f32, out_rgb_t1, 2),
                        b.extract(f32, out_c, 3))

    s1_res = s1_m3
    s1_res = b.select_vec(v4, 4, b.ieq(stage1_mode, b.c_uint(2)), s1_m2, s1_res)
    s1_res = b.select_vec(v4, 4, b.ieq(stage1_mode, b.c_uint(1)), s1_m1, s1_res)
    out_c = b.select_vec(v4, 4, b.ieq(stage1_mode, b.c_uint(0)), out_c, s1_res)

    # Scale RGB by uTevScale
    scaled_rgb = b.vec_scale(v3, b.shuffle(v3, out_c, out_c, 0, 1, 2), tev_scale)
    out_a = b.extract(f32, out_c, 3)
    out_c = b.construct(v4, b.extract(f32, scaled_rgb, 0), b.extract(f32, scaled_rgb, 1), b.extract(f32, scaled_rgb, 2), out_a)

    # Alpha test
    b_en = b.ine(en_alpha, b.c_uint(0))
    b_lt = b.flt(b.t_bool(), out_a, alpha_ref)
    do_discard = b.logical_and(b_en, b_lt)
    lbl_kill = b.new_id()
    lbl_keep = b.new_id()
    b.selection_merge(lbl_keep)
    b.branch_cond(do_discard, lbl_kill, lbl_keep)
    b.label(lbl_kill)
    b.kill()
    b.label(lbl_keep)
    b.store(out_frag, out_c)
    b.func_body.append(inst(253))
    return b.build()


def build_fxaa_vert() -> list[int]:
    b = SpirvBuilder(EXEC_VERTEX)
    u32 = b.t_uint()
    f32 = b.t_float()
    v2 = b.t_vec2()
    v4 = b.t_vec4()

    in_vid = b.global_var(SC_INPUT, u32, is_interface=True)
    b.decorate(in_vid, DEC_BUILTIN, BUILTIN_VERTEX_INDEX)

    per_vtx_st = b.t_struct([v4], "gl_PerVertex")
    b.decorate(per_vtx_st, DEC_BLOCK)
    b.member_decorate(per_vtx_st, 0, DEC_BUILTIN, BUILTIN_POSITION)
    out_per_vtx = b.global_var(SC_OUTPUT, per_vtx_st, is_interface=True)

    out_uv = b.global_var(SC_OUTPUT, v2, is_interface=True)
    b.decorate(out_uv, DEC_LOCATION, 0)

    vid = b.load(u32, in_vid)
    u_i = b.bitand(b.shl(vid, b.c_uint(1)), b.c_uint(2))
    v_i = b.bitand(vid, b.c_uint(2))
    u = b.utof(f32, u_i)
    v = b.utof(f32, v_i)
    px = b.fsub(f32, b.fmul(f32, u, b.c_float(2.0)), b.c_float(1.0))
    py = b.fsub(f32, b.c_float(1.0), b.fmul(f32, v, b.c_float(2.0)))
    clip_pos = b.construct(v4, px, py, b.c_float(0.0), b.c_float(1.0))
    uv = b.construct(v2, u, v)

    b.store(b.access(v4, SC_OUTPUT, out_per_vtx, b.c_sint(0)), clip_pos)
    b.store(out_uv, uv)
    b.func_body.append(inst(253))
    return b.build()


def emit_apply_display_grade(b: SpirvBuilder, rgb: int, u_brightness: int, u_gamma: int) -> int:
    v3 = b.t_vec3()
    f32 = b.t_float()
    zero3 = b.c_vec(v3, 0.0, 0.0, 0.0)
    one3 = b.c_vec(v3, 1.0, 1.0, 1.0)
    graded = b.ext(v3, GLSL_FCLAMP, rgb, zero3, one3)

    inv_g = b.fdiv(f32, b.c_float(1.0), b.ext(f32, GLSL_FMAX, u_gamma, b.c_float(0.25)))
    safe_base = b.ext(v3, GLSL_FMAX, graded, b.c_vec(v3, 1e-7, 1e-7, 1e-7))
    raw_pow = b.ext(v3, GLSL_POW, safe_base, b.construct(v3, inv_g, inv_g, inv_g))
    pos_mask = b.fgt(b.t_bvec(3), graded, zero3)
    safe_pow = b.emit_op_select_vec_mask(v3, pos_mask, raw_pow, zero3)

    diff_g = b.ext(f32, GLSL_FABS, b.fsub(f32, u_gamma, b.c_float(1.0)))
    use_gamma = b.fgt(b.t_bool(), diff_g, b.c_float(0.001))
    graded2 = b.select_vec(v3, 3, use_gamma, safe_pow, graded)
    return b.ext(v3, GLSL_FCLAMP, b.vec_scale(v3, graded2, u_brightness), zero3, one3)


def build_blit_frag() -> list[int]:
    b = SpirvBuilder(EXEC_FRAGMENT)
    ubo = add_fxaa_ubo(b)
    simg_ty = b.t_sampled_image2d()
    u_tex = b.global_var(SC_UNIFORM_CONSTANT, simg_ty)
    b.decorate(u_tex, DEC_DESCRIPTOR_SET, 0)
    b.decorate(u_tex, DEC_BINDING, 1)

    v2 = b.t_vec2()
    v3 = b.t_vec3()
    v4 = b.t_vec4()
    f32 = b.t_float()

    in_uv = b.global_var(SC_INPUT, v2, is_interface=True)
    b.decorate(in_uv, DEC_LOCATION, 0)
    out_frag = b.global_var(SC_OUTPUT, v4, is_interface=True)
    b.decorate(out_frag, DEC_LOCATION, 0)

    uv = b.load(v2, in_uv)
    u_bright = b.load(f32, b.access(f32, SC_UNIFORM, ubo, b.c_sint(3)))
    u_gamma = b.load(f32, b.access(f32, SC_UNIFORM, ubo, b.c_sint(4)))

    tex = b.sample_lod0(b.load(simg_ty, u_tex), uv)
    rgb = emit_apply_display_grade(b, b.shuffle(v3, tex, tex, 0, 1, 2), u_bright, u_gamma)
    out4 = b.construct(v4, b.extract(f32, rgb, 0), b.extract(f32, rgb, 1), b.extract(f32, rgb, 2), b.c_float(1.0))
    b.store(out_frag, out4)
    b.func_body.append(inst(253))
    return b.build()


def build_fxaa_frag() -> list[int]:
    b = SpirvBuilder(EXEC_FRAGMENT)
    ubo = add_fxaa_ubo(b)
    simg_ty = b.t_sampled_image2d()
    u_tex = b.global_var(SC_UNIFORM_CONSTANT, simg_ty)
    b.decorate(u_tex, DEC_DESCRIPTOR_SET, 0)
    b.decorate(u_tex, DEC_BINDING, 1)

    v2 = b.t_vec2()
    v3 = b.t_vec3()
    v4 = b.t_vec4()
    f32 = b.t_float()

    in_uv = b.global_var(SC_INPUT, v2, is_interface=True)
    b.decorate(in_uv, DEC_LOCATION, 0)
    out_frag = b.global_var(SC_OUTPUT, v4, is_interface=True)
    b.decorate(out_frag, DEC_LOCATION, 0)

    out_rgb_var = b.local_var(v3)

    uv = b.load(v2, in_uv)
    inv_sz = b.load(v2, b.access(v2, SC_UNIFORM, ubo, b.c_sint(0)))
    u_subpix = b.load(f32, b.access(f32, SC_UNIFORM, ubo, b.c_sint(1)))
    u_edge = b.load(f32, b.access(f32, SC_UNIFORM, ubo, b.c_sint(2)))
    u_bright = b.load(f32, b.access(f32, SC_UNIFORM, ubo, b.c_sint(3)))
    u_gamma = b.load(f32, b.access(f32, SC_UNIFORM, ubo, b.c_sint(4)))
    simg = b.load(simg_ty, u_tex)

    def sample_rgb(coord: int) -> int:
        s4 = b.sample_lod0(simg, coord)
        return b.shuffle(v3, s4, s4, 0, 1, 2)

    rgbM = sample_rgb(uv)
    rgbNW = sample_rgb(b.fadd(v2, uv, b.fmul(v2, b.c_vec(v2, -1.0, -1.0), inv_sz)))
    rgbNE = sample_rgb(b.fadd(v2, uv, b.fmul(v2, b.c_vec(v2, 1.0, -1.0), inv_sz)))
    rgbSW = sample_rgb(b.fadd(v2, uv, b.fmul(v2, b.c_vec(v2, -1.0, 1.0), inv_sz)))
    rgbSE = sample_rgb(b.fadd(v2, uv, b.fmul(v2, b.c_vec(v2, 1.0, 1.0), inv_sz)))

    luma_w = b.c_vec(v3, 0.299, 0.587, 0.114)
    lM = b.dot(rgbM, luma_w)
    lNW = b.dot(rgbNW, luma_w)
    lNE = b.dot(rgbNE, luma_w)
    lSW = b.dot(rgbSW, luma_w)
    lSE = b.dot(rgbSE, luma_w)

    lMin = b.ext(f32, GLSL_FMIN, lM, b.ext(f32, GLSL_FMIN, b.ext(f32, GLSL_FMIN, lNW, lNE), b.ext(f32, GLSL_FMIN, lSW, lSE)))
    lMax = b.ext(f32, GLSL_FMAX, lM, b.ext(f32, GLSL_FMAX, b.ext(f32, GLSL_FMAX, lNW, lNE), b.ext(f32, GLSL_FMAX, lSW, lSE)))
    lRange = b.fsub(f32, lMax, lMin)
    thresh = b.ext(f32, GLSL_FMAX, b.c_float(0.0312), b.fmul(f32, lMax, u_edge))
    skip_fxaa = b.flt(b.t_bool(), lRange, thresh)

    lbl_skip = b.new_id()
    lbl_fxaa = b.new_id()
    lbl_merge = b.new_id()
    b.selection_merge(lbl_merge)
    b.branch_cond(skip_fxaa, lbl_skip, lbl_fxaa)

    b.label(lbl_skip)
    b.store(out_rgb_var, rgbM)
    b.branch(lbl_merge)

    b.label(lbl_fxaa)
    dx = b.fsub(f32, b.fadd(f32, lSW, lSE), b.fadd(f32, lNW, lNE))
    dy = b.fsub(f32, b.fadd(f32, lNW, lSW), b.fadd(f32, lNE, lSE))
    dir_raw = b.construct(v2, dx, dy)
    dir_sum = b.fadd(f32, b.fadd(f32, lNW, lNE), b.fadd(f32, lSW, lSE))
    dir_reduce = b.ext(f32, GLSL_FMAX, b.fmul(f32, dir_sum, b.c_float(0.25 / 8.0)), b.c_float(1.0 / 128.0))
    rcp_dir_min = b.fdiv(
        f32,
        b.c_float(1.0),
        b.fadd(
            f32,
            b.ext(f32, GLSL_FMIN, b.ext(f32, GLSL_FABS, dx), b.ext(f32, GLSL_FABS, dy)),
            dir_reduce,
        ),
    )
    dir_clamped = b.ext(
        v2,
        GLSL_FCLAMP,
        b.vec_scale(v2, dir_raw, rcp_dir_min),
        b.c_vec(v2, -8.0, -8.0),
        b.c_vec(v2, 8.0, 8.0),
    )
    dir_uv = b.fmul(v2, dir_clamped, inv_sz)

    rgbA = b.vec_scale(
        v3,
        b.fadd(
            v3,
            sample_rgb(b.fadd(v2, uv, b.vec_scale(v2, dir_uv, b.c_float(1.0 / 3.0 - 0.5)))),
            sample_rgb(b.fadd(v2, uv, b.vec_scale(v2, dir_uv, b.c_float(2.0 / 3.0 - 0.5)))),
        ),
        b.c_float(0.5),
    )
    rgbB = b.fadd(
        v3,
        b.vec_scale(v3, rgbA, b.c_float(0.5)),
        b.vec_scale(
            v3,
            b.fadd(
                v3,
                sample_rgb(b.fadd(v2, uv, b.vec_scale(v2, dir_uv, b.c_float(-0.5)))),
                sample_rgb(b.fadd(v2, uv, b.vec_scale(v2, dir_uv, b.c_float(0.5)))),
            ),
            b.c_float(0.25),
        ),
    )
    lB = b.dot(rgbB, luma_w)
    out_of_range = b.logical_or(b.flt(b.t_bool(), lB, lMin), b.fgt(b.t_bool(), lB, lMax))
    fx_rgb = b.select_vec(v3, 3, out_of_range, rgbA, rgbB)
    subpix = b.ext(f32, GLSL_FCLAMP, u_subpix, b.c_float(0.0), b.c_float(1.0))
    blended = b.ext(v3, GLSL_FMIX, rgbM, fx_rgb, b.construct(v3, subpix, subpix, subpix))
    b.store(out_rgb_var, blended)
    b.branch(lbl_merge)

    b.label(lbl_merge)
    final_rgb = emit_apply_display_grade(b, b.load(v3, out_rgb_var), u_bright, u_gamma)
    out4 = b.construct(
        v4,
        b.extract(f32, final_rgb, 0),
        b.extract(f32, final_rgb, 1),
        b.extract(f32, final_rgb, 2),
        b.c_float(1.0),
    )
    b.store(out_frag, out4)
    b.func_body.append(inst(253))
    return b.build()


def format_u32_array(name: str, words: list[int]) -> str:
    lines = [f"inline constexpr uint32_t {name}[{len(words)}] = {{"]
    for i in range(0, len(words), 8):
        chunk = ", ".join(f"0x{w:08X}u" for w in words[i:i + 8])
        lines.append(f"    {chunk},")
    lines.append("};")
    return "\n".join(lines)


def main() -> int:
    shaders = [
        ("kGxTevVertSpv", build_gx_tev_vert()),
        ("kGxTevFragSpv", build_gx_tev_frag()),
        ("kFxaaVertSpv", build_fxaa_vert()),
        ("kBlitFragSpv", build_blit_frag()),
        ("kFxaaFragSpv", build_fxaa_frag()),
    ]
    out_path = Path(__file__).resolve().parent.parent / "include" / "pn03_vulkan_shaders.hpp"
    header = [
        "#pragma once",
        "// Auto-generated by tools/gen_vulkan_shaders.py -- do not edit manually.",
        "",
        "#include <cstdint>",
        "",
        "namespace pn03::vk_shaders {",
        "",
    ]
    for name, words in shaders:
        header.append(format_u32_array(name, words))
        header.append("")
    header.append("} // namespace pn03::vk_shaders")
    header.append("")
    out_path.write_text("\n".join(header), encoding="utf-8")
    for name, words in shaders:
        print(f"[SPV-GEN] {name}: {len(words)} words ({len(words) * 4} bytes)")
    print(f"[SPV-GEN] Wrote {out_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
