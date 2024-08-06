#ifndef ROLES_H
#define ROLES_H

#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <mainwindow.h>
#include <client.h>

namespace Ui {
class roles;
}


class roles : public QWidget
{
    Q_OBJECT

public:
    explicit roles(QWidget *parent = nullptr);
    ~roles();


private slots:
    void on_pushButton_admin_clicked();
    void on_pushButton_client_clicked();


private:
    Ui::roles *ui;
    QSqlDatabase db_roles;
    QSqlQueryModel *model_roles;
    MainWindow *mainwindow_form;
    client *client_form;
};

#endif // ROLES_H
