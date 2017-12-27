#include "Arenstorf.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <limits>

#define INPUT_FILE_OPEN_ERROR   "Failed to open input file "
#define OUTPUT_FILE_OPEN_ERROR  "Failed to open output file "
#define INVALID_FILE_FORMAT "wrong file format\n"
#define INVALID_PARAMETER_FORMAT "wrong parameter format\n"
#define INCORRECT_USAGE "wrong number of arguments\n"

#define ENTER_POS_X "Enter initial pos x:\n"
#define ENTER_POS_Y "Enter initial pos y:\n"
#define ENTER_VEL_X "Enter initial vel x:\n"
#define ENTER_VEL_Y "Enter initial vel y:\n"
#define ENTER_TIME "Enter total time T:\n"
#define ENTER_STEPS "Enter num of steps:\n"
#define ENTER_STEPS_TO_SAVE "Enter num of steps to save:\n"

using namespace std;

/**
 * This is the main file. It has a main method which receives arguments from the user (by a file
 * or by cin). Then, it creates an Arenstorf object and calculates its point in each time unit.
 */

/**
 * This struct holds the numbers - x,y,vx,vy,t,n,m which represent the users choice of
 * start velocity, position, time, ect. It will be received by an input file / user.
 */
struct Args
{
	long double x = 0;
	long double y = 0;
	long double vx = 0;
	long double vy = 0;
	long double T = 0;
	unsigned int n = 0;
	unsigned int m = 0;
};

//int RunTest(const Args &args);

int runExercise(std::ofstream &outputFile, const Args &args);

/**
 * fill arguments from input file
 * @param fileName the name of the input file
 * @param args a struct args
 * @return true if the process succeeded, and false otherwise.
 */
bool fillArgsFromFile(const char *fileName, Args *args)
{
	ifstream inputFile(fileName);

	if (!inputFile.is_open())
	{
		cerr << INPUT_FILE_OPEN_ERROR << fileName << "\n";
		return false;
	}

	string comma;

	inputFile >> args->x >> comma >> args->y >> comma >> args->vx >> comma >> args->vy;
	inputFile >> args->T >> comma >> args->n >> comma >> args->m;

	if (inputFile.fail())
	{
		cerr << INVALID_FILE_FORMAT;
		return false;
	}

	return true;
}

void checkAndResetInput(bool *flag)
{
	if (cin.fail())
	{
		//http://www.cplusplus.com/reference/ios/ios/clear/
		cin.clear(ios::goodbit);
		//http://www.cplusplus.com/reference/istream/istream/ignore/
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		*flag = false;
	}
}
/**
 * Get long double from the user
 * @param message a message which has information on the wanted long double
 * @param value the value to fill
 * @return true if the paramter that was given is valid, false otherwise.
 */
void getLongDouble(const char *messageOut, long double *value, bool* flag)
{
	cout << messageOut;
	cin >> *value;
	checkAndResetInput(flag);
}

/**
 * Get unsigned integer from the user.
 * @param message a message which has information on the wanted integer
 * @param value the value to fill
 * @return true if the paramter that was given is valid, false otherwise.
 */
void getUnsignedInteger(const char *messageOut, unsigned int *value, bool *flag)
{
	cout << messageOut;
	cin >> *value;
	checkAndResetInput(flag);
}

/**
 * Fill arguments from user
 * @param args a struct args
 * @return true if the process succeeded, and false otherwise.
 */
bool fillArgsFromUser(Args *args)
{
	bool flag = true;

	getLongDouble(ENTER_POS_X, &args->x, &flag);
	getLongDouble(ENTER_POS_Y, &args->y, &flag);
	getLongDouble(ENTER_VEL_X, &args->vx, &flag);
	getLongDouble(ENTER_VEL_Y, &args->vy, &flag);
	getLongDouble(ENTER_TIME, &args->T, &flag);
	getUnsignedInteger(ENTER_STEPS, &args->n, &flag);
	getUnsignedInteger(ENTER_STEPS_TO_SAVE, &args->m, &flag);

	if (!flag)
	{
		cerr << INVALID_PARAMETER_FORMAT << endl;
		return false;
	}

	return true;
}

/**
 * Fill args struct
 * @param argc number of arguments given
 * @param argv an array of arguments
 * @param args a struct args.
 * @return true if the process succeeded, false otherwise.
 */
bool fillArgs(int argc, char **argv, Args *args)
{
	if (argc == 3)
	{
		const char *inputFileName = argv[1];

		return fillArgsFromFile(inputFileName, args);
	}
	else
	{
		return fillArgsFromUser(args);
	}
}

/**
 * The main method of the program. Creates output (and input) file, gets arguments from user
 * and computes arenstorf , and writes the points to the output file.
 * @param argc number of arguments
 * @param argv an array of strings (output / input file)
 * @return 1 if there was an error, 0 if there was not.
 */
int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 3)
	{
		cerr << INCORRECT_USAGE;
		return EXIT_FAILURE;
	}

	const char *outputFileName = argv[argc - 1];

	ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		cerr << OUTPUT_FILE_OPEN_ERROR << outputFileName << "\n";
		return EXIT_FAILURE;
	}

	// Sets output format

	outputFile << std::setprecision(3) << std::scientific;

	Args args;

	bool ok = fillArgs(argc, argv, &args);
	if (!ok)
	{
		return EXIT_FAILURE;
	}

	return runExercise(outputFile, args);
}


int runExercise(ofstream &outputFile, const Args &args)
{

	ArenstorfPoint init(args.x, args.y, args.vx, args.vy);

	int result = Arenstorf::computeArenstorf(
			init,
			args.n,
			args.m,
			args.T / args.n,
			outputFile);
	return result;
}

