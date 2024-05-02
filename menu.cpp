#include "menu.h"
#include <QTableWidgetItem>

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
        "QWidget {"
        "   border: 3px solid yellow;"
        "}"
        "QLabel {"
        "   border: 0px solid black;"
        "}"
        "QPushButton:pressed {"
        "   border: 3px solid orange;"
        "   color: orange;"
        "}"
        "QTableWidget, QHeaderView {"
        "   text-align: center;"
        "   background-color: white;"
        "   color: black;"
        "}"
        );
}

// "QPushButton:hover {"
// "   border: 3px solid #ADFF2F;"
// "   color: #ADFF2F;"
// "}"
