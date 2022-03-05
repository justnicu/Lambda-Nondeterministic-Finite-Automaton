#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int STATE_MAX = 1e5 + 5;
const int WORD_MAX = 1e5 + 5;

int N, state;
vector < int > validStates;

int M, x, y;
char l[5];

int startState, nrF, finalState[STATE_MAX], nrWords;
char word[WORD_MAX];

vector < pair < int, char > > G[STATE_MAX];
vector < int > Path;

vector < int > lastVisit[STATE_MAX]; /// memoreaza numarul de caractere ramase dintr-un cuvant la trecerea printr-o stare pentru a depistarea ciclurilor lambda

bool Check(int currState, char *word, int len)
{
    for (int lastLen: lastVisit[currState]) {
        if (lastLen == len) {
            return false;
        }
    }
    lastVisit[currState].push_back(len);

    Path.push_back(currState);
    if (word[0] == 0 && finalState[currState] == true) {
        return finalState[currState];
    }

    for (pair < int, char > edge: G[currState]) {
        int nextState = edge.first;
        int letter = edge.second;
        if (letter == word[0] && letter != 0) {
            if (Check(nextState, word + 1, len - 1) == true) {
                return true;
            }
        }
        else if (letter == 0) {
            if (Check(nextState, word, len) == true) {
                return true;
            }
        }
    }
    Path.pop_back();
    return false;
}

void Reset()
{
    Path.clear();
    for (int state: validStates) {
        lastVisit[state].clear();
    }
}

int main()
{
    fin >> N;
    for (int i = 1; i <= N; i++) {
        fin >> state;
        validStates.push_back(state);
    }
    fin >> M;
    for (int i = 1; i <= M; i++) {
        fin >> x >> y;
        fin.getline(l, 3);
        G[x].push_back(make_pair(y, l[1]));
    }

    for (int state: validStates) {
        sort(G[state].begin(), G[state].end(), [](pair <int, char> a, pair <int, char> b) -> bool {
            return a.second > b.second;
        });
    }

    fin >> startState;
    fin >> nrF;
    for (int i = 1; i <= nrF; i++) {
        fin >> state;
        finalState[state] = 1;
    }

    fin >> nrWords;
    fin.get();
    for (int i = 1; i <= nrWords; i++) {
        Reset();
        fin.getline(word, WORD_MAX);
        if (Check(startState, word, strlen(word))) {
            fout << "DA\n";
            for (int state: Path) {
                fout << state << " ";
            }
            fout << "\n";
        }
        else {
            fout << "NU\n";
        }
    }
    return 0;
}
