#include "CCardTranslator.h"

QString CCardTranslator::ToString(ECardColor color)
{
    static QHash<ECardColor, QString>        m_colorHash;
    if (m_colorHash.isEmpty())
    {
        m_colorHash.insert(ECC_Red,     QString::fromUtf8("Red"));
        m_colorHash.insert(ECC_Yellow,  QString::fromUtf8("Yellow"));
        m_colorHash.insert(ECC_Blue,    QString::fromUtf8("Blue"));
        m_colorHash.insert(ECC_Green,   QString::fromUtf8("Green"));
        m_colorHash.insert(ECC_Black,   QString::fromUtf8("Black")); 
    }

    QString result;
    if (m_colorHash.contains(color))
    {
        result = m_colorHash.value(color);
    }

    return result;
}

QString CCardTranslator::ToString(ECardId id)
{
    static QHash<ECardId, QString>           m_idHash;
    if (m_idHash.isEmpty())
    {
        m_idHash.insert(ECI_Zero,       QString::fromUtf8("0"));
        m_idHash.insert(ECI_One,        QString::fromUtf8("1"));
        m_idHash.insert(ECI_Two,        QString::fromUtf8("2"));
        m_idHash.insert(ECI_Three,      QString::fromUtf8("3"));
        m_idHash.insert(ECI_Four,       QString::fromUtf8("4"));
        m_idHash.insert(ECI_Five,       QString::fromUtf8("5"));
        m_idHash.insert(ECI_Six,        QString::fromUtf8("6"));
        m_idHash.insert(ECI_Seven,      QString::fromUtf8("7"));
        m_idHash.insert(ECI_Eight,      QString::fromUtf8("8"));
        m_idHash.insert(ECI_Nine,       QString::fromUtf8("9"));
        m_idHash.insert(ECI_AddTwo,     QString::fromUtf8("+2"));          
        m_idHash.insert(ECI_Resverse,   QString::fromUtf8("Reverse"));
        m_idHash.insert(ECI_Stop,       QString::fromUtf8("Stop"));
        m_idHash.insert(ECI_Black,      QString::fromUtf8("Black"));
        m_idHash.insert(ECI_BlackFour,  QString::fromUtf8("Black+4")); 
    }
    
    QString result;
    if (m_idHash.contains(id))
    {
        result = m_idHash.value(id);
    }

    return result;
}

QString CCardTranslator::ToString(ECardAction action)
{
    static QHash<ECardAction, QString>       m_actionHash;
    if (m_actionHash.isEmpty())
    {
        m_actionHash.insert(ECA_None,           QString::fromUtf8("None"));                  
        m_actionHash.insert(ECA_Reverse,        QString::fromUtf8("Reverse"));           
        m_actionHash.insert(ECA_Stop,           QString::fromUtf8("Stop"));                 
        m_actionHash.insert(ECA_ChangeColor,    QString::fromUtf8("Color"));       
        m_actionHash.insert(ECA_ActionTwo,      QString::fromUtf8("+2"));          
        m_actionHash.insert(ECA_Black,          QString::fromUtf8("Black"));
        m_actionHash.insert(ECA_BlackFour,      QString::fromUtf8("Black+4"));        

    }
    
    QString result;
    if (m_actionHash.contains(action))
    {
        result = m_actionHash.value(action);
    }

    return result;
}

ECardColor CCardTranslator::ToColor(QString color)
{
    static QHash<QString, ECardColor>        m_strColorHash;
    if (m_strColorHash.isEmpty())
    {
        m_strColorHash.insert("Red",    ECC_Red);
        m_strColorHash.insert("Yellow", ECC_Yellow);
        m_strColorHash.insert("Blue",   ECC_Blue);
        m_strColorHash.insert("Green",  ECC_Green);
        m_strColorHash.insert("Black",  ECC_Black);
    }
    
    ECardColor result;
    if (m_strColorHash.contains(color))
    {
        result = m_strColorHash.value(color);
    }

    return result;
}

ECardId CCardTranslator::ToID(QString id)
{
    static QHash<QString, ECardId>           m_strIdHash;
    if (m_strIdHash.isEmpty())
    {
        m_strIdHash.insert("0",         ECI_Zero);
        m_strIdHash.insert("1",         ECI_One);
        m_strIdHash.insert("2",         ECI_Two);
        m_strIdHash.insert("3",         ECI_Three);
        m_strIdHash.insert("4",         ECI_Four);
        m_strIdHash.insert("5",         ECI_Five);
        m_strIdHash.insert("6",         ECI_Six);
        m_strIdHash.insert("7",         ECI_Seven);
        m_strIdHash.insert("8",         ECI_Eight);
        m_strIdHash.insert("9",         ECI_Nine);
        m_strIdHash.insert("+2",        ECI_AddTwo);
        m_strIdHash.insert("Reverse",   ECI_Resverse);
        m_strIdHash.insert("Stop",      ECI_Stop);
        m_strIdHash.insert("Black",     ECI_Black);
        m_strIdHash.insert("Black+4",   ECI_BlackFour);        
        
    }
    
    ECardId result;
    if (m_strIdHash.contains(id))
    {
        result = m_strIdHash.value(id);
    }

    return result;

}

ECardAction CCardTranslator::ToAction(QString action)
{
    static QHash<QString, ECardAction>       m_strActionHash;
    if (m_strActionHash.isEmpty())
    {
        m_strActionHash.insert("None",      ECA_None);
        m_strActionHash.insert("Reverse",   ECA_Reverse);
        m_strActionHash.insert("Stop",      ECA_Stop);
        m_strActionHash.insert("Color",     ECA_ChangeColor);
        m_strActionHash.insert("+2",        ECA_ActionTwo);
        m_strActionHash.insert("Black",     ECA_Black);
        m_strActionHash.insert("Black+4",   ECA_BlackFour);

    }
    
    ECardAction result;
    if (m_strActionHash.contains(action))
    {
        result = m_strActionHash.value(action);
    }

    return result;

}
