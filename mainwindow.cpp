#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    drivers_form = new Drivers();
    drivers_form -> show();
    this->close();

}


void MainWindow::on_pushButton_2_clicked()
{
    auto_form = new Auto();
    auto_form -> show();
    this->close();
}


void MainWindow::on_pushButton_3_clicked()
{
    routes_form = new routes();
    routes_form -> show();
    this->close();
}


void MainWindow::on_pushButton_4_add_drivers_clicked()
{
    add_drivers_form = new add_drivers();
    add_drivers_form -> show();
    this->close();
}


void MainWindow::on_pushButton_4_add_auto_clicked()
{
    add_auto_form = new add_auto();
    add_auto_form -> show();
    this->close();
}


void MainWindow::on_pushButton_5_clicked()
{
    attach_auto_from = new attaching_auto();
    attach_auto_from -> show();
    this->close();
}


void MainWindow::on_pushButton_6_clicked()
{
    add_routes_form = new add_routes();
    add_routes_form -> show();
    this->close();
}


void MainWindow::on_pushButton_del_drivers_clicked()
{
    del_drivers_form=new del_drivers();
    del_drivers_form->show();
    this->close();
}


void MainWindow::on_pushButton_del_auto_clicked()
{
    del_auto_form=new del_auto();
    del_auto_form->show();
    this->close();
}


void MainWindow::on_pushButton_4_edit_clicked()
{
    edit_drivers_form=new edit_drivers();
    edit_drivers_form->show();
    this->close();
}


void MainWindow::on_pushButton_edit_auto_clicked()
{
    edit_auto_form=new edit_auto();
    edit_auto_form->show();
    this->close();
}

