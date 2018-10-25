#pragma once
#include "datatypedefine.h"
#include <QString>
#include <QHash>


namespace CCardTranslator {

QString      ToString(ECardColor color);
QString      ToString(ECardId id);
QString      ToString(ECardAction action);

ECardColor   ToColor(QString color);
ECardId      ToID(QString id);
ECardAction  ToAction(QString action);

}
