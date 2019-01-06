#include <utility>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QTextStream>
#include <QDebug>
#define dPair pair<double, double>

// https://data.lacity.org/A-Livable-and-Sustainable-City/Street-Centerline/7j4e-nn4z

using namespace std;

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
    friend bool operator==(const myNode &a, const myNode &b) {
        return (a.lat == b.lat && a.lng == b.lng);
    }
};

bool read(const QString &fileName, QJsonObject &json);
void loadJSON(const QString &fileName, QList<myNode> &points);
double getDistance(const double &lat1, const double &lon1, const double &lat2, const double &lon2);
double toRadians(const double &degree);
QString getFileName();
void saveConvertedData(const QList<myNode> &points);

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QList<myNode> points;
    QString fileToConvert("/Users/j/QtStuff/CS08/LAstreetDataConverter/laStreetCenterline.json");
    loadJSON(fileToConvert, points);
    saveConvertedData(points);
    return 0;
}

bool read(const QString &fileName, QJsonObject &json) {
    QFile file(fileName);
    QJsonParseError jerror;
    file.open(QIODevice::ReadOnly);
    QJsonDocument jdoc= QJsonDocument::fromJson(file.readAll(),&jerror);
    file.close();
    json = jdoc.object();
    return jerror.error == QJsonParseError::NoError;
}

void loadJSON(const QString &fileName, QList<myNode> &points) {
    QJsonObject json;
    if(!read(fileName, json))
        qDebug()<<"An error occurred during the reading of the JSON file";
    QJsonArray data = json["data"].toArray(), temp;
    for(int i=0; i<data.size(); ++i) {
        temp = data[i].toArray();
        if(temp.at(17) == "90041" || temp.at(17) == "90042" || temp.at(17) == "90065") {
            QString line(temp.at(8).toString());
            line = line.mid(18);
            line = line.mid(0,line.length()-2);
            QStringList coordinates(line.split(',')), point;
            double lat1, lng1, lat2, lng2;
            for(int i=0; i<coordinates.size(); ++i) {
                point = coordinates[i].split(' ');
                if(point.at(0) == "") {
                    lat2 = lat1;
                    lng2 = lng1;
                    lat1 = point.at(2).toDouble();
                    lng1 = point.at(1).toDouble();
                    points.append(myNode(lat2, lng2, lat1, lng1, getDistance(lat2, lng2, lat1, lng1)));
                } else {
                    lat1 = point.at(1).toDouble();
                    lng1 = point.at(0).toDouble();
                }
            }
        }
    }
}

QString getFileName() {
    QTextStream qcin(stdin);
    QString filename;
    qDebug() << "Please enter the file you wish to open for writing: ";
    qcin >> filename;
    fflush(stdin);
    return filename;
}

void saveConvertedData(const QList<myNode> &points) {
    QString filename = getFileName();
    QFile file(filename);
    QJsonObject graphToSave;
    QJsonArray connections;
    graphToSave["edges"] = static_cast<int>(points.size());
    for(int i = 0; i < points.size(); ++i) {
        QJsonObject link, from, to;
        from["lat"] = points[i].lat;
        from["lng"] = points[i].lng;
        to["lat"] = points[i].toLat;
        to["lng"] = points[i].toLng;
        link["from"] = from;
        link["to"] = to;
        link["weight"] = points[i].weight;
        connections.append(link);
    }
    graphToSave["connections"] = connections;
    QJsonDocument doc(graphToSave);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}

double getDistance(const double &lat1, const double &lon1, const double &lat2, const double &lon2) {
    double convert = 3959,
           x1 = toRadians(lat1),
           x2 = toRadians(lat2),
           deltaX = toRadians(lat2-lat1),
           deltaY = toRadians(lon2-lon1),
           c = sin(deltaX/2) * sin(deltaX/2) + cos(x1) * cos(x2) * sin(deltaY/2) * sin(deltaY/2),
           d = 2.0 * atan2(sqrt(c), sqrt(1-c));
    return fabs(convert * d);
}

double toRadians(const double &degree) {
    return degree * 4. * atan(1.) / 360.;
}
