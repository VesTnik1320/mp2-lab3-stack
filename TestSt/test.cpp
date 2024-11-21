#include "pch.h"
#include "../Stack/TStack.h"

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

TEST(TStack, Copied_stack_is_equal_to_source_one)) {
	TStack<int> b(3);
	b.Push(2);
	b.Push(3);
	TStack<int> a(b);
	ASSERT_NO_THROW(a, b);
}

TEST(TStack, Copied_stack_has_is_own_memory)) {
	TStack<int> b(3);
	b.Push(2);
	TStack<int> a(b);
	a.Push(3);
	EXPECT_NE(a, b);
}

TEST(TStack, Can_push/pop_element)) {
	TStack<int> b(7);
	b.Push(2);
	b.Push(3);
	b.Push(190);
	EXPECT_EQ(b.Pop(), 190);
	EXPECT_EQ(b.Pop(), 3);
	EXPECT_EQ(b.Pop(), 2);
}

TEST(TStack, Throw_pop_empty_element)) {
	TStack<int> b(7);
	ASSERT_ANY_THROW(b.Pop());
}

TEST(TStack, Check_IsEmpty)) {
	TStack<int> b(7);
	EXPECT_TRUE(b.Empty());
	b.Push(1);
	EXPECT_FALSE(b.Empty());
}

TEST(TStack, Can_push_into_full_stack)) {
	TStack<int> b(2);
	b.Push(1);
	b.Push(2);
	ASSERT_ANY_THROW(b.Push(3));
}

TEST(TStack, Can_clear_stack)) {
	TStack<int> b(2);
	b.Push(1);
	b.Clear();
	EXPECT_TRUE(b.Empty());
}

TEST(TStack, Check_size_of_not_equal_stacks)) {
	TStack<int> a(1);
	TStack<int> b(2);
	EXPECT_FALSE(a == b);
}
