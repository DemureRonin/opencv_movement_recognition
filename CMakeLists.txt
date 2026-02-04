cmake_minimum_required(VERSION 4.0)
project(video_process)

set(CMAKE_CXX_STANDARD 20)

add_executable(video_process main.cpp)


target_include_directories(video_process PRIVATE ${CMAKE_SOURCE_DIR}/include)


target_link_libraries(video_process
        debug ${CMAKE_SOURCE_DIR}/lib/opencv_world4120d.lib
        optimized ${CMAKE_SOURCE_DIR}/lib/opencv_world4120.lib
)
if (WIN32)
    add_custom_command(TARGET video_process POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/bin/opencv_world4120.dll
            $<TARGET_FILE_DIR:video_process>
    )

    add_custom_command(TARGET video_process POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/bin/opencv_world4120d.dll
            $<TARGET_FILE_DIR:video_process>
    )
endif()
