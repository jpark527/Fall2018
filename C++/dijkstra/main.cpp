#include <QCoreApplication>
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <cmath>
#include <QRegExp>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QTextStream>

using namespace std;

#define MAX 100001
#define u_int unsigned int
#define u_intPair pair< u_int, u_int >
#define pb(x) push_back(x)

struct myComparator {
    bool operator() (const u_intPair &lhs, const u_intPair &rhs) const {
        return lhs.second > rhs.second;
    }
};

enum METHOD {WRITE, READ};

QString getFileName(METHOD method);
bool read(QString filename, QJsonObject &json);
bool createGraph(u_int &verticies, u_int &edges, vector<u_intPair> *&graph);
void dijkstra(vector<u_intPair> *&graph, u_int starting, u_int *&distance);
void getStarting(u_int &starting);
void displayResult(u_int verticies, u_int *distance);
void initializeDistanceVector(u_int verticies, u_int starting, u_int *&distance);
void manuallyCreateGraph(u_int &verticies, u_int &edges, vector<u_intPair> *&graph);
void saveGraph(bool directed, u_int &verticies, u_int &edges, vector<u_intPair> *graph);
bool loadJSON(u_int &verticies, u_int &edges, vector<u_intPair> *&graph);

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    string s;
    vector<u_intPair> *graph = new vector<u_intPair>[MAX];
    u_int *distance = new u_int[MAX];
    u_int verticies, edges, starting;
    while(createGraph(verticies, edges, graph)) {
        getStarting(starting);
        // initialize distance vector
        cout<<"Initializing distance vector"<<endl;
        initializeDistanceVector(verticies, starting, distance);
        // dijkstra
        cout<<"Performing Dijkstra's Algorithm"<<endl;
        dijkstra(graph, starting, distance);
        // result
        cout<<"Here are the results from Vertex "<<starting<<" to all other verticies"<<endl;
        displayResult(verticies,distance);
        getline(cin, s);
    }
    delete[] graph;
    delete[] distance;
    return 0;
}

void displayResult(u_int verticies, u_int *distance) {
    for (u_int i = 0; i < verticies; ++i)
        cout << "Node " << i << ", min weight = " << distance[i] << endl;
}

void initializeDistanceVector(u_int verticies, u_int starting, u_int *&distance) {
    for (u_int i = 0; i < verticies; ++i)
        distance[i] = 65535;
    distance[starting] = 0;
}

void getStarting(u_int &starting) {
    cout << "Enter the source node: ";
    cin >> starting;
}

void dijkstra(vector<u_intPair> *&graph, u_int starting, u_int *&distance) {
    u_int source, destination, weight, size;
    bool *visited = new bool[MAX];
    priority_queue<u_intPair, vector<u_intPair>, myComparator> priorityQueue;
    priorityQueue.push(u_intPair(starting, 0));
    for(u_int i = 0; i < MAX; ++i)
        visited[i] = false;
    while (!priorityQueue.empty()) {
        source = priorityQueue.top().first;
        priorityQueue.pop();
        if (visited[source])
            continue;
        size = graph[source].size();
        for (u_int i = 0; i < size; ++i) {
            destination = graph[source][i].first;
            weight = graph[source][i].second;
            if (!visited[destination] && (distance[source] + weight < distance[destination])) {
                distance[destination] = distance[source] + weight;
                priorityQueue.push(u_intPair(destination, distance[destination]));
            }
        }
        visited[source] = true; // done with this vertex.
    }
    delete[] visited;
}

void manuallyCreateGraph(u_int &verticies, u_int &edges, vector<u_intPair> *&graph) {
    u_int source, destination, weight;
    string ans;
    bool directed;
    cout << "Please enter the number of vertices in the graph: ";
    cin >> verticies;
    cout<<"Please enter the number of edges in the graph: ";
    cin >> edges;
    cout<<"Is this a directed graph? ";
    cin >> ans;
    directed = (toupper(ans[0]) == 'Y');
    cout << "Please enter the edges with weight in this format: <source> <destination> <weigth>: \n";
    for (u_int i = 0; i < edges; i++) {
        cout<<"Edge: "<<i<<": ";
        cin >> source >> destination >> weight;
        graph[source].pb(u_intPair(destination, weight));
        if(!directed)
            graph[destination].pb(u_intPair(source, weight)); // for undirected
    }
    if(!directed)
        edges *= 2;
    saveGraph(directed, verticies, edges, graph);
}

