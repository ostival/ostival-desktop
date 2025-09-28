/*
================================
To handle command line interface
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include <QDebug>
#include "config.h"
#include "cliHandler.h"
#include "TempFiles.h"

void cliHandler::setupParser(QCommandLineParser &parser)
{
    parser.setApplicationDescription(ABOUT_MESSAGE);
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({{"p", "proj"}, "Status of the current project"});
    parser.addOption({{"t2", "test2"}, "Test2 command, will be replaced with useful command"});
}

int cliHandler::run(QCommandLineParser &parser)
{
    if (parser.isSet("proj")) {
        if(TempFiles::tempFileExists()){
            TempFiles::readTempFile(projectName, projectPath);
            qDebug() << "Project Path:" << projectPath;
            qDebug() << "Project Name:" << projectName;
            qDebug() << "Temp File Path:" << TempFiles::getTempFilePath();
        } else {
            qDebug() << "There is no active project. Please create one.";
        }
        return 0;
    }

    if (parser.isSet("test2")) {
        qDebug() << "Test2 command, will be replaced with useful command";
        return 0;
    }

    return -1;
}
