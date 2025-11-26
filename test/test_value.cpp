#include <iostream>
#include "nbt_tags.h"
#include "value.h"

using namespace nbt;

int main()
{
    try {
        value v;

        v = int8_t(-5);
        std::cout << "assigned int8_t(-5): as int32=" << int32_t(v) << ", as double=" << double(v) << "\n";

        v = int16_t(12345);
        std::cout << "assigned int16_t(12345): as int32=" << int32_t(v) << ", as double=" << double(v) << "\n";

        v = int32_t(100000);
        std::cout << "assigned int32_t(100000): as int64=" << int64_t(v) << ", as double=" << double(v) << "\n";

        v = float(3.14f);
        std::cout << "assigned float(3.14): as double=" << double(v) << "\n";

        v = double(2.718281828);
        std::cout << "assigned double(2.71828): as double=" << double(v) << "\n";

        std::cout << "Test finished OK\n";
    }
    catch(const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
