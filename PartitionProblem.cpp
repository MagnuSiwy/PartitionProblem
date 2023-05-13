#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <ctime>

// #define K 3
// #define N 100
// #define randRange 50

// std::vector<int> subsetElements[K];

void generator(std::vector<int>& set, int K, int N, int randRange)
{
    srand((unsigned)time(NULL));

    for(int i = 0; i < N - 1; ++i)
    {
        set.push_back(rand() % randRange + 1);
    }

    int setSum = std::accumulate(set.begin(), set.end(), 0);

    int rest = setSum % K;

    set.push_back(K-rest);
}

bool heuristics(int setSum, int k)
{
    if(k == 1)
    {
        return true;
    }
    
    if(setSum % k == 0)
    {
        return true;
    }

    return false;
}


bool partition(std::vector<int>& set, std::vector<int>& subset, std::vector<int> subsetElements[], int k, int target)
{
    if (set.empty())
        return subset[0] == subset[k - 1];

    for (int i = 0; i < k; i++)
    {
        if(subset[i] + set.back() <= target)
        {
            subset[i] += set.back();
            subsetElements[i].push_back(set.back());


            set.pop_back();

            if (partition(set, subset, subsetElements, k, target))
                return true;
        }
    }

    return false;
}


int main(int argc, char* argv[])
{
    std::vector<int> set = {};

    if(argc < 4)
    {
        exit(1);
    }

    const int K = atoi(argv[1]);
    const int n = atoi(argv[2]);
    const int randRange = atoi(argv[3]);

    generator(set, K, n, randRange);

    // for(int i = 0; i < set.size(); ++i)
    // {
    //     std::cout << set[i] << " ";
    // }

    std::cout << std::endl;

    std::sort(set.begin(), set.end());

    std::vector<int> subset(K, 0);
    std::vector<int> subsetElements[K];

    int setSum = std::accumulate(set.begin(), set.end(), 0);
    int target = setSum / K;

    if(heuristics(setSum, K))
    {
        std::cout << "Heuristics: true" << std::endl;
        std::cout << std::boolalpha << "Greedy algorithm: " << partition(set, subset, subsetElements, K, target) << std::endl;
        std::cout << "Metaheuristics: " << std::endl;
        for(int i = 0; i < K; ++i)
        { 
            std::cout << std::accumulate(subsetElements[i].begin(), subsetElements[i].end(), 0) << " = ";
            for(int j : subsetElements[i])
                std::cout << j << " ";
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "Partition into " << K << " subsets of equal sum is not possible." << std::endl;
    }

    return 0;
}