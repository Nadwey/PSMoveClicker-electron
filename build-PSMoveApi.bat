git clone --recursive https://github.com/thp/psmoveapi.git psmoveapi-build
cd psmoveapi-build
mkdir -p build
cd build
cmake ..
echo Idk if the build was successful, but now you need to go to psmoveapi-build/build, open `PSMoveAPI.sln` using Visual studio and build everything