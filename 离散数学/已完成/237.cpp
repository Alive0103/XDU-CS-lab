#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void backtrack(vector<pair<int, int> >& relations, vector<vector<pair<int, int> > >& result, vector<int>& A, vector<int>& B, vector<bool>& used) {
    if (relations.size() == A.size()) {
        result.push_back(relations);
        return;
    }

    for (int i = 0; i < B.size(); i++) {
        if (!used[i]) {
            used[i] = true;
            relations.push_back(make_pair(A[relations.size()], B[i]));
            backtrack(relations, result, A, B, used);
            relations.pop_back();
            used[i] = false;
        }
    }
}

vector<vector<pair<int, int> > > findSurjections(vector<int>& A, vector<int>& B) {
    vector<vector<pair<int, int> > > result;
    vector<pair<int, int> > relations;
    vector<bool> used(B.size(), false);
    backtrack(relations, result, A, B, used);
    return result;
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

    vector<vector<pair<int, int> > > surjections = findSurjections(A, B);

    sort(surjections.begin(), surjections.end(), [](const vector<pair<int, int> >& a, const vector<pair<int, int> >& b) {
    if (a.size() == b.size()) {
        return a < b;
    }
    return a.size() < b.size();
});

    for (const auto& surjection : surjections) {
        cout << "{";
        for (int i = 0; i < surjection.size(); i++) {
            cout << "<" << surjection[i].first << "," << surjection[i].second << ">";
            if (i != surjection.size() - 1) {
                cout << ",";
            }
        }
        cout << "}" << endl;
    }

    return 0;
}

