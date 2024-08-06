#ifndef AUTO_H
#define AUTO_H

#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
//#include <mainwindow.h>
//#include <ui_mainwindow.h>
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class Auto;
}
class MainWindow; //Forward declaration
class Auto : public QWidget
{
    Q_OBJECT

public:
    explicit Auto(QWidget *parent = nullptr);
    void connectToPSql_auto();
    ~Auto();



private slots:
    void on_backToMainWind_clicked();

    void on_tableView_activated(const QModelIndex &index);



private:
    Ui::Auto *ui;
    MainWindow *main_form;
    QSqlQueryModel *model;
    QSqlQuery *gry;
    QSqlDatabase db;




};

#endif // AUTO_H
