#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <stdbool.h>

#define SCOREBOARD_FILE "scoreboard.txt"
#define MAX_NAME_LEN 32
#define MAX_RANKING_ENTRIES 10

typedef struct {
    char name[MAX_NAME_LEN];
    int score;
} ScoreEntry;

int LoadScores(ScoreEntry *entries, int maxEntries);
int SaveScores(const ScoreEntry *entries, int count);
void AddScore(ScoreEntry *entries, int *count, const char *name, int score);

#endif // SCORE_MANAGER_H
