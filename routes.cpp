#include "routes.h"
#include "ui_routes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>

routes::routes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::routes)
{
    ui->setupUi(this);
    model_routes = new QSqlQueryModel;
    connectToPSql_routes();
}

routes::~routes()
{
    delete model_routes;
    delete gry_routes;
    delete ui;
}

void routes::connectToPSql_routes()
{
    db_routes = QSqlDatabase::addDatabase("QPSQL", "routes_connect");
    db_routes.setHostName("127.0.0.1");
    db_routes.setPort(5432);
    db_routes.setUserName("postgres"); //username
    db_routes.setPassword("qwerty"); //password
    db_routes.setDatabaseName("tranzit"); //Name database
    if(db_routes.open()){
        QSqlQuery query(db_routes);
        if (query.exec("SELECT punkt_otpravlenia, punkt_naznachenia, data_routes, time_otpravlenia, time_pribetia FROM routes")){
            model_routes->setQuery(query);
            model_routes->setHeaderData(0, Qt::Horizontal, tr("Пункт отправления"));
            model_routes->setHeaderData(1, Qt::Horizontal, tr("Пункт назначения"));
            model_routes->setHeaderData(2, Qt::Horizontal, tr("Дата маршрута"));
            model_routes->setHeaderData(3, Qt::Horizontal, tr("Время отправления"));
            model_routes->setHeaderData(4, Qt::Horizontal, tr("Время прибытия"));

            ui->tableView->setModel(model_routes);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else {
                QSqlError error = query.lastError();
                qDebug() << "Error executing query: " << error.text();
            }
    }
    else {
    }
    db_routes.close();

}

void routes::on_pushButton_clicked()
{
    main_form_routes = new MainWindow();
    main_form_routes -> show();
    this->close();
}

