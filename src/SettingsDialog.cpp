/*
================================
All app setting logics goes here
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Settings");
    setFixedSize(300, 150);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Settings go here", this);
    layout->addWidget(label);

    setLayout(layout);
}