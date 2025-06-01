#include "circular_list.hpp"
#include <algorithm>

namespace cls {

// Constructor implementations
template <typename T>
circular_list<T>::circular_list() : head(nullptr), m_size(0) {}

template <typename T>
circular_list<T>::circular_list(std::initializer_list<T> init) : circular_list() {
    for (const auto& item : init) {
        push_back(item);
    }
}

template <typename T>
circular_list<T>::circular_list(const circular_list& other) : circular_list() {
    copy_nodes(other);
}

template <typename T>
circular_list<T>::circular_list(circular_list&& other) noexcept 
    : head(other.head), m_size(other.m_size) {
    other.head = nullptr;
    other.m_size = 0;
}

template <typename T>
circular_list<T>::~circular_list() {
    clear();
}

// Assignment operators
template <typename T>
circular_list<T>& circular_list<T>::operator=(const circular_list& other) {
    if (this != &other) {
        clear();
        copy_nodes(other);
    }
    return *this;
}

template <typename T>
circular_list<T>& circular_list<T>::operator=(circular_list&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        m_size = other.m_size;
        other.head = nullptr;
        other.m_size = 0;
    }
    return *this;
}

// Element access
template <typename T>
T& circular_list<T>::front() {
    if (empty()) throw std::out_of_range("List is empty");
    return head->next->data;
}

template <typename T>
const T& circular_list<T>::front() const {
    if (empty()) throw std::out_of_range("List is empty");
    return head->next->data;
}

template <typename T>
T& circular_list<T>::back() {
    if (empty()) throw std::out_of_range("List is empty");
    return head->data;
}

template <typename T>
const T& circular_list<T>::back() const {
    if (empty()) throw std::out_of_range("List is empty");
    return head->data;
}

// Iterators
template <typename T>
typename circular_list<T>::iterator circular_list<T>::begin() noexcept {
    return iterator(head ? head->next : nullptr);
}

template <typename T>
typename circular_list<T>::const_iterator circular_list<T>::begin() const noexcept {
    return const_iterator(head ? head->next : nullptr);
}

template <typename T>
typename circular_list<T>::const_iterator circular_list<T>::cbegin() const noexcept {
    return begin();
}

template <typename T>
typename circular_list<T>::iterator circular_list<T>::end() noexcept {
    return iterator(head);
}

template <typename T>
typename circular_list<T>::const_iterator circular_list<T>::end() const noexcept {
    return const_iterator(head);
}

template <typename T>
typename circular_list<T>::const_iterator circular_list<T>::cend() const noexcept {
    return end();
}

// Capacity
template <typename T>
bool circular_list<T>::empty() const noexcept {
    return m_size == 0;
}

template <typename T>
size_t circular_list<T>::size() const noexcept {
    return m_size;
}

// Modifiers
template <typename T>
void circular_list<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
    }
    m_size++;
}

template <typename T>
void circular_list<T>::push_back(T&& value) {
    Node* newNode = new Node(std::move(value));
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
    }
    m_size++;
}

template <typename T>
void circular_list<T>::push_front(const T& value) {
    push_back(value);
    head = head->prev;
}

template <typename T>
void circular_list<T>::push_front(T&& value) {
    push_back(std::move(value));
    head = head->prev;
}

template <typename T>
void circular_list<T>::pop_back() {
    if (empty()) throw std::out_of_range("List is empty");
    
    if (m_size == 1) {
        delete head;
        head = nullptr;
    } else {
        Node* toDelete = head->prev;
        head->prev = toDelete->prev;
        toDelete->prev->next = head;
        delete toDelete;
    }
    m_size--;
}

template <typename T>
void circular_list<T>::pop_front() {
    if (empty()) throw std::out_of_range("List is empty");
    
    if (m_size == 1) {
        delete head;
        head = nullptr;
    } else {
        Node* newHead = head->next;
        newHead->prev = head->prev;
        head->prev->next = newHead;
        delete head;
        head = newHead;
    }
    m_size--;
}

template <typename T>
void circular_list<T>::clear() noexcept {
    while (!empty()) {
        pop_back();
    }
}

template <typename T>
void circular_list<T>::swap(circular_list& other) noexcept {
    std::swap(head, other.head);
    std::swap(m_size, other.m_size);
}

// Operations
template <typename T>
void circular_list<T>::merge(circular_list& other) {
    if (this == &other) return;
    
    if (empty()) {
        *this = std::move(other);
        return;
    }
    
    if (other.empty()) {
        return;
    }
    
    head->prev->next = other.head->next;
    other.head->next->prev = head->prev;
    other.head->prev->next = head;
    head->prev = other.head->prev;
    
    m_size += other.m_size;
    other.head = nullptr;
    other.m_size = 0;
}

template <typename T>
void circular_list<T>::reverse() noexcept {
    if (m_size < 2) return;
    
    Node* current = head;
    do {
        std::swap(current->next, current->prev);
        current = current->prev;
    } while (current != head);
    
    head = head->next;
}

// Private methods
template <typename T>
void circular_list<T>::copy_nodes(const circular_list& other) {
    for (const auto& item : other) {
        push_back(item);
    }
}

// Explicit template instantiation
template class circular_list<int>;
template class circular_list<double>;

} // namespace cls
