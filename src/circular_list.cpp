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
void circular_list<T>::merge(circular_list& other) {
    if (this == &other) return;
    
    if (empty()) {
        head = other.head;
        m_size = other.m_size;
    } else if (!other.empty()) {
        Node* this_last = head->prev;
        Node* other_last = other.head->prev;
        
        this_last->next = other.head;
        other.head->prev = this_last;
        
        head->prev = other_last;
        other_last->next = head;
        
        m_size += other.m_size;
    }
    
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

template class circular_list<int>;
template class circular_list<double>;
template class circular_list<std::string>;

} // namespace cls
