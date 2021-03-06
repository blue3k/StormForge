

set CMAKE_SYSTEM_NAME=Windows
set PROCESS_ARCHITECTUR=x64


call ..\..\FindVC.cmd

if not exist build%CMAKE_SYSTEM_NAME% mkdir build%CMAKE_SYSTEM_NAME%
if not exist build%CMAKE_SYSTEM_NAME%\Debug mkdir build%CMAKE_SYSTEM_NAME%\Debug
if not exist build%CMAKE_SYSTEM_NAME%\RelWithDebInfo mkdir build%CMAKE_SYSTEM_NAME%\RelWithDebInfo

cd build%CMAKE_SYSTEM_NAME%


set CONFIGURATION=Debug
cd %CONFIGURATION%
cmake ../../1.17 -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% ^
	-DENABLE_TESTS=OFF -DENABLE_EXAMPLES=OFF ^
	-DENABLE_STATIC=ON -DENABLE_ZLIB=SYSTEM -DENABLE_BSON=ON -DZLIB_ROOT=../../../zlib/zlib-1.2.8 -DZLIB_LIBRARY=../../../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%/lib/zlib ^
	-DCMAKE_APPBUNDLE_PATH=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%;../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%lib;

cd ..

set CONFIGURATION=RelWithDebInfo
cd %CONFIGURATION%
cmake ../../1.17 -G %VCCMAKEGENERATOR% -A %PROCESS_ARCHITECTUR%  ^
	-DCMAKE_INSTALL_PREFIX=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%  -DCMAKE_SYSTEM_NAME=%CMAKE_SYSTEM_NAME% ^
	-DENABLE_TESTS=OFF -DENABLE_EXAMPLES=OFF ^
	-DENABLE_STATIC=ON -DENABLE_ZLIB=SYSTEM -DENABLE_BSON=ON -DZLIB_ROOT=../../../zlib/zlib-1.2.8 -DZLIB_LIBRARY=../../../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%/lib/zlib ^
	-DCMAKE_APPBUNDLE_PATH=../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%;../../../../%CMAKE_SYSTEM_NAME%/%CONFIGURATION%lib;

cd ..
cd ..
