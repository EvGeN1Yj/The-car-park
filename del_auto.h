#ifndef DEL_AUTO_H
#define DEL_AUTO_H

#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
//#include <mainwindow.h>
//#include <ui_mainwindow.h>
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class del_auto;
}
class MainWindow; //Forward declaration
class del_auto : public QWidget
{
    Q_OBJECT

public:
    explicit del_auto(QWidget *parent = nullptr);
    void connectToPSql_dell_auto();
    void loadDrivers();
    ~del_auto();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_del_clicked();

private:
    Ui::del_auto *ui;
    MainWindow *main_form;
    QSqlDatabase db_del_auto;
    QSqlQueryModel *model_del;
};

#endif // DEL_AUTO_H
