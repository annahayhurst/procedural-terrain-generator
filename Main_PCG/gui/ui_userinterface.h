/********************************************************************************
** Form generated from reading UI file 'userinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINTERFACE_H
#define UI_USERINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UserInterfaceClass
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QSlider *seedSlider;
    QLabel *label_7;
    QLabel *label_4;
    QSpinBox *octaveSpin;
    QCheckBox *lowBox;
    QSpinBox *perSpin;
    QLabel *label_6;
    QLabel *label;
    QSpinBox *seedSpin;
    QLabel *label_3;
    QSlider *octaveSlider;
    QSpinBox *scaleSpin;
    QComboBox *biomeMenu;
    QSlider *perSlider;
    QSlider *scaleSlider;
    QLabel *label_2;
    QComboBox *timeMenu;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *spacerItem;
    QPushButton *helpButton;

    void setupUi(QDialog *UserInterfaceClass)
    {
        if (UserInterfaceClass->objectName().isEmpty())
            UserInterfaceClass->setObjectName(QString::fromUtf8("UserInterfaceClass"));
        UserInterfaceClass->resize(563, 728);
        verticalLayout = new QVBoxLayout(UserInterfaceClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        title = new QLabel(UserInterfaceClass);
        title->setObjectName(QString::fromUtf8("title"));
        title->setMinimumSize(QSize(0, 100));
        title->setMaximumSize(QSize(16777215, 80));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(24);
        font.setBold(false);
        font.setWeight(50);
        title->setFont(font);

        verticalLayout->addWidget(title);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(17);
        gridLayout->setVerticalSpacing(50);
        gridLayout->setContentsMargins(-1, -1, -1, 65);
        label_5 = new QLabel(UserInterfaceClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(14);
        font1.setItalic(false);
        label_5->setFont(font1);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        seedSlider = new QSlider(UserInterfaceClass);
        seedSlider->setObjectName(QString::fromUtf8("seedSlider"));
        seedSlider->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal {\n"
"	width: 15px;\n"
" 	border: 0px;   \n"
"	border-radius: 2px;\n"
" 	margin: -1px 0;\n"
" 	background:#00a1ff;\n"
"	color: #0077bc;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"	height: 20px; \n"
"    border: 0px;\n"
"  	margin: 5px 0;\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y1:0, stop:0 #d4dadd, stop:1 #c1c8cc);\n"
"}	\n"
""));
        seedSlider->setMaximum(15000);
        seedSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(seedSlider, 0, 1, 1, 1);

        label_7 = new QLabel(UserInterfaceClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Calibri"));
        font2.setPointSize(14);
        label_7->setFont(font2);

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        label_4 = new QLabel(UserInterfaceClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        octaveSpin = new QSpinBox(UserInterfaceClass);
        octaveSpin->setObjectName(QString::fromUtf8("octaveSpin"));
        octaveSpin->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"    padding-right: 15px;\n"
"    border-width: 3;\n"
"	background: transparent;\n"
"	font-family: calibri;\n"
"	font-size: 15px;\n"
"	font-style: italic;\n"
"	\n"
"}\n"
"\n"
"QSpinBox::up-button {\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: top right;\n"
"}\n"
"\n"
"QSpinBox::down-button {\n"
"  	subcontrol-origin: border;\n"
"  	subcontrol-position: bottom right;\n"
"}\n"
"\n"
"/* The following are left deliberately blank to disable them */\n"
"\n"
"QSpinBox::up-button:hover {\n"
"  \n"
"}\n"
"\n"
"QSpinBox::up-button:pressed {\n"
" \n"
"}\n"
"\n"
"QSpinBox::up-arrow {\n"
" \n"
"}\n"
"\n"
"QSpinBox::up-arrow:disabled, QSpinBox::up-arrow:off { \n"
"}\n"
"\n"
"\n"
"\n"
"QSpinBox::down-button:hover {\n"
" \n"
"}\n"
"\n"
"QSpinBox::down-button:pressed {\n"
"   \n"
"}\n"
"\n"
"QSpinBox::down-arrow {\n"
"  \n"
"}\n"
"\n"
"QSpinBox::down-arrow:disabled, QSpinBox::down-arrow:off { \n"
"}"));
        octaveSpin->setMinimum(1);
        octaveSpin->setMaximum(10);

        gridLayout->addWidget(octaveSpin, 2, 2, 1, 1);

        lowBox = new QCheckBox(UserInterfaceClass);
        lowBox->setObjectName(QString::fromUtf8("lowBox"));
        lowBox->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    spacing: 5px;\n"
