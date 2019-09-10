/*
�ж�һ�� 9x9 �������Ƿ���Ч��ֻ��Ҫ�������¹�����֤�Ѿ�����������Ƿ���Ч����.
1. ���� 1-9 ��ÿһ��ֻ�ܳ���һ�Ρ�
2. ���� 1-9 ��ÿһ��ֻ�ܳ���һ�Ρ�
3. ���� 1-9 ��ÿһ���Դ�ʵ�߷ָ��� 3x3 ����ֻ�ܳ���һ�Ρ�

�������ֿո��������������֣��հ׸��� '.' ��ʾ��
ʾ�� 1:
����:
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
���: true
ʾ�� 2:
����:
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
���: false
����: ���˵�һ�еĵ�һ�����ִ� 5 ��Ϊ 8 ���⣬�ո����������־��� ʾ��1 ��ͬ��
������λ�����Ͻǵ� 3x3 ���������� 8 ����, ��������������Ч�ġ�

˵��:
1. һ����Ч�������������ѱ���䣩��һ���ǿɽ�ġ�
2. ֻ��Ҫ�������Ϲ�����֤�Ѿ�����������Ƿ���Ч���ɡ�
3. ������������ֻ�������� 1-9 ���ַ� '.' ��
4. ����������Զ�� 9x9 ��ʽ�ġ�
*/

#include<vector>
using namespace std;

class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		bool row = true, col = true, cell = true;
		// �����ˣ�O(N*N*N) so stupid...don't do it...
		// Ҫ���������˼�����������İ�...
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
					cellFlag[3 * (i / 3) + j / 3][c] = true;  // ���ת�����Ƿ�������!!��
				}
			}
		}
		return true;
	}
};




// �ڴ�ռ��С������Ҫ����������ά��(��������forѭ��) ��ԭʼ�뷨��ͬcell��̫���롣
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
					continue; // ���else����ȥ���ɣ���
			}
		return true;
	}
};




