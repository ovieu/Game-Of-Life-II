// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
using namespace std;


void displayWelcomeMsg() {
    cout << "Welcome to the game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells live and die by the following rules:" << endl << endl;
    cout << "\t - A cell with 1 or fewer neighbors dies of loneliness" << endl;
    cout << "\t - Locations with 2 neighbors remain stable" << endl;
    cout << "\t - Locations with 3 neighbors will spontaneously create life" << endl;
    cout << "\t - Locations with 4 or more neighbors die of overcrowding" << endl << endl;
    cout << " " << endl;
}

static string getFileName() {
    string filename;
    while(true) {
        filename = getLine("Grid input file name? ");
        if (fileExists(filename)) {
            return filename;
        }
        cout << "File does not exist" << endl;
    }
}

/** Obtain the row and column of the grid row from the file
 * @brief getRowAndColSize
 * @param numGridRow the number of rows in the bacteria grid
 * @param numGridCol the number of columns in the bacteria grid
 */
static void getRowAndColSize(string fileName, int& numGridRow, int& numGridCol) {
    //  open file
    ifstream inputStream;
    inputStream.open(fileName);

    //  read first line and set to row
    int lineCounter = 0;
    string line;
    while(getline(inputStream, line)) {
        if (lineCounter < 1) {
            numGridRow = stringToInteger(line);
            lineCounter++;
        }

        if (lineCounter >= 1) {
            numGridCol = stringToInteger(line);
            lineCounter++;
        }

        if (lineCounter > 2) break;
    }

    inputStream.close();
}

static void updateBacteriaColony(string line,
                                 Grid<char>& bacteriaGrid,
                                 int currentGridRow,
                                 int numGridCol) {
    for(int i = 0; i < numGridCol; i++) {
        bacteriaGrid.set(currentGridRow,i, line.at(i));
    }
}


/**
 *
 * @brief createBacteriaColony  creates a pattern from the input grid file,
 * updates the original bacteria colony
 * @param bacteriaGrid the grid to be updated with the pattern from file
 * @param fileName the source file for bacteria colonization
 */
static void createColonyFromFilePattern(Grid<char>& bacteriaGrid,
                                 string fileName,
                                 int numGridRows,
                                 int numGridCol) {
    //open the file
    ifstream inputStream;
    inputStream.open(fileName);

    int inputFileLineNumber = 0;

    string line;
    //  start reading from the third line
    //  update the grid number
    int currentGridRow = 0;

    while(getline(inputStream, line)) {
        if (inputFileLineNumber >=2) {
            if (inputFileLineNumber < (numGridRows + 2)) {
                string bacteriaRowPattern = line;
                //
                //  simp cout << line << endl;
                //
                updateBacteriaColony(bacteriaRowPattern, bacteriaGrid,
                                     currentGridRow, numGridCol);
                currentGridRow++;
            }
        }
        inputFileLineNumber++;
    }
    inputStream.close();

    //  check the grid to see the output here
    bacteriaGrid.toString();
}

static void gridDisplay(const Grid<char>& bacteriaGrid) {
    for(int i = 0; i < bacteriaGrid.nRows; i++) {
        for(int j = 0; j < bacteriaGrid.nCols; j++) {
            cout << bacteriaGrid.get(i, j);
        }
        cout << endl;
    }
}

int main() {
    displayWelcomeMsg();

    //  get the file from the user
    string file = getFileName();

//    //  open the file
//    ifstream inputStream;
//    inputStream.open(file);

    //  get the row and column number from the file
    int numGridRow;
    int numGridCol;

    getRowAndColSize(file, numGridRow, numGridCol);

    cout << "the num of grid row is: " << numGridRow << endl;
    cout << "the num of grid col is: " << numGridCol << endl;

    //  create the bacteria grid
    Grid<char> bacteriaGrid(numGridRow, numGridCol);

    //  insert grid pattern from file into grid
    createColonyFromFilePattern(bacteriaGrid, file, numGridRow, numGridCol);

    //  test using grid display
    gridDisplay(bacteriaGrid);

    return 0;
}
