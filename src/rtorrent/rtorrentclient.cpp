#include "rtorrentclient.h"

RTorrentClient::RTorrentClient(QObject *parent)
	: RITorrent(parent)
{
	RITorrent::command("view_list"); 
	get_info("get_download_rate");
	get_info("get_upload_rate");
	update();
	fullUpdate();
}

RTorrentClient::~RTorrentClient()
{
}

void RTorrentClient::fullUpdate()
{
	get_info("get_down_rate");
	get_info("get_up_rate");
}

double RTorrentClient::getDownRate(){
	return params["get_down_rate"].toDouble()/1024;
}
double RTorrentClient::getUpRate(){
	return params["get_up_rate"].toDouble()/1024;
}

void RTorrentClient::setDownloadRate(int rate)
{
	RITorrent::command("set_download_rate",(int)(rate*1024));
	update();
}
void RTorrentClient::setUploadRate(int rate)
{
	RITorrent::command("set_upload_rate",(int)(rate*1024));
	update();
}

void RTorrentClient::done(QString method, QString id, QVariant res )
{
	RITorrent::done(method, id,res);
	if(method == "view_list") exist_views = res.toStringList(); 
	if(method == "get_down_rate") emit changeDownRate(getDownRate());
	if(method == "get_up_rate") emit changeUpRate(getUpRate());
	if(method == "get_download_rate") emit changeDownloadRate(params["get_download_rate"].toInt()/1024);
	if(method == "get_upload_rate") emit changeUploadRate(params["get_upload_rate"].toInt()/1024);
}
void RTorrentClient::loadUsingViews()
{
	foreach(QString view, using_views)
		if(!torrents.contains(view))
			torrents[view] = new RTorrents(this,view);
	emit views_loaded();
}

RTorrents & RTorrentClient::operator[](int id){
	return *torrents[torrents.uniqueKeys()[id]];
}
