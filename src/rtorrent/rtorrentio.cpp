#include "rtorrentio.h"

RTorrentIO::RTorrentIO(QObject *parent)
	: QThread(parent)
{
	if(!InstanceCount)
	{
		start();
	}else
	{
		quit();
	}
	InstanceCount++;
}

RTorrentIO::RTorrentIO(QObject *parent, const QString & hostname, quint16 port , QString path)
	: QThread(parent)
{
	if(!InstanceCount)
	{
		start();
	}else
	{
		quit();
	}
	InstanceCount++;
	RTorrentIO::hostname = hostname;
	RTorrentIO::port = port;
	RTorrentIO::path = path;
}

RTorrentIO::~RTorrentIO()
{
	if(!--InstanceCount)
	{
		//terminate ();
		quit();
		//delete client;
	}
}

Client * RTorrentIO::operator ->()
{
	return client;
}

void RTorrentIO::run(){
	if(InstanceCount == 1)
	{
		client = new Client(parent());
		client->setHost(hostname,port,path);
	}
	exec();
	delete client;
}

Client * RTorrentIO::client =0;
int RTorrentIO::InstanceCount = 0;

//--------------------------------------
	
Client::Client(QObject * parent): xmlrpc::Client(parent)
{
	connect(this,SIGNAL(done(int,QVariant)),
		this,SLOT(x_done(int,QVariant)));
	connect(this,SIGNAL(failed(int, int, QString)),
		this,SLOT(x_processFault(int,int,QString)));
}

Client::Client(QObject * parent,const QString & hostname, quint16 port)
	: xmlrpc::Client(hostname,port,parent)
{

}

Client::~Client()
{
	query.clear();
}

void Client::request( QString methodName )
{
	QPair<QString,QString> val(methodName,QString());
	int key = xmlrpc::Client::request(methodName);
	query[key] = val;
}

void Client::request( QString methodName, xmlrpc::Variant param1 ){
	QPair<QString,QString> val(methodName,param1.toString());
	int key = xmlrpc::Client::request(methodName,param1);
	query[key] = val;
}    

void Client::request( QString methodName, xmlrpc::Variant param1, xmlrpc::Variant param2 ){
	QPair<QString,QString> val(methodName,param1.toString());
	int key = xmlrpc::Client::request(methodName,param1,param2);
	query[key] = val;
}

void Client::x_done( int requestId, QVariant res )
{
	QPair<QString,QString> val = query.take(requestId);
	emit done(val.first,val.second,res);
}

void Client::x_processFault(int requestId, int faultCode, QString faultString )
{
	QPair<QString,QString> val = query.take(requestId);
	emit processFault(val.first,val.second,faultCode,faultString);
}
