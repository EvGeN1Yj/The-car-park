#include "edit_drivers.h"
#include "ui_edit_drivers.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include "QMessageBox"
#include <QString>
#include <QComboBox>

edit_drivers::edit_drivers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_drivers)
{
    ui->setupUi(this);
    connectToPSql_edit_drivers();
}

void edit_drivers::connectToPSql_edit_drivers()
{
    db_edit_drivers = QSqlDatabase::addDatabase("QPSQL");
    db_edit_drivers.setHostName("127.0.0.1");
    db_edit_drivers.setPort(5432);
    db_edit_drivers.setUserName("adm_user"); //username
    db_edit_drivers.setPassword("12345678Aa!"); //passwd
    db_edit_drivers.setDatabaseName("tranzit"); //Name database
    db_edit_drivers.open(); // Открываем соединение
}





edit_drivers::~edit_drivers()
{
    delete ui;
}

void edit_drivers::on_pushButton_clicked()
{
    main_form = new MainWindow();
    main_form -> show();
    this->close();
}


void edit_drivers::on_pushButton_edit_clicked()
{
    // Получаем новые значения из виджетов
        QString newFIO = ui->lineEdit_fio->text();
        QDate newBirthDate = ui->dateEdit_born->date();
        QString newPhoneNumber = ui->lineEdit_phone->text();
        QString newLicenseNumber = ui->lineEdit_vod_ud->text();
        QString newCategoryOfRights = ui->lineEdit_kat_prav->text();
        QDate newIssueDate = ui->dateEdit_data_vidachi->date();
        QDate newExpiryDate = ui->dateEdit_data_finish->date();

        // Обновляем информацию о водителе в базе данных
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE Drivers SET SNP_driver = :fio, date_of_birth = :dob, phone_number = :phone, "
                            "drivers_license_number = :license_num, category_of_rights = :rights, "
                            "data_vidachi_prav = :issue_date, data_orkonch_prav = :expiry_date WHERE SNP_driver = :fio");
        updateQuery.bindValue(":fio", newFIO);
        updateQuery.bindValue(":dob", newBirthDate);
        updateQuery.bindValue(":phone", newPhoneNumber);
        updateQuery.bindValue(":license_num", newLicenseNumber);
        updateQuery.bindValue(":rights", newCategoryOfRights);
        updateQuery.bindValue(":issue_date", newIssueDate);
        updateQuery.bindValue(":expiry_date", newExpiryDate);

        if (updateQuery.exec()) {
            QMessageBox::information(this, "Success", "Информация о водителе успешно обновлена.");
        } else {
            QMessageBox::critical(this, "Error", "Ошибка при обновлении информации о водителе: " + updateQuery.lastError().text());
        }
}


void edit_drivers::on_pushButton_poisk_clicked()
{
    QString fioToSearch = ui->lineEdit_poisk->text();

        QSqlQuery query;
        query.prepare("SELECT * FROM Drivers WHERE SNP_driver = :fio");
        query.bindValue(":fio", fioToSearch);

        if (query.exec() && query.next()) {
            ui->lineEdit_fio->setText(query.value("SNP_driver").toString());
            ui->dateEdit_born->setDate(query.value("date_of_birth").toDate());
            ui->lineEdit_phone->setText(query.value("phone_number").toString());
            ui->lineEdit_vod_ud->setText(query.value("drivers_license_number").toString());
            ui->lineEdit_kat_prav->setText(query.value("category_of_rights").toString());
            ui->dateEdit_data_vidachi->setDate(query.value("data_vidachi_prav").toDate());
            ui->dateEdit_data_finish->setDate(query.value("data_orkonch_prav").toDate());
        } else {
            QMessageBox::information(this, "Info", "Водитель с указанным ФИО не найден.");
            // Сброс значений виджетов
            ui->lineEdit_fio->clear();
            ui->dateEdit_born->setDate(QDate());
            ui->lineEdit_phone->clear();
            ui->lineEdit_vod_ud->clear();
            ui->lineEdit_kat_prav->clear();
            ui->dateEdit_data_vidachi->setDate(QDate());
            ui->dateEdit_data_finish->setDate(QDate());
        }
}

