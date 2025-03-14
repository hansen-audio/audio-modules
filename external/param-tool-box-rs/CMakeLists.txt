cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    param-tool-box-rs
    GIT_REPOSITORY https://github.com/hansen-audio/param-tool-box-rs.git
    GIT_TAG main
)

FetchContent_MakeAvailable(param-tool-box-rs)

corrosion_import_crate(MANIFEST_PATH ${param-tool-box-rs_SOURCE_DIR}/Cargo.toml)

target_include_directories(param_tool_box_rs 
    INTERFACE 
        ${param-tool-box-rs_SOURCE_DIR}/include
)
