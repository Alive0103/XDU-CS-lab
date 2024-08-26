#include <iostream>
#include <vector>

using namespace std;

void g(vector<int>& A, vector<int>& B, vector<vector<pair<int, int> > >
	& functions, vector<pair<int, int> >& cur, vector<bool>& used, int index);

void print(vector<vector<pair<int, int> > >& f) ; 

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
    vector<vector<pair<int, int> > > f;
    vector<pair<int, int> > cur;
    vector<bool> used(n, 0);
    g(A, B, f, cur, used, 0);
    print(f);
    return 0;
}

void print(vector<vector<pair<int, int> > >& f) {
    for (int i = 0; i < f.size(); i++) {
        cout << "{";
        for (int j = 0; j < f[i].size(); j++) {
            cout << "<" << f[i][j].first << "," << f[i][j].second << ">";
            if (j != f[i].size() - 1) {
                cout << ",";
            }
        }
        cout << "}" << endl;
    }
}

void g(vector<int>& A, vector<int>& B, vector<vector<pair<int, int> > >& f, vector<pair<int, int> >& cur, vector<bool>& used, int index) {
    if (index == A.size()) {
        f.push_back(cur);
        return;
    }

    for (int i = 0; i < B.size(); i++) {
        if (!used[i]) {
            used[i] = true;
            cur.push_back(make_pair(A[index], B[i]));
            g(A, B, f, cur, used, index + 1);
            cur.pop_back();
            used[i] = false;
        }
    }
}

