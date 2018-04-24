
#include <QApplication>
#include "window.h"
#include <QtGui/QtGui>
#include"dialog.h"

int main(int argv, char *args[])
{
    QApplication app(argv, args);


    CLoginDlg dlg;




    dlg.show();
    return app.exec();
}
