#include "Terminal.h"
#include "DataGenerator.h"
#include "SortingAlgorithms.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int N_ALGORITHM = 7;
int N_OUTPUT_PARAM = 3;
int N_DATA_ORDER = 4;
string ALGORITHM_NAME[7] = { "selection-sort", "insertion-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort","radix-sort" };
string OUTPUT_PARAM[3] = { "-time","-comp","-both" };
string DATA_ORDER[4] = { "-rand","-nsorted","-sorted","-rev" };
int MAX_SIZE = 1000000;


//Kiểm tra chuỗi (string) có phải là một số không ? Kiểu trả về bool
bool isNumber(string s) {
    for (string::iterator i = s.begin(); i != s.end(); i++) {
        if (!isdigit(*i))
            return false;
    }
    return true;
}

//Tham chiếu đối số thứ 2 (int&) với chuỗi ALGORITHM_NAME[7]
bool isValidAlgorithm(string algorithm, int& valid_algorithm) {
    int Index = 0;
    while (Index < N_ALGORITHM) {
        if (ALGORITHM_NAME[Index] == algorithm)
            break;
        Index++;
    }

    if (Index == N_ALGORITHM)
        return false;

    valid_algorithm = Index;
    return true;
}

//Check Valid  parameters: "-time", "-comp", "-sort"
bool isValidOutputParam(string output_param, int& valid_output) {
    int Index = 0;
    while (Index < N_OUTPUT_PARAM) {
        if (OUTPUT_PARAM[Index] == output_param)
            break;
        Index++;
    }

    if (Index >= N_OUTPUT_PARAM) {
        return false;
    }

    valid_output = Index;
    return true;
}

//Check Valid order: "-rand", "-nsorted", "-sorted", "-rev"
bool isValidDataOrder(string data_order, int& valid_order) {
    int index = 0;
    while (index < N_DATA_ORDER) {
        if (DATA_ORDER[index] == data_order)
            break;
        index++;
    }
    if (index >= N_DATA_ORDER) {
        return false;
    }

    valid_order = index;
    return true;
}


/*
Input order
rand : randomized data
nsorted : nearly sorted data
sorted : sorted data
rev : reverse sorted data

Output parameters
• time : algorithms’s running time.
• comp : number of comparisions.
• both : both above options.

Valid Algorithm
"selection-sort", "insertion-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort", "radix-sort"
*/

bool readFile(string filename,int* &arr,int &input_size){
    ifstream ifs(filename);
    if(!ifs){
        cout << "Can't open '" << filename << "'\n";
        return false;
    }
    string n;
    getline(ifs,n);

    //Check if it is the number
    if (!isNumber(n)) {
        cout << "Not a number '" << n << "'" << endl;
        return false;
    }
    else {
        //Check the input size
        if (stoi(n) > MAX_SIZE) {
            cout << "Over the size limit: " << n << " > " << MAX_SIZE << endl;
            return false;
        }
        else {
            if (stoi(n) < 0) {
                cout << "Invalid size: n > 0" << endl;
                return false;
            }
        }
    }

    input_size = stoi(n);

    arr = new int[input_size];
    int i = 0;
    string tmp;

    while(!ifs.eof()){ 
        getline(ifs,tmp,' ');
        arr[i++] = stoi(n);
    }
    if(arr == NULL){
        cout << "Not enough memory" << endl;
        return false;
    }

    ifs.close();
    return true;
}

bool writeFile(string filename,int A[],int n){
    ofstream ofs(filename);
    if(!ofs){
        cout << "Can't open '" << filename <<"'.\n";
        return false;
    }

    ofs << n << endl;
    for(int i = 0; i < n - 1; i++){
        ofs << A[i] << " " ;
    }
    ofs << A[n - 1];
    ofs.close();
    return true;  
}

bool Command_1(int argc, char* argv[], int algorithm) {
    int output_param = 0;
    if (isValidOutputParam(argv[4], output_param) == false) {
        cout << "'" << argv[4] << "' is invalid output parameter." << endl;
        cout << "Output parameters: ";
        for (int i = 0; i < N_OUTPUT_PARAM; i++) {
            cout << OUTPUT_PARAM[i] << " ";
        }
        return false;
    }

    int input_size = 0;
    int* arr = NULL;
    if(readFile((string) argv[3],arr,input_size) == false){
        return false;
    }
   
    double running_time = 0;
    int count_compare = 0;

    switch (algorithm) {
        case 0:
            //Selection Sort
            selectionSort(arr, input_size, running_time, count_compare);
            break;
        case 1:
            //Insertion Sort, , , , and 
            insertionSort(arr, input_size, running_time, count_compare);
            break;
        case 2:
            //Bubble Sort
            bubbleSort(arr, input_size, running_time, count_compare);
            break;
        case 3:
            //Heap Sort
            break;
        case 4:
            //Merge Sort
            break;
        case 5:
            //QuickSort
            break;
        case 6:
            //Radix Sort
            break;
        case 7:
            break;
    }

    if(writeFile("output.txt",arr,input_size) == false){
        return false;
    }

    cout << "ALGORITHM MODE" << endl;
    cout << "Algorithm: " << ALGORITHM_NAME[algorithm] << endl;
    cout << "Input file: " << argv[3] << endl;
    cout << "Input size: " << input_size << endl;
    cout << "----------------------------------------------------------------" << endl;

    switch (output_param) {
        case 0:
            cout << "Running time: " << running_time << endl;
            break;
        case 1:
            cout << "Comparisons: " << count_compare << endl;
            break;
        case 2:
            cout << "Running time: " << running_time << endl;
            cout << "Comparisons: " << count_compare << endl;
            break;
    }

    if(arr != NULL)
        delete [] arr;
}

