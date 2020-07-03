#include "dialog.h"

#include <QPainter>
#include <QSize>
#include <qdebug.h>
#include <iostream>
#include <QStatusBar>


constexpr float fps = 60;
constexpr float timeStep = 0.01;

Dialog::Dialog(QWidget *parent)
    :QDialog(parent),m_game(nullptr),m_framerateTimer(new QTimer()),m_timestepTimer(new QTimer()){}

void Dialog::start(PoolGame *game)
{
    m_game = game;

    if (m_mementos.empty()){
        PoolGame* state = new PoolGame(m_game);
        m_origin->setState(state);
        m_mementos.push_back(m_origin->save());

        this->setMinimumSize(m_game->size());
        this->resize(m_game->size());
        connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
        connect(m_timestepTimer,SIGNAL(timeout()),this,SLOT(runSimulationStep()));
        m_framerateTimer->start(1000/fps);
        m_timestepTimer->start(1000*timeStep);
    }

    for (Ball* cball : m_game->getBalls()){
        if(cball->colour().name().toStdString() == "#ffffff"){
            m_cueball = static_cast<CueBallDecorator* >(cball);
        }
    }
}

Ball* Dialog::getCueball(){
    return m_cueball;
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    m_game->draw(p);
    drawStick(p);
    drawUI(p);
    drawScoreBoard(p);
}

void Dialog::drawScoreBoard(QPainter &p){
    if(scoreBoard){
        p.setPen(Qt::white);
        p.drawRect((m_game->getTable()->width()/2)+50,50,150,225);
        p.drawLine((m_game->getTable()->width()/2)+50,85,(m_game->getTable()->width()/2)+200,85);
        p.drawLine((m_game->getTable()->width()/2)+125,50,(m_game->getTable()->width()/2)+125,275);

        p.drawText((m_game->getTable()->width()/2)+70,70,tr("Player 1"));
        p.drawText((m_game->getTable()->width()/2)+145,70,tr("Player 2"));

        QString p1 = QString::fromStdString(std::to_string(m_game->getPlayer1Score()));
        QString p2 = QString::fromStdString(std::to_string(m_game->getPlayer2Score()));
        p.drawText((m_game->getTable()->width()/2)+85,105,p1);
        p.drawText((m_game->getTable()->width()/2)+160,105,p2);

    }
}

void Dialog::drawStick(QPainter &p){
    if(pressed){
        p.drawLine(mousePos.toPointF(),m_cueball->position().toPointF());
    }
}

void Dialog::drawUI(QPainter &p){
    if(m_cueball->velocity().x()==0 && m_cueball->velocity().y()==0){
        p.setPen(Qt::white);
        if(m_game->getPlayer()==1){
            p.drawText((m_game->getTable()->width()/2)-25,m_game->getTable()->height()/2,tr("Player1 Ready!"));
        }
        else if(m_game->getPlayer() == 2){
            p.drawText((m_game->getTable()->width()/2-25),m_game->getTable()->height()/2,tr("Player2 Ready!"));
        }
    }
    int count = 0;
    for(Ball* b : m_game->getBalls()){
        if(b->colour().name().toStdString() != "#ffffff"){
            count++;
            continue;
        }
    }
    if(count == m_game->getBalls().size()){
        p.setPen(Qt::white);
        p.drawText((m_game->getTable()->width()/2)-50,m_game->getTable()->height()/2,tr("Press R to restart!"));
    }
    if(m_game->getBalls().size()==1 && m_game->getBalls()[0]->colour().name().toStdString()=="#ffffff"){
        if(m_game->getPlayer1Score()>m_game->getPlayer2Score()){
            p.setPen(Qt::white);
            p.drawText((m_game->getTable()->width()/2)-50,m_game->getTable()->height()/2,tr("Player 1 win!!!"));
        }
        else if(m_game->getPlayer2Score()>m_game->getPlayer1Score()){
            p.setPen(Qt::white);
            p.drawText((m_game->getTable()->width()/2)-50,m_game->getTable()->height()/2,tr("Player 2 win!!!"));
        }
        else{
            p.setPen(Qt::white);
            p.drawText((m_game->getTable()->width()/2)-50,m_game->getTable()->height()/2,tr("Draw"));
        }
    }
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    if(m_cueball->velocity().x()==0 && m_cueball->velocity().y()==0
            && (QVector2D(event->pos())-m_cueball->position()).length() < m_cueball->radius()
            && event->button() == Qt::LeftButton){
        pressed = true;
        PoolGame* state = new PoolGame(m_game);
        m_origin->setState(state);
        m_mementos.push_back(m_origin->save());
        mousePos = QVector2D(event->pos());
    }
    emit mousePressed(event);
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if(pressed)
    {
        mousePos = QVector2D(event->pos());
    }

    emit mouseMoved(event);
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(pressed)
    {
        if(m_game->getPlayer()==1){
            m_game->setPlayer(2);
        }else{
            m_game->setPlayer(1);
        }
        pressed = false;
        m_cueball->setVelocity(4*(m_cueball->position()-mousePos));
    }
    emit mouseReleased(event);
}

void setCueBall(Ball* ball){
    emit setCueBall(ball);
}

void Dialog::keyPressEvent(QKeyEvent* event){
    if(event->key()==Qt::Key_R && m_mementos.size()>0){
        int count = 0;
        int p1=0;
        int p2=0;
        for(Ball* b : m_game->getBalls()){
            if(b->colour().name().toStdString() != "#ffffff"){
                count++;
                continue;
            }
        }
        if(count == m_game->getBalls().size()){
            p1=m_game->getPlayer1Score();
            p2=m_game->getPlayer2Score();
        }

        m_origin->restore(m_mementos[m_mementos.size()-1]);
        m_game = new PoolGame(m_origin->getState());
        m_game->setPlayer1Score(p1);
        m_game->setPlayer2Score(p2);
        start(m_game);
        setCueBall(m_cueball);
    }
    else if(event->key()==Qt::Key_Tab){
        scoreBoard = true;
    }
}

void Dialog::keyReleaseEvent(QKeyEvent *event){
    if(scoreBoard==true){
        scoreBoard = false;
    }
}

Dialog::~Dialog()
{
    delete m_game;
    delete m_framerateTimer;
    delete m_timestepTimer;
    delete m_cueball;;
}

void Dialog::runSimulationStep()
{
    m_game->simulateTimeStep(timeStep);
}
