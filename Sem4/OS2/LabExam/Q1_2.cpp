#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <cmath>
#include <pthread.h>
#include <atomic>
#include <semaphore.h>

using namespace std;

int n;
int k;
atomic<int> current(1); 
atomic<int> total(0); 
ofstream outfile("outFile.txt");
sem_t print;

bool perfect(int n)
{
    int sum = 0;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0)
            sum += i;
    }

    if (sum == n)
        return true;
    else 
        return false;
}

void routine(int index)
{
    int work;

    while(true)
    {   
        work = current.fetch_add(1);
        if (perfect(work))
        {
            sem_wait(&print);
            outfile << work <<" : Found by thread " << index << "\n";
            sem_post(&print);
            total.fetch_add(1);
        }

        if (current > n)
            break;
    }
}

int main()
{
    if (k > n)
        k = n;
    sem_init(&print, 0, 1);

    ifstream infile("inp.txt");

    infile >> n >> k;
    infile.close();
    vector<thread> threads;

    for (int i = 1; i <= k; i++)
    {
        threads.emplace_back(routine, i);
    }

    for (auto &thread : threads)
        thread.join();

    outfile << "Total number of perfect numbers in range 1 to " << n << " is " << total << "\n";
    outfile.close();
    return 0;
}