#include <iostream>
#include <fstream>

#include "Terminal.h"
#include "DataGenerator.h"
#include "SortingAlgorithms.h"

using namespace std;

int MAX_SIZE = 1000000;
int N_ALGORITHM = 11;
int N_OUTPUT_PARAM = 3;
int N_DATA_ORDER = 4;
string ALGORITHM_NAME[11] = { "selection-sort", "insertion-sort", "bubble-sort","shaker-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort","counting-sort","radix-sort","flash-sort" };
string OUTPUT_PARAM[3] = { "-time","-comp","-both" };
string DATA_ORDER[4] = { "-rand","-nsorted","-sorted","-rev"};



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
    int index = 0;
    while (index < N_ALGORITHM) {
        if (ALGORITHM_NAME[index] == algorithm)
            break;
        index++;
    }

    if (index == N_ALGORITHM)
        return false;

    valid_algorithm = index;
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
    int index = 0;
    while (index < N_OUTPUT_PARAM) {
        if (OUTPUT_PARAM[index] == output_param)
            break;
        index++;
    }

    if (index >= N_OUTPUT_PARAM) {
        return false;
    }

    valid_output = index;
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
/*
Input order  "rand" : randomized data | "nsorted" : nearly sorted data | "sorted" : sorted data | "rev" : reverse sorted data

Output parameters  "time" : algorithms’s running time. • "comp" : number of comparisions "both" : both above options.

Valid Algorithm
"selection-sort", "insertion-sort", "bubble-sort","shaker-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort","counting-sort","radix-sort","flash-sort" 
*/

bool CheckDir(const string& string){
    struct stat buffer;
    return (stat(string.c_str(), &buffer) == 0);
}

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
        arr[i++] = stoi(tmp);
    }
    if(arr == NULL){
        cout << "Not enough memory" << endl;
        return false;
    }

    ifs.close();
    return true;
}

bool writeFile(string filename,int *arr,int n){
    ofstream ofs(filename);
    if(!ofs){
        cout << "Can't open '" << filename <<"'.\n";
        return false;
    }

    ofs << n << endl;
    for(int i = 0; i < n - 1; i++){
        ofs << arr[i] << " " ;
    }
    ofs << arr[n - 1];
    ofs.close();
    
    return true;  
}

//Ham tao mang array theo yeu cau (Data Order) !!!CHU Y inputDataOrder
void DataOrderMODE(int* arr,int inputSIZE ,int inputDataOrder) {
    switch (inputDataOrder) {
        case 0:
            //rand: randomized data
            GenerateData(arr, inputSIZE, 0);
            break;
        case 1: 
            //nsorted: nearly sorted data
            GenerateData(arr, inputSIZE, 3);
            break;
        case 2: 
            GenerateData(arr, inputSIZE, 1);
            //sorted: sorted data
            break;
        case 3: 
            GenerateData(arr, inputSIZE, 2);
            //rev: reverse sorted data
            break;
    }
}

//Switch case Algo
void AlgorithmsMODE(int* arr, int inputSIZE, double& running_time,unsigned int& count_compare, int algorithm) {
    switch (algorithm) {
        case 0:
            //Selection Sort
            selectionSort(arr, inputSIZE, running_time, count_compare);
            break;
        case 1:
            //Insertion Sort, , , , and 
            insertionSort(arr, inputSIZE, running_time, count_compare);
            break;
        case 2:
            //Bubble Sort
            bubbleSort(arr, inputSIZE, running_time, count_compare);
            break;
        case 3:
            //Shaker Sort

            break;
        case 4:
            //Shell Sort
            shellSort(arr, inputSIZE, running_time,count_compare);
            break;
        case 5:
            //Heap Sort
            heapSort(arr, inputSIZE, running_time, count_compare);
            break;
        case 6:
            //Merge Sort
            break;
        case 7:
            //QuickSort
            quickSort(arr, inputSIZE, running_time, count_compare);
            break;
        case 8:
            //Couting Sort
            countingSort(arr, inputSIZE, running_time, count_compare);
            break;
        case 9:
            //Radix Sort
            radixSort(arr, inputSIZE, running_time, count_compare);
            break;
        case 10:
            //Flash Sort
            flashSort(arr, inputSIZE, running_time, count_compare);
            break;
    }

}

