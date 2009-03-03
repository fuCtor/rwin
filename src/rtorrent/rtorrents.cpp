#include "rtorrents.h"

RTorrents::RTorrents(QObject *parent, QString view)
	: RITorrent(parent,view)
{
	torrents.clear();
	update();
}

RTorrents::~RTorrents()
{
}

RTorrent & RTorrents::operator[](int id)
{
	return *torrents[torrents.uniqueKeys()[id]];
}

int RTorrents::count(){
	return torrents.count();
}

void RTorrents::update()
{
	RITorrent::command("download_list",getId());	
}

void RTorrents::done(QString method, QString id, QVariant res )
{
	if((getId() == id) && (method == "download_list") )
	{
		QStringList hashes = res.toStringList();

		foreach(QString hash, hashes)
			if(!torrents.contains(hash))
				if(alltorrents.contains(hash))
					torrents[hash] = alltorrents[hash];
				else
				{
					torrents[hash] = new RTorrent(this,hash);
					alltorrents[hash] = torrents[hash];
				}

		timer.start(UPDATE_INTERVAL);
		emit updated(getId());
	}	
}

QMap<QString,RTorrent*> RTorrents::alltorrents;
