/*
========================================
Creating and handling Ostival Temp Files
----------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
----------------------------------------
*/

#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "TempFiles.h"

QString TempFiles::getTempFilePath()
{
    QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    return QDir(tempDir).filePath("ostival_temp.json");
}

bool TempFiles::tempFileExists()
{
    return QFile::exists(getTempFilePath());
}

void TempFiles::createTempFile(const QString& projectName, const QString& projectPath)
{
    QJsonObject json;
    json["project_name"] = projectName;
    json["project_path"] = projectPath;

    QJsonDocument doc(json);

    QFile file(getTempFilePath());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "[TempFile] Created:" << getTempFilePath();
    } else {
        qWarning() << "[TempFile] Failed to create temp file.";
    }
}

bool TempFiles::readTempFile(QString& projectName, QString& projectPath)
{
    QFile file(getTempFilePath());
    if (!file.exists()) {
        qWarning() << "[TempFile] File does not exist.";
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "[TempFile] Failed to open file.";
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "[TempFile] JSON parse error:" << error.errorString();
        return false;
    }

    QJsonObject obj = doc.object();
    projectName = obj["project_name"].toString();
    projectPath = obj["project_path"].toString();

    return true;
}

void TempFiles::ensureTempFileExists()
{
    if (!tempFileExists()) {
        createTempFile("Ostival Project", "/tmp/ostival");
    }
}

void TempFiles::deleteTempFile()
{
    QFile::remove(getTempFilePath());
}
