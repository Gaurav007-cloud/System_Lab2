#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Artifact {
    int weights;
    int rarityvalue;
};

int maxrarityvalue(int a, vector<Artifact>& artifacts, int b, vector<vector<int>>& dp) {
    for (int i = 1; i <= a; i++) {
        for (int w = 1; w <= b; w++) {
            if (artifacts[i - 1].weights <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - artifacts[i - 1].weights] + artifacts[i - 1].rarityvalue);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[a][b];
}

void findartifacts(int a, vector<Artifact>& artifacts, int b, vector<vector<int>>& dp, vector<int>& selectedArtifacts) {
    int i = a, w = b;
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedArtifacts.push_back(i);
            w -= artifacts[i - 1].weights;
        }
        i--;
    }
}

int main() {
    int N; //enter the number of artifacts
    cout<<"N: ";
    cin >> N;

    cout<<"Magical Artifacts:"<<endl;
    

    vector<Artifact> artifacts(N);

   for (int i = 0; i < N; i++) {
        cout << "Artifact " << i + 1<<endl;
        cout<<"Weight: ";
        cin >> artifacts[i].weights;
        cout<<"Rarity value: ";
        cin >> artifacts[i].rarityvalue;
    }

   
    int MC; //enter maximum weight capacity of the bag
    cout<<"Maximum Capacity(MC)= ";
    cin >> MC;

    vector<vector<int>> dp(N + 1, vector<int>(MC + 1, 0));
    int maxRarityvalue = maxrarityvalue(N, artifacts, MC, dp);

    vector<int> selectedArtifacts;
    findartifacts(N, artifacts, MC, dp, selectedArtifacts);

    cout << "Maximum rarityvalue value that can be obtained: " << maxRarityvalue << endl;
    cout << "Chosen Artifacts: ";
    for (int i = selectedArtifacts.size() - 1; i >= 0; i--) {
        int idx = selectedArtifacts[i] - 1;
        cout << idx + 1 << " (Weights: " << artifacts[idx].weights << ", Rarity Value: " << artifacts[idx].rarityvalue << ")";
        if (i > 0) {
            cout << " and ";
            
        }
    }
    cout<<", ";
    cout<<"Rarity value:"<<maxRarityvalue<<endl;

    return 0;
}