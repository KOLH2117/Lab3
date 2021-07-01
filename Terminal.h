#pragma once
#ifndef _TERMINAL_H_
#define _TERMINAL_H_
#include <string>
using namespace std;
bool isNumber(string s);
bool isValidAlgorithm(string algorithm, int& valid_algorithm);
bool isValidOutputParam(string output_param, int& valid_output);
bool isValidDataOrder(string data_order, int& valid_order);
bool handleAlgorithmsMode(int argc, char* argv[]);
bool handleComparisonMode(int argc, char* argv[]);
bool handleArguments(int argc, char* argv[]);
bool Command_1(int argc, char* argv[], int algorithm);
bool Command_2(int argc, char* argv[], int algorithm);
#endif 