"	padding: 5px;\n"
"}\n"
""));

        gridLayout->addWidget(lowBox, 7, 1, 1, 1);

        perSpin = new QSpinBox(UserInterfaceClass);
        perSpin->setObjectName(QString::fromUtf8("perSpin"));
        perSpin->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"    padding-right: 15px;\n"
"    border-width: 3;\n"
"	background: transparent;\n"
"	font-family: calibri;\n"
"	font-size: 15px;\n"
"	font-style: italic;\n"
"	\n"
"}\n"
"\n"
"QSpinBox::up-button {\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: top right;\n"
"}\n"
"\n"
"QSpinBox::down-button {\n"
"  	subcontrol-origin: border;\n"
"  	subcontrol-position: bottom right;\n"
"}\n"
"\n"
"/* The following are left deliberately blank to disable them */\n"
"\n"
"QSpinBox::up-button:hover {\n"
"  \n"
"}\n"
"\n"
"QSpinBox::up-button:pressed {\n"
" \n"
"}\n"
"\n"
"QSpinBox::up-arrow {\n"
" \n"
"}\n"
"\n"
"QSpinBox::up-arrow:disabled, QSpinBox::up-arrow:off { \n"
"}\n"
"\n"
"\n"
"\n"
"QSpinBox::down-button:hover {\n"
" \n"
"}\n"
"\n"
"QSpinBox::down-button:pressed {\n"
"   \n"
"}\n"
"\n"
"QSpinBox::down-arrow {\n"
"  \n"
"}\n"
"\n"
"QSpinBox::down-arrow:disabled, QSpinBox::down-arrow:off { \n"
"}"));
        perSpin->setMaximum(100);
        perSpin->setSingleStep(5);

        gridLayout->addWidget(perSpin, 3, 2, 1, 1);

        label_6 = new QLabel(UserInterfaceClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font2);

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        label = new QLabel(UserInterfaceClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font2);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        seedSpin = new QSpinBox(UserInterfaceClass);
        seedSpin->setObjectName(QString::fromUtf8("seedSpin"));
        seedSpin->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"    padding-right: 15px;\n"
"    border-width: 3;\n"
"	background: transparent;\n"
"	font-family: calibri;\n"
"	font-size: 15px;\n"
"	font-style: italic;\n"
"	\n"
"}\n"
"\n"
"QSpinBox::up-button {\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: top right;\n"
"}\n"
"\n"
"QSpinBox::down-button {\n"
"  	subcontrol-origin: border;\n"
"  	subcontrol-position: bottom right;\n"
"}\n"
"\n"
"/* The following are left deliberately blank to disable them */\n"
"\n"
"QSpinBox::up-button:hover {\n"
"  \n"
"}\n"
"\n"
"QSpinBox::up-button:pressed {\n"
" \n"
"}\n"
"\n"
"QSpinBox::up-arrow {\n"
" \n"
"}\n"
"\n"
"QSpinBox::up-arrow:disabled, QSpinBox::up-arrow:off { \n"
"}\n"
"\n"
"\n"
"\n"
"QSpinBox::down-button:hover {\n"
" \n"
"}\n"
"\n"
"QSpinBox::down-button:pressed {\n"
"   \n"
"}\n"
"\n"
"QSpinBox::down-arrow {\n"
"  \n"
"}\n"
"\n"
"QSpinBox::down-arrow:disabled, QSpinBox::down-arrow:off { \n"
"}"));
        seedSpin->setMaximum(15000);

        gridLayout->addWidget(seedSpin, 0, 2, 1, 1);

        label_3 = new QLabel(UserInterfaceClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font2);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        octaveSlider = new QSlider(UserInterfaceClass);
        octaveSlider->setObjectName(QString::fromUtf8("octaveSlider"));
        octaveSlider->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal {\n"
"	width: 15px;\n"
" 	border: 0px;   \n"
"	border-radius: 2px;\n"
" 	margin: -1px 0;\n"
" 	background:#00a1ff;\n"
"	color: #0077bc;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"	height: 20px; \n"
"    border: 0px;\n"
"  	margin: 5px 0;\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y1:0, stop:0 #d4dadd, stop:1 #c1c8cc);\n"
"}	\n"
""));
        octaveSlider->setMinimum(1);
        octaveSlider->setMaximum(10);
        octaveSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(octaveSlider, 2, 1, 1, 1);

        scaleSpin = new QSpinBox(UserInterfaceClass);
        scaleSpin->setObjectName(QString::fromUtf8("scaleSpin"));
        scaleSpin->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"    padding-right: 15px;\n"
