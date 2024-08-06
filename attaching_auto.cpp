#include "attaching_auto.h"
#include "ui_attaching_auto.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include "QMessageBox"
#include <QSqlError>
#include <QComboBox>
#include <QString>
#include "roles.h"

attaching_auto::attaching_auto(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::attaching_auto)
{
    ui->setupUi(this);
    connectToPSql_attach_auto();
    fillComboBoxDrivers();
    fillComboBoxAuto();
}

void attaching_auto::connectToPSql_attach_auto()
{

    db_attach_auto = QSqlDatabase::addDatabase("QPSQL");
    db_attach_auto.setHostName("127.0.0.1");
    db_attach_auto.setPort(5432);
    db_attach_auto.setUserName("adm_user"); //username
    db_attach_auto.setPassword("12345678Aa!"); //password
    db_attach_auto.setDatabaseName("tranzit"); //Name database
    db_attach_auto.open(); // Открываем соединение

}

void attaching_auto::fillComboBoxDrivers()
{
    ui->comboBox_drivers->clear(); // очищаем comboBox перед заполнением
    QSqlQuery query;
    query.exec("SELECT SNP_driver, ID_driver FROM Drivers");
    while (query.next()) {
        ui->comboBox_drivers->addItem(query.value(0).toString(), query.value(1).toInt()); // Правильно добавляется идентификатор
    }
}

void attaching_auto::fillComboBoxAuto()
{
    ui->comboBox_auto->clear(); // очищаем comboBox перед заполнением
    QSqlQuery query;
    query.exec("SELECT marka_model, ID_auto FROM Auto WHERE ID_auto NOT IN (SELECT ID_auto FROM Driver_Auto)");
    while (query.next()) {
        ui->comboBox_auto->addItem(query.value(0).toString(), query.value(1).toInt());
    }
}

attaching_auto::~attaching_auto()
{
    delete ui;
}

void attaching_auto::on_pushButton_back_clicked()
{
    main_form_attach_auto = new MainWindow();
    main_form_attach_auto -> show();
    this->close();
}


void attaching_auto::on_pushButton_2_vipolnit_clicked()
{
    //roles::connectToPSql_adm();
    int selectedDriverIndex = ui->comboBox_drivers->currentIndex();
    int selectedCarIndex = ui->comboBox_auto->currentIndex();

    if (selectedDriverIndex != -1 && selectedCarIndex != -1) { // проверяем, что выбраны корректные значения
        int selectedDriverId = ui->comboBox_drivers->itemData(selectedDriverIndex).toInt();
        int selectedCarId = ui->comboBox_auto->itemData(selectedCarIndex).toInt();

        QSqlQuery query;
        query.prepare("INSERT INTO Driver_Auto (ID_auto, ID_driver) VALUES (:car_id, :driver_id)");
        query.bindValue(":car_id", selectedCarId);
        query.bindValue(":driver_id", selectedDriverId);
        if (query.exec()) {
            QMessageBox::information(this, tr("Успешно"), tr("Автомобиль успешно прикреплен к водителю."));
            fillComboBoxAuto(); // обновляем comboBox_auto после успешного прикрепления
        } else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось прикрепить автомобиль к водителю: %1").arg(query.lastError().text()));
        }
    } else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Выберите водителя и автомобиль для прикрепления."));
    }
}

