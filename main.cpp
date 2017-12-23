#include <iostream>
#include <fstream>
#include <cmath>
#include "Arenstorf.h"



using namespace std;


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

int RunTest(const Args &args);

int RunExercise(std::ofstream &outputFile, const Args &args);

/**
 * fill arguments from input file
 * @param fileName the name of the input file
 * @param args a struct args
 * @return true if the process succeeded, and false otherwise.
 */
bool FillArgsFromFile(const char* fileName, Args* args)
{
	ifstream inputFile(fileName);

	if (! inputFile.is_open())
	{
		cerr << "Failed to open input file " << fileName << "\n";
		return false;
	}

	string line1;
	string line2;

	getline(inputFile, line1);
	getline(inputFile, line2);

	sscanf(line1.c_str(), "%Le, %Le, %Le, %Le", &args->x, &args->y, &args->vx, &args->vy);
	sscanf(line2.c_str(), "%Le, %u, %u", &args->T, &args->n, &args->m);

	return true;
}

/**
 * fill arguments from user
 * @param args a struct args
 * @return true if the process succeeded, and false otherwise.
 */
bool FillArgsFromUser(Args* args)
{
	cout << "Enter initial pos x:\n";
	cin >> args->x;

	cout << "Enter initial pos y:\n";
	cin >> args->y;

	cout << "Enter initial vel x:\n";
	cin >> args->vx;

	cout << "Enter initial vel y:\n";
	cin >> args->vy;

	cout << "Enter total time T:\n";
	cin >> args->T;

	cout << "Enter num of steps:\n";
	cin >> args->n;

	cout << "Enter num of steps to save:\n";
	cin >> args->m;

	return true;
}

/**
 * fill argument array
 * @param argc number of arguments given
 * @param argv an array of arguments
 * @param args a struct args.
 * @return true if the process succeeded, false otherwise.
 */
bool FillArgs(int argc, char* argv[], Args* args)
{
	if (argc == 3)
	{
		const char* inputFileName = argv[1];

		return FillArgsFromFile (inputFileName, args);
	}
	else
	{
		return FillArgsFromUser (args);
	}
}

const long double epsilon = 0.001;

bool isDoubleEqual(long double lhs, long double rhs)
{
    return fabs(1 - (lhs / rhs)) < epsilon;
}

bool Test(const Args& args)
{
    long double expectedPoints[] = {
            9.940e-01, -3.416e+00,
            -9.133e+02, -6.831e+00,
            -1.836e+03, 3.101e+03,
            5.186e+03, 9.339e+03,
            2.815e+04, 6.373e+02,
            3.652e+04, -5.925e+04,
            -7.752e+04, -1.459e+05,
            -3.808e+05, -1.577e+04,
            -4.658e+05, 7.246e+05,
            8.672e+05, 1.709e+06};

    ArenstorfPoint init (args.x, args.y, args.vx, args.vy);

    Arenstorf arenstof(init, args.n, args.T/args.n);

    ArenstorfPoint* points = new ArenstorfPoint[args.m];

    arenstof.computePoints(points, args.m);

    for (unsigned int i = 0; i<args.m; i++)
    {
        if (! isDoubleEqual(points[i].getX(), expectedPoints[i * 2]) ||
            ! isDoubleEqual(points[i].getY(), expectedPoints[i * 2 + 1]))
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 3)
	{
		cerr << "Incorrect usage\n";
		return EXIT_FAILURE;
	}

	const char* outputFileName = argv[argc-1];

	ofstream outputFile(outputFileName);
	if (! outputFile.is_open())
	{
		cerr << "Failed to open output file " << outputFileName << "\n";
		return EXIT_FAILURE;
	}

	Args args;

	bool ok = FillArgs(argc, argv, &args);
	if (! ok)
	{
		return EXIT_FAILURE;
	}

    //return RunTest(args);

    return RunExercise(outputFile, args);
}

int RunExercise(ofstream &outputFile, const Args &args) {

	ArenstorfPoint init (args.x, args.y, args.vx, args.vy);

    int result = Arenstorf::computeArenstof(
        init,
        args.n,
		args.m,
		args.T / args.n,
		outputFile);
    return result;
}

int RunTest(const Args &args) {
    bool ok = Test(args);
    if (ok)
    {
        cout << "PASSED\n";
        return EXIT_SUCCESS;
    }
    else
    {
        cout << "FAILED\n";
        return EXIT_FAILURE;
    }
}