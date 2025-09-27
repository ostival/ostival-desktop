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

void cliHandler::setupParser(QCommandLineParser &parser)
{
    parser.setApplicationDescription(ABOUT_MESSAGE);
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({{"t1", "test1"}, "Test1 command, will be replaced with useful command"});
    parser.addOption({{"t2", "test2"}, "Test2 command, will be replaced with useful command"});
}

int cliHandler::run(QCommandLineParser &parser)
{
    if (parser.isSet("test1")) {
        qDebug() << "Test1 command, will be replaced with useful command";
        return 0;
    }

    if (parser.isSet("test2")) {
        qDebug() << "Test2 command, will be replaced with useful command";
        return 0;
    }

    return -1;
}
