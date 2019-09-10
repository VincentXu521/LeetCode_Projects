/*
编写一个程序，通过已填充的空格来解决数独问题。
一个数独的解法需遵循如下规则：
1.数字 1-9 在每一行只能出现一次。
2.数字 1-9 在每一列只能出现一次。
3.数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
4.空白格用 '.' 表示。

1.给定的数独序列只包含数字 1-9 和字符 '.' 。
2.你可以假设给定的数独只有唯一解。
3.给定数独永远是 9x9 形式的。
*/

#include<vector>
using namespace std;


// copy..._________________________________________________________________________TT
// 用到了 dfs ，据说和 N_Queen 有相似？？？
class Solution {
public:
	void solveSudoku(vector<vector<char> > &board) {
		if (board.empty() || board.size() != 9 || board[0].size() != 9) return;
		solveSudokuDFS(board, 0, 0);
	}
	bool solveSudokuDFS(vector<vector<char> > &board, int i, int j) {
		if (i == 9) return true;
		if (j >= 9) return solveSudokuDFS(board, i + 1, 0); // diff: >= or == ??? same?yes!!!
		if (board[i][j] == '.') {
			for (int k = 1; k <= 9; ++k) {
				board[i][j] = (char)(k + '0');
				if (isValid(board, i, j)) {
					if (solveSudokuDFS(board, i, j + 1)) return true;
				}
				board[i][j] = '.';
			}
		}
		else {
			return solveSudokuDFS(board, i, j + 1);
		}
		return false;
	}
	bool isValid(vector<vector<char> > &board, int i, int j) {
		for (int col = 0; col < 9; ++col) {
			if (col != j && board[i][j] == board[i][col]) return false;
		}
		for (int row = 0; row < 9; ++row) {
			if (row != i && board[i][j] == board[row][j]) return false;
		}
		for (int row = i / 3 * 3; row < i / 3 * 3 + 3; ++row) {
			for (int col = j / 3 * 3; col < j / 3 * 3 + 3; ++col) {
				if ((row != i || col != j) && board[i][j] == board[row][col]) return false;
			}
		}
		return true;
	}
};



// exe 0ms example:
// well, beyond my intelligence, bit operation...
class Solution {
public:
	bool solveSudoku(vector<vector<char>>& board) {
		vector<char> vt(1 << 8 + 1);
		for (int i = 0; i < 9; ++i) {
			vt[1 << i] = i + '1';
		}
		const int vm[9] = { 0,0,0,1,1,1,2,2,2 };
		const int vm2[9] = { 0,1,2,0,1,2,0,1,2 };

		//先确定行，列，块的剩余可选数
		vector<int> vr(9, 0x1ff);
		vector<int> vc(9, 0x1ff);
		vector<int> vb(9, 0x1ff);

		char e;
		int i, j, g, z, q;
		const char dot = '.' - '1';
		for (int r = 0; r < 9; ++r) {
			for (int c = 0; c < 9; ++c) {
				e = board[r][c] - '1';
				if (e != dot) {
					i = ~(1 << e);
					vr[r] = vr[r] & i;
					vc[c] = vc[c] & i;
					j = vm[r] * 3 + vm[c];
					vb[j] = vb[j] & i;
				}
			}
		}

		//每个空格子可选数
		int orow[9][9] = { 0 };
		int oc[9][9] = { 0 };
		int ob[9][9] = { 0 };
		for (int r = 0; r < 9; ++r) {
			for (int c = 0; c < 9; ++c) {
				if (board[r][c] == '.') {
					i = vr[r] & vc[c] & vb[vm[r] * 3 + vm[c]];
					//if (!i)
					//	return false;
					orow[r][c] = i;
					oc[c][r] = i;
					ob[vm[r] * 3 + vm[c]][vm2[r] * 3 + vm2[c]] = i;
				}
			}
		}

		//根据行列块中其它空格子的可选数判断一个空格子中是否存在唯一的可选数，有则为解
		bool hasChanged = false, complete = true;
		for (int r = 0; r < 9; ++r) {
			for (int c = 0; c < 9; ++c) {
				if (board[r][c] == '.') {
					g = orow[r][c];
					if (!g)
						return false;
					//行
					i = 0;
					for (j = 0; j < 9; ++j) {
						if (j != c)
							i |= orow[r][j];
					}
					z = g & ~i;
					if (z && !(z & (z - 1))) {
						board[r][c] = vt[z];

						z = ~z;
						q = vm[r] * 3 + vm[c];
						for (int t = 0; t < 9; ++t) {
							orow[r][t] &= z;
							oc[t][r] &= z;
							ob[vm[r] * 3 + vm[t]][vm2[r] * 3 + vm2[t]] &= z;

							oc[c][t] &= z;
							orow[t][c] &= z;
							ob[vm[t] * 3 + vm[c]][vm2[t] * 3 + vm2[c]] &= z;

							ob[q][t] &= z;
							orow[vm[q] * 3 + vm[t]][vm2[q] * 3 + vm2[t]] &= z;
							oc[vm2[q] * 3 + vm2[t]][vm[q] * 3 + vm[t]] &= z;
						}
						orow[r][c] = 0;
						oc[c][r] = 0;
						ob[q][vm2[r] * 3 + vm2[c]] = 0;

						hasChanged = true;
						continue;
					}
					//列
					i = 0;
					for (j = 0; j < 9; ++j) {
						if (j != r)
							i |= oc[c][j];
					}
					z = g & ~i;
					if (z && !(z & (z - 1))) {
						board[r][c] = vt[z];

						z = ~z;
						q = vm[r] * 3 + vm[c];
						for (int t = 0; t < 9; ++t) {
							orow[r][t] &= z;
							oc[t][r] &= z;
							ob[vm[r] * 3 + vm[t]][vm2[r] * 3 + vm2[t]] &= z;

							oc[c][t] &= z;
							orow[t][c] &= z;
							ob[vm[t] * 3 + vm[c]][vm2[t] * 3 + vm2[c]] &= z;

							ob[q][t] &= z;
							orow[vm[q] * 3 + vm[t]][vm2[q] * 3 + vm2[t]] &= z;
							oc[vm2[q] * 3 + vm2[t]][vm[q] * 3 + vm[t]] &= z;
						}
						orow[r][c] = 0;
						oc[c][r] = 0;
						ob[q][vm2[r] * 3 + vm2[c]] = 0;

						hasChanged = true;
						continue;
					}
					//块
					i = 0;
					q = vm2[r] * 3 + vm2[c];
					for (j = 0; j < 9; ++j) {
						if (j != q)
							i |= ob[vm[r] * 3 + vm[c]][j];
					}
					z = g & ~i;
					if (z && !(z & (z - 1))) {
						board[r][c] = vt[z];

						z = ~z;
						q = vm[r] * 3 + vm[c];
						for (int t = 0; t < 9; ++t) {
							orow[r][t] &= z;
							oc[t][r] &= z;
							ob[vm[r] * 3 + vm[t]][vm2[r] * 3 + vm2[t]] &= z;

							oc[c][t] &= z;
							orow[t][c] &= z;
							ob[vm[t] * 3 + vm[c]][vm2[t] * 3 + vm2[c]] &= z;

							ob[q][t] &= z;
							orow[vm[q] * 3 + vm[t]][vm2[q] * 3 + vm2[t]] &= z;
							oc[vm2[q] * 3 + vm2[t]][vm[q] * 3 + vm[t]] &= z;
						}
						orow[r][c] = 0;
						oc[c][r] = 0;
						ob[q][vm2[r] * 3 + vm2[c]] = 0;

						hasChanged = true;
						continue;
					}
					complete = false;
				}
			}
		}

		if (!complete) {
			if (hasChanged)
				return solveSudoku(board);
			else {
				for (int r = 0; r < 9; ++r) {
					for (int c = 0; c < 9; ++c) {
						if (board[r][c] == '.') {
							if (g = orow[r][c]) {
								for (z = 0; z < 9; ++z) {
									if (g & (1 << z)) {
										auto t = board;
										t[r][c] = z + '1';
										if (solveSudoku(t)) {
											board = t;
											return true;
										}
									}
								}
							}
							return false;
						}
					}
				}
			}
		}
		return true;
	}
};



