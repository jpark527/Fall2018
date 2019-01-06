#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <QMap>
#include <vector>
#include <utility>
#include <queue>
#include <QList>
#include <cmath>
#include <QRegExp>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#define MAX 100001
#define myInt unsigned long long
#define myPair pair<long long, double>
#define dPair pair<double, double>
#define dif(x,y) fabs(x-y)
#define fireStation1 dPair(34.139548, -118.210927)
#define fireStation2 dPair(34.123918, -118.218535)
#define fireStation3 dPair(34.111193, -118.190268)
#define epsilon .0003

using namespace std;

enum METHOD {WRITE, READ};

struct myNode {
    double lat, lng;
    double toLat, toLng;
    double weight;
    myNode(const double &lat = 0, const double &lng = 0, const double &toLat = 0,
           const double &toLng = 0, const double &weight = 0) {
        this->toLat = toLat;
        this->toLng = toLng;
        this->lat = lat;
        this->lng = lng;
        this->weight = weight;
    }
    myNode(const myNode &other) {
        lat = other.lat;
        lng = other.lng;
        toLat = other.toLat;
        toLng = other.toLng;
        weight = other.weight;
    }

    friend bool operator<(const myNode &a, const myNode &b) {
        return a.lat < b.lat;
    }

    friend bool operator>(const myNode &a, const myNode &b) {
        return a.lat > b.lat;
    }

    friend bool operator==(const myNode &a, const myNode &b) {
        return (a.lat == b.lat && a.lng == b.lng);
    }
};

struct myComparator {
    bool operator() (const myPair &lhs, const myPair &rhs) const {
        return lhs.second > rhs.second;
    }
};

class pathFinder {
    QList<pair<myInt, double>> *graph;
    QMap<myInt, myNode> backwardsNodeRef;
    QMap<myNode, myInt> fowardNodeRef;
    QMap<myNode, QList<myNode>> connectRef;
    QList<double> distance;
    QList<myInt> *path;
    myInt starting, ending;
    QString fileName;
    dPair startPoint, endPoint;
    void copyAll(const pathFinder &other);
    void deleteAll();
    bool read(QJsonObject &json);
    void loadJSON();
    void initializeDistanceVector();
    bool isDestinationValid();
    bool findClosestFireStation();
    double getDistance(const dPair &p1, const dPair &p2) const;
    double toRadians(const double &degree) const;
    bool matchPoints(const dPair &point, myInt &index, const double &range);

public:
    pathFinder(const QString &file);
    ~pathFinder();
    pathFinder(const pathFinder &other);
    pathFinder& operator=(const pathFinder &other);
    void addDestination(const QStringList &p);
    void findShortestPath(QList<dPair> &routes);
    void dijkstra();
    void clear();
};

#endif // PATHFINDER_H
