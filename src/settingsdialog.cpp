#include "settingsdialog.h"
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget *parent, Qt::WFlags f  )
	: QDialog(parent,f)
{
	setupUi(this);
	QSettings settings;
	host->setText(settings.value("host","localhost").toString());
	port->setText(settings.value("port",80).toString());
	path->setText(settings.value("path","/RPC2").toString());
	interval->setText(settings.value("updateInterval",5).toString());
	delete_completed->setChecked(settings.value("delete_completed",false).toBool());
	connect(buttonBox,SIGNAL(accepted()),
		this,SLOT(accept()));
	connect(buttonBox,SIGNAL(rejected()),
		this,SLOT(reject()));
}

void SettingsDialog::accept()
{
	QSettings settings;
	settings.setValue("host",host->text()),
	settings.setValue("port",port->text().toInt()),
	settings.setValue("path",path->text());
	settings.setValue("updateInterval",interval->text().toInt());
	settings.setValue("first_launch",false);
	settings.setValue("delete_completed",delete_completed->isChecked());
	QDialog::accept();
}

SettingsDialog::~SettingsDialog()
{
	
}
