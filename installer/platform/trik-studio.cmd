FOR /F "tokens=* USEBACKQ" %%F IN (`where java`) DO (SET JAVA_PATH=%%~dpF)

set PATH=%SystemRoot%;%SystemRoot%\system32;%JAVA_PATH%;
%~dp0trik-studio.exe %*
