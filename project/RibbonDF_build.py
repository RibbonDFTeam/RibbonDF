import argparse
import glob
import os
import shutil
import kconfiglib
from menuconfig import menuconfig


# @brief 解析命令行参数
# @return 命令行参数对象
def parse_args():
    parser = argparse.ArgumentParser(description="RibbonDF_build.py 参数解析")
    parser.add_argument("-d", "--distclean", action="store", help="distclean")
    parser.add_argument(
        "-s", "--search-module", action="store", help="检查当前路径下的模块列表"
    )
    parser.add_argument(
        "-m", "--kconfig-menuconfig", action="store", help="检查当前路径下的模块列表"
    )
    parser.add_argument(
        "-r",
        "--kconfig-reg",
        type=str,
        nargs="+",
        help="输出项目路径，和注册模块路径",
    )
    return parser.parse_args()


# @brief 检查是否为模块
# @param module_path 模块路径
# @return True/False
def check_module(module_path):
    if not os.path.isdir(module_path):
        return False
    return "CMakeLists.txt" in os.listdir(module_path)


def search_module(path, module_list):
    for dir_name in os.listdir(path):
        dir_path = os.path.join(path, dir_name)
        if check_module(dir_path):
            module_list.append(dir_path)


def kconfig_reg(project_path):
    init_project(project_path)
    kconfig_load()


def write_cmake_setting(kconf):
    # 遍历所有选项和配置
    with open(
        os.path.join(os.environ["RibbonDF_PROJECT_DIR"], "config/RibbonDFConfig.cmake"),
        "w",
    ) as cmake_file:
        cmake_file.write(
            "#generated automatically by RibbonDF_build.py, do not modify it manually\n"
        )
        for sym in kconf.unique_defined_syms:
            if sym.type == kconfiglib.BOOL:
                cmake_value = "on" if sym.str_value == "y" else "off"
            elif sym.type == kconfiglib.STRING:
                cmake_value = '"' + sym.str_value + '"'
            elif sym.type == kconfiglib.INT:
                cmake_value = sym.str_value
            # 生成CMake设置
            cmake_setting = "set(CONFIG_{0} {1})".format(sym.name, cmake_value)
            cmake_file.write(cmake_setting + "\n")


def kconfig_load():
    kconf = kconfiglib.Kconfig(
        os.path.join(os.environ["RibbonDF_PROJECT_DIR"], "../../Kconfig")
    )

    kconf.load_config()
    kconf.write_config()
    kconf.write_autoconf()
    write_cmake_setting(kconf)


def init_project(project_path):
    os.environ["RibbonDF_PROJECT_DIR"] = project_path
    os.environ["KCONFIG_CONFIG"] = os.path.join(project_path, "config/.config")
    os.environ["KCONFIG_AUTOHEADER"] = os.path.join(
        project_path, "config/RibbonDF_config.h"
    )

def kconfig_menuconfig(project_path):
    init_project(project_path)
    kconfig_file = os.path.join(project_path, "../../Kconfig")
    kconf = kconfiglib.Kconfig(kconfig_file)
    kconf.load_config()
    menuconfig(kconf)
    kconf.write_config()
    kconf.write_autoconf()


def distclean(project_path):
    shutil.rmtree(os.path.join(project_path, "build"))
    shutil.rmtree(os.path.join(project_path, "config"))
    os.mkdir(os.path.join(project_path, "build"))
    os.mkdir(os.path.join(project_path, "config"))


if __name__ == "__main__":
    args = parse_args()
    if args.distclean:
        distclean(args.distclean)
    elif args.search_module:
        module_list = []
        search_module(args.search_module, module_list)
        result = " ".join(module_list)
        print(result)
    elif args.kconfig_reg:
        project_path = args.kconfig_reg[0]
        kconfig_reg(project_path)
    elif args.kconfig_menuconfig:
        kconfig_menuconfig(args.kconfig_menuconfig)
    else:
        print("未知命令")

    exit(0)
