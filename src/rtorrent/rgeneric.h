#ifndef RGENERIC_H
#define RGENERIC_H

#include <QObject>
#include "ritorrent.h"

class RGeneric : public RITorrent
{
	Q_OBJECT

public:
	RGeneric(QObject *parent);
	~RGeneric();

	QString getName();
signals:
	void updated();

private:
	QMap<QString,QVariant> value;

private slots:
	void update(){};
	void done( QString method, QString id, QVariant res );
};

#endif // RGENERIC_H
