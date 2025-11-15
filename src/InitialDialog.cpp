/*
================================
Dialog to init project path or create
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QRegularExpression>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include "InitialDialog.h"
#include "config.h"
#include "TempFiles.h"

InitialDialog::InitialDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Ostival Create New Project");
    setFixedSize(450, 150);

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setPlaceholderText("Enter project name");

    pathLineEdit = new QLineEdit(this);
    pathLineEdit->setPlaceholderText("Select a project location");
    pathLineEdit->setReadOnly(true);

    browseButton = new QPushButton("Browse...", this);
    openProjectButton = new QPushButton("Open Existing Project");
    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->setContentsMargins(0, 0, 0, 0);
    pathLayout->addWidget(pathLineEdit);
    pathLayout->addWidget(browseButton);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Project Name:", nameLineEdit);
    formLayout->addRow("Project Path:", pathLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(openProjectButton);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(browseButton, &QPushButton::clicked, this, &InitialDialog::browseForPath);
    connect(openProjectButton, &QPushButton::clicked, this, &InitialDialog::openExistingProject);
    connect(okButton, &QPushButton::clicked, this, &InitialDialog::validateAndAccept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void InitialDialog::openExistingProject(){
    QString filePath = QFileDialog::getOpenFileName(this, "Select a file");

    if (filePath.isEmpty()){
        QMessageBox::warning(this, "No File Selected", "No File Selected");
        return;
    }
    
    QFileInfo fileInfo(filePath);
    QString fileExtension = fileInfo.suffix();

    qDebug() << fileExtension;

    if (fileExtension.compare("ostival", Qt::CaseInsensitive) == 0) {
        projectFile = filePath;
        QDir parentDir = fileInfo.dir();
        QString folderName = parentDir.dirName();
        projectName = folderName;

        if (parentDir.cdUp()) {
            QString parentPath = parentDir.absolutePath();
            projectPath = parentPath;
        } else {
            qDebug() << "Cannot go up from the current path:" << parentDir;
            return;
        }
        qDebug() << projectPath;
        qDebug() << projectName;
        QMessageBox::warning(this, "Opening the project", "Ostival Project: " + projectName + " is opening.");
        accept();
    } else {
        qDebug() << "Error: File has an incorrect extension: " << fileExtension;
        QMessageBox::warning(this, "File Error", "File is incorrect");
        return;
    }
}

void InitialDialog::browseForPath(){
    QString directory = QFileDialog::getExistingDirectory(this,tr("Select Project Path"), QDir::homePath());
    if (!directory.isEmpty()) {
        pathLineEdit->setText(directory);
    }
}

void InitialDialog::validateAndAccept(){
    QString projectName = getProjectName();
    QString projectPath = getProjectPath();
    QString project = projectPath + "/" + projectName;
    QString project_design = projectPath + "/" + projectName + "/design_src";
    QString project_log = projectPath + "/" + projectName + "/all_log_files";
    QString project_tb = projectPath + "/" + projectName + "/testbench_src";
    QString project_py = projectPath + "/" + projectName + "/python_src";
    QRegularExpression re("^[A-Za-z0-9_]+$");

    if (projectName.isEmpty() || projectPath.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Project name and path cannot be empty.");
        return;
    }

    QDir dir(projectPath);

    if (dir.exists(projectName)) {
        QMessageBox::warning(this, "Project Exists","Opening Existing Project");
    } else{
        if(dir.mkdir(project)){
            dir.mkdir(project_design);
            dir.mkdir(project_log);
            dir.mkdir(project_tb);
            dir.mkdir(project_py);
            QMessageBox::warning(this, "Folder created","Project folder created\n");
        }else {
            QMessageBox::warning(this, "Something wrong","Something wrong!!! Path Invalid\n");
            qDebug() << project;
            return;
        }
    }

    accept();
}

QString InitialDialog::getProjectName() const
{
    return nameLineEdit->text().trimmed();
}

QString InitialDialog::getProjectPath() const
{
    return pathLineEdit->text();
}