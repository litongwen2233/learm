---
title: '''Cmake_one'''
date: 2026-06-28 17:55:46
tags:
---
# Cmake学习第一章
* 一切皆Target
## CMake是什么
* 是一个生成器 去指挥别人干活
    * 读取你写的CMakeListe.txt,再去生成对应具体工作的文件
* CMake有两个阶段 ` 配置 ` ` 构建 `
    * 配置阶段
    
    ``` cmake
    cmake -S. -B build
    -S 指定源码目录 -B 指定构建目录
    ```    
    * 构建阶段
    ``` cmake
    cmake --build build
    找到build目录里生成构建脚本 然后调用对应的工具去做具体的事
    ```
* 养成源码外构建的习惯
    * 将构建的东西都放入到build 与源码进行隔离
## 第一个小项目
* 第一段代码 helloc world
``` C++
    #include<iostream>
    int main()
    {
        std::cout<<"Helloc CMake,this is the real world."<<std::endl;
        return 0;
    }
```
* 第一段代码对应的CMakeLists.txt
``` CMake
cmake_minimum_require(VERSION 3.20)
project(helloc_cmake LANGUAES CXX)
add_executable(helloc_cmake main.cpp)
set_project(TARGET helloc_cmake PROPERTY CXX_STANDARD 17)
    * cmake_minimum_require 对于cmake的最低版本要求
    * project 定义项目的名称和主要语言
    * add_executable 定义了一个名叫helloc_cmake的可执行文件Target，这个Target的源文件是main.cpp
    * set_project 是给helloc_cmake这个Target设置属性
```
* 运行
```
#配置
cmake -S. -B build
#构建
cmake --build build
#运行
./build/helloc_cmake
```
## 拥抱现代cmake 一切为了Target
* 一切都是Target 一切属性都应该附加到Target上
### 升级项目
* 目录结构
```
|--CMakeLists.txt
|--src
    |--CMakeLists.txt
    |--main.cpp
    |--math_utils.cpp
    |--math_utils.h
```
* math_utils.h
```C++
#pragma once
int add(int a,int b);
```
* math_utils.cpp
```C++
#include"math_utils.h"
int add(int a,int b)
{
    return a+b;
}
```
* main.cpp
```C++
#include<iostream>
#include"math_utils"
int main()
{
    std::cout<<"1 + 1 = "<<add(1,1)<<std::endl;
    return 0;
}
```
* 文件根目录下的CMakeLists.txt
```CMake
cmake_minmun_required(VERSION 3.20)
project(terget_demo LANGUAGES CXX)

add_subdirectory(src)
```
* src目录下的CMakeLists.txt
```CMake
# 定义一个名叫math_utils的库 Target
add_library(math_utils math_utils.cpp)
# 给math_utils这个Target添加一个属性 它的头文件目录
target_include_directoryies(math_utils 
    PUBLIC 
    $(CMAKE_CURRENT_SOURCE_DIR)
)
# 定义一个名叫dmeo的可执行文件 Target
add_executable(demo main.cpp)
# 给demo这个Target添加一个属性 它需要链接math_utils库
target_link_libraries(demo PRIVATE math_utils    
)
# 给demo这个Target 设置C++标准
set_property(TARGET demo PROPERTY CXX_STANDARD 17)
```
## 接入第三方库
* 现代CMake接入第三方库的主流方式是 find_package
* 一个好的三方库会提供一个...Config.cmake文件 find_package就是去找这个文件
* 找到...Config.cmake文件后 find_package会自动生成一个导入的Target(Imported Target)
### 示例
* CMakeLists.txt
```CMake
cmake_minimum_required(VERSION 3.20)
project(find_package_demo LANGUAGES CXX)
# 查找spdlog库 并且要求必须找到
find_package(spdlog REQUIRED)
add_executable(my_app main.cpp)
# 链接spdlog提供的导入Target
target_link_libraries(my_app
    PRIVATE
    spdlog::spdlog
    )
set_property(TARGET my_app PROPERTY CXX_STANDARD 17)
```
* main.cpp
```C++
#include"spdlog/sdplog.h"
int main()
{
    spdlog::info("Welcome to spdlog!");
    return 0;
}
```
## 管理更大的工程 添加开关
* 大型项目用到Debug/Release版本切换 或者某些功能按需编译
* Release
```CMake
cmake -S . -B builed
-DCMAKE_BUILD_TYPE=Release
```
* 功能开关
```CMake
option(ENABLE_DEBUG_UTILS "Enable debug utilities" OFF)
if(ENABLE_DEBUG_UTILS)
#如果开关打开了 就添加了debug_tils这个子目录
add_subdirectory(debug_utils)
endif()
```

