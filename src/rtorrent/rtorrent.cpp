#include "rtorrent.h"
#include <QMessageBox>

RTorrent::RTorrent(QObject *parent,QString hash)
	: RITorrent(parent,hash)
{
	get_info("d.get_name");
	get_info("d.get_size_chunks");
	get_info("d.get_chunk_size");
	updateState();
	update();
	fullUpdate();
}

RTorrent::~RTorrent()
{
}

void RTorrent::updateState(){
	get_info("d.get_state");
	get_info("d.is_active");
	get_info("d.is_open");
	//get_info("d.is_hash_checking");
}

void RTorrent::start(bool){
	command("d.start");
	updateState();
}
void RTorrent::pause(bool){
	command("d.pause");
}
void RTorrent::resume(bool){
	command("d.resume");
}
void RTorrent::stop(bool){
	command("d.stop");
	updateState();
}
void RTorrent::check_hash(bool){
	command("d.check_hash");
	updateState();
}
void RTorrent::erase(bool){
	if(QMessageBox::question(0,tr("Erase"),tr("Torrent %1 will be erased. Are you sure?").arg(getName()),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		command("d.erase");
		emit erased();
		updateState();		
	}
}
void RTorrent::close(bool){
	command("d.close");
	updateState();
}

void RTorrent::get_info(QString param){
	RITorrent::get_info(param,getId());
}

void RTorrent::command(QString param){
	RITorrent::command(param,getId());
}
void RTorrent::update()
{
	get_info("d.get_completed_chunks");
	get_info("d.get_down_rate");		
	get_info("d.get_state");
	get_info("d.is_hash_checking");
}

void RTorrent::fullUpdate()
{
	updateState();
	get_info("d.get_size_bytes");
	get_info("d.get_down_rate");
	get_info("d.get_up_rate");
	get_info("d.get_ratio");
	get_info("d.get_message");
	get_info("d.get_priority");
}

QString RTorrent::getName(){
	return params["d.get_name"].toString();
}
double RTorrent::getDownRate(){
	return params["d.get_down_rate"].toDouble();
}
double RTorrent::getUpRate(){
	return params["d.get_up_rate"].toDouble();
}
long RTorrent::getChunkSize(){
	return params["d.get_chunk_size"].toInt();
}
long RTorrent::getCompletedChunks(){
	return params["d.get_completed_chunks"].toInt();
}
long RTorrent::getSizeChunks(){
	return params["d.get_size_chunks"].toInt();
}
int RTorrent::getState(){
	return params["d.get_state"].toInt();
}
bool RTorrent::isHashChecking(){
	return params["d.is_hash_checking"].toBool();
}
double RTorrent::getRatio(){
	return params["d.get_ratio"].toDouble();
}
bool RTorrent::isActive(){
	return params["d.is_active"].toBool();
}
bool RTorrent::isOpen(){
	return params["d.is_open"].toBool();
}
QString RTorrent::getMessage(){
	return params["d.get_message"].toString();
}
int RTorrent::getPriority(){
	return params["d.get_priority"].toInt();
}
void RTorrent::setPriority(int priority){
	RITorrent::command("d.set_priority",getId(),priority);
}
long RTorrent::getSizeBytes(){
	return params["d.get_size_bytes"].toInt();
}

QString RTorrent::getDirectory(){
	return params["d.get_directory"].toString();
}
void RTorrent::setDirectory(QString path){
	RITorrent::command("d.set_directory",getId(),path);
	get_info("d.get_directory");
}

void RTorrent::done(QString method, QString id, QVariant res )
{
	if(getId() != id) return;
	RITorrent::done(method,id,res);
	if(method == "d.get_name") emit changeName(getName());
	if(method == "d.get_size_chunks") emit changeSizeChunks(getSizeChunks());
	if(method == "d.get_chunk_size") emit changeChunkSize(getChunkSize());
	if(method == "d.get_down_rate") emit changeDownRate(getDownRate()/1024);
	if(method == "d.get_up_rate") emit changeUpRate(getUpRate()/1024);
	if(method == "d.get_completed_chunks") emit changeCompletedChunks(getCompletedChunks());	
	if(method == "d.get_ratio") emit changeRatio(getRatio()/1000);
	if(method == "d.get_message") emit changeMessage(getMessage());
	if(method == "d.get_priority") emit changePriority(getPriority());
	if(method == "d.get_size_bytes")emit changeSizeBytes(getSizeBytes());
	if(method == "d.get_state")emit changeState(getState());
	if(method == "d.is_active")emit changeState(getState());
	if(method == "d.is_open")emit changeState(getState());
	if(method == "d.is_hash_checking")emit changeState(getState());
}
