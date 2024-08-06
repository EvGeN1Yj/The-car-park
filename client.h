#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include "mainwindow.h"


namespace Ui {
class client;
}
class roles; //Forward declaration
class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    void connectToPSql_client();
    ~client();

private slots:
    void on_pushButton_clicked();

private:
    Ui::client *ui;
    roles *roles_form;
    QSqlQueryModel *model_client;
    QSqlQuery *gry_client;
    QSqlDatabase db_client;


};

#endif // CLIENT_H
