#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>

// Count how many times threads are called
#define THREADS 4
int ptime = 0;
pthread_mutex_t mutex;

void* function(void* arg) {
    pthread_t k = pthread_self();
    int* a = (int*)arg;
    int b = *a;
    int *s = new int;
    *s = 0;
    for (int i = b; i < (b + 2); i++) {
        *s += i;
    }

    pthread_mutex_lock(&mutex);
    ptime++;
    printf("In thread1, pid = %lu, with output = %d\n", (unsigned long)k, b);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    pthread_mutex_unlock(&mutex);
    pthread_exit((void*)s);
}

int main() {
    pthread_t tid[THREADS];
    int ret;
    int val[THREADS];
    int a[THREADS];
    for (int i = 0; i < THREADS; i++) a[i] = i;
    for (int i = 0; i < THREADS; i++) {
        ret = pthread_create(&tid[i], NULL, function, (void*)&a[i]);   
    }

    int* s;
    for (int i = 0; i < THREADS; i++) {
        ret = pthread_join(tid[i], (void**)& s);
        val[i] = *s;
    }

    for (int i = 0; i < THREADS; i++) {
        std::cout << val[i] << '\n';
    }
    printf("Total threads called time: %d\n", ptime);
    delete s;
    return 0;
}
