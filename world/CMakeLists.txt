
project (world)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    Actor.cpp
    App.cpp
    TextureManager.cpp
    world.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
        FMT
        SFML::system
        SFML::graphics
        SFML::window
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        fmt
        sfml-system
        sfml-graphics
        sfml-window
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}
        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)