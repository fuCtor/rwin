#include "traymenu.h"
#include <QLabel>
#include <QComboBox>
#include <QWidgetAction>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QSpinBox>
#include "infoaction.h"
#include "settingsdialog.h"
#include <QSettings>

TrayMenu::TrayMenu(QObject *parent)
	: QObject(parent)
{
	
	tray = new QSystemTrayIcon(QIcon(":/img/update.png"),this);
	tray->show();
	//Create menu
	menu = new QMenu(tr("rTorrent client"),0);
	
	//create separator
	

	//add rate control
	QWidget * rate_control = new QWidget(menu);
	QVBoxLayout * vlayout = new QVBoxLayout(rate_control);
	
	// UP SECTION
	QHBoxLayout * hlayout = new QHBoxLayout();
	QSpinBox * spinUp = new QSpinBox(rate_control);
	InfoLabel * lbl_up = new InfoLabel(rate_control);
	QLabel * lbl = new QLabel(rate_control);
	lbl->setPixmap(QPixmap(":/img/up.png"));
	hlayout->addWidget(lbl);
	hlayout->addWidget(lbl_up);
	#if QT_VERSION >= 0x040403
	hlayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding));
	#endif
	hlayout->addWidget(spinUp);
	

	lbl_up->setText(tr("%1 kb/s"));
	spinUp->setMaximum (10*1024);
	spinUp->setSuffix (tr("kb/s"));
	//spinUp->setPrefix (tr("Up "));
	
	vlayout->addLayout(hlayout);

	//DOWN SECTION
	hlayout = new QHBoxLayout();
	QSpinBox * spinDown = new QSpinBox(rate_control);
	InfoLabel * lbl_down = new InfoLabel(rate_control);
	lbl = new QLabel(rate_control);
	lbl->setPixmap(QPixmap(":/img/down.png"));
	hlayout->addWidget(lbl);
	hlayout->addWidget(lbl_down);
	#if QT_VERSION >= 0x040403
	hlayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding));
	#endif
	hlayout->addWidget(spinDown);
	

	lbl_down->setText(tr("%1 kb/s"));
	spinDown->setMaximum (10*1024);
	spinDown->setSuffix (tr("kb/s"));
	//spinDown->setPrefix (tr("Down "));
	
	vlayout->addLayout(hlayout);

	//insert control
	QWidgetAction * waction = new QWidgetAction(menu);
	waction->setDefaultWidget(rate_control);
	menu->addAction(waction);

	menu->addSeparator();
	no_torrent = menu->addAction(tr("No torrents"));
	no_torrent->setDisabled(true);
	sep = menu->addSeparator();

	//set new limit rate value
	connect(spinUp,SIGNAL(valueChanged(int)),
		this,SIGNAL(setUploadRate(int)));
	connect(spinDown,SIGNAL(valueChanged(int)),
		this,SIGNAL(setDownloadRate(int)));

	//update limit rate value
	connect(this,SIGNAL(getUploadRate(int)),
		spinUp,SLOT(setValue(int)));
	connect(this,SIGNAL(getDownloadRate(int)),
		spinDown,SLOT(setValue(int)));

	//update rate value
	connect(this,SIGNAL(getUpRate(double)),
		lbl_up,SLOT(setParam(double)));
	connect(this,SIGNAL(getDownRate(double)),
		lbl_down,SLOT(setParam(double)));

	//create settings item
	QAction * settings = menu->addAction(QIcon(":/img/gear.png"),tr("Settings"));
	connect(settings,SIGNAL(triggered(bool)),
		this, SLOT(openSettings(bool)));

	//create status item
	status = new QAction(QIcon(":/img/state2.png"),tr("Disconnected"),menu);
	menu->addAction(status);
	tray->setContextMenu(menu);

	//create exit item
	QAction * exit = menu->addAction(QIcon(":/img/exit.png"),tr("Exit"));


	//connect menu show
	connect(menu,SIGNAL(aboutToShow()),
		this,SIGNAL(menuShow()));
	connect(menu,SIGNAL(aboutToHide()),
		this,SIGNAL(menuHide()));

	//connect exit
	connect(exit,SIGNAL(triggered(bool)),
		this,SIGNAL(exitClicked(bool)));
}

