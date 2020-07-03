#include "memento.h"

Memento::Memento(PoolGame* state):m_state(state){}

Memento::~Memento(){
    delete m_state;
}

void Memento::setState(PoolGame* state){
    m_state = state;
}

PoolGame *Memento::getState(){
    return m_state;
}
