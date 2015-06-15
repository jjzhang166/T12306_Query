/********************************************************************************
** Form generated from reading UI file 'T12306.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_T12306_H
#define UI_T12306_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_T12306
{
public:
    QComboBox *qidian_comboBox;
    QComboBox *zhongdian_comboBox_2;
    QPushButton *chaxun_pushButton;
    QDateEdit *dateEdit;
    QTableWidget *tableWidget;

    void setupUi(QDialog *T12306)
    {
        if (T12306->objectName().isEmpty())
            T12306->setObjectName(QStringLiteral("T12306"));
        T12306->resize(820, 472);
        qidian_comboBox = new QComboBox(T12306);
        qidian_comboBox->setObjectName(QStringLiteral("qidian_comboBox"));
        qidian_comboBox->setGeometry(QRect(30, 410, 161, 31));
        qidian_comboBox->setEditable(true);
        zhongdian_comboBox_2 = new QComboBox(T12306);
        zhongdian_comboBox_2->setObjectName(QStringLiteral("zhongdian_comboBox_2"));
        zhongdian_comboBox_2->setGeometry(QRect(210, 410, 161, 31));
        zhongdian_comboBox_2->setEditable(true);
        chaxun_pushButton = new QPushButton(T12306);
        chaxun_pushButton->setObjectName(QStringLiteral("chaxun_pushButton"));
        chaxun_pushButton->setGeometry(QRect(650, 410, 141, 41));
        dateEdit = new QDateEdit(T12306);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setGeometry(QRect(390, 410, 201, 31));
        dateEdit->setAlignment(Qt::AlignCenter);
        dateEdit->setReadOnly(false);
        dateEdit->setDateTime(QDateTime(QDate(2015, 5, 25), QTime(0, 0, 0)));
        dateEdit->setCalendarPopup(true);
        tableWidget = new QTableWidget(T12306);
        if (tableWidget->columnCount() < 14)
            tableWidget->setColumnCount(14);
        if (tableWidget->rowCount() < 11)
            tableWidget->setRowCount(11);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 801, 391));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setLineWidth(1);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSortingEnabled(true);
        tableWidget->setRowCount(11);
        tableWidget->setColumnCount(14);
        tableWidget->horizontalHeader()->setDefaultSectionSize(57);
        tableWidget->verticalHeader()->setVisible(false);

        retranslateUi(T12306);

        QMetaObject::connectSlotsByName(T12306);
    } // setupUi

    void retranslateUi(QDialog *T12306)
    {
        T12306->setWindowTitle(QApplication::translate("T12306", "T12306", 0));
        qidian_comboBox->setCurrentText(QApplication::translate("T12306", "\345\214\227\344\272\254", 0));
        zhongdian_comboBox_2->setCurrentText(QApplication::translate("T12306", "\351\276\231\345\262\251", 0));
        chaxun_pushButton->setText(QApplication::translate("T12306", "\346\237\245\350\257\242", 0));
        dateEdit->setDisplayFormat(QApplication::translate("T12306", "yyyy-M-dd", 0));
    } // retranslateUi

};

namespace Ui {
    class T12306: public Ui_T12306 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_T12306_H
