COMPILER=g++

mkdir -p build
echo "Building..."
$COMPILER *.cpp -o build/PSMoveClicker -lpsmoveapi -Lpsmoveapi-build/build -lX11 -lXtst
echo "Copying lib..."
cp -v psmoveapi-build/build/libpsmoveapi.so build/