void OutputConsoleForAlgorithmsMODE(int cmd,char* argv[],int output_param,double running_time,unsigned int count_compare,string Data_Order = "",bool isPrint = true,int file_size = 0){
    if(isPrint){
        cout << "ALGORITHM MODE"<<endl;

        string algorithm_name = (string) argv[2];
        cout << "Algorithm: " << algorithm_name << endl;
        
        if(cmd == 1){
            cout << "Input file: " << argv[3]<<endl;
            cout << "Input size: " << file_size << endl;
        }
        else{
            cout << "Input size: " << argv[3] << endl;
            if(cmd == 2){
                cout << "Input order: " << argv[4] << endl;
            }
        }
    }
        
    if(Data_Order != ""){
        if(cmd == 3){
            cout << endl<<"Input order: " << Data_Order << endl;
        }
    }
    cout << "----------------------------------------------------------------" << endl;
    switch (output_param) {
        case 0:
            cout << "Running time: " << running_time << "s" << endl;
            break;
        case 1:
            cout << "Comparisions: " << count_compare << endl;
            break;
        case 2:
            cout << "Running time: " << running_time << "s" << endl;
            cout << "Comparisions: " << count_compare << endl;
            break;
    }
}

void OutputConsoleForComparisonsMODE(int cmd,char* argv[],double running_time1,double running_time2,unsigned int count_compare1,unsigned int count_compare2,int INPUT_FILE_SIZE = 0){
    cout << "COMPARE MODE" <<endl;
    cout << "Algorithm: " << argv[2] << " | " << argv[3] << endl;
    if(cmd == 4){
        cout << "Input file: " << argv[4] << endl;
        cout << "Input size: " << INPUT_FILE_SIZE << endl;
    }
    else{
        if(cmd == 5){
            cout << "Input size: " << argv[4] << endl;
            cout << "Input order: "<< argv[5] << endl;
        }
    }

    cout << "----------------------------------------------------------------" << endl;
    cout << "Running time: "<< running_time1 << "s | " << running_time2 <<"s"<< endl;
    cout << "Comparisions: "<< count_compare1<< " | " << count_compare2<< endl;

}

bool Command_1(int argc, char* argv[], int algorithm) {
    string filename = (string) argv[3];
    int output_param = 0;
    if (isValidOutputParam(argv[4], output_param) == false) {
        ifNOTValidAlgorithm(argv[4]);
        return false;
    }

    int input_size = 0;
    int* arr = NULL;
    if(readFile(filename,arr,input_size) == false){
        return false;
    }
   
    double running_time = 0;
    unsigned int count_compare = 0;

    AlgorithmsMODE(arr, input_size, running_time, count_compare, algorithm);

    if(writeFile("output.txt",arr,input_size) == false){
        return false;
    }

    OutputConsoleForAlgorithmsMODE(1,argv,output_param,running_time, count_compare,"",true,input_size);
    
    if(arr != NULL)
        delete [] arr;
    return true;
}

bool Command_2(int argc, char* argv[], int algorithm) {
    //[Execution file] - a[Algorithm][Input size][Input order] [Output parameter(s)]
   
    //Check valid [Output parameter(s)] if not show valid [Output parameter(s)] 
    int output_param = 0;
    if (isValidOutputParam(argv[5], output_param) == false) {
        ifNOTValidAlgorithm(argv[5]);
        return false;
    }

    //[Input size]
    int inputSize = stoi((string)argv[3]);
    int x = inputSize;

    //Check valid input data order if not show valid input order to users
    //Check valid [Input order] if not show valid [Input order]
    int input_order = 0;
    if (!isValidDataOrder(argv[4], input_order)) {
        ifNOTValidDataOrder(argv[4]);
        return false;
    }

    //[Input order] MODE
    int* arr = new int[inputSize];
    DataOrderMODE(arr, inputSize, input_order);

    double running_time = 0;
    unsigned int count_compare = 0;

    //Write generated data to input.txt
    if(writeFile("input.txt", arr, inputSize) == false){
        return false;
    }

    AlgorithmsMODE(arr, inputSize, running_time, count_compare, algorithm);
    OutputConsoleForAlgorithmsMODE(2,argv,output_param,running_time, count_compare);
    
    //Write sorted data to output.txt
    if (writeFile("output.txt", arr, inputSize) == false) {
        return false;
    }

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

    double running_time = 0;
    unsigned int count_compare = 0;

    bool flag = true;
    for (int i = 0; i < 4; i++) {
        if(i == 1){
            flag = false;
        }
        //Tao mang du lieu theo yeu cau
        int* arr = new int[inputSize];
        running_time = 0;
        count_compare = 0;
        DataOrderMODE(arr, inputSize, i);

        string suffix = ".txt";
        string filename = "input_";
        filename.append(to_string(i + 1)).append(suffix);

        if(writeFile(filename, arr, inputSize) == false){
            return false;
        }

        AlgorithmsMODE(arr, inputSize, running_time, count_compare, algorithm);
        OutputConsoleForAlgorithmsMODE(3,argv,output_param,running_time, count_compare,DATA_ORDER[i], flag);

        delete[]arr;
    }
    
    return true;     
}

