/*
================================
For handling project related files
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QString>
#include "ProjectFileHandler.h"
#include "config.h"

int ProjectFileHandler::checkFile(){
    QString path = projectPath + "/" + projectName + "/" + projectName + ".ostival";
    return QFile::exists(path);
}

void ProjectFileHandler::createInitialfile(){
    qDebug() << "hello time to create the file";
    QString path = projectPath + "/" + projectName + "/" + projectName + ".ostival";

    QJsonObject projectJson;

    projectJson["ProjectPath"] = projectPath;
    projectJson["ProjectName"] = projectName;
    projectJson["src_files"] = "";
    projectJson["testbench_files"] = "";
    projectJson["python_files"] = "";


    QJsonDocument doc(projectJson);

    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "can't open the file for writing the issue is" << file.errorString();
    } else {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "file created success" << path;
    }

}