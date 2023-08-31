#ifndef STATE_H
#define STATE_H

#include<list>
#include<StateArg.h>

class State{
    std::list<IStateArg*> stateArg;
public:
    template<typename Obj, typename FSave, typename FRestore,
        typename = decltype(StateArg(std::declval<Obj*>(),std::declval<FSave>(),std::declval<FRestore>()))>
    void addState(Obj* obj, FSave fSave, FRestore fRestore);
    void saveState();
    void restoreState();
    ~State();
};

#include "State.inl"

#endif // STATE_H
