#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

template <class T>
class Sequence {
public:
    virtual T &GetFirst() = 0;

    virtual T &GetLast() = 0;

    virtual T &operator [] (int index) = 0;

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;

    virtual int GetLength() = 0;

    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(int index, T item) = 0;

    virtual void PopFirst() = 0;

    virtual void PopLast() = 0;

    virtual Sequence<T> *Concat(Sequence<T> *otherSequence) = 0;

    virtual Sequence<T> *Map(T (*f)(T)) = 0;

    virtual Sequence<T> *Where(bool (*f)(T)) = 0;

    virtual T Reduce(T (*f)(T, T), T c) = 0;

    virtual ~Sequence() = default;
};

#endif


