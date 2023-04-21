
#include "RandomNumberGenerator.h"
#include "scheduling.hpp"
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <fstream>
typedef std::vector<Job *> (*fun)(std::vector<Job *>);

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

/**
 * Generuje dane.
 *
 * @param n Ilość zadań.
 * @param seed Ziarno losowania.
 * @return Zwraca nieuporządkowane zadania.
 */
std::vector<Job *> generateOperations(const int &n, const int &seed)
{
    RandomNumberGenerator randf(seed);
    std::vector<Job *> J;
    int A = 0;

    for (int j = 1; j <= n; ++j)
    {
        Job *tmp = new Job(j);
        J.push_back(tmp);
    }

    for (int j = 0; j < n; ++j)
    {
        J[j]->processingTime = randf.nextInt(1, 29);
        A += J[j]->processingTime;
    }

    for (int j = 0; j < n; ++j)
    {
        J[j]->weight = randf.nextInt(1, 9);
    }

    for (int j = 0; j < n; ++j)
    {
        J[j]->deadline = randf.nextInt(1, 29);
    }

    return J;
}

/**
 * Wypisywanie raportu.
 *
 * @param name Nazwa zadania.
 * @param pi Wektor z uporządkowanymi zadaniami.
 */
std::chrono::duration<double> log(const char *name, std::vector<Job *> pi, fun ptr = nullptr)
{

    auto start = std::chrono::system_clock::now();
    if (ptr != nullptr)
        pi = ptr(pi);
    auto end = std::chrono::system_clock::now();

    // int size = pi.size();
    // int *C = new int[size];
    // int *T = new int[size];

    // printf("%s\npi: [", name);
    // for (int i = 0; i < size; ++i)
    // {
    //     printf("%3d", pi[i]->number);

    //     if (i != size - 1)
    //         printf(", ");
    // }
    // printf("]\n");

    // printf("C:  [");
    // for (int i = 0; i < size; ++i)
    // {
    //     if (i)
    //         C[i] = C[i - 1] + pi[i]->processingTime;
    //     else
    //         C[i] = pi[i]->processingTime;

    //     printf("%3d", C[i]);
    //     if (i != size - 1)
    //         printf(", ");
    // }
    // printf("]\n");

    // printf("T:  [");
    // for (int i = 0; i < size; ++i)
    // {
    //     T[i] = std::max(C[i] - pi[i]->deadline, 0);
    //     printf("%3d", T[i]);
    //     if (i != size - 1)
    //         printf(", ");
    // }
    // printf("]\n");

    // printf("wT: [");
    // int wiTi = 0;
    // for (int i = 0; i < size; ++i)
    // {
    //     int wT = T[i] * pi[i]->weight;
    //     wiTi += wT;
    //     printf("%3d", wT);
    //     if (i != size - 1)
    //         printf(", ");
    // }
    // printf("]\n");

    std::chrono::duration<double> diff = end - start;
    // printf("wiTi: %d\n", wiTi);
    // printf("Time: %fs\n\n", diff);

    // delete[] C;
    // delete[] T;
    return diff;
}

void measure_multiple(std::string filename, fun ptr)
{   
    int seed = 1;
    std::fstream file;
    file.open(filename, std::ios::out);

    for (int i = 5; i < 11; i++)
    {
        std::vector<Job *> J = generateOperations(i, seed);
        std::string s = std::to_string(i) + ";" + std::to_string(duration(log("Greedy", J, ptr))) + ";\n";
        file << s;
        // log("Natualna", J);
        // log("Greedy", J, Greedy);
        // log("BruteForce", J, BruteForce);
        // log("Dynamic", J, Dynamic);
        std::cout << s << std::endl;
    }

    file.close();
}

int main()
{
    // measure_multiple("Greedy.csv", Greedy);
    measure_multiple("BruteForce.csv", BruteForce);
    // measure_multiple("Dynamic.csv", Dynamic);
    return 0;
}