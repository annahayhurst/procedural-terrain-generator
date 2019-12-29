#pragma once

/* LoadDialog
* A basic dialog window designed to indicate that the grid is being generated, as this is a lengthy operation
* where the user may get the impression the system has crashed.
*/

#include <QDialog>
#include "ui_loaddialog.h"

class LoadDialog : public QDialog {
	Q_OBJECT

public:
	LoadDialog(QWidget *parent = Q_NULLPTR);
	~LoadDialog() {};

private:
	Ui::LoadDialog ui;
};
