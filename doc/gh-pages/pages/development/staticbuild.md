---
title: Static Build Guide
parent: Develop
nav_order: 4
---
# Static Build Guide

This tutorial will show you how to build a static version of MNE-CPP. In order to build statically we need to perform two steps:

 * Build a static version of Qt
 * Compile MNE-CPP with the `static` flag

This tutorial assumes the following folder structure:
```
Git/
├── qt5/
├── qt5_shadow/
├── qt5_binaries/
├── mne-cpp/
└── mne-cpp_shadow/
```

## Build a static version of Qt

### Get the Qt source code

Clone the current Qt version. Currently, MNE-CPP uses four Qt modules: QtBase, QtCharts, QtSvg and Qt3D. QtBase subdivides in other modules reflecting most of the Qt functionality (core, gui, widgets, etc). In order to setup the sources for Qt 5.14.2 type:

```
git clone https://code.qt.io/qt/qt5.git -b 5.14.2  
cd qt5
```

### Linux/MacOS

Install OpenGL dependencies (just to make sure). This is only needed on Linux:

```
sudo apt-get install build-essential libgl1-mesa-dev
```

Navigate to the `qt5` folder and init the repository:

```
./init-repository -f --module-subset=qtbase,qtcharts,qtsvg,qt3d
```

Navigate to the parent directory, create a new shadow build folder and cd into it:

```
cd ..
mkdir qt5_shadow
cd qt5_shadow
```

Call configure from the new working directory in order to setup a shadow build:

```
../qt5/configure -static -release -prefix "../qt5_binaries" -skip webengine -nomake tools -nomake tests -nomake examples -no-dbus -no-ssl -no-pch -opensource -confirm-license
```

Build Qt and install to target (prefix) location afterwards. You can change the `-j8` flag to the number of cores you want to use during compilation:

```
make module-qtbase module-qtsvg module-qtcharts module-qt3d -j8
make install -j8
```

A static Qt version should now be setup in the `qt5_binaries` folder.

### Windows 10

Setup the following dependencies:

* Install [Perl](https://www.activestate.com/products/perl/downloads/){:target="_blank" rel="noopener"} and add it to `PATH`
* Install [Python](https://www.python.org/downloads/){:target="_blank" rel="noopener"} and add it to `PATH`
* Install MSVC 2015 or higher (We recommend the [MSVC 2017 Community Version](https://visualstudio.microsoft.com/vs/older-downloads/){:target="_blank" rel="noopener"})
* Install the [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk/){:target="_blank" rel="noopener"} (can also be installed via the MSVC community edition installer)
* If you want to use multiple cores (MSVC's `nmake` does not support multicore usage), install the [jom compiler](http://download.qt.io/official_releases/jom/jom.zip){:target="_blank" rel="noopener"} and add it to `PATH`

Navigate to the `qt5` folder and init the repository:

```
perl init-repository -f --module-subset=qtbase,qtcharts,qtsvg,qt3d
```

Navigate to the parent directory, create a new shadow build folder and cd into it:

```
cd ..
mkdir qt5_shadow
cd qt5_shadow
```

Setup the visual studio compiler by starting the `VS2017 x64 Native Tools Command Prompt` or by typing (assuming you are using MSVC 2017):
    
```
cmd.exe /c "call `"C:\Program Files (x86)\Microsoft Visual Studio 15.0\VC\bin\amd64\vcvars64.bat`" && set > %temp%\vcvars.txt"
Get-Content "$env:temp\vcvars.txt" | Foreach-Object { if ($_ -match "^(.*?)=(.*)$") { Set-Content "env:\$($matches[1])" $matches[2] } }
```

Call configure from the new working directory in order to setup a shadow build.

```
../qt5/configure.bat -release -static -no-pch -optimize-size -opengl desktop -platform win32-msvc -prefix "C:\qt5_static_binaries" -skip webengine -nomake tools -nomake tests -nomake examples -opensource -confirm-license
```
    
Build Qt and install to target (prefix) location afterwards. You can change the `-j8` flag to the number of cores you want to use during compilation:

```
jom -j8
nmake install
```

## Compile MNE-CPP with the `static` flag

Create a shadow build folder, run `qmake` and build MNE-CPP (on Windows use `nmake` or `jom` instead of `make`):

```
mkdir mne-cpp_shadow
cd mne-cpp_shadow
../qt5_binaries/bin/qmake ../mne-cpp/mne-cpp.pro MNECPP_CONFIG += static
make -j8
```

All MNE-CPP applications (MNE Scan, examples, tests, etc.) should now be in the `mne-cpp/bin` folder.
