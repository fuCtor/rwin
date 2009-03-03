#include "infoaction.h"

InfoAction::InfoAction(QWidget *parent)
	: QAction(parent)
{
	tpl_text="";
	tpl_text1="";
	tpl_text2="";
	text1="";
	text2="";
}

InfoAction::~InfoAction()
{

}

void InfoAction::setParam1(int val){
	text1 = tpl_text1.arg(val);
	textUpdate();
}
void InfoAction::setParam2(int val){
	text2 = tpl_text2.arg(val);
	textUpdate();
}
void InfoAction::setParam1(double val){
	val = (qreal)(qRound(val*100))/100;
	text1 = tpl_text1.arg(val,0,'g',7);
	textUpdate();
}
void InfoAction::setParam2(double val){
	val = qRound(val*100)/100;
	text2 = tpl_text2.arg(val,0,'g',7);
	textUpdate();
}
void InfoAction::setParam1(QString val){
	text1 = tpl_text1.arg(val);
	textUpdate();
}
void InfoAction::setParam2(QString val){
	text2 = tpl_text2.arg(val);
	textUpdate();
}
void InfoAction::setText ( const QString & text ){
	tpl_text = text;
	textUpdate();
}
void InfoAction::setText1 ( const QString & text ){
	tpl_text1 = text;
}

void InfoAction::setText2 ( const QString & text ){
	tpl_text2 = text;
}
void InfoAction::textUpdate(){
	QAction::setText(tpl_text.arg(text1).arg(text2));
}

//--------------------------------------

InfoLabel::InfoLabel(QWidget *parent)
	: QLabel(parent)
{

}

InfoLabel::~InfoLabel()
{

}

void InfoLabel::setParam(int val){
	InfoLabel::text = tpl_text.arg(val);
	textUpdate();
}

void InfoLabel::setParam(double val){
	val = (qreal)(qRound(val*100))/100;
	InfoLabel::text = tpl_text.arg(val,0,'g',7);
	textUpdate();
}

void InfoLabel::setParam(QString val){
	InfoLabel::text = tpl_text.arg(val);
	textUpdate();
}

void InfoLabel::setText ( const QString & text ){
	tpl_text = text;
	textUpdate();
}

void InfoLabel::textUpdate(){
	QLabel::setText(InfoLabel::text);
}
