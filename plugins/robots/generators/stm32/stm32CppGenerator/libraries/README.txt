TRIK Studio with STM32 plugin.

Install information:

1. Install the compilers.

You should install GNU ARM Embedded Toolchain with compiler GCC 5.4 from https://launchpad.net/gcc-arm-embedded (Date of reference: 14.05.2017) or https://developer.arm.com/open-source/gnu-toolchain/gnu-rm (Date of reference: 14.05.2017).

You can read more information here http://gnuarmeclipse.github.io/toolchain/install/ (Date of reference: 14.05.2017). 

Directory to install compilers:
Put path to the directory "bin" in the file bin/debug/libraries/compileAndUpload* for your operation system.

Examples:
Windows:
COMPILERS_DIR="C:\Program Files (x86)\GNU Tools ARM Embedded\5.4 2016q3\bin"

Linux:
COMPILERS_DIR="/home/{username}/Downloads/gcc-arm-none-eabi-5_4-2016q3/bin"

MacOS X:
COMPILERS_DIR="/Users/{username}/Downloads/gcc-arm-none-eabi-6-2017-q1-update/bin"

Note:
For Linux you can install toolchain with sudo:
sudo apt-get install gcc-arm-none-eabi

2. Install OpenOCD.

You should install OpenOCD from https://sourceforge.net/projects/openocd/files/openocd/0.10.0/ (Date of reference: 14.05.2017)
You should use OpenOCD version 0.10.0.

Directory to install OpenOCD:
Put path to the directory "openocd-0.10.0" in the file bin/debug/libraries/compileAndUpload* for your operation system.

Examples:

Windows:

OPENOCD_DIR="C:\Users\{username}\Downloads\openocd-0.10.0"

Linux:
OPENOCD_DIR="/home/{username}/Downloads/openocd-0.10.0"

MacOS:
OPENOCD_DIR="/Users/{username}/Downloads/openocd-0.10.0"

Notes:

For Linux you can install OpenOCD with sudo:
sudo apt-get install openocd

For MacOS you can install OpenOCD with Homebrew:
brew install openocd

3. ST-LINK Drivers (for Windows)

If you use Windows, you should download and install ST-LINK drivers from ST's site:
http://www.st.com/content/st_com/en/products/embedded-software/development-tool-software/stsw-link009.html (Date of reference: 14.05.2017)

4. Setup Cygwin (for Windows)

If you use Windows, you should install cygwin from https://www.cygwin.com/ (Date of reference: 14.05.2017)

You definitely need to install these packages:

    Devel/make
    Devel/git

Directory to install Cygwin:
Put path to the directory "bin" in the file bin/debug/libraries/compileAndUploadWin.bat.

Example:
CYGWIN_DIR="C:\cygwin64\bin"

5. Run
