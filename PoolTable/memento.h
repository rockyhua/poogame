#ifndef MEMENTO_H
#define MEMENTO_H
#include "poolgame.h"
#include "originator.h"


/**
 * @brief The Memento class is a save state
 */
class Memento
{
public:
    Memento(PoolGame* state);
    ~Memento();

    /**
     * @brief setState can set the current state to a specific state
     * @param state
     */
    void setState(PoolGame* state);

    /**
     * @brief getState can return the current state
     * @return state
     */
    PoolGame* getState();

private:
    friend class Originator;
private:
    PoolGame* m_state;
};

#endif // MEMENTO_H
