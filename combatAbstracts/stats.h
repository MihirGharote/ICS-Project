#pragma once

typedef enum { NO_STAT, ATCK, DEFN, AGLT } StatName;

typedef struct {
    short atck;
    short defn;
    short aglt;
} Stats;

typedef struct {
    StatName statName;
    int delta;
} StatChange;
