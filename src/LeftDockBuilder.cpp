/*
================================
All left dock logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFileSystemWatcher>
#include <QMenu>
#include <QAction>
#include "LeftDockBuilder.h"
#include "config.h"

LeftDockBuilder::LeftDockBuilder(QMainWindow *mainWindow, QObject *parent)
    : QObject(parent), OstivalmainWindow(mainWindow)
{
    OstivalleftDock = new QDockWidget("Left Panel", OstivalmainWindow);
    OstivalmainWindow->addDockWidget(Qt::LeftDockWidgetArea, OstivalleftDock);

    QWidget *container = new QWidget;
    container->setStyleSheet(R"(
        QWidget {
            background-color: #f2ffdb;
            border-radius: 12px;
            border: 1px solid #CCCCCC;
        }
    )");

    QVBoxLayout *layout = new QVBoxLayout(container);

    QLabel *header = new QLabel("Project Navigation");
    header->setAlignment(Qt::AlignCenter);
    header->setFixedHeight(40);
    header->setStyleSheet(R"(
        QLabel {
            background-color: #002b73;
            color: white;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 600;
            padding-left: 10px;
            padding-right: 10px;
        }
    )");

    QListWidget *listWidget = new QListWidget;

    QString jsonpath = projectPath + "/" + projectName + "/" + projectName + ".ostival";

    // To load src_files from JSON into the list
    auto updateListFromJson = [listWidget, jsonpath]() {
        QFile f(jsonpath);
        if (!f.open(QIODevice::ReadOnly)) {
            qWarning() << "Can't open JSON file:" << jsonpath << f.errorString();
            listWidget->clear();
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
        f.close();

        QJsonArray arr = doc.object()["src_files"].toArray();
        qDebug() << "Found" << arr.size() << "files in JSON:" << arr;

        listWidget->clear();
        for (auto v : arr)
            listWidget->addItem(v.toString());
    };

    // Initial load
    updateListFromJson();

    // Watch JSON for changes
    QFileSystemWatcher *watcher = new QFileSystemWatcher(this);
    watcher->addPath(jsonpath);
    QObject::connect(watcher, &QFileSystemWatcher::fileChanged, [updateListFromJson](const QString &){
        qDebug() << "JSON file changed, updating list...";
        updateListFromJson();
    });

    listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(listWidget, &QListWidget::itemDoubleClicked, [=](QListWidgetItem *item){
        if (item) {
            QString fileName = item->text();
            qDebug() << "User double-clicked file:" << fileName;
            emit fileDoubleClicked(fileName);
        }
    });

    QObject::connect(listWidget, &QListWidget::customContextMenuRequested,
                     [=](const QPoint &pos) {
        QListWidgetItem *item = listWidget->itemAt(pos);
        if (!item) return;

        QMenu menu;
        QAction *deleteAction = menu.addAction("Delete File");

        QAction *selectedAction = menu.exec(listWidget->viewport()->mapToGlobal(pos));
        if (selectedAction == deleteAction) {
            QString fileName = item->text();
            QString filePath = projectPath + "/" + projectName + "/design_src/" + fileName;

            QFile file(filePath);
            if (file.exists() && file.remove()) {
                qDebug() << "Deleted file:" << filePath;

                QFile f(jsonpath);
                if (f.open(QIODevice::ReadOnly)) {
                    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
                    f.close();

                    QJsonObject obj = doc.object();
                    QJsonArray arr = obj["src_files"].toArray();
                    QJsonArray newArr;
                    for (auto v : arr) {
                        if (v.toString() != fileName) newArr.append(v.toString());
                    }
                    obj["src_files"] = newArr;

                    if (f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                        f.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
                        f.close();
                    }
                }

                // Remove from list
                delete listWidget->takeItem(listWidget->row(item));
            } else {
                qWarning() << "Failed to delete file:" << filePath;
            }
        }
    });

    // Refresh button
    QPushButton *refreshButton = new QPushButton("Refresh");
    refreshButton->setStyleSheet(R"(
        QPushButton {
            background-color: #196042;
            color: white;
            border-radius: 10px;
            padding: 6px 12px;
            font-size: 14px;
        }
        QPushButton:hover { background-color: #002b73; }
        QPushButton:pressed { background-color: #9cd304; }
    )");
    QObject::connect(refreshButton, &QPushButton::clicked, updateListFromJson);

    layout->addWidget(header);
    layout->addWidget(listWidget);
    layout->addWidget(refreshButton);

    container->setLayout(layout);
    OstivalleftDock->setWidget(container);
    OstivalleftDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
}

QDockWidget* LeftDockBuilder::getLeftDockWidget() const {
    return OstivalleftDock;
}