bool Command_2(int argc, char* argv[], int algorithm) {
    int output_param = 0;
    if (isValidOutputParam(argv[5], output_param) == false) {
        cout << "\"" << argv[5] << "\" is invalid output parameter." << endl;
        return false;
    }
   
    int input_order = 0;
    if (isValidDataOrder(argv[4], input_order) == false) {
        cout << "\"" << argv[4] << "\" is invalid input order." << endl;
        return false;
    }

    int inputSize = stoi((string)argv[3]);
    int* arr = new int[inputSize];
    double running_time = 0;
    int count_compare = 0;

    switch (input_order) {
        case 0: 
            //rand: randomized data
            GenerateData(arr, inputSize, 0);
            break;
        case 1: 
            //nsorted: nearly sorted data
            GenerateData(arr, inputSize, 3);
            break;
        case 2: 
            //sorted: sorted data
            GenerateData(arr, inputSize, 1);
            break;
        case 3: 
            //rev: reverse sorted data
            GenerateData(arr, inputSize, 2);
    }

    if(writeFile("input.txt",arr,inputSize) == false){
        return false;
    }

    switch (algorithm) {
        case 0:
            //Selection Sort
            selectionSort(arr, inputSize, running_time, count_compare);
            break;
        case 1:
            //Insertion Sort
            insertionSort(arr, inputSize, running_time, count_compare);
            break;
        case 2:
            //Bubble Sort
            bubbleSort(arr, inputSize, running_time, count_compare);
            break;
        case 3:
            //Heap Sort
            break;
        case 4:
            //Merge Sort
            break;
        case 5:
            //QuickSort
            break;
        case 6:
            //Radix Sort
            break;
        case 7:
            break;
    }

    cout << "ALGORITHM MODE" << endl;
    cout << "Algorithm: " << ALGORITHM_NAME[algorithm] << endl;
    cout << "Input size: " << inputSize << endl;
    cout << "Input order: " << DATA_ORDER[input_order] << endl;
    cout << "----------------------------------------------------------------" << endl;

    switch (output_param) {
        case 0:
            cout << "Running time: " << running_time << endl;
            break;
        case 1:
            cout << "Comparisons: " << count_compare << endl;
            break;
        case 2:
            cout << "Running time: " << running_time << endl;
            cout << "Comparisons: " << count_compare << endl;
            break;
    }
}

bool Command_3(int argc, char* argv[], int algorithm) {
    return true;
}
   
//---------------ALGORITHM MODE
bool handleAlgorithmsMode(int argc, char* argv[]) {
    if (argc <= 4) {
        cout << "Usage: [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]" << endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]" << endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]" << endl;
        return false;
    }
    else {
        int algorithm = 0;
        if (isValidAlgorithm(argv[2], algorithm) == false) {
            cout << "'" << argv[2] << "' is invalid algorithm name." << endl;
            cout << "All this name  will be accepted: " << endl;
            for (int i = 0; i < N_ALGORITHM; i++) {
                cout << "\t" << ALGORITHM_NAME[i] << endl;
            }
            return false;
        }
        else {  //isNumber((string)argv[3]
            if (isNumber((string)argv[3])) {
                if (stoi((string)argv[3]) > MAX_SIZE || stoi((string)argv[3]) < 0) {
                    cout << "Invalid input size" << endl;
                    cout << "Accepting input size n < " << MAX_SIZE << endl;
                    return false;
                }
                else {
                    if (argc > 6) {
                        cout << "Too many arguments" << endl;
                        return false;
                    }
                    else {
                        if (argc == 5) {
                            if(Command_3(argc, argv,algorithm) == false)
                                return false;
                        }
                        else {
                            if (argc == 6) {
                                if(Command_2(argc, argv,algorithm) == false)
                                    return false;
                            }
                        }
                    }

                }
            }
            else {
                if(Command_1(argc,argv,algorithm) == false)
                    return false;
            }
        }
    }
    return true;
}

//---------------COMPARISON MODE
bool handleComparisonMode(int argc, char* argv[]) {

    return true;
}

//---------------SHOW HELP AND CHANGE MODE
bool handleArguments(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]" << endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]" << endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]" << endl;
        cout << "       [Execution file] -c [Algorithm 1] [Algorithm 2] [Given input]" << endl;
        cout << "       [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]" << endl;
        return false;
    }
    else {
        if ((string)argv[1] == "-a") {
            return handleAlgorithmsMode(argc, argv);
        }
        else if((string)argv[1] == "-c")
            return handleComparisonMode(argc, argv);
    }

    return true;
}