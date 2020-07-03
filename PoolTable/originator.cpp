#include "originator.h"

Originator::Originator(PoolGame *state) : m_state(state){}

Originator::~Originator(){}

void Originator::setState(PoolGame* state){
    m_state = state;
}

PoolGame *Originator::getState(){
    return m_state;
}

Memento* Originator::save(){
    return new Memento(m_state);
}

void Originator::restore(Memento* m){
    m_state = m->getState();
}
