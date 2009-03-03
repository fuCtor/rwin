
#include "mainimpl.h"
#include "settingsdialog.h"
#include <QDebug>
#include <QSettings>

//
MainDialogImpl::MainDialogImpl( QWidget * parent, Qt::WFlags f)
        : QDialog(parent, f)
{
	tray = new TrayMenu(this);
	connect(tray,SIGNAL(exitClicked(bool)),
		this,SLOT(exitClicked(bool)));


	QSettings settings;

	if(settings.value("first_launch",true).toBool())
	{
		SettingsDialog form;
		form.setModal(true);
		form.exec();

	}
	
	io = new RTorrentIO(0,
		settings.value("host","localhost").toString(),
		settings.value("port",80).toInt(),
		settings.value("path","/RPC2").toString());

	if(io)
	{
		connect(io,SIGNAL(started()),
			this,SLOT(init_client()));
		io->start();
	}else
		tray->disconnected();

}

MainDialogImpl::~MainDialogImpl(){
	delete tray;
	io->terminate();
	delete io;
}

void MainDialogImpl::exitClicked(bool)
{
	QApplication::exit();
}

//
void MainDialogImpl::init_client()
{
	if(sender() == io){
		sys = new RSystem(parent());
		connect(sys,SIGNAL(updated(QString)),
			this,SLOT(loaded(QString)));
	}
}

void MainDialogImpl::loaded(QString id){
	if(sender()==sys)
	{
		tray->connected();
		disconnect(sender(),0,this,0);
		rtc = new RTorrentClient(parent());
		//update rate value
		connect(rtc,SIGNAL(changeUpRate(double)),
			tray,SIGNAL(getUpRate(double)));
		connect(rtc,SIGNAL(changeDownRate(double)),
			tray,SIGNAL(getDownRate(double)));
		
		//set new rate limit value
		connect(tray,SIGNAL(setUploadRate(int)),
			rtc,SLOT(setUploadRate(int)));
		connect(tray,SIGNAL(setDownloadRate(int)),
			rtc,SLOT(setDownloadRate(int)));

		//update rate limit value
		connect(rtc,SIGNAL(changeUploadRate(int)),
			tray,SIGNAL(getUploadRate(int)));
		connect(rtc,SIGNAL(changeDownloadRate(int)),
			tray,SIGNAL(getDownloadRate(int)));


		//connect update on show/hide event
		connect(tray,SIGNAL(menuShow()),
			rtc, SLOT(fullUpdate()));
		connect(tray,SIGNAL(menuShow()),
			rtc, SLOT(enableAutoUpdate()));
		connect(tray,SIGNAL(menuHide()),
			rtc, SLOT(disableAutoUpdate()));
		
		//-------
		connect(rtc,SIGNAL(updated(QString)),
			this,SLOT(loaded(QString)));
	}
	QSettings settings;
	QString view = settings.value("view","incomplete").toString();
	if(sender()==rtc)
	{
		disconnect(sender(),0,this,0);
		rtc->using_views << view;
		rtc->loadUsingViews();
		connect(rtc->torrents[view],SIGNAL(updated(QString)),
			this,SLOT(loaded(QString)));
		
	}
	if(id == view){
		disconnect(sender(),0,this,0);
		int tc = rtc->torrents[view]->count();
		for(int i = 0; i < tc; i++)
			tray->addTorrent(&((*rtc->torrents[view])[i]));

	}
}


void MainDialogImpl::on_pushButton_clicked()
{
	qDebug() << (*rtc)[7][1].getName();
}
