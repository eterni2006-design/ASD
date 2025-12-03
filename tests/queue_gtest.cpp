#include <gtest/gtest.h>
#include "queue.h"

TEST(QueueTest, DefaultConstructor) {
    Queue<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.get_capacity(), 0);
}

TEST(QueueTest, ConstructorWithInitialCapacity) {
    Queue<int> queue(10);
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_GE(queue.get_capacity(), 10);
}

TEST(QueueTest, ConstructorWithInitializerList) {
    Queue<int> queue = { 1, 2, 3, 4, 5 };
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 5);
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> queue1 = { 1, 2, 3, 4, 5 };
    Queue<int> queue2 = queue1;

    EXPECT_EQ(queue1.size(), queue2.size());
    EXPECT_EQ(queue1.front(), queue2.front());
    EXPECT_EQ(queue1.back(), queue2.back());

    queue1.pop();
    EXPECT_EQ(queue1.size(), 4);
    EXPECT_EQ(queue2.size(), 5);
    EXPECT_EQ(queue1.front(), 2);
    EXPECT_EQ(queue2.front(), 1);
}

TEST(QueueTest, AssignmentOperator) {
    Queue<int> queue1 = { 1, 2, 3 };
    Queue<int> queue2;
    queue2 = queue1;

    EXPECT_EQ(queue1.size(), queue2.size());
    EXPECT_EQ(queue1.front(), queue2.front());
    EXPECT_EQ(queue1.back(), queue2.back());

    queue1.push(4);
    EXPECT_EQ(queue1.size(), 4);
    EXPECT_EQ(queue2.size(), 3);
}

TEST(QueueTest, SelfAssignment) {
    Queue<int> queue = { 1, 2, 3 };
    queue = queue;

    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);
}

TEST(QueueTest, PushAndFront) {
    Queue<int> queue;

    queue.push(10);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 10);

    queue.push(20);
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 20);

    queue.push(30);
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 30);
}

TEST(QueueTest, Pop) {
    Queue<int> queue = { 10, 20, 30 };

    EXPECT_EQ(queue.front(), 10);
    queue.pop();
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 20);
    EXPECT_EQ(queue.back(), 30);

    queue.pop();
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 30);
    EXPECT_EQ(queue.back(), 30);

    queue.pop();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, PopEmptyQueue) {
    Queue<int> queue;

    EXPECT_THROW(queue.pop(), std::out_of_range);
}

TEST(QueueTest, FrontEmptyQueue) {
    Queue<int> queue;

    EXPECT_THROW(queue.front(), std::out_of_range);
}

TEST(QueueTest, BackEmptyQueue) {
    Queue<int> queue;

    EXPECT_THROW(queue.back(), std::out_of_range);
}

TEST(QueueTest, ConstFrontAndBack) {
    const Queue<int> queue = { 1, 2, 3 };

    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);
    EXPECT_EQ(queue.size(), 3);
}

TEST(QueueTest, Clear) {
    Queue<int> queue = { 1, 2, 3, 4, 5 };

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 5);

    queue.clear();

    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_THROW(queue.front(), std::out_of_range);
    EXPECT_THROW(queue.back(), std::out_of_range);
}

TEST(QueueTest, Reserve) {
    Queue<int> queue;

    EXPECT_EQ(queue.get_capacity(), 0);

    queue.reserve(20);
    EXPECT_GE(queue.get_capacity(), 20);

    size_t old_capacity = queue.get_capacity();
    for (int i = 0; i < 15; i++) {
        queue.push(i);
    }
    EXPECT_EQ(queue.get_capacity(), old_capacity);
}

TEST(QueueTest, AutoResize) {
    Queue<int> queue;

    for (int i = 0; i < 100; i++) {
        queue.push(i);
    }

    EXPECT_EQ(queue.size(), 100);
    EXPECT_GE(queue.get_capacity(), 100);
    EXPECT_EQ(queue.front(), 0);
    EXPECT_EQ(queue.back(), 99);
}

TEST(QueueTest, CircularBuffer) {
    Queue<int> queue(3);

    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);

    queue.pop();
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.back(), 3);

    queue.push(4);
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.back(), 4);

    queue.pop();
    EXPECT_EQ(queue.front(), 3);
    EXPECT_EQ(queue.back(), 4);

    queue.push(5);
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 3);
    EXPECT_EQ(queue.back(), 5);
}

