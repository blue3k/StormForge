

export CMAKE_SYSTEM_NAME=Linux
export PROCESS_ARCHITECTUR=x64


pushd $CMAKE_SYSTEM_NAME


export CONFIGURATION=Debug
pushd $CONFIGURATION
cmake --build . --target install  --config $CONFIGURATION

popd


export CONFIGURATION=RelWithDebInfo
pushd $CONFIGURATION
cmake --build . --target install  --config $CONFIGURATION

popd
popd

