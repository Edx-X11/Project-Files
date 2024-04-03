#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_THREADS 4
#define FILE_URL "http://example.com/file_to_download.txt"
#define MAX_RETRY 3
#define RETRY_DELAY 5

typedef struct {
    long startByte;
    long endByte;
    int threadId;
} ThreadData;

void* downloadFile(void* data) {
    ThreadData* threadData = (ThreadData*)data;
    int retryCount = 0;
    char command[100];
    while (retryCount < MAX_RETRY) {
        sprintf(command, "curl -o part_%d.txt --range %ld-%ld %s", threadData->threadId, threadData->startByte, threadData->endByte, FILE_URL);
        int status = system(command);
        if (status == 0) {
            pthread_exit(NULL);
        } else {
            printf("Thread %d failed to download. Retrying...\n", threadData->threadId);
            sleep(RETRY_DELAY);
            retryCount++;
        }
    }
    printf("Thread %d exceeded maximum retry limit. Exiting...\n", threadData->threadId);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];
    long fileSize = 1000000; // Example file size in bytes
    long bytesPerThread = fileSize / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].startByte = i * bytesPerThread;
        threadData[i].endByte = (i + 1) * bytesPerThread - 1;
        threadData[i].threadId = i;
        pthread_create(&threads[i], NULL, downloadFile, (void*)&threadData[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("File downloaded successfully!\n");
    return 0;
}
