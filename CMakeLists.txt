
cmake_minimum_required (VERSION 3.8)

project ("polishcow")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (polishcow "polishcow.cpp" "polishcow.h"      )

add_custom_target("Copy" ALL 
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/megadata/ $<TARGET_FILE_DIR:polishcow>/megadata)

target_link_libraries(polishcow sfml-graphics sfml-audio)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
