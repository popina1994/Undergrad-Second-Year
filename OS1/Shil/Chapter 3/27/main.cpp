#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstring>
using namespace std;

constexpr int ENDS = 2, BUFFER_SIZE = 30, ARG_READ = 1, ARG_WRITE = 2;
constexpr int READ_END = 0, WRITE_END = 1;

int main(int argC, char* argV[]) {
    int fileDescriptor[ENDS];
    char readMsg[BUFFER_SIZE + 1] = {0}, writeMsg[BUFFER_SIZE + 1] = "Mama";

    if (pipe(fileDescriptor) == -1) {
        cerr << "Error in piping" << endl;
        return 2;
    }

    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Error in creating process" << endl;
        return 1;
    }

    if (pid > 0) {
        close(fileDescriptor[READ_END]);

        FILE* fRead = fopen(argV[ARG_READ], "r");
       if (fRead == nullptr) {
            cerr << "Error in opening file / wrong name of file" << endl;
            close(fileDescriptor[WRITE_END]);
            exit(3);
        }

        char c;
        int cnt = 0;
        while (fscanf(fRead, "%c", &c) == 1) {
            writeMsg[cnt++] = c;
            if (cnt == BUFFER_SIZE) {
                write(fileDescriptor[WRITE_END], writeMsg, BUFFER_SIZE + 1);
                cnt = 0;
            }
        }

        // last reading from file wasn't multiplier of BUFFER_SIZE
        if (cnt != 0) {
            writeMsg[cnt] = '\0';
            write(fileDescriptor[WRITE_END], writeMsg, strlen(writeMsg) + 1);
        }
        close(fileDescriptor[WRITE_END]);
        fclose(fRead);

    }
    else if (pid == 0) { // child process
        close(fileDescriptor[WRITE_END]);

        FILE* fWrite = fopen(argV[ARG_WRITE], "w");
        if (fWrite == nullptr) {
            cerr << "Error in opening file" << endl;
            close(fileDescriptor[READ_END]);
            exit(3);
        }
        while (read(fileDescriptor[READ_END], readMsg, BUFFER_SIZE + 1) != 0)
            fprintf(fWrite, "%s", readMsg);

        close(fileDescriptor[READ_END]);
        fclose(fWrite);
    }



    return 0;
}
