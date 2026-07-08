```md
本文内容来源是github的Modern-CMake

有兴趣的朋友可以去阅读原文 这里仅是本人的学习记录

https://modern-cmake-cn.github.io/Modern-CMake-zh_CN/README_GitBook.html
```

# 现代CMake

## 行为准则

* 不要使用具有全局作用域的函数

* 不要添加非必要的PUBLIC要求

* 不要在file函数中添加GLOB文件

* 将库直接连接到需要构建的目标上

* 当链接库文件时，不要省略PUBLIC或PRIVATE关键字

* 把CMake程序视作代码

* 建立目标观念

* 导出你的接口

* 为库书写一个Config.cmake文件

* 声明一个ALIAS目标以保持使用的一致性

* 将常见的功能合并到有详细文档的函数或宏中

* 使用小写的函数名

* 使用cmake_policy 和/或 限定版本号范围

## 基础知识

* 最低版本要求
  
  * cmake_minmun_required本身是不区分大小写的 一般小写
  
  * `VERSION` 和它后面的版本号是这个函数的特殊关键字

```cmake
cmake_minmun_required(VERSION 3.1)
```

* 设置一个项目
  
  * 当前函数的第一个参数代表的是项目的名称
  
  * VERSION 对应项目的版本
  
  * 

```cmake
project(MyProject VERSION 1.0 
                  DESCRIPTION "Very nice project"
                  LANGUAGES CXX)
```

* 生成一个可执行文件
  
  * one`one` 既是生成的可执行文件的名称，也是创建的 `CMake` 目标(target)的名称

```cmake
add_executable(one two.cpp three.h)
```

* 生成一个库
  
  * 库的类型可以通过第二个参数进行定义包含
    
    * STATIC
    
    * SHARED
    
    * MODULE
    
    * 如果你不选择它，CMake 将会通过 `BUILD_SHARED_LIBS` 的值来选择构建 STATIC 还是 SHARED 类型的库

```cmake
add_library(one STATIC two.cpp three.h)
```

* 为目标添加一个头文件目录
  
  * #### 可见性修饰符
    
    * PUBLIC 当前目标及依赖者都生效
    
    * PROVATE 只影响当前目标，不影响依赖
    
    * INIERFACE 只影响依赖

```cmake
target_include_directories(one PUBLIC include)
```

* 将目标之间链接起来
  
  * 这个命令需要指定一个目标 `another`，并且在给出该目标的名字（ `another` ）后为此目标添加一个依赖 `one`

```cmake
# 生成一个库
add_library(another STATIC another.cpp another.h)
# 给库目标添加依赖
target_link_library(another PUBLIC one)
```

* 一个简单的CMakeLists.txt

```cmake
camke_minmun_required(VERSION 3.8)
project(Calcular LANGUAGES CXX)

# 创建一个库目标calclib
add_library(calclib STATIC src/calclib.cpp include/calc/lib.hpp)
# 为库目标calclib添加头文件目录
target_include_directories(calclib PUBLIC include)
# 用于指定目标所需的编译器特性
targrt_compile_features(calclib PUBLIC cxx_std_11)
# 创建可执行文件目标calc
add_executable(calc apps/calc.cpp)
# 将库目标calclib链接到可执行目标calc
target_link_libraries(calc PUBLIC calclib)
```


