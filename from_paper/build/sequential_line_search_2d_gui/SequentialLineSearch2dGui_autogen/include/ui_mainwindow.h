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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mainwidget.h"
#include "widgetpreview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBatch_visualization;
    QAction *actionProceed_optimization;
    QAction *actionClear_all_data;
    QAction *actionPrint_current_best;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    MainWidget *widget_m;
    MainWidget *widget_s;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_4;
    MainWidget *widget_e;
    MainWidget *widget_y;
    QLabel *label_3;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    WidgetPreview *widget_preview;
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menuAdd;
    QMenu *menuView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(590, 508);
        actionBatch_visualization = new QAction(MainWindow);
        actionBatch_visualization->setObjectName(QStringLiteral("actionBatch_visualization"));
        actionProceed_optimization = new QAction(MainWindow);
        actionProceed_optimization->setObjectName(QStringLiteral("actionProceed_optimization"));
        actionClear_all_data = new QAction(MainWindow);
        actionClear_all_data->setObjectName(QStringLiteral("actionClear_all_data"));
        actionPrint_current_best = new QAction(MainWindow);
        actionPrint_current_best->setObjectName(QStringLiteral("actionPrint_current_best"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget_m = new MainWidget(centralWidget);
        widget_m->setObjectName(QStringLiteral("widget_m"));
        widget_m->setMinimumSize(QSize(200, 200));

        gridLayout->addWidget(widget_m, 3, 0, 1, 1);

        widget_s = new MainWidget(centralWidget);
        widget_s->setObjectName(QStringLiteral("widget_s"));
        widget_s->setMinimumSize(QSize(200, 200));

        gridLayout->addWidget(widget_s, 3, 1, 1, 1);

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
        widget_e->setMinimumSize(QSize(200, 200));

        gridLayout->addWidget(widget_e, 0, 1, 1, 1);

        widget_y = new MainWidget(centralWidget);
        widget_y->setObjectName(QStringLiteral("widget_y"));
        widget_y->setMinimumSize(QSize(200, 200));

        gridLayout->addWidget(widget_y, 0, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 4, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_preview = new WidgetPreview(centralWidget);
        widget_preview->setObjectName(QStringLiteral("widget_preview"));

        verticalLayout->addWidget(widget_preview);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 590, 22));
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
        menuAdd->addAction(actionPrint_current_best);

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
        actionPrint_current_best->setText(QApplication::translate("MainWindow", "Print current best", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "EI", nullptr));
        label->setText(QApplication::translate("MainWindow", "f(x)", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "y_var", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "y_mean", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Next", nullptr));
        menuAdd->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
