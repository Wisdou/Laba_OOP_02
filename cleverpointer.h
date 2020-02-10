#ifndef CLEVERPOINTER_H
#define CLEVERPOINTER_H

#include <QTextStream>

template<class T>
class CleverPointer
{
private:
    class Element
    {
    public:
        Element* next;
        T* datum = new T;
        void show(QTextStream* stream)
        {
            *stream << *datum << "\n";
            if (next)
                next->show(stream);
        }
        void add_element(T new_element)
        {
            if (!next)
            {
                next = new Element;
                *(next->datum) = new_element;
                next->next = nullptr;
            }
            else if (next)
                next->add_element(new_element);
        }
        bool find(T check_Element)
        {
            if (*datum == check_Element)
                return 1;
            else if (next)
                return next->find(check_Element);
            else
                return 0;
        }
        Element* deleter(T del_Element, unsigned int* size)
        {
            if (!this)
                return nullptr;
            else if (del_Element == datum)
            {
                Element* reset = next;
                *size --;
                delete datum;
                delete this;
                return reset->deleter(del_Element,size);
            }
            else
            {
                next = next->deleter(del_Element,size);
                return this;
            }
        }
        void clear_all()
        {
            if (next)
            {
                next->clear_all();
                delete datum;
                delete next;
            }
        }
        T get_datum()
        {
            return *datum;
        }
    };
    unsigned int m_size = 0;
    Element* part;
public:
    template<typename> friend class Iterator;
    CleverPointer()
    {
        part = nullptr;
    }
    ~CleverPointer()
    {
        clear();
    }
    CleverPointer<T>(const CleverPointer<T> &other)
    {
        part = nullptr;
        Element* dater = other.part;
        while (dater)
        {
            add_element(*(dater->datum));
            dater = dater->next;
        }
    }
    void operator=(const CleverPointer<T> &other)
    {
        clear();
        Element* dater = other.part;
        while (dater)
        {
            add_Element(*(dater->datum));
            dater = dater->next;
        }
    }
    void clear()
    {
        m_size = 0;
        if (part)
            part->clear_all();
        delete part;
        part = nullptr;
    }
    bool operator==(const CleverPointer<T> &other)
    {
        Element* start = part;
        Element* other_start = other.part;
        if (m_size != other.get_size())
            return 0;
        while(start)
        {
            if (!other_start->find(start->get_datum()))
                return 0;
            start = start->next;
        }
        return 1;
    }
    unsigned int get_size() const
    {
        return m_size;
    }
    void add_element(T new_element)
    {
        if (!part)
        {
            part = new Element;
            *(part->datum) = new_element;
            part->next = nullptr;
        }
        else
            part->add_element(new_element);
        m_size++;
    }
    void show(QTextStream* stream)
    {
        if (part)
            part->show(stream);
    }
    void deleter(T del_element)
    {
        part = part->deleter(del_element,&m_size);
    }
    bool find(T check_Element)
    {
        if (part)
            return part->find(check_Element);
        else
            return 0;
    }
};

#endif // CLEVERPOINTER_H