// exe 8ms e.g.:
// same method as the first one...
class Solution {
public:
	void solveSudoku(vector<vector<char>>& board) {
		result(board, 0, 0);
	}
	bool result(vector<vector<char>>& board, int row, int column)
	{
		if (row == 9)
			return true;
		if (column == 9)
			return result(board, row + 1, 0);

		if (board[row][column] == '.')
		{
			for (char index = '1'; index <= '9'; index++)
			{
				if (isValidSudoku(board, row, column, index))
				{
					board[row][column] = index;
					if (result(board, row, column + 1))
						return true;
					board[row][column] = '.';
				}
			}
		}
		else
			return (result(board, row, column + 1));

		return false;
	}
	bool isValidSudoku(vector<vector<char>>& board, int i, int j, char val) {
		for (int h = 0; h<9; h++)
		{
			if (board[i][h] == val) return false; // check row 
			if (board[h][j] == val) return false; // check column 
			if (board[i - i % 3 + h / 3][j - j % 3 + h % 3] == val)return false; // check cub
		}
		return true;
	}
};



// more normal method, easy to understand..
class Solution {
public:
	void solveSudoku(vector<vector<char>>& board) {
		dfs(board);
	}
	bool dfs(vector<vector<char>> & board) {
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board.size(); ++j) {
				if (board[i][j] == '.') {
					for (int k = 0; k < 9; ++k) {
						board[i][j] = k + '1';
						if (isValid(board, i, j) && dfs(board))
							return true;
						board[i][j] = '.';
					}
					return false;
				}
			}
		}
		return true;
	}
	bool isValid(vector<vector<char>> & board, int x, int y) {
		for (int i = 0; i < board.size(); ++i)
			if (i != x && board[i][y] == board[x][y])
				return false;
		for (int j = 0; j < board.size(); ++j)
			if (j != y && board[x][j] == board[x][y])
				return false;

		for (int i = 3 * (x / 3); i < 3 * (x / 3 + 1); ++i) {
			for (int j = 3 * (y / 3); j < 3 * (y / 3 + 1); ++j) {
				if ((i != x || j != y) && board[i][j] == board[x][y])
					return false;
			}
		}
		return true;
	}
};


