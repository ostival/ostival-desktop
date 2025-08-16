/*
================================
Dialog to init project path or create
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#ifndef INITIALDIALOG_H
#define INITIALDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QString>

class QPushButton;

class InitialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitialDialog(QWidget *parent = nullptr);

    QString getProjectName() const;
    QString getProjectPath() const;

private slots:
    void browseForPath();
    void validateAndAccept();

private:
    QLineEdit *nameLineEdit;
    QLineEdit *pathLineEdit;
    QPushButton *browseButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif
