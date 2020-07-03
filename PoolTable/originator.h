#ifndef ORIGINATOR_H
#define ORIGINATOR_H
#include "memento.h"
#include "ball.h"

class Memento;
/**
 * @brief The Originator class can save and revert back from last state.
 */
class Originator
{
public:
    Originator(PoolGame* state);
    ~Originator();
    /**
     * @brief setState can set the current state to a specific state
     * @param state
     */
    void setState(PoolGame* state);

    /**
     * @brief getState return the current state
     * @return state
     */
    PoolGame* getState();

    /**
     * @brief save will create a new memento as a state
     * @return memento
     */
    Memento* save();

    /**
     * @brief restore can revert back from the input memento
     * @param m
     */
    void restore(Memento* m);
private:
    PoolGame* m_state;
};

#endif // ORIGINATOR_H
