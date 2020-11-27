QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bonus.cpp \
    Bullet.cpp \
    BulletEnemy.cpp \
    CustomGraphicsView.cpp \
    Enemy.cpp \
    Player.cpp \
    PlayerStateDuration.cpp \
    Weapon.cpp \
    Widget.cpp \
    main.cpp

HEADERS += \
    Bonus.h \
    Bullet.h \
    BulletEnemy.h \
    CustomGraphicsView.h \
    Enemy.h \
    EnemySlot.h \
    Player.h \
    PlayerState.h \
    PlayerStateDuration.h \
    Weapon.h \
    Widget.h
RESOURCES += \
        resources/cursor.qrc
FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
