#include "auto.h"
#include "ui_auto.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
//#include <main.cpp>


Auto::Auto(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Auto)
{
    ui->setupUi(this);
    model = new QSqlQueryModel;
    connectToPSql_auto();
}

void Auto::connectToPSql_auto()
{
    db = QSqlDatabase::addDatabase("QPSQL", "auto_connect");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setUserName("postgres"); //username
    db.setPassword("qwerty"); //password
    db.setDatabaseName("tranzit"); //Name database
    if(db.open()){
        QSqlQuery query_auto(db);
        if (query_auto.exec("SELECT marka_model, gosnomer, god_vipuska, VIN, sostoyanie FROM Auto;")){
            model->setQuery(query_auto);
            model->setHeaderData(0, Qt::Horizontal, tr("Марка и Модель"));
            model->setHeaderData(1, Qt::Horizontal, tr("Госномер"));
            model->setHeaderData(2, Qt::Horizontal, tr("Год выпуска"));
            model->setHeaderData(3, Qt::Horizontal, tr("VIN"));
            model->setHeaderData(4, Qt::Horizontal, tr("Состояние"));

            ui->tableView->setModel(model);
            //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableView->resizeColumnsToContents(); // Подгонка ширины колонок под содержимое
            db.close();

        }
        else {
                QSqlError error = query_auto.lastError();
                qDebug() << "Error executing query: " << error.text();
            }

    }
    db.close();


}

Auto::~Auto()
{
    delete model;
    delete gry;
    delete ui;
}

void Auto::on_backToMainWind_clicked()
{
    main_form = new MainWindow();
    main_form -> show();
    this->close();
}


void Auto::on_tableView_activated(const QModelIndex &index)
{


}


