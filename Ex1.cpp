#include "Arenstorf.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

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

struct Args {
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
bool fillArgsFromFile(const char *fileName, Args *args) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cerr << INPUT_FILE_OPEN_ERROR << fileName << "\n";
        return false;
    }

    string comma;

    inputFile >> args->x >> comma >> args->y >> comma >> args->vx >> comma >> args->vy;
    inputFile >> args->T >> comma >> args->n >> comma >> args->m;

    if (inputFile.fail()) {
        cerr << INVALID_FILE_FORMAT << endl;

        return false;
    }

    return true;
}

bool getLongDouble(const char *message, long double *value) {
    cout << message;
    cin >> *value;
    if (cin.fail()) {
        cerr << INVALID_PARAMETER_FORMAT << endl;
        return false;
    }
    return true;
}

bool getUnsignedInteger(const char *message, unsigned int *value) {
    cout << message;
    cin >> *value;
    if (cin.fail()) {
        cerr << INVALID_PARAMETER_FORMAT << endl;
        return false;
    }
    return true;
}

bool checkArgs(const Args& args) {
    bool ok =
        args.n % args.m == 0 &&
        args.T >= 0;

    if (! ok){
        cerr << "The time must be non-negative and m must divide n" << endl;
    }

    return ok;
}

/**
 * fill arguments from user
 * @param args a struct args
 * @return true if the process succeeded, and false otherwise.
 */
bool fillArgsFromUser(Args *args) {

    return
        getLongDouble(ENTER_POS_X, &args->x) &&
        getLongDouble(ENTER_POS_Y, &args->y) &&
        getLongDouble(ENTER_VEL_X, &args->vx) &&
        getLongDouble(ENTER_VEL_Y, &args->vy) &&
        getLongDouble(ENTER_TIME, &args->T) &&
        getUnsignedInteger(ENTER_STEPS, &args->n) &&
        getUnsignedInteger(ENTER_STEPS_TO_SAVE, &args->m);
}

/**
 * fill argument array
 * @param argc number of arguments given
 * @param argv an array of arguments
 * @param args a struct args.
 * @return true if the process succeeded, false otherwise.
 */
bool FillArgs(int argc, char *argv[], Args *args) {
    if (argc == 3) {
        const char *inputFileName = argv[1];

        return fillArgsFromFile(inputFileName, args);
    } else {
        return fillArgsFromUser(args);
    }
}

const long double epsilon = 11;

long double distance(long double lhs, long double rhs) {
    //return fabs(1 - (lhs / rhs));
    return fabs(lhs - rhs);
}

bool isDoubleEqual(long double lhs, long double rhs) {
    return distance(lhs, rhs) < epsilon;
}

bool Test(const Args &args) {
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
            8.672e+05, 1.709e+06
    };

    ArenstorfPoint init(args.x, args.y, args.vx, args.vy);

    Arenstorf arenstof(init, args.n, args.T / args.n);

    ArenstorfPoint *points = new ArenstorfPoint[args.m];

    arenstof.computePoints(points, args.m);

    for (unsigned int i = 0; i < args.m; i++) {

        long double dx = distance(points[i].getX(), expectedPoints[i * 2]);
        long double dy = distance(points[i].getY(), expectedPoints[i * 2 + 1]);

        cout << std::setprecision(3) << std::scientific << points[i].getX() << "\t" << points[i].getY() << endl;

//        if (!isDoubleEqual(points[i].getX(), expectedPoints[i * 2]) ||
//            !isDoubleEqual(points[i].getY(), expectedPoints[i * 2 + 1])) {
//            return false;
//        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << INCORRECT_USAGE;
        return EXIT_FAILURE;
    }

    const char *outputFileName = argv[argc - 1];

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << OUTPUT_FILE_OPEN_ERROR << outputFileName << "\n";
        return EXIT_FAILURE;
    }

    // Sets output format

    outputFile << std::setprecision(3) << std::scientific;

    Args args;

    bool ok = FillArgs(argc, argv, &args);
    if (!ok) {
        return EXIT_FAILURE;
    }

    if (!checkArgs(args)) {
        return EXIT_FAILURE;
    }

    //return RunTest(args);

    return RunExercise(outputFile, args);
}

int RunExercise(ofstream &outputFile, const Args &args) {

    ArenstorfPoint init(args.x, args.y, args.vx, args.vy);

    int result = Arenstorf::computeArenstorf(
            init,
            args.n,
            args.m,
            args.T / args.n,
            outputFile);
    return result;
}

int RunTest(const Args &args) {
    bool ok = Test(args);
    if (ok) {
        cout << "PASSED\n";
        return EXIT_SUCCESS;
    } else {
        cout << "FAILED\n";
        return EXIT_FAILURE;
    }
}