#include "mainwindow.h"
#include "set.h"
#include <QString>
#include <QRegExp>
#include <assert.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Set<QString> set;
//    assert(set.size() == 0);
//    QTextStream stream(stdout);
//    set<<"Apple";
//    assert(set.size() == 1);
//    set<<"Apple";
//    assert(set.size() == 1);
//    assert(set["Apple"]);
//    set.deleter("Apple");
//    assert(set.size() == 0);
//    assert(!set["Apple"]);
//    set<<"Apple";
//    set<<"Reader";
//    set<<"Deletable";
////    stream << set.maximum() << "\n\n";
//    set<<"Apple";
//    set<<"Reader";
////    stream << set.maximum() << "\n\n";
//    assert(set.size() == 3);
//    set.deleter("Deletable");
//    assert(set.size() == 2);
//    assert(!set["Deletable"]);
//    set.deleter("Deletable");
//    assert(set.size() == 2);
//    assert(!set["Deletable"]);
//    Set<QString> empty;
//    Set<QString> set2;
//    set2<<"Apple";
//    set2<<"Reader2";
//    set2<<"Deletable3";
//    set2.clear();
//    assert(set2 == empty);
//    set2 = set;
//    assert(set == set2);
//    set2<<"Apple";
//    set2<<"Reader";
//    set2<<"Deletable2";
//    set2<<"Apple2";
////    stream << "\n\n\n";
////    set2.print(&stream);
//    set2<<"Reader2";
//    set2<<"Deletable3";
//    set2<<"Appe";
//    set2<<"Reder";
//    set2<<"De=letable2";
//    set2<<"Aple2";
//    set2<<"Rader2";
//    set2<<"Deletae3";
//    set2<<"Ap212e2";
////    stream << "\n\n\n";
////    set2.print(&stream);
//    set2<<"Rad214er2";
//    set2<<"De12214letae3";
//    set2<<"Deletae3";
//    set2<<"Ap214122e2";
//    set2<<"Rad12214er2";
//    set2<<"De1122214letae3";
////    stream << "\n\n\n";
////    set2.print(&stream);
//    set2.deleter("Apple");
//    set2.deleter("Dodo");
//    Set<QString> set3(set);
//    assert(set3 == set);
//    set3 << "Apple_Juice";
//    set.write_file("C:/Users/User/Desktop/Qtcodes/Set2/Set.txt");
//    set3.write_file("C:/Users/User/Desktop/Qtcodes/Set2/Set3.txt");
//    assert(set3 != set);
////    stream << "\n\n\n";
//    set << "wef";
//    set << "wefwewege";
//    set << "wegjwioeig";
//    set << "wefio";
////    stream << "\n\n\n\n";
//    set2 = set;
//    Set<QString> set4;
//    set4 << "Apple";
//    set4 << "wef";
//    set4 << "kwfgui";
//    set2 = (set4 && set);
//    assert((set && empty) == empty);
//    assert((set+empty) == set);
//    assert((set2&&set2) == set2);
//    set2.write_file("C:/Users/User/Desktop/Qtcodes/Set2/Set2.txt");
//    set4.read_file("C:/Users/User/Desktop/Qtcodes/Set2/Set2.txt");
//    assert(set2 == set4);
//    stream << "All tests are completed!\n";
    return a.exec();
}
