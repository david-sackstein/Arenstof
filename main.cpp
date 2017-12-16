#include <iostream>
#include <fstream>
#include <cmath>
#include "Arenstof.h"

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

bool FillArgsFromFile(const char* fileName, Args* args)
{
	std::ifstream inputFile(fileName);

	if (! inputFile.is_open())
	{
		std::cerr << "Failed to open input file " << fileName << "\n";
		return false;
	}

	std::string line1;
	std::string line2;

	getline(inputFile, line1);
	getline(inputFile, line2);

	sscanf(line1.c_str(), "%Le, %Le, %Le, %Le", &args->x, &args->y, &args->vx, &args->vy);
	sscanf(line2.c_str(), "%Le, %u, %u", &args->T, &args->n, &args->m);

	return true;
}

bool FillArgsFromUser(Args* args)
{
	std::cout << "Enter initial pos x:\n";
	std::cin >> args->x;

	std::cout << "Enter initial pos y:\n";
	std::cin >> args->y;

	std::cout << "Enter initial vel x:\n";
	std::cin >> args->vx;

	std::cout << "Enter initial vel y:\n";
	std::cin >> args->vy;

	std::cout << "Enter total time T:\n";
	std::cin >> args->T;

	std::cout << "Enter num of steps:\n";
	std::cin >> args->n;

	std::cout << "Enter num of steps to save:\n";
	std::cin >> args->m;

	return true;
}

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

    ArenstofPoint init (args.x, args.y, args.vx, args.vy);

    Arenstof arenstof(init, args.n, args.T/args.n);

    ArenstofPoint* points = new ArenstofPoint[args.m];

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
		std::cerr << "Incorrect usage\n";
		return EXIT_FAILURE;
	}

	const char* outputFileName = argv[argc-1];

	std::ofstream outputFile(outputFileName);
	if (! outputFile.is_open())
	{
		std::cerr << "Failed to open output file " << outputFileName << "\n";
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

int RunExercise(std::ofstream &outputFile, const Args &args) {
    ArenstofPoint init (args.x, args.y, args.vx, args.vy);

    int result = Arenstof::computeArenstof(
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
        std::cout << "PASSED\n";
        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "FAILED\n";
        return EXIT_FAILURE;
    }
}