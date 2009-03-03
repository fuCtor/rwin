#ifndef RITORRENT_H
#define RITORRENT_H

#include <QObject>
#include "rtorrentio.h"

class RITorrent : public QObject
{
	Q_OBJECT

public:
	RITorrent(QObject *parent, QString id = QString());
	~RITorrent();
	QString getId();

signals:
	void updated(QString id);
	void request(QString method);
	void request(QString method, xmlrpc::Variant param1);
	void request(QString method, xmlrpc::Variant param1, xmlrpc::Variant param2);
public slots:
	virtual void update() = 0;
	virtual void fullUpdate(){};
	void enableAutoUpdate();
	void disableAutoUpdate();
protected:
	RTorrentIO IO;
	QMap<QString,QVariant> params;
	QTimer timer;

	void command(QString method);
	void command(QString method, xmlrpc::Variant param1);
	void command(QString method, xmlrpc::Variant param1, xmlrpc::Variant param2);

	void get_info(QString param);
	void get_info(QString param, xmlrpc::Variant id);
	QString hash;
	
private:
	QString id;

protected slots:
	virtual void done(QString method, QString id, QVariant res );
	virtual void processFault( QString method, QString id, int, QString );
	
	
};

#endif // RITORRENT_H
