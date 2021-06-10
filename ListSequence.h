#ifndef LAB2_LISTSEQUENCE_H
#define LAB2_LISTSEQUENCE_H


#include "Sequence.h"
#include "LinkedList.h"


template <class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> list;

public:
    ListSequence() {
        this->list = LinkedList<T>();
    }

    ListSequence(T *items, int count) {
        this->list = LinkedList<T>(items, count);
    }

    explicit ListSequence(const LinkedList<T> &list) {
        this->list = LinkedList<T>(list);
    }

    ListSequence(const ListSequence<T> &listSequence) {
        this->list = LinkedList<T>(listSequence.list);
    }

    ListSequence<T> &operator = (const ListSequence<T> &listSequence) {
        this->list = LinkedList<T>(listSequence.list);
        return *this;
    }

    T &GetFirst() {
        return this->list[0];
    }

    T &GetLast() {
        return this->list[this->list.GetLength() - 1];
    }

    T &operator [] (int index) {
        if (index < 0 || index >= this->GetLength())
            throw out_of_range("incorrect index");
        return this->list[index];
    }

    ListSequence<T> *GetSubsequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= this->GetLength() || endIndex < 0 || endIndex >= this->GetLength() || startIndex > endIndex)
            throw out_of_range("incorrect indexes");
        auto *res = new ListSequence<T>(this->list.GetSubList(startIndex, endIndex));
        return res;
    }

    int GetLength() {
        return this->list.GetLength();
    }

    void Append(T item) {
        this->list.Append(item);
    }

    void Prepend(T item) {
        this->list.Prepend(item);
    }

    void InsertAt(int index, T item) {
        this->list.InsertAt(index, item);
    }

    void PopFirst() {
        this->list.PopFirst();
    }

    void PopLast() {
        this->list.PopLast();
    }

    ListSequence<T> *Concat(Sequence<T> *otherSequence) {
        auto *res = new ListSequence<T>();
        for (int i = 0; i < this->list.GetLength(); i++)
            res->Append(this->list[i]);
        for (int i = 0; i < otherSequence->GetLength(); i++)
            res->Append(otherSequence->operator[](i));
        return res;
    }

    ListSequence<T> *Map(T (*f)(T)) {
        auto *res = new ListSequence<T>();
        for (int i = GetLength() - 1; i >= 0; i--)
            res->Prepend(f(list[i]));
        return res;
    }

    ListSequence<T> *Where(bool (*f)(T)) {
        auto *res = new ListSequence<T>();
        for (int i = GetLength() - 1; i >= 0; i--) {
            if (f(list[i]))
                res->Prepend(list[i]);
        }
        return res;
    }

    T Reduce(T (*f)(T, T), const T c) {
        T res = f(GetFirst(), c);
        for (int i = 1; i < GetLength(); i++)
            res = f(list[i], res);
        return res;
    }

    ~ListSequence() = default;
};

#endif

