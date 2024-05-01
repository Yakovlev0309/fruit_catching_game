QT += core gui widgets multimedia

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        apple.cpp \
        applecore.cpp \
        footer.cpp \
        fruit.cpp \
        game.cpp \
        gameover.cpp \
        health.cpp \
        main.cpp \
        mainmenu.cpp \
        menu.cpp \
        menubutton.cpp \
        pause.cpp \
        pausemenu.cpp \
        pear.cpp \
        player.cpp \
        score.cpp \
        wormapple.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    apple.h \
    applecore.h \
    footer.h \
    fruit.h \
    game.h \
    gameover.h \
    health.h \
    mainmenu.h \
    menu.h \
    menubutton.h \
    pause.h \
    pausemenu.h \
    pear.h \
    player.h \
    score.h \
    wormapple.h

RESOURCES += \
    res.qrc

FORMS += \
    mainmenu.ui \
    pause.ui \
    pausemenu.ui
