#include <gtest/gtest.h>

#include "ContainerAssociative/Set.h"

class TestSetSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestSetSuite, ConstructorDefault)
{
    Set<int> testObj;
}

TEST_F(TestSetSuite, ConstructorInitializerList)
{
    Set<int> testObj;
}

TEST_F(TestSetSuite, ConstructorVector)
{
    Set<int> testObj;
}

TEST_F(TestSetSuite, ConstructorAnotherSet)
{
    Set<int> testObj;
}

TEST_F(TestSetSuite, MethodSwap)
{
    Set<int> testObj;
}

TEST_F(TestSetSuite, MethodInsert)
{
    Set<int> testObj;
}

TEST_F(TestSetSuite, MethodErase)
{
    Set<int> testObj;
}

TEST_F(TestSetSuite, MethodClear)
{
    Set<int> testObj;
}

TEST_F(TestSetSuite, MethodCount)
{
    Set<int> testObj;
}

TEST_F(TestSetSuite, MethodFind)
{
    Set<int> testObj;
}
