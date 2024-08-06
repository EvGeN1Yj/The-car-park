#ifndef DRIVERS_H
#define DRIVERS_H

#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <add_drivers.h>
#include <ui_add_drivers.h>

namespace Ui {
class Drivers;
}

class MainWindow; //Forward declaration
class Drivers : public QWidget
{
    Q_OBJECT

public:
    explicit Drivers(QWidget *parent = nullptr);
    void connectToPSql_drivers();
    ~Drivers();



private slots:
    void on_pushButton_Lichn_inf_clicked();

    void on_pushButton_inf_routes_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_Drivers_Auto_clicked();

private:
    Ui::Drivers *ui;
    MainWindow *main_form_drivers;
    QSqlQueryModel *model_drivers;
    QSqlQuery *gry_drivers;
    QSqlDatabase db_drivers;

};

#endif // DRIVERS_H
