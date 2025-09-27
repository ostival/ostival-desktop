/*
================================
To handle command line interface
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#ifndef CLIHANDLER_H
#define CLIHANDLER_H

#include <QCommandLineParser>
#include <QCoreApplication>

class cliHandler {
public:
    static void setupParser(QCommandLineParser &parser);
    static int run(QCommandLineParser &parser);
};

#endif