#include <iostream>
#include <vector>

using namespace std;

void warshall(vector< vector < int > > & matrix) {
    int n = matrix.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0)
                    matrix[i][j] = matrix[i][k] & matrix[k][j];
                else
                    matrix[i][j] = 1;
            }
        }
    }
}

int main() 
{
    int N;
//    cin.get(N);
    cin >> N;
    vector<vector<int> > matrix(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }
    warshall(matrix);
//    cout << "图G的可达矩阵d为：" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

