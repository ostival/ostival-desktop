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

class ToolCommunicator 
{
    public:
    int iverilogcheck();
    int yosyscheck();
    int magiccheck();
    int netgencheck();

};

#endif