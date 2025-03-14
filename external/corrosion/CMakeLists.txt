cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    Corrosion
    GIT_REPOSITORY https://github.com/AndrewGaspar/corrosion.git
    GIT_TAG v0.5.1
)

FetchContent_MakeAvailable(Corrosion)
