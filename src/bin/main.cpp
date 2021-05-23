#include <QApplication>
#include <QIcon>

#include "../lib/interface/MyWindow.hpp"

int main(int argc, char **argv)
{
    //Creation de l'application
    QApplication app (argc, argv);
    app.setWindowIcon(QIcon("../src/lib/interface/ressources/logo.png"));
    MyWindow* window = new MyWindow();
    window->show();
    return app.exec();
}
