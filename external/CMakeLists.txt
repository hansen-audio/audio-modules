cmake_minimum_required(VERSION 3.15.0)

if(NOT HA_GIT_REPOSITORY_URL)
    set(HA_GIT_REPOSITORY_URL "https://www.github.com")
endif()

add_subdirectory(corrosion)
add_subdirectory(fx-collection-rs)
add_subdirectory(aligned-allocator)
add_subdirectory(param-tool-box-rs)
add_subdirectory(fx-collection)