TrayMenu::~TrayMenu()
{
	tray->hide();
	delete tray;
}


void TrayMenu::addTorrent(RTorrent * torrent)
{
	no_torrent->setVisible(false);
	InfoAction * action = 0;
	QWidgetAction * waction = 0;
	QMenu * tmenu = new QMenu(menu);
	tmenu->setTitle(tr("Loading..."));

	//Add caption
	QLabel * lbl =  new QLabel(tr("<b>Torrent's info</b>"));
	lbl->setAlignment(Qt::AlignHCenter);
	waction = new QWidgetAction(tmenu);
	waction->setDefaultWidget(lbl);
	tmenu->addAction(waction);
	connect(torrent,SIGNAL(changeName(QString)),
		this,SLOT(changeName(QString)));

	//Add rate status
	action = new InfoAction(tmenu);
	action->setText(tr("%1, %2"));
	action->setText1(tr("UP: %1 kb/s"));
	action->setText2(tr("DOWN: %1 kb/s"));

	action->setParam1(tr("N/A"));
	action->setParam2(tr("N/A"));

	action->setIcon(QIcon(":/img/updown.png"));

	connect(torrent,SIGNAL(changeDownRate(double)),
		action,SLOT(setParam2(double)));

	connect(torrent,SIGNAL(changeUpRate(double)),
		action,SLOT(setParam1(double)));
	
	tmenu->addAction(action);

	//Add rateio status
	action = new InfoAction(tmenu);
	action->setText(tr("%1"));
	action->setText1(tr("Rateio: %1"));
	action->setParam1(tr("N/A"));

	connect(torrent,SIGNAL(changeRatio(double)),
		action,SLOT(setParam1(double)));
	tmenu->addAction(action);

	//Add progress
	QProgressBar * bar = new QProgressBar(tmenu);
	bar->setAlignment(Qt::AlignHCenter);
	waction = new QWidgetAction(tmenu);
	waction->setDefaultWidget(bar);
	tmenu->addAction(waction);

	connect(torrent,SIGNAL(changeCompletedChunks(int)),
		bar,SLOT(setValue(int)));

	connect(torrent,SIGNAL(changeSizeChunks(int)),
		bar,SLOT(setMaximum(int)));
	connect(torrent,SIGNAL(changeCompletedChunks(int)),
		this,SLOT(changeCompletedChunks(int)));

	//Add priority
	QComboBox * combo =  new QComboBox(tmenu);
	combo->addItem(QIcon(),tr("Idle"));
	combo->addItem(QIcon(),tr("Low"));
	combo->addItem(QIcon(),tr("Normal"));
	combo->addItem(QIcon(),tr("High"));
	combo->setEditable(false);

	waction = new QWidgetAction(tmenu);
	waction->setDefaultWidget(combo);
	tmenu->addAction(waction);

	connect(torrent,SIGNAL(changePriority(int)),
		combo,SLOT(setCurrentIndex (int)));
	connect(combo,SIGNAL(activated(int)),
		torrent,SLOT(setPriority(int)));
	
	//Other
	connect(torrent,SIGNAL(changeChunkSize(long)),
		this,SLOT(changeChunkSize(long)));
	connect(torrent,SIGNAL(changeState(int)),
		this,SLOT(changeState(int)));

	tmenu->addSeparator();
	QAction * command = 0;

	//control action
	command = tmenu->addAction(QIcon(":/img/close.png"),tr("Close"));
	connect(command,SIGNAL(triggered (bool)),
		torrent,SLOT(close(bool)));
	command = tmenu->addAction(QIcon(":/img/open.png"),tr("Start"));
	connect(command,SIGNAL(triggered (bool)),
		torrent,SLOT(start(bool)));
	command = tmenu->addAction(QIcon(":/img/stop.png"),tr("Stop"));
	connect(command,SIGNAL(triggered (bool)),
		torrent,SLOT(stop(bool)));
	command = tmenu->addAction(QIcon(":/img/rehash0.png"),tr("Rehash"));
	connect(command,SIGNAL(triggered (bool)),
		torrent,SLOT(check_hash(bool)));
	command = tmenu->addAction(QIcon(":/img/erase.png"),tr("Erase"));
	connect(command,SIGNAL(triggered (bool)),
		torrent,SLOT(erase(bool)));

	//connect AutoUpdate when menu visible
	connect(tmenu,SIGNAL(aboutToShow()),
		torrent, SLOT(fullUpdate()));
	connect(tmenu,SIGNAL(aboutToShow()),
		torrent,SLOT(enableAutoUpdate()));
	connect(tmenu,SIGNAL(aboutToHide()),
		torrent,SLOT(disableAutoUpdate()));

	torrents[torrent->getId()] = tmenu;
	menu->insertMenu(sep,tmenu);
}

