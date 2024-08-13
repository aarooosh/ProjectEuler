#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PATHS 3400

typedef struct {
    int sums[17];
    int length;
} Path;

Path paths[MAX_PATHS];
int count = 0;

// Compatibility matrix
bool compatibility[MAX_PATHS][MAX_PATHS] = {false};

// Function to add a new path to the list
void addPath(int* sums, int length) {
    for (int i = 0; i < length; i++) {
        paths[count].sums[i] = sums[i];
    }
    paths[count].length = length;
    count++;
}

// Recursive function to generate all paths
void generatePaths(int N, int currentSum, int* sums, int length) {
    if (currentSum == N) {
        addPath(sums, length);
        return;
    }
    if (currentSum > N) {
        return;
    }

    sums[length] = currentSum + 2;
    generatePaths(N, currentSum + 2, sums, length + 1);

    sums[length] = currentSum + 3;
    generatePaths(N, currentSum + 3, sums, length + 1);
}

// Function to check if two paths are compatible
bool arePathsCompatible(Path* path1, Path* path2) {
    int minLength = path1->length < path2->length ? path1->length : path2->length;
    for (int i = 0; i < minLength - 1; i++) {
        for (int j = 0; j < path2->length - 1; j++) {
            if (path1->sums[i] == path2->sums[j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to populate the compatibility matrix
void populateCompatibilityMatrix() {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (arePathsCompatible(&paths[i], &paths[j])) {
                compatibility[i][j] = true;
                compatibility[j][i] = true;
            }
        }
    }
}

// Function to count valid sequences of m paths using dynamic programming
unsigned long long countValidSequences(int m) {
    unsigned long long dp[MAX_PATHS][m + 1];
    
    // Initialize dp array
    for (int i = 0; i < count; i++) {
        dp[i][1] = 1;  // Any single path can be a sequence of length 1
        for (int j = 2; j <= m; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill the dp table
    for (int j = 2; j <= m; j++) {
        for (int i = 0; i < count; i++) {
            for (int k = 0; k < count; k++) {
                if (compatibility[i][k]) {
                    dp[i][j] += dp[k][j - 1];
                }
            }
        }
    }

    // Sum up all valid sequences of length m
    unsigned long long totalCount = 0;
    for (int i = 0; i < count; i++) {
        totalCount += dp[i][m];
    }

    return totalCount;
}

int main() {
    

    int sums[17]; 
    generatePaths(32, 0, sums, 0);

    // Populate the compatibility matrix
    populateCompatibilityMatrix();

    // Count the number of valid sequences of length m
    unsigned long long totalCount = countValidSequences(10);

    printf("Total number of valid configurations: %llu\n", totalCount);

    return 0;
}
