#include "CState.h"
#include "CAbstractTransform.h"

CState::CState(int state)
    :m_state(state)
    ,m_transforms()
{
    
}

CState::~CState()
{
    std::list<CAbstractTransform*>::iterator iter;
    do
    {
        if (this->m_transforms.empty())
        {
            break;
        }
        else
        {
            iter = this->m_transforms.begin();
            m_transforms.erase(iter);
        }
        
    }while(true);
}

int CState::getCurState() const
{
    return this->m_state;
}

int CState::toNextState()
{
    int return_state = this->m_state;
    std::list<CAbstractTransform*>::iterator iter;
    for (iter = this->m_transforms.begin(); iter != this->m_transforms.end(); ++iter)
    {
        CAbstractTransform *ptran = *iter;
        if (ptran->transForm())
        {
            return_state = ptran->tarState();
            break;
        }
        else
        {
            ;
        }
        
    }
    return return_state;
    
}

void CState::addTransform(CAbstractTransform *transform)
{
    this->m_transforms.push_back(transform);
}

void CState::removeTransform(CAbstractTransform *transform)
{
    std::list<CAbstractTransform*>::iterator iter;
    for (iter = this->m_transforms.begin(); iter != this->m_transforms.end(); ++iter)
    {
        CAbstractTransform *ptran = *iter;
        if (ptran == transform)
        {
            this->m_transforms.erase(iter);
        }
        else
        {
            ;
        }   
    }
}
