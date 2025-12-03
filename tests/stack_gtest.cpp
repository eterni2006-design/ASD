#include <gtest/gtest.h>
#include "../lib_easy_example/easy_example.h"
#include "stack.h"
#include <string>


TEST(StackTest, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(stack.get_capacity(), 0);
}

TEST(StackTest, ConstructorWithInitialCapacity) {
    Stack<int> stack(10);
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    EXPECT_GE(stack.get_capacity(), 10);
}

TEST(StackTest, ConstructorWithInitializerList) {
    Stack<int> stack = { 1, 2, 3, 4, 5 };
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.top(), 5);
}

TEST(StackTest, CopyConstructor) {
    Stack<int> stack1 = { 1, 2, 3 };
    Stack<int> stack2 = stack1;

    EXPECT_EQ(stack1.size(), stack2.size());
    EXPECT_EQ(stack1.top(), stack2.top());
    EXPECT_FALSE(stack2.empty());

    // Изменение одной не должно влиять на другую
    stack1.pop();
    EXPECT_EQ(stack1.size(), 2);
    EXPECT_EQ(stack2.size(), 3);
}

TEST(StackTest, AssignmentOperator) {
    Stack<int> stack1 = { 1, 2, 3 };
    Stack<int> stack2;
    stack2 = stack1;

    EXPECT_EQ(stack1.size(), stack2.size());
    EXPECT_EQ(stack1.top(), stack2.top());

    stack1.push(4);
    EXPECT_EQ(stack1.size(), 4);
    EXPECT_EQ(stack2.size(), 3);
}

TEST(StackTest, SelfAssignment) {
    Stack<int> stack = { 1, 2, 3 };
    stack = stack;

    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), 3);
}

TEST(StackTest, PushAndTop) {
    Stack<int> stack;

    stack.push(10);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 10);

    stack.push(20);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 20);

    stack.push(30);
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), 30);
}

TEST(StackTest, Pop) {
    Stack<int> stack = { 10, 20, 30 };

    EXPECT_EQ(stack.top(), 30);
    stack.pop();
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 20);

    stack.pop();
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 10);

    stack.pop();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, PopEmptyStack) {
    Stack<int> stack;

    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackTest, TopEmptyStack) {
    Stack<int> stack;

    EXPECT_THROW(stack.top(), std::out_of_range);
}

TEST(StackTest, ConstTop) {
    const Stack<int> stack = { 1, 2, 3 };

    EXPECT_EQ(stack.top(), 3);
    EXPECT_EQ(stack.size(), 3);
}

TEST(StackTest, Clear) {
    Stack<int> stack = { 1, 2, 3, 4, 5 };

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 5);

    stack.clear();

    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    EXPECT_THROW(stack.top(), std::out_of_range);
}

TEST(StackTest, Reserve) {
    Stack<int> stack;

    EXPECT_EQ(stack.get_capacity(), 0);

    stack.reserve(20);
    EXPECT_GE(stack.get_capacity(), 20);

    // Добавление элементов не должно вызывать перераспределение
    size_t old_capacity = stack.get_capacity();
    for (int i = 0; i < 15; i++) {
        stack.push(i);
    }
    EXPECT_EQ(stack.get_capacity(), old_capacity);
}

TEST(StackTest, AutoResize) {
    Stack<int> stack;

    // Добавляем больше элементов, чем начальная емкость
    for (int i = 0; i < 100; i++) {
        stack.push(i);
    }

    EXPECT_EQ(stack.size(), 100);
    EXPECT_GE(stack.get_capacity(), 100);
    EXPECT_EQ(stack.top(), 99);
}

TEST(StackTest, Swap) {
    Stack<int> stack1 = { 1, 2, 3 };
    Stack<int> stack2 = { 4, 5, 6, 7 };

    size_t size1 = stack1.size();
    size_t size2 = stack2.size();

    stack1.swap(stack2);

    EXPECT_EQ(stack1.size(), size2);
    EXPECT_EQ(stack2.size(), size1);
    EXPECT_EQ(stack1.top(), 7);
    EXPECT_EQ(stack2.top(), 3);
}

