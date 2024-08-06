#include "mainwindow.h"
#include <QWidget>
#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include "roles.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    roles w;
    w.show();
    return a.exec();
}
