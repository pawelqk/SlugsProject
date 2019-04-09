#include "gtest/gtest.h"
#include "../src/Leaf.h"

TEST(testxD, lel)
{
    Leaf *leaf = new Leaf();
    leaf->eat();
    EXPECT_EQ(leaf->getSize(), 99);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
