#include "menubutton.h"
#include <QPainter>

MenuButton::MenuButton(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet(
        "border: 2px solid yellow;"
        "border-radius: 5;"
        "color: yellow; "
        "font: 30px Comic Sans MS;"
        // "QPushButton:hover {color: red;}"
        );
}
