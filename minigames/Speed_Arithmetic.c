#include "../choice_handling/choice_system.h"
#include "../globals.h"
#include "../renderer/renderStory.h"
#include "./minigames.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void print_centered(WINDOW *win, int y, const char *text) {
    int max_x = getmaxx(win);
    mvwprintw(win, y, (max_x - strlen(text)) / 2, "%s", text);
}

int play_arithmetic() {
    int num1, num2, operator_choice, answer;
    char op;
    int score = 0;
    int num_questions = 6;
    int pass_threshold = 40; // out of 60

    struct timeval start_t, end_t;
    double total_time;

    char opt_buffers[3][32];
    char *options[3];
    for (int i = 0; i < 3; i++) {
        options[i] = opt_buffers[i];
    }

    srand(time(0));
    char buf[128];

    werase(mainwin);
    box(mainwin, 0, 0);
    wattron(mainwin, A_HEADER);
    mvwprintw(mainwin, 0, 2, " Speed Arithmetic ");
    wattroff(mainwin, A_HEADER);

    wattron(choicewin, A_HEADER);
    mvwprintw(choicewin, 0, 2, " Choices ");
    wattroff(choicewin, A_HEADER);
    wrefresh(choicewin);

    _renderTitle("Speed Arithmetic", COLOR_MAGENTA);

    sprintf(buf, "Answer %d questions as fast as possible!", num_questions);
    print_centered(mainwin, 3, buf);
    print_centered(mainwin, 5, "Press any key to start...");
    wrefresh(mainwin);
    wgetch(mainwin);

    for (int q = 0; q < num_questions; q++) {
        werase(mainwin);
        box(mainwin, 0, 0); // Keep the box intact for every question
        wattron(mainwin, A_HEADER);
        mvwprintw(mainwin, 0, 2, " Speed Arithmetic ");
        wattroff(mainwin, A_HEADER);

        num1 = rand() % 20 + 1;
        num2 = rand() % 20 + 1;
        operator_choice = rand() % 3;

        switch (operator_choice) {
        case 0:
            op = '+';
            answer = num1 + num2;
            break;
        case 1:
            op = '-';
            answer = num1 - num2;
            break;
        case 2:
            op = '*';
            answer = num1 * num2;
            break;
        }

        int correct_idx = rand() % 3;
        for (int i = 0; i < 3; i++) {
            if (i == correct_idx) {
                sprintf(options[i], "%d", answer);
            } else {
                int wrong_ans;
                do {
                    wrong_ans = answer + ((rand() % 21) - 10);
                } while (wrong_ans == answer);
                sprintf(options[i], "%d", wrong_ans);
            }
        }

        // Display centered question data
        sprintf(buf, "Question %d of %d", q + 1, num_questions);
        print_centered(mainwin, 3, buf);

        sprintf(buf, "Current Score: %d", score);
        print_centered(mainwin, 4, buf);

        sprintf(buf, "Solve: %d %c %d = ?", num1, op, num2);
        print_centered(mainwin, 6, buf);
        wrefresh(mainwin);

        gettimeofday(&start_t, NULL);
        int user_selection = get_menu_choice(choicewin, options, 3) - 1;
        gettimeofday(&end_t, NULL);

        // Calculate difference in seconds + microseconds
        total_time = (end_t.tv_sec - start_t.tv_sec) +
                     (end_t.tv_usec - start_t.tv_usec) / 1000000.0;

        // Evaluate answer
        if (user_selection == correct_idx) {
            sprintf(buf, "Correct! Time: %.2fs", total_time);
            print_centered(mainwin, 7, buf);
            if (total_time < 2.0) {
                score += 10;
            } else {
                score += 5;
            }
        } else {
            sprintf(buf, "Wrong! The answer was %d.", answer);
            print_centered(mainwin, 7, buf);
            score -= 2;
        }

        print_centered(mainwin, 9, "Press any key for the next question...");
        wrefresh(mainwin);
        wgetch(mainwin);
    }

    werase(mainwin);
    box(mainwin, 0, 0);
    wattron(mainwin, A_HEADER);
    mvwprintw(mainwin, 0, 2, " Speed Arithmetic ");
    wattroff(mainwin, A_HEADER);

    bool passed = (score >= pass_threshold);

    _renderTitle("Results", COLOR_YELLOW);

    sprintf(buf, "Final Score: %d / %d", score, num_questions * 10);
    print_centered(mainwin, 3, buf);

    if (passed) {
        print_centered(mainwin, 5, "[ PASS ] Excellent speed and accuracy!");
    } else {
        sprintf(buf, "[ FAIL ] You need at least %d points to pass.",
                pass_threshold);
        print_centered(mainwin, 5, buf);
    }

    wrefresh(mainwin);
    nextChoice();

    return passed;
}