#include <cxxtest/TestSuite.h>
#include <cstdint>
#include "value.h"

using namespace nbt;

class value_assignment_test : public CxxTest::TestSuite
{
public:
    void test_numeric_assignments()
    {
        value v;

        v = int8_t(-5);
        TS_ASSERT_EQUALS(int32_t(v), int32_t(-5));
        TS_ASSERT_EQUALS(double(v), static_cast<double>(int8_t(-5)));

        v = value();
        v = int16_t(12345);
        TS_ASSERT_EQUALS(int32_t(v), int32_t(12345));
        TS_ASSERT_EQUALS(double(v), static_cast<double>(int16_t(12345)));

        v = value();
        v = int32_t(100000);
        TS_ASSERT_EQUALS(int64_t(v), int64_t(100000));
        TS_ASSERT_EQUALS(double(v), static_cast<double>(int32_t(100000)));

        v = value();
        v = float(3.14f);
        TS_ASSERT_EQUALS(double(v), static_cast<double>(3.14f));

        v = value();
        v = double(2.718281828);
        TS_ASSERT_EQUALS(double(v), 2.718281828);
    }
};
