#ifndef INFOACTION_H
#define INFOACTION_H

#include <QAction>
#include <QLabel>
class InfoAction : public QAction
{
	Q_OBJECT

public:
	InfoAction(QWidget *parent);
	~InfoAction();

public slots:
	void setParam1(int);
	void setParam2(int);
	void setParam1(double);
	void setParam2(double);
	void setParam1(QString);
	void setParam2(QString);
	void setText ( const QString & text );
	void setText1 ( const QString & text );
	void setText2 ( const QString & text );
private:
	QString tpl_text,tpl_text1, tpl_text2;
	QString text1, text2;
	void textUpdate();
};


class InfoLabel : public QLabel
{
	Q_OBJECT

public:
	InfoLabel(QWidget *parent);
	~InfoLabel();

public slots:
	void setParam(int);
	void setParam(double);
	void setParam(QString);
	void setText ( const QString & text );

private:
	QString tpl_text;
	QString text;
	void textUpdate();
};

#endif // INFOACTION_H
