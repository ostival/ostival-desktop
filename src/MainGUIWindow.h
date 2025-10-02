/*
================================
All main window logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#ifndef MAIN_GUI_WINDOW_H
#define MAIN_GUI_WINDOW_H

#include <QMainWindow>
#include "RightDockBuilder.h"
#include "StatusBarBuilder.h"
#include "LeftDockBuilder.h"

class MainGUIWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainGUIWindow(QWidget *parent = nullptr);
    ~MainGUIWindow() override = default; 
    friend class ToolBarBuilder;

private:
    RightDockBuilder *OstivalrightDockBuilder = nullptr;
    StatusBarBuilder *OstivalstatusBarBuilder = nullptr;
    LeftDockBuilder *OstivalleftDockBuilder = nullptr;
    
};

#endif