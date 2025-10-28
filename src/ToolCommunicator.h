/*
========================================
All VLSI tools processes
----------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
----------------------------------------
*/

#ifndef TOOLCOMMUNICATOR_H
#define TOOLCOMMUNICATOR_H

#include <QProcess>
#include <QDebug>

class ToolCommunicator 
{
    public:
    int iverilogcheck();
    int yosyscheck();
    int magiccheck();
    int netgencheck();
    int gitcheck();
    int pythoncheck();
    int python3check();
};

#endif