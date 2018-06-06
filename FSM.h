#ifndef FSM_H
#define FSM_H
#include <unordered_map>
#include <functional>
#include <unistd.h>

#include "CAbState.h"
#include <map>
#include "CGameLoop.h"


class CAbState;

class FSM
{
public:
    FSM();
    ~FSM();
    
public:

    
//Game loop
    void        initFSM();
    bool        registerState(int e, CAbState *pState);
    bool        transState(int newState);
    void        tick();
      
  
private:
    std::map<int, CAbState*>            m_states;                       
    CGameLoop                           *m_game_loop;
};

#endif // FSM_H




