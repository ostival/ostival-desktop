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

FileMenuBuilder::FileMenuBuilder(QMenuBar *menuBar, QWidget *parentWindow, QObject *parent)
    : QObject(parent), m_menuBar(menuBar), m_parentWindow(parentWindow)
{
    QMenu *fileMenu = m_menuBar->addMenu("File");

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
    connect(exitAction, &QAction::triggered, m_parentWindow, &QWidget::close);

    // --- Edit Menu ---
    QMenu *editMenu = m_menuBar->addMenu("Edit");
    QAction *cutAction = editMenu->addAction("Cut");
    fileMenu->addSeparator();
    QAction * copyAction = editMenu->addAction("Copy");

    // --- Run Flow Menu ---
    QMenu *flowMenu = m_menuBar->addMenu("Run");
    QAction *compileAction = flowMenu->addAction("Compile");

    // --- Tools Menu ---
    QMenu *toolsMenu = m_menuBar->addMenu("Tools");
    QAction *settingTool = toolsMenu->addAction("Ostival Settings");
    connect(settingTool, &QAction::triggered, this, &FileMenuBuilder::openSettingsDialog);

    // --- Reports Menu ---
    QMenu *reportsMenu = m_menuBar->addMenu("Reports");
    QAction *synthesisReportAction = reportsMenu->addAction("Get Synthesis Report");

    // --- View Menu ---
    QMenu *viewMenu = m_menuBar->addMenu("View");
    QAction *exampleView = viewMenu->addAction("Something");

    // --- Help Menu ---
    QMenu *helpMenu = m_menuBar->addMenu("Help");
    QAction *aboutAction = helpMenu->addAction("About");
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(m_parentWindow, "About Ostival", ABOUT_MESSAGE);
    });
}

void FileMenuBuilder::onOpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(m_parentWindow, "Select a file");
    if (!filePath.isEmpty())
        qDebug() << "Selected file:" << filePath;
}

void FileMenuBuilder::onOpenFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(m_parentWindow, "Select a folder");
    if (!folderPath.isEmpty())
        qDebug() << "Selected folder:" << folderPath;
}

void FileMenuBuilder::handleClear()
{
    qDebug() << "Clear triggered from FileMenuBuilder";
}

void FileMenuBuilder::openSettingsDialog()
{
    SettingsDialog dialog(m_parentWindow);
    dialog.exec();
}