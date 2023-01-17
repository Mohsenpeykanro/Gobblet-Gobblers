/*
University project, Gobblet Gobblers game!

Winner :
If u want to win you have to line up 3 of your Gobblers in a row to win !!

Equipment :
Each player have 6 pieces called "Gobblers"
2 Small Gobblers
2 Medium Gobblers
2 Big Gobblers
Just remember !
Small(1) < Medium(2) < Big(3)

Rules :
U can put ur Gobblers on an empty space or over a small Gobbler
and beside that u can move your Gobbler on the Board !

HAVE FUN !!!!
*/

#include <iostream>
using namespace std;

// Objects --> Players :
struct Player {
    char ColorMark;
    string Color;
    int pieces[3] = {2, 2, 2};
};

// Global Variables
Player Players[2];
string Board[3][3];

// Functions Code Block:
void GameplayPieceChecker(int);

//*********************************************************************
void clear () {
    system("clear");
}

//*********************************************************************
int InputMessage (string message = ">>") {
    cout << message << " ";
    int a;
    cin >> a;
    return a;
}

//*********************************************************************
string ToUpper (string Text) {
    for (int i = 0; i < Text.length(); i++) {
        Text[i] = toupper(Text[i]);
    }
    return Text;
}

//*********************************************************************
void BoardInformation () {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Board[i][j] = "";
        }
    }
}

//*********************************************************************
void PlayersInformation () {
    Players[0].ColorMark = 'B'; Players[0].Color = "BLUE";
    Players[1].ColorMark = 'R'; Players[1].Color = "RED";
}

//*********************************************************************
void Table () {
    clear();
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            string Piece = Board[i][j];
            if (Piece.length() >= 2) {
                cout << Piece.substr(Piece.length() - 2, 2);
            } else {
                cout << "  ";
            }
            cout << " | ";
        }
        cout << endl;
        if (i != 2) {
            for (int a = 0; a < 16; a++) {
                if (a % 5 == 0) {

                    cout << "|";
                } else {
                    cout << "-";
                }
            }
            cout << endl;
        }
    }
}

//*********************************************************************
char WinCondition () {
    string top_board[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Board[i][j].length() < 2) {
                top_board[i][j] = "  ";
            } else {
                top_board[i][j] = Board[i][j].substr(Board[i][j].length() - 2, 2);
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (top_board[i][0][0] == top_board[i][1][0] && top_board[i][1][0] == top_board[i][2][0]) {
            if (top_board[i][0][0] != ' ') {
                return top_board[i][0][0];
            }
        }
    }
    for (int j = 0; j < 3; j++) {
        if (top_board[0][j][0] == top_board[1][j][0] && top_board[1][j][0] == top_board[2][j][0]) {
            if (top_board[0][j][0] != ' ') {
                return top_board[0][j][0];
            }
        }
    }
    if (top_board[0][0][0] == top_board[1][1][0] && top_board[1][1][0] == top_board[2][2][0]) {
        if (top_board[0][0][0] != ' ') {
            return top_board[0][0][0];
        }
    }
    if (top_board[0][2][0] == top_board[1][1][0] && top_board[1][1][0] == top_board[2][0][0]) {
        if (top_board[0][2][0] != ' ') {
            return top_board[0][2][0];
        }
    }

    return ' ';
}

//*********************************************************************
void Gameplay (int player = 0) {
    int Row = -1;
    int Column = -1;
    string Piece = "";
    int Choice = 0;

    while (true) {
        back:
        cout << "**********************************" <<endl;
        Row = InputMessage("Which row you want to play? ") - 1;
        Column = InputMessage("Which column ? ") - 1;

        if (Row < 0 || Row > 2 || Column < 0 || Column > 2) {
            cout << "Out of range! Try again." << endl;
            continue;
        }

        string StringPiece = Board[Row][Column];
        int SizeOfPieces = 0;

        if (StringPiece.length() >= 2) {
            SizeOfPieces = StringPiece[StringPiece.length() - 1] - '0';
        }

        if (SizeOfPieces > 2) {
            cout << "This cell is unusable :( " << endl;
        } else {
            break;
        }

        cin.ignore();
    }

    while (true) {
        cin.ignore();
        cout << "What piece u going to play? ";
        cin >> Piece;
        Piece = ToUpper(Piece);

        if (Piece.length() != 2) {
            cout << "U can't use your piece here :(" << endl;
            goto back;
        }

        Choice = Piece[1] - '0';

        if (Piece[0] != Players[player].ColorMark || Choice < 1 || Choice > 3) {
            cout << "U can't use your piece here :(" << endl;
            goto back;
        }

        if (Players[player].pieces[Choice - 1] < 1) {
            cout << "U already played that piece!" << endl;
            continue;
        }

        string pieces = Board[Row][Column];
        int SizeOfPieces = 0;

        if (pieces.length() >= 2) {
            SizeOfPieces = pieces[pieces.length() - 1] - '0';
        }

        if (Choice <= SizeOfPieces) {
            cout << "that piece don't have enough power :( try something else." << endl;
            continue;
        }

        break;
    }

    Board[Row][Column] += Piece;

    Players[player].pieces[Choice - 1]--;

    Table();
    if (player == 0) {
        GameplayPieceChecker(1);
    } else {
        GameplayPieceChecker(0);
    }
}

