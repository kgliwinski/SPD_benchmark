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
    int dueTime;
    int releaseTime;
    Job(int id, int processingTime, int releaseTime, int dueTime) : id(id), processingTime(processingTime), releaseTime(releaseTime), dueTime(dueTime) {}
};

bool compareJobs(const Job &a, const Job &b)
{
    if(a.releaseTime == b.releaseTime){
        return a.processingTime > b.processingTime;
    }
    return a.releaseTime < b.releaseTime;
}
double jacksonAlgorithm(std::vector<Job> &jobs)
{
    TimeVar t1 = timeNow();
    std::sort(jobs.begin(), jobs.end(), compareJobs);
    return duration(timeNow() - t1);
    // int currentTime = 0;
    // int tardiness = 0;
    // for (auto job : jobs)
    // {
    //     currentTime += job.processingTime;
    //     tardiness += std::max(0, currentTime - job.dueTime);
    //     std::cout << "Job " << job.id << " starts at " << currentTime - job.processingTime << " and finishes at " << currentTime << std::endl;
    // }
    // std::cout
    //     << "Total tardiness: " << tardiness << std::endl;
    // return tardiness;
}

std::vector<Job> generateJobsVector(int num)
{
    std::vector<Job> jobs;

    for (int i = 1; i <= num; ++i)
    {
        srand((unsigned)time(NULL));
        int random1 = rand() % 100;
        srand((unsigned)time(NULL));
        int random2 = rand() % 100;
        srand((unsigned)time(NULL));
        int random3 = rand() % 100;
        jobs.push_back(Job(i, random1, random2, random3));
    }
    return jobs;
}

int main()
{
    std::ofstream file("result.csv");
    double res;
    std::vector<Job> jobs;
    std::cout.precision(17);
    // for(int i = i; i < 100; ++i)
    for (int i = 1; i <= 1000000; i+=1000)
    {
        jobs = generateJobsVector(i);
        file << jobs.size() << ";";
        // std::cout << jobs.size() << ";";
        res = jacksonAlgorithm(jobs);
        file << std::setprecision(17) << res << ";\n";
        // std::cout << std::setprecision(17) << res << ";\n";
    }

    return 0;
}