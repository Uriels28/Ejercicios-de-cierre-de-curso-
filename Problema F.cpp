#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct Grid {
    vector<string> cells;
    int h, w;

    Grid(vector<string> cells) : cells(cells), h(cells.size()), w(cells[0].size()) {}

    bool operator==(const Grid &other) const {
        return cells == other.cells;
    }

    bool operator!=(const Grid &other) const {
        return cells != other.cells;
    }

    string toString() const {
        string result;
        for (const auto &row : cells) {
            result += row + '\n';
        }
        return result;
    }

    void tiltLeft() {
        for (int i = 0; i < h; ++i) {
            int fillPosition = 0;
            for (int j = 0; j < w; ++j) {
                if (cells[i][j] != '.') {
                    if (fillPosition != j) {
                        swap(cells[i][fillPosition], cells[i][j]);
                    }
                    fillPosition++;
                }
            }
        }
    }

    void tiltRight() {
        for (int i = 0; i < h; ++i) {
            int fillPosition = w - 1;
            for (int j = w - 1; j >= 0; --j) {
                if (cells[i][j] != '.') {
                    if (fillPosition != j) {
                        swap(cells[i][fillPosition], cells[i][j]);
                    }
                    fillPosition--;
                }
            }
        }
    }

    void tiltUp() {
        for (int j = 0; j < w; ++j) {
            int fillPosition = 0;
            for (int i = 0; i < h; ++i) {
                if (cells[i][j] != '.') {
                    if (fillPosition != i) {
                        swap(cells[fillPosition][j], cells[i][j]);
                    }
                    fillPosition++;
                }
            }
        }
    }

    void tiltDown() {
        for (int j = 0; j < w; ++j) {
            int fillPosition = h - 1;
            for (int i = h - 1; i >= 0; --i) {
                if (cells[i][j] != '.') {
                    if (fillPosition != i) {
                        swap(cells[fillPosition][j], cells[i][j]);
                    }
                    fillPosition--;
                }
            }
        }
    }

    vector<Grid> getNextStates() {
        vector<Grid> nextStates;
        Grid temp = *this;

        temp.tiltLeft();
        nextStates.push_back(temp);
        temp = *this;

        temp.tiltRight();
        nextStates.push_back(temp);
        temp = *this;

        temp.tiltUp();
        nextStates.push_back(temp);
        temp = *this;

        temp.tiltDown();
        nextStates.push_back(temp);

        return nextStates;
    }
};

bool bfs(const Grid &start, const Grid &goal) {
    queue<Grid> q;
    unordered_set<string> visited;

    q.push(start);
    visited.insert(start.toString());

    while (!q.empty()) {
        Grid current = q.front();
        q.pop();

        if (current == goal) {
            return true;
        }

        for (Grid nextState : current.getNextStates()) {
            string stateString = nextState.toString();
            if (visited.find(stateString) == visited.end()) {
                q.push(nextState);
                visited.insert(stateString);
            }
        }
    }

    return false;
}

int main() {
    int h, w;
    cin >> h >> w;
    cin.ignore();

    vector<string> initialCells(h);
    for (int i = 0; i < h; ++i) {
        getline(cin, initialCells[i]);
    }

    string blankLine;
    getline(cin, blankLine);  // Leer la línea en blanco

    vector<string> finalCells(h);
    for (int i = 0; i < h; ++i) {
        getline(cin, finalCells[i]);
    }

    Grid initialGrid(initialCells);
    Grid finalGrid(finalCells);

    if (bfs(initialGrid, finalGrid)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
