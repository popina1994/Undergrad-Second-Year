#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

constexpr int BUFFER_SIZE = 25, READ_END = 0, WRITE_END = 1;
constexpr int FILE_DESCRIPTORS = 2, ENDS = 2;


int main() {
    char writeMsg[BUFFER_SIZE] = "Hi There";
    char readMsg[BUFFER_SIZE];
    int fileDescriptor[FILE_DESCRIPTORS][ENDS];


    if ( (pipe(fileDescriptor[0]) == -1) || (pipe(fileDescriptor[1]) == -1 ) ){
        cerr << "Creating pipe failed" << endl;
        exit(1);
    }
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Error in creating child process" << endl;
        exit(2);
    }
    if (pid > 0) {
        close(fileDescriptor[0][READ_END]); // pipe for passing data to child process
        close(fileDescriptor[1][WRITE_END]); // pipe for recieving data from child process


        // passes message to child process
        write(fileDescriptor[0][WRITE_END], writeMsg, strlen(writeMsg) + 1);

        // it finished passing message  to child process
        close(fileDescriptor[0][WRITE_END]);

        // wait for reveresed message from child process
        read(fileDescriptor[1][READ_END], readMsg, BUFFER_SIZE);

        // close read mode from child process
        close(fileDescriptor[1][READ_END]);

        cout << "Reveresed message is " << readMsg << endl;
    }
    else {
        close(fileDescriptor[0][WRITE_END]);
        close(fileDescriptor[1][READ_END]);

        // reads message from parent process
        read(fileDescriptor[0][READ_END], readMsg, BUFFER_SIZE);

        // it finished passing message from parent process
        close(fileDescriptor[0][READ_END]);

        // switch case of letters in message sent from child process
        for (unsigned idx = 0; idx < strlen(readMsg) + 1; idx ++)
            if ( (readMsg[idx] >= 'A') && (readMsg[idx] <= 'Z') )
                writeMsg[idx] = readMsg[idx] -  'A' + 'a';
            else if ( (readMsg[idx] >= 'a') && (readMsg[idx] <= 'z') )
                writeMsg[idx] = readMsg[idx] -  'a' + 'A';
            else
                writeMsg[idx] = readMsg[idx];

        // passes reveresed message to parent process
        write(fileDescriptor[1][WRITE_END], writeMsg, strlen(writeMsg) + 1);

        // close write mode to parent proecess
        close(fileDescriptor[1][WRITE_END]);
    }
    return 0;
}
