#include <gtest/gtest.h>

#include "ContainerSequence/String.h"

class TestStringSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestStringSuite, ConstructorDefault)
{
    String testObj;
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestStringSuite, ConstructorList)
{
    String testObj = {'a', 'b', 'c'};
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.capacity(), 6U);
    EXPECT_EQ(testObj[0], 'a');
    EXPECT_EQ(testObj[1], 'b');
    EXPECT_EQ(testObj[2], 'c');
}

TEST_F(TestStringSuite, ConstructorAnotherString)
{
    String another = {'a', 'b', 'c'};
    String testObj(another);
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.capacity(), 6U);
    EXPECT_EQ(testObj[0], 'a');
    EXPECT_EQ(testObj[1], 'b');
    EXPECT_EQ(testObj[2], 'c');
}

TEST_F(TestStringSuite, ConstructorCStyleString)
{
    String testObj("abc");
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.capacity(), 6U);
    EXPECT_EQ(testObj[0], 'a');
    EXPECT_EQ(testObj[1], 'b');
    EXPECT_EQ(testObj[2], 'c');
}

TEST_F(TestStringSuite, ConstructorCStyleStringWithSize)
{
    String testObj("abcdef", 3U);
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.capacity(), 6U);
    EXPECT_EQ(testObj[0], 'a');
    EXPECT_EQ(testObj[1], 'b');
    EXPECT_EQ(testObj[2], 'c');
}

TEST_F(TestStringSuite, AssignmentOperatorAnotherString)
{
    String another("abc");
    String testObj = another;
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.capacity(), 6U);
    EXPECT_EQ(testObj[0], 'a');
    EXPECT_EQ(testObj[1], 'b');
    EXPECT_EQ(testObj[2], 'c');
}

TEST_F(TestStringSuite, AssignmentOperatorCStyleString)
{
    String testObj = "abc";
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.capacity(), 6U);
    EXPECT_EQ(testObj[0], 'a');
    EXPECT_EQ(testObj[1], 'b');
    EXPECT_EQ(testObj[2], 'c');
}

TEST_F(TestStringSuite, CompareEqualOperator)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodSwap)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodPushBack)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodPopBack)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodInsertElementAtIndex)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodInsertIteratorAtIndex)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodInsertCStyleStringAtIndex)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodInsertElementAtIterator)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodInsertIteratorAtIterator)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodInsertAnotherStringAtIterator)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodInsertCStyleStringAtIterator)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodEraseAtIndex)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodEraseAtIterator)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodClear)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodAccessFront)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodAccessBack)
{
    String testObj;
}

TEST_F(TestStringSuite, AccessOperator)
{
    String testObj;
}

TEST_F(TestStringSuite, ConcatrationOperator)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodSize)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodCapacity)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodReturnCStyleString)
{
    String testObj;
}

TEST_F(TestStringSuite, MethodExpand)
{
    String testObj;
}
