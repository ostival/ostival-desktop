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

#endif