QString getFileName(METHOD method) {
    bool repeat = true;
//    int pos;
    QTextStream qcin(stdin);
    QString filename, ans;
    while(repeat) {
        cout<<"Please enter the file you wish to open for "<<(method ? "reading: " : "writing: ");
        qcin >> filename;
        fflush(stdin);
        if(!filename.endsWith(".json")) {
            if(filename.indexOf('.') != -1)
                filename = filename.remove(QRegExp("\\.[^.]*$"));
            filename += ".json";
        }
        QFile file(filename);
        if(file.open((QIODevice::ReadOnly))) {
            switch(method) {
                case READ : repeat = false;
                            break;
                case WRITE : cout<<"That file already exists. Do you wish to overwrite it? ";
                             qcin >> ans;
                             fflush(stdin);
                             if(ans.toUpper()[0] == 'Y')
                                 repeat = false;
            }
        } else {
            switch(method) {
                case WRITE : repeat = false;
                             break;
                case READ : cout<<"That file does not exist. Please enter a new file name. "<<endl;
            }
        }
        file.close();
    }
    return filename;
}

void saveGraph(bool directed, u_int &verticies, u_int &edges, vector<u_intPair> *graph) {
    QString filename = getFileName(WRITE);
    QFile file(filename);
    QJsonObject graphToSave;
    QJsonArray connections;
    graphToSave["directed"] = directed;
    graphToSave["verticies"] = static_cast<int>(verticies);
    graphToSave["edges"] = static_cast<int>(edges);
    for(u_int i = 0; i < edges; ++i)
        for(u_int j = 0; j < graph[i].size(); ++j) {
            QJsonObject link;
            link["from"] = static_cast<int>(i);
            link["to"] = static_cast<int>(graph[i][j].first);
            link["weight"] = static_cast<int>(graph[i][j].second);
            connections.append(link);
        }
    graphToSave["connections"] = connections;
    QJsonDocument doc(graphToSave);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}


bool createGraph(u_int &verticies, u_int &edges, vector<u_intPair> *&graph) {
    string input;
    bool cont = true;
    while(cont) {
        fflush(stdin);
        cout<<"Would you like to load (L) a file or manually enter a graph (M) (blank line ends program): ";
        getline(cin,input);

        if(input.empty())
            return false;
        switch(toupper(input[0])) {
            case 'M' : manuallyCreateGraph(verticies, edges, graph);
                       cont = false;
                       break;

            case 'L' : cont = loadJSON(verticies, edges, graph);
                       break;

            default  : cout<<"Unknown option. Please try again."<<endl;
        }
    }
    return true;
}

bool read(QString filename, QJsonObject &json) {
    QFile file(filename);
    QJsonParseError jerror;
    file.open(QIODevice::ReadOnly);
    QJsonDocument jdoc= QJsonDocument::fromJson(file.readAll(),&jerror);
    file.close();
    json = jdoc.object();
    return jerror.error == QJsonParseError::NoError;
}

bool loadJSON(u_int &verticies, u_int &edges, vector<u_intPair> *&graph) {
    QString filename = getFileName(READ);
    QJsonObject json, data;
    int to, from, weight;
    if(!read(filename, json)) {
        cout<<"An error occurred during the reading of the JSON file"<<endl;
        return true;
    }
    edges = static_cast<u_int>(json["edges"].toInt());
    verticies = static_cast<u_int>(json["verticies"].toInt());
    QJsonArray connections = json["connections"].toArray();
    for(int i = 0; i < connections.size(); ++i) {
        data = connections[i].toObject();
        to = data["to"].toInt();
        from = data["from"].toInt();
        weight = data["weight"].toInt();
        cout<<"from: "<<from<<" to: "<<to<<" weight: "<<weight<<endl;
        graph[from].push_back(pair<int,int>(to,weight));
    }
    return false;
}
