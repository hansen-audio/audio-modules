cmake_minimum_required(VERSION 3.20.0)

include(FetchContent)

FetchContent_Declare(
    fx-collection-rs
    GIT_REPOSITORY https://github.com/hansen-audio/fx-collection-rs.git
    GIT_TAG main
)

FetchContent_MakeAvailable(fx-collection-rs)

corrosion_import_crate(MANIFEST_PATH ${fx-collection-rs_SOURCE_DIR}/Cargo.toml)

target_include_directories(fx_collection_rs 
    INTERFACE 
        ${fx-collection-rs_SOURCE_DIR}/include
)
