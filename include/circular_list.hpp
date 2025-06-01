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
    // Iterator classes
    class iterator;
    class const_iterator;

    // Constructors
    circular_list();
    circular_list(std::initializer_list<T> init);
    circular_list(const circular_list& other);
    circular_list(circular_list&& other) noexcept;
    ~circular_list();

    // Assignment operators
    circular_list& operator=(const circular_list& other);
    circular_list& operator=(circular_list&& other) noexcept;

    // Element access
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    // Iterators
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_t size() const noexcept;

    // Modifiers
    void push_back(const T& value);
    void push_back(T&& value);
    void push_front(const T& value);
    void push_front(T&& value);
    void pop_back();
    void pop_front();
    void clear() noexcept;
    void swap(circular_list& other) noexcept;

    // Operations
    void merge(circular_list& other);
    void reverse() noexcept;

private:
    void copy_nodes(const circular_list& other);
};

// Iterator implementation
template <typename T>
class circular_list<T>::iterator {
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

template <typename T>
class circular_list<T>::const_iterator {
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

// Non-member functions
template <typename T>
void swap(circular_list<T>& lhs, circular_list<T>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T>
bool operator==(const circular_list<T>& lhs, const circular_list<T>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

} // namespace cls
