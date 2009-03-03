#include "rsystem.h"

RSystem::RSystem(QObject *parent)
	: RITorrent(parent,"_system")
{
	timer.stop();
	value[QString("system.client_version")] = QVariant();
	RITorrent::get_info("system.client_version");
	value[QString("system.pid")] = QVariant();
	RITorrent::get_info("system.pid");
	value[QString("system.get_cwd")] = QVariant();
	RITorrent::get_info("system.get_cwd");
}

RSystem::~RSystem()
{
}

void RSystem::setCwd(QString new_cwd)
{
	RITorrent::command("system.set_cwd", new_cwd);
	RITorrent::get_info("system.get_cwd");
}

void RSystem::done( QString method, QString id, QVariant res )
{
	if(value.contains(method))
	{
		value[method] = res;
		emit updated(id);
	}	
}

QString RSystem::getVersion()
{
	return value["system.client_version"].toString();
}
int RSystem::getPid()
{
	return value["system.pid"].toInt();
}
QString RSystem::getCwd()
{
	return value["system.get_cwd"].toString();
}
