#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../src/Leaf.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
