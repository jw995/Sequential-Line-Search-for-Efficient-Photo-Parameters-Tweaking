/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "mainwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBatch_visualization;
    QAction *actionProceed_optimization;
    QAction *actionClear_all_data;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    MainWidget *widget_y;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_4;
    MainWidget *widget_e;
    MainWidget *widget_m;
    MainWidget *widget_s;
    QMenuBar *menuBar;
    QMenu *menuAdd;
    QMenu *menuView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(634, 706);
        actionBatch_visualization = new QAction(MainWindow);
        actionBatch_visualization->setObjectName(QStringLiteral("actionBatch_visualization"));
        actionProceed_optimization = new QAction(MainWindow);
        actionProceed_optimization->setObjectName(QStringLiteral("actionProceed_optimization"));
        actionClear_all_data = new QAction(MainWindow);
        actionClear_all_data->setObjectName(QStringLiteral("actionClear_all_data"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        widget_y = new MainWidget(centralWidget);
        widget_y->setObjectName(QStringLiteral("widget_y"));
        widget_y->setMinimumSize(QSize(300, 300));

        gridLayout->addWidget(widget_y, 0, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 4, 1, 1, 1);

        widget_e = new MainWidget(centralWidget);
        widget_e->setObjectName(QStringLiteral("widget_e"));
        widget_e->setMinimumSize(QSize(300, 300));

        gridLayout->addWidget(widget_e, 0, 1, 1, 1);

        widget_m = new MainWidget(centralWidget);
        widget_m->setObjectName(QStringLiteral("widget_m"));

        gridLayout->addWidget(widget_m, 3, 0, 1, 1);

        widget_s = new MainWidget(centralWidget);
        widget_s->setObjectName(QStringLiteral("widget_s"));
        widget_s->setMinimumSize(QSize(300, 300));

        gridLayout->addWidget(widget_s, 3, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 634, 22));
        menuAdd = new QMenu(menuBar);
        menuAdd->setObjectName(QStringLiteral("menuAdd"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuAdd->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuAdd->addAction(actionBatch_visualization);
        menuAdd->addAction(actionProceed_optimization);
        menuAdd->addAction(actionClear_all_data);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionBatch_visualization->setText(QApplication::translate("MainWindow", "Batch visualization", nullptr));
        actionProceed_optimization->setText(QApplication::translate("MainWindow", "Proceed optimization", nullptr));
#ifndef QT_NO_SHORTCUT
        actionProceed_optimization->setShortcut(QApplication::translate("MainWindow", "Ctrl+Return", nullptr));
#endif // QT_NO_SHORTCUT
        actionClear_all_data->setText(QApplication::translate("MainWindow", "Clear all data", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "y_mean", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "EI", nullptr));
        label->setText(QApplication::translate("MainWindow", "f(x)", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "y_var", nullptr));
        menuAdd->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
