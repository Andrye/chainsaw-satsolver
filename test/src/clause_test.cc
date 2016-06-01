#include <iostream>
#include <sstream>

#include "gtest/gtest.h"
#include "sat_include_all.h"

TEST(ClauseTest, test_1)
{
    clause cl;
    cl.addVariable(2);
    EXPECT_FALSE(cl.isEmpty());
    EXPECT_FALSE(cl.isSatisfied());
}

TEST(ClauseTest, test_2)
{
    clause cl;
    cl.addVariable(2);
    cl.addSatisfyingLiteral(2);
    EXPECT_TRUE(cl.isSatisfied());
}

TEST(ClauseTest, test_3)
{
    clause cl;
    cl.addVariable(1);
    cl.addSatisfyingLiteral(2);
    EXPECT_FALSE(cl.isSatisfied());
}

TEST(ClauseTest, test_4)
{
    clause cl;
    cl.addVariable(1);
    EXPECT_FALSE(cl.isSatisfied());
}

TEST(ClauseTest, test_5)
{
    clause cl;
    cl.addVariable(1);
    EXPECT_TRUE(cl.isUnitClause());

    cl.addVariable(2);
    EXPECT_FALSE(cl.isUnitClause());

    EXPECT_TRUE(cl.removeLiteral(1));
    EXPECT_TRUE(cl.isUnitClause());
}

TEST(ClauseTest, test_6)
{
    clause cl;
    cl.addVariable(1);
    cl.addVariable(2);

    EXPECT_TRUE(cl.removeLiteral(2));
    EXPECT_FALSE(cl.removeLiteral(2));
}

TEST(ClauseTest, test_7)
{
    clause cl;
    cl.addVariable(1);
    EXPECT_TRUE(cl.isUnitClause());

    cl.addVariable(2);
    EXPECT_FALSE(cl.isUnitClause());

    cl.addVariable(3);
    EXPECT_FALSE(cl.isUnitClause());

    EXPECT_TRUE(cl.removeLiteral(3));
    EXPECT_FALSE(cl.isUnitClause());

    EXPECT_FALSE(cl.removeLiteral(3));
    EXPECT_FALSE(cl.isUnitClause());

    EXPECT_TRUE(cl.removeLiteral(2));
    EXPECT_TRUE(cl.isUnitClause());
}

TEST(ClauseTest, test_8)
{
    std::stringstream sstr;
    clause cl;
    std::vector<typename clause::literal_type> ll{1,2,3,4,5};
    for (const auto& i : ll)
        cl.addVariable(i);
    std::copy(cl.begin(), cl.end(), std::ostream_iterator<typename clause::literal_type>(sstr, " "));
    EXPECT_EQ("1 2 3 4 5 ", sstr.str());
}
