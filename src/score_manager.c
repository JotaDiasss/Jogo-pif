#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/score_manager.h"

static int CompareScores(const void *a, const void *b)
{
    const ScoreEntry *sa = (const ScoreEntry *)a;
    const ScoreEntry *sb = (const ScoreEntry *)b;
    return sb->score - sa->score;
}

int LoadScores(ScoreEntry *entries, int maxEntries)
{
    FILE *file = fopen(SCOREBOARD_FILE, "r");
    if (!file) {
        return 0;
    }

    char line[128];
    int count = 0;

    while (count < maxEntries && fgets(line, sizeof(line), file)) {
        size_t len = strcspn(line, "\r\n");
        line[len] = '\0';

        // Encontra o último espaço antes do número
        char *ptr = line + strlen(line);
        while (ptr > line && isspace((unsigned char)ptr[-1])) {
            ptr--;
        }
        *ptr = '\0';

        char *scoreText = ptr;
        while (scoreText > line && !isspace((unsigned char)scoreText[-1])) {
            scoreText--;
        }

        if (scoreText == line) {
            continue;
        }

        int score = atoi(scoreText);
        size_t nameLen = (size_t)(scoreText - line);
        if (nameLen >= MAX_NAME_LEN) {
            nameLen = MAX_NAME_LEN - 1;
        }

        if (nameLen > 0) {
            strncpy(entries[count].name, line, nameLen);
            entries[count].name[nameLen] = '\0';
            entries[count].score = score;
            count++;
        }
    }

    fclose(file);

    qsort(entries, count, sizeof(ScoreEntry), CompareScores);
    return count;
}

int SaveScores(const ScoreEntry *entries, int count)
{
    FILE *file = fopen(SCOREBOARD_FILE, "w");
    if (!file) {
        return 0;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", entries[i].name, entries[i].score);
    }

    fclose(file);
    return 1;
}

void AddScore(ScoreEntry *entries, int *count, const char *name, int score)
{
    if (!name || name[0] == '\0') {
        return;
    }

    ScoreEntry entry;
    strncpy(entry.name, name, MAX_NAME_LEN - 1);
    entry.name[MAX_NAME_LEN - 1] = '\0';
    entry.score = score;

    if (*count < MAX_RANKING_ENTRIES) {
        entries[*count] = entry;
        (*count)++;
    } else if (score > entries[*count - 1].score) {
        entries[*count - 1] = entry;
    } else {
        return;
    }

    qsort(entries, *count, sizeof(ScoreEntry), CompareScores);

    if (*count > MAX_RANKING_ENTRIES) {
        *count = MAX_RANKING_ENTRIES;
    }
}
