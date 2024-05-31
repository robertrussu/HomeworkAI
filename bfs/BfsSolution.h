#ifndef AI_HOMEWORK_DFSSOLUTION_H
#define AI_HOMEWORK_DFSSOLUTION_H

#include "../includes.h"
class BfsSolution {
public:
    BfsSolution(int numCities, const vector<vector<int>>& distances)
        : numCities(numCities), distances(distances), minLongestDistance(INT_MAX) {}

    void solve() {
        queue<State> q;
        vector<bool> initialVisited(numCities, false);
        initialVisited[0] = true;
        q.push({ 0, {0}, initialVisited, 0 });

        while (!q.empty()) {
            State currentState = q.front();
            q.pop();

            if (currentState.route.size() == numCities) {
                int currentLongest = max(currentState.currentLongest, distances[currentState.node][0]);
                if (currentLongest < minLongestDistance) {
                    minLongestDistance = currentLongest;
                    bestRoute = currentState.route;
                    bestRoute.push_back(0);
                }
                continue;
            }

            for (int i = 0; i < numCities; ++i) {
                if (!currentState.visited[i]) {
                    vector<bool> newVisited = currentState.visited;
                    newVisited[i] = true;
                    vector<int> newRoute = currentState.route;
                    newRoute.push_back(i);
                    int newLongest = max(currentState.currentLongest, distances[currentState.node][i]);
                    q.push({ i, newRoute, newVisited, newLongest });
                }
            }
        }
    }

    void printSolution() const {
        cout << "Minimum longest distance: " << minLongestDistance << endl;
        cout << "Best path: ";
        for (int city : bestRoute) {
            cout << city << " ";
        }
        cout << endl;
    }

    int calculateTotalCost() const {
        int totalCost = 0;
        for (size_t i = 0; i < bestRoute.size() - 1; ++i) {
            totalCost += distances[bestRoute[i]][bestRoute[i + 1]];
        }
        return totalCost;
    }

private:
    struct State {
        int node;
        vector<int> route;
        vector<bool> visited;
        int currentLongest;
    };

    int numCities;
    vector<vector<int>> distances;
    int minLongestDistance;
    vector<int> bestRoute;
};

#endif //AI_HOMEWORK_DFSSOLUTION_H
