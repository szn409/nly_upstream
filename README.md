# README

## 第三方库列表

| 库                                                           | 说明                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [abseil-cpp](https://github.com/abseil/abseil-cpp/releases/tag/20250127.0) | /                                                            |
| [protobuf](https://github.com/protocolbuffers/protobuf/releases/tag/v30.0-rc1) | 此库依赖 abseil-cpp                                          |
| [boost](https://github.com/boostorg/boost/releases/tag/boost-1.87.0) | 当前用的 [boost-1.87.0-cmake.zip](https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.zip) |



## 使用方式

* 打开 start.py，按需配置编译参数
  * 每个库的 install 目录下均会生成一个 script_command.txt
  * 该文件记录了此库的 config、build、install 相关的参数
  * 每个库生成的工作条件：相应的 install 目录下不存在 script_command.txt 即会触发 config、build、install
* 配置好 start.py 后，运行此脚本即可



## 使用示例

* CMakeLists.txt

  ```cmake
  cmake_minimum_required(VERSION 3.0.0)
  project(szn)
  
  # 指定 C++17, 因为 nly_upstream 编译的时候指定了 C++17
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
  
  # 指定 nly_upstream 的安装路径, 用于 find_package
  set(nly_upstream_install_root "D:/nly_upstream/nly_install")
  list(APPEND CMAKE_PREFIX_PATH "${nly_upstream_install_root}/abseil-cpp_install_path")
  list(APPEND CMAKE_PREFIX_PATH "${nly_upstream_install_root}/protobuf_install_path")
  list(APPEND CMAKE_PREFIX_PATH "${nly_upstream_install_root}/boost_install_path")
  
  find_package(absl REQUIRED)
  find_package(protobuf REQUIRED)
  find_package(boost_filesystem REQUIRED) # 此处以 filesystem 为示例
  
  add_executable(szn 
    ${CMAKE_SOURCE_DIR}/main.cpp 
  
    # 由 nly_upstream 生成的 protoc.exe 生成的文件
    ${CMAKE_SOURCE_DIR}/templateFile.pb.cc
    )
  
  target_link_libraries(szn PRIVATE
    # 测试 abseil-cpp 的可用性
    absl::strings absl::base
  
    # 测试 protobuf 的可用性
    protobuf::libprotobuf protobuf::libprotobuf-lite protobuf::libprotoc
    
    # 得以这种方式添加
    Boost::filesystem 
    )
  
  target_include_directories(szn PRIVATE ${CMAKE_SOURCE_DIR})
  ```

* main.cpp

  ```c++
  #include "absl/strings/str_cat.h"
  #include "boost/filesystem.hpp"
  #include "templateFile.pb.h"
  
  int main()
  {
      std::string hello = "Hello";
      std::string world = "World";
      std::string message = absl::StrCat(hello, ", ", world, "!");
      // message = "Hello, World!"
  
      CornerTemplate cornerTemplate;
      cornerTemplate.set_imgwidth(1024);
      std::string out;
      if (!cornerTemplate.SerializeToString(&out))
      {
          return {};
      }
      auto size = out.size();
      // size = 3
  
      auto tmp = boost::filesystem::current_path();
      // tmp = {m_pathname=L"D:\\cmake_test\\out\\build\\x64-Debug\\Debug" }
  
      return 0;
  }
  ```

