mkdir -p build
echo "Building..."
g++ *.cpp -o build/PSMoveClicker -lpsmoveapi -Lpsmoveapi-build/build -std=c++17 \
    `pkg-config gtkmm-4.0 --cflags --libs` \
    -static-libgcc -static-libstdc++
echo "Copying lib..."
cp -v psmoveapi-build/build/psmoveapi.dll build/