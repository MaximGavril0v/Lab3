#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H


#include "Sequence.h"
#include "DynamicArray.h"


template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> array;

public:
    ArraySequence() {
        this->array = DynamicArray<T>();
    }

    ArraySequence(T *items, int count) {
        this->array = DynamicArray<T>(items, count);
    }

    explicit ArraySequence(const DynamicArray<T> &array) {
        this->array = DynamicArray<T>(array);
    }

    ArraySequence(const ArraySequence<T> &arraySequence) {
        this->array = DynamicArray<T>(arraySequence.array);
    }

    ArraySequence<T> &operator = (const ArraySequence<T> &arraySequence) {
        this->array = DynamicArray<T>(arraySequence.array);
        return *this;
    }

    T &GetFirst() {
        if (!this->GetLength())
            throw out_of_range("empty list");
        return this->array[0];
    }

    T &GetLast() {
        if (!this->GetLength())
            throw out_of_range("empty list");
        return this->array[this->array.GetLength() - 1];
    }

    T &operator [] (int index) {
        if (index < 0 || index >= this->GetLength())
            throw out_of_range("incorrect index");
        return this->array[index];
    }

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= this->GetLength() || endIndex < 0 || endIndex >= this->GetLength() || startIndex > endIndex)
            throw out_of_range("incorrect indexes");
        auto *res = new ArraySequence<T>();
        for (int j = startIndex; j < endIndex + 1; j++)
            res->Append(this->array[j]);
        return res;
    }

    int GetLength() {
        return this->array.GetLength();
    }

    void Append(T item) {
        this->array.Resize(GetLength() + 1);
        this->array[GetLength() - 1] = item;
    }

    void Prepend(T item) {
        this->array.Resize(this->GetLength() + 1);
        for (int i = this->GetLength() - 1; i > 0; i--)
            this->array[i] = this->array[i - 1];
        this->array[0] = item;
    }

    void InsertAt(int index, T item) {
        if (index < 0 || index >= this->GetLength())
            throw out_of_range("incorrect index");
        this->array.Resize(this->GetLength() + 1);
        for (int i = this->GetLength() - 1; i > index; i--)
            this->array[i] = this->array[i - 1];
        this->array[index] = item;
    }

    void PopFirst() {
        for (int i = 0; i < this->GetLength() - 1; i++)
            this->array[i] = this->array[i + 1];
        this->array.Resize(this->GetLength() - 1);
    }

    void PopLast() {
        this->array.Resize(this->GetLength() - 1);
    }

    ArraySequence<T> *Concat(Sequence<T> *otherSequence) {
        auto *res = new ArraySequence<T>();
        for (int i = 0; i < this->GetLength(); i++)
            res->Append(this->array[i]);
        for (int i = 0; i < otherSequence->GetLength(); i++)
            res->Append(otherSequence->operator[](i));
        return res;
    }

    ArraySequence<T> *Map(T (*f)(T)) {
        auto *res = new ArraySequence<T>();
        for (int i = 0; i < GetLength(); i++)
            res->Append(f(array[i]));
        return res;
    }

    ArraySequence<T> *Where(bool (*f)(T)) {
        auto *res = new ArraySequence<T>();
        for (int i = 0; i < GetLength(); i++) {
            if (f(array[i]))
                res->Append(array[i]);
        }
        return res;
    }

    T Reduce(T (*f)(T, T), const T c) {
        T res = f(GetFirst(), c);
        for (int i = 1; i < GetLength(); i++)
            res = f(array[i], res);
        return res;
    }
};

#endif



