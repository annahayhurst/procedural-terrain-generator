#pragma once

/* HelpDialog
* A simple pop up menu accessed through the 'Help' button in the loaded instance of
* FormDialog. It displays help about the different parameters that can be changed
* and gives advice about whether the user should select the low end computer option.
*/

#include <QDialog>
#include "ui_helpdialog.h"

class HelpDialog : public QDialog, public Ui_helpdialog {
	Q_OBJECT

public:
	HelpDialog(QWidget *parent = Q_NULLPTR);
	~HelpDialog() {};
};
