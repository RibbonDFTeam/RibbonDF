#include <stdio.h>
#include "RibbonDF_config.h"
#include "gtest/gtest.h"

bool Even(int num)
{
    if (num % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

TEST(EvenTest, EvenTest)
{
    EXPECT_TRUE(Even(0));
    EXPECT_FALSE(Even(1));
    EXPECT_TRUE(Even(2));
    EXPECT_FALSE(Even(3));
    EXPECT_TRUE(Even(4));
}

int main()
{
    printf("start gtest\n");
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
