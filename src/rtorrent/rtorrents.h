#ifndef RTORRENTS_H
#define RTORRENTS_H

#include <QObject>
#include "rtorrent.h"

class RTorrents : public RITorrent
{
	Q_OBJECT

public:
	RTorrents(QObject *parent, QString view);
	~RTorrents();
	RTorrent & operator[](int);
	int count();

private:
	int rq;
	QTimer timer;
	QMap<QString,RTorrent*> torrents;
	static QMap<QString,RTorrent*> alltorrents;

private slots:
	void done(QString method, QString id, QVariant res );
	void update();

};

#endif // RTORRENTS_H
