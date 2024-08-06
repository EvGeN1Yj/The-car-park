#include "edit_auto.h"
#include "ui_edit_auto.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include "QMessageBox"
#include <QString>
#include <QComboBox>

edit_auto::edit_auto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_auto)
{
    ui->setupUi(this);
    connectToPSql_edit_auto();
}

void edit_auto::connectToPSql_edit_auto()
{
    db_edit_auto = QSqlDatabase::addDatabase("QPSQL");
    db_edit_auto.setHostName("127.0.0.1");
    db_edit_auto.setPort(5432);
    db_edit_auto.setUserName("adm_user"); //username
    db_edit_auto.setPassword("12345678Aa!"); //passwd
    db_edit_auto.setDatabaseName("tranzit"); //Name database
    db_edit_auto.open(); // Открываем соединение
}

edit_auto::~edit_auto()
{
    delete ui;
}

void edit_auto::on_pushButton_back_clicked()
{
    main_form = new MainWindow();
    main_form -> show();
    this->close();
}


void edit_auto::on_pushButton_poisk_clicked()
{
    QString gosnomerToSearch = ui->lineEdit_poisk->text();

        QSqlQuery query;
        query.prepare("SELECT * FROM Auto WHERE gosnomer = :gosnomer");
        query.bindValue(":gosnomer", gosnomerToSearch);

        if (query.exec() && query.next()) {
            ui->lineEdit->setText(query.value("marka_model").toString());
            ui->lineEdit_gosnomer->setText(query.value("gosnomer").toString());
            ui->lineEdit_vin->setText(query.value("VIN").toString());

            bool isCarWorking = query.value("sostoyanie").toString() == "Исправен";
            ui->radioButton_ispraven->setChecked(isCarWorking);
            ui->radioButton_remont->setChecked(!isCarWorking);
        } else {
            QMessageBox::information(this, "Info", "Автомобиль с указанным госномером не найден.");
            // Сброс значений виджетов
            ui->lineEdit->clear();
            ui->lineEdit_gosnomer->clear();
            // Сброс элементов управления для VIN и состояния автомобиля
            // Не забудьте дополнительно установить значения по умолчанию для radioButton'ов
        }
}


void edit_auto::on_pushButton_edit_clicked()
{
    QString newMarkaModel = ui->lineEdit->text();
        QString newGosnomer = ui->lineEdit_gosnomer->text();
        QString newVIN = ui->lineEdit_vin->text();
        QString newSostoyanie = ui->radioButton_ispraven->isChecked() ? "Исправен" : "На ремонте";

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE Auto SET marka_model = :newMarkaModel, gosnomer = :newGosnomer, VIN = :newVIN, sostoyanie = :newSostoyanie WHERE gosnomer = :gosnomer");
        updateQuery.bindValue(":newMarkaModel", newMarkaModel);
        updateQuery.bindValue(":newGosnomer", newGosnomer);
        updateQuery.bindValue(":newVIN", newVIN);
        updateQuery.bindValue(":newSostoyanie", newSostoyanie);
        updateQuery.bindValue(":gosnomer", newGosnomer);

        if (updateQuery.exec()) {
            QMessageBox::information(this, "Success", "Информация об автомобиле успешно обновлена.");
        } else {
            QMessageBox::critical(this, "Error", "Ошибка при обновлении информации об автомобиле: " + updateQuery.lastError().text());
        }
}

