
#include "DataGenerator.h"
#include "SortingAlgorithms.h"
#include "Terminal.h"
#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {
   
    
    //Luu y, neu thay doi o ham main nhu the nao -> thi vao trong ham DevTestMode thay doi y chang cho co command danh dau -> De chay DevTestMode binh thuong
    
    // comment cai nay de chay DevTestMode
    /*
    
    if (handleArguments(argc, argv)) {
    }
    
    */

    //Xoa comment phia tren va comment DevTestMode de build ra file .exe nhu binh thuong
    DevTestMode();
    return 0;
}