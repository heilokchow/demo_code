#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>

// Count how many times threads are called
#define THREADS 4
int ptime = 0;
pthread_mutex_t mutex;

struct cal {
    int i;
    int s;
};

void* function(void* arg) {
    pthread_t k = pthread_self();
    cal* a = (cal*)arg;
    int b = a->i;
    int s = 0;
    for (int i = b; i < (b + 2); i++) {
        s += i;
    }
    a->s = s;

    pthread_mutex_lock(&mutex);
    ptime++;
    // printf("In thread1, pid = %lu, with output = %d\n", (unsigned long)k, *s);
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    pthread_mutex_unlock(&mutex);
    // pthread_exit((void*) s);
}

int main() {
    pthread_t tid[THREADS];
    int ret;
    cal val[THREADS];
    
    for (int i = 0; i < THREADS; i++) val[i].i = i;
    for (int i = 0; i < THREADS; i++) {
        ret = pthread_create(&tid[i], NULL, function, (void*)&val[i]);   
    }

    // int* s;
    for (int i = 0; i < THREADS; i++) {
        ret = pthread_join(tid[i], NULL);
        // printf("%lu with value: %d\n", (unsigned long)s, *s);
        // val[i] = *s;
        // delete s;
    }

    for (int i = 0; i < THREADS; i++) {
        std::cout << val[i].s << '\n';
    }
    printf("Total threads called time: %d\n", ptime);
    return 0;
}
