#include <iostream>

using namespace std;


void print_board(int** board, int board_len);
bool isValid(int** board, int board_len, int x, int y);
void move_knight(int** board, int board_len, int* x, int* y, int level, int possible_pos[][2]);
bool nextMove(int** board, int board_len, int possible_pos[][2], int* x, int* y);
int getEmptySquares(int** board, int board_len, int x, int y, int possible_pos[][2]);


int main() {

	int board_len;
	int start_x;
	int start_y;

	int possible_pos[][2] = { {-1,2}, {2, 1}, {1, 2}, {-2, 1}, {2, -1}, {1, -2}, {-1, -2} , {-2, -1}};

	cout << "Velikost sahovnice: ";
	cin >> board_len;
	cout << "Zacetni x: ";
	cin >> start_x;
	cout << "Zacetni y: ";
	cin >> start_y;

	int** board = new int* [board_len];
	for (int i = 0; i < board_len; i++) {
		board[i] = new int[board_len];
	}

	for (int y = 0; y < board_len; y++) {
		for (int x = 0; x < board_len; x++) {
			board[y][x] = -1;
		}
	}

	board[start_y][start_x] = 0;
	move_knight(board, board_len, &start_x, &start_y, 1, possible_pos);
	cout << "Ni rešitve";
}

void move_knight(int** board, int board_len, int* x, int* y, int level, int possible_pos[][2]) {

	if (level == board_len * board_len) {
		print_board(board, board_len);
		exit(0);
	}

	int next_x = *x;
	int next_y = *y;

	if (nextMove(board, board_len, possible_pos, &next_x, &next_y)) {
		board[next_y][next_x] = level;
		move_knight(board, board_len, &next_x, &next_y, level + 1, possible_pos);
		board[next_y][next_x] = -1;
	}
	return;
}
	

bool isValid(int** board, int board_len, int x, int y) {
	return x >= 0 && x < board_len && y >= 0 && y < board_len && board[y][x] == -1;
}

void print_board(int** board, int board_len) {
	for (int y = 0; y < board_len; y++) {
		for (int x = 0; x < board_len; x++) {
			cout << board[y][x] + 1 << " ";
		}
		cout << endl;
	}
}

int getEmptySquares(int** board, int board_len, int x, int y, int possible_pos[][2]) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		if (isValid(board, board_len, x + possible_pos[i][0], y + possible_pos[i][1]))
			count++;
	}
	return count;
}

bool nextMove(int** board,int board_len, int possible_pos[][2], int *x, int *y) {
	int min_deg_idx = -1;
	int c;
	int min_deg = board_len+1;
	int next_x;
	int next_y;

	int start = rand() % board_len;
	
	for (int count = 0; count < board_len; ++count) {
		int i = (start + count) % board_len;
		next_x = *x + possible_pos[i][0];
		next_y = *y + possible_pos[i][1];

		if ((isValid(board, board_len, next_x, next_y)) && (c = getEmptySquares(board, board_len, next_x, next_y, possible_pos)) < min_deg) {
			min_deg_idx = i;
			min_deg = c;
		}
	}
	if (min_deg_idx == -1)
		return false;

	next_x = *x + possible_pos[min_deg_idx][0];
	next_y = *y + possible_pos[min_deg_idx][1];

	board[next_y][next_x] = board[*y][*x] + 1;

	*x = next_x;
	*y = next_y;

	return true;

}



