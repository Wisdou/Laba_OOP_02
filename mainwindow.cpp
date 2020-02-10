#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>

namespace Randomer
{

    int integer(int from = INT_MIN, int to = INT_MAX) {
        return QRandomGenerator::global()->bounded(from, to);
    }
};

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow),
    m_intValidator(1,1000,this),m_doubleValidator(-100, 1000, 2, this)//directory(QCoreApplication::applicationDirPath() +"/Files")
{
    ui->setupUi(this);
//    MainWindow::setFixedSize(340,460);
    QMenu *file = menuBar()->addMenu("File");
    QMenu *del = menuBar()->addMenu("Edit");
    QAction *findable = new QAction(tr("Find element"), this);
    findable->setShortcut(tr("Ctrl+F"));
    QAction *inter = new QAction(tr("Intersection of sets"), this);
    inter->setShortcut(tr("Ctrl+K"));
    QAction *intersect = new QAction(tr("Intersection of many"), this);
    intersect->setShortcut(tr("Ctrl+I"));
    QAction *adder = new QAction(tr("Add element"), this);
    adder->setShortcut(tr("Ctrl+A"));
    QAction *saver = new QAction(tr("Save as"), this);
    QAction *uni = new QAction(tr("Union of sets"), this);
    uni->setShortcut(tr("Ctrl+U"));
    QAction *save_simple = new QAction(tr("Save"), this);
    save_simple->setShortcut(tr("Ctrl+S"));
    QAction *openFile = new QAction(tr("Open"), this);
    openFile->setShortcut(tr("Ctrl+O"));
    QAction *deleter = new QAction(tr("Clear set"), this);
    deleter->setShortcut(tr("Ctrl+Q"));
    QAction *deleter_1 = new QAction(tr("Delete element"), this);
    deleter_1->setShortcut(tr("Ctrl+D"));
    connect(adder, SIGNAL(triggered()), this, SLOT(add()));
    connect(save_simple, SIGNAL(triggered()), this, SLOT(saver()));
    connect(saver, SIGNAL(triggered()), this, SLOT(saved()));
    connect(openFile, SIGNAL(triggered()), this, SLOT(opened()));
    connect(deleter, SIGNAL(triggered()), this, SLOT(deleted_all()));
    connect(deleter_1, SIGNAL(triggered()), this, SLOT(deleted()));
    connect(findable, SIGNAL(triggered()), this, SLOT(find()));
    connect(uni, SIGNAL(triggered()), this, SLOT(multiple()));
    connect(intersect, SIGNAL(triggered()), this, SLOT(intersection()));
    connect(inter, SIGNAL(triggered()), this, SLOT(union_s()));
    file->addAction(save_simple);
    file->addAction(saver);
    file->addAction(inter);
    file->addAction(openFile); // Привязка экшена к меню File
    del->addAction(deleter); // Привязка экшена к меню Delete
    del->addAction(deleter_1); // Привязка экшена к меню Delete
    del->addAction(adder);
    del->addAction(findable);
    del->addAction(uni);
    del->addAction(intersect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    ui->listWidget->clear();
    for (size_t i = 0; i < names.maximum(); i++)
    {
        Iterator<QString> p(names.table[i]);
        while (!p.atEnd())
         {
             ui->listWidget->addItem(p.get());
             p.move();
         }
    }
}

void MainWindow::deleted()
{
    int n;
    n = ui->listWidget->count() - 1;
    for(int j = n; j >= 0; j--)
    {
      QListWidgetItem *it = ui->listWidget->item(j);
      if (it->isSelected())
          names.deleter(it->text());
    }
    reset();
}

void MainWindow::finder(QString find_element)
{
    if (!names.find(find_element))
        return;
    else
    {
        int n;
        n = ui->listWidget->count() - 1;
        for(int j = n; j >= 0; j--)
        {
          QListWidgetItem *it = ui->listWidget->item(j);
          if (it->text() == find_element)
              it->setSelected(1);
        }
    }
}
