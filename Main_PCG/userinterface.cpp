#include "userinterface.h"

// Constructor, which makes a call to setup the UI
// The parent in this case will always be left as null, because this is the base window
// and isn't the child of any other.
FormDialog::FormDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);
	if (resubmit) setFormValues();
}

// A function to gather the information put into the form by the user from each of its fields
UserInput FormDialog::getUserInput() {
	uin = {
		ui.seedSlider->value(),
		ui.octaveSlider->value(),
		ui.perSlider->value(),
		ui.scaleSlider->value(),
		ui.biomeMenu->currentIndex(),
		ui.timeMenu->currentIndex(),
		ui.lowBox->isChecked()
	};

	resubmit = true;

	return uin;
}

// Change form values to ones used on previous submission
void FormDialog::setFormValues() {
	ui.seedSlider->setValue(uin.seed);
	ui.seedSpin->setValue(uin.seed);
	ui.octaveSlider->setValue(uin.octave);
	ui.octaveSpin->setValue(uin.octave);
	ui.perSlider->setValue(uin.persistence);
	ui.perSpin->setValue(uin.persistence);
	ui.scaleSlider->setValue(uin.scale);
	ui.scaleSpin->setValue(uin.scale);
	ui.biomeMenu->setCurrentIndex(uin.biomeChoice);
	ui.timeMenu->setCurrentIndex(uin.timeChoice);
	ui.lowBox->setChecked(uin.isLowEnd);
}

// A slot that tells qt to execute an instance of the help dialog window when the member named
// "helpButton" is clicked on
void FormDialog::on_helpButton_clicked() {
	HelpDialog help(this); // sets this window as the parent for the new dialog
	help.exec(); // run the instance
}