#include <gtest/gtest.h>
#include "List.h"

TEST(ListTest, DefaultConstructor) {
    List<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, ConstructorWithInitializerList) {
    List<int> list = { 1, 2, 3, 4, 5 };
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 5);
}

TEST(ListTest, CopyConstructor) {
    List<int> list1 = { 1, 2, 3, 4, 5 };
    List<int> list2 = list1;

    EXPECT_EQ(list1.size(), list2.size());
    EXPECT_EQ(list1.front(), list2.front());
    EXPECT_EQ(list1.back(), list2.back());

    list1.pop_front();
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list2.size(), 5);
    EXPECT_EQ(list1.front(), 2);
    EXPECT_EQ(list2.front(), 1);
}

TEST(ListTest, AssignmentOperator) {
    List<int> list1 = { 1, 2, 3 };
    List<int> list2;
    list2 = list1;

    EXPECT_EQ(list1.size(), list2.size());
    EXPECT_EQ(list1.front(), list2.front());
    EXPECT_EQ(list1.back(), list2.back());

    list1.push_back(4);
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list2.size(), 3);
}

TEST(ListTest, SelfAssignment) {
    List<int> list = { 1, 2, 3 };
    list = list;

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, PushBack) {
    List<int> list;

    list.push_back(10);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);

    list.push_back(20);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 20);

    list.push_back(30);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);
}

TEST(ListTest, PushFront) {
    List<int> list;

    list.push_front(10);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);

    list.push_front(20);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 10);

    list.push_front(30);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 30);
    EXPECT_EQ(list.back(), 10);
}

TEST(ListTest, PopFront) {
    List<int> list = { 10, 20, 30 };

    EXPECT_EQ(list.front(), 10);
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 30);

    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 30);
    EXPECT_EQ(list.back(), 30);

    list.pop_front();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, PopBack) {
    List<int> list = { 10, 20, 30 };

    EXPECT_EQ(list.back(), 30);
    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 20);

    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);

    list.pop_back();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, PopFrontEmptyList) {
    List<int> list;

    EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TEST(ListTest, PopBackEmptyList) {
    List<int> list;

    EXPECT_THROW(list.pop_back(), std::out_of_range);
}

TEST(ListTest, FrontEmptyList) {
    List<int> list;

    EXPECT_THROW(list.front(), std::out_of_range);
}

TEST(ListTest, BackEmptyList) {
    List<int> list;

    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(ListTest, ConstFrontAndBack) {
    const List<int> list = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 5);
    EXPECT_EQ(list.size(), 5);
}

TEST(ListTest, AtMethod) {
    List<int> list = { 10, 20, 30, 40, 50 };

    EXPECT_EQ(list.at(0), 10);
    EXPECT_EQ(list.at(2), 30);
    EXPECT_EQ(list.at(4), 50);

    list.at(1) = 25;
    EXPECT_EQ(list.at(1), 25);
}

TEST(ListTest, AtMethodOutOfRange) {
    List<int> list = { 1, 2, 3 };

    EXPECT_THROW(list.at(3), std::out_of_range);
    EXPECT_THROW(list.at(5), std::out_of_range);
}

TEST(ListTest, OperatorIndex) {
    List<int> list = { 100, 200, 300 };

    EXPECT_EQ(list[0], 100);
    EXPECT_EQ(list[1], 200);
    EXPECT_EQ(list[2], 300);

    list[1] = 250;
    EXPECT_EQ(list[1], 250);
    EXPECT_EQ(list[0], 100);
    EXPECT_EQ(list[2], 300);
}

TEST(ListTest, InsertAtBeginning) {
    List<int> list = { 2, 3, 4 };

    list.insert(0, 1);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
}

TEST(ListTest, InsertAtEnd) {
    List<int> list = { 1, 2, 3 };

    list.insert(3, 4);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.back(), 4);
    EXPECT_EQ(list[2], 3);
    EXPECT_EQ(list[3], 4);
}

TEST(ListTest, InsertInMiddle) {
    List<int> list = { 1, 3, 4 };

    list.insert(1, 2);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
    EXPECT_EQ(list[3], 4);
}

TEST(ListTest, InsertInvalidPosition) {
    List<int> list = { 1, 2, 3 };

    EXPECT_THROW(list.insert(10, 4), std::out_of_range);
}

TEST(ListTest, EraseAtBeginning) {
    List<int> list = { 1, 2, 3, 4 };

    list.erase(0);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 3);
    EXPECT_EQ(list[2], 4);
}

