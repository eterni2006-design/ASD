#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int list_size;

    // Вспомогательная функция для очистки списка
    void clear_list() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        list_size = 0;
    }

    // Вспомогательная функция для копирования списка
    void copy_list(const List& other) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

public:
    // Конструктор по умолчанию
    List() : head(nullptr), tail(nullptr), list_size(0) {}

    // Конструктор со списком инициализации
    List(std::initializer_list<T> init_list) : head(nullptr), tail(nullptr), list_size(0) {
        for (const auto& item : init_list) {
            push_back(item);
        }
    }

    // Копирующий конструктор
    List(const List& other) : head(nullptr), tail(nullptr), list_size(0) {
        copy_list(other);
    }

    // Деструктор
    ~List() {
        clear_list();
    }

    // Добавление элемента в начало списка
    void push_front(const T& value) {
        Node* new_node = new Node(value);

        if (empty()) {
            head = tail = new_node;
        }
        else {
            new_node->next = head;
            head = new_node;
        }
        list_size++;
    }

    // Добавление элемента в конец списка
    void push_back(const T& value) {
        Node* new_node = new Node(value);

        if (empty()) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node;
        }
        list_size++;
    }

    // Вставка элемента по позиции
    void insert(int position, const T& value) {
        if (position > list_size) {
            throw std::out_of_range("Position out of range");
        }

        if (position == 0) {
            push_front(value);
        }
        else if (position == list_size) {
            push_back(value);
        }
        else {
            Node* new_node = new Node(value);
            Node* current = head;

            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }

            new_node->next = current->next;
            current->next = new_node;
            list_size++;
        }
    }

    // Удаление элемента из начала списка
    void pop_front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        Node* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        list_size--;
    }

    // Удаление элемента из конца списка
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }

            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        list_size--;
    }

    // Удаление элемента по позиции
    void erase(int position) {
        if (position >= list_size) {
            throw std::out_of_range("Position out of range");
        }

        if (position == 0) {
            pop_front();
        }
        else if (position == list_size - 1) {
            pop_back();
        }
        else {
            Node* current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }

            Node* to_delete = current->next;
            current->next = to_delete->next;

            delete to_delete;
            list_size--;
        }
    }

    // Получение элемента по индексу
    T& at(int index) {
        if (index >= list_size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T& at(int index) const {
        if (index >= list_size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Оператор [] для доступа по индексу
    T& operator[](int index) {
        return at(index);
    }

    const T& operator[](int index) const {
        return at(index);
    }

    // Проверка на пустоту
    bool empty() const {
        return list_size == 0;
    }

    // Размер списка
    int size() const {
        return list_size;
    }

    // Очистка списка
    void clear() {
        clear_list();
    }

    // Поиск элемента
    int find(const T& value) const {
        Node* current = head;
        int index = 0;

        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return list_size;
    }

    // Оператор присваивания
    List& operator=(const List& other) {
        if (this != &other) {
            clear_list();
            copy_list(other);
        }
        return *this;
    }

    // Оператор сравнения
    bool operator==(const List& other) const {
        if (list_size != other.list_size) {
            return false;
        }

        Node* current1 = head;
        Node* current2 = other.head;

        while (current1 != nullptr) {
            if (current1->data != current2->data) {
                return false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return true;
    }

    bool operator!=(const List& other) const {
        return !(*this == other);
    }

    // Класс итератора
    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    // Методы для итераторов
    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    // Вывод списка
    friend std::ostream& operator<<(std::ostream& os, const List<T>& list) {
        os << "List (size: " << list.list_size << "): [";
        Node* current = list.head;
        while (current != nullptr) {
            os << current->data;
            if (current->next != nullptr) {
                os << ", ";
            }
            current = current->next;
        }
        os << "]";
        return os;
    }
};




template <typename T>
class Stack {
private:
    List<T> list;

public:
    Stack() {}

    Stack(std::initializer_list<T> init_list) {
        for (const auto& item : init_list) {
            push(item);
        }
    }

    Stack(const Stack& other) : list(other.list) {}

    void push(const T& value) {
        list.push_front(value);
    }


    void pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        list.pop_front();
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return list.at(0);
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return list.at(0);
    }

    bool empty() const {
        return list.empty();
    }

    int size() const {
        return list.size();
    }

    void clear() {
        list.clear();
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    bool operator==(const Stack& other) const {
        return list == other.list;
    }

    bool operator!=(const Stack& other) const {
        return list != other.list;
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
        os << "Stack (size: " << stack.size() << "): [";
        for (int i = 0; i < stack.size(); ++i) {
            if (i > 0) os << ", ";
            os << stack.list[i];
        }
        os << "]";
        return os;
    }
};



template <typename T>
class Queue {
private:
    List<T> list;

public:
    Queue() {}

    Queue(std::initializer_list<T> init_list) {
        for (const auto& item : init_list) {
            push(item);
        }
    }

    Queue(const Queue& other) : list(other.list) {}

    void push(const T& value) {
        list.push_back(value);
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        list.pop_front();
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return list.at(0);
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return list.at(0);
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return list.at(list.size() - 1);
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return list.at(list.size() - 1);
    }

    bool empty() const {
        return list.empty();
    }

    int size() const {
        return list.size();
    }

    void clear() {
        list.clear();
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    bool operator==(const Queue& other) const {
        return list == other.list;
    }

    bool operator!=(const Queue& other) const {
        return list != other.list;
    }

    friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
        os << "Queue (size: " << queue.size() << "): [";
        if (!queue.empty()) {
            // Вывод от начала к концу
            for (int i = 0; i < queue.list.size(); ++i) {
                if (i > 0) os << ", ";
                os << queue.list[i];
            }
        }
        os << "]";
        return os;
    }
};






int main() {
    // Тестирование очереди
    Queue<int> q1;
    Queue<int> q2 = { 10, 20, 30, 40, 50 };

    std::cout << "q2: " << q2 << std::endl;
    std::cout << "Front: " << q2.front() << std::endl;  // 10
    std::cout << "Back: " << q2.back() << std::endl;    // 50

    // Добавление элементов
    q2.push(60);
    std::cout << "After push(60): " << q2 << std::endl;
    std::cout << "New back: " << q2.back() << std::endl;  // 60

    // Удаление элементов
    q2.pop();
    std::cout << "After pop(): " << q2 << std::endl;
    std::cout << "New front: " << q2.front() << std::endl;  // 20

    // Копирование
    Queue<int> q3 = q2;
    std::cout << "q3 (copy of q2): " << q3 << std::endl;

    // Проверка равенства
    std::cout << "q2 == q3: " << (q2 == q3) << std::endl;  // true


    // Очистка
    q3.clear();
    std::cout << "q3 after clear: " << q3 << std::endl;
    std::cout << "q3 empty: " << q3.empty() << std::endl;  // true

    return 0;
}
