#include "menubutton.h"
#include <QPainter>

MenuButton::MenuButton(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet(
        "QPushButton {"
        "   border: 3px solid yellow;"
        "   border-radius: 10;"
        "   color: yellow;"
        "   font: 24px Comic Sans MS;"
        "   padding: 4px;"
        "   margin: 4px"
        "}"
        "QPushButton:pressed {"
        "   border: 3px solid orange;"
        "   color: orange;"
        "}"
        // "QPushButton:hover {"
        // "   border: 3px solid #ADFF2F;"
        // "   color: #ADFF2F;"
        // "}"
        );
}
