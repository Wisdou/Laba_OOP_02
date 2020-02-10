#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "set.h"
#include <QDoubleValidator>
#include <QIntValidator>
#include <QFileDialog>
#include <QWidget>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QCoreApplication>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void reset();
    void reset_size();
    void reset_browser();

private slots:
    void deleted_all()
    {
        names.clear();
        reset();
        QTextStream stream(stdout);
        stream << filename << "\n\n\n";
    }

    void multiple()//объединение двух множеств
    {
        QString str;
        opendir2(&str);
        Set<QString> new_set;
        new_set.read_file(str);
        if (str != "")
        {
            names += new_set;
        }
        reset();
    }

    void union_s()
    {
        QString dir = QCoreApplication::applicationDirPath() +"/Files/";
        QStringList list_of_files = QFileDialog::getOpenFileNames(this,tr("Open text file"), dir, tr("Text Files (*.txt)"));
        if (list_of_files.size() != 0)
        {
            filename.clear();
            for (int i = 0; i < list_of_files.size(); ++i)
            {
                if (i == 0)
                    names.read_file(list_of_files[i]);
                else
                {
                    Set<QString> new_set;
                    new_set.read_file(list_of_files[i]);
                    names *= new_set;
                }
            }
        }
        reset();
    }

    void intersection()//пересечение двух множеств
    {
        QString str;
        opendir2(&str);
        Set<QString> new_set;
        new_set.read_file(str);
        if (str != "")
        {
            names *= new_set;
        }
        reset();
    }

    void find()//Поиск элемента в множестве
    {
        QDialog adder(this);
        adder.setWindowTitle(tr("Find element"));
        QLineEdit *ledit1 = new QLineEdit(&adder);
        QDialogButtonBox *btn_box = new QDialogButtonBox(&adder);
        btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(btn_box, &QDialogButtonBox::accepted, &adder, &QDialog::accept);
        connect(btn_box, &QDialogButtonBox::rejected, &adder, &QDialog::reject);

        QFormLayout *layout = new QFormLayout();
        layout->addRow(tr("Find element:"), ledit1);
        layout->addWidget(btn_box);

        adder.setLayout(layout);
        // В случае, если пользователь нажал "Ok".
        if(adder.exec() == QDialog::Accepted)
        {
            QString str;
            str = ledit1->text();
            if (str == "")
            {
                QMessageBox error;
                error.setText("Empty data!");
                error.setWindowTitle("Error");
                error.exec();
            }
            finder(str);
        }
    }

    void deleted();//Удаление элемента из множества

    void add()
    {
        QDialog adder(this);
        adder.setWindowTitle(tr("Add new element"));
        QLineEdit *ledit1 = new QLineEdit(&adder);
        QDialogButtonBox *btn_box = new QDialogButtonBox(&adder);
        btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(btn_box, &QDialogButtonBox::accepted, &adder, &QDialog::accept);
        connect(btn_box, &QDialogButtonBox::rejected, &adder, &QDialog::reject);

        QFormLayout *layout = new QFormLayout();
        layout->addRow(tr("Input the name of place:"), ledit1);
        layout->addWidget(btn_box);

        adder.setLayout(layout);
        // В случае, если пользователь нажал "Ok".
        if(adder.exec() == QDialog::Accepted)
        {
            QString str;
            str = ledit1->text();
            if (str == "")
            {
                QMessageBox error;
                error.setText("Empty data!");
                error.setWindowTitle("Error");
                error.exec();
            }
            else
            {
                names << str;
                reset();
            }
        }
    }

    void opened()
    {
        QString new_str;
        opendir(new_str);
    }

    void saved()
    {
        QDialog dlg(this);
        dlg.setWindowTitle(tr("Save file"));

        QLineEdit *ledit1 = new QLineEdit(&dlg);

        QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
        btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
        connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

        QFormLayout *layout = new QFormLayout();
        layout->addRow(tr("Enter the name of file for saving:"), ledit1);
        layout->addWidget(btn_box);

        dlg.setLayout(layout);

        // В случае, если пользователь нажал "Ok".
        if(dlg.exec() == QDialog::Accepted) {
            QString str1 = ledit1->text();
            if (str1[0] == '/' || str1[0] == '\\')
            {
                QMessageBox error;
                error.setText("The name of file shouldn't include\n symbols '\' and '/'!");
                error.setWindowTitle("Error");
                error.exec();
            }
            else
            {
                filer(str1);
                QMessageBox save_info;
                save_info.setText("The changes were saved successfully!");
                save_info.setWindowTitle("Saving information");
                save_info.exec();
            }
        }
    }

    void saver()
    {
        if (this->filename.isEmpty())
        {
            QDialog dlg(this);
            dlg.setWindowTitle(tr("Save file"));

            QLineEdit *ledit1 = new QLineEdit(&dlg);

            QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
            btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

            connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
            connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

            QFormLayout *layout = new QFormLayout();
            layout->addRow(tr("Enter the name of file for saving:"), ledit1);
            layout->addWidget(btn_box);

            dlg.setLayout(layout);

            // В случае, если пользователь нажал "Ok".
            if(dlg.exec() == QDialog::Accepted) {
                QString str1 = ledit1->text();
                if (str1[0] == '/' || str1[0] == '\\')
                {
                    QMessageBox error;
                    error.setText("The name of file shouldn't include\n symbols '\' and '/'!");
                    error.setWindowTitle("Error");
                    error.exec();
                }
                else
                {
                    filer(str1);
                    QMessageBox save_info;
                    save_info.setText("The changes were saved successfully!");
                    save_info.setWindowTitle("Saving information");
                    save_info.exec();
                }
            }
        }
        else
        {
            names.write_file(this->filename);
            QMessageBox save_info;
            save_info.setText("The changes were saved successfully!");
            save_info.setWindowTitle("Saving information");
            save_info.exec();
        }
    }

private:
    Ui::MainWindow *ui;
    Set<QString> names;
    QString filename;
    QIntValidator m_intValidator;
    QDoubleValidator m_doubleValidator;
    void filer(QString str)
    {
        QString dir = QCoreApplication::applicationDirPath() +"/Files/";
        str = dir + str + ".txt";
        names.write_file(str);
        filename = str;
    }
    void opendir(QString str)
    {
        QString dir = QCoreApplication::applicationDirPath() +"/Files/";
        str = QFileDialog::getOpenFileName(this,tr("Open text file"), dir, tr("Text Files (*.txt)"));
        if (!str.isEmpty())
        {
            names.read_file(str);
            this->filename = str;
        }
        reset();
    }
    void opendir(QString* str)
    {
        QString dir = QCoreApplication::applicationDirPath() +"/Files/";
        *str = QFileDialog::getOpenFileName(this,tr("Open text file"), dir, tr("Text Files (*.txt)"));
        if (!str->isEmpty())
            names.read_file(*str);
        reset();
    }
    void opendir2(QString* str)
    {
        QString dir = QCoreApplication::applicationDirPath() +"/Files/";
        *str = QFileDialog::getOpenFileName(this,tr("Open text file"), dir, tr("Text Files (*.txt)"));
    }
    void finder(QString);
};

#endif // MAINWINDOW_H
