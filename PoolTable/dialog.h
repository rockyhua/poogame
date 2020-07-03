#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QMouseEvent>
#include "poolgame.h"
#include "memento.h"
#include "cueballdecorator.h"

class CueBallDecorator;
/**
 * @brief The Dialog class starts up and displays a poolgame
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Dialog constructor
     * @param game is a pointer to a PoolGame, this takes ownership of that pointer
     * @param parent is the parent widget
     */
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    /**
     * @brief starts the simulation
     */
    void start(PoolGame * game);

    /**
     * @brief draws the simulation
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief mousePressEvent just emits the mousePressed signal
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mousePressEvent just emits the mouseMoved signal
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief mousePressEvent just emits a mouseReleased signal
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief KeyPressEvent will identify two different key, "R" key will revert the game
     * , "Tab" key will show the score board
     * @param event
     */
    void keyPressEvent(QKeyEvent* event);

    /**
     * @brief KeyReleaseEvent will cancel the display of score board when "Tab" key is released
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event);

    /**
     * @brief getCueball will return private cue ball.
     * @return m_cueball
     */
    Ball* getCueball();

    /**
     * @brief drawStick will draw a hitting sitck
     * @param p
     */
    void drawStick(QPainter &p);

    /**
     * @brief drawUI will shows the game status.
     * @param p
     */
    void drawUI(QPainter &p);

    /**
     * @brief drawStick will draw score board of two players
     * @param p
     */
    void drawScoreBoard(QPainter &p);

signals:
    void mousePressed(QMouseEvent * event);
    void mouseMoved(QMouseEvent * event);
    void mouseReleased(QMouseEvent * event);
    void setCueBall(Ball* ball);

public slots:
    void runSimulationStep();
private:
    bool scoreBoard = false;
    QVector2D endpoint;
    QVector2D mousePos;
    PoolGame * m_game;
    QTimer * m_framerateTimer;
    QTimer * m_timestepTimer;
    std::vector<Memento* > m_mementos;
    Originator* m_origin;
    CueBallDecorator* m_cueball;
    bool pressed = false;
    QVector2D mousepos;
};

#endif // DIALOG_H
