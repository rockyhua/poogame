#ifndef POOLGAME_H
#define POOLGAME_H

#include <vector>
#include <QPainter>
#include <QSize>

#include "stage2table.h"
#include "ball.h"

#include "changeinpoolgame.h"

/**
 * @brief The PoolGame class runs the pool game, it is in charge of the physics of the pool game as well as
 * drawing the game
 */
class PoolGame
{
public:
    /**
     * @brief PoolGame constructor
     * @param m_table a pointer to a Table object, Poolgame takes ownership of this pointer
     * @param balls a vector of pointers to balls, Poolgame takes ownership of all the contained pointers
     */
    PoolGame(Table * m_table,std::vector<Ball*> balls)
        :m_table(m_table),m_balls(balls)
    {}

    /**
     * @brief PoolGame copy constructor
     * @param poolgame a pointer to a Poolgame object, Poolgame takes ownership of this pointer
     */
    PoolGame(PoolGame *poolgame){
        m_table = new Stage2Table();
        m_table = poolgame->getTable();
        for (Ball* cball:poolgame->getBalls()){
            m_balls.push_back((Ball*)cball->clone());
        }
        player = poolgame->getPlayer();
        player1_score = poolgame->getPlayer1Score();
        player2_score = poolgame->getPlayer2Score();
    }

    ~PoolGame();

    /**
     * @brief simulate one timestep of the game
     * @param timeStep is the period of time that this timestep is simulating
     */
    void simulateTimeStep(float timeStep);

    /**
     * @brief set m_balls to input balls
     * @param a vetor of balls
     */
    void setBalls(std::vector<Ball*> balls);

    /**
     * @brief get m_balls
     * @return a vetor of balls
     */
    std::vector<Ball*> getBalls();

    /**
     * @brief set m_table to input table
     * @param table
     */
    void setTable(Table* table);

    /**
     * @brief get table
     * @return table
     */
    Table* getTable();

    /**
     * @brief draws all elements of the game, table and balls in that order
     * @param p is the painter which is used to paint the object
     */
    void draw(QPainter &p);

    /**
     * @brief size
     * @return the size of the game
     */
    QSize size(){return QSize(m_table->width(),m_table->height());}

    /**
     * @brief set current player number
     * @param i
     */
    void setPlayer(int i){player = i;}

    /**
     * @brief get current player number
     * @return player
     */
    int getPlayer(){return player;}

    /**
     * @brief set player 1 score
     * @param i
     */
    void setPlayer1Score(int i){player1_score = i;}

    /**
     * @brief get player 1 score
     * @return player1_score
     */
    int getPlayer1Score(){return player1_score;}

    /**
     * @brief set player 2 score
     * @param i
     */
    void setPlayer2Score(int i){player2_score = i;}

    /**
     * @brief get player 2 score
     * @param player2_score
     */
    int getPlayer2Score(){return player2_score;}

private:
    /**
     * @brief collide two balls if they are in contact
     * @param b1
     * @param b2
     * @return the change in the pool game after the collision
     */
    ChangeInPoolGame collide(Ball *b1, Ball *b2);


    Table * m_table;
    std::vector<Ball*> m_balls;
    int player=1;
    int player1_score = 0;
    int player2_score = 0;
};

#endif // POOLGAME_H
