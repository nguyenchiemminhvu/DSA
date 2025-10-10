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
    EXPECT_TRUE(testObj == testObj);
    EXPECT_TRUE(testObj == String());
    EXPECT_TRUE(testObj == "");
    EXPECT_FALSE(testObj == "a");
    
    testObj = "a";
    EXPECT_TRUE(testObj == "a");
    EXPECT_FALSE(testObj == "A");
    EXPECT_FALSE(testObj == "");
    EXPECT_FALSE(testObj == "aa");
}

TEST_F(TestStringSuite, MethodSwap)
{
    String testObj;
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);

    String another = "abc";
    testObj.swap(another);
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.capacity(), 6U);

    testObj.swap(another);
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestStringSuite, MethodPushBack)
{
    String testObj;
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);

    testObj.push_back('a');
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 1U);
    EXPECT_EQ(testObj.capacity(), 1U);

    testObj.push_back('a');
    EXPECT_EQ(testObj.size(), 2U);
    EXPECT_EQ(testObj.capacity(), 2U);

    testObj.push_back('a');
    EXPECT_EQ(testObj.size(), 3U);
    EXPECT_EQ(testObj.capacity(), 4U);

    testObj.push_back('a');
    EXPECT_EQ(testObj.size(), 4U);
    EXPECT_EQ(testObj.capacity(), 4U);

    testObj.push_back('a');
    EXPECT_EQ(testObj.size(), 5U);
    EXPECT_EQ(testObj.capacity(), 8U);

    testObj.push_back('a');
    EXPECT_EQ(testObj.size(), 6U);
    EXPECT_EQ(testObj.capacity(), 8U);
    
    testObj.push_back('a');
    EXPECT_EQ(testObj.size(), 7U);
    EXPECT_EQ(testObj.capacity(), 8U);

    testObj.push_back('a');
    EXPECT_EQ(testObj.size(), 8U);
    EXPECT_EQ(testObj.capacity(), 8U);
}

TEST_F(TestStringSuite, MethodPopBack)
{
    String testObj = "abcdef";
    EXPECT_TRUE(testObj.data() != nullptr);
    EXPECT_EQ(testObj.size(), 6U);
    EXPECT_EQ(testObj.capacity(), 12U);

    while (!testObj.empty())
    {
        EXPECT_EQ(testObj.capacity(), 12U);
        testObj.pop_back();
    }

    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestStringSuite, MethodInsertElementAtIndex)
{
    String testObj;
    EXPECT_THROW(testObj.insert(1U, 'a'), std::out_of_range);
    EXPECT_NO_THROW(testObj.insert(0U, 'a'));
    EXPECT_NO_THROW(testObj.insert(1U, 'b'));
    EXPECT_NO_THROW(testObj.insert(2U, 'c'));
    EXPECT_TRUE(testObj == "abc");
}

TEST_F(TestStringSuite, MethodInsertIteratorAtIndex)
{
    String testObj;
    String another = "abc";
    EXPECT_THROW(testObj.insert(1U, another.begin(), another.end()), std::out_of_range);
    EXPECT_NO_THROW(testObj.insert(0U, another.begin(), another.end()));
    EXPECT_TRUE(testObj == another);
}

TEST_F(TestStringSuite, MethodInsertCStyleStringAtIndex)
{
    String testObj;
    EXPECT_THROW(testObj.insert(1U, "abc"), std::out_of_range);
    EXPECT_NO_THROW(testObj.insert(0U, "abc"));
    EXPECT_TRUE(testObj == "abc");
}

TEST_F(TestStringSuite, MethodEraseAtIndex)
{
    String testObj;
    EXPECT_THROW(testObj.erase(0U), std::out_of_range);

    testObj = "abcdef";
    EXPECT_NO_THROW(testObj.erase(testObj.size() - 1U));
    EXPECT_TRUE(testObj == "abcde");

    EXPECT_NO_THROW(testObj.erase(0U));
    EXPECT_TRUE(testObj == "bcde");
    
    while (!testObj.empty())
    {
        testObj.erase(0U);
    }

    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestStringSuite, MethodClear)
{
    String testObj;
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);

    testObj.clear();
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);

    testObj = "abc";
    testObj.clear();
    EXPECT_TRUE(testObj.data() == nullptr);
    EXPECT_EQ(testObj.size(), 0U);
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestStringSuite, MethodAccessFront)
{
    String testObj;
    EXPECT_THROW(testObj.front(), std::out_of_range);

    testObj = "abc";
    EXPECT_NO_THROW(testObj.front());
    EXPECT_EQ(testObj.front(), 'a');

    testObj.erase(0U);
    EXPECT_EQ(testObj.front(), 'b');

    testObj.erase(0U);
    EXPECT_EQ(testObj.front(), 'c');

    testObj.clear();
    EXPECT_THROW(testObj.front(), std::out_of_range);
}

TEST_F(TestStringSuite, MethodAccessBack)
{
    String testObj;
    EXPECT_THROW(testObj.back(), std::out_of_range);

    testObj = "abc";
    EXPECT_NO_THROW(testObj.back());
    EXPECT_EQ(testObj.back(), 'c');

    testObj.pop_back();
    EXPECT_EQ(testObj.back(), 'b');

    testObj.pop_back();
    EXPECT_EQ(testObj.back(), 'a');

    testObj.pop_back();
    EXPECT_THROW(testObj.back(), std::out_of_range);
}

TEST_F(TestStringSuite, AccessOperator)
{
    String testObj;
    EXPECT_THROW(testObj[0], std::out_of_range);

    testObj = "abc";
    for (std::size_t i = 0U; i < testObj.size(); i++)
    {
        EXPECT_NO_THROW(testObj[i]);
    }
}

TEST_F(TestStringSuite, ConcatrationOperator)
{
    String testObj;
    testObj += "abc";
    EXPECT_TRUE(testObj == "abc");

    testObj += "def";
    EXPECT_TRUE(testObj == "abcdef");
}

TEST_F(TestStringSuite, MethodSize)
{
    String testObj;
    EXPECT_EQ(testObj.size(), 0U);

    testObj = "abc";
    EXPECT_EQ(testObj.size(), 3U);

    testObj.clear();
    EXPECT_EQ(testObj.size(), 0U);
}

TEST_F(TestStringSuite, MethodCapacity)
{
    String testObj;
    EXPECT_EQ(testObj.capacity(), 0U);

    testObj = "abc";
    EXPECT_EQ(testObj.capacity(), 6U);

    testObj.clear();
    EXPECT_EQ(testObj.capacity(), 0U);
}

TEST_F(TestStringSuite, MethodReturnCStyleString)
{
    String testObj;
    EXPECT_TRUE(testObj.c_str() == nullptr);

    testObj = "abc";
    const char* str = testObj.c_str();
    EXPECT_TRUE(str != nullptr);
    EXPECT_EQ(strlen(str), 3U);
}
