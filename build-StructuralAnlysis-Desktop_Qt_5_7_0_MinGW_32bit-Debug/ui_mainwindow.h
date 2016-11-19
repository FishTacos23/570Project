/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave_Results;
    QAction *actionClear;
    QAction *actionJoints;
    QAction *actionMembers;
    QAction *actionProperties;
    QAction *actionConstraints;
    QAction *actionForces;
    QAction *actionUndo;
    QAction *actionRedo;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_Force;
    QPushButton *pushButton_solve;
    QCheckBox *checkBox_const;
    QGraphicsView *graphicsView;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_Disp;
    QLCDNumber *lcdNumber;
    QSlider *horizontalSlider_scaleDisp;
    QLabel *label;
    QPushButton *pushButton_Stress;
    QSpacerItem *verticalSpacer_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuInsert;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(502, 334);
        QIcon icon;
        icon.addFile(QStringLiteral("../build-StructuralAnlysis-Desktop_Qt_5_7_0_MinGW_32bit-Debug/10876-200.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave_Results = new QAction(MainWindow);
        actionSave_Results->setObjectName(QStringLiteral("actionSave_Results"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionJoints = new QAction(MainWindow);
        actionJoints->setObjectName(QStringLiteral("actionJoints"));
        actionMembers = new QAction(MainWindow);
        actionMembers->setObjectName(QStringLiteral("actionMembers"));
        actionProperties = new QAction(MainWindow);
        actionProperties->setObjectName(QStringLiteral("actionProperties"));
        actionConstraints = new QAction(MainWindow);
        actionConstraints->setObjectName(QStringLiteral("actionConstraints"));
        actionForces = new QAction(MainWindow);
        actionForces->setObjectName(QStringLiteral("actionForces"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        checkBox_Force = new QCheckBox(centralWidget);
        checkBox_Force->setObjectName(QStringLiteral("checkBox_Force"));

        gridLayout->addWidget(checkBox_Force, 4, 2, 1, 1);

        pushButton_solve = new QPushButton(centralWidget);
        pushButton_solve->setObjectName(QStringLiteral("pushButton_solve"));
        pushButton_solve->setEnabled(false);
        pushButton_solve->setAutoFillBackground(false);

        gridLayout->addWidget(pushButton_solve, 8, 2, 1, 1);

        checkBox_const = new QCheckBox(centralWidget);
        checkBox_const->setObjectName(QStringLiteral("checkBox_const"));

        gridLayout->addWidget(checkBox_const, 5, 2, 1, 1);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMouseTracking(true);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setDragMode(QGraphicsView::NoDrag);

        gridLayout->addWidget(graphicsView, 0, 0, 9, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 2, 1, 1);

        pushButton_Disp = new QPushButton(centralWidget);
        pushButton_Disp->setObjectName(QStringLiteral("pushButton_Disp"));
        pushButton_Disp->setEnabled(false);

        gridLayout->addWidget(pushButton_Disp, 6, 2, 1, 1);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 85, 127, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(0, 128, 191, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(0, 106, 159, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 42, 63, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 56, 84, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        lcdNumber->setPalette(palette);
        lcdNumber->setFrameShadow(QFrame::Plain);
        lcdNumber->setLineWidth(0);
        lcdNumber->setDigitCount(2);

        gridLayout->addWidget(lcdNumber, 9, 2, 1, 1);

        horizontalSlider_scaleDisp = new QSlider(centralWidget);
        horizontalSlider_scaleDisp->setObjectName(QStringLiteral("horizontalSlider_scaleDisp"));
        horizontalSlider_scaleDisp->setSliderPosition(0);
        horizontalSlider_scaleDisp->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_scaleDisp, 9, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 9, 1, 1, 1);

        pushButton_Stress = new QPushButton(centralWidget);
        pushButton_Stress->setObjectName(QStringLiteral("pushButton_Stress"));
        pushButton_Stress->setEnabled(false);

        gridLayout->addWidget(pushButton_Stress, 7, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 502, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuInsert = new QMenu(menuBar);
        menuInsert->setObjectName(QStringLiteral("menuInsert"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuInsert->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_Results);
        menuFile->addAction(actionClear);
        menuInsert->addAction(actionJoints);
        menuInsert->addAction(actionMembers);
        menuInsert->addAction(actionConstraints);
        menuInsert->addAction(actionForces);
        menuInsert->addAction(actionProperties);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);

        retranslateUi(MainWindow);
        QObject::connect(horizontalSlider_scaleDisp, SIGNAL(sliderMoved(int)), lcdNumber, SLOT(display(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Dyno-Sim", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionSave_Results->setText(QApplication::translate("MainWindow", "Save Results", 0));
        actionClear->setText(QApplication::translate("MainWindow", "Clear", 0));
        actionJoints->setText(QApplication::translate("MainWindow", "Joints", 0));
        actionMembers->setText(QApplication::translate("MainWindow", "Members", 0));
        actionProperties->setText(QApplication::translate("MainWindow", "Properties", 0));
        actionConstraints->setText(QApplication::translate("MainWindow", "Constraints", 0));
        actionForces->setText(QApplication::translate("MainWindow", "Forces", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0));
        checkBox_Force->setText(QApplication::translate("MainWindow", "Forces", 0));
        pushButton_solve->setText(QApplication::translate("MainWindow", "Solve", 0));
        checkBox_const->setText(QApplication::translate("MainWindow", "Constraints", 0));
        pushButton_Disp->setText(QApplication::translate("MainWindow", "Displacement", 0));
        label->setText(QApplication::translate("MainWindow", "Scale Factor:", 0));
        pushButton_Stress->setText(QApplication::translate("MainWindow", "Stress", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuInsert->setTitle(QApplication::translate("MainWindow", "Insert", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
