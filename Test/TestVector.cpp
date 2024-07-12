#include <gtest/gtest.h>

#include "DSA/Vector.h"

class TestVectorSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestVectorSuite, ConstructorDefault)
{
    Vector<int> testObj;
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestVectorSuite, ConstructorList)
{
    Vector<int> testObj = {1, 2, 3, 4, 5};
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 10U);
}

TEST_F(TestVectorSuite, ConstructorIterator)
{
    int buffer[5] = {1, 2, 3, 4, 5};
    Vector<int> testObj(buffer, buffer + 5);
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 10U);

    for (std::size_t i = 0U; i < testObj.size(); i++)
    {
        EXPECT_EQ(testObj[i], buffer[i]);
    }
}

TEST_F(TestVectorSuite, ConstructorAnotherVector)
{
    Vector<int> anotherV1;
    Vector<int> testObj1(anotherV1);
    EXPECT_TRUE(testObj1.data() == nullptr);
    EXPECT_EQ(testObj1.size(), 0U);
    EXPECT_EQ(testObj1.capacity(), 0U);

    Vector<int> anotherV2 = {1, 2, 3, 4 ,5};
    Vector<int> testObj2(anotherV2);
    EXPECT_TRUE(testObj2.data() != nullptr);
    EXPECT_EQ(testObj2.size(), 5U);
    EXPECT_EQ(testObj2.capacity(), 10U);

    for (std::size_t i = 0U; i < testObj2.size(); i++)
    {
        EXPECT_EQ(testObj2[i], anotherV2[i]);
    }
}

TEST_F(TestVectorSuite, AssignmentOperator)
{
    Vector<int> another = {1, 2, 3, 4 ,5};
    Vector<int> testObj = another;
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 10U);

    for (std::size_t i = 0U; i < testObj.size(); i++)
    {
        EXPECT_EQ(testObj[i], another[i]);
    }
}

TEST_F(TestVectorSuite, CompareEqualOperator)
{
    Vector<int> v1;
    Vector<int> v2;
    EXPECT_TRUE(v1 == v2);

    v1.push_back(1);
    v2.push_back(2);
    EXPECT_FALSE(v1 == v2);

    v1.clear();
    v2.clear();
    EXPECT_TRUE(v1 == v2);

    v1.push_back(5);
    v2.push_back(5);
    EXPECT_TRUE(v1 == v2);

    v1.clear();
    EXPECT_FALSE(v1 == v2);
}

TEST_F(TestVectorSuite, MethodSwap)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodPushBack)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodPopBack)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodInsertElementAtIndex)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodInsertIteratorAtIndex)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodInsertElemetAtIterator)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodInsertIteratorAtIterator)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodEraseAtIndex)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodEraseAtIterator)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodClear)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodAccessFront)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodAccessBack)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, AccessOperator)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodSize)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodCapacity)
{
    Vector<int> testObj;
}

TEST_F(TestVectorSuite, MethodExpand)
{
    Vector<int> testObj;
}
