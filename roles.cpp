#include "roles.h"
#include "ui_roles.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QString>
#include <QMessageBox>
#include <QApplication>

roles::roles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roles)
{
    ui->setupUi(this);
}

roles::~roles()
{
    delete ui;

}

void roles::on_pushButton_admin_clicked()
{
    QString enteredPassword = ui->lineEdit_password->text();
    QString expectedAdminPassword = "admin"; // Пароль администратора
    if (enteredPassword == expectedAdminPassword)
    {
        mainwindow_form =new MainWindow();
        mainwindow_form -> show();
        this->close();
    }
    else
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Неверный пароль"));
    }

}


void roles::on_pushButton_client_clicked()
{
    client_form = new client();
    client_form->show();
    this->close();

}

