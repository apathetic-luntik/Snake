cmake_minimum_required(VERSION 3.16)

project(Snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt6 COMPONENTS Core Gui Widgets Test REQUIRED)

file(GLOB SOURCES "src/*.cpp")

file(GLOB HEADERS "src/*.h")

file(GLOB UI_FILES "src/*.ui")

qt6_wrap_ui(UI_HEADERS ${UI_FILES})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DEPRECATED_WARNINGS)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

file(GLOB TEST_SOURCES "src/tests/*.cpp")

add_executable(SnakeTests ${TEST_SOURCES})

target_include_directories(SnakeTests PRIVATE src)

target_link_libraries(SnakeTests PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test)
