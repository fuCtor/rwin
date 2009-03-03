#ifndef RTORRENTIO_H
#define RTORRENTIO_H
#define UPDATE_INTERVAL 5 //sec
//#include <QObject>
#include <QThread>
#include <QPair>
#include <QString>
#include "../xmlrpc/client.h"

typedef QPair<QString,QString> r_key;
class Client;

class RTorrentIO : public QThread
{
	Q_OBJECT

public:
	RTorrentIO(QObject *parent = 0);
	RTorrentIO(QObject *parent, const QString & hostname, quint16 port = 80, QString path="/");
	~RTorrentIO();
	Client * getInstance(){return client;};
	Client * operator ->();
private:
	QString hostname;
	quint16 port;
	QString path;
	static Client * client ;
	static int InstanceCount ;
	void run() ;
};


class Client : public xmlrpc::Client
{
	Q_OBJECT
public:
	Client(QObject *parent = 0);
	Client(QObject *parent, const QString & hostname, quint16 port = 80);
	~Client();
	
public slots:
	void request( QString methodName );
	void request( QString methodName, xmlrpc::Variant param1 );    
    void request( QString methodName, xmlrpc::Variant param1, xmlrpc::Variant param2 );

signals:
	void done(QString method, QString id, QVariant res );
	void processFault( QString method, QString id, int, QString );

private slots:
	void x_done( int requestId, QVariant res );
	void x_processFault( int, int, QString );
private:
	QMap<int,r_key> query;
};

#endif // RTORRENTIO_H
