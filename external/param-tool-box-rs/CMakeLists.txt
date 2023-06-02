cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    param-tool-box-rs
    GIT_REPOSITORY https://github.com/hansen-audio/param-tool-box-rs.git
    GIT_TAG main
)

FetchContent_GetProperties(param-tool-box-rs)
if(NOT fx-collection-rs_POPULATED)
    FetchContent_Populate(param-tool-box-rs)
endif()

corrosion_import_crate(MANIFEST_PATH ${param-tool-box-rs_SOURCE_DIR}/Cargo.toml)

target_include_directories(param-tool-box-rs 
    INTERFACE 
        ${param-tool-box-rs_SOURCE_DIR}/include
)
