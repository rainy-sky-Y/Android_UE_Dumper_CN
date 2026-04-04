# Android Unreal Engine Dumper / UE Dumper CN
[中文](README_zh.md) | [English](README.md)

Show respect for [MJx0](https://github.com/MJx0) !!!

Thanks for my friend [ZRO](https://github.com/bikhx) 's help!!

Generate sdk and functions script for unreal engine games on android.

The dumper is based on [AndUEDumper](https://github.com/MJx0/AndUEDumper)
project.

## Features

* Supported ABI ARM64, ARM, x86 and x86_64
* Can be compiled as executable for external and as library for internal use
* Dump UE offsets, classes, structs, enums and functions
* Generate function names json script to use with IDA & Ghidra etc
* Symbol and pattern scanning to find GUObjectArray, GNames , Physx ,Matrix, FrameCount and NamePoolData addresses automatically
* Find GEngine and GWorld in '.bss'
* Dump UE library from memory

## Currently Supported Games

* Delta Force(CN)
* Valorant(CN)
* Arena Breakout(CN)
* Farlight 84(CN)
* 枪战特训2
* 洛克王国世界
* 和平精英

## Library Usage

Simply load or inject the library with whichever method and let it do it's thing.
Run logcat with tag filter "UEDump3r" for dump logs.
The dump output will be at the game's external data folder (/sdcard/Android/data/< game >/files) to avoid external storage permission.

## Executable Usage

You will have to push the dumper in an executable directory like /data/local/tmp then give it execute permission. Its recommended to have adb, you can check [push](AndUEDumper/push.bat) script for this.
Use the compatible dumper, if game is 64bit use arm64 or x86_64, if 32bit then use arm or x86 version.

```bash
Usage: ./UEDump3r_arm64 [-h] [-o] [ options ]

Required arguments:
   -o, --output        specify output directory path.

Optional arguments:
   -h, --help          show available arguments
   -p, --package       specify game package ID in advance.
   -d, --dumplib       dump UE library from memory.
```

## Output Files

### AIOHeader.hpp

* An all-in-one dump file header

### Offsets.hpp

* Header containing UE Offsets

### Logs.txt

* Log file containing dump process logs

### Objects.txt

* ObjObjects dump

### script.json

* If you are familiar with Il2cppDumper script.json, this is similar. It contains a json array of function names and addresses

## Adding a new game to the Dumper

Follow the prototype in [GameProfiles](AndUEDumper/src/UE/UEGameProfiles)

You can also use the provided patterns to find GUObjectArray, GNames or NamePoolData.

## Building

You need to have 'make' installed on your OS and NDK_HOME env variable should be set.

```bash
git clone --recursive https://github.com/MJx0/AndUEDumper
cd AndUEDumper/AndUEDumper
make clean && make
```

## Credits & Thanks

* [UE4Dumper-4.25](https://github.com/guttir14/UnrealDumper-4.25)
* [Il2cppDumper](https://github.com/Perfare/Il2CppDumper)
* [Dumper-7](https://github.com/Encryqed/Dumper-7)
* [UEDumper](https://github.com/Spuckwaffel/UEDumper)
* [MJx0](https://github.com/MJx0)
* [ZRO]
