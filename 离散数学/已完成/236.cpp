#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void g(vector<vector<int> >& result, vector<int>& mapping, vector<int>& A, vector<int>& B, int idx);

int main()
{
    int m, n;
    cin >> m >> n;
    vector<int> A(m);
    vector<int> B(n);
    for (int i = 0; i < m; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }
    vector<vector<int> > result; 
    vector<int> mapping(m); 
    g(result, mapping, A, B, 0); 
    for (int i = 0; i < result.size(); i++) {
        vector<int> mappedElements(B.size(), 0);
        for (int j = 0; j < A.size(); j++) {
            for (int k = 0; k < B.size(); k++) {
                if (result[i][j] == B[k]) {
                    mappedElements[k] = 1;
                    break;
                }
            }
        }
        if (count(mappedElements.begin(), mappedElements.end(), 1) == B.size()) {
            cout << "{";
            for (int j = 0; j < A.size(); j++) {
                cout << "<" << A[j] << "," << result[i][j] << ">";
                if (j < A.size() - 1)
                    cout << ",";
            }
            cout << "}" << endl;
        }
    }
    return 0;
}

void g(vector<vector<int> >& result, vector<int>& mapping, vector<int>& A, vector<int>& B, int idx)
{
    if (idx == A.size()) {
        result.push_back(mapping); 
        return;
    }
    for (int i = 0; i < B.size(); i++) {
        mapping[idx] = B[i]; 
        g(result, mapping, A, B, idx + 1); 
    }
}

