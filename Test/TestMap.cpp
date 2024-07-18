#include <gtest/gtest.h>

#include "ContainerAssociative/Map.h"

class TestMapSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestMapSuite, ConstructorDefault)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, ConstructorAnotherMap)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, OpeatorAssignmentAnotherMap)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, MethodSwap)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, MethodInsert)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, MethodContain)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, MethodErase)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, MethodClear)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, MethodAt)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, OperatorAccessByKey)
{
    Map<int, int> testObj;
}

TEST_F(TestMapSuite, MethodTraversal)
{
    Map<int, int> testObj;
}
