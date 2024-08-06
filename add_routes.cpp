#include "add_routes.h"
#include "ui_add_routes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include "QMessageBox"
#include <QSqlError>
#include <QString>
#include <QComboBox>
#include <QDate>
#include <QTime>
#include <QStandardItem>
add_routes::add_routes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::add_routes)
{
    ui->setupUi(this);
    connectToPSql_add_routes();
    fillcombobox_fio();
    connect(ui->comboBox_fio, &QComboBox::currentIndexChanged, this, &add_routes::driverSelected);



}

void add_routes::connectToPSql_add_routes()
{

    db_add_routes = QSqlDatabase::addDatabase("QPSQL");
    db_add_routes.setHostName("127.0.0.1");
    db_add_routes.setPort(5432);
    db_add_routes.setUserName("adm_user"); //username
    db_add_routes.setPassword("12345678Aa!"); //password
    db_add_routes.setDatabaseName("tranzit"); //Name database
    db_add_routes.open(); // Открываем соединение

}

void add_routes::fillcombobox_fio()
{
    ui->comboBox_fio->clear(); // очищаем comboBox перед заполнением
    QSqlQuery query;
    query.exec("SELECT SNP_driver, ID_driver FROM Drivers");
    while (query.next())
    {
        ui->comboBox_fio->addItem(query.value(0).toString());
    }
}

void add_routes::fillcombobox_auto(int driverID)
{
    ui->comboBox_auto->clear();
        QSqlQuery query;
        query.prepare("SELECT Auto.ID_auto, Auto.marka_model FROM Auto "
                      "INNER JOIN Driver_Auto ON Auto.ID_auto = Driver_Auto.ID_auto "
                      "WHERE Driver_Auto.ID_driver = :driverId");
        query.bindValue(":driverId", driverID);
        query.exec();
        while (query.next())
            {
                QString displayText = QString("%1 (%2)").arg(query.value(0).toString(), query.value(1).toString());
                ui->comboBox_auto->addItem(displayText);
                ui->comboBox_auto->setItemData(ui->comboBox_auto->count() - 1, QVariant(query.value(0).toInt()), Qt::UserRole);
            }

}


int add_routes::getDriverIdByFIO(const QString& fio)
{
    QSqlQuery query;
    query.prepare("SELECT ID_driver FROM Drivers WHERE SNP_driver = :fio");
    query.bindValue(":fio", fio);
    query.exec();
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1; // Возвращаем -1 или другое значение, указывающее на ошибку
}

void add_routes::driverSelected(int index)
{
    QString selectedDriver = ui->comboBox_fio->currentText();
    int driverID = getDriverIdByFIO(selectedDriver);
    fillcombobox_auto(driverID);
}

add_routes::~add_routes()
{
    delete ui;
}

void add_routes::on_pushButton_back_clicked()
{
    main_form_add_routes = new MainWindow();
    main_form_add_routes -> show();
    this->close();
}


void add_routes::on_pushButton_add_clicked()
{

    int driverId = ui->comboBox_fio->currentIndex();
        int carId = ui->comboBox_auto->itemData(ui->comboBox_auto->currentIndex(), Qt::UserRole).toInt();
        QString departurePoint = ui->comboBox_otprav->currentText();
        QString destination = ui->comboBox_nazn->currentText();
        QDate travelDate = ui->dateEdit->date();
        QTime departureTime = ui->timeEdit_otprav->time();
        QTime arrivalTime = ui->timeEdit_prib->time();

        if (!departurePoint.isEmpty() &&!destination.isEmpty() && travelDate.isValid() && departureTime.isValid() && arrivalTime.isValid()) {
            QSqlQuery query;
            query.prepare("INSERT INTO routes (ID_auto, data_routes, punkt_otpravlenia, punkt_naznachenia, time_otpravlenia, time_pribetia) VALUES (:car_id, :travel_date, :departure_point, :destination, :departure_time, :arrival_time)");
            query.bindValue(":car_id", carId);
            query.bindValue(":travel_date", travelDate);
            query.bindValue(":departure_point", departurePoint);
            query.bindValue(":destination", destination);
            query.bindValue(":departure_time", departureTime.toString("HH:mm:ss"));
            query.bindValue(":arrival_time", arrivalTime.toString("HH:mm:ss"));

            if (!query.exec()) {
                QMessageBox::warning(this, "Ошибка", QString("Не удалось добавить маршрут: %1").arg(query.lastError().text()).toLocal8Bit().constData());
            } else {
                QMessageBox::information(this, "Успех", "Маршрут успешно добавлен.");
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Заполните все поля.");
        }
}








