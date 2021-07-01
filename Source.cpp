#include "DataGenerator.h"
#include "SortingAlgorithms.h"
#include "Terminal.h"
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
    //handleArguments(argc, argv);
    int algorithm = 0;
    if (Command_2(argc, argv, algorithm) == false)
        return false;
    return 0;
}
