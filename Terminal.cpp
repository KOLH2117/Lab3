#include "Terminal.h"
#include "DataGenerator.h"
#include "SortingAlgorithms.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
const int N_ALGORITHM = 7;
const int N_OUTPUT_PARAM = 3;
const int N_DATA_ORDER = 4;
string ALGORITHM_NAME[7] = { "selection-sort", "insertion-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort","radix-sort" };
string OUTPUT_PARAM[3] = { "-time","-comp","-both" };
string DATA_ORDER[4] = { "-rand","-nsorted","-sorted","-rev" };
const int MAX_SIZE = 1000000;


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
void ifNOTValidAlgorithm(string algorithm) {
    cout << "'" << algorithm << "' is invalid algorithm name." << endl;
    cout << "All this name  will be accepted: " << endl;
    for (int i = 0; i < N_ALGORITHM; i++) {
        cout << "\t" << ALGORITHM_NAME[i] << endl;
    }
    
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
void ifNOTValidOutputParam(string output_param) {
    cout << "'" << output_param << "' is invalid output parameter." << endl;
    cout << "Output parameters: ";
    for (int i = 0; i < N_OUTPUT_PARAM; i++) {
        cout << OUTPUT_PARAM[i] << " ";
    }
    
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
void ifNOTValidDataOrder(string data_order) {
    cout << "\"" << data_order << "\" is invalid input order." << endl;
    cout << "Input order: ";
    for (int i = 0; i < N_DATA_ORDER; i++) {
        cout << DATA_ORDER[i] << " ";
    }
   
}

//Ham tao mang array theo yeu cau (Data Order) !!!CHU Y inputDataOrder
void DataOrderMODE(int* arr,int inputSIZE ,int inputDataOrder) {
    switch (inputDataOrder) {
    case 0: {
        //rand: randomized data
        GenerateData(arr, inputSIZE, 0);
    } break;
    case 1: {
        //nsorted: nearly sorted data
        GenerateData(arr, inputSIZE, 3);
    } break;
    case 2: {
        GenerateData(arr, inputSIZE, 1);
        //sorted: sorted data
    } break;
    case 3: {
        GenerateData(arr, inputSIZE, 2);
        //rev: reverse sorted data
    } break;
    }
}

//Switch case Algo
void AlgorithmsMODE(int* arr, int inputSIZE, double& running_time, int& count_compare, int algorithm) {

    switch (algorithm) {
    case 0:
        //Selection Sort
        selectionSort(arr, inputSIZE, running_time, count_compare);
        break;
    case 1:
        //Insertion Sort
        insertionSort(arr, inputSIZE, running_time, count_compare);
        break;
    case 2:
        //Bubble Sort
        bubbleSort(arr, inputSIZE, running_time, count_compare);
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

}

//Support only for command 1,2,3
void OutputConsole(string ALGORITHM_NAME, int INPUT_SIZE, string INPUT_ODER, int output_param,double running_time, int count_compare, string INPUT_FILE = "") {
    cout << endl;
    cout << "ALGORITHM MODE" << endl;
    cout << "Algorithm: " << ALGORITHM_NAME << endl;
    if (INPUT_FILE != "") {
        cout << "Input file: " << INPUT_SIZE << endl;
    }
    else {
        if (INPUT_SIZE > 0) {
            cout << "Input size " << INPUT_SIZE << endl;
       }
    }
    cout << "Input order: " << INPUT_ODER << endl;
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

/*
Input order  "rand" : randomized data | "nsorted" : nearly sorted data | "sorted" : sorted data | "rev" : reverse sorted data

Output parameters  "time" : algorithms’s running time. • "comp" : number of comparisions "both" : both above options.

Valid Algorithm
"selection-sort", "insertion-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort", "radix-sort"
*/

//Make directory Output in current directory
bool CheckDir(const string& string)
{
    struct stat buffer;
    return (stat(string.c_str(), &buffer) == 0);
}

bool writeGenarateArray(string filename, int* arr, int n, int MODE = 1) {
    fstream fs;
    string temp;
    if (CheckDir("Output")) {
        temp = "output\\" + filename;
        fs.open(temp, ios::out);
    }
    else {
       int checkMake = _mkdir("output");
       if (!checkMake) {
           fs.open(temp, ios::out);
       }
       else {
           fs.open(filename, ios::out);
       }
    }

   
   
    if (fs) {
        fs << n << endl;
        for (int i = 0; i < n; i++) {
            fs << arr[i] << " ";
        }
        fs.close();
        if (MODE == 1) {
            cout << "Write to file '" << filename << "' successfully\n";
        }
        return true;
    }
    else {
        if (MODE == 1) {
            cout << "Write to file '" << filename << "' failed\n"; 
        }
        return false;
    }
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

    string filename = argv[3];
    ifstream ifs(filename);
    if (!ifs) {
        cout << "Can't open file '" << filename << "' to read" << endl;
        return false;
    }

    //Read input size
    string n = "";
    getline(ifs, n);

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


    int* arr = new int[stoi(n)];
    int x = 0;
    string tmp;

    //Read the array from file to arr
    while (!ifs.eof()) {
        getline(ifs, tmp, ' ');
        arr[x++] = stoi(tmp);
    }

    double running_time = 0;
    int count_compare = 0;

    switch (algorithm) {
    case 0:
        //Selection Sort
        selectionSort(arr, x, running_time, count_compare);
        break;
    case 1:
        //Insertion Sort
        insertionSort(arr, x, running_time, count_compare);
        break;
    case 2:
        //Bubble Sort
        bubbleSort(arr, x, running_time, count_compare);
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
    cout << "Input file: " << filename << endl;
    cout << "Input size: " << n << endl;
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

bool Command_2(int argc, char* argv[], int algorithm) {
    //[Execution file] - a[Algorithm][Input size][Input order] [Output parameter(s)]
   
    //Check valid [Output parameter(s)] if not show valid [Output parameter(s)] 
    int output_param = 0;
    if (!isValidOutputParam(argv[5], output_param)) {
        ifNOTValidAlgorithm(argv[5]);
        return false;
    }

    //[Input size]
    int inputSize = stoi((string)argv[3]);
    int x = inputSize;

    //Check valid [Input order] if not show valid [Input order]
    int input_order = 0;
    if (!isValidDataOrder(argv[4], input_order)) {
        ifNOTValidDataOrder(argv[4]);
        return false;
    }
    //[Input order] MODE
    int* arr = new int[inputSize];
    DataOrderMODE(arr, inputSize, input_order);
    
    // Write down the generated input to the "input.txt" file
    bool checkInputFile = writeGenarateArray("input.txt", arr, x, 0);

    //[Algorithm] MODE
    double running_time = 0;
    int count_compare = 0;

    AlgorithmsMODE(arr, inputSize, running_time, count_compare, algorithm);
    OutputConsole(ALGORITHM_NAME[algorithm], inputSize, DATA_ORDER[input_order], output_param,running_time, count_compare);
    
    
    
    if (checkInputFile == false) {
        cout << "Write to file 'input.txt' failed \n";
    }
    else {
        cout << "Write to file 'input.txt' successfully \n";
    }

    //Write down the sorted array to the "output.txt" file.
    writeGenarateArray("output.txt", arr, x, 1);

    delete[]arr;
    return true;

}
   
bool Command_3(int argc, char* argv[], int algorithm) {
    //[Execution file] -a [Algorithm] [Input size] [Output parameter(s)]

    
    //Check vaid output parameters if not show valid output parameters to users
    int output_param = 0;
    if (!isValidOutputParam(argv[4], output_param)) {
        ifNOTValidOutputParam(argv[4]);
        return false;
    }
    
    //Check valid input size 
    int inputSize = stoi((string)argv[3]);
    int x = inputSize; 

    //int* arr = new int[inputSize];
    //double running_time = 0;
    //int count_compare = 0;
    
    for (int i = 0; i < 4; i++) {
        //Tao mang du lieu theo yeu cau
        int* arr = new int[inputSize];
        double running_time = 0;
        int count_compare = 0;
        DataOrderMODE(arr, inputSize, i);

        string suffix = ".txt";
        string filename = "input_";
        filename.append(to_string(i + 1)).append(suffix);

        bool checkCount = writeGenarateArray(filename, arr, inputSize, 0);


        AlgorithmsMODE(arr, inputSize, running_time, count_compare, algorithm);
        OutputConsole(ALGORITHM_NAME[algorithm], inputSize, DATA_ORDER[i], output_param, running_time, count_compare);

        delete[]arr;
if (checkCount) {
    cout << "Write to file " << filename << " successfully\n";
}

    }
    //delete[]arr;
    return true;

}

bool Command_4(int argc, char* argv[], int algorithm1, int algorithm2) {
    cout << "day la command 4";
    return true;
};

//---------------ALGORITHM MODE
bool handleAlgorithmsMode(int argc, char* argv[]) {
    /*if (argc <= 4) {
        cout << "Usage: [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]" << endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]" << endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]" << endl;
        return false;
    }*/
    //else {
    int algorithm = 0;
    if (isValidAlgorithm(argv[2], algorithm) == false) {
        ifNOTValidAlgorithm(argv[2]);
        return false;
    }
    else {  //isNumber((string)argv[3]
        if (stoi((string)argv[3])) {
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
                    if (argc == 6) {
                        if (Command_2(argc, argv, algorithm) == false) {
                            return false;
                        }
                        return true;
                    }
                    else {
                        if (argc == 5) {
                            if (Command_3(argc, argv, algorithm) == false) {
                                return false;
                            }
                            return true;
                        }
                    }
                }

            }
        } //if argv[3] not a number -> input file
            //check inputfile
        else {
            /*
            if(Command_1(argc,argv,algorithm) == false)
                return false;
            */
        }
    }
    //}
    return true;
}

//---------------COMPARISON MODE
bool handleComparisonMode(int argc, char* argv[]) {
    int algorithm1 = 0;
    int algorithm2 = 0;
    //kiem tra thuat toan 1
    if (isValidAlgorithm(argv[2], algorithm1) == false) {
        ifNOTValidAlgorithm(argv[2]);
        return false;
    }
    else {
        //kiem tra thuat toan 2
        if (isValidAlgorithm(argv[3], algorithm2) == false) {
            ifNOTValidAlgorithm(argv[3]);
            return false;
        }
        else {
            //Check input size for command 4
            bool check = isNumber((string)argv[4]);
            if (check) {
                if (stoi((string)argv[4]) > MAX_SIZE || stoi((string)argv[4]) < 0) {
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
                        if (argc == 6) {
                        /*
                        
                        COMMAND 5 IS HERE
                        Vi du
                        if(Command_5(argc, argv, algorithm1, algorithm2) == false) {
                            return false;
                        }
                        return true;

                        */
                            
                        }
                        
                    }
                }
            }
            //Neu argv[4] khong phai la 1 so -> Input file
            else {
                if (argc == 5) {
                       if(Command_4(argc, argv, algorithm1,algorithm2 ) == false) {
                           return false;
                       }
                       else {
                           return true;
                       }

    
                }
            }
            
        }
    }
    return true;
}

//---------------SHOW HELP AND CHANGE MODE
bool handleArguments(int argc, char* argv[]) {
    if (argc <= 4) {
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
        else {
            cout << "Wrong mode: only accept: '-a': Algorithm mode | '-c': Comparison mode";
            return false;
        }
    }

    return true;
}
void DevTestMode() {
   
    cout << "\n-----------------TEST MODE-----------------\n";
    cout << "1 - Sorting test: \n";
    cout << "2 - Console test: \n";
    cout << "---------------------------------------------\n";
    int choice; cout << "Enter choice: "; cin >> choice;

    if (choice == 1) {
        cout << "\n-----------------SORTING TEST---------------\n";
        cout << "0-Selection Sort,1-Insertion Sort, 2-Bubble Sort, 3-Heap Sort, 4-Merge Sort, 5-QuickSort, 6-Radix Sort \n";
        unsigned int algorithm;
        do {
            cout << "input algorithm code (0-6) \n";
            cin >> algorithm;
        }
        while ( algorithm > 6);
        unsigned int DATA_SIZE[6] = { 10000 ,30000,50000,100000, 300000, 500000 };
        for (int i = 0; i < 6; i++) {
            
            
            for (int j = 0; j < 4; j++) {
                int inputSize = DATA_SIZE[i];
                int* arr = new int[inputSize];
                double running_time = 0;
                int count_compare = 0;
                DataOrderMODE(arr, inputSize, j);
                AlgorithmsMODE(arr, inputSize, running_time, count_compare, algorithm);
                OutputConsole(ALGORITHM_NAME[algorithm], inputSize, DATA_ORDER[j], 2, running_time, count_compare);
                delete[]arr;
            }
           
        }
        
    }

    if (choice == 2) {
        
        cout << "\n-----------------CONSOLE MODE---------------\n";
        cout << "Enter commnad \n";
        cin.ignore();
        string line,temp[6]; int argc = 0;
        char** argv = new char* [6];
        getline(cin, line);
        stringstream ss(line);
        while (!ss.eof()) {
            getline(ss, temp[argc], ' ');
            argc++;
        }

        for (int i = 0; i < argc; i++) {
            argv[i] = new char[30];
            for (int j = 0; j < temp[i].size(); j++) {
                argv[i][j] = temp[i][j];
            }
            argv[i][temp[i].size()] = '\0';
        }
        
       
       //Write your code here:
        //-------------------------------------------

        if (handleArguments(argc, argv)) {
        }
       
       //-------------------------------------------        
    }
   
}