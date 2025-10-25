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

    QLabel *design_header  = new QLabel("Design Files");
    design_header->setAlignment(Qt::AlignCenter);
    design_header->setFixedHeight(20);
    design_header->setStyleSheet(MODERN_TITLE_STYLE);

    QLabel *tb_header  = new QLabel("Testbench Files");
    tb_header->setAlignment(Qt::AlignCenter);
    tb_header->setFixedHeight(20);
    tb_header->setStyleSheet(MODERN_TITLE_STYLE);

    QLabel *py_header  = new QLabel("Python Files");
    py_header->setAlignment(Qt::AlignCenter);
    py_header->setFixedHeight(20);
    py_header->setStyleSheet(MODERN_TITLE_STYLE);

    QListWidget *listWidget = new QListWidget;                  // Design Files
    listWidget->setStyleSheet(MODERN_LIST_STYLE);

    QListWidget *listWidget1 = new QListWidget;                 // Testbench Files
    listWidget1->setStyleSheet(MODERN_LIST_STYLE);

    QListWidget *listWidget2 = new QListWidget;                 // Python Files
    listWidget2->setStyleSheet(MODERN_LIST_STYLE);

    QString jsonpath = projectPath + "/" + projectName + "/" + projectName + ".ostival";

    // To load src_files from JSON into the list
    auto updateListFromJson = [listWidget, listWidget1, listWidget2, jsonpath]() {
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

        QJsonArray arr1 = doc.object()["testbench_files"].toArray();
        qDebug() << "Found" << arr1.size() << "files in JSON:" << arr1;

        QJsonArray arr2 = doc.object()["python_files"].toArray();
        qDebug() << "Found" << arr2.size() << "files in JSON:" << arr2;

        listWidget->clear();
        for (auto v : arr)
            listWidget->addItem(v.toString());
        
        listWidget1->clear();
        for (auto v : arr1)
            listWidget1->addItem(v.toString());

        listWidget2->clear();
        for (auto v : arr2)
            listWidget2->addItem(v.toString());
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
            fileName = "/design_src/" + fileName;
            qDebug() << "User double-clicked file:" << fileName;
            emit fileDoubleClicked(fileName);
        }
    });

    listWidget1->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(listWidget1, &QListWidget::itemDoubleClicked, [=](QListWidgetItem *item){
        if (item) {
            QString fileName = item->text();
            fileName = "/testbench_src/" + fileName;
            qDebug() << "User double-clicked file:" << fileName;
            emit fileDoubleClicked(fileName);
        }
    });

    listWidget2->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(listWidget2, &QListWidget::itemDoubleClicked, [=](QListWidgetItem *item){
        if (item) {
            QString fileName = item->text();
            fileName = "/python_src/" + fileName;
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

    layout->addWidget(design_header);
    layout->addWidget(listWidget);
    layout->addWidget(tb_header);
    layout->addWidget(listWidget1);
    layout->addWidget(py_header);
    layout->addWidget(listWidget2);

    container->setLayout(layout);
    OstivalleftDock->setWidget(container);
    OstivalleftDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
}

QDockWidget* LeftDockBuilder::getLeftDockWidget() const {
    return OstivalleftDock;
}
