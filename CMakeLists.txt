cmake_minimum_required(VERSION 3.10)
project(GraveyBoy)

set(CMAKE_CXX_STANDARD 17)


if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/deps/SDL2/include)
    link_directories(${CMAKE_SOURCE_DIR}/deps/SDL2/lib/x64)
    
    set(SDL2_LIBS SDL2main SDL2)
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    set(SDL2_LIBS ${SDL2_LIBRARIES})
endif()

file(GLOB_RECURSE SOURCES 
    main.cpp 
    src/*.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBS})

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/deps/SDL2/bin/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()