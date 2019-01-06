#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <fstream>

using namespace std;

class LogFile {
    mutex mu;
    ofstream out;
public:
    LogFile(const string &path) {
        out.open(path);
    }

    void print(string id, int value) {
        lock_guard<mutex> locker(mu);
        out << "From " << id << ": " << value << endl;
    }

    // NEVER return out to the outside world!
    ofstream& getStream() { return out; }
    // NEVER pass out as an argument to user provided function
    void process(void fun(ofstream&)) { fun(out); }
};

int test(int n) {
    cout << "\ngonichiwa! : " << n << endl;
    return n*10;
}

void threadDemo() {
    thread t(test, 10);   // t starts running
    t.join();       // main thread waits for t to finish
//    t.detach();       // t will freely on its own -- daemon process
}

void whatIHaveLearned() {
    // thread
    thread t1(test, 3);

    // mutex
    mutex mu;
    lock_guard<mutex> locker(mu);
    unique_lock<mutex> uLocker(mu);

    // condition variable
    condition_variable cond;

    // future and promise
    promise<int> p;
    future<int> f = p.get_future();

    // async()
//    future<int> fu = async(test, 3); // might generate another thread, might go with the same thread

    // package task - class template that can be parameterized with a function signiture
    //                of the task we create
    packaged_task<int(int)> t(test);
//  In this case, t(3) == test(3);
    future<int> fu2 = t.get_future();
    t(3);
}

long double factorial(long double n) {
    return n > 1 ? n * factorial(n-1) : n;
}

#include <cmath>
int main() {
//    cout << "Max # of thread possible: " << thread::hardware_concurrency() << endl;
//    threadDemo();
//    for(int i=0; i<30; ++i)
//        cout << "Hello world!" << endl;
//    return 0;
//    cout << factorial(70) << endl;
//    cout << (unsigned long int)factorial(31) * (unsigned long int)32 * (unsigned long int)33 * (unsigned long int)34* (unsigned long int)35 << endl;
    cout << 400000 * ((3.25/12) * pow((1+(3.25/12)),180)) / pow((1+(3.25/12)),180) - 1 << endl;
}
