#include <iostream>

using namespace std;
enum square_state {
    O, X, UNKNOWN
};

string to_string(square_state state) {
    switch(state) {
        case O:
            return "O";
        case X:
            return "X";
        case UNKNOWN:
            return "Unknown";
    }
}

class board {
    
    static const int SIZE = 3;
    
    square_state grid[SIZE][SIZE];

public:
    
    board() {
        for(int i = 0; i < SIZE; ++i) {
            for(int j = 0; j < SIZE; ++j) {
                grid[i][j] = UNKNOWN;
            }
        }
    }
    
    
    void print() {
        cout << " ";
        for(int x = 0; x < SIZE; x++)cout << x;
        cout << endl;
        
        for(int x = 0; x < SIZE; ++x) {
            cout << x;
            for(int y = 0; y < SIZE; ++y) {
                char s;
                switch(grid[x][y]) {
                    case O:
                        s = 'O';
                        break;
                    case X:
                        s = 'X';
                        break;
                    case UNKNOWN:
                        s = '.';
                        break;
                }
                cout << s;
            }
            cout << endl;
        }
    }
    
    
    bool set_state(int x, int y, square_state state) {
        if(x < 0 or x >= SIZE or y < 0 or y >= SIZE or grid[x][y] != UNKNOWN or state == UNKNOWN) {
            return false;
        }
        grid[x][y] = state;
        return true;
    }
    
    square_state get_winner() {
        static const int dx[] = {1, 0, -1, 1, 0, -1, 1, -1};
        static const int dy[] = {1, 1, 1, -1, -1, -1, 0, 0};
        
        for(int x = 0; x < SIZE; ++x) {
            for(int y = 0; y < SIZE; ++y) {
                if(grid[x][y] == UNKNOWN)continue;
                for(int dir = 0; dir < 8; dir++) {
                    bool ok = true;
                    for(int dis = 1; dis < 3; dis++) {
                        int newx = x + dx[dir] * dis, newy = y + dy[dir] * dis;
                        if(newx < 0 or newx >= SIZE or newy < 0 or newy >= SIZE or grid[newx][newy] != grid[x][y]) {
                            ok = false;
                            break;
                        }
                    }
                    if(ok)return grid[x][y];
                }
            }
        }
        return UNKNOWN;
    }
    
    bool is_tie() {
        for(int x = 0; x < SIZE; ++x) {
            for(int y = 0; y < SIZE; ++y) {
                if(grid[x][y] == UNKNOWN)return false;
            }
        }
        return true;
    }
};

int main() {
    board board;
    square_state current_player = O;
    while(true) {
        int x, y;
        cout << "------------------------------------------------------" << endl;
        board.print();
        cout << "Player " << to_string(current_player) << ":" << endl;
        cout << "Please input x and y coordinates to make a move: ";
        cin >> x >> y;
        if(!board.set_state(x, y, current_player)) {
            cout << "not valid move" << endl;
        } else {
            if(current_player == O)current_player = X;
            else current_player = O;
        }
        if(board.get_winner() != UNKNOWN) {
            cout << "------------------------------------------------------" << endl;
            board.print();
            cout << to_string(board.get_winner()) << " is the winner!" << endl;
            break;
        } else if(board.is_tie()) {
            cout << "------------------------------------------------------" << endl;
            board.print();
            cout << "There is no winner!" << endl;
            break;
        }
    }
    
    return 0;
}
