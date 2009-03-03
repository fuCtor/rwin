#ifndef RSYSTEM_H
#define RSYSTEM_H

#include <QObject>
#include "ritorrent.h"

class RSystem : public RITorrent
{
	Q_OBJECT

public:
	RSystem(QObject *parent);
	~RSystem();

	QString getVersion();
	int getPid();
	QString getCwd();
	void setCwd(QString cwd);

private:
	QMap<QString,QVariant> value;

private slots:
	void update(){};
	void done( QString method, QString id, QVariant res );
	
};

#endif // RSYSTEM_H
