#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0, width() ,ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    world->SetContactListener(this);
    // Setting Size
    GameItem::setGlobalSize(QSizeF(16*3,9*3),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(8*3,1.5,48,3,QPixmap(":/ground.png").scaled(width(),height()/7.0),world,scene));
    // Create slingshot
    itemList.push_back(new Slingshot(2.5 ,7  ,0.0001 ,0.0001,QPixmap(":/image/Slingshot.png").scaled(50,100),world,scene));
    //test obstacle
    itemList.push_back(new obstacle_rotate(15,10,0.2,3.0,&timer,QPixmap(":/image/stick.png").scaled(80,60),world,scene));
    //construct house
    itemList.push_back(new Wood(37,9, 16*3.5/54 *1.5 , 9*2.5/10.5 ,&timer,QPixmap(":/image/rec_ver_wood.png").scaled(width()/30,height()/5),world,scene));
    itemList.push_back(new Wood(46,9, 16*3.5/54 *1.5 , 9*2.5/10.5 ,&timer,QPixmap(":/image/rec_ver_wood.png").scaled(width()/30,height()/5),world,scene));
    itemList.push_back(new Wood(42.5, 12 , 9*2.5/10.5 , 16*3.5/54 *1.5 ,&timer,QPixmap(":/image/rec_hor_wood.png").scaled(height()/5,width()/30),world,scene));
    itemList.push_back(new Wood(-2.0 , 0.0, 1.0 ,27.0  ,&timer,QPixmap(":/image/rec_ver_wood.png").scaled(width()/30,height()/5),world,scene));
    itemList.push_back(new Wood(50 , 0.0, 1.0 ,27.0  ,&timer,QPixmap(":/image/rec_ver_wood.png").scaled(width()/30,height()/5),world,scene));

// unsureZzszs
    scoreboard = new QLabel(this);
    scoreboard->setStyleSheet("color:black; background-color: transparent; font: 32pt Comic Sans MS");
    scoreboard->setText("0");
    scoreboard->setGeometry(800, 30, 100, 50);
    scoreboard->show();

