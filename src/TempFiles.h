/*
========================================
Creating and handling Ostival Temp Files
----------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
----------------------------------------
*/

#ifndef TEMPFILES_H
#define TEMPFILES_H

#include <QString>

class TempFiles
{
public:
    static QString getTempFilePath();

    static bool tempFileExists();

    static void createTempFile(const QString& projectName, const QString& projectPath);

    static bool readTempFile(QString& projectName, QString& projectPath);

    static void ensureTempFileExists();

    static void deleteTempFile();
};




#endif