/********************************************************************************
** Form generated from reading UI file 'helpdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPDIALOG_H
#define UI_HELPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_helpdialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_17;
    QFormLayout *formLayout_2;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_16;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_20;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;

    void setupUi(QDialog *helpdialog)
    {
        if (helpdialog->objectName().isEmpty())
            helpdialog->setObjectName(QString::fromUtf8("helpdialog"));
        helpdialog->resize(815, 716);
        verticalLayout_2 = new QVBoxLayout(helpdialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(helpdialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(20);
        label->setFont(font);

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_4);

        label_2 = new QLabel(helpdialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(200, 0));
        label_2->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(11);
        label_2->setFont(font1);
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_3 = new QLabel(helpdialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(50, 0));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Calibri"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label_3->setFont(font2);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(helpdialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 15));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Calibri"));
        font3.setPointSize(10);
        label_4->setFont(font3);
        label_4->setWordWrap(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, label_4);

        label_5 = new QLabel(helpdialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(helpdialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(0, 25));
        label_6->setFont(font3);
        label_6->setWordWrap(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, label_6);

        label_7 = new QLabel(helpdialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(helpdialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(0, 25));
        label_8->setFont(font3);
        label_8->setWordWrap(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, label_8);

        label_9 = new QLabel(helpdialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(35, 0));
        label_9->setFont(font2);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_9);

        label_10 = new QLabel(helpdialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(0, 15));
        label_10->setFont(font3);
        label_10->setWordWrap(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, label_10);

        label_11 = new QLabel(helpdialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font2);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_11);

        label_12 = new QLabel(helpdialog);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(0, 15));
        label_12->setFont(font3);
        label_12->setWordWrap(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, label_12);

        label_13 = new QLabel(helpdialog);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font2);

        formLayout->setWidget(5, QFormLayout::LabelRole, label_13);

        label_14 = new QLabel(helpdialog);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(0, 15));
        label_14->setFont(font3);
        label_14->setWordWrap(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, label_14);


        verticalLayout->addLayout(formLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);

        label_15 = new QLabel(helpdialog);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMaximumSize(QSize(16777215, 16777215));
        label_15->setFont(font1);
        label_15->setWordWrap(true);

        verticalLayout->addWidget(label_15);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_3);

        label_17 = new QLabel(helpdialog);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Calibri"));
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setWeight(75);
        label_17->setFont(font4);

        verticalLayout->addWidget(label_17);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_18 = new QLabel(helpdialog);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font2);
        label_18->setMargin(0);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_18);

        label_19 = new QLabel(helpdialog);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font3);
        label_19->setIndent(5);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, label_19);

        label_16 = new QLabel(helpdialog);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font2);
        label_16->setMargin(0);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_16);

        label_21 = new QLabel(helpdialog);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font2);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_21);

        label_22 = new QLabel(helpdialog);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font3);
        label_22->setIndent(5);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, label_22);

        label_20 = new QLabel(helpdialog);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font3);
        label_20->setIndent(5);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, label_20);


        verticalLayout->addLayout(formLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(helpdialog);
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

        horizontalLayout->addWidget(okButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(helpdialog);
        QObject::connect(okButton, SIGNAL(clicked()), helpdialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(helpdialog);
    } // setupUi

    void retranslateUi(QDialog *helpdialog)
    {
        helpdialog->setWindowTitle(QApplication::translate("helpdialog", "Help", nullptr));
        label->setText(QApplication::translate("helpdialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Calibri'; font-size:20pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/banners/gui/banner_help.png\" /></p></body></html>", nullptr));
        label_2->setText(QApplication::translate("helpdialog", "The procedural generator can be used to create a multitude of 3D environments, generated using the Perlin noise algorithm. The following settings can be adjusted to change the final outcome:", nullptr));
        label_3->setText(QApplication::translate("helpdialog", "Seed", nullptr));
        label_4->setText(QApplication::translate("helpdialog", "This value shuffles the array the noise values are generated from. Each seed will produce a unique map.", nullptr));
        label_5->setText(QApplication::translate("helpdialog", "Octaves", nullptr));
        label_6->setText(QApplication::translate("helpdialog", "This value determines how many times noise is calculated and added together. More octaves will produce a map with more hills and dips.", nullptr));
        label_7->setText(QApplication::translate("helpdialog", "Persistence", nullptr));
        label_8->setText(QApplication::translate("helpdialog", "This is the percentage that each successive octave affects the overall noise value. Setting persistence to 0 means only the first octave will be used.", nullptr));
        label_9->setText(QApplication::translate("helpdialog", "Vertical Scaling", nullptr));
        label_10->setText(QApplication::translate("helpdialog", "The percentage here will stretch the map vertically, increasing height in comparison to width and depth.", nullptr));
        label_11->setText(QApplication::translate("helpdialog", "Biome", nullptr));
        label_12->setText(QApplication::translate("helpdialog", "The chosen biome determines the colour scheme of the generated map.", nullptr));
        label_13->setText(QApplication::translate("helpdialog", "Time of Day", nullptr));
        label_14->setText(QApplication::translate("helpdialog", "The chosen time of day determines the lighting and skybox of the generated map.", nullptr));
        label_15->setText(QApplication::translate("helpdialog", "<html><head/><body><p>'Low End Computer' should be ticked if you have slower hardware - for example an integrated graphics card, or an older CPU. It will reduce the load on your system. </p><p>Try a variety of settings and see what you can create!</p></body></html>", nullptr));
        label_17->setText(QApplication::translate("helpdialog", "Controls", nullptr));
        label_18->setText(QApplication::translate("helpdialog", "W A S D", nullptr));
        label_19->setText(QApplication::translate("helpdialog", "Navigate camera through the scene", nullptr));
        label_16->setText(QApplication::translate("helpdialog", "Up, Down", nullptr));
        label_21->setText(QApplication::translate("helpdialog", "Escape", nullptr));
        label_22->setText(QApplication::translate("helpdialog", "Exit scene and return to main form", nullptr));
        label_20->setText(QApplication::translate("helpdialog", "Move camera vertically", nullptr));
        okButton->setText(QApplication::translate("helpdialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class helpdialog: public Ui_helpdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPDIALOG_H
