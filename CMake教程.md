# CMake 从入门到实战 — 完整教程

> CMake 是一款开源、跨平台的自动化构建系统生成器。它不直接编译代码，而是根据 `CMakeLists.txt` 配置文件生成 Makefile、Visual Studio 项目等构建文件，再由底层构建工具完成编译。

---

## 目录

- [1. CMake 简介](#1-cmake-简介)
- [2. 安装 CMake](#2-安装-cmake)
- [3. 工作流程](#3-工作流程)
- [4. 渐进式教程：从最简单到完整项目](#4-渐进式教程从最简单到完整项目)
- [5. 常用命令速查](#5-常用命令速查)
- [6. 变量系统](#6-变量系统)
- [7. 现代 CMake 最佳实践](#7-现代-cmake-最佳实践)
- [8. 安装与打包](#8-安装与打包)
- [9. 调试技巧](#9-调试技巧)
- [10. 综合实战案例：计算器项目](#10-综合实战案例计算器项目)

---

## 1. CMake 简介

### 什么是 CMake？

CMake（Cross-Platform Make）是一个**构建系统生成器**，而非编译器。它的核心思路是：

```
编写 CMakeLists.txt → cmake 生成构建文件 → make / msbuild 编译 → 得到可执行文件
```

### 为什么用 CMake？

| 优势 | 说明 |
|------|------|
| 跨平台 | 同一份配置可在 Linux、macOS、Windows 上生成对应的构建文件 |
| 大项目标配 | LLVM、OpenCV、Boost 等知名项目均使用 CMake |
| 依赖管理 | `find_package` 自动查找第三方库 |
| 现代化 | `target_*` 系列命令精确控制编译属性，告别全局污染 |

---

## 2. 安装 CMake

### Linux（Ubuntu/Debian）

```bash
sudo apt update
sudo apt install cmake build-essential
```

### macOS

```bash
brew install cmake
```

### Windows

- 官网下载安装包：https://cmake.org/download/
- 或通过 `winget install cmake`

### 验证安装

```bash
cmake --version
# 输出如：cmake version 3.28
```

---

## 3. 工作流程

### 推荐：Out-of-source 构建

保持源码目录干净，在单独的 `build` 目录中构建：

```bash
mkdir build && cd build
cmake ..          # 配置，生成构建文件
make              # 编译
./myapp           # 运行
```

### 项目目录结构示例

```
MyProject/
├── CMakeLists.txt
├── include/
│   └── myheader.h
├── src/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   └── utils.cpp
├── lib/
│   ├── CMakeLists.txt
│   └── mylib.cpp
└── build/        # 构建输出目录（不提交到 Git）
```

---

## 4. 渐进式教程：从最简单到完整项目

### 第 0 步：最简单的项目

单文件编译，只需 3 行：

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)
add_executable(myapp main.cpp)
```

> `cmake_minimum_required` 指定最低 CMake 版本；`project` 定义项目名；`add_executable` 声明可执行目标。

### 第 1 步：添加多个源文件

用 `set` 定义源文件列表变量：

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(SRC_FILES main.cpp utils.cpp helper.cpp)
add_executable(myapp ${SRC_FILES})
```

### 第 2 步：自动收集源文件

用 `aux_source_directory` 自动收集目录下所有 `.cpp` 文件，省去手动列举：

```cmake
aux_source_directory(. SRC_FILES)
add_executable(myapp ${SRC_FILES})
```

> ⚠️ `aux_source_directory` 不会递归子目录，新增文件需重新运行 cmake。

### 第 3 步：添加头文件搜索路径

```cmake
include_directories(include third_party/include)
aux_source_directory(. SRC_FILES)
add_executable(myapp ${SRC_FILES})
```

> 这样代码中可直接 `#include "myheader.h"`，无需写完整路径。

### 第 4 步：项目结构化（多目录）

根目录 `CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

include_directories(include)
add_subdirectory(src)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
```

`src/CMakeLists.txt`：

```cmake
aux_source_directory(. SRC_LIST)
add_executable(myapp ${SRC_LIST})
```

### 第 5 步：生成库文件

```cmake
# 静态库（.a / .lib）
add_library(mylib STATIC src/mylib.cpp)

# 动态库（.so / .dll）
add_library(mylib_shared SHARED src/mylib.cpp)

# 设置库输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
```

| 库类型 | Linux | Windows | 说明 |
|--------|--------|----------|------|
| STATIC | `.a` | `.lib` | 编译时链接，体积大但独立 |
| SHARED | `.so` | `.dll` | 运行时链接，体积小但需部署 |

### 第 6 步：链接库文件

```cmake
add_executable(myapp src/main.cpp)
target_link_libraries(myapp mylib)       # 链接静态库
# 或
target_link_libraries(myapp mylib_shared) # 链接动态库
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
```

### 第 7 步：查找并链接系统库

```cmake
# 查找系统中的 jsoncpp 库
find_library(JSON_LIB jsoncpp)

add_executable(myapp src/main.cpp)
target_link_libraries(myapp ${JSON_LIB} pthread)
```

### 第 8 步：添加编译选项与条件编译

```cmake
add_compile_options(-Wall -Wextra -std=c++17)

option(ENABLE_DEBUG "Enable debug mode" OFF)
if(ENABLE_DEBUG)
    add_compile_options(-g -DDEBUG)
else()
    add_compile_options(-O2)
endif()
```

构建时切换：

```bash
cmake .. -DENABLE_DEBUG=ON   # 开启调试
cmake .. -DENABLE_DEBUG=OFF  # 发布优化
```

### 第 9 步：现代 CMake 写法（推荐）

为目标单独设置属性，避免全局污染：

```cmake
add_executable(myapp src/main.cpp)

# 仅对 myapp 添加头文件路径
target_include_directories(myapp PUBLIC include)

# 仅对 myapp 设置 C++ 标准
set_target_properties(myapp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
```

---

## 5. 常用命令速查

### 基础指令

| 指令 | 语法 | 说明 |
|------|------|------|
| `cmake_minimum_required` | `cmake_minimum_required(VERSION 3.10)` | 指定 CMake 最低版本 |
| `project` | `project(MyProject VERSION 1.0 LANGUAGES C CXX)` | 定义项目名、版本、语言 |
| `set` | `set(VAR value)` | 定义变量 |
| `message` | `message(STATUS "info")` | 输出信息（STATUS / WARNING / FATAL_ERROR） |
| `option` | `option(OPT "描述" ON/OFF)` | 定义可选项 |

### 目录与文件管理

| 指令 | 语法 | 说明 |
|------|------|------|
| `include_directories` | `include_directories(dir1 dir2)` | 添加头文件搜索路径（全局） |
| `add_subdirectory` | `add_subdirectory(src)` | 添加子目录构建 |
| `aux_source_directory` | `aux_source_directory(. VAR)` | 收集目录下所有源文件 |

### 目标管理

| 指令 | 语法 | 说明 |
|------|------|------|
| `add_executable` | `add_executable(app main.cpp)` | 生成可执行文件 |
| `add_library` | `add_library(lib STATIC src.cpp)` | 生成库文件 |
| `target_link_libraries` | `target_link_libraries(app lib)` | 链接库到目标 |
| `target_include_directories` | `target_include_directories(app PUBLIC include)` | 为目标设置头文件路径 |
| `set_target_properties` | `set_target_properties(app PROPERTIES ...)` | 设置目标属性 |

### 依赖查找

| 指令 | 语法 | 说明 |
|------|------|------|
| `find_package` | `find_package(OpenCV REQUIRED)` | 查找并加载外部包 |
| `find_library` | `find_library(VAR name HINTS path)` | 查找库文件 |
| `find_path` | `find_path(VAR header.h)` | 查找头文件路径 |

### 条件编译

```cmake
option(USE_FEATURE "Enable feature" ON)

if(USE_FEATURE)
    target_compile_definitions(myapp PRIVATE USE_FEATURE)
endif()

# 控制 if/else
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release mode")
endif()
```

---

## 6. 变量系统

### 预定义变量

| 变量名 | 含义 |
|--------|------|
| `PROJECT_SOURCE_DIR` | 项目根源码目录 |
| `PROJECT_BINARY_DIR` | 项目构建目录 |
| `CMAKE_CURRENT_SOURCE_DIR` | 当前 CMakeLists.txt 所在目录 |
| `CMAKE_SOURCE_DIR` | 顶层 CMakeLists.txt 所在目录 |
| `CMAKE_BINARY_DIR` | 顶层构建目录 |
| `EXECUTABLE_OUTPUT_PATH` | 可执行文件输出路径 |
| `LIBRARY_OUTPUT_PATH` | 库文件输出路径 |
| `CMAKE_C_COMPILER` | C 编译器路径 |
| `CMAKE_CXX_COMPILER` | C++ 编译器路径 |
| `CMAKE_BUILD_TYPE` | 构建类型（Debug / Release / RelWithDebInfo / MinSizeRel） |
| `CMAKE_C_FLAGS` | C 编译选项 |
| `CMAKE_CXX_FLAGS` | C++ 编译选项 |
| `CMAKE_INSTALL_PREFIX` | 安装路径前缀（默认 `/usr/local`） |
| `BUILD_SHARED_LIBS` | 全局控制生成共享库还是静态库 |

### 自定义变量

```cmake
set(MY_NAME "Calculator")
set(SRC_LIST main.cpp add.cpp subtract.cpp)
message(STATUS "Project: ${MY_NAME}")
message(STATUS "Sources: ${SRC_LIST}")
```

- 引用变量：`${变量名}`
- 访问环境变量：`$ENV{变量名}`

### 变量作用域

- **顶层 CMakeLists.txt** 的变量会向子目录传递（子目录可见）
- 子目录中 `set` 的新变量不会向上回传
- 使用 `PARENT_SCOPE` 可将子目录变量传给父目录：

```cmake
set(MY_VAR "value" PARENT_SCOPE)
```

---

## 7. 现代 CMake 最佳实践

### 核心原则

| 原则 | 说明 |
|------|------|
| 用 `target_*` 代替全局命令 | 精确控制依赖传播，避免全局污染 |
| 用 `PRIVATE / PUBLIC / INTERFACE` | 控制属性传播范围 |
| 不要用 `include_directories`（全局） | 用 `target_include_directories` |
| 不要用 `add_definitions`（全局） | 用 `target_compile_definitions` |
| 不要用 `add_compile_options`（全局） | 用 `target_compile_options` |
| 用 `cmake_minimum_required(VERSION 3.10+)` | 玳代特性需 3.10 以上 |

### PRIVATE / PUBLIC / INTERFACE 区别

| 修饰符 | 对自身 | 对依赖者 | 对被依赖者 |
|--------|--------|----------|-----------|
| `PRIVATE` | ✅ 生效 | ❌ 不传播 | ❌ 不传播 |
| `PUBLIC` | ✅ 生效 | ✅ 传播 | ✅ 传播 |
| `INTERFACE` | ❌ 自身不生效 | ✅ 仅传播 | ✅ 仅传播 |

示例：

```cmake
# 头文件路径：自己用，也传给链接 mylib 的目标
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 编译定义：仅自己用
target_compile_definitions(mylib PRIVATE MYLIB_INTERNAL)

# C++ 标准：自己用，链接 mylib 的目标也需要
set_target_properties(mylib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    INTERFACE_CXX_STANDARD 17  # 传播给依赖者
)
```

### Generator Expressions（生成器表达式）

根据不同构建配置产生不同值：

```cmake
target_compile_definitions(myapp PRIVATE
    $<$<CONFIG:Debug>:DEBUG_MODE>     # 仅 Debug 时定义 DEBUG_MODE
    $<$<CONFIG:Release>:NDEBUG>       # 仅 Release 时定义 NDEBUG
)

target_link_libraries(myapp PRIVATE
    $<$<PLATFORM_ID:Linux>:pthread>   # 仅 Linux 时链接 pthread
)
```

---

## 8. 安装与打包

### 安装规则

```cmake
# 安装可执行文件
install(TARGETS myapp DESTINATION bin)

# 安装库文件
install(TARGETS mylib
        LIBRARY DESTINATION lib      # 动态库
        ARCHIVE DESTINATION lib)     # 静态库

# 安装头文件
install(FILES include/mylib.h DESTINATION include)
```

执行安装：

```bash
cmake --install .                    # 安装到默认路径（/usr/local）
cmake --install . --prefix=/opt/my   # 安装到指定路径
```

### CMake CPack 打包

```cmake
include(CPack)

set(CPACK_PACKAGE_NAME "MyApp")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "A simple application")
set(CPACK_GENERATOR "TGZ")          # 打包格式：TGZ / DEB / RPM / NSIS
```

打包命令：

```bash
cpack
```

---

## 9. 调试技巧

### message 输出

```cmake
message(STATUS "Source dir: ${PROJECT_SOURCE_DIR}")
message(WARNING "Variable MY_VAR is empty")
message(FATAL_ERROR "Required package not found!")  # 终止构建
```

### 开启详细输出

```cmake
set(CMAKE_VERBOSE_MAKEFILE ON)
```

或在命令行：

```bash
cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON
make VERBOSE=1
```

### 常见问题排查

| 问题 | 解决方法 |
|------|----------|
| 修改 CMakeLists.txt 后没生效 | 删除 `build/` 目录中的 `CMakeCache.txt` 重新配置 |
| `find_package` 找不到库 | 检查 `CMAKE_PREFIX_PATH`，或设置 `-Dxxx_DIR=/path` |
| 链接错误 undefined reference | 检查 `target_link_libraries` 是否遗漏库 |
| 头文件找不到 | 用 `target_include_directories` 正确指定路径 |

---

## 10. 综合实战案例：计算器项目

### 项目结构

```
Calculator/
├── CMakeLists.txt
├── include/
│   ├── add.h
│   ├── subtract.h
│   ├── multiply.h
│   └── divide.h
├── src/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── add.cpp
│   ├── subtract.cpp
│   ├── multiply.cpp
│   └── divide.cpp
└── build/
```

### 根目录 CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(Calculator VERSION 1.0 LANGUAGES CXX)

# 编译选项
add_compile_options(-Wall -Wextra)

# 输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 条件编译：是否启用乘除功能
option(ADVANCED_FEATURES "Enable multiply and divide" ON)

# 进入 src 子目录
add_subdirectory(src)
```

### src/CMakeLists.txt

```cmake
# 基础功能库（加减）
add_library(calc_basic STATIC add.cpp subtract.cpp)
target_include_directories(calc_basic PUBLIC ${PROJECT_SOURCE_DIR}/include)

# 高级功能库（乘除）- 条件编译
if(ADVANCED_FEATURES)
    add_library(calc_advanced STATIC multiply.cpp divide.cpp)
    target_include_directories(calc_advanced PUBLIC ${PROJECT_SOURCE_DIR}/include)
    target_compile_definitions(calc_advanced PUBLIC ADVANCED_FEATURES)
endif()

# 可执行文件
add_executable(calculator main.cpp)
target_include_directories(calculator PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(calculator PRIVATE calc_basic)

if(ADVANCED_FEATURES)
    target_link_libraries(calculator PRIVATE calc_advanced)
endif()

# 设置 C++ 标准
set_target_properties(calculator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# 安装规则
install(TARGETS calculator DESTINATION bin)
install(TARGETS calc_basic calc_advanced
        ARCHIVE DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION include)
```

### 构建与运行

```bash
# 配置（启用高级功能）
mkdir build && cd build
cmake .. -DADVANCED_FEATURES=ON

# 编译
make

# 运行
./bin/calculator

# 安装
cmake --install . --prefix=/opt/calculator
```

---

## 附录：CMake 命令行常用选项

| 选项 | 说明 |
|------|------|
| `-S <path>` | 指定源码目录 |
| `-B <path>` | 指定构建目录 |
| `-D <var>=<value>` | 设置变量（如 `-DCMAKE_BUILD_TYPE=Release`） |
| `-G <generator>` | 指定生成器（如 `-G "Unix Makefiles"` / `-G "Visual Studio 17 2022"`） |
| `--build <dir>` | 构建项目（通用命令，无需关心底层工具） |
| `--install <dir>` | 安装项目 |
| `--clean-first` | 构建前先清理 |

示例：

```bash
# 一步到位
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build --prefix=/opt/myapp
```

---

> 📌 **学习建议**：从第 0 步开始，每完成一步就 `mkdir build && cd build && cmake .. && make` 验证结果，逐步递进。遇到问题优先检查 `CMakeCache.txt`，必要时删除重新配置。
