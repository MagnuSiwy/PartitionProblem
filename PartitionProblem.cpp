#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <ctime>
#include <tuple>


// This generator only creates sets that are solvable according to heuristics
// This means their sum is divisible by K
std::tuple<std::vector<int>, int> generateSet(int K, int N, int randRange)
{
    std::vector<int> setTemp = {};
    srand((unsigned)time(NULL));

    for(int i = 0; i < N - 1; ++i)
    {
        setTemp.push_back(rand() % randRange + 1);
    }

    int setSum = std::accumulate(setTemp.begin(), setTemp.end(), 0);

    int rest = setSum % K;

    setTemp.push_back(K-rest);

    return std::make_tuple(setTemp, setSum + K - rest);
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


bool greedyAlgorithm(std::vector<int>& set, std::vector<int>& subset, std::vector<int> subsetElements[], int k, int target)
{
    if (set.empty())
    {
        return subset[0] == subset[k - 1];
    }

    for (int i = 0; i < k; i++)
    {
        if(subset[i] + set.back() <= target)
        {
            subset[i] += set.back();
            subsetElements[i].push_back(set.back());

            set.pop_back();

            if (greedyAlgorithm(set, subset, subsetElements, k, target))
                return true;
        }
    }

    return false;
}


int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        std::cout << "Error! Not enough arguments";
        exit(1);
    }

    // K - number of subsets into which the program devides the main set
    // N - number of elements in the set
    // randRange - range of randomly generated numbers
    const int K = atoi(argv[1]);
    const int N = atoi(argv[2]);
    const int randRange = atoi(argv[3]);

    std::vector<int> set;
    int setSum;

    tie(set, setSum) = generateSet(K, N, randRange);

    std::cout << "Generated set: " << std::endl;
    for(int i = 0; i < set.size(); ++i)
    {
        std::cout << set[i] << " ";
    }
    std::cout << std::endl << std::endl;

    // Greedy algorithm needs set to be sorted - it always chooses the largest possible value
    std::sort(set.begin(), set.end());
    
    
    if(heuristics(setSum, K))
    {
        bool greedyAlgorithmAns;
        int target = setSum / K;
        std::vector<int> subset(K, 0);
        std::vector<int> subsetElements[K];

        greedyAlgorithmAns = greedyAlgorithm(set, subset, subsetElements, K, target);

        std::cout << "Heuristics: true" << std::endl;
        std::cout << std::boolalpha << "Greedy algorithm: " << greedyAlgorithmAns << std::endl;

        // Metaheuristics aproach uses the Greedy Algorithm's calculations to work out optimal solution (the best possible). 
        std::cout << "Metaheuristics: " << std::endl;
        for(int i = 0; i < K; ++i)
        { 
            int subsetSum = std::accumulate(subsetElements[i].begin(), subsetElements[i].end(), 0);

            std::cout << subsetSum << " => ";
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