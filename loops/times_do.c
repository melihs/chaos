#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "loop.h"
#include "../utilities/injector.h"

void startTimesDo(long long int iter) {
    if (loop_mode != NULL) {
        loop_mode->nested_counter++;
        return;
    }

    loop_mode = (Loop*)calloc(1, sizeof(Loop));
    loop_mode->body = "";
    loop_mode->type = TIMESDO;
    loop_mode->iter = iter;
    loop_mode->nested_counter = 0;

    recordToken(strdup("\n"), 1);
}