bool Command_4(int argc, char* argv[], int algorithm1, int algorithm2){
    string filename = argv[4];

    int* arr;
    int input_size = 0;
    
    if(readFile(filename,arr,input_size) == false)
        return false;

    //Copy input to brr
    int* brr = new int[input_size];
    for (int i = 0; i < input_size; i++)
        brr[i] = arr[i];

    double running_time1 = 0, running_time2 = 0;
    unsigned int count_compare1 = 0, count_compare2 = 0;

    AlgorithmsMODE(arr, input_size, running_time1, count_compare1, algorithm1);
    AlgorithmsMODE(brr, input_size, running_time2, count_compare2, algorithm2);

    OutputConsoleForComparisonsMODE(4,argv,running_time1,running_time2, count_compare1, count_compare2,input_size);
 
    delete[]arr;
    delete[]brr;
    return true;
}

//---------------ALGORITHM MODE
bool handleAlgorithmsMode(int argc, char* argv[]) {
    int algorithm = 0;
    if (isValidAlgorithm(argv[2], algorithm) == false) {
        ifNOTValidAlgorithm(argv[2]);
        return false;
    }
    else {
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
            if ( isNumber((string)argv[4])) {
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
        cout << "0-Selection Sort,1-Insertion Sort,2-Bubble Sort,3-Shaker Sort,4-Shell Sort,5-Heap Sort,6-Merge Sort,7-Quick Sort,8-Counting Sort,9-Radix Sort,10-Flash Sort \n";
        unsigned int algorithm;
        do {
            cout << "input algorithm code (0-10) \n";
            cin >> algorithm;
        }
        while ( algorithm > 10);
        unsigned int DATA_SIZE[6] = { 10000 ,30000,50000,100000, 300000, 500000 };
        cout << "Algorithms: " <<ALGORITHM_NAME[algorithm] << endl;
        for (int i = 0; i < 6; i++) {
            for (int j = 1; j < 4; j++) {
                int inputSize = DATA_SIZE[i];
                int* arr = new int[inputSize];
                double running_time = 0;
                unsigned int count_compare = 0;
                DataOrderMODE(arr, inputSize, j);
                AlgorithmsMODE(arr, inputSize, running_time, count_compare, algorithm);
                cout <<"Input size: " <<inputSize << endl;
                cout <<"Input order: "<< DATA_ORDER[j] << endl;
                cout << "---------------------------------------------" <<endl;
                cout << "Running time: " << running_time  << "s"<< endl;
                cout << "Comparisions: " << count_compare << "\n\n";
                delete[]arr;
            }
        }
        
    }

    if (choice == 2) {
        while(true){
            cout << "\n-----------------CONSOLE MODE---------------\n";
            cout << "Enter 'q' to quit program.\n";
            cout << "Enter command: \n";
            string line,temp[6]; 
            int argc = 0;
            char** argv = new char* [6];
            cin.ignore();
            getline(cin, line);
            if(line == "q" || line == "")
                break;
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

            for(int i = 0; i < argc;i++){
                delete[] argv[i];
            }
            delete[] argv;
            
        //-------------------------------------------  
        }
              
    }
   
}