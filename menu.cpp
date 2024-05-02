#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    setStyleSheet(
        "QWidget {"
        "   background-color: transparent;"
        "   border-radius: 10;"
        "   color: yellow;"
        "   font: 24px Comic Sans MS;"
        "   padding: 4px;"
        "   margin: 4px"
        "}"
        "QPushButton, QLineEdit {"
        "   border: 3px solid yellow;"
        "}"
        "QPushButton:pressed {"
        "   border: 3px solid orange;"
        "   color: orange;"
        "}"
        );
}

// "QPushButton:hover {"
// "   border: 3px solid #ADFF2F;"
// "   color: #ADFF2F;"
// "}"
