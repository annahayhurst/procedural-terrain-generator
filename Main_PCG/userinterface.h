#pragma once

/*
* FormDialog
* A QT class that serves as a base for the QT side of the application. It presents the user with a form that
* they can interact with and edit, and then either submit or cancel to exit the program. It also provides a function
* to spawn the additional help window when the corresponding button is pressed.
*/

#include <QtWidgets/QDialog>
#include <QtWidgets/QApplication>
#include "ui_userinterface.h"
#include "helpdialog.h"

// A struct that stores all information submitted from the main form
struct UserInput {
	int seed;
	int octave;
	int persistence;
	int scale;
	int biomeChoice;
	int timeChoice;
	bool isLowEnd;
};

class FormDialog : public QDialog { // the gui is a dialog - pops up and asks for user input
	Q_OBJECT

public:
	FormDialog(QWidget *parent = Q_NULLPTR);
	UserInput getUserInput();

private:
	Ui::UserInterfaceClass ui;
	bool resubmit = false;
	UserInput uin;

	void setFormValues();
	
private slots: // slots are functions that are called when some given signal is emitted during runtime
	void on_helpButton_clicked();
};
