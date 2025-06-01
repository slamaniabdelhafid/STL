#pragma once
#include <iterator>
#include <memory>
#include <stdexcept>
#include <initializer_list>

namespace cls {

template <typename T>
class circular_list {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        Node(T&& value) : data(std::move(value)), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    size_t m_size;

public:
    class iterator;
    class const_iterator;

    circular_list() : head(nullptr), m_size(0) {}
    circular_list(std::initializer_list<T> init) : circular_list() {
        for (const auto& item : init) {
            push_back(item);
        }
    }
    ~circular_list() { clear(); }

    // Iterators
    iterator begin() noexcept { return iterator(head); }
    const_iterator begin() const noexcept { return const_iterator(head); }
    const_iterator cbegin() const noexcept { return begin(); }
    iterator end() noexcept { return iterator(nullptr); }
    const_iterator end() const noexcept { return const_iterator(nullptr); }
    const_iterator cend() const noexcept { return end(); }

    // Capacity
    bool empty() const noexcept { return m_size == 0; }
    size_t size() const noexcept { return m_size; }

    // Element access
    T& front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }
    
    const T& front() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }
    
    T& back() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->prev->data;
    }
    
    const T& back() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head->prev->data;
    }

    // Modifiers
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void clear() noexcept;

    // Iterator classes
    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node* ptr = nullptr) : current(ptr) {}

        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }

        iterator& operator++() {
            current = current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--() {
            current = current->prev;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        Node* current;
        friend class circular_list<T>;
    };

    class const_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator(Node* ptr = nullptr) : current(ptr) {}

        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }

        const_iterator& operator++() {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_iterator& operator--() {
            current = current->prev;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const { return current == other.current; }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }

    private:
        Node* current;
        friend class circular_list<T>;
    };
};

} // namespace cls