void TrayMenu::removeTorrent(QString hash)
{
}

//SLOTS

void TrayMenu::openSettings(bool){
	SettingsDialog * form = new SettingsDialog();
	if(form->exec() == QDialog::Accepted)
		QApplication::exit();
	delete form;
}

void TrayMenu::connected()
{
	tray->showMessage(tr("Client connected"),tr("Client connected to rTorrent successfully."));
	tray->setIcon(QIcon(":/img/state1.png"));
	status->setIcon(QIcon(":/img/state1.png"));
	status->setText(tr("Connected"));
}

void TrayMenu::disconnected()
{
	tray->showMessage(tr("Client dicconnected"),tr("Coonection to rTorrent losted."));
	status->setIcon(QIcon(":/img/state2.png"));
	status->setText(tr("Disconnected"));
}

void TrayMenu::erased(){
	RTorrent * torrent = dynamic_cast<RTorrent *>(sender());
	tray->showMessage(tr("Torrent erased"),tr("Torrent %1 erased").arg(torrent->getName()));
}
void TrayMenu::changeName(QString name)
{
	RTorrent * torrent = dynamic_cast<RTorrent *>(sender());
	if(!torrent) return;
	torrents[torrent->getId()]->setTitle(
		truncateString(name,torrents[torrent->getId()]->font(),200)
		);
}

void TrayMenu::changeChunkSize(long){
}

void TrayMenu::changeState(int state){
	static int phase = 1;
	RTorrent * torrent = dynamic_cast<RTorrent *>(sender());
	if(!torrent) return;
	QMenu * tmenu = torrents[torrent->getId()];
	if(torrent->getState())
		tmenu->setIcon(QIcon(":/img/open.png")); 
	else
		tmenu->setIcon(QIcon(":/img/close.png")); 

	if(torrent->isHashChecking())
	{
		phase=phase?0:1;
		tmenu->setIcon(QIcon(QString(":/img/rehash%1.png").arg(phase)));
	}
	
}

void TrayMenu::changeCompletedChunks(int)
{
	RTorrent * torrent = dynamic_cast<RTorrent *>(sender());
	if(!torrent) return;
	
	if(torrent->getSizeChunks() == torrent->getCompletedChunks())
	{
		QMenu * tmenu = torrents.take(torrent->getId());
		tray->showMessage(tr("Torrent complete"),tr("Torrent %1 downloaded").arg(torrent->getName()));
		QSettings settings;
		if(settings.value("delete_completed",false).toBool())
		{
			delete tmenu;
			delete torrent;
			if(torrents.isEmpty())
				no_torrent->setVisible(true);
		}else{
			tmenu->setIcon(QIcon(":/img/finish.png"));			
		}
		
	}
}

void TrayMenu::changeMessage(QString){
}
void TrayMenu::changeSizeBytes(long){
}
void TrayMenu::changeDirectory(QString){
}

QString TrayMenu::truncateString( QString str, QFont font, int sideBarWidth ) const
{
    //TODO pointless? Use QFontMetrics::elidedText()?

    QFontMetrics fm( font );
    Qt::TextElideMode elideMode;

    if ( str.left( 9 ) == "podcast://" )
        elideMode = Qt::ElideMiddle;
    else
    {
        if ( fm.width( str ) > sideBarWidth - 48 )
        {
            QString tmpStr = str.left( 1 ) + "...";

            for ( int i = str.length(); i > 0; i-- )
            {
                if ( str.mid( i - 1, 1 ) == " " ) continue;

                tmpStr = str.left( i ) + "...";

                if ( fm.width( tmpStr ) < sideBarWidth - 48 )
                    return tmpStr;
            }

            return tmpStr;
        }
        else
            return str;
    }

    return fm.elidedText( str, elideMode, sideBarWidth - 48 );
}
