#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h>
using namespace std;

class Shape {
public:
    int posX;
    int posY;
    vector<vector<string>> shape;
    virtual ~Shape() {}
};

class Board {
public:
    vector<vector<string>> board;
public:
    Board();
    void DrawBoard(const Shape&);
};

// 2x2 shape
class Square : public Shape {
public:
    Square();
    void DrawSquare();
    void ControlSquare();
};

Square::Square() {
    this->posX = 0;
    this->posY = 0;
    this->shape = vector<vector<string>>(2, vector<string>(2, " "));

    // assign * to represent shape
    this->shape[this->posY][this->posX] = "*";
    this->shape[this->posY][this->posX + 1] = "*";
    this->shape[this->posY + 1][this->posX] = "*";
    this->shape[this->posY + 1][this->posX + 1] = "*";
}

void Square::DrawSquare() {
    for (int i = 0; i < this->shape.size(); i++) {
        for (int j = 0; j < this->shape[i].size(); j++) {
            cout << this->shape[i][j];
        }
        cout << endl;
    }
}

void Square::ControlSquare() {

}

Board::Board() {
    this->board = vector<vector<string>>(20, vector<string>(10, "[ ]"));
}

void Board::DrawBoard(const Shape& s) {
    system("cls");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            bool drawn = false;
            for (int si = 0; si < s.shape.size(); si++) {
                for (int sj = 0; sj < s.shape[si].size(); sj++) {
                    if (s.shape[si][sj] == "*" &&
                        i == s.posY + si &&
                        j == s.posX + sj) {
                        cout << "[*]";
                        drawn = true;
                        break;
                    }
                }
                if (drawn) break;
            }
            if (!drawn) {
                cout << board[i][j];
            }
        }
        cout << endl;
    }
}

int main()
{
    Board B1;
    Square S1;
    while (true) {
        if (_kbhit()) {
            char key = _getch();

            switch (key) {
            case 's':
            case 'S':
                if (S1.posY < 18) S1.posY++;
                break;
            
            case 'a':
            case 'A':
                if (S1.posX > 0) S1.posX--;
                break;

            case 'd':
            case 'D':
                if (S1.posX < 8) S1.posX++;
                break;

            case 'q':
            case 'Q':
                return 0; // quit game
            }
        }

        B1.DrawBoard(S1);
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}