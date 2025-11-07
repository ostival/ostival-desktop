/*
================================
All file menu logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QDateTime>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "FileMenuBuilder.h"
#include "InitialDialog.h"
#include "TempFiles.h"
#include "ProjectFileHandler.h"
#include "config.h"

FileMenuBuilder::FileMenuBuilder(QMenuBar *menuBar, QWidget *parentWindow, LeftDockBuilder *leftDock, RightDockBuilder *rightDock, QObject *parent)
    : QObject(parent), OstivalmenuBar(menuBar), OstivalparentWindow(parentWindow),OstivalleftDockBuilder(leftDock),OstivalrightDockBuilder(rightDock)
{
    QMenu *fileMenu = OstivalmenuBar->addMenu("File");

    QAction *openAction = fileMenu->addAction("Open Project");
    connect(openAction, &QAction::triggered, this, &FileMenuBuilder::onOpenFile);

    QAction *openFolderAction = fileMenu->addAction("Create New Project");
    connect(openFolderAction, &QAction::triggered, this, &FileMenuBuilder::onOpenFolder);    

    fileMenu->addSeparator();
    QAction *createVfile = fileMenu->addAction("Create Design file");
    connect(createVfile, &QAction::triggered, this, &FileMenuBuilder::createVerilogFile);

    QAction *createtbfile = fileMenu->addAction("Create Testbench file");
    connect(createtbfile, &QAction::triggered, this, &FileMenuBuilder::createTBFile);
    
    QAction *createpyfile = fileMenu->addAction("Create Python file");
    connect(createpyfile, &QAction::triggered, this, &FileMenuBuilder::createpyFile);

    fileMenu->addSeparator();
    QAction *clearAction = fileMenu->addAction("Clear");
    connect(clearAction, &QAction::triggered, this, &FileMenuBuilder::handleClear);

    fileMenu->addSeparator();

    QAction *exitAction = fileMenu->addAction("Exit");
    connect(exitAction, &QAction::triggered, OstivalparentWindow, &QWidget::close);

    // --- Edit Menu ---
    QMenu *editMenu = OstivalmenuBar->addMenu("Edit");
    QAction *cutAction = editMenu->addAction("Cut");
    fileMenu->addSeparator();
    QAction * copyAction = editMenu->addAction("Copy");

    // --- Run Flow Menu ---
    QMenu *flowMenu = OstivalmenuBar->addMenu("Run");
    QAction *compileAction = flowMenu->addAction("Compile");

    // --- Tools Menu ---
    QMenu *toolsMenu = OstivalmenuBar->addMenu("Tools");
    QAction *settingTool = toolsMenu->addAction("Ostival Settings");
    connect(settingTool, &QAction::triggered, this, &FileMenuBuilder::openSettingsDialog);

    // --- Reports Menu ---
    QMenu *reportsMenu = OstivalmenuBar->addMenu("Reports");
    QAction *synthesisReportAction = reportsMenu->addAction("Get Synthesis Report");

    // --- View Menu ---
    QMenu *viewMenu = OstivalmenuBar->addMenu("View");
    QAction *toggleLeftPanel = new QAction("Left Panel", this);
    toggleLeftPanel->setCheckable(true);
    toggleLeftPanel->setChecked(true);
    viewMenu->addAction(toggleLeftPanel);
    connect(toggleLeftPanel, &QAction::toggled,OstivalleftDockBuilder->getLeftDockWidget(), &QDockWidget::setVisible);
    connect(OstivalleftDockBuilder->getLeftDockWidget(), &QDockWidget::visibilityChanged,toggleLeftPanel, &QAction::setChecked);

    QAction *toggleRightPanel = new QAction("Right Panel", this);
    toggleRightPanel->setCheckable(true);
    toggleRightPanel->setChecked(true);
    viewMenu->addAction(toggleRightPanel);
    connect(toggleRightPanel, &QAction::toggled,OstivalrightDockBuilder->getRightDockWidget(), &QDockWidget::setVisible);
    connect(OstivalrightDockBuilder->getRightDockWidget(), &QDockWidget::visibilityChanged,toggleRightPanel, &QAction::setChecked);

    // --- Help Menu ---
    QMenu *helpMenu = OstivalmenuBar->addMenu("Help");
    QAction *aboutAction = helpMenu->addAction("About");
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(OstivalparentWindow, "About Ostival", ABOUT_MESSAGE);
    });
}

void FileMenuBuilder::createVerilogFile() {
    QDialog dialog(OstivalparentWindow);
    dialog.setWindowTitle("Create Design File");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QLabel *label = new QLabel("Enter Verilog file name (e.g., alu_core):", &dialog);
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QLabel *errorLabel = new QLabel(&dialog);
    errorLabel->setStyleSheet("color: red;");

    QPushButton *okButton = new QPushButton("Create", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(errorLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    QObject::connect(okButton, &QPushButton::clicked, [&]() {
        QString fileName = lineEdit->text().trimmed();

        // Validation
        if (fileName.isEmpty()) {
            errorLabel->setText("Please enter a file name.");
            lineEdit->setFocus();
            return;
        }

        QRegularExpression validName("^[A-Za-z_][A-Za-z0-9_]*$");
        if (!validName.match(fileName).hasMatch()) {
            errorLabel->setText("Invalid name. Use only letters, digits, and underscores.\nMust not start with a number.");
            lineEdit->setFocus();
            return;
        }

        fileName = fileName.toLower();
        QString verilogPath = projectPath + "/" + projectName + "/design_src/" + fileName + ".v";

        if (QFile::exists(verilogPath)) {
            errorLabel->setText("File already exists!");
            lineEdit->setFocus();
            return;
        }

        // Create Verilog file
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QFile file(verilogPath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            errorLabel->setText("Can't open file: " + file.errorString());
            return;
        }

        QTextStream out(&file);
        out << "// File created using Ostival\n";
        out << "// Created on: " << timestamp << "\n";
        out << "// Filename: " << fileName << ".v\n";
        file.close();

        qDebug() << "File created successfully:" << verilogPath;

        // Append filename to JSON ("src_files")
        QString jsonPath = projectPath + "/" + projectName + "/" + projectName + ".ostival";

        QFile jsonFile(jsonPath);
        if (!jsonFile.exists()) {
            qWarning() << "JSON file not found:" << jsonPath;
            dialog.accept();
            return;
        }

        if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Can't open JSON file for reading:" << jsonFile.errorString();
            dialog.accept();
            return;
        }

        QByteArray jsonData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (!doc.isObject()) {
            qWarning() << "Invalid JSON structure.";
            dialog.accept();
            return;
        }

        QJsonObject root = doc.object();
        QJsonArray srcFiles = root["src_files"].toArray();

        if (!srcFiles.contains(fileName + ".v")) {
            srcFiles.append(fileName + ".v");
            root["src_files"] = srcFiles;
            doc.setObject(root);

            if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                jsonFile.write(doc.toJson(QJsonDocument::Indented));
                jsonFile.close();
                qDebug() << "Added" << fileName + ".v" << "to src_files in JSON.";
            } else {
                qWarning() << "Failed to open JSON for writing:" << jsonFile.errorString();
            }
        } else {
            qDebug() << "File already listed in src_files.";
        }

        dialog.accept();
    });

    dialog.exec();
}

void FileMenuBuilder::createTBFile() {
    QDialog dialog(OstivalparentWindow);
    dialog.setWindowTitle("Create Design File");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QLabel *label = new QLabel("Enter Verilog testbench name (e.g., alu_core):", &dialog);
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QLabel *errorLabel = new QLabel(&dialog);
    errorLabel->setStyleSheet("color: red;");

    QPushButton *okButton = new QPushButton("Create", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(errorLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    QObject::connect(okButton, &QPushButton::clicked, [&]() {
        QString fileName = lineEdit->text().trimmed();

        // Validation
        if (fileName.isEmpty()) {
            errorLabel->setText("Please enter a file name.");
            lineEdit->setFocus();
            return;
        }

        QRegularExpression validName("^[A-Za-z_][A-Za-z0-9_]*$");
        if (!validName.match(fileName).hasMatch()) {
            errorLabel->setText("Invalid name. Use only letters, digits, and underscores.\nMust not start with a number.");
            lineEdit->setFocus();
            return;
        }

        fileName = fileName.toLower();
        QString verilogPath = projectPath + "/" + projectName + "/testbench_src/" + fileName + "_tb.v";

        if (QFile::exists(verilogPath)) {
            errorLabel->setText("File already exists!");
            lineEdit->setFocus();
            return;
        }

        // Create Verilog file
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QFile file(verilogPath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            errorLabel->setText("Can't open file: " + file.errorString());
            return;
        }

        QTextStream out(&file);
        out << "// File created using Ostival\n";
        out << "// Created on: " << timestamp << "\n";
        out << "// Filename: " << fileName << "_tb.v\n";
        file.close();

        qDebug() << "File created successfully:" << verilogPath;

        // Append filename to JSON ("src_files")
        QString jsonPath = projectPath + "/" + projectName + "/" + projectName + ".ostival";

        QFile jsonFile(jsonPath);
        if (!jsonFile.exists()) {
            qWarning() << "JSON file not found:" << jsonPath;
            dialog.accept();
            return;
        }

        if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Can't open JSON file for reading:" << jsonFile.errorString();
            dialog.accept();
            return;
        }

        QByteArray jsonData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (!doc.isObject()) {
            qWarning() << "Invalid JSON structure.";
            dialog.accept();
            return;
        }

        QJsonObject root = doc.object();
        QJsonArray srcFiles = root["testbench_files"].toArray();

        if (!srcFiles.contains(fileName + "_tb.v")) {
            srcFiles.append(fileName + "_tb.v");
            root["testbench_files"] = srcFiles;
            doc.setObject(root);

            if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                jsonFile.write(doc.toJson(QJsonDocument::Indented));
                jsonFile.close();
                qDebug() << "Added" << fileName + "_tb.v" << "to testbench_files in JSON.";
            } else {
                qWarning() << "Failed to open JSON for writing:" << jsonFile.errorString();
            }
        } else {
            qDebug() << "File already listed in testbench_files.";
        }

        dialog.accept();
    });

    dialog.exec();
}

void FileMenuBuilder::createpyFile() {
    QDialog dialog(OstivalparentWindow);
    dialog.setWindowTitle("Create Python File");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QLabel *label = new QLabel("Enter Verilog file name (e.g., my_script):", &dialog);
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QLabel *errorLabel = new QLabel(&dialog);
    errorLabel->setStyleSheet("color: red;");

    QPushButton *okButton = new QPushButton("Create", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(errorLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    QObject::connect(okButton, &QPushButton::clicked, [&]() {
        QString fileName = lineEdit->text().trimmed();

        // Validation
        if (fileName.isEmpty()) {
            errorLabel->setText("Please enter a file name.");
            lineEdit->setFocus();
            return;
        }

        QRegularExpression validName("^[A-Za-z_][A-Za-z0-9_]*$");
        if (!validName.match(fileName).hasMatch()) {
            errorLabel->setText("Invalid name. Use only letters, digits, and underscores.\nMust not start with a number.");
            lineEdit->setFocus();
            return;
        }

        fileName = fileName.toLower();
        QString pyPath = projectPath + "/" + projectName + "/python_src/" + fileName + ".py";

        if (QFile::exists(pyPath)) {
            errorLabel->setText("File already exists!");
            lineEdit->setFocus();
            return;
        }

        // Create Verilog file
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QFile file(pyPath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            errorLabel->setText("Can't open file: " + file.errorString());
            return;
        }

        QTextStream out(&file);
        out << "# File created using Ostival\n";
        out << "# Created on: " << timestamp << "\n";
        out << "# Filename: " << fileName << ".py\n";
        file.close();

        qDebug() << "Python File created successfully:" << pyPath;

        // Append filename to JSON ("python_files")
        QString jsonPath = projectPath + "/" + projectName + "/" + projectName + ".ostival";

        QFile jsonFile(jsonPath);
        if (!jsonFile.exists()) {
            qWarning() << "JSON file not found:" << jsonPath;
            dialog.accept();
            return;
        }

        if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Can't open JSON file for reading:" << jsonFile.errorString();
            dialog.accept();
            return;
        }

        QByteArray jsonData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (!doc.isObject()) {
            qWarning() << "Invalid JSON structure.";
            dialog.accept();
            return;
        }

        QJsonObject root = doc.object();
        QJsonArray srcFiles = root["python_files"].toArray();

        if (!srcFiles.contains(fileName + ".py")) {
            srcFiles.append(fileName + ".py");
            root["python_files"] = srcFiles;
            doc.setObject(root);

            if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                jsonFile.write(doc.toJson(QJsonDocument::Indented));
                jsonFile.close();
                qDebug() << "Added" << fileName + ".py" << "to src_files in JSON.";
            } else {
                qWarning() << "Failed to open JSON for writing:" << jsonFile.errorString();
            }
        } else {
            qDebug() << "File already listed in src_files.";
        }

        dialog.accept();
    });

    dialog.exec();
}

void FileMenuBuilder::onOpenFile(){
    QString filePath = QFileDialog::getOpenFileName(OstivalparentWindow, "Select a file");
    if (!filePath.isEmpty())
        qDebug() << "Selected file:" << filePath;
    
    QFileInfo fileInfo(filePath);
    QString fileExtension = fileInfo.suffix();

    if (fileExtension.compare("ostival", Qt::CaseInsensitive) == 0) {
        projectFile = filePath;
        qDebug() << "File has the correct .ostival extension.";
        QDir parentDir = fileInfo.dir();

        QString folderName = parentDir.dirName();
        projectName = folderName;

        if (parentDir.cdUp()) {
        QString parentPath = parentDir.absolutePath();
        projectPath = parentPath;
        } else {
            qDebug() << "Cannot go up from the current path:" << parentDir;
        }
        qDebug() << projectPath;
        qDebug() << projectName;
        TempFiles::createTempFile(projectName,projectPath);
        emit reloadRequested();
        QMessageBox::about(OstivalparentWindow, "Opening the project", projectName + " is opening");
    } else {
        qDebug() << "Error: File has an incorrect extension: " << fileExtension;
    }
}

void FileMenuBuilder::onOpenFolder(){
    if(TempFiles::tempFileExists()){                            // If temp file exists, it means there is a history of the project. Check history and 
        InitialDialog dialog;                                   //Initial dialog box is added so that user can choose project path and project name.

        if (dialog.exec() == QDialog::Accepted) {
            projectName = dialog.getProjectName();                      //Project path is the main directory for the project.
            projectPath = dialog.getProjectPath();                      //Project name is the identifier for the project.
            TempFiles::createTempFile(projectName,projectPath);         //Create temp file
            ProjectFileHandler project_file;
            project_file.createInitialfile();
        } else {
            qDebug() << "Cancel Pressed\n";
        }
    } else {                                                    // It there is not temp file, it means no history, and create one.
        qDebug() << "There is not temp file, someone deleted it.\n";
    }
}

void FileMenuBuilder::handleClear(){
    qDebug() << "Clear triggered from FileMenuBuilder";
}

void FileMenuBuilder::openSettingsDialog(){
    SettingsDialog dialog(OstivalparentWindow);
    dialog.exec();
}