//huge pig king
//    pig *piggy = new pig(24.0f,4.5*2.5f,0.4f,&timer,QPixmap(":/image/Pig_normal.png").scaled(height(),height()),world,scene);
//    itemList.push_back(piggy);
    // to test a jumping pig full restitution
    piggy2 = new pig(20.0f, 10.0f,0.5f,&timer,QPixmap(":/image/Pig_normal.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(piggy2);
    piggy3 = new pig(20.0f, 15.0f,0.5f,&timer,QPixmap(":/image/Pig_normal.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(piggy3);
    piggy4 = new pig(20.0f, 18.0f,0.5f,&timer,QPixmap(":/image/Pig_normal.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(piggy4);
    piggy5 = new pig(20.0f, 24.0f,0.5f,&timer,QPixmap(":/image/Pig_normal.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(piggy5);
    piggy6 = new pig(20.0f, 21.0f,0.5f,&timer,QPixmap(":/image/Pig_normal.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(piggy6);

    //creat bird
    birdie1 = new bird_red(0.0f,10.0f,0.5f,&timer,QPixmap(":/bird.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(birdie1);
    birdie2 = new bird_blue(90.0f,10.0f,0.5f,&timer,QPixmap(":/image/bird_blue.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(birdie2);
    birdie3 = new bird_yello(80.0f,10.0f,0.5f,&timer,QPixmap(":/image/angry_yellow.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(birdie3);
    birdie4 = new bird_yello(70.0f,10.0f,0.5f,&timer,QPixmap(":/image/angry_white.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(birdie4);
    birdie5 = new bird_black(60.0f,10.0f,0.5f,&timer,QPixmap(":/image/angry_black.png").scaled(height()/12.0,height()/12.0),world,scene);
    itemList.push_back(birdie5);

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

//--------------- do something special... music ? add score
void MainWindow::BeginContact(b2Contact* contact){
    void* bodyuserdata = contact->GetFixtureA()->GetBody()->GetUserData();
    if(bodyuserdata)
        static_cast<GameItem*>(bodyuserdata)->collide();

    bodyuserdata = contact->GetFixtureB()->GetBody()->GetUserData();
    if(bodyuserdata)
        static_cast<GameItem*>(bodyuserdata)->collide();
    if( static_cast<GameItem*>(bodyuserdata)->get_numCollideA() == 1)
        score += 100; static_cast<GameItem*>(bodyuserdata)->set_numCollideA();
}

void MainWindow::EndContact(b2Contact *contact){
/*    void* bodyuserdata = contact->GetFixtureA()->GetBody()->GetUserData();

    bodyuserdata = contact->GetFixtureA()->GetBody()->GetUserData();
    if(bodyuserdata){
        static_cast<pig*>(bodyuserdata)->endContacting();std::cout<<"  endContacting"<<std::endl;}
*/
}

//--------------lack  skill and new happen at th sane time
bool MainWindow::eventFilter(QObject *, QEvent *event)
{

    if(event->type() == QEvent::MouseButtonPress)
    {
        if(Mode == 0) Mode = 1; //enter mouseButtonPress
        if( count_birdie == 1 ){
            if (!ifshoot) {birdie1->setPosition(2.5 , 8.0); ifshoot = true;}
            //invoke skill or not
            if (Mode == 2){
                if(birdie1->getLinearVelocity() == b2Vec2(0,0) ){
                   Mode = 0; ++count_birdie; ifshoot = false;
                }
                else{Mode = 0; ++count_birdie; ifshoot = false;birdie1->skill(); return false;
                }
            }
        }
        else if( count_birdie == 2 ){
            if (!ifshoot) {birdie2->setPosition(2.5 , 8.0); ifshoot = true;}
            //invoke skill or not
            if (Mode == 2){
                if(birdie1->getLinearVelocity() == b2Vec2(0,0) ){
                   Mode = 0; ++count_birdie; ifshoot = false;
                }
                else{static_cast<bird_blue  *>(birdie2)->setxy_blue(birdie2->getPosition(),birdie2->getLinearVelocity());
                    birdie2->skill();Mode = 0; ++count_birdie; ifshoot = false; return false;
                }
            }
        }
        else if( count_birdie == 3 ){
            if (!ifshoot) {birdie3->setPosition(2.5 , 8.0); ifshoot = true;}
            //invoke skill or not
            if (Mode == 2){
                if(birdie3->getLinearVelocity() == b2Vec2(0,0) ){
                   Mode = 0; ++count_birdie; ifshoot = false;
                }
                else{birdie3->skill();  Mode = 0; ++count_birdie; ifshoot = false; return false;
                }
            }
        }
        else if( count_birdie == 4 ){
            if (!ifshoot) {birdie4->setPosition(2.5 , 8.0); ifshoot = true;}
            //invoke skill or not
            if (Mode == 2){
                if(birdie4->getLinearVelocity() == b2Vec2(0,0) ){
                   Mode = 0; ++count_birdie; ifshoot = false;
                }
                else{birdie4->skill();  Mode = 0; ++count_birdie; ifshoot = false; return false;
                }
            }
        }
        else if( count_birdie == 5 ){
            if (!ifshoot) {birdie5->setPosition(2.5 , 8.0); ifshoot = true;}
            //invoke skill or not
            if (Mode == 2){
                if(birdie5->getLinearVelocity() == b2Vec2(0,0) ){
                   Mode = 0; ++count_birdie; ifshoot = false;
                }
                else{birdie5->skill();  Mode = 0; ++count_birdie; ifshoot = false; return false;
                }
            }
        }
    }
    if(event->type() == QEvent::MouseMove)
    {
        // when mouse is pressing
        if(Mode == 1){
            if(count_birdie == 1){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
                X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                birdie1->setPosition( X , Y );
                std::cout<<" x = "<<me->x()<<"  y = "<<me->y()<<std::endl;
                std::cout<<" x = "<<X<<"  y.fix = "<<Y<<std::endl;
            }
            else if(count_birdie == 2){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
//                if ( birdie1->getLinearVelocity() == b2Vec2(0,0)){
                    X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                    Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                    birdie2->setPosition( X , Y );
                    std::cout<<" x = "<<me->x()<<"  y = "<<me->y()<<std::endl;
                    std::cout<<" x = "<<X<<"  y.fix = "<<Y<<std::endl;
//                }
            }
            else if(count_birdie == 3){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
//                if ( birdie2->getLinearVelocity() == b2Vec2(0,0)){
                    X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                    Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                    birdie3->setPosition( X , Y );
                    std::cout<<" x = "<<me->x()<<"  y = "<<me->y()<<std::endl;
                    std::cout<<" x = "<<X<<"  y.fix = "<<Y<<std::endl;
//                }
            }
            else if(count_birdie == 4){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
//                if ( birdie3->getLinearVelocity() == b2Vec2(0,0)){
                    X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                    Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                    birdie4->setPosition( X , Y );
                    std::cout<<" x = "<<me->x()<<"  y = "<<me->y()<<std::endl;
                    std::cout<<" x = "<<X<<"  y.fix = "<<Y<<std::endl;
//                }
            }
            else if(count_birdie == 5){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
//                if ( birdie4->getLinearVelocity() == b2Vec2(0,0)){
                    X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                    Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                    birdie5->setPosition( X , Y );
                    std::cout<<" x = "<<me->x()<<"  y = "<<me->y()<<std::endl;
                    std::cout<<" x = "<<X<<"  y.fix = "<<Y<<std::endl;
//                }
            }
        }
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if (Mode ==1){
            if(count_birdie == 1){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
                X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                birdie1->setGravity();
                birdie1->setLinearVelocity(b2Vec2( (2.5 -X)*15.0  , (8.0-Y)*15.0 ));
                Mode = 2; //release press , able to skill
            }
            else if(count_birdie == 2){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
                X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                birdie2->setGravity();
                birdie2->setLinearVelocity(b2Vec2((2.5 -X)*15.0  , (8.0-Y)*15.0));
                Mode = 2; //release press , able to skill
            }
            else if(count_birdie == 3){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
                X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                birdie3->setGravity();
                birdie3->setLinearVelocity(b2Vec2((2.5 -X)*15.5  , (8.0-Y)*15.5));
                Mode = 2; //release press , able to skill
            }
            else if(count_birdie == 4){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
                X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                birdie4->setGravity();
                birdie4->setLinearVelocity(b2Vec2((2.5 -X)*15.0  , (8.0-Y)*15.0));
                Mode = 2; //release press , able to skill
            }
            else if(count_birdie == 5){
                QMouseEvent *me = static_cast<QMouseEvent *>(event);
                X = me->x() /50.0 ; if(X>3.5)X=3.5; if(X<1.5)X=1.5;
                Y = -(me->y()-520.0 ) /50.0; if(Y>10.0)Y=10.0; if (Y<7.0)Y=7.0;
                birdie5->setGravity();
                birdie5->setLinearVelocity(b2Vec2((2.5 -X)*15.0  , (8.0-Y)*15.0));
                Mode = 2; //release press , able to skill
            }
        }

    }
    return false;
}

/*
bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
      //std::cout << "Press !" << std::endl ;
        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        std::cout<<"Now X = "<<me->x()<<",  Now Y = " <<me->y()<<std::endl;

        Bird *birdie1 = new bird_red( me->x()*22.5/950 , me->y()*48/500, 0.5f ,&timer,QPixmap(":/bird.png").scaled(height()/12.0,height()/12.0),world,scene);
        birdie1->offsetGravity();
        itemList.push_back(birdie1);
        while( event->type() != QEvent::MouseButtonRelease )
        {
            birdie1->setPosition( me->x(), me->y());
        }
    }

    if(event->type() == QEvent::MouseMove)
    {
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        //std::cout << "Release !" << std::endl ;

    }
    return false;
}  */

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();

    if(count_birdie == 6 && birdie5->getLinearVelocity() == b2Vec2_zero){
        QString result;
        QTextStream(&result) << "Your score : " << score << "\n\n  Try again ?";
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Gameover !!", result, QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::No) exitGame(); //end game
        else restartGame();
    }
}

void MainWindow::restartGame(){
    std::cout<<"enter restart"<<std::endl;
    count_birdie = 1;
    score =0;
    Mode = 0;
    ifshoot = false;
    piggy2->stop();piggy3->stop();piggy4->stop();piggy5->stop();piggy6->stop();
    birdie1->stop();birdie2->stop();birdie3->stop();birdie4->stop();birdie5->stop();
    birdie1->setPosition(100.0f,100.0f);birdie2->setPosition(90.0f,90.0f);birdie3->setPosition(40.0f,50.0f);birdie4->setPosition(70.0f,80.0f);birdie5->setPosition(60.0f,70.0f);
    piggy2->setPosition(20.00f , 10.0f);piggy3->setPosition(20.00f , 15.0f);piggy4->setPosition(20.00f , 18.0f);piggy5->setPosition(20.00f , 21.0f);piggy6->setPosition(20.00f , 24.0f);
    piggy2->setGravity();piggy3->setGravity();piggy4->setGravity();piggy5->setGravity();piggy6->setGravity();
}


void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::exitGame(){
    close();
}
