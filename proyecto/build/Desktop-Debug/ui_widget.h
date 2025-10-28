/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *NombreWifi;
    QLineEdit *ContraseniaWifi;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *Temp;
    QPushButton *pushButton_2;
    QToolButton *btnAlarmaGas;
    QToolButton *btnNivelBajo;
    QToolButton *btnNivelMedio;
    QToolButton *btnNivelAlto;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(747, 434);
        Widget->setStyleSheet(QString::fromUtf8("selection-background-color: rgb(180, 180, 180);"));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 10, 341, 61));
        QFont font;
        font.setItalic(true);
        label->setFont(font);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 60, 341, 61));
        label_2->setFont(font);
        NombreWifi = new QLineEdit(Widget);
        NombreWifi->setObjectName(QString::fromUtf8("NombreWifi"));
        NombreWifi->setGeometry(QRect(290, 30, 341, 22));
        ContraseniaWifi = new QLineEdit(Widget);
        ContraseniaWifi->setObjectName(QString::fromUtf8("ContraseniaWifi"));
        ContraseniaWifi->setGeometry(QRect(330, 80, 301, 22));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 140, 341, 61));
        label_3->setFont(font);
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 190, 171, 31));
        label_4->setFont(font);
        Temp = new QLineEdit(Widget);
        Temp->setObjectName(QString::fromUtf8("Temp"));
        Temp->setGeometry(QRect(280, 160, 71, 22));
        Temp->setReadOnly(true);
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(620, 380, 111, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 161, 161);\n"
"selection-background-color: rgb(255, 175, 175);"));
        btnAlarmaGas = new QToolButton(Widget);
        btnAlarmaGas->setObjectName(QString::fromUtf8("btnAlarmaGas"));
        btnAlarmaGas->setEnabled(false);
        btnAlarmaGas->setGeometry(QRect(300, 190, 26, 26));
        btnAlarmaGas->setMinimumSize(QSize(26, 26));
        btnAlarmaGas->setMaximumSize(QSize(26, 26));
        btnAlarmaGas->setTabletTracking(false);
        btnAlarmaGas->setAcceptDrops(false);
        btnAlarmaGas->setAutoFillBackground(false);
        btnAlarmaGas->setStyleSheet(QString::fromUtf8("background-color: #2e2e2e;      /* LED apagado */\n"
"border-radius: 12px;             /* mitad del tama\303\261o para que sea circular */\n"
"border: 1px solid #C0C0C0;\n"
"min-width: 24px;\n"
"min-height: 24px;\n"
"max-width: 24px;\n"
"max-height: 24px;"));
        btnAlarmaGas->setChecked(false);
        btnAlarmaGas->setAutoRepeat(false);
        btnAlarmaGas->setAutoExclusive(false);
        btnAlarmaGas->setArrowType(Qt::ArrowType::NoArrow);
        btnNivelBajo = new QToolButton(Widget);
        btnNivelBajo->setObjectName(QString::fromUtf8("btnNivelBajo"));
        btnNivelBajo->setEnabled(false);
        btnNivelBajo->setGeometry(QRect(690, 130, 50, 50));
        btnNivelBajo->setMinimumSize(QSize(50, 50));
        btnNivelBajo->setMaximumSize(QSize(50, 50));
        btnNivelBajo->setTabletTracking(false);
        btnNivelBajo->setAcceptDrops(false);
        btnNivelBajo->setAutoFillBackground(false);
        btnNivelBajo->setStyleSheet(QString::fromUtf8("\n"
"   background-color: #2e2e2e;      /* verde encendido */\n"
"    border-radius: 24px;            /* c\303\255rculo perfecto */\n"
"    border: 1px solid #C0C0C0;\n"
"    min-width: 48px;\n"
"    min-height: 48px;\n"
"    max-width: 48px;\n"
"    max-height: 48px;"));
        btnNivelBajo->setChecked(false);
        btnNivelBajo->setAutoRepeat(false);
        btnNivelBajo->setAutoExclusive(false);
        btnNivelBajo->setArrowType(Qt::ArrowType::NoArrow);
        btnNivelMedio = new QToolButton(Widget);
        btnNivelMedio->setObjectName(QString::fromUtf8("btnNivelMedio"));
        btnNivelMedio->setEnabled(false);
        btnNivelMedio->setGeometry(QRect(690, 190, 50, 50));
        btnNivelMedio->setMinimumSize(QSize(50, 50));
        btnNivelMedio->setMaximumSize(QSize(50, 50));
        btnNivelMedio->setTabletTracking(false);
        btnNivelMedio->setAcceptDrops(false);
        btnNivelMedio->setAutoFillBackground(false);
        btnNivelMedio->setStyleSheet(QString::fromUtf8("background-color: #2e2e2e;      /* LED encendido */\n"
"    border-radius: 24px;           /* c\303\255rculo perfecto */\n"
"    border: 1px solid #C0C0C0;\n"
"    min-width: 48px;\n"
"    min-height: 48px;\n"
"    max-width: 48px;\n"
"    max-height: 48px;"));
        btnNivelMedio->setChecked(false);
        btnNivelMedio->setAutoRepeat(false);
        btnNivelMedio->setAutoExclusive(false);
        btnNivelMedio->setArrowType(Qt::ArrowType::NoArrow);
        btnNivelAlto = new QToolButton(Widget);
        btnNivelAlto->setObjectName(QString::fromUtf8("btnNivelAlto"));
        btnNivelAlto->setEnabled(false);
        btnNivelAlto->setGeometry(QRect(690, 250, 50, 50));
        btnNivelAlto->setMinimumSize(QSize(50, 50));
        btnNivelAlto->setMaximumSize(QSize(50, 50));
        btnNivelAlto->setTabletTracking(false);
        btnNivelAlto->setAcceptDrops(false);
        btnNivelAlto->setAutoFillBackground(false);
        btnNivelAlto->setStyleSheet(QString::fromUtf8("background-color: #2e2e2e;         /* LED encendido */\n"
"    border-radius: 24px;           /* c\303\255rculo perfecto */\n"
"    border: 1px solid #C0C0C0;\n"
"    min-width: 48px;\n"
"    min-height: 48px;\n"
"    max-width: 48px;\n"
"    max-height: 48px;"));
        btnNivelAlto->setChecked(false);
        btnNivelAlto->setAutoRepeat(false);
        btnNivelAlto->setAutoExclusive(false);
        btnNivelAlto->setArrowType(Qt::ArrowType::NoArrow);
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(470, 140, 221, 31));
        label_5->setFont(font);
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(450, 200, 251, 31));
        label_6->setFont(font);
        label_7 = new QLabel(Widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(470, 260, 281, 31));
        label_7->setFont(font);
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 380, 121, 41));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Panel de control anti incendios", nullptr));
        label->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"justify\"><span style=\" font-size:16pt;\">Ingrese el Nombre del Wifi:</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"justify\"><span style=\" font-size:16pt;\">Ingrese la contrase\303\261a del Wifi:</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"justify\"><span style=\" font-size:16pt;\">Temperatura Detectada</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"justify\"><span style=\" font-size:16pt;\">Gas Detectado</span></p><p align=\"justify\"><br/></p></body></html>", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "Salir", nullptr));
        btnAlarmaGas->setText(QString());
        btnNivelBajo->setText(QString());
        btnNivelMedio->setText(QString());
        btnNivelAlto->setText(QString());
        label_5->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"justify\"><span style=\" font-size:16pt;\">Nivel bajo de peligro</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"justify\"><span style=\" font-size:16pt;\">Nivel medio de peligro</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"justify\"><span style=\" font-size:16pt;\">Nivel alto de peligro</span></p></body></html>", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "Conectar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
