#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QStandardItemModel>
#include <iostream>
#include <QStringList>
#include <QList>
#include <QStandardItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button2_clicked()
{
    QStringList items;
    QString path = QDir::current().path();
    QString filename = QFileDialog::getOpenFileName(this, path);
    ui -> label1 -> setText(filename);
    QFile file(filename);

    ui->treeWidget->setColumnCount(2);
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0, "DI");
    // Add root nodes
    //addTreeRoot("B", "Root_second");
    //addTreeRoot("C", "Root_third");

    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            qDebug() << "File not exists";
    } else {
        // Создаём поток для извлечения данных из файла
                QTextStream in(&file);
                QString a[5000][2] = {};
                unsigned index = 0;
                // Считываем данные до конца файла
                while (!in.atEnd()){
                    // ... построчно
                    QString line = in.readLine();
                    //qDebug() << line;
                     //учитываем, что строка разделяется точкой с запятой на колонки
                    items = line.split(";");
                    //unsigned index = items[0].toInt()-1;
                    a[index][0] = items[2];
                    a[index][1] = items[3];

                    //std:: cout << a[index][1].toStdString() << std::endl;

                    if (index > 0) {
                        addTreeChild(treeItem, items[2], items[3]);
                    }
                    ++index;
                    //std:: cout << a[0][0].toStdString() << std::endl;
                    //for (size_t i = 0 ; sizeof (a)/sizeof (a[0][0]) ; ++i){
                    //    qDebug() << a[i][0];
                    //    //std:: cout << a[i][0].toStdString() << std::endl;
                    //}

                }

                file.close();
    }
}

void MainWindow::addTreeChild(QTreeWidgetItem *parent,
                  QString name, QString description)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description.toLocal8Bit().data());

    // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
    parent->addChild(treeItem);
}

