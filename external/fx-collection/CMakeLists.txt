cmake_minimum_required (VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    ha-fx-collection
    GIT_REPOSITORY https://github.com/hansen-audio/fx-collection.git
    GIT_TAG master
)

FetchContent_MakeAvailable(ha-fx-collection)
