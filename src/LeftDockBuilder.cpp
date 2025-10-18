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

const QString MODERN_BUTTON_STYLE = R"(
    QPushButton {
        background-color: #00A9A5;
        color: white;
        border: none;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: #008F8B;
    }
    QPushButton:pressed {
        background-color: #006B68;
    }
)";

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
            background-color: #f877ff;
            color: white;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 600;
            padding-left: 10px;
            padding-right: 10px;
        }
    )");

    QListWidget *listWidget = new QListWidget;
    listWidget->setStyleSheet(R"(
    QListWidget {
        background-color: #f5f7fa;
        color: #5C4033; /* Brown text */
        border: 1px solid #d0d0d0;
        border-radius: 6px;
        padding: 4px;
        font-size: 14px;
        outline: 0;
    }

    QListWidget::item {
        padding: 8px 12px;
        border: none;
        margin: 2px 0;
        color: #5C4033; /* Brown for normal items */
    }

    QListWidget::item:selected {
        background-color: #00A9A5;
        color: white; /* White text when selected */
        border-radius: 4px;
    }

    QListWidget::item:hover {
        background-color: #e0f7f6;
        border-radius: 4px;
    })");

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
    QPushButton *compileButton = new QPushButton("Compile");
    compileButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QPushButton *simulateButton = new QPushButton("Simulate");
    simulateButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QPushButton *synthesisButton = new QPushButton("Synthesis");
    synthesisButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QPushButton *implementationButton = new QPushButton("PnR");
    implementationButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QPushButton *layoutButton = new QPushButton("Generate Layout");
    layoutButton->setStyleSheet(MODERN_BUTTON_STYLE);

    QObject::connect(compileButton, &QPushButton::clicked, updateListFromJson);

    layout->addWidget(header);
    layout->addWidget(listWidget);
    layout->addWidget(compileButton);
    layout->addWidget(simulateButton);
    layout->addWidget(synthesisButton);
    layout->addWidget(implementationButton);
    layout->addWidget(layoutButton);


    container->setLayout(layout);
    OstivalleftDock->setWidget(container);
    OstivalleftDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
}

QDockWidget* LeftDockBuilder::getLeftDockWidget() const {
    return OstivalleftDock;
}
