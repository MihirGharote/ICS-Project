#include "../globals.h"
#include "../renderer/renderStory.h"
#include "./minigames.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define REACTION_COUNT 3
#define render_centre(s) (getmaxx(mainwin) - strlen(s)) / 2, s

static double timespec_diff_sec(const struct timespec *a,
                                const struct timespec *b) {
    return (b->tv_sec - a->tv_sec) + (b->tv_nsec - a->tv_nsec) / 1e9;
}

static void manual_wait_with_input_discard(WINDOW *win, int delay_ms) {
    int ch;
    nodelay(win, TRUE);
    int elapsed = 0;
    const int step = 50;
    while (elapsed < delay_ms) {
        // discard any key presses during wait
        while ((ch = wgetch(win)) != ERR) {
            (void)ch;
        }
        napms(step);
        elapsed += step;
    }
    nodelay(win, FALSE);
}

int play_reaction() {
    noecho();
    int c = REACTION_COUNT;
    int success = 0;
    double total_reaction = 0;
    // Display initial prompts

    werase(mainwin);
    box(mainwin, 0, 0);

    werase(choicewin);
    box(choicewin, 0, 0);

    wattron(mainwin, A_HEADER);
    mvwprintw(mainwin, 0, 2, "Reaction Test");
    wattroff(mainwin, A_HEADER);

    wattron(choicewin, A_HEADER);
    mvwprintw(choicewin, 0, 2, " Choices ");
    wattroff(choicewin, A_HEADER);

    _renderTitle("Reaction Test", COLOR_MAGENTA);
    wrefresh(choicewin);
    wrefresh(mainwin);
    refresh();

    while (c--) {
        mvwprintw(mainwin, 9,
                  render_centre("                                     "));
        mvwprintw(mainwin, 6, render_centre("Press ENTER to start"));
        wrefresh(mainwin);
        refresh();

        // Wait for initial ENTER (blocking)
        int ch;
        while ((ch = wgetch(mainwin)) != '\n' && ch != '\r' &&
               ch != KEY_ENTER) {
        }

        // Seed RNG and choose delay between 2000 to 5000 ms
        srand(time(NULL));
        int delay_ms = (rand() % 4 + 2) * 1000;

        mvwprintw(mainwin, 6, render_centre("                    "));
        mvwprintw(mainwin, 6, render_centre("Waiting..."));
        mvwprintw(mainwin, 7, render_centre("Press Enter when I say \"NOW\""));

        wrefresh(mainwin);
        refresh();

        // Non-blocking wait that discards input
        manual_wait_with_input_discard(mainwin, delay_ms);

        // Show NOW, beep, and start timing
        beep();
        mvwprintw(mainwin, 6, render_centre("                    "));
        mvwprintw(mainwin, 7, render_centre("                              "));
        wattron(mainwin, A_BOLD | COLOR_PAIR(COLOR_BLUE));
        mvwprintw(mainwin, 7, render_centre("NOW"));
        wattroff(mainwin, A_BOLD | COLOR_PAIR(COLOR_BLUE));
        wrefresh(mainwin);
        refresh();

        struct timespec t_start, t_end;
        clock_gettime(CLOCK_MONOTONIC, &t_start);

        // Wait for ENTER (blocking) to record reaction
        while ((ch = wgetch(mainwin)) != '\n' && ch != '\r' &&
               ch != KEY_ENTER) { /* block */
        }

        clock_gettime(CLOCK_MONOTONIC, &t_end);
        double reaction = timespec_diff_sec(&t_start, &t_end);
        total_reaction += reaction;

        // Show result
        mvwprintw(mainwin, 7, render_centre("                              "));
        mvwprintw(mainwin, 9, render_centre("Reaction Time: %.3f seconds"),
                  reaction);
        mvwprintw(mainwin, 10,
                  render_centre("Average Reaction Time: %.3f seconds"),
                  total_reaction / (REACTION_COUNT - c));
        wrefresh(mainwin);
        refresh();
        napms(1000);
    }
    nextChoice();
    mvwprintw(mainwin, 9, render_centre("                              "));
    if (total_reaction / REACTION_COUNT > 0.666) {
        mvwprintw(mainwin, 9, render_centre("Too slow!"));
        success = false;
    } else {
        mvwprintw(mainwin, 9, render_centre("You did it!"));
        success = true;
    }
    wrefresh(mainwin);
    refresh();

    echo();
    nextChoice();
    return success;
}