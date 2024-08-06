#include "client.h"
#include "ui_client.h"
#include "roles.h"
#include <QSqlError>
#include <QApplication>

client::client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    connectToPSql_client();
    model_client = new QSqlQueryModel;
}

void client::connectToPSql_client()
{
    db_client = QSqlDatabase::addDatabase("QPSQL");
    db_client.setHostName("127.0.0.1");
    db_client.setPort(5432);
    db_client.setUserName("client__user"); //username
    db_client.setPassword("111"); //password
    db_client.setDatabaseName("tranzit"); //Name database
    if(db_client.open()){
        QSqlQuery query(db_client);
        if (query.exec("SELECT punkt_otpravlenia, punkt_naznachenia, data_routes, time_otpravlenia, time_pribetia FROM routes")){
            model_client->setQuery(query);
            model_client->setHeaderData(0, Qt::Horizontal, tr("Пункт отправления"));
            model_client->setHeaderData(1, Qt::Horizontal, tr("Пункт назначения"));
            model_client->setHeaderData(2, Qt::Horizontal, tr("Дата маршрута"));
            model_client->setHeaderData(3, Qt::Horizontal, tr("Время отправления"));
            model_client->setHeaderData(4, Qt::Horizontal, tr("Время прибытия"));

            ui->tableView->setModel(model_client);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else {
                QSqlError error = query.lastError();
                qDebug() << "Error executing query: " << error.text();
            }
    }
    else {
    }
    //db_client.close();
}

client::~client()
{
    delete model_client;
    delete gry_client;
    delete ui;
}

void client::on_pushButton_clicked()
{
    roles_form = new roles();
    roles_form -> show();
    this->close();

}

