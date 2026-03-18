#pragma once

typedef enum {
    NO_STATUS = 0,
    POISON = 1 << 0,
    REGEN = 1 << 1,
} StatusFlags;

typedef struct {
    StatusFlags status;
    int severity;
} StatusEffect;
