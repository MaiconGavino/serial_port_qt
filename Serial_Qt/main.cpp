#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setFixedSize(296,208);
    w.setWindowTitle("Acionadores");
    w.show();
    return a.exec();
}
