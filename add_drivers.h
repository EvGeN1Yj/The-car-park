#ifndef ADD_DRIVERS_H
#define ADD_DRIVERS_H

#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
//#include <mainwindow.h>
//#include <ui_mainwindow.h>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QString>
#include <QDate>

namespace Ui {
class add_drivers;
}
class MainWindow; //Forward declaration
class add_drivers : public QWidget
{
    Q_OBJECT

public:
    explicit add_drivers(QWidget *parent = nullptr);
    void connectToPSql_add_drivers();
    ~add_drivers();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_drivers *ui;
    MainWindow *main_form_add_drivers;
    QSqlDatabase db_add_drivers;

};

#endif // ADD_DRIVERS_H
