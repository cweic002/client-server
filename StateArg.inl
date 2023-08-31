
template<typename Obj_t, typename FSave_t, typename FRestore_t,typename Arg, typename Enable_t>
StateArg<Obj_t,FSave_t,FRestore_t,Arg,Enable_t>::StateArg(Obj_t * obj, FSave_t fSave, FRestore_t fRestore):
    _obj(obj),_arg(fSave(obj)),_fSave(fSave),_fRestore(fRestore){};

template<typename Obj_t, typename FSave_t, typename FRestore_t,typename Arg, typename Enable_t>
void inline StateArg<Obj_t,FSave_t,FRestore_t,Arg,Enable_t>::saveState(){
    _arg = _fSave(_obj);
};

template<typename Obj_t, typename FSave_t, typename FRestore_t,typename Arg, typename Enable_t>
void inline StateArg<Obj_t,FSave_t,FRestore_t,Arg,Enable_t>::restoreState() {
    if constexpr (std::is_invocable_v<FRestore_t, Obj_t*, std::add_lvalue_reference_t<Arg>>) {
        _fRestore(_obj, _arg);
    }
    else {
        _fRestore(_arg);
    }
};

template<typename Obj_t, typename FSave_t, typename FRestore_t,typename Arg, typename Enable_t>
StateArg<Obj_t,FSave_t,FRestore_t,Arg,Enable_t>::~StateArg(){};
