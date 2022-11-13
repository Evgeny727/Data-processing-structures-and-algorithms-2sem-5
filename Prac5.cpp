#include <iostream>
#include <fstream>
#include <queue>
#include "BinFile.h"
#include "BinSearchTree.h"
#include "SplaySearchTree.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    testBinTask();
    binSearchTreeTest();
    splaySearchTreeTest();
    return 0;
}