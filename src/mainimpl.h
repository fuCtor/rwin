#ifndef MAINIMPL_H
#define MAINIMPL_H
//
#include <QDialog>
#include "./rtorrent/rsystem.h"
#include "./rtorrent/rtorrentclient.h"
#include "traymenu.h"
//
class MainDialogImpl : public QDialog
{
Q_OBJECT
public:
	MainDialogImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	~MainDialogImpl();

private slots:
	void on_pushButton_clicked();

	void init_client();
	void loaded(QString);
	void exitClicked(bool);

private:
	RTorrentClient * rtc;
	RTorrentIO * io;
	RSystem * sys;
	TrayMenu * tray;
};
#endif




