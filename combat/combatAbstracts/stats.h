#pragma once

typedef enum { NO_STAT, ATCK, DEFN, AGLT } StatName;

typedef struct {
    short atck;
    short defn;
    short aglt;
    int hp;
    int max_hp;
} Stats;

typedef struct {
    StatName statName;
    int delta;
} StatChange;
