#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main(void) {
    bool shouldRun = true;
    char* args[MAX_LINE / 2 +1];
    char s[MAX_LINE + 1];

    while (shouldRun) {
        printf("osh>");
        fflush(stdout);
        fflush(stdin);

        memset(args, 0, sizeof(args));

        scanf("%[^\n]", s);
        getchar();
        int len = strlen(s);
        s[len] = '\n';
        s[len + 1] = '\0';
        char* c = s;
        int idx;
        for (idx = 0; *c != '\0'; idx++) {
            args[idx] = c;
            for (; *c != ' ' && *c != '\n'; c++);
            *c++ = '\0';
            printf("Argument je: %d %s\n", idx, args[idx]);
        }
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid < 0)  {
            fprintf(stderr, "Desila se greska");
        }
        else if (pid == 0) { // child process
            if (args[idx -1][0] == '&')
                args[idx-1] = NULL; // it shouldn't be passed to child process
            execvp(args[0], args);
            shouldRun = false;
            printf ("Dete gotovo\n");
            fflush(stdout);
        }
        else {
            if (args[idx-1][0] == '&') {
                    wait(NULL);
                }
            printf ("Glavna gotova\n");
        }
    }
    return 0;
}
