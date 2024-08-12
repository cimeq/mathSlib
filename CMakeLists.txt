cmake_minimum_required(VERSION 3.14)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(MathS VERSION 2.2.0)

#Set Version
message(STATUS "Compiling Version: ${${PROJECT_NAME}_VERSION} of project ${PROJECT_NAME}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "export the build rules into a JSON files for clang-tidy" FORCE)

#If the library is interface only use the keywork INTERFACE. If the library contain cpp files, use STATIC
add_library(${PROJECT_NAME} STATIC EXCLUDE_FROM_ALL
        mathS/src/Evaluate.cpp
        mathS/src/ExtendedCMath.cpp
        mathS/src/LBAssembler.cpp
        mathS/src/lexer.cpp
        mathS/src/MathObject.cpp
        mathS/src/MathParser.cpp
        mathS/src/NFunction.cpp
        mathS/src/NFunctionalOperator.cpp
        mathS/src/NMathObject.cpp
        mathS/src/Rule.cpp
        mathS/src/RuleLib.cpp
        mathS/src/string-switch.cpp
        )
#adding a namespace for the library
add_library(CIMEQ_Libraries::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/mathS/include
        )

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        USE_NEWLIB
        )

target_compile_options(${PROJECT_NAME}
        PRIVATE
        "-Wno-unused-parameter"
        "-Os"
        )

get_target_property(_TARGET_TYPE ${PROJECT_NAME} TYPE)
if(_TARGET_TYPE STREQUAL "INTERFACE_LIBRARY")
    set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_VERSION ${PROJECT_VERSION} )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} )
endif()
