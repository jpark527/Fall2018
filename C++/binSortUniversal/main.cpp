#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

enum DIRECTION {MIN_SORT, MAX_SORT};

using namespace std;

// Int
void binsortI(vector<int> &list, bool dir);
void goBinsortI(vector<int> &list, bool dir);
// Double
void binsortD(vector<double> &list, bool dir);
void goBinsortD(vector<double> &list, bool dir);
// String
void binsortS(vector<string> &list, bool dir);

void setType(char &type);
void run(char type);
bool again();
template <typename T>
void addData(vector<T> &v, DIRECTION &dir);
template <typename T>
void display(vector<T> &v, const string &name);

int main() {
    char type = '\0';
    do {
        setType(type);
        run(type);
    } while(again());

    return 0;
}

// Int
void binsortI(vector<int> &list, bool dir) {
    vector<int> plus, minus;
    for(size_t i=0; i<list.size(); ++i) {
        if(to_string(list[i]).at(0)=='-')
            minus.push_back(stoi(to_string(list[i]).substr(1)));
        else
            plus.push_back(list[i]);
    }
    goBinsortI(minus, !dir);
    goBinsortI(plus, dir);
    list.clear();
    for(size_t i=0; i<minus.size(); ++i)
        minus[i] = -1*minus[i];
    if(dir) {
        list.insert(list.end(), plus.begin(), plus.end());
        list.insert(list.end(), minus.begin(), minus.end());
    } else {
        list.insert(list.end(), minus.begin(), minus.end());
        list.insert(list.end(), plus.begin(), plus.end());
    }
}

void goBinsortI(vector<int> &list, bool dir) {
    int power = 1, endIndex = dir ? 9 : 0, ten = 10;
    vector<int> bins[ten];
    while(bins[endIndex].size() != list.size()) {
        for(int i = 0; i < ten; ++i)
            bins[i].clear();
        for(size_t i = 0; i < list.size(); ++i)
            bins[dir ? (9 - ((list[i]/power) % ten)) : ((list[i]/power) % ten)].push_back(list[i]);
        power *= ten;
        list.clear();
        for(int i = 0; i < ten; ++i)
            list.insert(list.end(), bins[i].begin(), bins[i].end());
    }
}

// Double
void binsortD(vector<double> &list, bool dir) {
    vector<double> plus, minus;
    for(size_t i=0; i<list.size(); ++i) {
        if(to_string(list[i]).at(0)=='-')
            minus.push_back(stod(to_string(list[i]).substr(1)));
        else
            plus.push_back(list[i]);
    }
    goBinsortD(minus, !dir);
    goBinsortD(plus, dir);
    list.clear();
    for(size_t i=0; i<minus.size(); ++i)
        minus[i] = -1*minus[i];
    if(dir) {
        list.insert(list.end(), plus.begin(), plus.end());
        list.insert(list.end(), minus.begin(), minus.end());
    } else {
        list.insert(list.end(), minus.begin(), minus.end());
        list.insert(list.end(), plus.begin(), plus.end());
    }
}

void goBinsortD(vector<double> &list, bool dir) {
    int index, power = 1, endIndex = dir ? 9 : 0, eleven = 11, ten = 10;
    string data;
    vector<double> bins[eleven];
    while(bins[ten].size() != list.size()) {
        for(int i = 0; i < eleven; ++i)
            bins[i].clear();
        for(size_t i = 0; i < list.size(); ++i) {
            data = to_string(list[i]);
            index = data[data.length()-power]=='.' ? ten : data[data.length()-power]-'0';
            bins[dir && index<10 ? 9 - index : index].push_back(list[i]);
        }
        power += 1;
        list.clear();
        for(int i = 0; i < eleven; ++i)
            list.insert(list.end(), bins[i].begin(), bins[i].end());
    }
    power = 1;
    while(bins[endIndex].size() != list.size()) {
        for(int i = 0; i < ten; ++i)
            bins[i].clear();
        for(size_t i = 0; i < list.size(); ++i)
            bins[dir ? (9 - (int(list[i]/power) % ten)) : (int(list[i]/power) % ten)].push_back(list[i]);
        power *= ten;
        list.clear();
        for(int i = 0; i < ten; ++i)
            list.insert(list.end(), bins[i].begin(), bins[i].end());
    }
}

// String
void binsortS(vector<string> &list, bool dir) {
    int power = 1, endIndex = dir ? 127 : 0;
    char index;
    vector<string> bins[128];
    while(bins[endIndex].size() != list.size()) {
        for(int i = 0; i < 128; ++i)
            bins[i].clear();
        for(size_t i = 0; i < list.size(); ++i) {
            index = (int)(list[i].length()-power) < 0 ? 0 : list[i].at(list[i].length()-power);
            bins[dir ? (127 - index) : index].push_back(list[i]);
        }
        power += 1;
        list.clear();
        for(int i = 0; i < 128; ++i)
            list.insert(list.end(), bins[i].begin(), bins[i].end());
    }
}

// Testers
void setType(char &type) {
    while(1) {
        cout << "Enter 'i' for int, 'd' for double, and 's' for string: ";
        cin >> type;
        type = tolower(type);
        if(type=='i' || type=='d' || type=='s')
            break;
    }
}

void run(char type) {
    vector<int> vi;
    vector<double> vd;
    vector<string> vs;
    DIRECTION dir;
    switch(type) {
        case 'i':
            addData<int>(vi, dir);
            display(vi, "Original Data:");
            binsortI(vi, dir);
            display(vi, "Sorted Data:");
            break;
        case 'd':
            addData<double>(vd, dir);
            display(vd, "Original Data:");
            binsortD(vd, dir);
            display(vd, "Sorted Data:");
            break;
        default:
            addData<string>(vs, dir);
            display(vs, "Original Data:");
            binsortS(vs, dir);
            display(vs, "Sorted Data:");
    }
}

bool again() {
    char ans;
    cout << "Again?[Y/N] ";
    cin >> ans;
    ans = tolower(ans);
    return ans == 'y';
}

template <typename T>
void addData(vector<T> &v, DIRECTION &dir) {
    int len;
    char order = '\0';
    T data;
    cout << "Enter the number of elements to add: ";
    cin >> len;
    for(int i=0; i<len; ++i) {
        cin >> data;
        v.push_back(data);
    }
    while(order!='a' && order!='d') {
        cout << "Assending or Descending?[A/D] ";
        cin >> order;
        order = tolower(order);
    }
    dir = order=='a' ? MIN_SORT : MAX_SORT;
}

template <typename T>
void display(vector<T> &v, const string &name) {
    cout << "----------------------------\n" << name << endl;
    for(size_t i=0; i<v.size(); ++i)
        cout << v[i] << endl;
}
