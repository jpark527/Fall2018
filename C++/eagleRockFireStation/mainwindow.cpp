#include "mainwindow.h"

// Public
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    this->setWindowTitle("Eagle Rock Fire Stations");
    initialize();
    setupWebEngine();
    setupSignalsAndSlots();
    setupLayout();
}

MainWindow::~MainWindow() {
    delete accessNetwork;
    delete pFinder;
    delete channel;
    delete view;
    delete loadButton;
    delete navigateButton;
    delete streetViewButton;
    delete quitButton;
    delete layout;
    delete main;
}

// Private
void MainWindow::initialize() {
    QFile style("styleSheet.qss");
    style.open(QIODevice::ReadOnly);
    this->setStyleSheet(style.readAll());
    main = new QWidget;
    loadButton = new QPushButton("Load Map");
    navigateButton = new QPushButton("Navigate");
    streetViewButton = new QPushButton("Street View");
    quitButton = new QPushButton("Quit");
    this->setCentralWidget(main);
    pFinder = new pathFinder("convertedData.json");
    accessNetwork = new QNetworkAccessManager(this);
}

void MainWindow::setupSignalsAndSlots() {
    connect(navigateButton,SIGNAL(clicked(bool)),this,SLOT(findPath()));
    connect(loadButton,SIGNAL(clicked(bool)),this,SLOT(loadMap()));
    connect(streetViewButton,SIGNAL(clicked(bool)),this,SLOT(loadStreetView()));
    connect(quitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(accessNetwork, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkFinished(QNetworkReply*)));
}

void MainWindow::setupLayout() {
    hl = new QHBoxLayout;
    vl = new QVBoxLayout;
    vl2 = new QVBoxLayout;
    vl->addWidget(loadButton);
    vl->addWidget(navigateButton);
    vl2->addWidget(streetViewButton);
    vl2->addWidget(quitButton);
    hl->addLayout(vl);
    hl->addLayout(vl2);
    layout = new BorderLayout;
    layout->addWidget(view, BorderLayout::Center);
    layout->add(hl, BorderLayout::South);
    main->setLayout(layout);
}

void MainWindow::setupWebEngine() {
    view = new QWebEngineView;
    channel = new QWebChannel(view->page());
    view->page()->setWebChannel(channel);
    channel->registerObject(QStringLiteral("mainwindow"), this);
    page = view->page();
}

void MainWindow::updateLatLong() {
    page->runJavaScript("pos;",[this](const QVariant &v) { dest = v.toString(); });
}

// Slots
void MainWindow::loadMap() {
    QDir dir("map.html");
    page->load(QUrl(QUrl::fromLocalFile(dir.canonicalPath())));
}

void MainWindow::loadStreetView() {
    if(dest.isEmpty())
        return ;
    if(dest.at(0) == 'L') {
        dest = dest.mid(7);
        dest = dest.mid(0, dest.length()-1);
    }
    QString address("http://maps.googleapis.com/maps/api/streetview?key=*******YOUR_API_KEY&size=600x400&location=");
    address += dest;
    QUrl url(address);
    QNetworkRequest request(url);
    accessNetwork->get(request);
}

void MainWindow::networkFinished(QNetworkReply *reply) {
    QByteArray urlData = reply->readAll();
    QPixmap urlImg;
    urlImg.loadFromData(urlData);
    QMessageBox mBox;
    mBox.setIconPixmap(urlImg);
    mBox.setStandardButtons(QMessageBox::Ok);
    mBox.setDefaultButton(QMessageBox::Ok);
    mBox.exec();
}

void MainWindow::findPath() {
    page->runJavaScript("clearRoutes();");
    if(dest.isEmpty())
        return ;
    if(dest.at(0) == 'L') {
        dest = dest.mid(7);
        dest = dest.mid(0, dest.length()-1);
    }
    QStringList coordinates(dest.split(','));
    routes.clear();
    pFinder->clear();
    pFinder->addDestination(coordinates);
    pFinder->findShortestPath(routes);
    for(int i=0; i<routes.size(); ++i)
        emit sendCoordinate(routes[i].first, routes[i].second, !i || i==routes.size()-1 ? true : false);
}
