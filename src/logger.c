#include "logger.h"

void log_event(const char* message) {
    FILE* f = fopen("logs.txt", "a");
    if (!f) return;

    time_t now = time(NULL);
    char* timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0';

    fprintf(f, "[%s] %s\n", timestamp, message);
    fclose(f);
}
