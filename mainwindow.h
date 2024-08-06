#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <drivers.h>
#include <ui_drivers.h>
#include <routes.h>
#include <ui_routes.h>
#include <auto.h>
#include <ui_auto.h>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <add_drivers.h>
#include <ui_add_drivers.h>
#include <add_auto.h>
#include <ui_add_auto.h>
#include <attaching_auto.h>
#include <ui_attaching_auto.h>
#include <add_routes.h>
#include <ui_add_routes.h>
#include <del_drivers.h>
#include <del_auto.h>
#include <edit_drivers.h>
#include <edit_auto.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_add_drivers_clicked();

    void on_pushButton_4_add_auto_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_del_drivers_clicked();

    void on_pushButton_del_auto_clicked();

    void on_pushButton_4_edit_clicked();

    void on_pushButton_edit_auto_clicked();

private:
    Ui::MainWindow *ui;
    Drivers *drivers_form;
    routes *routes_form;
    Auto *auto_form;
    add_drivers *add_drivers_form;
    add_auto *add_auto_form;
    attaching_auto *attach_auto_from;
    add_routes *add_routes_form;
    del_drivers *del_drivers_form;
    del_auto *del_auto_form;
    edit_drivers * edit_drivers_form;
    edit_auto *edit_auto_form;


};
#endif // MAINWINDOW_H
