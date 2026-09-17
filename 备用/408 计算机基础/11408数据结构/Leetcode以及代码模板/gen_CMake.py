from pathlib import Path

IGNORED_DIRS = {"build", "cmake-build-debug", ".idea"}
CMAKE_VERSION = "3.16"
PROJECT_NAME = "DS_408"


def valid_subdirs(root: Path):
    """返回可用于 add_subdirectory 的子目录"""
    return [
        p for p in root.iterdir()
        if p.is_dir() and p.name not in IGNORED_DIRS
    ]


def generate_level2_cmake(root: Path):
    """
    二级目录：
    - 只有子目录 -> add_subdirectory
    - 只有 cpp     -> add_executable
    忽略 CMakeLists.txt
    """
    dirs = valid_subdirs(root)

    files = [
        p for p in root.iterdir()
        if p.is_file() and p.name != "CMakeLists.txt"
    ]

    cpps = [p for p in files if p.suffix == ".cpp"]
    others = [p for p in files if p.suffix != ".cpp"]

    cmake = root / "CMakeLists.txt"

    with cmake.open("w", encoding="utf-8") as f:
        # 情况 1：只有子目录
        if dirs and not cpps and not others:
            for d in dirs:
                f.write(f'message(STATUS "***  Exiting 2-level folder {d.name}")\n')
                f.write(f'add_subdirectory({d.name})\n')

        # 情况 2：只有 cpp
        elif cpps and not dirs and not others:
            f.write('message(STATUS "====================================================")\n')
            for cpp in cpps:
                name = cpp.stem
                f.write(f'message(STATUS "&&&    found executable programme: {name}")\n')
                f.write(f'add_executable({name} {cpp.name})\n')

        else:
            raise RuntimeError(
                f"目录结构非法：dirs={len(dirs)}, cpp={len(cpps)}, others={len(others)}"
            )

    print(f"✔ 已生成（二级）: {cmake}")


def generate_chapter_cmake(root: Path):
    """
    Chapter 级目录：
    - 若干 cpp (ADT实现)
    - 一个 Problems 文件夹
    需要递归为 Problems 生成二级 CMakeLists
    """
    dirs = valid_subdirs(root)
    cpps = [
        p for p in root.iterdir()
        if p.is_file() and p.suffix == ".cpp"
    ]

    problems_dir = None
    for d in dirs:
        if d.name == "Problems":
            problems_dir = d
            break

    if problems_dir is None:
        raise RuntimeError("Chapter 目录必须包含 Problems 文件夹")

    cmake = root / "CMakeLists.txt"

    with cmake.open("w", encoding="utf-8") as f:
        f.write('message(STATUS "====================================================")\n')

        # 生成 ADT cpp 可执行程序
        for cpp in cpps:
            name = cpp.stem
            f.write(f'message(STATUS "&&&    found executable programme: {name}")\n')
            f.write(f'add_executable({name} {cpp.name})\n')

        # 添加 Problems 子目录
        f.write(f'message(STATUS "***  Exiting Chapter folder {problems_dir.name}")\n')
        f.write(f'add_subdirectory({problems_dir.name})\n')

    print(f"✔ 已生成（Chapter级）: {cmake}")

    # 递归生成 Problems 二级 CMake
    # generate_level2_cmake(problems_dir)


def generate_project_cmake(root: Path):
    """
    项目 / 根目录 CMakeLists.txt
    """
    dirs = valid_subdirs(root)
    cmake = root / "CMakeLists.txt"

    with cmake.open("w", encoding="utf-8") as f:
        f.write(f"cmake_minimum_required(VERSION {CMAKE_VERSION})\n")
        f.write(f"project({PROJECT_NAME})\n\n")
        for d in dirs:
            f.write(f'message(STATUS "***  Exiting ROOT-level folder {d.name}")\n')
            f.write(f'add_subdirectory({d.name})\n')

    print(f"✔ 已生成（项目级）: {cmake}")


def show_menu(root: Path):
    print(f"\n当前目录: {root}\n")

    dirs = valid_subdirs(root)
    cpps = [p for p in root.iterdir() if p.is_file() and p.suffix == ".cpp"]

    if dirs:
        for i, d in enumerate(dirs, 1):
            print(f"({i}) {d.name}")
    else:
        for cpp in cpps:
            print(f"    {cpp.name}")

    print("\n[a] 上一级目录")
    print("[b] 生成当前目录（二级）CMakeLists.txt(新建章节)")
    print("[c] 生成项目级 CMakeLists.txt")
    print("[d] 生成 Chapter 级 CMakeLists.txt(ADT+Problems)")


def main():
    root = Path.cwd()

    while True:
        show_menu(root)
        choice = input("\n请输入选项: ").strip()

        if choice == "a":
            if root.parent != root:
                root = root.parent
            else:
                print("⚠ 已经是根目录")

        elif choice == "b":
            try:
                generate_level2_cmake(root)
            except Exception as e:
                print(f"✘ 失败: {e}")

        elif choice == "c":
            try:
                generate_project_cmake(root)
            except Exception as e:
                print(f"✘ 失败: {e}")

        elif choice == "d":
            try:
                generate_chapter_cmake(root)
            except Exception as e:
                print(f"✘ 失败: {e}")

        elif choice.isdigit():
            dirs = valid_subdirs(root)
            idx = int(choice) - 1
            if 0 <= idx < len(dirs):
                root = dirs[idx]
            else:
                print("✘ 无效编号")

        else:
            print("✘ 无效输入")


if __name__ == "__main__":
    main()