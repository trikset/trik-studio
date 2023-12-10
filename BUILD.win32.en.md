To build **TRIK Studio for Windows x32 from the command line**, you'll need the following tools and steps:

## Prerequisites
*Ensure that you select options for installing required versions of compilers and tools (in this case, **32-bit**).*
1. [**Python**](https://www.python.org/downloads/windows/): version 3.8 or above;
2. [**MSYS2**](https://www.msys2.org/): latest version;
3. [**Qt for Windows**](https://www.qt.io/download-open-source): version 5.12. Qt Creator and development tools will also be installed during this process.

## Install dependencies
Open msys2, install packages `pkg-config`, `libusb`, `zlib`:
   ```
   pacman -Su mingw-w64-i686-pkg-config mingw-w64-i686-libusb mingw-w64-i686-zlib
   ```

## Build steps
1. **Configure Environment Variables**.
* Make sure that your PATH contains the **C:\Windows\System32** path.
* Add the Qt path to the PATH variable, such as **C:\Qt\5.x.x\mingwXX_32\bin** and **C:\Qt\Tools\mingwXX0_32**, where 5.x.x is the Qt version and mingwXX_32 is your MinGW version.
* Add correct Python path to the PATH variable, for example, **C:\Python\Python3XX-32**, where 3XX is your Python version.
* Add the MinGW paths to the PATH variable, for example, **C:\msys64\mingw32\bin** and **C:\msys64\usr\bin**.

*Here is an example of building for a 32-bit version of Windows with Python 3.10, Qt 5.12.0 and MinGW 7.3.0 32bit:*
   ```
   set PATH=C:\Windows\System32;C:\Qt\Tools\mingw730_32\bin;C:\Qt\5.12.0\mingw73_32\bin;C:\Python\Python310-32;C:\msys64\mingw32\bin;C:\msys64\usr\bin:%PATH%
   ```

2. **Clone repo**.
Open Command Prompt, go to folder, where you want to locate TRIK Studio. Clone TRIK Studio Repository and all dependent modules:
   ```
   git clone https://github.com/trikset/trik-studio.git
   cd trik-studio
   git submodule update --init --recursive
   ```

3. **Prepare folder**.
Create and go to the folder where you want to build the project:
   ```
   mkdir build
   cd build
   ```

4. **Configuring the environment**.
Use the `qmake` command to configure the environment, set various configuration flags and generate build files. You need to add to command parameters the main configuration file - **studio.pro**. This file usually locates in root directory of TRIK Studio project. Also you need to add **PYTHON_PATH** with the path to Python version (that you added to PATH in step 1) to the command parameters.


Here is an example of configuration, where TRIK Studio is located in folder **C:\trik-studio**:
   ```
   qmake C:\trik-studio\studio.pro -spec win32-g++ "CONFIG+=qtquickcompiler" CONFIG+=no-sanitizers CONFIG+=force_debug_info PYTHON_PATH=C:\Python\Python310-32 CONFIG+=tests && mingw32-make qmake_all
   ```

5. **Building the TRIK Studio**.
Call `mingw32-make` to actually build the project using generated build files:
   ```
   mingw32-make -j 4
   ```

6. **Launching the application**.
After a successful build without errors, go to directory with the compiled application and launch TRIK Studio:
   ```
   cd bin\release
   trik-studio.exe
   ```

*Now you have successfully built TRIK Studio under 32-bit Windows, ready to use. Good luck with your work!*
