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


int main() {
    displayWelcomeMsg();
    
    //  get the file from the user
    string file = getFileName();

    //  open the file
    ifstream inputStream;
    inputStream.open(file);

    //  get the row and column number from the file
    int numGridRow;
    int numGridCol;

    getRowAndColSize(file, numGridRow, numGridCol);

    cout << "the num of grid row is: " << numGridRow << endl;
    cout << "the num of grid col is: " << numGridCol << endl;


    return 0;
}
