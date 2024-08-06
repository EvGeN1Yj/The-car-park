#include "add_auto.h"
#include "ui_add_auto.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include "QMessageBox"
#include <QSqlError>
#include "roles.h"


add_auto::add_auto(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::add_auto)
{
    ui->setupUi(this);
    connectToPSql_add_auto();
}

void add_auto::connectToPSql_add_auto()
{

    db_add_auto = QSqlDatabase::addDatabase("QPSQL");
    db_add_auto.setHostName("127.0.0.1");
    db_add_auto.setPort(5432);
    db_add_auto.setUserName("adm_user"); //username
    db_add_auto.setPassword("12345678Aa!"); //password
    db_add_auto.setDatabaseName("tranzit"); //Name database
    db_add_auto.open(); // Открываем соединение

    if (!db_add_auto.open()) { // Открываем соединение
            QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось установить соединение с базой данных.") + "\n" + db_add_auto.lastError().text());
            return;
        }


}

add_auto::~add_auto()
{
    db_add_auto.close(); // Закрываем соединение в деструкторе
    delete ui;
}

void add_auto::on_pushButton_back_clicked()
{
    main_form_add_auto = new MainWindow();
    main_form_add_auto -> show();
    this->close();
}


void add_auto::on_pushButton_2_clicked()
{
    QString marca =ui->lineEdit_marka->text();
    int god = ui->lineEdit_god->text().toInt();
    QString gosnomer = ui->lineEdit_gosnomer->text();
    QString vin =ui->lineEdit_VIN->text();
    bool ispraven = ui->radioButton_ispraven->isChecked();
    bool remont = ui->radioButton_remont->isChecked();

    if (!marca.isEmpty() && god >= 1900 &&!gosnomer.isEmpty() &&!vin.isEmpty() && (ispraven || remont)) {
        QSqlQuery query;
        if (ispraven || remont) {
            query.prepare("INSERT INTO Auto (marka_model, god_vipuska, gosnomer, VIN, sostoyanie) "
                          "VALUES (?,?,?,?,?)");
            query.addBindValue(marca);
            query.addBindValue(god);
            query.addBindValue(gosnomer);
            query.addBindValue(vin);
            query.addBindValue(ispraven? "Исправен" : "На ремонте");
            if (query.exec()) {
                QMessageBox::information(this, tr("Успешно"), tr("Автомобиль успешно добавлен."));
            } else {
                QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось добавить автомобиль. Попробуйте снова.") + "\n" + query.lastError().text());
            }
        } else {
            QMessageBox::warning(this, tr("Предупреждение"), tr("Выберите состояние автомобиля."));
        }
    } else {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Проверьте введенные данные."));
    }

}

