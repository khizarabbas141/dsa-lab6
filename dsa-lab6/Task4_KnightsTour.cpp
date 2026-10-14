#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int N;
int board[15][15];
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isValid(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N && board[r][c] == -1;
}

int countMoves(int r, int c) {
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        if (isValid(r + dx[i], c + dy[i]))
            cnt++;
    }
    return cnt;
}

bool solveKnightTour(int row, int col, int moveNumber) {
    if (moveNumber == N * N)
        return true;

    int nr[8], nc[8], deg[8];
    int total = 0;

    for (int i = 0; i < 8; i++) {
        int r = row + dx[i];
        int c = col + dy[i];
        if (isValid(r, c)) {
            nr[total] = r;
            nc[total] = c;
            deg[total] = countMoves(r, c);
            total++;
        }
    }

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (deg[j] > deg[j + 1]) {
                swap(deg[j], deg[j + 1]);
                swap(nr[j], nr[j + 1]);
                swap(nc[j], nc[j + 1]);
            }
        }
    }

    for (int i = 0; i < total; i++) {
        board[nr[i]][nc[i]] = moveNumber + 1;
        if (solveKnightTour(nr[i], nc[i], moveNumber + 1))
            return true;
        board[nr[i]][nc[i]] = -1;
    }

    return false;
}

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(4) << board[i][j];
        cout << endl;
    }
}

int main() {
    int x, y;

    cout << "Enter board size N: ";
    cin >> N;
    cout << "Enter starting row and column: ";
    cin >> x >> y;

    if (N < 1 || N > 15 || x < 0 || x >= N || y < 0 || y >= N) {
        cout << "Invalid input." << endl;
        return 0;
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    board[x][y] = 1;

    if (solveKnightTour(x, y, 1)) {
        cout << "Tour found:" << endl;
        printBoard();
    } else {
        cout << "No tour was found for this board and starting position." << endl;
    }

    return 0;
}
