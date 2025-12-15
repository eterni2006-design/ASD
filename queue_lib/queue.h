#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Queue {
private:
    T* data;
    size_t capacity;
    size_t front_index;
    size_t back_index;
    size_t queue_size;

    // Увеличение емкости
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < queue_size; i++) {
            size_t old_index = (front_index + i) % capacity;
            new_data[i] = data[old_index];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
        front_index = 0;
        back_index = queue_size;
    }

    // Проверка необходимости увеличения емкости
    void check_capacity() {
        if (queue_size >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
    }

public:
    // Конструктор по умолчанию
    Queue() : data(nullptr), capacity(0), front_index(0), back_index(0), queue_size(0) {}

    // Конструктор с начальной емкостью
    explicit Queue(size_t initial_capacity) :
        capacity(initial_capacity),
        front_index(0),
        back_index(0),
        queue_size(0)
    {
        if (initial_capacity > 0) {
            data = new T[initial_capacity];
        }
        else {
            data = nullptr;
        }
    }

    // Конструктор со списком инициализации
    Queue(std::initializer_list<T> init_list) :
        capacity(init_list.size()),
        front_index(0),
        back_index(0),
        queue_size(0)
    {
        if (capacity > 0) {
            data = new T[capacity];
            for (const auto& item : init_list) {
                push(item);
            }
        }
        else {
            data = nullptr;
        }
    }

    // Копирующий конструктор
    Queue(const Queue& other) :
        capacity(other.capacity),
        front_index(0),
        back_index(other.queue_size),
        queue_size(other.queue_size)
    {
        if (capacity > 0) {
            data = new T[capacity];
            for (size_t i = 0; i < queue_size; i++) {
                size_t other_index = (other.front_index + i) % other.capacity;
                data[i] = other.data[other_index];
            }
        }
        else {
            data = nullptr;
        }
    }

    // Деструктор
    ~Queue() {
        delete[] data;
    }

    // Добавление элемента в конец очереди
    void push(const T& value) {
        check_capacity();

        data[back_index] = value;
        back_index = (back_index + 1) % capacity;
        queue_size++;
    }

    // Удаление элемента из начала очереди
    void pop() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }

        front_index = (front_index + 1) % capacity;
        queue_size--;

        if (empty()) {
            front_index = 0;
            back_index = 0;
        }
    }

    // Получение первого элемента
    T& front() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data[front_index];
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data[front_index];
    }

    // Получение последнего элемента
    T& back() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        size_t last_index = (back_index == 0) ? capacity - 1 : back_index - 1;
        return data[last_index];
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        size_t last_index = (back_index == 0) ? capacity - 1 : back_index - 1;
        return data[last_index];
    }

    // Проверка на пустоту
    bool empty() const {
        return queue_size == 0;
    }

    // Размер очереди
    size_t size() const {
        return queue_size;
    }

    // Емкость очереди
    size_t get_capacity() const {
        return capacity;
    }

    // Очистка очереди
    void clear() {
        front_index = 0;
        back_index = 0;
        queue_size = 0;
    }

    // Изменение емкости
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            resize(new_capacity);
        }
    }

    // Обмен содержимого с другой очередью
    void swap(Queue& other) {
        std::swap(data, other.data);
        std::swap(capacity, other.capacity);
        std::swap(front_index, other.front_index);
        std::swap(back_index, other.back_index);
        std::swap(queue_size, other.queue_size);
    }

    // Оператор присваивания
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            Queue temp(other);
            swap(temp);
        }
        return *this;
    }

    // Оператор сравнения
    bool operator==(const Queue& other) const {
        if (queue_size != other.queue_size) {
            return false;
        }

        for (size_t i = 0; i < queue_size; i++) {
            size_t this_index = (front_index + i) % capacity;
            size_t other_index = (other.front_index + i) % other.capacity;

            if (data[this_index] != other.data[other_index]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Queue& other) const {
        return !(*this == other);
    }

    // Вывод очереди
    friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
        os << "Queue (size: " << queue.size() << ", capacity: " << queue.get_capacity() << "): [";
        for (size_t i = 0; i < queue.queue_size; i++) {
            size_t index = (queue.front_index + i) % queue.capacity;
            os << queue.data[index];
            if (i != queue.queue_size - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

