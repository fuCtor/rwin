#ifndef RTORRENT_H
#define RTORRENT_H

#include <QObject>
#include "ritorrent.h"

namespace RT
{
	const int IDLE_PRIORITY = 0;
	const int LOW_PRIORITY = 1;
	const int NORMAL_PRIORITY = 2;
	const int HIGH_PRIORITY = 3;
}

class RTorrent : public RITorrent
{
	Q_OBJECT

public:
	RTorrent(QObject *parent, QString hash);
	~RTorrent();


	QString getName();
	double getDownRate();
	double getUpRate();
	long getChunkSize();
	long getCompletedChunks();
	long getSizeChunks();
	int getState();
	bool isHashChecking();
	double getRatio();
	bool isActive();
	bool isOpen();
	QString getMessage();
	int getPriority();
	long getSizeBytes();
	QString getDirectory();

public slots:
	void start(bool);
	void pause(bool);
	void resume(bool);
	void stop(bool);
	void check_hash(bool);
	void erase(bool);
	void close(bool);
	void setPriority(int priority);
	void setDirectory(QString path);
	void update();
	void fullUpdate();
signals:
	void erased();
	void changeName(QString);
	void changeDownRate(double);
	void changeUpRate(double);
	void changeChunkSize(long);
	void changeCompletedChunks(int);
	void changeSizeChunks(int);
	void changeState(int);
	void changeRatio(double);
	void changeMessage(QString);
	void changePriority(int);
	void changeSizeBytes(long);
	void changeDirectory(QString);

private:
	void get_info(QString param);
	void command(QString param);
	void updateState();

private slots:
	void done(QString method, QString id, QVariant res );
	
};

#endif // RTORRENT_H


