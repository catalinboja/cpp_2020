#include "pch.h"
#include "Assignmnet1.h"


double balance = 5000;

TEST(TestWithdraw, TestNegativeBalance) {
	double negative_balance = -5;
	withdraw(&negative_balance, 2000);
	EXPECT_TRUE(negative_balance == -5.5);
}

TEST(TestWithdraw, TestNegativeAmount) {
	double balance = 10;
	withdraw(&balance, -10);
	EXPECT_EQ(balance, 20);
}

TEST(TestWithdraw, TestBalanceTooLow) {
	double balance = 1000;
	withdraw(&balance, 1100);
	EXPECT_EQ(balance, 1000);
}

TEST(TestWithdraw, TestZeroAmount) {
	double balance = 5000;
	withdraw(&balance, 0);
	EXPECT_EQ(balance, 4750);
}

TEST(TestWithdraw, RightTest) {
	double balance = 2000;
	withdraw(&balance, 1000);
	EXPECT_EQ(balance, 1000);
}

//withdraw2

TEST(TestWithdraw2, TestNegativeBalance) {
	double negative_balance = -5;
	withdraw2(negative_balance, 2000);
	EXPECT_TRUE(negative_balance == -5.5);
}

TEST(TestWithdraw2, TestNegativeAmount) {
	double balance = 10;
	withdraw2(balance, -10);
	EXPECT_EQ(balance, 20);
}

TEST(TestWithdraw2, TestBalanceTooLow) {
	double balance = 1000;
	withdraw2(balance, 1100);
	EXPECT_EQ(balance, 1000);
}

TEST(TestWithdraw2, TestZeroAmount) {
	double balance = 5000;
	withdraw2(balance, 0);
	EXPECT_EQ(balance, 4750);
}

TEST(TestWithdraw2, RightTest) {
	double balance = 2000;
	withdraw2(balance, 1000);
	EXPECT_EQ(balance, 1000);
}

// titlecase

TEST(TestTitleCase, RightTest) {
	char* text = "salut. ce mai faci";
	char* newText = toTitleCase(text);
	ASSERT_TRUE(newText != nullptr);
	EXPECT_EQ(strcmp(newText, "Salut. Ce Mai Faci"), 0);
}

// removeSpaces

TEST(TestRemoveSpaces, RightTest) {
	char* text = " salut.   acesta este un test ";
	char* newText = removeSpaces(text);
	ASSERT_TRUE(newText != nullptr);
	EXPECT_EQ(strcmp(newText, "salut.acestaesteuntest"), 0);
}