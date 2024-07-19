#include <gtest/gtest.h>

#include "Tree/BinaryIndexedTree.h"

class TestBinaryIndexedTreeSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestBinaryIndexedTreeSuite, ConstructorDefault)
{
    BinaryIndexedTree<int> testObj;
}
