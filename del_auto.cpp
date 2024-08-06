#include "del_auto.h"
#include "ui_del_auto.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include "QMessageBox"
#include <QString>
#include <QComboBox>

del_auto::del_auto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::del_auto)
{
    ui->setupUi(this);
    connectToPSql_dell_auto();
}

void del_auto::connectToPSql_dell_auto()
{
    db_del_auto = QSqlDatabase::addDatabase("QPSQL");
    db_del_auto.setHostName("127.0.0.1");
    db_del_auto.setPort(5432);
    db_del_auto.setUserName("adm_user"); //username
    db_del_auto.setPassword("12345678Aa!"); //passwd
    db_del_auto.setDatabaseName("tranzit"); //Name database
    db_del_auto.open(); // Открываем соединение
    loadDrivers();
}

void del_auto::loadDrivers()
{
    QSqlQuery query(db_del_auto); // Передаём объект базы данных в конструктор запроса
       query.prepare("SELECT ID_auto, marka_model, gosnomer FROM Auto");

       if (query.exec()) {
           ui->listWidget->clear();
           while (query.next()) {
               QString driverItem = query.value(1).toString() + " - " + query.value(2).toString();
               ui->listWidget->addItem(driverItem);
           }
       } else {
           QSqlError err = query.lastError();
           qDebug() << "Ошибка при выполнении запроса:" << err.text();
           QMessageBox::warning(this, "Ошибка", "Не удалось загрузить список водителей");
       }
}

del_auto::~del_auto()
{
    delete ui;
}

void del_auto::on_pushButton_back_clicked()
{
    main_form = new MainWindow();
    main_form -> show();
    this->close();
}


void del_auto::on_pushButton_del_clicked()
{
    if (ui->listWidget->currentRow() >= 0)
    {
        QString selectedAuto = ui->listWidget->currentItem()->text();
        int ID_auto = selectedAuto.split(" - ").at(0).toInt();

        QSqlQuery deleteDriverAutoQuery;
        deleteDriverAutoQuery.prepare("DELETE FROM Driver_Auto WHERE ID_auto = :ID_auto");
        deleteDriverAutoQuery.bindValue(":ID_auto", ID_auto);
        if (deleteDriverAutoQuery.exec())
        {
            QSqlQuery deleteRoutesQuery;
            deleteRoutesQuery.prepare("DELETE FROM routes WHERE ID_auto = :ID_auto");
            deleteRoutesQuery.bindValue(":ID_auto", ID_auto);
            if (!deleteRoutesQuery.exec())
            {
                QSqlQuery deleteAutoQuery;
                deleteAutoQuery.prepare("DELETE FROM Auto WHERE ID_auto = :ID_auto");
                deleteAutoQuery.bindValue(":ID_auto", ID_auto);
                if (deleteAutoQuery.exec()) {
                    QMessageBox::information(this, "Успех", "Авто успешно удалено из базы данных.");
                    loadDrivers(); // Обновим список авто
                } else {
                    QMessageBox::critical(this, "Ошибка", "Ошибка удаления авто из базы данных: " + deleteAutoQuery.lastError().text());
                }
            }
        }

    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите автомобиль для удаления");
    }
}

