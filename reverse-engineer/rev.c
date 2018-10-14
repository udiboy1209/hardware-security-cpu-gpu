#include<stdio.h>
#include<stdlib.h>
#include<x86intrin.h>

int main(int argc, char** argv) {
    int array_start;
    int array_end;
    int stride;

    //printf("%d %s\n", argc, argv[1]);
    if(argc < 4) exit(1);
    sscanf(argv[1], "%d", &array_start);
    sscanf(argv[2], "%d", &array_end);
    sscanf(argv[3], "%d", &stride);

    size_t* straccess;
    //unsigned long long timing[array_end];
    unsigned long long tdiff;

    int i, j, tstride = stride/sizeof(size_t), t, ui;
    size_t* next;

    for(i = array_start; i < array_end; i+=1) {
        straccess = malloc(sizeof(size_t) * i);

        for(j = 0; j < i; j ++) {
            t = j + tstride;
            if(t >= i) t %= tstride;
            straccess[j] = ((size_t)straccess) + sizeof(size_t)*t;
        }

        next = straccess;
        tdiff = __rdtsc();
        for(j = 0; j < 65536; j++) {
            next = *((size_t**)next);
        }
        tdiff = __rdtsc() - tdiff;
        //timing[i] = tdiff;
	printf("%d %ld\n", i*sizeof(size_t), tdiff);

	free(straccess);
    }
}
