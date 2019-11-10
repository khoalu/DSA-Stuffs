#include <iostream>

#include <functional>

#include <ctime>
#include <cstdlib>

#include <stack>
#include "Stack.h"

#include <queue>
#include "Queue.h"

#include "LList.h"
#include <vector>

using namespace std;

class Timer
{
private:
    clock_t startClock;
    double elapsedTime;
public:
    Timer(): startClock(0), elapsedTime(0) {}

    void start() {startClock = clock();}
    void stop() {elapsedTime = 1.0*(clock()-startClock)/CLOCKS_PER_SEC * 1000;}
    void reset() {elapsedTime = 0;}
    friend std::ostream& operator << (std::ostream &os, const Timer& timer)
    {
        os << timer.elapsedTime << " ms";
        return os;
    }
};


class TestClass {
private:
    static int N;
public:

    static int getN() {return N;}
    static int setN(int _N) {N = _N;}

    void test1()
    {
        // best cases of the two
        Timer timer;

        LList<int> a;
        timer.start();
        for(int i = 0; i < N; i++) a.insertHead(i);
        timer.stop();

        cout << "Singly linked list insert head: " << timer << "\n";


        vector<int> v;

        timer.reset();
        timer.start();
        for(int i = 0; i < N; i++) v.push_back(i);
        timer.stop();
        cout << "std::vector push_back: " << timer << "\n";
    }

    void test2()
    {
        // worst case of the two
        Timer timer;

        timer.start();
        LList<int> a;
        for(int i = 0; i < N; i++) a.insertTail(i);
        timer.stop();

        cout << "Singly linked list insert tail: " << timer << "\n";

        timer.reset();
        vector<int> v;
        for(int i = 0; i < N; i++) v.insert(v.begin(),i);
        timer.stop();

        cout << "std::vector insert(v.begin(),i): " << timer << "\n";

    }

    void test3()
    {
        Timer timer;

        timer.start();
        Stack<int> st1;
        for(int i = 0; i < N; i++) st1.push(i);
        timer.stop();
        cout << "my stack with push: " << timer << "\n";
        timer.reset();
        timer.start();
        while (!st1.isEmpty()) st1.pop();
        timer.stop();
        cout << "my stack with pop: " << timer << "\n";

        timer.reset();
        timer.start();
        stack<int> st2;
        for(int i = 0; i < N; i++) st2.push(i);
        timer.stop();
        cout << "std::stack with push: " << timer << "\n";
        timer.reset();
        timer.start();
        while (!st2.empty()) st2.pop();
        timer.stop();
        cout << "std::stack with pop: " << timer << "\n";
    }
};
int TestClass::N = 5e6;

int main()
{
    TestClass tc;

    tc.setN(5e7);
    cout << "with N = " <<  tc.getN() << "\n\n";
    tc.test3();
    //tc.test1();
//    cout <<"\n";
    //tc.test2();

    return 0;
}
