#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Stack {
private:
    T* data;
    size_t capacity;
    size_t top_index;

    // Увеличение емкости
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];

        // Копируем существующие элементы
        for (size_t i = 0; i < top_index; i++) {
            new_data[i] = data[i];
        }

        // Освобождаем старую память
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    // Проверка необходимости увеличения емкости
    void check_capacity() {
        if (top_index >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
    }

public:
    // Конструктор по умолчанию
    Stack() : data(nullptr), capacity(0), top_index(0) {}

    // Конструктор с начальной емкостью
    explicit Stack(size_t initial_capacity) : capacity(initial_capacity), top_index(0) {
        if (initial_capacity > 0) {
            data = new T[initial_capacity];
        }
        else {
            data = nullptr;
        }
    }

    // Конструктор со списком инициализации
    Stack(std::initializer_list<T> init_list) : capacity(init_list.size()), top_index(init_list.size()) {
        if (capacity > 0) {
            data = new T[capacity];
            size_t i = 0;
            for (const auto& item : init_list) {
                data[i++] = item;
            }
        }
        else {
            data = nullptr;
        }
    }

    // Копирующий конструктор
    Stack(const Stack& other) : capacity(other.capacity), top_index(other.top_index) {
        if (capacity > 0) {
            data = new T[capacity];
            for (size_t i = 0; i < top_index; i++) {
                data[i] = other.data[i];
            }
        }
        else {
            data = nullptr;
        }
    }

    // Оператор присваивания
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            // Освобождаем старую память
            delete[] data;

            // Копируем данные
            capacity = other.capacity;
            top_index = other.top_index;

            if (capacity > 0) {
                data = new T[capacity];
                for (size_t i = 0; i < top_index; i++) {
                    data[i] = other.data[i];
                }
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    // Деструктор
    ~Stack() {
        delete[] data;
    }

    // Добавление элемента на вершину стека
    void push(const T& value) {
        check_capacity();
        data[top_index++] = value;
    }

    // Удаление элемента с вершины стека
    void pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        top_index--;
    }

    // Получение элемента с вершины стека
    T& top() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data[top_index - 1];
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data[top_index - 1];
    }

    // Проверка на пустоту
    bool empty() const {
        return top_index == 0;
    }

    // Размер стека
    size_t size() const {
        return top_index;
    }

    // Емкость стека
    size_t get_capacity() const {
        return capacity;
    }

    // Очистка стека
    void clear() {
        top_index = 0;
    }

    // Изменение емкости
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            resize(new_capacity);
        }
    }

    // Обмен содержимого с другим стеком
    void swap(Stack& other) {
        std::swap(data, other.data);
        std::swap(capacity, other.capacity);
        std::swap(top_index, other.top_index);
    }

    // Оператор сравнения
    bool operator==(const Stack& other) const {
        if (top_index != other.top_index) {
            return false;
        }

        for (size_t i = 0; i < top_index; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Stack& other) const {
        return !(*this == other);
    }

    // Вывод стека
    friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
        os << "Stack (size: " << stack.size() << ", capacity: " << stack.get_capacity() << "): [";
        for (size_t i = 0; i < stack.top_index; i++) {
            os << stack.data[i];
            if (i != stack.top_index - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

