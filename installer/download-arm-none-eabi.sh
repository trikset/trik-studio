#!/usr/bin/bash -x
sudo apt install wget
help()
{
    echo "Usage: download-arm-none-eabi.sh [ -p | --path ] /path/to/dir
               [ -h | --help  ]"
    exit 0
}
PATH="/home/$USER"


install_arm()
{
wget https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz

tar -xf arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz -C $PATH
echo "arm-none-eabi installed at $PATH"
}




if [ $# -eq 0 ]
then
    read -r -p "Do you want to install arm-none-eabi at $PATH? [y/N] " response
    if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]
    then
       install_arm
    else
        help
    fi
    exit 0
fi



case "$1" in
-p | --path )
    PATH=$2
    if [[ ! -d "$PATH" ]]
    then
        echo "$PATH doesn't exists on your filesystem."
    else
        install_arm
    fi
    ;;

-h | --help)
    help
    ;;

*)
    echo "Unexpected option: $1"
    help
    ;;
esac





