#ifndef DEL_DRIVERS_H
#define DEL_DRIVERS_H

#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
//#include <mainwindow.h>
//#include <ui_mainwindow.h>
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class del_drivers;
}
class MainWindow; //Forward declaration
class del_drivers : public QWidget
{
    Q_OBJECT

public:
    explicit del_drivers(QWidget *parent = nullptr);
    void connectToPSql_dell_drivers();
    void loadDrivers();
    //void fillcombobox_fio();
    //void driverSelected(int index);
    //int getDriverIdByFIO(const QString& str);
    ~del_drivers();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_del_clicked();


private:
    Ui::del_drivers *ui;
    MainWindow *main_form;
    QSqlDatabase db_del_drivers;
    QSqlQueryModel *model_del;


};

#endif // DEL_DRIVERS_H
