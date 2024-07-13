#include <gtest/gtest.h>

#include "ContainerSequence/Vector.h"

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
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);

    Vector<int> another = {1, 2, 3, 4, 5};
    testObj.swap(another);
    EXPECT_TRUE(another.data() == nullptr);
    EXPECT_EQ(another.size(), 0U);
    EXPECT_EQ(another.capacity(), 0U);
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 10U);

    testObj.swap(another);
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
    EXPECT_TRUE(another.data() != nullptr);
    EXPECT_EQ(another.size(), 5U);
    EXPECT_EQ(another.capacity(), 10U);
}

TEST_F(TestVectorSuite, MethodPushBack)
{
    Vector<int> testObj;
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);

    testObj.push_back(1);
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 1U);
    EXPECT_EQ(testObj.capacity(), 1U);

    testObj.push_back(1);
    EXPECT_EQ(testObj.size(), 2U);
    EXPECT_EQ(testObj.capacity(), 2U);

    testObj.push_back(1);
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.capacity(), 4U);

    testObj.push_back(1);
    EXPECT_EQ(testObj.size(), 4U);
    EXPECT_EQ(testObj.capacity(), 4U);

    testObj.push_back(1);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 8U);
    
    testObj.push_back(1);
    EXPECT_EQ(testObj.size(), 6U);
    EXPECT_EQ(testObj.capacity(), 8U);

    testObj.push_back(1);
    EXPECT_EQ(testObj.size(), 7U);
    EXPECT_EQ(testObj.capacity(), 8U);

    testObj.push_back(1);
    EXPECT_EQ(testObj.size(), 8U);
    EXPECT_EQ(testObj.capacity(), 8U);
}

TEST_F(TestVectorSuite, MethodPopBack)
{
    Vector<int> testObj = {1, 2, 3, 4, 5};
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 10U);

    testObj.pop_back();
    EXPECT_EQ(testObj.size(), 4U);
    EXPECT_EQ(testObj.capacity(), 10U);

    while (!testObj.empty())
    {
        testObj.pop_back();
    }

    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestVectorSuite, MethodInsertElementAtIndex)
{
    Vector<int> testObj;
    EXPECT_THROW(testObj.insert(10U, 0), std::out_of_range);

    EXPECT_NO_THROW(testObj.insert(0U, 1));
    EXPECT_EQ(testObj[0], 1);
    EXPECT_EQ(testObj.capacity(), 1U);

    EXPECT_NO_THROW(testObj.insert(0U, 2));
    EXPECT_EQ(testObj[0], 2);

    EXPECT_NO_THROW(testObj.insert(2U, 3));
    EXPECT_EQ(testObj.back(), 3);

    EXPECT_NO_THROW(testObj.insert(2U, 4));
    EXPECT_EQ(testObj[2U], 4);
}

TEST_F(TestVectorSuite, MethodInsertIteratorAtIndex)
{
    Vector<int> testObj;

    Vector<int> another = {1, 2, 3, 4, 5};
    EXPECT_NO_THROW(testObj.insert(0U, another.begin(), another.end()));
    EXPECT_EQ(testObj, another);
}

TEST_F(TestVectorSuite, MethodEraseAtIndex)
{
    Vector<int> testObj;
    EXPECT_THROW(testObj.erase(0U), std::out_of_range);

    testObj = {1, 2, 3, 4, 5};
    EXPECT_NO_THROW(testObj.erase(testObj.size() - 1));

    EXPECT_EQ(testObj.back(), 4);

    while (!testObj.empty())
    {
        testObj.erase(0U);
    }

    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestVectorSuite, MethodClear)
{
    Vector<int> testObj = {1, 2, 3, 4 ,5};
    testObj.clear();
    EXPECT_TRUE(testObj.empty());
    EXPECT_NO_FATAL_FAILURE(testObj.clear());
}

TEST_F(TestVectorSuite, MethodAccessFront)
{
    Vector<int> testObj;
    EXPECT_THROW(testObj.front(), std::out_of_range);
    
    testObj.push_back(1);
    EXPECT_NO_THROW(testObj.front());
    EXPECT_EQ(testObj.front(), 1);
}

TEST_F(TestVectorSuite, MethodAccessBack)
{
    Vector<int> testObj;
    EXPECT_THROW(testObj.back(), std::out_of_range);

    testObj.push_back(1);
    testObj.push_back(2);
    EXPECT_EQ(testObj.back(), 2);
}

TEST_F(TestVectorSuite, AccessOperator)
{
    Vector<int> testObj;

    EXPECT_THROW(testObj[0], std::out_of_range);

    testObj = {1, 2, 3, 4, 5};
    for (std::size_t i = 0U; i < testObj.size(); i++)
    {
        EXPECT_EQ(testObj[i], static_cast<int>(i + 1));
    }
}

TEST_F(TestVectorSuite, MethodSize)
{
    Vector<int> testObj;
    EXPECT_EQ(testObj.size(), 0U);

    testObj = {1, 2, 3, 4, 5};
    EXPECT_EQ(testObj.size(), 5U);

    testObj.clear();
    EXPECT_EQ(testObj.size(), 0U);
}

TEST_F(TestVectorSuite, MethodCapacity)
{
    Vector<int> testObj;
    EXPECT_EQ(testObj.capacity(), 0U);

    testObj = {1, 2, 3, 4, 5};
    EXPECT_EQ(testObj.capacity(), 10U);

    testObj.clear();
    EXPECT_EQ(testObj.capacity(), 0U);
}
