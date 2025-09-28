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
#include "ToolCommunicator.h"

void cliHandler::setupParser(QCommandLineParser &parser)
{
    parser.setApplicationDescription(ABOUT_MESSAGE);
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({{"p", "proj"}, "Status of the current project"});
    parser.addOption({{"t", "tool"}, "Check for tools availability"});
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

    if (parser.isSet("tool")){
        /*
        VLSI Tool availability check
        */
        ToolCommunicator toolcheck;

        if(toolcheck.iverilogcheck()){
            qDebug().noquote() << RED  "iVerilog tool not found"  RESET;
        } else {
            qDebug().noquote() << GREEN  "*iVerilog tool found*"  RESET;
        }

        if(toolcheck.yosyscheck()){
            qDebug().noquote() << RED  "Yosys tool not found"  RESET;
        } else {
            qDebug().noquote() << GREEN  "*Yosys tool found*"  RESET;
        }
        
        if(toolcheck.magiccheck()){
            qDebug().noquote() << RED  "Magic tool not found"  RESET;
        } else {
            qDebug().noquote() << GREEN  "*Magic tool found*"  RESET;
        }

        if(toolcheck.netgencheck()){
            qDebug().noquote() << RED "Netgen tool not found"  RESET;
        } else {
            qDebug().noquote() << GREEN  "*Netgen tool found*"  RESET;
        }

        return 0;
    }

    return -1;
}
