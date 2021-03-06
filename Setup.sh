#!/bin/bash


SF_PATH=$(dirname "$0")
FBX_SDK_INSTALL_FILE_LINUX=fbx20201_fbxsdk_linux.tar.gz

ATF_PATH=$SF_PATH/../ATF


# install vulkan SDK link
if [ ! -f "/etc/apt/sources.list.d/lunarg-vulkan-1.2.148-bionic.list" ]; then
	wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
	sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.2.148-bionic.list https://packages.lunarg.com/vulkan/1.2.148/lunarg-vulkan-1.2.148-bionic.list
	sudo apt update
fi


sudo apt-get install git-lfs build-essential clang cmake rsync zip ninja-build
sudo apt-get install -y libatomic-ops-dev gdb
sudo apt install build-essential clang vulkan-sdk libssl-dev perl libssl-dev pkg-config libsasl2-dev


if [ ! -d "$ATF_PATH" ]; then
	echo $ATF_PATH
	git clone https://github.com/blue3k/ATFClone.git $ATF_PATH
fi


if [ ! -f "Test/UnitTest/UnitTest1/Test/LogServer/LocalData/serveraddress.txt" ]; then
	mkdir Test/UnitTest/UnitTest1/Test/LogServer/LocalData
	cp Test/UnitTest/UnitTest1/Test/LogServer/serveraddress_sample.txt Test/UnitTest/UnitTest1/Test/LogServer/LocalData/serveraddress.txt
fi


pushd $SF_PATH/3rdParties 


# linux version install doesn't work
# if [ ! -f "$FBX_SDK_INSTALL_FILE_LINUX" ]; then
	# wget https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-1/fbx20201_fbxsdk_linux.tar.gz
	# sudo apt install uuid-dev libxmu-dev libxi-dev libx11-dev
# fi

# # linux version install doesn't work
# if [ ! -d "FBXSDK_Linux_Install" ]; then
	# mkdir FBXSDK_Linux_Install
# fi
# tar -xvf fbx20201_fbxsdk_linux.tar.gz -C FBXSDK_Linux_Install
# chmod ugo+x FBXSDK_Linux_Install/fbx20201_fbxsdk_linux
# ./FBXSDK/fbx20201_fbxsdk_linux /usr




pushd src/mysql/
./setup_ubuntu.sh
popd

pushd src/mongoc/
./download.sh
popd

pushd src/lzma/
./download.sh
popd

pushd src/jansson/
./download.sh
popd

pushd src/avro/
./download.sh
popd



echo ==============================================================
echo Register test host names 
echo Zookeeper: SFTestZookeeper.com
echo Kafka: SFTestKafka.com
echo host file location
echo   - Windows 10 – “C:\Windows\System32\drivers\etc\hosts”
echo   - Linux – “/etc/hosts”
echo   - Mac OS X – “/private/etc/hosts”
echo ==============================================================

# to root
popd


