#include "../lib/interface/MyWindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
    //Creation de l'application
    QApplication app (argc, argv);
    app.setWindowIcon(QIcon("../src/lib/interface/ressources/logo.png"));
    MyWindow window;
    window.show();
    return app.exec();
}
