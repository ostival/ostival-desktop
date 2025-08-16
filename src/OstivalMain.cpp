/*
================================
The main function of the GUI Application
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include <QApplication>
#include <QDebug>
#include <QCommandLineParser>
#include "config.h"
#include "MainGUIWindow.h"
#include "InitialDialog.h"


int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    // Application Metadata
    app.setApplicationName(APP_NAME);
    app.setApplicationDisplayName(APP_NAME);
    app.setApplicationVersion(APP_VERSION);
    app.setOrganizationName(DEV_TEAM);
    app.setOrganizationDomain(DOMAIN_NAME);

    // Command line parser
    QCommandLineParser parser;
    parser.setApplicationDescription(ABOUT_MESSAGE);
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(app);
    
    qDebug() << "Ostival Desktop Started";

    InitialDialog dialog;

    if (dialog.exec() == QDialog::Accepted)
    {
        projectName = dialog.getProjectName();
        projectPath = dialog.getProjectPath();

        MainGUIWindow window;
        window.setWindowTitle("Ostival Desktop");
        window.showMaximized();

        qDebug() << projectPath;

        return app.exec();
    }

    return 0;
}