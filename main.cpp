#include <iostream>
#include <fstream>
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

    int result = Arenstof::computeArenstof(
        ArenstofPoint(args.x, args.y, args.vx, args.vy),
        args.n,
		args.m,
		args.T / args.n,
		outputFile);

	return 0;
}