cmake_minimum_required(VERSION 3.21)
project(lab)

set(CMAKE_CXX_STANDARD 17 )

# Добавьте каталог Python include и найдите каталог, в который вы установили python. Путь установки Python по умолчанию: "C: \ Users \ ваше собственное имя пользователя \ AppData \ Local \ Programs \ Python"
#include_directories(C:\\Users\\micha\\AppData\\Local\\Programs\\Python\\Python39\\include)
#include_directories(C:/Users/micha/anaconda3/include)

include_directories(C:\\Users\\micha\\AppData\\Local\\Programs\\Python\\Python39\\Lib/site-packages/numpy/core/include)
#"C:/Users/micha/anaconda3/Lib/site-packages/numpy/core/include"

# Добавьте библиотеку Python lib, а также найдите файл python37.lib в папке libs в каталоге установки python
#link_libraries(C:/Users/micha/AppData/Local/Programs/Python/Python39/libs/python39.lib)
#link_libraries(C:/Users/micha/anaconda3/libs/python39.lib)



add_executable(lab main.cpp tube_array.h tube_array.tpp)

