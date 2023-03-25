# PSMoveClicker-electron

Program was made for ADOFAI, but you can use it as a mouse :)

Btw, I'm not responsible for breaking your PSMove or something else

## Wayland

Wayland is **not** currently supported.

Contributions are welcome.

## Building

### Unix

#### Dependencies

Fedora/shit with dnf: `sudo dnf install libusb-compat-0.1-devel libusbx-devel bluez bluez-libs-devel dbus-devel libXtst-devel gtkmm4.0-devel`
Debian/Ubuntu/Linux Mint: Good luck

I will add more distros sometime... For now just install whatever `build-PSMoveApi.sh` spits out and gtkmm4.

#### Building PSMoveApi

Run `build-PSMoveApi.sh` it should do the job. If not, you can manually put `libpsmoveapi.so` in `psmoveapi-build/build/`

#### Building

Run `build.sh`

The default compiler is `clang++` you can change this by editing the top line.

~~I could make the build use CMake, but I'm too lazy and I don't know how to use CMake :D~~

## Usage

Run `sudo run.sh` (It needs to be root because PSMoveApi)

## Credits

* [uiii/FakeInput](https://github.com/uiii/FakeInput)
* [thp/psmoveapi](https://github.com/thp/psmoveapi/)

There's probably more that I forgot about...
