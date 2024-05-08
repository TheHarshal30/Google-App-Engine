#include<iostream>
#include<vector>
using namespace std;

class NQueens{
    private:
    int N;
    vector<vector<int>> board;
    public:
    NQueens(int n): N(n),board(n,vector<int>(n,0)){}

    bool isSafe(int row, int col){
        for(int i = 0; i <row ;i++){
            if(board[i][col] == 1) return false;
        }
        for(int i=row,j=col; i>=0 && j>=0 ; i--,j--){
            if(board[i][j] == 1) return false;
        }
        for(int i=row,j=col; i>=0 && j<N; i--,j++){
            if(board[i][j] == 1) return false;
        }
        return true;
    }

    bool solveNqueensUtil(int row){
        if(row == N) return true;

        for(int i=0;i<N;i++){
            if(isSafe(row,i)){
                board[row][i] = 1;

                if(solveNqueensUtil(row+1)) return true;
                board[row][i] = 0;
            }

        }
        return false;
    }

    void solveNQueens(){
        if(!solveNqueensUtil(0)) return;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};


int main(){
    NQueens Q(7);
    Q.solveNQueens();
    return 0;
}