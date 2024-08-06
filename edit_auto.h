#ifndef EDIT_AUTO_H
#define EDIT_AUTO_H

#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class edit_auto;
}
class MainWindow; //Forward declaration
class edit_auto : public QWidget
{
    Q_OBJECT

public:
    explicit edit_auto(QWidget *parent = nullptr);
    void connectToPSql_edit_auto();
    ~edit_auto();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_poisk_clicked();

    void on_pushButton_edit_clicked();

private:
    Ui::edit_auto *ui;
    MainWindow *main_form;
    QSqlDatabase db_edit_auto;
};

#endif // EDIT_AUTO_H
