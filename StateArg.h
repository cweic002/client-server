#ifndef STATEARG_H
#define STATEARG_H

#include <type_traits>

struct IStateArg {
    virtual void saveState() = 0;
    virtual void restoreState() = 0;
    virtual ~IStateArg() {}
};

template<typename Obj_t, typename FSave_t, typename FRestore_t,typename Arg = std::invoke_result_t<FSave_t, Obj_t*>,
    typename = std::enable_if_t<
    std::is_invocable_v<FRestore_t, Obj_t*, std::add_lvalue_reference_t<Arg>> ||
    std::is_invocable_v<FRestore_t,std::add_lvalue_reference_t<Arg>>>>
class StateArg : public IStateArg {
    Obj_t* _obj;
    Arg _arg;
    FSave_t _fSave;
    FRestore_t _fRestore;
public:
    StateArg(Obj_t * obj, FSave_t fSave, FRestore_t fRestore);
    void inline saveState() override;
    void inline restoreState() override ;
    ~StateArg();
};

#include<StateArg.inl>

#endif // STATEARG_H
