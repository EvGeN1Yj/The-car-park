#ifndef ADD_AUTO_H
#define ADD_AUTO_H

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
class add_auto;
}
class MainWindow; //Forward declaration
class add_auto : public QWidget
{
    Q_OBJECT

public:
    explicit add_auto(QWidget *parent = nullptr);
    void connectToPSql_add_auto();
    ~add_auto();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_auto *ui;
    MainWindow *main_form_add_auto;
    QSqlDatabase db_add_auto;

};

#endif // ADD_AUTO_H
