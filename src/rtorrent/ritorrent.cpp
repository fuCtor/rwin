#include "ritorrent.h"
#include <QSettings>

RITorrent::RITorrent(QObject *parent,QString id)
	: QObject(parent),id(id)
{
	//Response connect
	connect(IO.getInstance(),SIGNAL(done(QString,QString,QVariant)),
		this,SLOT(done(QString,QString,QVariant)));
	connect(IO.getInstance(), SIGNAL(processFault( QString,QString, int, QString )),
        this, SLOT(processFault( QString,QString, int, QString )) );

	connect(&timer,SIGNAL(timeout()),
		this,SLOT(update()));


	//Request connect
	connect(this,SIGNAL(request(QString)),
		IO.getInstance(),SLOT(request(QString)));
	connect(this,SIGNAL(request(QString,xmlrpc::Variant)),
		IO.getInstance(),SLOT(request(QString,xmlrpc::Variant)));
	connect(this,SIGNAL(request(QString,xmlrpc::Variant,xmlrpc::Variant)),
		IO.getInstance(),SLOT(request(QString,xmlrpc::Variant,xmlrpc::Variant)));
	QSettings settings;
	timer.setInterval(settings.value("updateInterval",UPDATE_INTERVAL).toInt()*1000);
}

RITorrent::~RITorrent()
{
	IO.getInstance()->disconnect();
	timer.stop();
}

void RITorrent::enableAutoUpdate(){
	//Timer full update connect
	connect(&timer,SIGNAL(timeout()),
		this,SLOT(fullUpdate()));	
}
void RITorrent::disableAutoUpdate(){
	//Timer full update connect
	disconnect(&timer,SIGNAL(timeout()),
		this,SLOT(fullUpdate()));	
}

void RITorrent::done(QString method, QString req_id, QVariant res )
{
	if(getId() != req_id) return;

	params[method] = res;
	timer.start();
	emit updated(getId());
}

void RITorrent::processFault( QString method, QString id, int, QString err)
{
	qDebug() << err;
}

void RITorrent::get_info(QString param){
	emit request(param);
}

void RITorrent::get_info(QString param,xmlrpc::Variant id){
	emit request(param,id);
}

void RITorrent::command(QString method){
	emit request(method);
}
void RITorrent::command(QString method,xmlrpc::Variant param1){
	emit request(method,param1);
}
void RITorrent::command(QString method,xmlrpc::Variant param1, xmlrpc::Variant param2){
	emit request(method,param1,param2);
}

QString RITorrent::getId(){
	return id;
}
