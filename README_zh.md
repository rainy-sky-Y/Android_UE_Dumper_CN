# Android Unreal Engine Dumper / UE Dumper CN
[中文](README_zh.md) | [English](README.md)


向 [MJx0](https://github.com/MJx0) 致敬！！！
感谢 我的朋友 [ZRO](https://github.com/bikhx) 的帮助!!
为 Android 平台的 Unreal Engine 游戏生成 SDK 和函数脚本。

此 Dumper 基于 [AndUEDumper](https://github.com/MJx0/AndUEDumper)

项目。

## 功能特性

* 支持的 ABI：ARM64、ARM、x86 和 x86_64

* 可编译为外部可执行文件，也可编译为内部库

* 转储 UE 偏移量、类、结构体、枚举和函数

* 生成函数名 JSON 脚本，可用于 IDA 和 Ghidra 等工具

* 符号和模式扫描，自动查找 GUObjectArray、GNames、Physx、Matrix、FrameCount 和 NamePoolData 地址

* 在 '.bss' 文件中查找 GEngine 和 GWorld

* 从内存中转储 UE 库

## 当前支持的游戏

* 三角洲行动（国服）

* 无畏契约（国服）

* 暗区突围（国服）

* 远光 84（国服）

* 枪战特训2
  
* 洛克王国世界
  
* 和平精英

## 库使用方法

只需使用任意方法加载或注入库，即可运行。

运行带有标签过滤器“UEDump3r”的 logcat 命令以查看转储日志。

为避免外部存储权限，转储输出将位于游戏的外部数据文件夹（/sdcard/Android/data/<游戏>/files）。

## 可执行文件用法

您需要将转储程序推送到可执行目录，例如 /data/local/tmp，并赋予其执行权限。建议使用 adb，您可以查看 [push](AndUEDumper/push.bat) 脚本了解详情。

请使用兼容的转储程序。如果游戏是 64 位，请使用 arm64 或 x86_64 版本；如果是 32 位，请使用 arm 或 x86 版本。

```bash

用法：./UEDump3r_arm64 [-h] [-o] [选项]

必需参数：

-o, --output 指定输出目录路径.

可选参数：

-h, --help 显示可用参数

-p, --package 预先指定游戏包 ID.

-d, --dumplib 从内存中转储 UE 库. 
```

## 输出文件

### AIOHeader.hpp

* 一体化转储文件头

### Offsets.hpp

* 包含 UE 偏移量的头文件

### Logs.txt

* 包含转储过程日志的日志文件

### Objects.txt

* ObjObjects 转储

### script.json

* 如果您熟悉 Il2cppDumper 的 script.json 文件，它与之类似。它包含一个函数名称和地址的 JSON 数组

## 向 Dumper 添加新游戏

请参考 [GameProfiles](AndUEDumper/src/UE/UEGameProfiles) 中的原型

您还可以使用提供的模式来查找 GUObjectArray、GNames 或 NamePoolData。

## 构建

您的操作系统需要安装 'make' 工具，并且需要设置 NDK_HOME 环境变量。

```bash

git clone --recursive https://github.com/MJx0/AndUEDumper

cd AndUEDumper/AndUEDumper

make clean && make

```

## 致谢

* [UE4Dumper-4.25](https://github.com/guttir14/UnrealDumper-4.25)

* [Il2cppDumper](https://github.com/Perfare/Il2CppDumper)

* [Dumper-7](https://github.com/Encryqed/Dumper-7)

* [UEDumper](https://github.com/Spuckwaffel/UEDumper)

* [ZRO]()
