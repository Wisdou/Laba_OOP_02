#ifndef CLEVERPOINTER_H
#define CLEVERPOINTER_H

#include <QTextStream>

template <class T>
class Iterator;

template<class T>
class CleverPointer
{
private:
    struct Node
    {
        Node(const T &value)
        {
            this->next = nullptr;
            this->value = value;
        }
        Node* next;
        T value;
    };
    Node* root;
public:
    friend class Iterator<T>;
    explicit CleverPointer()
    {
        root = nullptr;
    }
    ~CleverPointer()
    {
        this->clear();
    }
    void add(const T &value)
    {
        if (!root)
        {
            root = new Node(value);
            return;
        }
        Node* pointer = root;
        while (pointer->next)
        {
            pointer = pointer->next;
        }
        pointer->next = new Node(value);
    }
    void deleter(const T &value)
    {
        if (!root)
        {
            return;
        }
        Node* previous = root;
        while (root->value == value)
        {
            this->root = this->root->next;
            if (!root)
            {
                return;
            }
            delete previous;
            previous = this->root;
        }
        previous = root;
        Node* pointer = root;
        while (pointer)
        {
            if (pointer->value == value)
            {
                previous->next = pointer->next;
                delete pointer;
                pointer = previous->next;
            }
            else
            {
                previous = pointer;
                pointer = pointer->next;
            }
        }
    }
    bool find(const T &value)
    {
        Node* pointer = root;
        while (pointer)
        {
            if (pointer->value == value)
            {
                return true;
            }
            pointer = pointer->next;
        }
        return false;
    }
    void clear()
    {
        Node* previous;
        Node* pointer = this->root;
        while (pointer)
        {
            previous = pointer;
            pointer = pointer->next;
            delete previous;
        }
        this->root = nullptr;
    }
};

template <class T>
class Iterator
{
private:
    typedef typename CleverPointer<T>::Node* Pointer;
    Pointer pointer;
public:
    Iterator(const CleverPointer<T> &data)
    {
        this->pointer = data.root;
    }
    Iterator(CleverPointer<T>* data)
    {
        this->pointer = data->root;
    }
    bool atEnd()
    {
        return this->pointer == nullptr ? true:false;
    }
    void move()
    {
        if (!atEnd())
            this->pointer = this->pointer->next;
    }
    T get()
    {
        return this->pointer->value;
    }
};
#endif // CLEVERPOINTER_H
