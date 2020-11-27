#include <QApplication>
#include <QGraphicsScene>
#include <Player.h>
#include <QGraphicsView>
#include <QTimer>
#include <Widget.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    new Widget();
    return a.exec();
}
