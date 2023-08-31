#include "State.h"

void State::saveState(){
    for(auto & iter : stateArg){
        iter->saveState();
    }
}

void State::restoreState() {
    for (auto & iter : stateArg) {
        iter->restoreState();
    }
}

State::~State(){
    for (auto& iter : stateArg){
        delete iter;
    }
};
