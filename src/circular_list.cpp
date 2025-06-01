#include "circular_list.hpp"
#include <algorithm>

namespace cls {

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
void circular_list<T>::push_front(const T& value) {
    push_back(value);
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

// Explicit template instantiation
template class circular_list<int>;
template class circular_list<double>;
template class circular_list<std::string>;

} // namespace cls
