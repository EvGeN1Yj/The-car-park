#include "drivers.h"
#include "ui_drivers.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>


Drivers::Drivers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Drivers)
{
    ui->setupUi(this);
    model_drivers = new QSqlQueryModel;

    connectToPSql_drivers();
}

void Drivers::connectToPSql_drivers()
{
    db_drivers = QSqlDatabase::addDatabase("QPSQL", "drivers_connect");
    db_drivers.setHostName("127.0.0.1");
    db_drivers.setPort(5432);
    db_drivers.setUserName("postgres"); //username
    db_drivers.setPassword("qwerty"); //password
    db_drivers.setDatabaseName("tranzit"); //Name database
}

Drivers::~Drivers()
{
    delete model_drivers;
    delete gry_drivers;
    delete ui;
    if (db_drivers.isOpen())
    {
        db_drivers.close();
    }
}

void Drivers::on_pushButton_Lichn_inf_clicked()
{
    if (db_drivers.open())
    {
            QSqlQuery query(db_drivers);
            if (query.exec("SELECT SNP_driver, date_of_birth, phone_number, drivers_license_number, category_of_rights, data_vidachi_prav, data_orkonch_prav FROM Drivers"))
            {
                model_drivers->setQuery(query);
                model_drivers->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
                model_drivers->setHeaderData(1, Qt::Horizontal, tr("Дата рождения"));
                model_drivers->setHeaderData(2, Qt::Horizontal, tr("Телефон"));
                model_drivers->setHeaderData(3, Qt::Horizontal, tr("Номер удостоверения"));
                model_drivers->setHeaderData(4, Qt::Horizontal, tr("Категория прав"));
                model_drivers->setHeaderData(5, Qt::Horizontal, tr("Дата выдачи прав"));
                model_drivers->setHeaderData(6, Qt::Horizontal, tr("Дата окончания прав"));

                ui->tableView->setModel(model_drivers);
                ui->tableView->resizeColumnsToContents();
            }
            else
            {
                qDebug() << "Error executing query: " << query.lastError().text();
            }
        }
}


void Drivers::on_pushButton_inf_routes_clicked()
{
    if(db_drivers.open())
    {
        QSqlQuery query(db_drivers);
        if (query.exec("SELECT Drivers.SNP_driver, Auto.marka_model, routes.data_routes, "
            "routes.punkt_otpravlenia, routes.punkt_naznachenia, routes.time_otpravlenia, routes.time_pribetia "
            "FROM Drivers "
            "JOIN Driver_Auto ON Drivers.ID_driver = Driver_Auto.ID_driver "
            "JOIN Auto ON Driver_Auto.ID_auto = Auto.ID_auto "
            "JOIN routes ON Auto.ID_auto = routes.ID_auto"))
        {
            model_drivers->setQuery(query);
            model_drivers->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
            model_drivers->setHeaderData(1, Qt::Horizontal, tr("Авто"));
            model_drivers->setHeaderData(2, Qt::Horizontal, tr("Дата маршрута"));
            model_drivers->setHeaderData(3, Qt::Horizontal, tr("Пункт отправления"));
            model_drivers->setHeaderData(4, Qt::Horizontal, tr("Пункт назначения"));
            model_drivers->setHeaderData(5, Qt::Horizontal, tr("Время отправления"));
            model_drivers->setHeaderData(6, Qt::Horizontal, tr("Время прибытия"));

            ui->tableView->setModel(model_drivers);
            ui->tableView->resizeColumnsToContents();
        }
        else
        {
            qDebug() << "Error executing query: " << query.lastError().text();
        }
    }
    db_drivers.close();
}


void Drivers::on_pushButton_clicked()
{
    main_form_drivers = new MainWindow();
    main_form_drivers -> show();
    this->close();
}





void Drivers::on_pushButton_2_Drivers_Auto_clicked()
{
    if(db_drivers.open())
    {
        QSqlQuery query(db_drivers);
        if (query.exec("SELECT Drivers.SNP_driver, Auto.marka_model FROM Drivers "
            "JOIN Driver_Auto ON Drivers.ID_driver = Driver_Auto.ID_driver "
            "JOIN Auto ON Driver_Auto.ID_auto = Auto.ID_auto"))
        {
            model_drivers->setQuery(query);
            model_drivers->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
            model_drivers->setHeaderData(1, Qt::Horizontal, tr("Авто"));
            ui->tableView->setModel(model_drivers);
            ui->tableView->resizeColumnsToContents();
        }
        else
        {
            qDebug() << "Error executing query: " << query.lastError().text();
        }
    }
}

