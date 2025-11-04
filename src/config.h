/*
================================
Configuration for the application
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

#define APP_VERSION "1.0.0"
#define APP_NAME "Ostival GUI Desktop"
#define ABOUT_MESSAGE "Ostival Desktop is a toolkit for VLSI Design Flow\n From Verilog to GDSII\n Version 1.0.0\n\n Developed by Team Ostival"
#define DEV_TEAM "Team Ostival"
#define DOMAIN_NAME "ostival.org"

/*
Colors for command line interface.
*/
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

/*
Global variables to handle the project.
*/
extern QString projectName;
extern QString projectPath;
extern QString mainDesignFile;
extern QString mainTestbenchFile;
extern QString mainPythonFile;
extern QString defaultSyntax;

/*
User Interface constants
*/
const QString MODERN_TITLE_STYLE = R"(
        QLabel {
            background-color: #ff8808;
            color: white;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 600;
            padding-left: 10px;
            padding-right: 10px;
        }
    )";
;

const QString MODERN_LIST_STYLE = R"(
    QListWidget {
        background-color: #f5f7fa;
        color: #5C4033; /* Brown text */
        border: 1px solid #d0d0d0;
        border-radius: 6px;
        padding: 4px;
        font-size: 14px;
        outline: 0;
    }

    QListWidget::item {
        padding: 8px 12px;
        border: none;
        margin: 2px 0;
        color: #5C4033;
    }

    QListWidget::item:selected {
        background-color: #00A9A5;
        color: white;
        border-radius: 4px;
    }

    QListWidget::item:hover {
        background-color: #e0f7f6;
        border-radius: 4px;
    })";

#endif