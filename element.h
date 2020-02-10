//#ifndef ELEMENT_H
//#define ELEMENT_H

//#include <QTextStream>

//template <class T>
//class Data
//{
//private:
//    struct Element
//    {
//        Element* next;
//        T* datum;
//        T get_datum()
//        {
//            return *datum;
//        }
//        void set_datum(const T &new_element)
//        {
//            datum = new T;
//            *datum = new_element;
//        }
//    };
//    Element* cell;
//public:
//    class Iterator
//    {
//    private:
//        Element* pointer;
//        Iterator()
//        {
//            pointer = nullptr;
//        }
//    public:
//        Iterator(const Data &data)
//        {
//            pointer = data.cell;
//        }
//        bool atEnd()
//        {
//            return pointer == nullptr ? 1:0;
//        }
//        void move()
//        {
//            if (!atEnd())
//                pointer = pointer->next;
//        }
//        T get()
//        {
//            return pointer->get_datum();
//        }
//    };
//    void show(QTextStream* stream)
//    {
//        Iterator it(*this);
//        while (!it.atEnd())
//        {
//            stream << it.get() << "\n";
//            it.move();
//        }
//    }
//    void add_element(T new_element)
//    {
//        Element* pointer = cell;
//        while (pointer)
//        {
//            pointer =  pointer->next;
//        }
//        pointer = new Element;
//        pointer->set_datum(new_element);
//        pointer->next = nullptr;
//    }
//    bool find(const T &check_element) const
//    {
//        Element* pointer = cell;
//        while (pointer)
//        {
//            if (pointer->get_datum() == check_element)
//                return 1;
//            pointer =  pointer->next;
//        }
//        return 0;
//    }
//    Element* deleter(const T &del_element)
//    {

//    }
//    void clear_all()
//    {
//        if (next)
//        {
//            next->clear_all();
//            delete next;
//        }
//    }
//};
//#endif // ELEMENT_H
