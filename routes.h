#ifndef ROUTES_H
#define ROUTES_H

#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
namespace Ui {
class routes;
}
class MainWindow; //Forward declaration

class routes : public QWidget
{
    Q_OBJECT

public:
    explicit routes(QWidget *parent = nullptr);
    ~routes();
    void connectToPSql_routes();

private slots:
    void on_pushButton_clicked();

private:
    Ui::routes *ui;
    MainWindow *main_form_routes;
    QSqlQueryModel *model_routes;
    QSqlQuery *gry_routes;
    QSqlDatabase db_routes;
};

#endif // ROUTES_H
