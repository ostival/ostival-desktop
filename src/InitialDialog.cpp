/*
================================
Dialog to init project path or create
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QRegularExpression>
#include "InitialDialog.h"
#include <QDebug>


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
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(browseButton, &QPushButton::clicked, this, &InitialDialog::browseForPath);
    connect(okButton, &QPushButton::clicked, this, &InitialDialog::validateAndAccept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void InitialDialog::browseForPath()
{
    QString directory = QFileDialog::getExistingDirectory(this,tr("Select Project Path"), QDir::homePath());

    if (!directory.isEmpty()) {
        pathLineEdit->setText(directory);
    }
}

void InitialDialog::validateAndAccept()
{
    QString projectName = getProjectName();
    QString projectPath = getProjectPath();
    QString project = projectPath + "/" + projectName;
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