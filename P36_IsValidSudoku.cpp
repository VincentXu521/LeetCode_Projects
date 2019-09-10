/*
判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可.
1. 数字 1-9 在每一行只能出现一次。
2. 数字 1-9 在每一列只能出现一次。
3. 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。

数独部分空格内已填入了数字，空白格用 '.' 表示。
示例 1:
输入:
[
["5","3",".",".","7",".",".",".","."],
["6",".",".","1","9","5",".",".","."],
[".","9","8",".",".",".",".","6","."],
["8",".",".",".","6",".",".",".","3"],
["4",".",".","8",".","3",".",".","1"],
["7",".",".",".","2",".",".",".","6"],
[".","6",".",".",".",".","2","8","."],
[".",".",".","4","1","9",".",".","5"],
[".",".",".",".","8",".",".","7","9"]
]
输出: true
示例 2:
输入:
[
["8","3",".",".","7",".",".",".","."],
["6",".",".","1","9","5",".",".","."],
[".","9","8",".",".",".",".","6","."],
["8",".",".",".","6",".",".",".","3"],
["4",".",".","8",".","3",".",".","1"],
["7",".",".",".","2",".",".",".","6"],
[".","6",".",".",".",".","2","8","."],
[".",".",".","4","1","9",".",".","5"],
[".",".",".",".","8",".",".","7","9"]
]
输出: false
解释: 除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。
但由于位于左上角的 3x3 宫内有两个 8 存在, 因此这个数独是无效的。

说明:
1. 一个有效的数独（部分已被填充）不一定是可解的。
2. 只需要根据以上规则，验证已经填入的数字是否有效即可。
3. 给定数独序列只包含数字 1-9 和字符 '.' 。
4. 给定数独永远是 9x9 形式的。
*/

#include<vector>
using namespace std;

class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		bool row = true, col = true, cell = true;
		// 不会了，O(N*N*N) so stupid...don't do it...
		// 要不，看看人家如何巧妙做的吧...
	}
};

// ------------------------------ copy...------------ OMG!!! so skillful...-------
class Solution {
public:
	bool isValidSudoku(vector<vector<char> > &board) {
		if (board.empty() || board[0].empty()) return false;
		int m = board.size(), n = board[0].size();
		vector<vector<bool> > rowFlag(m, vector<bool>(n, false));
		vector<vector<bool> > colFlag(m, vector<bool>(n, false));
		vector<vector<bool> > cellFlag(m, vector<bool>(n, false));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] >= '1' && board[i][j] <= '9') {
					int c = board[i][j] - '1';
					if (rowFlag[i][c] || colFlag[c][j] || cellFlag[3 * (i / 3) + j / 3][c]) return false;
					rowFlag[i][c] = true;
					colFlag[c][j] = true;
					cellFlag[3 * (i / 3) + j / 3][c] = true;  // 这个转换我是服得厉害!!！
				}
			}
		}
		return true;
	}
};




// 内存占用小，不需要建立布尔二维表：(但有三个for循环) 最原始想法，同cell不太好想。
class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		if (board.size() != 9 || board[0].size() != 9) return false;
		for (int x = 0; x < 9; x++)
			for (int y = 0; y < 9; y++) {
				if (board[x][y] != '.') {
					for (int i = 0; i < 9; i++) {
						if (i != x && board[i][y] == board[x][y]) return false;
						if (i != y && board[x][i] == board[x][y]) return false;
						if ((x/3*3+i/3)!=x && (y/3*3+i%3)!=y && board[x/3*3+i/3][y/3*3+i%3] == board[x][y]) return false;
					}
				}
				else
					continue; // 这个else可以去掉吧？！
			}
		return true;
	}
};




