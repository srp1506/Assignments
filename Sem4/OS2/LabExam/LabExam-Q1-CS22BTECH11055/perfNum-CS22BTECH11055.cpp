#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <cmath>
#include <pthread.h>
#include <atomic>
#include <semaphore.h>
#include <chrono>
#include <cmath>

using namespace std;

int n;
int k;
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
    for (int i = index; i <= n; i += k)
    {
        if (perfect(i))
        {
            sem_wait(&print);
            outfile << i <<" : Found by thread " << index << "\n";
            sem_post(&print);
            total.fetch_add(1);
        }
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

    auto start = chrono::high_resolution_clock::now();

    for (int i = 1; i <= k; i++)
    {
        threads.emplace_back(routine, i);
    }

    for (auto &thread : threads)
        thread.join();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    outfile << "Total number of perfect numbers in range 1 to " << n << " is " << total << endl;
    outfile << "Time taken is " << duration.count() / 1000000.0 << " seconds";
    outfile.close();
    return 0;
}