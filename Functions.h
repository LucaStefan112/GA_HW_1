#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <cstdlib>
#include <time.h>
#include <vector>

class Functions{
  public:
    enum FunctionTypes { Dejong, Schwefel, Rastrigin, Michalewicz };

    // Select function:
    void selectFunction(FunctionTypes functionType, int dimension);

    // Generate Random Function Input:
    std::vector<int> generateRandom();

    // Generate best neighbour:
    std::vector<int> generateBestNeighbour(std::vector<int> candidate);
    
    // Generate first better neighbour:
    std::vector<int> generateFirstBetterNeighbour(std::vector<int> candidate);

    // Generate worst better neighbour:
    std::vector<int> generateWorstBetterNeighbour(std::vector<int> candidate);

    // Generate random neighbour:
    std::vector<int> generateRandomNeighbour(std::vector<int> candidate);

    // Function result:
    float getResult(std::vector<int> x);

  // private:
    int bitSpace, dimension;
    float a, b;
    FunctionTypes functionType;
    
    static const int decimalPrecision = 100000;

    // Functions:
    static float dejong1(std::vector<float> x);
    static float schwefel7(std::vector<float> x);
    static float rastrigin6(std::vector<float> x);
    static float michalewicz12(std::vector<float> x);
};

#endif //FUNCTIONS_H