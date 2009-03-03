#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include "rtorrent/rtorrent.h"


class TrayMenu : public QObject
{
	Q_OBJECT

public:
	TrayMenu(QObject *parent);
	~TrayMenu();
	void addTorrent(RTorrent *);
	void removeTorrent(QString);

signals:
	void exitClicked(bool);

	void getUpRate(double);
	void getDownRate(double);

	void getUploadRate(int);
	void getDownloadRate(int);

	void setUploadRate(int);
	void setDownloadRate(int);
	
	void menuShow();
	void menuHide();

public slots:
	void connected();
	void disconnected();
	
private:
	QSystemTrayIcon * tray;
	QMenu * menu;
	QAction *status, *sep, *no_torrent;

	QMap<QString,QMenu *> torrents;
	QString truncateString( QString str, QFont font, int sideBarWidth ) const;
private slots:
	void erased();
	void changeName(QString name);
	void changeState(int state);
	void changeCompletedChunks(int);
	void changeChunkSize(long);
	void changeMessage(QString);
	void changeSizeBytes(long);
	void changeDirectory(QString);

	void openSettings(bool);

};

#endif // TRAYMENU_H
