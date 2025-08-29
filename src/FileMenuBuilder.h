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

class FileMenuBuilder : public QObject
{
    Q_OBJECT

public:
    explicit FileMenuBuilder(QMenuBar *menuBar, QWidget *parentWindow, QObject *parent = nullptr);

private slots:
    void onOpenFile();
    void onOpenFolder();
    void handleClear();
    void openSettingsDialog();

private:
    QMenuBar *OstivalmenuBar;
    QWidget *OstivalparentWindow;
};

#endif