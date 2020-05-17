#include <iostream>

#include "itask.h"
#include "tester.h"

#include "king.h"
#include "knight.h"
#include "fen.h"
#include "truckdrivers.h"

using namespace std;
namespace fs = std::experimental::filesystem;

int main()
{
    King king;
    Tester testerKing(&king, "1. King", fs::current_path().string() + "\\1.Bitboard");
    testerKing.RunTasks();

    Knight knight;
    Tester testerKnight(&knight, "2. Knight", fs::current_path().string() + "\\2.Bitboard");
    testerKnight.RunTasks();

    FEN fen;
    Tester testerFEN(&fen, "3. FEN", fs::current_path().string() + "\\3.Bitboard");
    testerFEN.RunTasks();

    TruckDrivers truckDrivers;
    Tester testerTruckDrivers(&truckDrivers, "4. TruckDrivers", fs::current_path().string() + "\\4.Bitboard");
    testerTruckDrivers.RunTasks();

    return 0;
}

