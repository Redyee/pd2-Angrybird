#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <QMessageBox>
#include <QTextStream>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <mycontactlistener.h>
#include <qlabel.h>

#include <gameitem.h>
#include <land.h>
#include <obstacle_rotate.h>
#include <bird.h>
#include <bird_red.h>
#include <bird_black.h>
#include <bird_yello.h>
#include <bird_white.h>
#include <bird_blue.h>
#include <pig.h>
#include <slingshot.h>
#include <wood.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow , MyContactListener
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void restartGame();
    Bird *birdie1;
    Bird *birdie2;
    Bird *birdie3;
    Bird *birdie4;
    Bird *birdie5;
    pig *piggy2;
    pig *piggy3;
    pig *piggy4;
    pig *piggy5;
    pig *piggy6;
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    QLabel *scoreboard;
    QTextStream *report;
    void exitGame();

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    int score =0;
    int count_birdie = 1;
    int Mode = 0;
    bool ifshoot = false;
    float X ,Y ;
};

#endif // MAINWINDOW_H
