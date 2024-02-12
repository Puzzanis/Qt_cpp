#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QStandardItemModel>
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
    int ind = ui->treeWidget-> topLevelItemCount();
    if (ind > 0){
        ui->treeWidget->clear();
    }
    ui->treeWidget->setColumnCount(2);
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    // Add root nodes
    treeItem->setText(0, "DI");


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
                     //учитываем, что строка разделяется точкой с запятой на колонки
                    items = line.split(";");

                    if (index > 0) {
                        addTreeChild(treeItem, items[2], items[3]);
                    }
                    ++index;
                }

                file.close();
    }
}

void MainWindow::addTreeChild(QTreeWidgetItem *parent,
                  QString name, QString description)
{

    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setText(1, description); // для нормального вывода кирилицы
    parent->addChild(treeItem);
}

