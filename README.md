# README

## 第三方库列表

| 库                                                           | 说明                                                         | target                                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| [googletest](https://github.com/google/googletest/releases/tag/v1.16.0) | /                                                            | GTest::gtest_main                                            |
| [abseil-cpp](https://github.com/abseil/abseil-cpp/releases/tag/20250127.0) | /                                                            | absl::strings<br>absl::base<br>...                           |
| [protobuf](https://github.com/protocolbuffers/protobuf/releases/tag/v30.0-rc1) | 此库依赖 abseil-cpp                                          | protobuf::libprotobuf<br/>protobuf::libprotobuf-lite<br/>protobuf::libprotoc<br/>... |
| [boost](https://github.com/boostorg/boost/releases/tag/boost-1.87.0) | 当前用的 [boost-1.87.0-cmake.zip](https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.zip) | Boost::filesystem<br/>...                                    |
| [fmt](https://github.com/fmtlib/fmt/releases/tag/11.1.3)     | /                                                            | fmt::fmt                                                     |
| [json](https://github.com/nlohmann/json/releases/tag/v3.11.3) | /                                                            | nlohmann_json::nlohmann_json                                 |
| [hiredis](https://github.com/redis/hiredis/releases/tag/v1.2.0) | /                                                            | hiredis::hiredis                                             |
| [redis-plus-plus](https://github.com/sewenew/redis-plus-plus/releases/tag/1.3.13) | 此库依赖 hiredis                                             | redis++::redis++                                             |
| [cpp-httplib](https://github.com/yhirose/cpp-httplib/releases/tag/v0.19.0) | /                                                            | httplib::httplib                                             |
| [thread-pool](https://github.com/bshoshany/thread-pool/releases/tag/v5.0.0) | 此库无 CMakeLists.txt<br>拷贝 include/BS_thread_pool.hpp 使用即可 | /                                                            |



## 使用方式

* 打开 start.py，按需配置编译参数
  * 每个库的 install 目录下均会生成一个 script_command.txt
  * 该文件记录了此库的 config、build、install 相关的参数
  * 每个库生成的工作条件：相应的 install 目录下不存在 script_command.txt 即会触发 config、build、install
* 配置好 start.py 后，运行此脚本即可



## CMake

* 参考：[nly](https://github.com/szn409/nly.git)

* 注意点

  * 使用者的 CXX 的版本，要和此库保持一致（此库默认使用 CXX17）

  * find_package 示例

    ```cmake
    # 指定 nly_upstream 的安装路径, 用于 find_package
    set(NLY_UPSTREAM_INSTALL "D:/nly_upstream/nly_install")
    list(APPEND CMAKE_PREFIX_PATH "${NLY_UPSTREAM_INSTALL}/abseil-cpp_install_path")
    list(APPEND CMAKE_PREFIX_PATH "${NLY_UPSTREAM_INSTALL}/protobuf_install_path")
    list(APPEND CMAKE_PREFIX_PATH "${NLY_UPSTREAM_INSTALL}/boost_install_path")
    list(APPEND CMAKE_PREFIX_PATH "${NLY_UPSTREAM_INSTALL}/fmt_install_path")
    list(APPEND CMAKE_PREFIX_PATH "${NLY_UPSTREAM_INSTALL}/json_install_path")
    list(APPEND CMAKE_PREFIX_PATH "${NLY_UPSTREAM_INSTALL}/hiredis_install_path")
    list(APPEND CMAKE_PREFIX_PATH "${NLY_UPSTREAM_INSTALL}/redis-plus-plus_install_path")
    list(APPEND CMAKE_PREFIX_PATH "${NLY_UPSTREAM_INSTALL}/cpp-httplib_install_path")
    
    find_package(absl REQUIRED)
    find_package(protobuf REQUIRED)
    find_package(Boost REQUIRED COMPONENTS  date_time serialization)
    find_package(fmt REQUIRED)
    find_package(nlohmann_json REQUIRED)
    find_package(hiredis REQUIRED)
    find_package(redis++ REQUIRED)
    find_package(httplib REQUIRED)
    
    # 按需链接即可
    target_link_libraries(your_target PUBLIC
      absl::strings absl::base
      protobuf::libprotobuf protobuf::libprotobuf-lite protobuf::libprotoc
      Boost::date_time Boost::serialization
      fmt::fmt
      nlohmann_json::nlohmann_json
      hiredis::hiredis  
      redis++::redis++  
      httplib::httplib
      )
    ```
    

