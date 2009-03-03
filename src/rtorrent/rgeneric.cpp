#include "rgeneric.h"

RGeneric::RGeneric(QObject *parent)
	: RITorrent(parent,"_generic")
{
	timer.stop();
	value[QString("get_name")] = QVariant();
	RITorrent::get_info("get_name");
}

RGeneric::~RGeneric()
{

}

QString RGeneric::getName()
{
	return value["get_name"].toString();
}

void RGeneric::done( QString method, QString id, QVariant res )
{
	if(value.contains(method))
	{
		value[method] = res;
		emit updated();
	}	
}
