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
    size_t list_size;

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

    // Оператор присваивания
    List& operator=(const List& other) {
        if (this != &other) {
            clear_list();
            copy_list(other);
        }
        return *this;
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
    void insert(size_t position, const T& value) {
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

            for (size_t i = 0; i < position - 1; i++) {
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
    void erase(size_t position) {
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
            for (size_t i = 0; i < position - 1; i++) {
                current = current->next;
            }

            Node* to_delete = current->next;
            current->next = to_delete->next;

            delete to_delete;
            list_size--;
        }
    }

    // Получение первого элемента
    T& front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    // Получение последнего элемента
    T& back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    // Получение элемента по индексу
    T& at(size_t index) {
        if (index >= list_size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T& at(size_t index) const {
        if (index >= list_size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Оператор [] для доступа по индексу
    T& operator[](size_t index) {
        return at(index);
    }

    const T& operator[](size_t index) const {
        return at(index);
    }

    // Проверка на пустоту
    bool empty() const {
        return list_size == 0;
    }

    // Размер списка
    size_t size() const {
        return list_size;
    }

    // Очистка списка
    void clear() {
        clear_list();
    }

    // Поиск элемента
    size_t find(const T& value) const {
        Node* current = head;
        size_t index = 0;

        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return list_size; // Возвращаем size если не нашли
    }

    // Проверка наличия элемента
    bool contains(const T& value) const {
        return find(value) != list_size;
    }

    // Реверс списка
    void reverse() {
        if (empty() || head == tail) {
            return;
        }

        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        tail = head;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }

    // Обмен содержимого с другим списком
    void swap(List& other) {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(list_size, other.list_size);
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
                os << " -> ";
            }
            current = current->next;
        }
        os << "]";
        return os;
    }
};

