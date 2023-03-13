#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <utility>
#include <cstdlib>
#include <fstream>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

struct Job
{
    int id;
    int processingTime;
    int prepareTime;
    int deliveryTime;
    Job(int id, int prepareTime, int deliveryTime, int processingTime) : id(id), processingTime(processingTime), deliveryTime(deliveryTime), prepareTime(prepareTime) {}
};

bool compareJobs(const Job &a, const Job &b)
{
    return a.prepareTime < b.prepareTime;
}

double sortR(std::vector<Job> &jobs)
{
    TimeVar t1 = timeNow();
    std::sort(jobs.begin(), jobs.end(), compareJobs);
    double ret = duration(timeNow() - t1);
    // std::cout << "Nr | rj | pj | qj " << std::endl;
    // for (auto job : jobs)
    // {
    //     std::cout << std::setw(2) << job.id << " | " << std::setw(2) << job.prepareTime << " | " << std::setw(2) << job.processingTime << " | " << std::setw(2) << job.deliveryTime << std::endl;
    // }
    return ret;
}

std::vector<Job> generateJobsVector(int num)
{
    std::vector<Job> jobs;

    srand((unsigned)time(NULL));
    for (int i = 1; i <= num; ++i)
    {
        int random1 = rand() % 100;
        int random2 = rand() % 100;
        int random3 = rand() % 100;
        jobs.push_back(Job(i, random1, random2, random3));
    }
    return jobs;
}

int main()
{
    std::ofstream file("result.csv");
    double res;
    std::vector<Job> jobs{Job(1, 3, 2, 10), Job(2, 1, 6, 15), Job(3, 7, 2, 20), Job(4, 5, 6, 17)};
    std::cout.precision(17);

    res = sortR(jobs);
    std::cout << res << std::endl;
    // for(int i = i; i < 100; ++i)
    for (int i = 1; i <= 1000000; i += 1000)
    {
        jobs = generateJobsVector(i);
        file << jobs.size() << ";";
        // std::cout << jobs.size() << ";";
        res = sortR(jobs);
        file << std::setprecision(17) << res << ";\n";
        // std::cout << std::setprecision(17) << res << ";\n";
    }
    return 0;
}