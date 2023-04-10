#include <stdio.h>
#include <stdint.h>
#include "RandomNumberGenerator.h"
#include <iostream>
#include <fstream>

#include "scheduling.hpp"

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

void log(const char *name, std::vector<job> &jobs, const std::vector<Pi> &pi)
{
    printf("%s\npi: [", name);

    for (uint32_t i = 0; i < pi.size(); ++i)
    {
        printf("%3d", pi[i].number + 1);
        if (i != pi.size() - 1)
            printf(", ");
    }

    printf("]\nS:  [");

    for (uint32_t i = 0; i < pi.size(); ++i)
    {
        printf("%3d", pi[i].s);
        if (i != pi.size() - 1)
            printf(", ");
    }

    printf("]\nC:  [");

    for (uint32_t i = 0; i < pi.size(); ++i)
    {
        printf("%3d", pi[i].c);
        if (i != pi.size() - 1)
            printf(", ");
    }

    printf("]\nCq: [");

    for (uint32_t i = 0; i < pi.size(); ++i)
    {
        printf("%3d", pi[i].c + jobs[pi[i].number].q);
        if (i != pi.size() - 1)
            printf(", ");
    }

    printf("]\nCmax: %d\n\n", cmax(jobs, pi));
}

std::vector<job> generateJobs(int size, int seed)
{
    RandomNumberGenerator randf(seed);
    int A = 0;
    int X = 29;            // bo tak
    std::vector<job> jobs; // zadania

    // //generowanie instancji
    for (uint32_t i = 0; i < size; ++i)
    {
        jobs.emplace_back(i);
    }

    for (uint32_t i = 0; i < size; ++i)
    {
        jobs[i].p = randf.nextInt(1, 29); // losowanie czasu wykonywania
        A += jobs[i].p;
    }

    for (uint32_t i = 0; i < size; ++i)
    {
        jobs[i].r = randf.nextInt(1, A); // losowanie czasu przygotowywania
    }

    for (uint32_t i = 0; i < size; ++i)
    {
        jobs[i].q = randf.nextInt(1, A); // losowanie czasu stygniecia
    }

    return jobs;
}

void printJobsInfo(std::vector<job> jobs, int size, int seed)
{
    printf("Źródło losowania: %d \nRozmiar problemu: %d\n\n", seed, size);

    printf("nr: [");

    for (uint32_t i = 0; i < jobs.size(); ++i)
    {
        printf("%3d", jobs[i].number + 1);
        if (i != jobs.size() - 1)
            printf(", ");
    }

    printf("]\nr:  [");

    for (uint32_t i = 0; i < jobs.size(); ++i)
    {
        printf("%3d", jobs[i].r);
        if (i != jobs.size() - 1)
            printf(", ");
    }

    printf("]\np:  [");

    for (uint32_t i = 0; i < jobs.size(); ++i)
    {
        printf("%3d", jobs[i].p);
        if (i != jobs.size() - 1)
            printf(", ");
    }

    printf("]\nq:  [");

    for (uint32_t i = 0; i < jobs.size(); ++i)
    {
        printf("%3d", jobs[i].q);
        if (i != jobs.size() - 1)
            printf(", ");
    }
    printf("\n\n");
}

int main()
{
    int size = 10000;
    int seed = 7523;
    std::vector<Pi> pi;

    std::fstream file;
    file.open("result.csv", std::ios::out);


    for(int i = 0; i < 100000; i++)
    {
        std::vector<job> jobs = generateJobs(i, seed);
        TimeVar start = timeNow();
        pi = Carlier(jobs);
        TimeVar end = timeNow();
        printf("Ilosc: %d, Czas: %lld\n", i, duration(end - start));
        file << i << ";" << duration(end - start) << ";" << std::endl;
    }
    // std::vector<job> jobs = generateJobs(size, seed);
    // printJobsInfo(jobs, size, seed);

    // log("Carlier", jobs, Carlier(jobs));
    file.close();
    return 0;
}
