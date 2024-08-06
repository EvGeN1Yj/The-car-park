#include "add_drivers.h"
#include "ui_add_drivers.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include "QMessageBox"
#include <QSqlError>
#include "roles.h"

add_drivers::add_drivers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::add_drivers)
{
    ui->setupUi(this);
    //model_add_drivers = new QSqlQueryModel;
    connectToPSql_add_drivers();
}

void add_drivers::connectToPSql_add_drivers()
{

    db_add_drivers = QSqlDatabase::addDatabase("QPSQL");
    db_add_drivers.setHostName("127.0.0.1");
    db_add_drivers.setPort(5432);
    db_add_drivers.setUserName("adm_user"); //username
    db_add_drivers.setPassword("12345678Aa!"); //passwo rd
    db_add_drivers.setDatabaseName("tranzit"); //Name database
    db_add_drivers.open(); // Открываем соединение



    if (!db_add_drivers.open()) {
            qDebug() << "Failed to open database connection";
            qDebug() << db_add_drivers.lastError().text();
            return;
        }

}

add_drivers::~add_drivers()
{
    //delete model_add_drivers;
    //delete gry_add_drivers;
    //if (db_add_drivers.isOpen()){
   //     db_add_drivers.close();
   // }
    delete ui;
}

void add_drivers::on_pushButton_back_clicked()
{
    main_form_add_drivers = new MainWindow();
    main_form_add_drivers -> show();
    this->close();
}


void add_drivers::on_pushButton_2_clicked()
{
    QString fio = ui->lineEdit_fio->text();
    QDate birthdate = ui->dateEdit_DateOfBirth -> date();
    QString phone = ui->lineEdit_Phone->text();
    QString driverLicenseNumber = ui->lineEdit_2_DriverLicenseNumber->text();
    QString drivingCategory = ui->lineEdit_DrivingCategory->text();
    QDate licenseStartDate = ui->dateEdit_LicenseStartDate->date();
    QDate licenseFinishDate = ui->dateEdit_LicenseFinishDate->date();

    QRegularExpression phoneRegex("^\\+7\\d{10}$");
    QRegularExpression driverLicenseNumberRegex("^\\d{1,6}$");
    QRegularExpression drivingCategoryRegex("^[A-F]$");

    if (!fio.isEmpty() && birthdate.isValid() &&!phone.isEmpty() &&!driverLicenseNumber.isEmpty() &&!drivingCategory.isEmpty() && licenseStartDate.isValid() && licenseFinishDate.isValid())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO Drivers (SNP_driver, date_of_birth, phone_number, "
                      "drivers_license_number, category_of_rights, data_vidachi_prav, "
                      "data_orkonch_prav) VALUES (:fio, :birthdate, :phone, :driverLicenseNumber, "
                      ":drivingCategory, :licenseStartDate, :licenseFinishDate)");
        query.bindValue(":fio", fio);
        query.bindValue(":birthdate",birthdate.toString(Qt::ISODate));
        query.bindValue(":phone",phone);
        query.bindValue(":driverLicenseNumber",driverLicenseNumber);
        query.bindValue(":drivingCategory",drivingCategory);
        query.bindValue(":licenseStartDate", licenseStartDate.toString(Qt::ISODate));
        query.bindValue(":licenseFinishDate", licenseFinishDate.toString(Qt::ISODate));

        if (query.exec()) {
            QMessageBox::information(this, tr("Успешно"), tr("Водитель успешно добавлен."));
        } else {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось добавить водителя. Попробуйте снова."));
        }
    }
    else {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Все поля обязательны для заполнения."));
    }
}

