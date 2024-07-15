#include <gtest/gtest.h>

#include "ContainerAdaptor/Stack.h"

class TestStackSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestStackSuite, ConstructorDefault)
{
    Stack<int> testObj;
    EXPECT_THROW(testObj.top(), std::out_of_range);
    EXPECT_THROW(testObj.pop(), std::out_of_range);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestStackSuite, MethodSwap)
{
    Stack<int> testObj;
    EXPECT_THROW(testObj.top(), std::out_of_range);
    EXPECT_THROW(testObj.pop(), std::out_of_range);
    EXPECT_TRUE(testObj.empty());

    Stack<int> another;
    another.push(1);
    another.push(2);
    another.push(3);

    testObj.swap(another);
    EXPECT_NO_THROW(testObj.top());
    EXPECT_FALSE(testObj.empty());
    EXPECT_EQ(testObj.top(), 3);

    testObj.swap(another);
    EXPECT_THROW(testObj.top(), std::out_of_range);
    EXPECT_THROW(testObj.pop(), std::out_of_range);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestStackSuite, MethodPush)
{
    Stack<int> testObj;
    
    testObj.push(1);
    EXPECT_EQ(testObj.top(), 1);

    testObj.push(2);
    EXPECT_EQ(testObj.top(), 2);

    testObj.push(3);
    EXPECT_EQ(testObj.top(), 3);
}

TEST_F(TestStackSuite, MethodPop)
{
    Stack<int> testObj;

    testObj.push(1);
    testObj.push(2);
    testObj.push(3);

    EXPECT_EQ(testObj.top(), 3);
    testObj.pop();
    EXPECT_EQ(testObj.top(), 2);
    testObj.pop();
    EXPECT_EQ(testObj.top(), 1);
    testObj.pop();
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestStackSuite, MethodTop)
{
    Stack<int> testObj;
    EXPECT_THROW(testObj.top(), std::out_of_range);

    testObj.push(1);
    EXPECT_NO_THROW(testObj.top());
    EXPECT_EQ(testObj.top(), 1);
}