//*********************************************************************
void GameplayRowColumnChecker (int player = 0) {
    int OrgRow = -1;
    int OrgColumn = -1;
    int ChangedToRow = -1;
    int ChangedToColumn = -1;
    int Source = 0;

    while (true) {
        OrgRow = InputMessage("which row u want to change? ") - 1;
        OrgColumn = InputMessage("what column? ") - 1;

        if (OrgRow < 0 || OrgRow > 2 || OrgColumn < 0 || OrgColumn > 2) {
            cout << "Out of range! Try again." << endl;
            continue;
        }

        string Piece = Board[OrgRow][OrgColumn];

        if (Piece.length() < 2) {
            cout << "cell is empty :/" << endl;
            continue;
        }

        Source = Piece[Piece.length() - 1] - '0';

        if (Piece[Piece.length() - 2] != Players[player].ColorMark) {
            cout << "that's not yours u cheater!" << endl;
            continue;
        }

        bool Proper = false;

        for (auto & i : Board) {
            for (auto & j : i) {
                int size = 0;
                if (j.length() >= 2) {
                    size = j[-1] - '0';
                }
                if (size < Source) {
                    Proper = true;
                    break;
                }
            }
            if (Proper) {
                break;
            }
        }

        if (!Proper) {
            continue;
        }

        break;
    }

    while (true) {
        ChangedToRow = InputMessage("Which row should i put this ?") - 1;
        ChangedToColumn = InputMessage("What column? ") - 1;

        if (ChangedToRow < 0 || ChangedToRow > 2 || ChangedToColumn < 0 || ChangedToColumn > 2) {
            cout << "Out of range! Try again." << endl;
            continue;
        }

        string Piece = Board[ChangedToRow][ChangedToColumn];

        int size_of_target = 0;

        if (Piece.length() >= 2) {
            size_of_target = Piece[Piece.length() - 1] - '0';
        }

        if (Source <= size_of_target) {
            cout << "that piece don't have enough power :( try something else." << endl;
            continue;
        }

        break;
    }

    string SourcePiece = Board[OrgRow][OrgColumn];
    string Piece = SourcePiece.substr(SourcePiece.length() - 2, 2);
    Board[OrgRow][OrgColumn] = SourcePiece.substr(0, SourcePiece.length() - 2);

    string target_pieces = Board[ChangedToRow][ChangedToColumn];
    Board[ChangedToRow][ChangedToColumn] = target_pieces.substr(0, target_pieces.length() - 2);
    Board[ChangedToRow][ChangedToColumn] += Piece;

    Table();
    if (player == 0) {
        GameplayPieceChecker(1);
    } else {
        GameplayPieceChecker(0);
    }
}

//*********************************************************************
void Winner (char winner) {
    Table();

    cout << endl;

    Player player;
    for (auto & i : Players) {
        if (i.ColorMark == winner) {
            player = i;
            break;
        }
    }
    cout << "Winner Winner ,Chicken Dinner !"<< endl;
    cout << player.Color << " Won the War!!!!!." << endl;

    cout << endl;
}

//*********************************************************************
void GameplayPieceChecker (int player = 0) {

    char result = WinCondition();
    if (result != ' ') {
        Winner(result);
        return;
    }

    cout << "It's " << Players[player].Color << " turn." << endl;
    int NumPieces = 0;
    for (int i = 0; i < 3; i++) {
        NumPieces += Players[player].pieces[i];
    }
    if (NumPieces != 0) {
        cout << "And they are ur warriors(Piece) : " << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < Players[player].pieces[i]; j++) {
                cout << Players[player].ColorMark << i + 1 << " ";
            }
        }
        cout << endl;

        if (NumPieces < 6) {
            cout << "*************************************************"<< endl;
            cout << "These Are Your Plan Commander !" << endl;
            cout << "1- Play new Piece." << endl;
            cout << "2- Change place of the piece u already played." << endl;
            while (true) {
                int choice = InputMessage("Which Plan you going to play?");
                if (choice == 1) {
                    Gameplay(player);
                    break;
                } else if (choice == 2) {
                    GameplayRowColumnChecker(player);
                    break;
                } else {
                    cout << "We don't have that plan :/" << endl;
                }
            }
        } else {
            Gameplay(player);
        }
    } else {
        cout << ",you don't have any soldier !" << endl;
        cout << "you can only change place of remaining pieces you have on the table." << endl;
        GameplayRowColumnChecker(player);
    }
}


// Main Function :
int main () {
    PlayersInformation();
    BoardInformation();
    Table();
    GameplayPieceChecker();
    return 0;
}
