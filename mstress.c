#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

// Function to read the cycle count using rdtsc
static inline uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main(int argc, char *argv[]) {
    int opt;
    int num_chunks = 10;    // Default number of memory chunks
    size_t chunk_size = 1024; // Default chunk size in bytes
    int reverse = 0;        // Flag for reverse freeing
    int repeats = 1;

    // Parse command line arguments
    while ((opt = getopt(argc, argv, "n:s:i:r")) != -1) {
        switch (opt) {
            case 'n':
                num_chunks = atoi(optarg);
                break;
            case 's':
                chunk_size = atoi(optarg);
                break;
            case 'i':
                repeats = atoi(optarg);
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n num_chunks] [-s chunk_size] [-r]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    printf("Number of chunks: %d\n", num_chunks);
    printf("Size of each chunk: %zu bytes\n", chunk_size);
    printf("Freeing in reverse order: %s\n", reverse ? "Yes" : "No");

    // Allocate memory for storing chunk pointers
    void **chunks = malloc(num_chunks * sizeof(void *));
    if (chunks == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for(int r=0;r<repeats;r++) {
        // Measure allocation time for each chunk
        printf("Per allocation timing (in cycles):\n");
        for (int i = 0; i < num_chunks; i++) {
            uint64_t alloc_start = rdtsc();  // Start cycle count
            chunks[i] = malloc(chunk_size);
            uint64_t alloc_end = rdtsc();    // End cycle count

            if (chunks[i] == NULL) {
                fprintf(stderr, "Memory allocation for chunk %d failed\n", i);
                exit(EXIT_FAILURE);
            }

            printf("  Allocated Chunk %d: %lu cycles\n", i, alloc_end - alloc_start);
        }

        // Measure free time for each chunk
        printf("Per free timing (in cycles):\n");
        if (reverse) {
            for (int i = num_chunks - 1; i >= 0; i--) {
                uint64_t free_start = rdtsc();  // Start cycle count
                free(chunks[i]);
                uint64_t free_end = rdtsc();    // End cycle count
                printf("  Freed Chunk %d: %lu cycles\n", i, free_end - free_start);
            }
        } else {
            for (int i = 0; i < num_chunks; i++) {
                uint64_t free_start = rdtsc();  // Start cycle count
                free(chunks[i]);
                uint64_t free_end = rdtsc();    // End cycle count
                printf("  Freed Chunk %d: %lu cycles\n", i, free_end - free_start);
            }
        }
    }
    // Free the array of chunk pointers
    free(chunks);

    return 0;
}
