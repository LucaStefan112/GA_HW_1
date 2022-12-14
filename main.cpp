#include <bits/stdc++.h>
#include "Functions.h"


#define T_MAX 10000
#define TEMPERATURE 5000

int dimension, algorithmType, functionType;
Functions thisFunction;

std::string getOsName()
{
    #ifdef _WIN32
    return "Windows";
    #elif _WIN64
    return "Windows";
    #elif __APPLE__ || __MACH__
    return "Mac";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
} 

void clearConsole(){
  if(getOsName() == "Windows")
    system("cls");
  else
    system("clear");
}

void readData(){
  clearConsole();
  
  std::cout << "Introduceti dimensiunea: ";
  std::cin >> dimension;
  clearConsole();

  std::cout << "0 -> De Jong's Function 1;\n1 -> Schwefel's Function 7;\n2 -> Rastrigin's Function 6;\n3 -> Michalewicz's Function 12;\n\n";
  std::cout << "Introduceti functia: ";
  std::cin >> functionType;
  clearConsole();

  std::cout << "0 -> Hill Climbing (first improvement);\n1 -> Hill Climbing (best improvement);\n2 -> Hill Climbing (worst improvement);\n3 -> Simulated Annealing;\n\n";
  std::cout << "Introduceti algoritmul: ";
  std:: cin >> algorithmType;
  clearConsole();

  thisFunction.selectFunction(static_cast<Functions::FunctionTypes>(functionType), dimension);
}

std::vector<int> selectNeighbour(std::vector<int> candidate){
  
  switch (algorithmType){
  case 0:
    return thisFunction.generateFirstBetterNeighbour(candidate);
  break;
  case 1:
    return thisFunction.generateBestNeighbour(candidate);
  break;
  case 2:
    return thisFunction.generateWorstBetterNeighbour(candidate);
  break;
  case 3:
    return thisFunction.generateRandomNeighbour(candidate);
  break;
  }

  return candidate;
}

void showStats(std::vector<int> best){
  //clearConsole();
  std::cout << "Best overall score: f(x) = " << thisFunction.getResult(best) << '\n';
}

void hillCLimbing(){
  std::vector<int> best(thisFunction.generateRandom());

  for(int t = 0; t < T_MAX; t++){
    bool local = false;
    std::vector<int> candidate(thisFunction.generateRandom()), improvement;
    
    do{      
      local = true;
      improvement = selectNeighbour(candidate);

      if(thisFunction.getResult(improvement) < thisFunction.getResult(candidate)){
        local = false;
        candidate = improvement;
      }
    }while(!local);

    if(thisFunction.getResult(candidate) < thisFunction.getResult(best))
      best = candidate;
  }

  showStats(best);
}

void simulatedAnnealing(){
  std::vector<int> best(thisFunction.generateRandom()), neighbour;
  float t = TEMPERATURE;
  int iteration;

  while(t > 0){
    for(iteration = 0; iteration < T_MAX / 20; iteration++){
      neighbour = thisFunction.generateBestNeighbour(best);

      float neighbourScore = thisFunction.getResult(neighbour),
            bestScore = thisFunction.getResult(best);

      if(neighbourScore < bestScore)
        best = neighbour;

      else if (float(rand() % Functions::decimalPrecision) / Functions::decimalPrecision < exp(-abs(bestScore - neighbourScore) * 2000 / t))
        best = neighbour;
    }
    t -= 5;
  }
  showStats(best);
}

void computeAlgorithm(){
  if(algorithmType == 3)
    simulatedAnnealing();
  else
    hillCLimbing();
}

void algorithmData(clock_t start, clock_t end){
  double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
  std::cout << "Time: " << time_taken << " seconds\n";
  std::cout << "Function Type: ";
  switch (functionType){
    case 0:
      std::cout << "De Jong's Function 1";
    break;
    case 1:
      std::cout << "Schwefel's Function 7";
    break;
    case 2:
      std::cout << "Rastrigin's Function 6";
    break;
    case 3:
      std::cout << "Michalewicz's Function 12";
    break;
  }
  std::cout << '\n';
  std::cout << "Dimension: " << dimension << '\n';
  std::cout << "Algorythm type: ";
  switch (algorithmType){
    case 0:
      std::cout << "HC-FI";
    break;
    case 1:
      std::cout << "HC-BI";
    break;
    case 2:
      std::cout << "HC-WI";
    break;
    case 3:
      std::cout << "SA-BI";
    break;
  }
  std::cout << '\n';
}

int main(){
  clock_t start, end;
  start = clock();

  srand(time(0));
  
  readData();

  computeAlgorithm();

  end = clock();

  algorithmData(start, end);

  system("pause");

  return 0;
}