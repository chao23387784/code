#include "mainwindow.h"
#include <QApplication>
//#include "sqliteengine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //SqliteEngine sql;
    //sql.CreateDefaultCrtTables();
    return a.exec();
}