TEST(QueueTest, Swap) {
    Queue<int> queue1 = { 1, 2, 3 };
    Queue<int> queue2 = { 4, 5, 6, 7 };

    size_t size1 = queue1.size();
    size_t size2 = queue2.size();

    queue1.swap(queue2);

    EXPECT_EQ(queue1.size(), size2);
    EXPECT_EQ(queue2.size(), size1);
    EXPECT_EQ(queue1.front(), 4);
    EXPECT_EQ(queue1.back(), 7);
    EXPECT_EQ(queue2.front(), 1);
    EXPECT_EQ(queue2.back(), 3);
}

TEST(QueueTest, EqualityOperator) {
    Queue<int> queue1 = { 1, 2, 3 };
    Queue<int> queue2 = { 1, 2, 3 };
    Queue<int> queue3 = { 1, 2 };
    Queue<int> queue4 = { 1, 2, 4 };
    Queue<int> queue5;

    EXPECT_TRUE(queue1 == queue2);
    EXPECT_FALSE(queue1 == queue3);
    EXPECT_FALSE(queue1 == queue4);
    EXPECT_FALSE(queue1 == queue5);
    EXPECT_TRUE(queue5 == Queue<int>());
}

TEST(QueueTest, InequalityOperator) {
    Queue<int> queue1 = { 1, 2, 3 };
    Queue<int> queue2 = { 1, 2, 4 };

    EXPECT_TRUE(queue1 != queue2);
    EXPECT_FALSE(queue1 != queue1);
}

TEST(QueueTest, ManyPushPopOperations) {
    Queue<int> queue;

    for (int i = 0; i < 1000; i++) {
        queue.push(i);
    }

    EXPECT_EQ(queue.size(), 1000);

    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(queue.front(), i);
        queue.pop();
    }

    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, QueueOfChars) {
    Queue<char> queue;

    queue.push('a');
    queue.push('b');
    queue.push('c');

    EXPECT_EQ(queue.front(), 'a');
    EXPECT_EQ(queue.back(), 'c');

    queue.pop();
    EXPECT_EQ(queue.front(), 'b');
}

TEST(QueueTest, QueueOfDoubles) {
    Queue<double> queue;

    queue.push(3.14);
    queue.push(2.71);
    queue.push(1.41);

    EXPECT_DOUBLE_EQ(queue.front(), 3.14);
    EXPECT_DOUBLE_EQ(queue.back(), 1.41);

    queue.pop();
    EXPECT_DOUBLE_EQ(queue.front(), 2.71);
}

TEST(QueueTest, LargeQueueWithResizing) {
    Queue<int> queue;
    const int N = 10000;

    for (int i = 0; i < N; i++) {
        queue.push(i * 2);
    }

    EXPECT_EQ(queue.size(), N);
    EXPECT_EQ(queue.front(), 0);
    EXPECT_EQ(queue.back(), (N - 1) * 2);

    for (int i = 0; i < N; i++) {
        EXPECT_EQ(queue.front(), i * 2);
        queue.pop();
    }

    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, OutputOperator) {
    Queue<int> queue = { 1, 2, 3 };

    std::stringstream ss;
    ss << queue;

    std::string result = ss.str();
    EXPECT_TRUE(result.find("Queue (size: 3") != std::string::npos);
    EXPECT_TRUE(result.find("1, 2, 3") != std::string::npos);
}

TEST(QueueTest, QueueAfterClearAndReuse) {
    Queue<int> queue;

    for (int i = 0; i < 10; i++) {
        queue.push(i);
    }

    EXPECT_EQ(queue.size(), 10);
    queue.clear();
    EXPECT_TRUE(queue.empty());

    for (int i = 0; i < 5; i++) {
        queue.push(i * 10);
    }

    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.front(), 0);
    EXPECT_EQ(queue.back(), 40);
}

TEST(QueueTest, CircularBufferComplex) {
    Queue<int> queue(5);

    for (int i = 1; i <= 5; i++) {
        queue.push(i);
    }

    for (int i = 1; i <= 3; i++) {
        queue.pop();
    }

    for (int i = 6; i <= 8; i++) {
        queue.push(i);
    }

    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.front(), 4);
    EXPECT_EQ(queue.back(), 8);
}

