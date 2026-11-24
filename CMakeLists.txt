cmake_minimum_required(VERSION 3.20)
project(PN03_WinPort VERSION 2.4.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8 /bigobj /MP)
    add_compile_definitions(NOMINMAX _CRT_SECURE_NO_WARNINGS)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(PN03_RUNTIME_SOURCES
    src/runtime/config.cpp
    src/runtime/pn03_logger.cpp
    src/runtime/iso_reader.cpp
    src/runtime/pad_xinput.cpp
    src/runtime/gx_renderer.cpp
    src/runtime/gx_3d_interface.cpp
    src/runtime/audio_ax_hle.cpp
    src/runtime/localization_zh.cpp
    src/runtime/dolphin_sdk_hle.cpp
    src/runtime/win32_d3d11_host.cpp
    src/runtime/win32_vulkan_host.cpp
    src/launcher/win32_cyber_launcher.cpp
    src/decompiled/function_table_registry.cpp
    src/decompiled/indirect_call_table.cpp
    src/decompiled/tools_rel_decompiled.cpp
)

# Full static recompilation translation units (all 6,246 main.dol functions across 9 subsystems)
option(PN03_BUILD_ALL_RECOMP_UNITS "Compile all 9 subsystem static recompilation units (6,246 functions)" ON)
if(PN03_BUILD_ALL_RECOMP_UNITS)
    file(GLOB PN03_SUBSYS_SOURCES "src/decompiled/subsystems/*.cpp")
    list(APPEND PN03_RUNTIME_SOURCES ${PN03_SUBSYS_SOURCES})
endif()

add_executable(PN03_WinPort
    src/launcher/launcher_main.cpp
    ${PN03_RUNTIME_SOURCES}
)

if(WIN32)
    target_link_libraries(PN03_WinPort PRIVATE xinput d3d11 dxgi d3dcompiler xaudio2 ole32 comdlg32 user32 gdi32 gdiplus dwmapi msimg32 winmm shell32)
endif()

add_executable(pn03_cpp_tests
    tests/test_runtime_cpp.cpp
    ${PN03_RUNTIME_SOURCES}
)
if(WIN32)
    target_link_libraries(pn03_cpp_tests PRIVATE xinput d3d11 dxgi d3dcompiler xaudio2 ole32 comdlg32 user32 gdi32 gdiplus dwmapi msimg32 winmm shell32)
endif()

enable_testing()
add_test(NAME PN03RuntimeCppTests COMMAND pn03_cpp_tests)
