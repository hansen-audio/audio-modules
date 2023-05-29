cmake_minimum_required(VERSION 3.15.0)

#include(FetchContent)
#
#FetchContent_Declare(
#    fx-collection-rs
#    GIT_REPOSITORY ${HA_GIT_REPOSITORY_URL}/hansen-audio/fx-collection-rs.git
#    GIT_TAG main
#)
#
#FetchContent_GetProperties(fx-collection-rs)
#if(NOT fx-collection-rs_POPULATED)
#    FetchContent_Populate(fx-collection-rs)
#endif()

set (param-tool-box-rs_SOURCE_DIR "/mnt/veracrypt2/Developer/github/hansen-audio/param-tool-box-rs")
corrosion_import_crate(MANIFEST_PATH ${param-tool-box-rs_SOURCE_DIR}/Cargo.toml)

target_include_directories(param-tool-box-rs 
    INTERFACE 
        ${param-tool-box-rs_SOURCE_DIR}/include
)