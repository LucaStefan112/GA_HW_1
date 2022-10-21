#include "Functions.h"

// Select function:
void Functions::selectFunction(FunctionTypes thisFunctionType, int thisDimension){
  Functions::dimension = thisDimension;
  Functions::functionType = thisFunctionType;

  switch(thisFunctionType){
    case Dejong:
      Functions::a = -5.12;  Functions::b = 5.12;
    break;
    case Schwefel:
      Functions::a = -500; Functions::b = 500;
    break;
    case Rastrigin:
      Functions::a = -5.12;  Functions::b = 5.12;
    break;
    case Michalewicz:
      Functions::a = 0;  Functions::b = M_PI;
    break;
  }
  
  Functions::bitSpace = ceil(log2((Functions::b - Functions::a) * Functions::decimalPrecision));
}

// Generate random input:
std::vector<int> Functions::generateRandom(){
  std::vector<int> x;

  for(int i = 0; i < bitSpace * dimension; i++)
    x.push_back(rand() % 2);
  
  return x;
}

// Generate best neighbour:
std::vector<int> Functions::generateBestNeighbour(std::vector<int> candidate){
  std::vector<int> neighbour(candidate), bestNeighbour(candidate);
  float bestScore = getResult(candidate);

  for(int i = 0; i < dimension * bitSpace; i++){
    neighbour[i] = 1 - neighbour[i];

    float neighbourScore = getResult(neighbour);

    if(neighbourScore < bestScore){
      bestScore = neighbourScore;
      bestNeighbour = neighbour;
    }

    neighbour[i] = 1 - neighbour[i];
  }

  return bestNeighbour;
}

// Generate first better neighbour:
std::vector<int> Functions::generateFirstBetterNeighbour(std::vector<int> candidate){
  std::vector<int> neighbour(candidate);
  float candidateScore = getResult(candidate);

  for(int i = 0; i < dimension * bitSpace; i++){
    neighbour[i] = 1 - neighbour[i];

    float neighbourScore = getResult(neighbour);

    if(neighbourScore < candidateScore)
      return neighbour;

    neighbour[i] = 1 - neighbour[i];
  }

  return neighbour;
}

// Generate worst better neighbour:
std::vector<int> Functions::generateWorstBetterNeighbour(std::vector<int> candidate){
  std::vector<int> neighbour(candidate), worstBetterNeighbour(candidate);
  float candidateScore = getResult(candidate), worstBetterScore = getResult(candidate);
  bool foundBetter = false;

  for(int i = 0; i < dimension * bitSpace; i++){
    neighbour[i] = 1 - neighbour[i];

    float neighbourScore = getResult(neighbour);

    if(neighbourScore < candidateScore && (neighbourScore > worstBetterScore || !foundBetter)){
      foundBetter = true;
      worstBetterScore = neighbourScore;
      worstBetterNeighbour = neighbour;
    }

    neighbour[i] = 1 - neighbour[i];
  }

  return worstBetterNeighbour;
}

// Generate random neighbour:
std::vector<int> Functions::generateRandomNeighbour(std::vector<int> candidate){
  std::vector<int> neighbour(candidate);
  int randomBit = rand() % (dimension * bitSpace);
  neighbour[randomBit] = 1 - neighbour[randomBit];

  return neighbour;
}

// Get function result:
float Functions::getResult(std::vector<int> x){
  std::vector<float> values;

  for(int i = 0; i < dimension; i++){
    int decimalValue = 0;

    for(int j = 0; j < bitSpace; j++){
      decimalValue <<= 1;
      decimalValue |= x[i * bitSpace + j];
    }

    values.push_back(a + decimalValue * (b - a) / (pow(2, bitSpace) - 1));
  }

  switch(functionType){
    case Dejong:
      return dejong1(values);
    case Schwefel:
      return schwefel7(values);
    case Rastrigin:
      return rastrigin6(values);
    case Michalewicz:
      return michalewicz12(values);
  }

  return 0;
}

/*########################################################################################*/

// De Jong's Function 1:
float Functions::dejong1(std::vector<float> x){
  float sum = 0;
  
  for(std::vector<float>::const_iterator i = x.cbegin(); i != x.cend(); i++)
    sum += ((*i) * (*i));

  return sum;
}

// Schwefel's Function 7:
float Functions::schwefel7(std::vector<float> x){
  float sum = 0;

  for(std::vector<float>::const_iterator i = x.cbegin(); i != x.cend(); i++)
    sum += (-(*i) * sin(sqrt(abs(*i))));

  return sum;
}

// Rastrigin's Function 6:
float Functions::rastrigin6(std::vector<float> x){
  float sum = 10 * x.size();

  for(std::vector<float>::const_iterator i = x.cbegin(); i != x.cend(); i++)
    sum += (pow(*i, 2) - 10 * cos(2 * M_PI * (*i)));

  return sum;
}

// Michalewicz's Function 12:
float Functions::michalewicz12(std::vector<float> x){
  float sum = 0;
  const float m = 10;
  int iterator = 1;

  for(std::vector<float>::const_iterator i = x.cbegin(); i != x.cend(); i++)
    sum -= (sin(*i) * pow(sin((iterator++ * pow(*i, 2)) / M_PI), 2 * m));

  return sum;
}