"    border-width: 3;\n"
"	background: transparent;\n"
"	font-family: calibri;\n"
"	font-size: 15px;\n"
"	font-style: italic;\n"
"	\n"
"}\n"
"\n"
"QSpinBox::up-button {\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: top right;\n"
"}\n"
"\n"
"QSpinBox::down-button {\n"
"  	subcontrol-origin: border;\n"
"  	subcontrol-position: bottom right;\n"
"}\n"
"\n"
"/* The following are left deliberately blank to disable them */\n"
"\n"
"QSpinBox::up-button:hover {\n"
"  \n"
"}\n"
"\n"
"QSpinBox::up-button:pressed {\n"
" \n"
"}\n"
"\n"
"QSpinBox::up-arrow {\n"
" \n"
"}\n"
"\n"
"QSpinBox::up-arrow:disabled, QSpinBox::up-arrow:off { \n"
"}\n"
"\n"
"\n"
"\n"
"QSpinBox::down-button:hover {\n"
" \n"
"}\n"
"\n"
"QSpinBox::down-button:pressed {\n"
"   \n"
"}\n"
"\n"
"QSpinBox::down-arrow {\n"
"  \n"
"}\n"
"\n"
"QSpinBox::down-arrow:disabled, QSpinBox::down-arrow:off { \n"
"}"));
        scaleSpin->setMinimum(1);
        scaleSpin->setMaximum(100);

        gridLayout->addWidget(scaleSpin, 4, 2, 1, 1);

        biomeMenu = new QComboBox(UserInterfaceClass);
        biomeMenu->addItem(QString());
        biomeMenu->addItem(QString());
        biomeMenu->addItem(QString());
        biomeMenu->addItem(QString());
        biomeMenu->addItem(QString());
        biomeMenu->setObjectName(QString::fromUtf8("biomeMenu"));
        biomeMenu->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	height: 20px;\n"
"\n"
"    border: 0px;\n"
"    border-radius: 2px;\n"
"    padding: 1px 15px 1px 5px;\n"
"\n"
"	font-family: calibri;\n"
"	font-size: 15px;\n"
"\n"
"	background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop:0 #d4dadd, stop:1 #c1c8cc);\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    padding-top: 3px;\n"
"    padding-left: 3px;\n"
"	border-radius: 2px;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    width: 0px;\n"
"}"));

        gridLayout->addWidget(biomeMenu, 5, 1, 1, 1);

        perSlider = new QSlider(UserInterfaceClass);
        perSlider->setObjectName(QString::fromUtf8("perSlider"));
        perSlider->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal {\n"
"	width: 15px;\n"
" 	border: 0px;   \n"
"	border-radius: 2px;\n"
" 	margin: -1px 0;\n"
" 	background:#00a1ff;\n"
"	color: #0077bc;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"	height: 20px; \n"
"    border: 0px;\n"
"  	margin: 5px 0;\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y1:0, stop:0 #d4dadd, stop:1 #c1c8cc);\n"
"}	\n"
""));
        perSlider->setMinimum(0);
        perSlider->setMaximum(100);
        perSlider->setSingleStep(5);
        perSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(perSlider, 3, 1, 1, 1);

        scaleSlider = new QSlider(UserInterfaceClass);
        scaleSlider->setObjectName(QString::fromUtf8("scaleSlider"));
        scaleSlider->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal {\n"
"	width: 15px;\n"
" 	border: 0px;   \n"
"	border-radius: 2px;\n"
" 	margin: -1px 0;\n"
" 	background:#00a1ff;\n"
"	color: #0077bc;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"	height: 20px; \n"
"    border: 0px;\n"
"  	margin: 5px 0;\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y1:0, stop:0 #d4dadd, stop:1 #c1c8cc);\n"
"}	\n"
""));
        scaleSlider->setMinimum(1);
        scaleSlider->setMaximum(100);
        scaleSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(scaleSlider, 4, 1, 1, 1);

        label_2 = new QLabel(UserInterfaceClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font2);

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        timeMenu = new QComboBox(UserInterfaceClass);
        timeMenu->addItem(QString());
        timeMenu->addItem(QString());
        timeMenu->addItem(QString());
        timeMenu->addItem(QString());
        timeMenu->addItem(QString());
        timeMenu->setObjectName(QString::fromUtf8("timeMenu"));
        timeMenu->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	height: 20px;\n"
