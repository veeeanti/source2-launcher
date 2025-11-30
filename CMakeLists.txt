cmake_minimum_required(VERSION 3.18)
project(HLVRLauncher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hlvr_launcher
    hlvr_launcher.cpp
    hlvr_launcher.rc
)

if(WIN64)
    target_compile_definitions(hlvr_launcher PRIVATE -DPLATFORM_WINDOWS64)
endif()

set_target_properties(hlvr_launcher PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)