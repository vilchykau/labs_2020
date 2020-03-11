#include "pch.h"

#include "../lab_templates_2/Complex.h"

TEST(LAB_NAME, ComplexInit) {
	{
		using c = Complex<1>;
		ASSERT_EQ(c::rl, 1);
		ASSERT_EQ(c::im, 0);
		ASSERT_EQ(c::abs, 1);
	}
	{
		using c = Complex<1, 1>;
		ASSERT_EQ(c::rl, 1);
		ASSERT_EQ(c::im, 1);
		ASSERT_EQ(c::abs, 1);
	}
	{
		using c = Complex<-3, 4>;
		ASSERT_EQ(c::rl, -3);
		ASSERT_EQ(c::im, 4);
		ASSERT_EQ(c::abs, 5);
	}
}

TEST(LAB_NAME, ComplexSum) {
	{
		using c1 = Complex<1>;
		using c2 = Complex<-1, 2>;
		using sum = ComplexSum<c1, c2>::value;
		ASSERT_EQ(sum::rl, 0);
		ASSERT_EQ(sum::im, 2);
		ASSERT_EQ(sum::abs, 2);
	}
}

TEST(LAB_NAME, ComplexSub) {
	{
		using c1 = Complex<-1>;
		using c2 = Complex<-1, 2>;
		using sum = ComplexSub<c1, c2>::value;
		ASSERT_EQ(sum::rl, 0);
		ASSERT_EQ(sum::im, -2);
		ASSERT_EQ(sum::abs, 2);
	}
}

TEST(LAB_NAME, ComplexRoot) {
	{
		using r1 = ComplexRoot<-5>;
		ASSERT_EQ(r1::value_1::rl, 0);
		ASSERT_EQ(r1::value_1::im, 2);
		ASSERT_EQ(r1::value_2::rl, 0);
		ASSERT_EQ(r1::value_2::im, -2);
	}
	{
		using r1 = ComplexRoot<5>;
		ASSERT_EQ(r1::value_1::rl, 2);
		ASSERT_EQ(r1::value_1::im, 0);
		ASSERT_EQ(r1::value_2::rl, -2);
		ASSERT_EQ(r1::value_2::im, 0);
	}
}