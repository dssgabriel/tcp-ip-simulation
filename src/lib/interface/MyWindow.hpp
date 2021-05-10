#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "MenuEntete.hpp"
#include "FenetreReseau.hpp"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>

class MyWindow : public QWidget
{
Q_OBJECT
    private:
        // Attributs
        MenuEntete* m_F1;

        FenetreReseau* m_F2;

        QVBoxLayout* m_Vlayout;

    public:
    // Constructeur
    MyWindow();

    // Destructeur
    ~MyWindow();

};

#endif // MYWINDOW_H
