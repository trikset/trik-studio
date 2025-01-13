@ECHO OFF
SETLOCAL ENABLEEXTENSIONS
IF ERRORLEVEL 1 ECHO Failed to enable extensions
TITLE TRIK Studio Safe Mode
rem if JAVA_HOME is missing try to find the first Java executable in PATH
IF DEFINED JAVA_HOME (ECHO JAVA_HOME is "%JAVA_HOME%" && set "JAVA_PATH=%JAVA_HOME%\bin") ^
ELSE (   
   java -version 2>NUL
   IF ERRORLEVEL 1 ECHO Missing working java.exe in PATH="%PATH%"
   FOR /f "usebackq tokens=1* delims=:" %%F IN (`where java 2^>NUL ^| findstr /n "^"`) DO @IF %%F == 1 ( ECHO Using Java: "%%G" && SET "JAVA_PATH=%%~dpG")
)
rem Clear PATH after Java detection attempt
SET "PATH=%SystemRoot%;%SystemRoot%\system32"
IF "%JAVA_PATH%" == "" ( ECHO Failed to detect Java/JRE ) ELSE (SET "PATH=%PATH%;%JAVA_PATH%" && java -version)
ENDLOCAL

%~dp0trik-studio.exe "%*"
