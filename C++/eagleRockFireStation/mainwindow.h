#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QWebEnginePage>
#include <QWebEngineView>
#include <QWebChannel>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QPushButton>
#include <borderlayout.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QUrl>
#include <QPixmap>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "pathfinder.h"



class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        Q_INVOKABLE void updateLatLong();

    signals:
        void sendCoordinate(double, double, bool);

    private:
        QWebEngineView *view;
        QWebEnginePage *page;
        QWebChannel *channel;
        QString httpString, dest;
        QPushButton *loadButton, *navigateButton, *streetViewButton, *quitButton;
        BorderLayout *layout;
        QHBoxLayout *hl;
        QVBoxLayout *vl, *vl2;
        QWidget *main;
        pathFinder *pFinder;
        QNetworkAccessManager *accessNetwork;
        QList<dPair> routes;

        void initialize();
        void setupWebEngine();
        void setupLayout();
        void setupSignalsAndSlots();

    private slots:
        void loadMap();
        void loadStreetView();
        void findPath();
        void networkFinished(QNetworkReply *reply);
};

#endif // MAINWINDOW_H
