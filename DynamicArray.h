#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H

#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class DynamicArray {

private:
    T *arr;
    int size;

public:

    DynamicArray() {
        this->arr = new T[1]();
        this->size = 0;
    }

    explicit DynamicArray(int size) {
        if (size < 0)
            throw out_of_range("incorrect size");
        this->size = size;
        this->arr = new T[size]();
    }

    DynamicArray(T *otherArray, int size) {
        if (size < 0)
            throw out_of_range("incorrect size");
        if (otherArray == nullptr)
            throw invalid_argument("non-existent array");
        this->size = size;
        this->arr = new T[size]();
        for (int i = 0; i < size; i++)
            this->arr[i] = otherArray[i];
    }

    DynamicArray(const DynamicArray<T> &otherArray) {
        if (otherArray.size == 0) {
            this->size  = 0;
            this->arr = new T[1];
        }
        else {
            this->size = otherArray.size;
            this->arr = new T[otherArray.size];
            for (int i = 0; i < otherArray.size; i++)
                this->arr[i] = otherArray.arr[i];
        }
    }

    DynamicArray<T> &operator = (const DynamicArray<T> &otherArray) {
        this->~DynamicArray();
        if (otherArray.size == 0) {
            this->size  = 0;
            this->arr = new T[1];
        }
        else {
            this->size = otherArray.size;
            this->arr = new T[otherArray.size];
            for (int i = 0; i < otherArray.size; i++)
                this->arr[i] = otherArray.arr[i];
        }
        return *this;
    }

    T &operator [] (int index) {
        if (index < 0 || index >= this->size)
            throw out_of_range("incorrect index");
        return this->arr[index];
    }

    int GetLength() { return this->size; }

    void Resize(int newSize) {
        if (newSize < 0)
            throw out_of_range("incorrect size");
        T *newArr = new T[newSize];
        if (newSize >= this->size)
            for (int i = 0; i < this->size; i++)
                newArr[i] = this->arr[i];
        else
            for (int i = 0; i < newSize; i++)
                newArr[i] = this->arr[i];
        delete[] this->arr;
        this->size = newSize;
        this->arr = newArr;
    }


    ~DynamicArray() { delete[] this->arr; }
};

#endif