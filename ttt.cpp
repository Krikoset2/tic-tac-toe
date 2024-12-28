#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void cs() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pb(const vector<vector<char>>& b) {
    cs();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char c = b[i][j];
            char n = '1' + i * 3 + j;
            if (c == 'X') {
                cout << "\033[32mX\033[0m";
            } else if (c == 'O') {
                cout << "\033[31mO\033[0m";
            } else {
                cout << "\033[90m" << n << "\033[0m";
            }
            if (j < 2) {
                cout << "\033[38;5;250m I \033[0m";
            }
        }
        cout << endl;
        if (i < 2) {
            cout << "\033[38;5;250m--+---+--\033[0m" << endl;
        }
    }
    cout << endl;
}

bool cw(const vector<vector<char>>& b, char p) {
    vector<vector<int>> wc = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}
    };
    for (auto& c : wc) {
        if (b[c[0] / 3][c[0] % 3] == p &&
            b[c[1] / 3][c[1] % 3] == p &&
            b[c[2] / 3][c[2] % 3] == p) {
            return true;
        }
    }
    return false;
}

bool ibf(const vector<vector<char>>& b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

vector<pair<int, int>> gec(const vector<vector<char>>& b) {
    vector<pair<int, int>> e;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ') {
                e.push_back({i, j});
            }
        }
    }
    return e;
}

int mm(vector<vector<char>>& b, int d, bool m) {
    if (cw(b, 'O')) return 1;
    if (cw(b, 'X')) return -1;
    if (ibf(b)) return 0;

    if (m) {
        int bs = -1000;
        for (auto& mv : gec(b)) {
            b[mv.first][mv.second] = 'O';
            int score = mm(b, d + 1, false);
            b[mv.first][mv.second] = ' ';
            bs = max(score, bs);
        }
        return bs;
    } else {
        int bs = 1000;
        for (auto& mv : gec(b)) {
            b[mv.first][mv.second] = 'X';
            int score = mm(b, d + 1, true);
            b[mv.first][mv.second] = ' ';
            bs = min(score, bs);
        }
        return bs;
    }
}

pair<int, int> cm(vector<vector<char>>& b) {
    int bs = -1000;
    pair<int, int> bm;
    for (auto& mv : gec(b)) {
        b[mv.first][mv.second] = 'O';
        int score = mm(b, 0, false);
        b[mv.first][mv.second] = ' ';
        if (score > bs) {
            bs = score;
            bm = mv;
        }
    }
    return bm;
}

pair<int, int> pm(vector<vector<char>>& b) {
    int mv;
    while (true) {
        cout << "\033[90mEnter your move (1-9): \033[0m";
        cin >> mv;
        mv--;
        int r = mv / 3;
        int c = mv % 3;
        if (mv >= 0 && mv <= 8 && b[r][c] == ' ') {
            return {r, c};
        }
        cout << "\033[31mInvalid move! Try again.\033[0m" << endl;
    }
}

void pg() {
    vector<vector<char>> b(3, vector<char>(3, ' '));
    cout << "\033[36mGame starting!\033[0m" << endl;
    pb(b);

    while (true) {
        cout << "\033[32mYour turn (X):\033[0m" << endl;
        auto [r, c] = pm(b);
        b[r][c] = 'X';
        pb(b);
        if (cw(b, 'X')) {
            cout << "\033[32mCongratulations! You win!\033[0m" << endl;
            break;
        }
        if (ibf(b)) {
            cout << "\033[90mIt's a tie!\033[0m" << endl;
            break;
        }

        cout << "\033[31mComputer's turn (O):\033[0m" << endl;
        auto [cr, cc] = cm(b);
        b[cr][cc] = 'O';
        pb(b);
        if (cw(b, 'O')) {
            cout << "\033[31mComputer wins!\033[0m" << endl;
            break;
        }
        if (ibf(b)) {
            cout << "\033[90mIt's a tie!\033[0m" << endl;
            break;
        }
    }

    char pa;
    cout << "\033[36mPlay again? (Y/N): \033[0m";
    cin >> pa;
    if (pa == 'Y' || pa == 'y') {
        pg();
    } else {
        cout << "\033[36mThanks for playing!\033[0m" << endl;
    }
}

int main() {
    cs();
    cout << "\033[36mWelcome to Tic Tac Toe!\033[0m" << endl;
    cout << "\033[32mYou are X\033[0m and \033[31mComputer is O\033[0m" << endl;
    pg();
    return 0;
}