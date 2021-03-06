#pragma warning(disable:4996)
#ifndef _TERMINAL_H
#define _TERMINAL_H
#include <string>
#include <sys/stat.h>
#include<direct.h>
#include <sstream>


using namespace std;
bool isNumber(string s);
bool isValidAlgorithm(string algorithm, int& valid_algorithm);
bool isValidOutputParam(string output_param, int& valid_output);
bool isValidDataOrder(string data_order, int& valid_order);
void ifNOTValidAlgorithm(string algorithm);
void ifNOTValidOutputParam(string output_param);
void ifNOTValidDataOrder(string data_order);
void OutputConsole(string ALGORITHM_NAME, int INPUT_SIZE, string INPUT_ODER, int output_param, double running_time, int count_compare,string INPUT_FILE);
void DataOrderMODE(int* arr, int inputSIZE, int inputDataOrder);
bool handleAlgorithmsMode(int argc, char* argv[]);
void AlgorithmsMODE(int* arr, int inputSIZE, double& running_time, int& count_compare, int algorithm);
bool handleComparisonMode(int argc, char* argv[]);
bool handleArguments(int argc, char* argv[]);
bool Command_1(int argc, char* argv[], int algorithm);
bool Command_2(int argc, char* argv[], int algorithm);
bool Command_3(int argc, char* argv[], int algorithm);
//MODE = 1 have cout, MODE = 0 no cout, default MODE = 1
bool writeGenarateArray(string filename, int* arr, int n, int MODE);
bool CheckDir(const string& string);
void DevTestMode();
#endif 
