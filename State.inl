

template<typename Obj, typename FSave, typename FRestore,typename>
void State::addState(Obj* obj, FSave fSave, FRestore fRestore){
        stateArg.emplace_back(
                new decltype(StateArg(obj, fSave, fRestore))(obj, fSave, fRestore));
}

