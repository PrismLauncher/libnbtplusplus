# libnbt++ 2

libnbt++ is a free C++ library for Minecraft's file format Named Binary Tag
(NBT). It can read and write compressed and uncompressed NBT files and
provides a code interface for working with NBT data.

----------

libnbt++2 is a remake of the old libnbt++ library with the goal of making it
more easily usable and fixing some problems. The old libnbt++ especially
suffered from a very convoluted syntax and boilerplate code needed to work
with NBT data.

## Building

This project uses CMake for building. Ensure you have CMake installed.

### Prerequisites
- C++11 compatible compiler
- CMake 3.15 or later
- ZLIB (optional, for compressed NBT support)

### Build Steps
1. Clone the repository:
   ```
   git clone https://github.com/PrismLauncher/libnbtplusplus.git
   cd libnbtplusplus
   ```

2. Create a build directory:
   ```
   mkdir build
   cd build
   ```

3. Configure with CMake:
   ```
   cmake ..
   ```
   Options:
   - `NBT_BUILD_SHARED=OFF` (default): Build static library
   - `NBT_USE_ZLIB=ON` (default): Enable zlib support
   - `NBT_BUILD_TESTS=ON` (default): Build tests

4. Build:
   ```
   cmake --build .
   ```

5. Install (optional):
   ```
   cmake --install .
   ```

## Usage

Include the headers and link against the library.

### Example
```cpp
#include <nbt_tags.h>
#include <fstream>
#include <iostream>

int main() {
    // Read an NBT file
    std::ifstream file("example.nbt", std::ios::binary);
    nbt::tag_compound root = nbt::io::read_compound(file).first;

    // Access data
    std::cout << root["some_key"].as<nbt::tag_string>() << std::endl;

    return 0;
}
```

## License

This project is licensed under the GNU General Public License v3.0. See the [COPYING](COPYING) file for details.
