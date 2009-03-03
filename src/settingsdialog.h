#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ui_settingsdialog.h"

class SettingsDialog : public QDialog , public Ui::SettingsDialogClass
{
	Q_OBJECT

public:
	SettingsDialog(QWidget *parent = 0, Qt::WFlags f = 0 );
	~SettingsDialog();

private slots:
	void accept();	
};

#endif // SETTINGSDIALOG_H
