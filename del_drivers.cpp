#include "del_drivers.h"
#include "ui_del_drivers.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include "QMessageBox"
#include <QString>
#include <QComboBox>

del_drivers::del_drivers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::del_drivers)
{
    ui->setupUi(this);
    //fillcombobox_fio();
    connectToPSql_dell_drivers();



}

void del_drivers::connectToPSql_dell_drivers()
{
    db_del_drivers = QSqlDatabase::addDatabase("QPSQL");
    db_del_drivers.setHostName("127.0.0.1");
    db_del_drivers.setPort(5432);
    db_del_drivers.setUserName("adm_user"); //username
    db_del_drivers.setPassword("12345678Aa!"); //passwd
    db_del_drivers.setDatabaseName("tranzit"); //Name database
    db_del_drivers.open(); // Открываем соединение
    loadDrivers();

}

void del_drivers::loadDrivers()
{
    QSqlQuery query(db_del_drivers); // Передаём объект базы данных в конструктор запроса
       query.prepare("SELECT ID_driver, SNP_driver FROM Drivers");

       if (query.exec()) {
           ui->listWidget->clear();
           while (query.next()) {
               QString driverItem = query.value(0).toString() + " - " + query.value(1).toString();
               ui->listWidget->addItem(driverItem);
           }
       } else {
           QSqlError err = query.lastError();
           qDebug() << "Ошибка при выполнении запроса:" << err.text();
           QMessageBox::warning(this, "Ошибка", "Не удалось загрузить список водителей");
       }

}




del_drivers::~del_drivers()
{
    delete ui;
}

void del_drivers::on_pushButton_back_clicked()
{
    main_form = new MainWindow();
    main_form -> show();
    this->close();
}


void del_drivers::on_pushButton_del_clicked()
{
    if (ui->listWidget->currentRow() >= 0) {
            QString selectedDriver = ui->listWidget->currentItem()->text();
            int driverID = selectedDriver.split(" - ").at(0).toInt();

            // Удаление из таблицы Driver_Auto
            QSqlQuery deleteQuery;
            deleteQuery.prepare("DELETE FROM Driver_Auto WHERE ID_driver = :driverID");
            deleteQuery.bindValue(":driverID", driverID);

            if (deleteQuery.exec())
            {
                // Удаление из таблицы Drivers
                QSqlQuery query;
                query.prepare("DELETE FROM Drivers WHERE ID_driver = :driverID");
                query.bindValue(":driverID", driverID);

                if (query.exec())
                {
                    // Успешно удалено из базы данных
                    QMessageBox::information(this, "Успех", "Водитель успешно удален из базы данных.");
                    loadDrivers(); // Обновим список водителей
                } else
                {
                    QMessageBox::critical(this, "Ошибка", "Ошибка удаления водителя из базы данных.");
                }
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "Ошибка удаления связей с автомобилями для водителя.");
            }
        }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Выберите водителя для удаления.");
    }

}