TEST(ListTest, EraseAtEnd) {
    List<int> list = { 1, 2, 3, 4 };

    list.erase(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(ListTest, EraseInMiddle) {
    List<int> list = { 1, 2, 3, 4 };

    list.erase(1);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 3);
    EXPECT_EQ(list[2], 4);
}

TEST(ListTest, EraseInvalidPosition) {
    List<int> list = { 1, 2, 3 };

    EXPECT_THROW(list.erase(3), std::out_of_range);
    EXPECT_THROW(list.erase(5), std::out_of_range);
}

TEST(ListTest, Clear) {
    List<int> list = { 1, 2, 3, 4, 5 };

    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 5);

    list.clear();

    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(ListTest, Find) {
    List<int> list = { 10, 20, 30, 40, 50 };

    EXPECT_EQ(list.find(10), 0);
    EXPECT_EQ(list.find(30), 2);
    EXPECT_EQ(list.find(50), 4);
    EXPECT_EQ(list.find(100), list.size());
}

TEST(ListTest, Contains) {
    List<int> list = { 1, 2, 3, 4, 5 };

    EXPECT_TRUE(list.contains(1));
    EXPECT_TRUE(list.contains(3));
    EXPECT_TRUE(list.contains(5));
    EXPECT_FALSE(list.contains(10));
    EXPECT_FALSE(list.contains(0));
}

TEST(ListTest, Reverse) {
    List<int> list = { 1, 2, 3, 4, 5 };

    list.reverse();

    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list.front(), 5);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list[0], 5);
    EXPECT_EQ(list[1], 4);
    EXPECT_EQ(list[2], 3);
    EXPECT_EQ(list[3], 2);
    EXPECT_EQ(list[4], 1);
}

TEST(ListTest, ReverseEmpty) {
    List<int> list;

    list.reverse();
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, ReverseSingleElement) {
    List<int> list = { 42 };

    list.reverse();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 42);
    EXPECT_EQ(list.back(), 42);
}

TEST(ListTest, Swap) {
    List<int> list1 = { 1, 2, 3 };
    List<int> list2 = { 4, 5, 6, 7 };

    size_t size1 = list1.size();
    size_t size2 = list2.size();

    list1.swap(list2);

    EXPECT_EQ(list1.size(), size2);
    EXPECT_EQ(list2.size(), size1);
    EXPECT_EQ(list1.front(), 4);
    EXPECT_EQ(list1.back(), 7);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 3);
}

TEST(ListTest, EqualityOperator) {
    List<int> list1 = { 1, 2, 3, 4, 5 };
    List<int> list2 = { 1, 2, 3, 4, 5 };
    List<int> list3 = { 1, 2, 3 };
    List<int> list4 = { 1, 2, 4, 5, 6 };
    List<int> list5;

    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 == list3);
    EXPECT_FALSE(list1 == list4);
    EXPECT_FALSE(list1 == list5);
    EXPECT_TRUE(list5 == List<int>());
}

TEST(ListTest, InequalityOperator) {
    List<int> list1 = { 1, 2, 3 };
    List<int> list2 = { 1, 2, 4 };

    EXPECT_TRUE(list1 != list2);
    EXPECT_FALSE(list1 != list1);
}

TEST(ListTest, Iterator) {
    List<int> list = { 1, 2, 3, 4, 5 };

    int expected = 1;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected);
        expected++;
    }

    expected = 1;
    for (int value : list) {
        EXPECT_EQ(value, expected);
        expected++;
    }
}

TEST(ListTest, IteratorEmptyList) {
    List<int> list;

    EXPECT_TRUE(list.begin() == list.end());

    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

TEST(ListTest, IteratorModification) {
    List<int> list = { 1, 2, 3 };

    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = *it * 2;
    }

    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 4);
    EXPECT_EQ(list[2], 6);
}

TEST(ListTest, ManyOperations) {
    List<int> list;
    const int N = 1000;

    for (int i = 0; i < N; i++) {
        list.push_back(i);
    }

    EXPECT_EQ(list.size(), N);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), N - 1);

    for (int i = 0; i < N / 2; i++) {
        list.pop_front();
    }

    EXPECT_EQ(list.size(), N / 2);
    EXPECT_EQ(list.front(), N / 2);

    list.clear();
    EXPECT_TRUE(list.empty());

    for (int i = 0; i < N; i++) {
        list.push_front(i);
    }

    EXPECT_EQ(list.size(), N);
    EXPECT_EQ(list.front(), N - 1);
    EXPECT_EQ(list.back(), 0);
}

TEST(ListTest, CharList) {
    List<char> list;

    list.push_back('a');
    list.push_back('b');
    list.push_back('c');

    EXPECT_EQ(list.front(), 'a');
    EXPECT_EQ(list.back(), 'c');

    list.pop_front();
    EXPECT_EQ(list.front(), 'b');
}

TEST(ListTest, DoubleList) {
    List<double> list;

    list.push_back(3.14);
    list.push_back(2.71);
    list.push_back(1.41);

    EXPECT_DOUBLE_EQ(list.front(), 3.14);
    EXPECT_DOUBLE_EQ(list.back(), 1.41);

    list.pop_front();
    EXPECT_DOUBLE_EQ(list.front(), 2.71);
}

TEST(ListTest, OutputOperator) {
    List<int> list = { 1, 2, 3 };

    std::stringstream ss;
    ss << list;

    std::string result = ss.str();
    EXPECT_TRUE(result.find("List (size: 3") != std::string::npos);
    EXPECT_TRUE(result.find("1 -> 2 -> 3") != std::string::npos);
}

TEST(ListTest, ComplexOperations) {
    List<int> list;

    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }

    list.insert(5, 99);
    EXPECT_EQ(list[5], 99);

    list.erase(3);
    EXPECT_EQ(list[3], 4);

    list.reverse();
    EXPECT_EQ(list.front(), 9);
    EXPECT_EQ(list.back(), 0);

    EXPECT_TRUE(list.contains(99));
    EXPECT_FALSE(list.contains(100));
}


