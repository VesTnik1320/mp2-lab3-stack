#include "pch.h"
#include "../Stack/TSack2.h"

TEST(TStack, Can_create_stack_with_positive_size) {
	ASSERT_NO_THROW(TStack<int> a(10));
}

TEST(TStack, Can_create_too_large_stack) {
	ASSERT_ANY_THROW(TStack<int> a(999999));
}

TEST(TStack, Can_create_stack_with_negativ_size) {
	ASSERT_ANY_THROW(TStack<int> a(-10));
}

TEST(TStack, Can_create_copied_stack) {
	TStack<int> b(3);
	ASSERT_NO_THROW(TStack<int> a(b));
}

TEST(TStack, Copied_stack_is_equal_to_source_one) {
	TStack<int> b(3);
	b.Push(2);
	b.Push(3);
	TStack<int> a(b);
	ASSERT_NO_THROW(a, b);
}

TEST(TStack, Copied_stack_has_is_own_memory) {
	TStack<int> b(3);
	b.Push(2);
	TStack<int> a(b);
	a.Push(3);
	EXPECT_NE(a, b);
}

TEST(TStack, Can_push_and_pop_element) {
	TStack<int> b(7);
	b.Push(2);
	b.Push(3);
	b.Push(190);
	EXPECT_EQ(b.Pop(), 190);
	EXPECT_EQ(b.Pop(), 3);
	EXPECT_EQ(b.Pop(), 2);
}

TEST(TStack, Throw_pop_empty_element) {
	TStack<int> b(7);
	ASSERT_ANY_THROW(b.Pop());
}

TEST(TStack, Check_IsEmpty) {
	TStack<int> b(7);
	EXPECT_TRUE(b.Empty());
	b.Push(1);
	EXPECT_FALSE(b.Empty());
}

TEST(TStack, Can_push_into_full_stack) {
	TStack<int> b(2);
	b.Push(1);
	b.Push(2);
	ASSERT_ANY_THROW(b.Push(3));
}

TEST(TStack, Can_clear_stack) {
	TStack<int> b(2);
	b.Push(1);
	b.Clear();
	EXPECT_TRUE(b.Empty());
}

TEST(TStack, Check_size_of_not_equal_stacks) {
	TStack<int> a(1);
	TStack<int> b(2);
	EXPECT_FALSE(a == b);
}

TEST(TStack, Check_size_of_not_equal_stacks2)
{
	TStack<int> a(8);
	TStack<int> b(2);
	EXPECT_TRUE(a != b);

}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> a(5);
	a.Push(3);
	ASSERT_NO_THROW(a = a);
	EXPECT_TRUE(a == a);
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
	TStack<int> a(5);
	a.Push(3);
	TStack<int> b(5);
	ASSERT_NO_THROW(b = a);
	EXPECT_EQ(b, a);

}

TEST(TStack, can_assign_stacks_of_different_size)
{
	TStack<int> a(5);
	a.Push(2);
	TStack<int> b(3);
	ASSERT_NO_THROW(b = a);
	EXPECT_EQ(b, a);

}

TEST(TStack, compare_equal_stacks)
{
	TStack<int> a(3);
	TStack<int> b(3);
	a.Push(2);
	b.Push(2);
	EXPECT_TRUE(a == b);
}

TEST(TStack, Check_top_on_empty_stack)
{
	TStack<int> a(3);
	ASSERT_ANY_THROW(a.Top());
}

TEST(TStack, Check_top_element_without_removing)
{
	TStack<int> a(5);
	a.Push(2);
	EXPECT_EQ(a.Top(), 2);
	EXPECT_FALSE(a.Empty());
}
TEST(TStack, Check_full_stack_isFull)
{
	TStack<int> a(2);
	a.Push(5);
	a.Push(2);
	EXPECT_TRUE(a.Full());
}

TEST(TStack, check_empty_stacks_of_same_size_are_equal)
{
	TStack<int> a(5);
	TStack<int> b(5);
	EXPECT_EQ(a, b);
}

TEST(TStack, copying_stack_does_not_break_original)
{
	TStack<int> b(3);
	b.Push(2);
	b.Push(3);
	TStack<int> a(b);
	a.Pop();
	EXPECT_EQ(b.Top(), 3);
}

TEST(TStack, can_push_and_check_top)
{
	TStack<int> a(3);
	a.Push(52);
	EXPECT_EQ(a.Top(), 52);
	EXPECT_EQ(a.Pop(), 52);
	EXPECT_TRUE(a.Empty());
}

