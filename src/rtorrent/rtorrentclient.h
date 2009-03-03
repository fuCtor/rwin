#ifndef RTORRENTCLIENT_H
#define RTORRENTCLIENT_H

#include <QObject>
#include "rtorrents.h"
class RTorrentClient : public RITorrent
{
	Q_OBJECT

public:
	RTorrentClient(QObject *parent);
	~RTorrentClient();
	QMap<QString,RTorrents *> torrents;
	double getDownRate();
	double getUpRate();
	
	QStringList exist_views;
	QStringList using_views;
	void loadUsingViews();

	RTorrents & operator[](int);
signals:
	void views_loaded();
	void changeDownRate(double);
	void changeUpRate(double);
	void changeDownloadRate(int rate);
	void changeUploadRate(int rate);

public slots:
	void setDownloadRate(int rate);
	void setUploadRate(int rate);
	void update(){};
	void fullUpdate();
private:
	int list_req_id;
	void updateState();

private slots:
	void done(QString method, QString id, QVariant res );
	
};

#endif // RTORRENTCLIENT_H
