#ifndef CUEBALLDECORATOR_H
#define CUEBALLDECORATOR_H
#include "balldecorator.h"

#include "dialog.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class Dialog;
/**
 * @brief The CueBallDecorator class is the decorator that turns a ball into a cue ball
 */
class CueBallDecorator : public BallDecorator, public QObject
{
public:
    /**
     * @brief CueBallDecorator decorates a ball to be used as a cue ball
     * @param b is the ball to be decorated
     * @param parent is the parent Dialog, this is used to connect to the signals it emits
     */
    CueBallDecorator(Ball * b, Dialog * parent);
    void draw(QPainter &p);
    Prototype* clone(){
        Ball* b = (Ball*)m_ball->clone();
        return b;
    }
public slots:
    void mousePressed(QMouseEvent * event);
    void mouseMoved(QMouseEvent * event);
    void mouseReleased(QMouseEvent * event);
    void setCueBall(Ball* ball);

private:
    QVector2D endpoint;
    QVector2D mousePos;
    bool clicked;
};

#endif // CUEBALLDECORATOR_H
