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

TEST_F(TestTrieSuite, MethodCount)
{
    Trie testObj;
    testObj.insert("aaaaaaaa");
    EXPECT_EQ(testObj.count("aaaaaaaa"), 1U);

    testObj.insert("aaaaaaaa");
    EXPECT_EQ(testObj.count("aaaaaaaa"), 2U);

    testObj.insert("aaaaaaaa");
    EXPECT_EQ(testObj.count("aaaaaaaa"), 3U);

    testObj.insert("aaaaaaaaa");
    EXPECT_EQ(testObj.count("aaaaaaab"), 0U);
}

TEST_F(TestTrieSuite, MethodContainWildcards)
{
    Trie testObj;
    testObj.insert("abc");
    testObj.insert("abc");
    testObj.insert("abd");
    testObj.insert("abe");

    EXPECT_TRUE(testObj.contain_wildcards("***"));
    EXPECT_TRUE(testObj.contain_wildcards("ab*"));
    EXPECT_TRUE(testObj.contain_wildcards("a*c"));
    EXPECT_TRUE(testObj.contain_wildcards("**e"));
    EXPECT_FALSE(testObj.contain_wildcards("****"));
}

TEST_F(TestTrieSuite, MethodCountWildcards)
{
    Trie testObj;
    testObj.insert("abc");
    testObj.insert("abc");
    testObj.insert("abd");
    testObj.insert("abe");

    EXPECT_EQ(testObj.count_wildcards("ab*"), 4U);
    EXPECT_EQ(testObj.count_wildcards("a*c"), 2U);
    EXPECT_EQ(testObj.count_wildcards("***"), 4U);
    EXPECT_EQ(testObj.count_wildcards("**e"), 1U);
    EXPECT_EQ(testObj.count_wildcards("****"), 0U);
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

    std::sort(L.begin(), L.end());
    EXPECT_TRUE(L[0] == "abc");
    EXPECT_TRUE(L[1] == "abc");
    EXPECT_TRUE(L[2] == "abd");
    EXPECT_TRUE(L[3] == "abe");
}

TEST_F(TestTrieSuite, MethodGetListPrefix)
{
    Trie testObj;

    std::vector<std::string> L = testObj.get_list_prefix("ab");
    EXPECT_TRUE(L.empty());

    testObj.insert("abc");
    testObj.insert("abc");
    testObj.insert("abd");
    testObj.insert("abe");
    L = testObj.get_list_prefix("ab");
    EXPECT_EQ(L.size(), 4U);

    std::sort(L.begin(), L.end());
    EXPECT_TRUE(L[0] == "abc");
    EXPECT_TRUE(L[1] == "abc");
    EXPECT_TRUE(L[2] == "abd");
    EXPECT_TRUE(L[3] == "abe");
}

TEST_F(TestTrieSuite, MethodErase)
{
    Trie testObj;
    testObj.insert("abc");
    testObj.insert("abc");
    testObj.insert("abd");
    testObj.insert("abe");

    EXPECT_EQ(testObj.count("abc"), 2U);

    testObj.erase("abc");
    EXPECT_EQ(testObj.count("abc"), 1U);

    testObj.erase("abc");
    EXPECT_EQ(testObj.count("abc"), 0U);

    testObj.erase("abd");
    EXPECT_FALSE(testObj.contain("abd"));

    testObj.erase("abe");
    EXPECT_FALSE(testObj.contain("abe"));
}

TEST_F(TestTrieSuite, MethodClear)
{
    Trie testObj;

    testObj.insert("abc");
    testObj.insert("abc");
    testObj.insert("abd");
    testObj.insert("abe");

    testObj.clear();
    EXPECT_TRUE(testObj.empty());
}
