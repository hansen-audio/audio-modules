cmake_minimum_required(VERSION 3.14.0)

project(ha-audio-modules)

add_subdirectory(external)

add_library(audio-modules STATIC
    include/ha/audio_modules/module.h
    include/ha/audio_modules/audio_modules.h
    include/ha/audio_modules/convert_funcs.h
    include/ha/audio_modules/module_factory.h
    include/ha/audio_modules/module_tags.h
    include/ha/audio_modules/param_info.h
    include/ha/audio_modules/types.h
    source/factory/module_factory.cpp
    source/trance_gate/trance_gate_config.cpp
    source/trance_gate/trance_gate_config.h
    source/trance_gate/trance_gate_processor.cpp
    source/trance_gate/trance_gate_processor.h
    source/trance_gate/silence_detection.cpp
    source/trance_gate/silence_detection.h
)

target_include_directories(audio-modules
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/source
)

target_link_libraries(audio-modules
    PRIVATE
        aligned-allocator
        fx-collection
        param-tool-box
)

target_compile_features(audio-modules
    PUBLIC 
        cxx_std_17
)

enable_testing()

add_executable(audio-modules_test
    test/trance_gate_processor_test.cpp
    test/thread_malloc_detector.cpp
    test/thread_malloc_detector.h
    test/module_factory_test.cpp
)

target_link_libraries(audio-modules_test
    PRIVATE
        aligned-allocator
        audio-modules
        fx-collection
        gtest
        gtest_main
)

target_include_directories(audio-modules_test
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/source
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/test
)

add_test(NAME audio-modules_test 
    COMMAND audio-modules_test
)