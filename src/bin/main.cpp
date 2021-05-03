#include "../lib/interface/MyWindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
    //Creation de l'application
    QApplication app (argc, argv);
    MyWindow window;
    window.show();
    return app.exec();
}
