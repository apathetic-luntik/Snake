cmake_minimum_required(VERSION 3.16)

project(Snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка директории для исполняемых файлов в папку build внутри каталога сборки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Поиск необходимых пакетов Qt6: Core, Gui и Widgets
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

file(GLOB SOURCES "src/*.cpp")

file(GLOB HEADERS "src/*.h")

file(GLOB UI_FILES "src/*.ui")

# Обработка UI файлов для генерации соответствующих заголовочных файлов
qt6_wrap_ui(UI_HEADERS ${UI_FILES})

# Создание исполняемого файла проекта с использованием найденных исходников, заголовков и сгенерированных UI заголовков
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_HEADERS}
)

# Добавление директории src в список путей для поиска заголовочных файлов при компиляции
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Добавление определения макроса QT_DEPRECATED_WARNINGS для компилятора
target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DEPRECATED_WARNINGS)

# Линковка с необходимыми библиотеками Qt6: Core, Gui и Widgets
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
