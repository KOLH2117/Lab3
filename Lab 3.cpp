#include <string>
#include <sstream>

#include "DataGenerator.cpp"

using namespace std;

int N_ALGORITHM = 7;
int N_OUTPUT_PARAM = 3;
int N_DATA_ORDER =4;
string ALGORITHM_NAME[7] = {"selection-sort", "insertion-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort","radix-sort"};
string OUTPUT_PARAM[3] = {"-time","-comp","-both"};
string DATA_ORDER[4] = {"-rand","-nsorted","-sorted","-rev"};
int MAX_SIZE = 1000000;

void swap(int &a,int &b){
    int c = a;
    a = b;
    b = c;
}

//-------------------------->Insertion Sort
void insertionSort(int arr[], int n, double &running_time, int &count_compare){
    clock_t start, end;
    start = clock();

    int key, j;
    for (int i = 1;(++count_compare) && i < n; i++){
        key = arr[i];
        j = i - 1;

        while (((++count_compare) && j >= 0) &&((++count_compare) && arr[j] > key)){
            //count_compare += 2;
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }

    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Insertion Sort

//-------------------------->Bubble Sort
void bubbleSort(int arr[], int n, double &running_time, int &count_compare){
	clock_t start, end;
	start = clock();

	for (int i = 0;(++count_compare) && i < n-1; i++){
		for (int j = 0; (++count_compare) && j < n - i - 1; j++){
			 if ((++count_compare) && arr[j] > arr[j + 1])
				 swap(arr[j], arr[j + 1]);
		}
	}

	end = clock();
	running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Bubble Sort

//-------------------------->Heap Sort
void sift(int arr[], int left, int right,double &running_time,int &count_compare){
    int i = left;
    int j = 2 * i;
    int x = arr[i];

    while ((++count_compare) && j <= right){
        if ((++count_compare) && j < right)
            if ((++count_compare) && arr[j] > arr[j + 1])
                j++;
        if ((++count_compare) &&x <= arr[j])
            break;
        arr[i] = arr[j];
        i = j;
        j = 2 * i;
    }

    arr[i] = x;
}

void createHeap(int arr[], int n,double &running_time, int &count_compare){
    //Make the array into a heap

    int left = (n-1) / 2;
    while ((++count_compare) && left > -1){
        sift(arr, left, n - 1,running_time,count_compare);
        left--;
    }
}

void heapSort(int arr[], int n, double &running_time, int &count_compare){
    clock_t start, end;
    start = clock();

    createHeap(arr,n,running_time,count_compare);

    int right = n - 1;

    while ((++count_compare) && right > 0){ 
        swap(arr[0],arr[right]);
        right--;
        sift(arr,0, right,running_time,count_compare);
    }

    for (int i = 0;(++count_compare) && i < n / 2; i++){
        swap(arr[i],arr[n - 1 - i]);
    }

    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Heap Sort

//-------------------------->Quick Sort
int partition(int arr[], int low, int high, int &count_compare)
{
    int pivot = arr[high];
    int left = low;
    int right = high - 1;
    while (true)
    {
        while ((++count_compare && left <= right) && (++count_compare && arr[left] < pivot))
        {
            left++;
        }

        while ((++count_compare && right >= left) && (++count_compare && arr[right] > pivot))
        {
            right--;
        }

        
        if (++count_compare && left >= right)
            break;

        swap(arr[left], arr[right]);
        left++;
        right--;
    }
    swap(arr[left], arr[high]);
    return left;
}

void Sort(int arr[], int low, int high, int &count_compare)
{
    if (++count_compare && low < high)
    {
        int pi = partition(arr, low, high, count_compare);

        Sort(arr, low, pi - 1, count_compare);
        Sort(arr, pi + 1, high, count_compare);
    }
}

void QuickSort(int arr[], int n, double& time_use, int& count_compare)
{
    count_compare = 0;
    time_use = 0;

    clock_t start, end;

    start = clock();

    Sort(arr, 0, n - 1, count_compare);

    end = clock();

    time_use = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Quick Sort


void printArray(int *arr, int n){
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

bool isNumber(string s){
    for(string::iterator i = s.begin(); i != s.end();i++){
        if(!isdigit(*i)) 
            return false;
    }
    return true;
}

bool isValidAlgorithm(string algorithm,int &valid_algorithm){
    int Index = 0;
    while(Index < N_ALGORITHM){
        if(ALGORITHM_NAME[Index] == algorithm)
            break;
        Index++;
    }

    if(Index == N_ALGORITHM)
        return false;
    
    valid_algorithm = Index;
    return true;
}

bool isValidOutputParam(string output_param,int &valid_output){
    int Index = 0;
    while(Index < N_OUTPUT_PARAM){
        if(OUTPUT_PARAM[Index] == output_param)
            break;
        Index++;
    }

    if(Index >= N_OUTPUT_PARAM){
        return false;
    }

    valid_output = Index;
    return true;
}

bool Command_1(int argc,char* argv[],int algorithm){
    int output_param = 0;
    if(isValidOutputParam(argv[4],output_param) == false){
        cout << "'" << argv[4] << "' is invalid output parameter." << endl;
        cout << "Output parameters: ";
        for(int i = 0; i < N_OUTPUT_PARAM;i++){
            cout << OUTPUT_PARAM[i] << " ";
        }
        return false;
    }

    string filename = argv[3];
    ifstream ifs(filename);
    if(!ifs){
        cout << "Can't open file '" << filename <<"' to read"<<endl;
        return false;
    }

    //Read input size
    string n="";
    getline(ifs,n);
    int size = 0;
    //Check if it is the number
    if(!isNumber(n)){
        cout << "Not a number '" << n << "'" << endl;
        return false;
    }
    else{
        //Check the input size
        size = stoi(n);
        if(size > MAX_SIZE){
            cout << "Over the size limit: "<<n<<" > " << MAX_SIZE << endl;
            return false;
        }
        else{
            if(size < 0){
                cout << "Invalid size: n > 0"<<endl;
                return false;
            }
        }
    }
    
    
    int *arr = new int[size];
    int arr_size = 0;
    string tmp;

    //Read the array from file to arr
    while(!ifs.eof()){
        getline(ifs, tmp,' ');
        arr[arr_size++] = stoi(tmp);
    }
    ifs.close();

    double running_time = 0;
    int count_compare = 0;

    switch(algorithm){
        case 0:
            break;
        case 1:
            insertionSort(arr,arr_size,running_time,count_compare);
            break;
        case 2:
            bubbleSort(arr,arr_size,running_time,count_compare);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
    }

    ofstream ofs("output.txt");
    if(!ofs){
        cout << "Can't open file to write"<<endl;
        return false;
    }

    ofs << n << endl;
    for(int i = 0; i < arr_size - 1; i++){
        ofs << arr[i] << " ";
    }
    ofs << arr[size - 1];
    ofs.close();

    cout << "ALGORITHM MODE"<<endl;
    cout << "Algorithm: " << ALGORITHM_NAME[algorithm]<<endl;
    cout << "Input file: "<<filename<<endl;
    cout << "Input size: "<< n<<endl;
    cout << "----------------------------------------------------------------"<<endl;

    switch(output_param){
        case 0: 
            cout << "Running time: "<< running_time << endl; 
            break;
        case 1:
            cout << "Comparisons: "<<count_compare << endl;
            break;
        case 2:
            cout << "Running time: "<< running_time << endl;
            cout << "Comparisons: "<<count_compare << endl;
            break;  
    }  
}


bool handleAlgorithmsMode(int argc,char* argv[]){
    if(argc <= 4){
        cout << "Usage: [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]"<<endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]"<<endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]"<<endl;
        return false;
    }
    else{
        int algorithm = 0;
        if(isValidAlgorithm(argv[2],algorithm) == false){
            cout << "'" <<argv[2] << "' is invalid algorithm name." << endl;
            cout << "All this name  will be accepted: "<<endl;
            for(int i = 0; i < N_ALGORITHM; i++){
                cout <<"\t"<< ALGORITHM_NAME[i]<<endl;
            }
            return false;
        }
        else{
            if(isNumber((string) argv[3])){
                if(stoi((string) argv[3]) > MAX_SIZE || stoi((string) argv[3]) < 0){
                    cout <<"Invalid input size" << endl;
                    cout << "Accepting input size n < "<< MAX_SIZE <<endl;
                    return false;
                }
                else{
                    if (argc > 6){
                        cout << "Too many arguments" << endl;
                        return false;
                    }
                    else{
                        if(argc == 5){
                            
                        }
                        else{
                            if(argc == 6){

                            }
                        }
                    }
                    
                }
            }
            else{
                if(Command_1(argc,argv,algorithm) == false)
                    return false;
            }
        }
    }
    return true;
}

bool handleComparisonMode(int argc,char* argv[]){
    
    return true;
}


bool handleArguments(int argc, char*argv[]){
    if(argc < 2){
        cout << "Usage: [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]"<<endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]"<<endl;
        cout << "       [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]"<<endl;
        cout << "       [Execution file] -c [Algorithm 1] [Algorithm 2] [Given input]"<<endl;
        cout << "       [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]"<<endl;
        return false;
    }
    else{
        if((string)argv[1] == "-a"){
            return handleAlgorithmsMode(argc, argv);
        }
        else
            return handleComparisonMode(argc, argv);
    }

    return true;    
}



int main(int argc, char *argv[]){
    // if(handleArguments(argc,argv) == false)
    //    return 0;
    ofstream ofs("input.txt",ios::out);
    if(!ofs){
        cout << "Can't open file" ;
        return 0;
    }

    int n;
    cin >> n;
    int *arr = new int[n];
    ofs << n << endl;
    GenerateData(arr,n,0);
    for(int i = 0; i < n - 1; i++){
        ofs << arr[i] << " ";
    }
    ofs << arr[n-1];

    return 0;
}
