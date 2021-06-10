#ifndef LAB2_LINKEDLIST_H
#define LAB2_LINKEDLIST_H

#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class LinkedList {
private:
    class Node;
    int size;
    Node *head;

    class Node {
    public:
        T data;
        Node *next;

        Node(T data, Node *next = nullptr) {
            this->data = data;
            this->next = next;
        }
    };

public:

    LinkedList() {
        this->size = 0;
        this->head = nullptr;
    }

    LinkedList(T *arr, int size) {
        if (arr == nullptr)
            throw invalid_argument("non-existent array");
        if (size < 0)
            throw out_of_range("incorrect size");
        this->head = new Node(arr[0]);
        this->size = size;
        Node *current = this->head;
        for (int i = 1; i < size; i++) {
            current->next = new Node(arr[i]);
            current = current->next;
        }
    }

    LinkedList(const LinkedList<T> &otherList) {
        if (otherList.head) {
            this->size = otherList.size;
            this->head = new Node(otherList.head->data);
            Node *current1 = this->head;
            Node *current2 = otherList.head;
            while (current2->next != nullptr) {
                current1->next = new Node(current2->next->data);
                current1 = current1->next;
                current2 = current2->next;
            }
        } else {
            this->size = 0;
            this->head = nullptr;
        }
    }

    LinkedList<T> &operator = (const LinkedList<T> &otherList) {
        this->~LinkedList();
        if (otherList.head) {
            this->size = otherList.size;
            this->head = new Node(otherList.head->data);
            Node *current1 = this->head;
            Node *current2 = otherList.head;
            while (current2->next != nullptr) {
                current1->next = new Node(current2->next->data);
                current1 = current1->next;
                current2 = current2->next;
            }
        }
        else {
            this->size = 0;
            this->head = nullptr;
        }
        return *this;
    }

    T &operator [] (int index) {
        if (!this->head)
            throw out_of_range("empty list");
        if (index < 0 || index >= this->size)
            throw out_of_range("incorrect index");
        Node *current = this->head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->data;
    }

    T &GetFirst() {
        if (!this->head) {
            throw out_of_range("empty list");
        }
        return this->head->data;
    }

    T &GetLast() {
        if (!this->head) {
            throw out_of_range("empty list");
        }
        return this->operator[](this->size - 1);
    }

    LinkedList<T> GetSubList(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= this->size || endIndex < 0 || endIndex >= this->size || startIndex > endIndex)
            throw out_of_range("incorrect indexes");
        Node *current1 = this->head;
        for (int i = 0; i < startIndex; i++) {
            current1 = current1->next;
        }
        LinkedList<T> subList;
        subList.head = new Node(current1->data);
        subList.size = endIndex - startIndex + 1;
        Node *current2 = subList.head;
        for (int i = startIndex; i < endIndex; i++) {
            current2->next = new Node(current1->next->data);
            current1 = current1->next;
            current2 = current2->next;
        }
        return subList;
    }

    int GetLength() { return this->size; }

    void Append(T item) {
        if (!this->head)
            this->head = new Node(item);
        else {
            Node *current = this->head;
            while (current->next != nullptr)
                current = current->next;
            current->next = new Node(item);
        }
        this->size++;
    }

    void Prepend(T item) {
        if (!this->head)
            this->head = new Node(item);
        else
            this->head = new Node(item, this->head);
        this->size++;
    }

    T PopFirst() {
        if (this->size == 0)
            throw range_error("empty list");
        else {
            this->size--;
            Node *temp = this->head;
            T data = temp->data;
            this->head = this->head->next;
            delete temp;
            return data;
        }
    }

    T PopLast() {
        if (!this->size)
            throw range_error("empty list");
        else if (this->size == 1)
            this->PopFirst();
        else {
            Node *current = this->head;
            while (current->next->next != nullptr)
                current = current->next;
            Node *temp = current->next;
            T data = temp->data;
            delete temp;
            current->next = nullptr;
            this->size--;
            return data;
        }
    }

    void InsertAt(int index, T item) {
        if (index < 0 || index >= this->size)
            throw out_of_range("incorrect index");
        if (index == 0)
            this->Prepend(item);
        else {
            Node *current = this->head;
            for (int i = 0; i < index - 1; i++)
                current = current->next;
            current->next = new Node(item, current->next);
            this->size++;
        }
    }

    void Set(int index, T value) {
        if (index < 0 || index >= this->size)
            throw range_error("index < 0 or index >= length");
        this->operator[](index) = value;
    }

    LinkedList<T> operator + (const LinkedList<T> &otherList) {
        LinkedList<T> res;
        res.size = this->size + otherList.size;
        res.head = new Node(this->head->data);
        Node *current1 = this->head;
        Node *current2 = res.head;
        while (current1->next != nullptr) {
            current2->next = new Node(current1->next->data);
            current1 = current1->next;
            current2 = current2->next;
        }
        Node *current3 = otherList.head;
        while (current3 != nullptr) {
            current2->next = new Node(current3->data);
            current2 = current2->next;
            current3 = current3->next;
        }
        return res;
    }

    void Print() {
        for (int i = 0; i < this->size; i++)
            cout << this->operator[](i) << " ";
        cout << endl;
    }

    ~LinkedList() {
        while(this->size) {
            Node *temp = this->head;
            this->head = this->head->next;
            delete temp;
            this->size--;
        }
    }
};

#endif



