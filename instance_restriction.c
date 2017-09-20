#include "instance_restriction.h"

bool ReachedMaximumInstance()
{
    for (int i = 0;; i++)
    {
        // Concat file location.
        char *path = (char *)malloc((strlen(LOCK_PREFIX) + strlen(LOCK_SUFFIX) + MAX_INSTANCE_DIGITS) * sizeof(char));

        char i_char[MAX_INSTANCE_DIGITS];
        sprintf(i_char, "%d", i);

        strcpy(path, LOCK_PREFIX);
        strcat(path, i_char);
        strcat(path, LOCK_SUFFIX);

        // Check if there are locks.
        int fd = open(path, O_RDONLY);
        if (fd > 0)
        {
            // One or more locks exist.
            pid_t maybePid;
            read(fd, &maybePid, sizeof(maybePid));

            // Lock exists already, check if process still exists.
            if (kill(maybePid, 0) == 0)
            {
                if (i >= MAX_INSTANCE - 1)
                {
                    free(path);
                    return true;
                }
                close(fd);
            }
            // Lock exists already, process has been terminated.
            else if (errno == ESRCH)
            {
                // Remove deprecated lock.
                remove(path);

                // Create new lock.
                int fd2 = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
                pid_t currentPid = getpid();
                write(fd2, &currentPid, sizeof(currentPid));

                free(path);
                return false;
            }
            else
            {
                // Unknown other error, check for errno.
                perror("Unknown process error.");
            }
        }
        else
        {
            // Lock does not exist. Create new lock.
            int fd2 = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
            pid_t currentPid = getpid();
            write(fd2, &currentPid, sizeof(currentPid));

            free(path);
            return false;
        }
        free(path);
    }
}
