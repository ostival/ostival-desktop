/*
================================
All file menu logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include "FileMenuBuilder.h"
#include "config.h"

FileMenuBuilder::FileMenuBuilder(QMenuBar *menuBar, QWidget *parentWindow, LeftDockBuilder *leftDock, RightDockBuilder *rightDock, QObject *parent)
    : QObject(parent), OstivalmenuBar(menuBar), OstivalparentWindow(parentWindow),OstivalleftDockBuilder(leftDock),OstivalrightDockBuilder(rightDock)
{
    QMenu *fileMenu = OstivalmenuBar->addMenu("File");

    fileMenu->addSeparator();

    QAction *openAction = fileMenu->addAction("Open");
    connect(openAction, &QAction::triggered, this, &FileMenuBuilder::onOpenFile);

    fileMenu->addSeparator();

    QAction *openFolderAction = fileMenu->addAction("Open Folder");
    connect(openFolderAction, &QAction::triggered, this, &FileMenuBuilder::onOpenFolder);

    fileMenu->addSeparator();

    QAction *clearAction = fileMenu->addAction("Clear");
    connect(clearAction, &QAction::triggered, this, &FileMenuBuilder::handleClear);

    fileMenu->addSeparator();

    QAction *exitAction = fileMenu->addAction("Exit");
    connect(exitAction, &QAction::triggered, OstivalparentWindow, &QWidget::close);

    // --- Edit Menu ---
    QMenu *editMenu = OstivalmenuBar->addMenu("Edit");
    QAction *cutAction = editMenu->addAction("Cut");
    fileMenu->addSeparator();
    QAction * copyAction = editMenu->addAction("Copy");

    // --- Run Flow Menu ---
    QMenu *flowMenu = OstivalmenuBar->addMenu("Run");
    QAction *compileAction = flowMenu->addAction("Compile");

    // --- Tools Menu ---
    QMenu *toolsMenu = OstivalmenuBar->addMenu("Tools");
    QAction *settingTool = toolsMenu->addAction("Ostival Settings");
    connect(settingTool, &QAction::triggered, this, &FileMenuBuilder::openSettingsDialog);

    // --- Reports Menu ---
    QMenu *reportsMenu = OstivalmenuBar->addMenu("Reports");
    QAction *synthesisReportAction = reportsMenu->addAction("Get Synthesis Report");

    // --- View Menu ---
    QMenu *viewMenu = OstivalmenuBar->addMenu("View");
    QAction *toggleLeftPanel = new QAction("Left Panel", this);
    toggleLeftPanel->setCheckable(true);
    toggleLeftPanel->setChecked(true);
    viewMenu->addAction(toggleLeftPanel);
    connect(toggleLeftPanel, &QAction::toggled,OstivalleftDockBuilder->getLeftDockWidget(), &QDockWidget::setVisible);
    connect(OstivalleftDockBuilder->getLeftDockWidget(), &QDockWidget::visibilityChanged,toggleLeftPanel, &QAction::setChecked);

    QAction *toggleRightPanel = new QAction("Right Panel", this);
    toggleRightPanel->setCheckable(true);
    toggleRightPanel->setChecked(true);
    viewMenu->addAction(toggleRightPanel);
    connect(toggleRightPanel, &QAction::toggled,OstivalrightDockBuilder->getRightDockWidget(), &QDockWidget::setVisible);
    connect(OstivalrightDockBuilder->getRightDockWidget(), &QDockWidget::visibilityChanged,toggleRightPanel, &QAction::setChecked);

    // --- Help Menu ---
    QMenu *helpMenu = OstivalmenuBar->addMenu("Help");
    QAction *aboutAction = helpMenu->addAction("About");
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(OstivalparentWindow, "About Ostival", ABOUT_MESSAGE);
    });
}

void FileMenuBuilder::onOpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(OstivalparentWindow, "Select a file");
    if (!filePath.isEmpty())
        qDebug() << "Selected file:" << filePath;
}

void FileMenuBuilder::onOpenFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(OstivalparentWindow, "Select a folder");
    if (!folderPath.isEmpty())
        qDebug() << "Selected folder:" << folderPath;
}

void FileMenuBuilder::handleClear()
{
    qDebug() << "Clear triggered from FileMenuBuilder";
}

void FileMenuBuilder::openSettingsDialog()
{
    SettingsDialog dialog(OstivalparentWindow);
    dialog.exec();
}