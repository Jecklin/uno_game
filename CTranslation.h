#ifndef CTRANSLATION_H
#define CTRANSLATION_H

#include "CAbState.h"

class CTranslation
{
public:
    CTranslation();
    
    void        initStates();
    bool        registerState(int e, CAbState *pState);
    bool        transState(int newState);
    
private:
    std::map<int, CAbState*>            m_states;  
};

#endif // CTRANSLATION_H
