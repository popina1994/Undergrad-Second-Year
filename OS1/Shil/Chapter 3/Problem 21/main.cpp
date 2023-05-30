#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argC, char *argV[]) {
    if (argC != 2) {

        cerr << argC << "is wrong number of arguments" << endl;
        exit(1);
    }

    int n = atoi(argV[1]);
    if (n < 0) {
        cerr << "Negative number is not allowed" << endl;
        exit(2);
    }

    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Error in creating process" << endl;
        exit(3);
    }

    if (pid > 0) {
        wait(nullptr);
        cout << "Program finished successfully" << endl;
        exit(0);
    }
    else {
        while (n > 1) {
            cout << n << " ";
            if (n % 2 == 0)
                n /= 2;
            else
                n = 3 * n + 1;
        }
        cout << n << endl;
    }


    return 0;
}
