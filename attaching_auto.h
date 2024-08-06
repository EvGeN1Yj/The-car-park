#ifndef ATTACHING_AUTO_H
#define ATTACHING_AUTO_H

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
class attaching_auto;
}
class MainWindow; //Forward declaration
class attaching_auto : public QWidget
{
    Q_OBJECT

public:
    explicit attaching_auto(QWidget *parent = nullptr);
    void connectToPSql_attach_auto();
    void fillComboBoxDrivers();
    void fillComboBoxAuto();
    ~attaching_auto();

private slots:
    void on_pushButton_back_clicked();


    void on_pushButton_2_vipolnit_clicked();

private:
    Ui::attaching_auto *ui;
    MainWindow *main_form_attach_auto;
    QSqlDatabase db_attach_auto;

};

#endif // ATTACHING_AUTO_H
