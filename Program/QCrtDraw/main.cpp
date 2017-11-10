#include "mainwindow.h"
#include <QApplication>
#include "crtstyle.h"
//#include "sqliteengine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyle(new CrtStyle());
    MainWindow w;
    w.show();
    //SqliteEngine sql;
    //sql.CreateDefaultCrtTables();
    return a.exec();
}
