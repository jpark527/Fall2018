#include "pathfinder.h"

// Public
pathFinder::pathFinder(const QString &file) {
    fileName = file;
    graph = new QList<pair<myInt, double>>[MAX];
    loadJSON();
    path = new QList<myInt>[connectRef.size()];
}

pathFinder::~pathFinder() {
    deleteAll();
}

pathFinder::pathFinder(const pathFinder &other) {
    copyAll(other);
}

pathFinder& pathFinder::operator=(const pathFinder &other) {
    if(this != &other) {
        deleteAll();
        copyAll(other);
    }
    return *this;
}

void pathFinder::clear() {
    starting = ending = 0;
    startPoint = endPoint = dPair();
    for(int i=0; i<connectRef.size(); ++i) {
        path[i].clear();
        path[i].append(i);
    }
}

void pathFinder::findShortestPath(QList<dPair> &routes) {
    if(!isDestinationValid())
        return ;
    findClosestFireStation();
    dijkstra();
    for(int i=0; i<path[ending].size(); ++i)
        routes.append(dPair(backwardsNodeRef[path[ending][i]].lat, backwardsNodeRef[path[ending][i]].lng));
}

// Private
void pathFinder::copyAll(const pathFinder &other) {
    memcpy(graph, other.graph, sizeof(QList<pair<myInt, double>>)*MAX);
    memcpy(path, other.path, sizeof(QList<myInt>)*other.connectRef.size());
    fileName = other.fileName;
    starting = other.starting;
    ending = other.ending;
    startPoint = other.startPoint;
    endPoint = other.endPoint;
    backwardsNodeRef = other.backwardsNodeRef;
    fowardNodeRef = other.fowardNodeRef;
    connectRef = other.connectRef;
    distance = other.distance;
    backwardsNodeRef.detach();
    fowardNodeRef.detach();
    connectRef.detach();
    distance.detach();
}

void pathFinder::deleteAll() {
    delete[] graph;
    delete[] path;
    backwardsNodeRef.clear();
    fowardNodeRef.clear();
    connectRef.clear();
    distance.clear();
    fileName.clear();
    starting = ending = 0;
    startPoint = endPoint = dPair();
}

bool pathFinder::read(QJsonObject &json) {
    QFile file(fileName);
    QJsonParseError jerror;
    file.open(QIODevice::ReadOnly);
    QJsonDocument jdoc= QJsonDocument::fromJson(file.readAll(),&jerror);
    file.close();
    json = jdoc.object();
    return jerror.error == QJsonParseError::NoError;
}

void pathFinder::loadJSON() {
    QJsonObject json, fromObj, toObj;
    if(!read(json))
        qDebug()<<"An error occurred during the reading of the JSON file";
    myInt numOfEdges = (myInt)json["edges"].toDouble(), h = 0;
    for(myInt i = 0; i< numOfEdges; ++i) {
        fromObj = json["connections"].toArray()[i].toObject()["from"].toObject();
        toObj = json["connections"].toArray()[i].toObject()["to"].toObject();
        myNode direct(fromObj["lat"].toDouble(), fromObj["lng"].toDouble(), toObj["lat"].toDouble(), toObj["lng"].toDouble(), json["connections"].toArray()[i].toObject()["weight"].toDouble()),
               transitive(toObj["lat"].toDouble(), toObj["lng"].toDouble(), fromObj["lat"].toDouble(), fromObj["lng"].toDouble(), json["connections"].toArray()[i].toObject()["weight"].toDouble());
        connectRef[direct].append(direct);
        connectRef[transitive].append(transitive);
    }
    for(QMap<myNode, QList<myNode>>::iterator it=connectRef.begin(); it != connectRef.end(); ++it) {
        backwardsNodeRef[h] = it.key();
        fowardNodeRef[it.key()] = h++;
    }
    for(QMap<myNode, QList<myNode>>::iterator it=connectRef.begin(); it != connectRef.end(); ++it)
        for(int j = 0; j<it.value().size(); ++j)
            graph[fowardNodeRef[it.key()]].append(pair<myInt, double>(fowardNodeRef[myNode(it.value()[j].toLat, it.value()[j].toLng)], it.value()[j].weight));
}

void pathFinder::addDestination(const QStringList &p) {
    endPoint.first = p[0].toDouble();
    endPoint.second = p[1].toDouble();
}

void pathFinder::initializeDistanceVector() {
    distance.clear();
    for (int i = 0; i < connectRef.size(); ++i)
        distance.append(99999.);
    distance[starting] = 0;
}

bool pathFinder::matchPoints(const dPair &point, myInt &index, const double &range) {
    for(int i=0; i<backwardsNodeRef.size(); ++i)
        if(dif(backwardsNodeRef[i].lat, point.first) < range && dif(backwardsNodeRef[i].lng, point.second) < range) {
            index = i;
            return true;
        }
    return false;
}

bool pathFinder::isDestinationValid() {
    return matchPoints(endPoint, ending, epsilon)   || matchPoints(endPoint, ending, epsilon*2) ||
           matchPoints(endPoint, ending, epsilon*3) || matchPoints(endPoint, ending, epsilon*4) ||
           matchPoints(endPoint, ending, epsilon*5) || matchPoints(endPoint, ending, epsilon*6) ||
           matchPoints(endPoint, ending, epsilon*7) || matchPoints(endPoint, ending, epsilon*8);
}

bool pathFinder::findClosestFireStation() {
    double one = getDistance(endPoint, fireStation1), two = getDistance(endPoint, fireStation2),
           three = getDistance(endPoint, fireStation3),
           smallest = min(one, two) == one ? min(one, three) : min(two, three);
    if(one == smallest)
        startPoint = fireStation1;
    else if(two == smallest)
        startPoint = fireStation2;
    else
        startPoint = fireStation3;
    return matchPoints(startPoint, starting, epsilon) || matchPoints(startPoint, starting, epsilon*2);
}

double pathFinder::getDistance(const dPair &p1, const dPair &p2) const {
    double convert = 3959,
           x1 = toRadians(p1.first),
           x2 = toRadians(p2.first),
           deltaX = toRadians(p2.first-p1.first),
           deltaY = toRadians(p2.second-p1.second),
           c = sin(deltaX/2) * sin(deltaX/2) + cos(x1) * cos(x2) * sin(deltaY/2) * sin(deltaY/2),
           d = 2.0 * atan2(sqrt(c), sqrt(1-c));
    return fabs(convert * d);
}

double pathFinder::toRadians(const double &degree) const {
    return degree * 4. * atan(1.) / 360.;
}

void pathFinder::dijkstra() {
    double weight;
    myInt source, destination;
    bool *visited = new bool[MAX];
    priority_queue<myPair, vector<myPair>, myComparator> priorityQueue;
    priorityQueue.push(myPair(starting, 0));
    initializeDistanceVector();
    for(myInt i = 0; i < MAX; ++i)
        visited[i] = false;
    while (!priorityQueue.empty()) {
        source = priorityQueue.top().first;
        priorityQueue.pop();
        if (visited[source])
            continue;
        for (int i = 0; i < graph[source].size(); ++i) {
            destination = graph[source][i].first;
            weight = graph[source][i].second;
            if (!visited[destination] && (distance[source] + weight < distance[destination])) {
                path[destination].clear();
                path[destination].append(path[source]);
                path[destination].append(destination);
                distance[destination] = distance[source] + weight;
                priorityQueue.push(myPair(destination, distance[destination]));
            }
        }
        visited[source] = true;
    }
    path[ending].append(ending);
    delete[] visited;
}
