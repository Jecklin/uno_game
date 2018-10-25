#include "CState.h"
#include "CAbstractTransform.h"

CState::CState(int state)
    :m_state(state)
    ,m_transforms()
{
    
}

CState::~CState()
{
    //delete m_transforms
    while(!this->m_transforms.empty())
    {
        this->m_transforms.erase(this->m_transforms.begin());
    }
}

int CState::GetCurState() const
{
    return this->m_state;
}

int CState::ToNextState()
{
    int result = this->m_state;
    QList<CAbstractTransform*>::const_iterator iter = this->m_transforms.begin();
    
    for (iter; iter != this->m_transforms.end(); ++iter)
    {
        CAbstractTransform *transform = *iter;
        if (transform->TransForm())
        {
            result = transform->TarState();
            break;
        }
    }

    return result;
        
}

void CState::AddTransform(CAbstractTransform *transform)
{
    this->m_transforms.push_back(transform);
}

void CState::RemoveTransform(CAbstractTransform *transform)
{
    QList<CAbstractTransform*>::Iterator iter = this->m_transforms.begin();
    
    for (iter; iter != this->m_transforms.end(); ++iter)
    {
        CAbstractTransform *findTransform = *iter;
        if (findTransform == transform)
        {
            this->m_transforms.erase(iter);
            break;
        }
    }
}
