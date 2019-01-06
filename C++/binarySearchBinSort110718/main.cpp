#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

void binsort(vector<int> &list);
void loadRandom(vector<int> &list);
bool getInput(string &line);
void process(string line, const vector<int> &list);
bool validate(string line, int &number);
bool binarySearch(const vector<int> &list,int number, int &pos);
void display(const vector<int> &list);

int main()
{
    vector<int> list;
    string line;
    srand(time(0));
    loadRandom(list);
    binsort(list);
    display(list);
    while(getInput(line))
        process(line, list);
    return 0;
}

bool binarySearch(const vector<int> &list,int number, int &pos)
{
   int low = -1, high = list.size(), mid = (high + low)/2;
   while(!((low == mid) || (high == mid)))
   {
         cout<<"low = "<<low<<" mid = "<<mid<<" high = "<<high<<endl;
         if(list[mid] == number)
         {
             pos = mid;
             return true;
         }
         if(number < list[mid])
             high = mid;
         else
             low = mid;
         mid = (high + low)/2;
   }
   return false;
}

bool validate(string line, int &number)
{
    if(line.find_first_not_of("0123456789-") < line.size())
        return false;
    number = stoi(line);
    return true;
}

void process(string line, const vector<int> &list)
{
    int number, pos;
    if(validate(line, number))
        if(binarySearch(list,number, pos))
            cout<<number<<" was found at position "<<pos<<" in the vector"<<endl;
        else
            cout<<number<<" was not found in the vector"<<endl;
    else
        cout<<"Illegal input -- please try again"<<endl;
}

bool getInput(string &line)
{
    cout<<"Number for which to search? ";
    getline(cin,line);
    return !line.empty();
}

void binsort(vector<int> &list)
{
    vector<int> bins[10];
    cout<<"Starting binsort"<<endl;
    int power = 1;
    while(bins[0].size() != list.size())
    {
       // cout<<"Power = "<<power<<endl;
        for(int i = 0; i < 10; ++i)
            bins[i].clear();
        for(int i = 0; i < list.size(); ++i)
        {
            bins[(list[i]/power) % 10].push_back(list[i]);
           // cout<<"Bin["<<(list[i]/power) % 10<<"] gets "<<list[i]<<" becuase digits = "<<(list[i]/power)%10<<endl;
        }
        power *= 10;
        list.clear();
        for(int i = 0; i < 10; ++i)
            list.insert(list.end(), bins[i].begin(), bins[i].end());
    }
    cout<<"Ending bin sort"<<endl;
}

void display(const vector<int> &list)
{
    cout<<"Your numbers:"<<endl;
    for(int i = 0; i < list.size(); ++i)
    {
        if(i%10 == 0)
            cout<<endl;
        cout<<setw(5)<<list[i];
    }
    cout<<endl<<endl;
}

void loadRandom(vector<int> &list)
{
    for(int i= 0; i < 10; ++i)
            list.push_back(rand()%100);
}