TEST(TStack, clear_works_correctly_on_non_empty_stack)
{
	TStack<int> a(6);
	a.Push(6);
	a.Push(3);
	a.Push(2);
	a.Clear();
	EXPECT_TRUE(a.Empty());
	EXPECT_ANY_THROW(a.Pop());
}

/////////////////////////

TEST(TCalc, can_create_postfix) {
	TCalc c;
	c.SetInfix("1+6-4");
	EXPECT_NO_THROW(c.ToPostfix());
	c.ToPostfix();
	EXPECT_EQ(c.GetPostfix(), "1 6 + 4 - ");
}
TEST(TCalc, can_not_create_wrong_postfix) {
	TCalc c;
	c.SetInfix("5*2))");
	EXPECT_ANY_THROW(c.ToPostfix());
	c.SetInfix("((6+3");
	EXPECT_ANY_THROW(c.ToPostfix());
}
TEST(TCalc, can_add_numbers)
{
	TCalc c;
	c.SetInfix("1+3");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 4);
	c.SetInfix("9+8");
	EXPECT_EQ(c.Calc(), 17);
}
TEST(TCalc, can_subtract_numbers)
{
	TCalc c;
	c.SetInfix("6-3");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 3);
	c.SetInfix("8-9");
	EXPECT_EQ(c.Calc(), -1);
}
TEST(TCalc, can_multiply_numbers)
{
	TCalc c;
	c.SetInfix("6*3");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 18);
	c.SetInfix("5*2");
	EXPECT_EQ(c.Calc(), 10);
}
TEST(TCalc, can_divide_numbers)
{
	TCalc c;
	c.SetInfix("6/3");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 2);
	c.SetInfix("6/4");
	EXPECT_EQ(c.Calc(), 1.5);
}
TEST(TCalc, can_raises_a_number_to_a_power)
{
	TCalc c;
	c.SetInfix("2^10");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 1024);
	c.SetInfix("2^6");
	EXPECT_EQ(c.Calc(), 64);
}
TEST(TCalc, can_perform_arithmetic_expressions)
{
	TCalc c;
	c.SetInfix("6^3*5+2-1");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 1081);
	c.SetInfix("5-2+(6-3)^3+6/4+5*2");
	EXPECT_EQ(c.Calc(), 41.5);
}
TEST(TCalc, throws_when_dividing_by_zero) {
	TCalc c;
	c.SetInfix("6/0");
	c.ToPostfix();
	EXPECT_ANY_THROW(c.CalcPostfix());
	c.SetInfix("3/0");
	EXPECT_ANY_THROW(c.Calc());
}
TEST(TCalc, can_work_with_unary_minus) {
	TCalc c;
	c.SetInfix("-2+5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 3);
	c.SetInfix("-6+3");
	EXPECT_EQ(c.Calc(), -3);
}
TEST(TCalc, throws_when_invalid_expression) {
	TCalc c;
	c.SetInfix("+");
	c.ToPostfix();
	EXPECT_ANY_THROW(c.CalcPostfix());
	c.SetInfix("9+*3");
	c.ToPostfix();
	EXPECT_ANY_THROW(c.CalcPostfix());
	c.SetInfix("6*");
	c.ToPostfix();
	EXPECT_ANY_THROW(c.CalcPostfix());

	c.SetInfix("2+7A5");
	EXPECT_ANY_THROW(c.Calc());
	c.SetInfix("8*6))");
	EXPECT_ANY_THROW(c.Calc());
	c.SetInfix("((5+5");
	EXPECT_ANY_THROW(c.Calc());

	c.SetInfix("+");
	EXPECT_ANY_THROW(c.Calc());
	c.SetInfix("9+*3");
	EXPECT_ANY_THROW(c.Calc());
	c.SetInfix("8*");
	EXPECT_ANY_THROW(c.Calc());
}
TEST(TCalc, can_divide_positive_numbers) {
	TCalc c;
	c.SetInfix("5/2");
	EXPECT_DOUBLE_EQ(c.Calc(), 2.5);
}
TEST(TCalc, can_add_positive_decimal_and_integer) {
	TCalc c;
	c.SetInfix("3.14+5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 8.14);
}
TEST(TCalc, can_multiply_two_positive_numbers) {
	TCalc c;
	c.SetInfix("2.5*4");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 10.0);
}
TEST(TCalc, can_raise_decimal_to_power) {
	TCalc c;
	c.SetInfix("2.5^3");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 15.625);
}
TEST(TCalc, can_raise_decimal_to_fractional_power) {
	TCalc c;
	c.SetInfix("4.0^0.5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 2.0);
}