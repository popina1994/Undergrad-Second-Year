#include <iostream>
#include <pthread.h>
#include <bitset>

using namespace std;

constexpr int SIZE = 9, THREADS = 11, SQUARES = 9, SIZE_SQUARE = 3;

struct Position{
    int row, col;
    constexpr Position(int _row, int _col) : row(_row), col(_col) {}
};

class Sudoku {
    static int x[SIZE][SIZE];
    static bitset<THREADS> sudokuRegular;

public:
    enum THREAD { RAW = 0, COL, SQUARE };
    static void* CheckRaw(void* arg) {
        for (int row = 0; row < SIZE; row ++) {
            bitset <SIZE> regular;
            for (int col = 0; col < SIZE; col++)
                regular.set(x[row][col] - 1);
            if (!regular.all())
                return nullptr;
        }
        sudokuRegular.set(RAW);
        pthread_exit(nullptr);
    }

    static void* CheckCol(void* arg) {
        for (int col = 0; col < SIZE; col ++) {
            bitset <SIZE> regular;
            for (int row = 0; row < SIZE; row++)
                regular.set(x[row][col] - 1);
            if (!regular.all())
                return nullptr;
        }
        sudokuRegular.set(COL);
        pthread_exit(nullptr);
    }

    static void* CheckSquare(void* arg) {
        Position* pos = (Position*)arg;
        bitset <SIZE> regular;

        for (int row = pos->row; row < SIZE_SQUARE + pos->row; row ++)
            for (int col = pos->col; col < SIZE_SQUARE + pos->col; col ++)
                regular.set(x[row][col] - 1);
        if (!regular.all())
            return nullptr;
        sudokuRegular.set(SQUARE + pos->row + pos->col / 3);
        pthread_exit(nullptr);
    }

    static bool CheckSudoku() {
        return sudokuRegular.all();
    }
};

int Sudoku::x[SIZE][SIZE] = { {6, 2, 4, 5, 3, 9 , 1, 8, 7} , {5, 1, 9, 7, 2, 8, 6, 3, 4}, {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9}, {9, 5, 8, 2, 4, 7, 3, 6, 1}, {7, 6, 2, 3, 9, 1, 4, 5, 8}, {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3}, {2, 8, 5, 4, 7, 3, 9, 1, 6}};

bitset<THREADS> Sudoku::sudokuRegular;

using PtFunction = void*(*) (void*);

constexpr PtFunction function[THREADS] = {Sudoku::CheckRaw, Sudoku::CheckCol, Sudoku::CheckSquare};
Position square[SQUARES] = { Position(0, 0), Position(0, 3), Position(0, 6), Position(3, 0), Position(3, 3), Position(3, 6),
    Position(6, 0), Position(6, 3), Position(6, 6)};

int main() {
    pthread_attr_t defAttr;
    pthread_attr_init(&defAttr);

    for (int cnt = 0; cnt < THREADS; cnt ++) {
        pthread_t tId;
        if (cnt < Sudoku::SQUARE)
            pthread_create(&tId, &defAttr, function[cnt], nullptr);
        else
            pthread_create(&tId, &defAttr, function[Sudoku::SQUARE], &square[cnt - Sudoku::SQUARE]);
        pthread_join(tId, nullptr);
    }
    if (Sudoku::CheckSudoku())
        cout << "Sudoku is regular" << endl;
    else
        cout << "Sudoku is not regular" << endl;
    return 0;
}
