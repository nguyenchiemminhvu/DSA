#include <gtest/gtest.h>

#include "ContainerSequence/Array.h"

class TestArraySuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestArraySuite, ConstructorDefault)
{
    Array<int, 5U> testObj;
    EXPECT_TRUE(testObj.size() == 5U);
}

TEST_F(TestArraySuite, ConstructorInitializeList)
{
    Array<int, 5U> testObj = {1, 2, 3, 4, 5};
    EXPECT_EQ(testObj.size(), 5U);

    for (std::size_t i = 0U; i < testObj.size(); i++)
    {
        EXPECT_EQ(i + 1, testObj[i]);
    }
}

TEST_F(TestArraySuite, Operators)
{
    Array<int, 5U> testObj = {1, 2, 3, 4, 5};
    EXPECT_EQ(testObj[0], 1);
    EXPECT_EQ(testObj[1], 2);
    EXPECT_EQ(testObj[2], 3);
    EXPECT_EQ(testObj[3], 4);
    EXPECT_EQ(testObj[4], 5);
}

TEST_F(TestArraySuite, Iterators)
{
    Array<int, 5U> testObj = {1, 2, 3, 4, 5};

    int cur_val = 1;
    Array<int, 5U>::iterator it = testObj.begin();
    while (it != testObj.end())
    {
        EXPECT_EQ(*it, cur_val);
        cur_val++;
        it++;
    }
}
