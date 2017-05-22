TRIK Studio with STM32 plugin.

Install information:

1. Setup Cygwin (for Windows)

Hope you'll figure out how to setup cygwin by yourself.

You definitely need to install these packages:

    Devel/make
    Devel/git

Directory to install Cygwin:
"C:\cygwin64\"

2. Install the compilers

Just grab the latest from https://launchpad.net/gcc-arm-embedded in .exe and install compilers. I highly recommend to add environment variables to your path when promted at the last step of installation.

Directory to install compilers:
Put path to the directory in the file bin/debug/libraries/compileAndUpload... for your operation system.

Examples:
Windows:
"C:\Program Files (x86)\GNU Tools ARM Embedded\5.4 2016q3\bin"

Linux:
You can install with sudo:
sudo apt-get install gcc-arm-none-eabi

3. Drivers (for Windows)

Download and install ST-LINK drivers from ST's site:

http://www.st.com/content/st_com/en/products/embedded-software/development-tool-software/stsw-link009.html

4. Install OpenOCD

Grab the precompiled binaries from https://sourceforge.net/projects/openocd/files/openocd/0.10.0/
You should use OpenOCD version 0.10.0.

Install openOCD to the directory:
Put path to the directory in the file bin/debug/libraries/compileAndUpload... for your operation system.

Examples:

Windows:
"C:\cygwin64\install\openocd-0.10.0"

Linux:
You can install with sudo:
sudo apt-get install openocd

5. Run
