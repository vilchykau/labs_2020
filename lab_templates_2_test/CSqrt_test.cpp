#include "pch.h"

#include "../lab_templates_2/CSqrt.h"

TEST(LAB_NAME, CSqrt) {
	ASSERT_EQ(cRoot<65>(), 8);
	ASSERT_EQ(cRoot<0>(), 0);
	ASSERT_EQ(cRoot<64>(), 8);
	ASSERT_EQ(cRoot<63>(), 7);
	ASSERT_EQ(cRoot<81>(), 9);
	ASSERT_EQ(cRoot<80>(), 8);
	ASSERT_EQ(cRoot<82>(), 9);
}