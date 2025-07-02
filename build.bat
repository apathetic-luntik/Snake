@echo off
REM Скрипт для сборки проекта Snake с использованием CMake на Windows

REM Создаем папку build, если ее нет
if not exist build (
    mkdir build
)

REM Переходим в папку build
cd build

REM Генерируем файлы сборки
cmake ..

REM Собираем проект
cmake --build .

REM Возвращаемся в корень проекта
cd ..
