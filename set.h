#ifndef SET_H
#define SET_H
#include <QTextStream>
#include "cleverpointer.h"
#include  <cstddef>
#include <QFile>

template <class T>
class Iterator;

template <class A> class Set
{
private:
    typedef CleverPointer<A> Pointer;
    unsigned int num_size; //число элементов в множестве
    unsigned int max_size; //максимальное число элементов в множеств
    Pointer* table;
    void reset()
    {
        unsigned int max = max_size;
        max_size *=2;
        Pointer* new_set = this->table;
        num_size = 0;
        table = new Pointer[max_size];
        for (size_t i = 0; i < max; i++)
        {
            Iterator<A> p(new_set[i]);
            while (!p.atEnd())
            {
                insert(p.get());
                p.move();
            }
        }
        for (size_t i = 0; i < max; i++)
            new_set[i].clear();
        delete [] new_set;
    }
public:
    friend class MainWindow;
    Set():num_size(0), max_size(4)
    {
        table = new Pointer[max_size];
    }
    Set<A>(const Set<A> &new_set):num_size(0), max_size(new_set.maximum())
    {
        table = new Pointer[max_size];
        max_size = new_set.maximum();
        for (size_t i = 0; i < max_size; i++)
        {
            Iterator<A> p(new_set.table[i]);
            while (!p.atEnd())
            {
                insert(p.get());
                p.move();
            }
        }
    }
    Set<A>(Set<A> *new_set):num_size(0), max_size(new_set->maximum())
    {
        Pointer* new_datum = new Pointer[max_size];
        table = new_datum;
        max_size = new_set->maximum();
        for (size_t i = 0; i < max_size; i++)
        {
            Iterator<A> p(new_set->table[i]);
            while (!p.atEnd())
            {
                insert(p.get());
                p.move();
            }
        }
    }
    ~Set()
    {
        clear();
    }
    unsigned int size() const
    {
        return num_size;
    }
    unsigned int maximum() const
    {
        return max_size;
    }
    size_t hash_function(A new_element) const
    {
        return qHash(new_element)%max_size;
    }
    bool find(const A &new_element) const
    {
        if (table[hash_function(new_element)].find(new_element))
            return 1;
        return 0;
    }
    void write_file(const QString &file_name) const
    {
        QFile file(file_name);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        print(&stream);
        file.close();
    }
    void read_file(const QString &file_name)
    {
        QFile file(file_name);
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        clear();
        while (!stream.atEnd())
        {
            QString str = stream.readLine();
            insert(str);
        }
        file.close();
    }
    void insert(const A &new_element)
    {
        if (!find(new_element))
        {
            table[hash_function(new_element)].add_element(new_element);
            num_size++;
        }
        if (num_size >= max_size)
            reset();
    }
    void print(QTextStream* stream) const
    {
        for (size_t i = 0; i < max_size; i++)
            table[i].show(stream);
    }
    void operator<< (const A &new_element)
    {
        insert(new_element);
    }
    bool operator[] (const A &new_element) const
    {
        return find(new_element);
    }
    void deleter(const A &del_element)
    {
        if (find(del_element))
        {
            table[hash_function(del_element)].deleter(del_element);
            num_size--;
        }
    }
    void clear()
    {
        for (size_t i = 0; i < max_size; i++)
            table[i].clear();
        num_size = 0;
    }
    void operator=(const Set<A> &other)
    {
        clear();
        max_size = other.maximum();
        for (size_t i = 0; i < other.maximum(); i++)
        {
            Iterator<A> p(other.table[i]);
            while (!p.atEnd())
            {
                insert(p.get());
                p.move();
            }
        }
    }
    void operator=(Set<A>* other)
    {
        clear();
        max_size = other->maximum();
        table = new Pointer[max_size];
        for (size_t i = 0; i < other->maximum(); i++)
        {
            Iterator<A> p(other->table[i]);
            while (!p.atEnd())
            {
                insert(p.get());
                p.move();
            }
        }
    }
    Set<A> operator&&(const Set<A> &other)
    {
        Set<A> new_set(*this);
        for (size_t i = 0; i < max_size; i++)
        {
            Iterator<A> p(table[i]);
            while (!p.atEnd())
             {
                 if (!other.find(p.get()))
                     new_set.deleter(p.get());
                 p.move();
             }
        }
        return new_set;
    }
    Set<A> operator+(const Set<A> &other)
    {
        Set<A> new_set(this);
        new_set += other;
        return new_set;
    }
    void operator+=(const Set<A> &other)
    {
        for (size_t i = 0; i < other.maximum(); i++)
        {
             Iterator<A> p(other.table[i]);
             while (!p.atEnd())
             {
                 this->insert(p.get());
                 p.move();
             }
        }
    }
    bool operator==(const Set<A> &other) const
    {
        if (num_size != other.size())
            return 0;
        for (size_t i = 0; i < max_size; i++)
        {
            Iterator<A> p(table[i]);
            while (!p.atEnd())
             {
                 if (!find(p.get()))
                     return 0;
                 p.move();
             }
        }
        return 1;
    }
    bool operator!=(const Set<A> &other) const
    {
        return !(*this == other);
    }
    void operator*=(const Set<A> &other)
    {
        Set<A> new_set(*this);
        for (size_t i = 0; i < new_set.maximum(); i++)
        {
            Iterator<A> p(new_set.table[i]);
            while (!p.atEnd())
             {
                 if (!other.find(p.get()))
                     deleter(p.get());
                 p.move();
             }
        }
    }
    void sizeset(QTextStream* stream)
    {
        for (size_t i =0 ; i < maximum(); i++)
            *stream << table[i].get_size() << "\n";
    }
};

template <class T>
class Iterator
{
private:
    typename CleverPointer<T>::Element* pointer;
public:
    Iterator()
    {
        pointer = nullptr;
    }
public:
    Iterator(const CleverPointer<T> &data)
    {
        pointer = data.part;
    }
    bool atEnd()
    {
        return pointer == nullptr ? 1:0;
    }
    void move()
    {
        if (!atEnd())
            pointer = pointer->next;
    }
    T get()
    {
        return pointer->get_datum();
    }
};

#endif // SET_H
