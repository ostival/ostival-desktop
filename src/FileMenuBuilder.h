/*
================================
All file menu logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#ifndef FILEMENUBUILDER_H
#define FILEMENUBUILDER_H

#include <QObject>
#include <QMenuBar>
#include "SettingsDialog.h"
#include "LeftDockBuilder.h"
#include "RightDockBuilder.h"

class FileMenuBuilder : public QObject
{
    Q_OBJECT

public:
    FileMenuBuilder(QMenuBar *menuBar, QWidget *parentWindow, LeftDockBuilder *leftDock, RightDockBuilder *rightDock, QObject *parent = nullptr);

private slots:
    void createVerilogFile();
    void createTBFile();
    void createpyFile();
    void onOpenFile();
    void onOpenFolder();
    void handleClear();
    void openSettingsDialog();

signals:
    void reloadRequested();

private:
    QMenuBar *OstivalmenuBar;
    QWidget *OstivalparentWindow;
    LeftDockBuilder *OstivalleftDockBuilder;
    RightDockBuilder *OstivalrightDockBuilder;
};

#endif