"\n"
"    border: 0px;\n"
"    border-radius: 2px;\n"
"    padding: 1px 15px 1px 5px;\n"
"\n"
"	font-family: calibri;\n"
"	font-size: 15px;\n"
"\n"
"	background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop:0 #d4dadd, stop:1 #c1c8cc);\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    padding-top: 3px;\n"
"    padding-left: 3px;\n"
"	border-radius: 2px;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    width: 0px;\n"
"}"));

        gridLayout->addWidget(timeMenu, 6, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(UserInterfaceClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #00a1ff;\n"
"\n"
" 	font: 14px;\n"
"	font-family: calibri;\n"
"\n"
"    border-width: 0px;\n"
"    border-radius: 2px;\n"
"	padding: 3px;\n"
"\n"
"    min-width: 5em;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color:#4193bf;\n"
"}"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(UserInterfaceClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #00a1ff;\n"
"\n"
" 	font: 14px;\n"
"	font-family: calibri;\n"
"\n"
"    border-width: 0px;\n"
"    border-radius: 2px;\n"
"	padding: 3px;\n"
"\n"
"    min-width: 5em;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color:#4193bf;\n"
"}"));

        hboxLayout->addWidget(cancelButton);

        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        helpButton = new QPushButton(UserInterfaceClass);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #00a1ff;\n"
"\n"
" 	font: 14px;\n"
"	font-family: calibri;\n"
"\n"
"    border-width: 0px;\n"
"    border-radius: 2px;\n"
"	padding: 3px;\n"
"\n"
"    min-width: 5em;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color:#4193bf;\n"
"}"));

        hboxLayout->addWidget(helpButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(UserInterfaceClass);
        QObject::connect(okButton, SIGNAL(clicked()), UserInterfaceClass, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), UserInterfaceClass, SLOT(reject()));
        QObject::connect(scaleSlider, SIGNAL(valueChanged(int)), scaleSpin, SLOT(setValue(int)));
        QObject::connect(scaleSpin, SIGNAL(valueChanged(int)), scaleSlider, SLOT(setValue(int)));
        QObject::connect(perSlider, SIGNAL(valueChanged(int)), perSpin, SLOT(setValue(int)));
        QObject::connect(perSpin, SIGNAL(valueChanged(int)), perSlider, SLOT(setValue(int)));
        QObject::connect(octaveSlider, SIGNAL(valueChanged(int)), octaveSpin, SLOT(setValue(int)));
        QObject::connect(octaveSpin, SIGNAL(valueChanged(int)), octaveSlider, SLOT(setValue(int)));
        QObject::connect(seedSlider, SIGNAL(valueChanged(int)), seedSpin, SLOT(setValue(int)));
        QObject::connect(seedSpin, SIGNAL(valueChanged(int)), seedSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(UserInterfaceClass);
    } // setupUi

    void retranslateUi(QDialog *UserInterfaceClass)
    {
        UserInterfaceClass->setWindowTitle(QApplication::translate("UserInterfaceClass", "Procedural Generator", nullptr));
        title->setText(QApplication::translate("UserInterfaceClass", "<html><head/><body><p><img src=\":/banners/gui/banner_form.png\"/></p></body></html>", nullptr));
        label_5->setText(QApplication::translate("UserInterfaceClass", "Vertical Scaling (%)", nullptr));
        label_7->setText(QApplication::translate("UserInterfaceClass", "Low End Computer", nullptr));
        label_4->setText(QApplication::translate("UserInterfaceClass", "Persistence (%)", nullptr));
        lowBox->setText(QString());
        label_6->setText(QApplication::translate("UserInterfaceClass", "Time of Day", nullptr));
        label->setText(QApplication::translate("UserInterfaceClass", "Seed", nullptr));
        label_3->setText(QApplication::translate("UserInterfaceClass", "Octaves", nullptr));
        biomeMenu->setItemText(0, QApplication::translate("UserInterfaceClass", "Grassland", nullptr));
        biomeMenu->setItemText(1, QApplication::translate("UserInterfaceClass", "Mountains", nullptr));
        biomeMenu->setItemText(2, QApplication::translate("UserInterfaceClass", "Dunes", nullptr));
        biomeMenu->setItemText(3, QApplication::translate("UserInterfaceClass", "Glacier", nullptr));
        biomeMenu->setItemText(4, QApplication::translate("UserInterfaceClass", "Heatmap", nullptr));

        label_2->setText(QApplication::translate("UserInterfaceClass", "Biome", nullptr));
        timeMenu->setItemText(0, QApplication::translate("UserInterfaceClass", "Morning", nullptr));
        timeMenu->setItemText(1, QApplication::translate("UserInterfaceClass", "Midday", nullptr));
        timeMenu->setItemText(2, QApplication::translate("UserInterfaceClass", "Evening", nullptr));
        timeMenu->setItemText(3, QApplication::translate("UserInterfaceClass", "Midnight", nullptr));
        timeMenu->setItemText(4, QApplication::translate("UserInterfaceClass", "None", nullptr));

        okButton->setText(QApplication::translate("UserInterfaceClass", "OK", nullptr));
        cancelButton->setText(QApplication::translate("UserInterfaceClass", "Cancel", nullptr));
        helpButton->setText(QApplication::translate("UserInterfaceClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserInterfaceClass: public Ui_UserInterfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINTERFACE_H
