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
extern QString projectFile;
extern QString mainDesignFile;
extern QString mainTestbenchFile;
extern QString mainPythonFile;
extern QString defaultSyntax;

/*
User Interface constants
*/
const QString MODERN_LANDING_DIALOG_STYLE = "QDialog {"
            "background-color: #2b2b2b;"
            "color: #f0f0f0;"
            "border: 1px solid #555555;"
        "}"
        "QLineEdit {"
            "background-color: #3c3c3c;"
            "border: 1px solid #555555;"
            "color: #f0f0f0;"
        "}"
        "QPushButton {"
            "background-color: #00A9A5;"
            "color: #ffffff;"
            "border: 1px solid #00A9A5;"
            "border-radius: 8px;"
            "padding: 6px 8px;"
        "}"

        "QPushButton:hover {"
            "background-color: #008785;"
            "border: 1px solid #008785;"
        "}"

        "QPushButton:pressed {"
            "background-color: #01d0cd;"
        "}"
        "QLabel {"
            "color: #f0f0f0;"
        "}"
        "QLineEdit {"
            "border-radius: 5px;"
            "border: 1px solid gray;"
        "}";


const QString MODERN_TITLE_STYLE = R"(
        QLabel {
            background-color: #2caa8d;
            color: #e1e1e1;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 400;
        }
    )";

const QString MODERN_LIST_STYLE = R"(
    QListWidget {
        background-color: #effffc;
        color: #000000;
        border: 1px solid #610707;
        border-radius: 6px;
        padding: 2px;
        font-size: 14px;
    }

    QListWidget::item {
        padding: 4px 3px;
        border: none;
        margin: 2px 0;
    }

    QListWidget::item:selected {
        background-color: #00A9A5;
        border-radius: 4px;
    }

    QListWidget::item:hover {
        background-color: #3292ca;
        border-radius: 4px;
    })";

    const QString MODERN_BUTTON_STYLE = R"(
        QPushButton {
            background-color: #5c9102;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #008F8B;
        }
        QPushButton:pressed {
            background-color: #006B68;
        }
    )";

    const QString MODERN_BUTTON_STYLE1 = R"(
        QPushButton {
            background-color: #00A9A5;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #008F8B;
        }
        QPushButton:pressed {
            background-color: #006B68;
        }
    )";

    const QString MODERN_BUTTON_STYLE2 = R"(
        QPushButton {
            background-color: #99CC00;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #008F8B;
        }
        QPushButton:pressed {
            background-color: #006B68;
        }
    )";

    const QString MODERN_BUTTON_STYLE3 = R"(
        QPushButton {
            background-color: #80B300;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #008F8B;
        }
        QPushButton:pressed {
            background-color: #006B68;
        }
    )";

    const QString MODERN_BUTTON_STYLE4 = R"(
        QPushButton {
            background-color: #669900;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #008F8B;
        }
        QPushButton:pressed {
            background-color: #006B68;
        }
    )";

    const QString MODERN_BUTTON_STYLE5 = R"(
        QPushButton {
            background-color: #4D8000;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #008F8B;
        }
        QPushButton:pressed {
            background-color: #006B68;
        }
    )";

#endif