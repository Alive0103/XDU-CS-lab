#include <iostream>
#include <vector>

using namespace std;

void generateFunctions(vector<int>& A, vector<int>& B, vector<vector<pair<int, int> > >& functions, vector<pair<int, int> >& current, int index) {
    if (index == A.size()) {
        functions.push_back(current);
        return;
    }

    for (int i = 0; i < B.size(); i++) {
        current.push_back(make_pair(A[index], B[i]));
        generateFunctions(A, B, functions, current, index + 1);
        current.pop_back();
    }
}

void printFunctions(vector<vector<pair<int, int> > >& functions) {
    for (int i = 0; i < functions.size(); i++) {
        cout << "{";
        for (int j = 0; j < functions[i].size(); j++) {
            cout << "<" << functions[i][j].first << "," << functions[i][j].second << ">";
            if (j != functions[i].size() - 1) {
                cout << ",";
            }
        }
        cout << "}" << endl;
    }
}


int main() {
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

    vector<vector<pair<int, int> > > functions;
    vector<pair<int, int> > current;
    generateFunctions(A, B, functions, current, 0);
    printFunctions(functions);

    return 0;
}

