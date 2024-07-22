#include <gtest/gtest.h>

#include "Tree/Trie.h"

class TestTrieSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestTrieSuite, ConstructorDefault)
{
    Trie testObj;
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestTrieSuite, ConstructorSingleString)
{
    std::string str("abc");
    Trie testObj(str);
    EXPECT_FALSE(testObj.empty());
}

TEST_F(TestTrieSuite, ConstructorlistOfStrings)
{
    std::vector<std::string> strs = {
        "abc",
        "abd",
        "bbc",
    };
    Trie testObj(strs);
    EXPECT_FALSE(testObj.empty());
}

TEST_F(TestTrieSuite, MethodSwap)
{
    std::vector<std::string> strs = {
        "abc",
        "abd",
        "bbc",
    };
    Trie another(strs);
    Trie testObj;
    EXPECT_TRUE(testObj.empty());

    testObj.swap(another);
    EXPECT_FALSE(testObj.empty());

    testObj.swap(another);
    EXPECT_TRUE(testObj.empty());
}

TEST_F(TestTrieSuite, MethodInsert)
{
    Trie testObj;
    EXPECT_NO_FATAL_FAILURE(testObj.insert("test"));
    EXPECT_NO_FATAL_FAILURE(testObj.insert("test"));
    EXPECT_NO_FATAL_FAILURE(testObj.insert("abc"));
    EXPECT_NO_FATAL_FAILURE(testObj.insert("adg"));
    EXPECT_NO_FATAL_FAILURE(testObj.insert("nguyen chiem minh vu"));
}

TEST_F(TestTrieSuite, MethodContain)
{
    Trie testObj;
    testObj.insert("aaaaaaaa");
    EXPECT_TRUE(testObj.contain("aaaaaaaa"));

    EXPECT_FALSE(testObj.contain("aaaaaaa"));
    EXPECT_FALSE(testObj.contain("aaaaaaaaa"));
    EXPECT_FALSE(testObj.contain("aaaabaaa"));
}

TEST_F(TestTrieSuite, MethodContainWildcards)
{
    Trie testObj;
}

TEST_F(TestTrieSuite, MethodGetList)
{
    Trie testObj;

    std::vector<std::string> L = testObj.get_list();
    EXPECT_TRUE(L.empty());

    testObj.insert("abc");
    testObj.insert("abc");
    testObj.insert("abd");
    testObj.insert("abe");
    L = testObj.get_list();
    EXPECT_EQ(L.size(), 4U);

    EXPECT_EQ(L[0], "abc");
    EXPECT_EQ(L[1], "abc");
    EXPECT_EQ(L[2], "abd");
    EXPECT_EQ(L[3], "abe");
}

TEST_F(TestTrieSuite, MethodGetListPrefix)
{
    Trie testObj;
}

TEST_F(TestTrieSuite, MethodErase)
{
    Trie testObj;
}

TEST_F(TestTrieSuite, MethodClear)
{
    Trie testObj;
}