TEST(StackTest, EqualityOperator) {
    Stack<int> stack1 = { 1, 2, 3 };
    Stack<int> stack2 = { 1, 2, 3 };
    Stack<int> stack3 = { 1, 2 };
    Stack<int> stack4 = { 1, 2, 4 };
    Stack<int> stack5;

    EXPECT_TRUE(stack1 == stack2);
    EXPECT_FALSE(stack1 == stack3);
    EXPECT_FALSE(stack1 == stack4);
    EXPECT_FALSE(stack1 == stack5);
    EXPECT_TRUE(stack5 == Stack<int>());
}

TEST(StackTest, InequalityOperator) {
    Stack<int> stack1 = { 1, 2, 3 };
    Stack<int> stack2 = { 1, 2, 4 };

    EXPECT_TRUE(stack1 != stack2);
    EXPECT_FALSE(stack1 != stack1);
}

TEST(StackTest, StringStack) {
    Stack<std::string> stack;

    stack.push("Hello");
    stack.push("World");
    stack.push("!");

    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), "!");

    stack.pop();
    EXPECT_EQ(stack.top(), "World");

    stack.pop();
    EXPECT_EQ(stack.top(), "Hello");
}

TEST(StackTest, DoubleStack) {
    Stack<double> stack;

    stack.push(3.14);
    stack.push(2.71);
    stack.push(1.41);

    EXPECT_DOUBLE_EQ(stack.top(), 1.41);

    stack.pop();
    EXPECT_DOUBLE_EQ(stack.top(), 2.71);
}

TEST(StackTest, LargeNumberOfElements) {
    Stack<int> stack;
    const int N = 10000;

    for (int i = 0; i < N; i++) {
        stack.push(i);
    }

    EXPECT_EQ(stack.size(), N);
    EXPECT_EQ(stack.top(), N - 1);

    for (int i = N - 1; i >= 0; i--) {
        EXPECT_EQ(stack.top(), i);
        stack.pop();
    }

    EXPECT_TRUE(stack.empty());
}

TEST(StackTest, MoveSemanticsNotSupportedButCopyWorks) {
    Stack<int> stack1 = { 1, 2, 3 };
    Stack<int> stack2 = std::move(stack1);  // Это вызовет копирование

    EXPECT_EQ(stack2.size(), 3);
    EXPECT_EQ(stack2.top(), 3);
}

TEST(StackTest, OutputOperator) {
    Stack<int> stack = { 1, 2, 3 };

    std::stringstream ss;
    ss << stack;

    std::string expected = "Stack (size: 3, capacity: ";
    // Проверяем начало строки
    EXPECT_TRUE(ss.str().find(expected) == 0);
}

TEST(StackTest, StackOfStacks) {
    Stack<Stack<int>> stack_of_stacks;

    Stack<int> stack1 = { 1, 2, 3 };
    Stack<int> stack2 = { 4, 5, 6, 7 };

    stack_of_stacks.push(stack1);
    stack_of_stacks.push(stack2);

    EXPECT_EQ(stack_of_stacks.size(), 2);
    EXPECT_EQ(stack_of_stacks.top().top(), 7);

    stack_of_stacks.pop();
    EXPECT_EQ(stack_of_stacks.top().top(), 3);
}

TEST(StackBoolTest, BoolStack) {
    Stack<bool> stack;

    stack.push(true);
    stack.push(false);
    stack.push(true);
    stack.push(false);

    EXPECT_EQ(stack.size(), 4);
    EXPECT_FALSE(stack.top());  // Последний был false

    stack.pop();
    EXPECT_TRUE(stack.top());   // Теперь верхний true

    stack.pop();
    EXPECT_FALSE(stack.top());  // Теперь верхний false

    stack.pop();
    EXPECT_TRUE(stack.top());   // Теперь верхний true

    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(StackBoolTest, BoolStackEmpty) {
    Stack<bool> stack;

    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);

    EXPECT_THROW(stack.top(), std::out_of_range);
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackBoolTest, BoolStackLarge) {
    Stack<bool> stack;
    const int N = 100;

    for (int i = 0; i < N; i++) {
        stack.push(i % 2 == 0);  // true for even, false for odd
    }

    EXPECT_EQ(stack.size(), N);

    for (int i = N - 1; i >= 0; i--) {
        EXPECT_EQ(stack.top(), (i % 2 == 0));
        stack.pop();
    }

    EXPECT_TRUE(stack.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
