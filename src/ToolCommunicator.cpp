/*
========================================
All VLSI tools processes
----------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
----------------------------------------
*/

#include "ToolCommunicator.h"


int ToolCommunicator::iverilogcheck(){
    QProcess process;

    process.start("iverilog", QStringList() << "-v");

    if(!process.waitForStarted()){
        // qDebug() << "Something wrong"; 
        return -1;
    }

    if(!process.waitForFinished()){
        // qDebug() << "Something wrong";
        return -1;
    }

    return 0;
}

int ToolCommunicator::yosyscheck(){
    QProcess process;

    process.start("yosys", QStringList() << "--version");

    if(!process.waitForStarted()){
        // qDebug() << "Something wrong"; 
        return -1;
    }

    if(!process.waitForFinished()){
        // qDebug() << "Something wrong";
        return -1;
    }

    return 0;
}

int ToolCommunicator::magiccheck(){
    QProcess process;

    process.start("magic", QStringList() << "--version");

    if(!process.waitForStarted()){
        // qDebug() << "Something wrong"; 
        return -1;
    }

    if(!process.waitForFinished()){
        // qDebug() << "Something wrong";
        return -1;
    }

    return 0;
}

int ToolCommunicator::netgencheck(){
    QProcess process;

    process.start("netgen", QStringList() << "-v");

    if(!process.waitForStarted()){
        // qDebug() << "Something wrong"; 
        return -1;
    }

    if(!process.waitForFinished()){
        // qDebug() << "Something wrong";
        return -1;
    }

    return 0;
}

int ToolCommunicator::gitcheck(){
    QProcess process;
    process.start("git", QStringList() << "-v");
    if(!process.waitForStarted()){
        return -1;                      // something wrong
    }

    if(!process.waitForFinished()){     // something wrong
        return -1;
    }

    return 0;
}

int ToolCommunicator::pythoncheck(){
    QProcess process;
    process.start("python", QStringList() << "--version");
    if(!process.waitForStarted()){
        return -1;                      // something wrong
    }

    if(!process.waitForFinished()){     // something wrong
        return -1;
    }

    return 0;
}

int ToolCommunicator::python3check(){
    QProcess process;
    process.start("python3", QStringList() << "--version");
    if(!process.waitForStarted()){
        return -1;                      // something wrong
    }

    if(!process.waitForFinished()){     // something wrong
        return -1;
    }

    return 0;
}
