#include <pthread.h>
#include <iostream>
#include <stdio.h>

// Count how many times threads are called
int ptime = 0;
pthread_mutex_t mutex;

void* function1(void* arg) {
    pthread_t k = pthread_self();
    int* a = (int*)arg;
    int b = *a;
    int *s = new int;
    *s = 0;
    for (int i = b; i < (b + 2); i++) {
        *s += i;
    }
    printf("In thread1, pid = %lu\n", (unsigned long)k);

    pthread_mutex_lock(&mutex);
    ptime++;
    pthread_mutex_unlock(&mutex);
    pthread_exit((void*)s);
}

void* function2(void* arg) {
    pthread_t k = pthread_self();
    int* a = (int*)arg;
    int b = *a;
    int* s = new int;
    *s = 0;
    for (int i = b; i < (b + 3); i++) {
        *s += i;
    }
    printf("In thread2, pid = %lu\n", (unsigned long)k);
    pthread_mutex_lock(&mutex);
    ptime++;
    pthread_mutex_unlock(&mutex);
    pthread_exit((void*)s);
}

int main() {
    pthread_t tid1;
    pthread_t tid2;
    int m1 = 1, m2 = 2;
    int* a1 = &m1;
    int* a2 = &m2;
    int ret;

    ret = pthread_create(&tid1, NULL, function1, (void*)a1);
    ret = pthread_create(&tid2, NULL, function2, (void*)a2);

    int* s1;
    int* s2;
    ret = pthread_join(tid1, (void**)& s1);
    ret = pthread_join(tid2, (void**)& s2);
    std::cout << *s1 << std::endl;
    std::cout << *s2 << std::endl;
    printf("Total threads called time: %d\n", ptime);
    delete s1;
    delete s2;
    return 0;
}
