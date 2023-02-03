
project (world)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    Actor.cpp
    App.cpp
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
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
        DEBUG_POSTFIX "-d"
)