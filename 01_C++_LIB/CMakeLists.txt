cmake_minimum_required(VERSION 3.14)
project(01_C++_LIB)

# 下载 spdlog 的另一种方式：URL 下载
include(FetchContent)

# 使用 URL 直接下载 zip 包，比 Git 克隆更快更稳定
FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.12.0.tar.gz
    # 启用下载提取时间戳（解决警告）
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(spdlog)

add_executable(01_C++_LIB main.cpp)
target_link_libraries(01_C++_LIB PRIVATE spdlog::spdlog)