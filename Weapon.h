#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QWidget>


class Weapon: public QGraphicsRectItem, public QObject {

public:
    Weapon(qreal x, qreal y, qreal w, qreal h, QWidget *parent = 0) :
        QGraphicsRectItem (x, y, w, h),
        QObject(parent) {
        //setBrush(Qt::blue);
    }

};

#endif // WEAPON_H
