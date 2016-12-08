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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
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
    QAction *actionAbout;
    QAction *actionHelp_Document;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox_Force;
    QCheckBox *checkBox_const;
    QPushButton *pushButton_Disp;
    QPushButton *pushButton_Stress;
    QPushButton *pushButton_solve;
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSlider_scaleDisp;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuInsert;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(531, 451);
        QIcon icon;
        icon.addFile(QStringLiteral("../build-StructuralAnlysis-Desktop_Qt_5_7_0_MinGW_32bit-Debug/10876-200.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave_Results = new QAction(MainWindow);
        actionSave_Results->setObjectName(QStringLiteral("actionSave_Results"));
        actionSave_Results->setEnabled(false);
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
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionHelp_Document = new QAction(MainWindow);
        actionHelp_Document->setObjectName(QStringLiteral("actionHelp_Document"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMouseTracking(true);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setDragMode(QGraphicsView::NoDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(58, 56, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalSpacer_3 = new QSpacerItem(58, 57, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalSpacer = new QSpacerItem(68, 57, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        checkBox_Force = new QCheckBox(centralWidget);
        checkBox_Force->setObjectName(QStringLiteral("checkBox_Force"));

        verticalLayout->addWidget(checkBox_Force);

        checkBox_const = new QCheckBox(centralWidget);
        checkBox_const->setObjectName(QStringLiteral("checkBox_const"));

        verticalLayout->addWidget(checkBox_const);

        pushButton_Disp = new QPushButton(centralWidget);
        pushButton_Disp->setObjectName(QStringLiteral("pushButton_Disp"));
        pushButton_Disp->setEnabled(false);

        verticalLayout->addWidget(pushButton_Disp);

        pushButton_Stress = new QPushButton(centralWidget);
        pushButton_Stress->setObjectName(QStringLiteral("pushButton_Stress"));
        pushButton_Stress->setEnabled(false);

        verticalLayout->addWidget(pushButton_Stress);

        pushButton_solve = new QPushButton(centralWidget);
        pushButton_solve->setObjectName(QStringLiteral("pushButton_solve"));
        pushButton_solve->setEnabled(false);
        pushButton_solve->setAutoFillBackground(false);

        verticalLayout->addWidget(pushButton_solve);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSlider_scaleDisp = new QSlider(centralWidget);
        horizontalSlider_scaleDisp->setObjectName(QStringLiteral("horizontalSlider_scaleDisp"));
        horizontalSlider_scaleDisp->setSliderPosition(0);
        horizontalSlider_scaleDisp->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider_scaleDisp);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

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

        horizontalLayout->addWidget(lcdNumber);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        horizontalLayout->addWidget(progressBar);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 531, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuInsert = new QMenu(menuBar);
        menuInsert->setObjectName(QStringLiteral("menuInsert"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
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
        menuBar->addAction(menuHelp->menuAction());
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
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionHelp_Document);

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
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionHelp_Document->setText(QApplication::translate("MainWindow", "Help Document", 0));
        checkBox_Force->setText(QApplication::translate("MainWindow", "Forces", 0));
        checkBox_const->setText(QApplication::translate("MainWindow", "Constraints", 0));
        pushButton_Disp->setText(QApplication::translate("MainWindow", "Displacement", 0));
        pushButton_Stress->setText(QApplication::translate("MainWindow", "Stress", 0));
        pushButton_solve->setText(QApplication::translate("MainWindow", "Solve", 0));
        label->setText(QApplication::translate("MainWindow", "Scale Factor:", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuInsert->setTitle(QApplication::translate("MainWindow", "Insert", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
