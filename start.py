import os

# 此处定义编译相关的参数, 根据需要调整即可
generate = "Visual Studio 16 2019"
platform = "x64"
build_type = "Debug"
cxx_standard = 17

config_param = f'-DBUILD_TESTING=OFF -G "{generate}" -DCMAKE_BUILD_TYPE={build_type} -DCMAKE_CXX_STANDARD={cxx_standard}'
if platform:
    config_param = f"{config_param} -A {platform}"

root_path = os.getcwd()
build_root_path = f"{root_path}/nly_build"
install_root_path = f"{root_path}/nly_install"


def get_target_build_path(package_name: str):
    return f"{build_root_path}/{package_name}_build_path"


def get_target_install_path(package_name: str):
    return f"{install_root_path}/{package_name}_install_path"


def print_with_notify(content: str):
    print(f"----------: {content}")


def deal_command(command: str) -> bool:
    return os.system(command) == 0


def build_third_package(
    package_name: str,
    build_shared_library=True,
    extra_config_param: str = config_param,
    extra_build_param: str = "",
    extra_install_param: str = "",
) -> bool:
    target_build_path = get_target_build_path(package_name)
    target_install_path = get_target_install_path(package_name)
    target_filename = f"{target_install_path}/script_command.txt"

    print_with_notify(f"start deal {package_name}")
    print_with_notify(f"target filename is {target_filename}")

    if os.path.exists(target_filename):
        print_with_notify(
            f"{target_filename} already exists, The processing of {package_name} will be skipped."
        )
        return True

    build_shared_library_param = (
        f'-DBUILD_SHARED_LIBS={"ON" if build_shared_library else "OFF"}'
    )

    config_command = f'cmake -S "{root_path}/upstream/{package_name}" -B "{target_build_path}" {build_shared_library_param} {extra_config_param}'
    build_command = f'cmake --build "{target_build_path}" --config {build_type} -j {extra_build_param}'
    install_command = f'cmake --install "{target_build_path}" --prefix "{target_install_path}" --config {build_type} {extra_install_param}'
    print_with_notify(f"config_command: {config_command}")
    print_with_notify(f"build_command: {build_command}")
    print_with_notify(f"install_command: {install_command}")

    for stage_name, command in [
        ("config", config_command),
        ("build", build_command),
        ("install", install_command),
    ]:
        print_with_notify(f"start {stage_name} {package_name}")

        if not deal_command(command):
            print_with_notify(f"falied to {stage_name} {package_name}")
            return False

    with open(target_filename, "w") as f:
        f.write(f"{config_command}\n")
        f.write(f"{build_command}\n")
        f.write(f"{install_command}\n")

    return True


# for abseil-cpp
absl_name = "abseil-cpp"
if not build_third_package(absl_name):
    exit(-1)

# for protobuf
protobuf_config_param = f"{config_param} \
-DCMAKE_PREFIX_PATH={get_target_install_path(absl_name)} \
-Dprotobuf_LOCAL_DEPENDENCIES_ONLY=ON \
-Dprotobuf_BUILD_TESTS=OFF \
-Dprotobuf_WITH_ZLIB=OFF \
-Dutf8_range_ENABLE_TESTS=OFF"
if not build_third_package(
    "protobuf",
    True,
    protobuf_config_param,
):
    exit(-1)

# for boost
if not build_third_package("boost"):
    exit(-1)

# for googletest
if not build_third_package("googletest"):
    exit(-1)

print_with_notify("finish")
