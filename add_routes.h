#ifndef ADD_ROUTES_H
#define ADD_ROUTES_H

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
#include <QComboBox>

namespace Ui {
class add_routes;
}
class MainWindow; //Forward declaration
class add_routes : public QWidget
{
    Q_OBJECT

public:
    explicit add_routes(QWidget *parent = nullptr);
    void connectToPSql_add_routes();
    void fillcombobox_fio();
    void fillcombobox_auto(int index);
    void driverSelected(int index);
    int getDriverIdByFIO(const QString& str);


    ~add_routes();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_add_clicked();




private:
    Ui::add_routes *ui;
    MainWindow *main_form_add_routes;
    QSqlDatabase db_add_routes;
};

#endif // ADD_ROUTES_H
