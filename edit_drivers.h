#ifndef EDIT_DRIVERS_H
#define EDIT_DRIVERS_H

#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <add_drivers.h>
#include <ui_add_drivers.h>


namespace Ui {
class edit_drivers;
}
class MainWindow; //Forward declaration
class edit_drivers : public QWidget
{
    Q_OBJECT

public:
    explicit edit_drivers(QWidget *parent = nullptr);
    void connectToPSql_edit_drivers();
    void loadDriverData(int driverID);
    void saveDriverData();
    ~edit_drivers();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_poisk_clicked();

private:
    Ui::edit_drivers *ui;
    MainWindow *main_form;
    QSqlDatabase db_edit_drivers;
    //QSqlQueryModel *model_del;
};

#endif // EDIT_DRIVERS_H
