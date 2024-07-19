#include <gtest/gtest.h>

#include "Tree/SegmentTree.h"

class TestSegmentTreeSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(TestSegmentTreeSuite, ConstructorDefault)
{
    SegmentTree<int> testObj;
}
