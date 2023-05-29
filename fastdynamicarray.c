#include "fastdynamicarray.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define END_OBJECT FDA_END_OBJECT

// To simplify, we use this as a list of the end object
typedef END_OBJECT* subarray;

// Optimized 32-bit power results used in this data structure
const uint32_t POWs[34] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648};

// Quick function to allocate an "subarray" into the memory
static inline subarray new_subarray(size_t size) {
    return (subarray) malloc(sizeof(END_OBJECT) * size);
}

/**
 * Fast Dynamic Subarrays
 */
typedef struct fda{
    uint32_t roots_length;
    uint32_t capacity;
    subarray* subarrays;
} FastDynamicArray;

// Debug for me
void debug_roots(FastDynamicArray* array) {
    printf("Roots length: %i\n", array->roots_length);
    for(uint32_t i = 0; i < array->roots_length; i++) {
        printf("  Root %i: %s\n", i, array->subarrays[i] != NULL ? "Built" : "Null");
    }
}


FastDynamicArray* fda_new_array() {
    FastDynamicArray* fda = (FastDynamicArray*) malloc(sizeof(FastDynamicArray));
    fda->roots_length = 0;
    fda->capacity = 0;
    fda->subarrays = NULL;
    return fda;
}

void fda_free(FastDynamicArray* array) {
    for(uint32_t i = 0; i < array->roots_length; i++)
        free(array->subarrays[i]);
    free(array);
}

void add_roots(FastDynamicArray* array, uint32_t add) {
    uint32_t old_root_size = array->roots_length;
    subarray* new_subarray = calloc(add + old_root_size, sizeof(subarray));
    memcpy(new_subarray, array->subarrays, sizeof(subarray) * old_root_size);
    array->roots_length += add;
    free(array->subarrays);
    array->subarrays = new_subarray;
}

// Frees memory, this does not reduce count of roots as there are so few root nodes that can exist
void pop_roots(FastDynamicArray* array, uint32_t remove) {
    if(remove > array->roots_length)
        remove = array->roots_length;
    uint32_t i, j;
    for(i = array->roots_length, j = remove; j >= 0; i--, j--) {
        if(array->subarrays[i]) {
            free(array->subarrays[i]);
            array->subarrays[i] = NULL;
        }
    }
}

// Quicker way than using the standard library to find floor of log2 of n.
static inline uint32_t floorlog2(uint32_t n) {
    uint32_t res = 0;
    if(n >= 65536) { n >>= 16; res += 16;}
    if(n >= 256)   { n >>= 8;  res += 8; }
    if(n >= 16)    { n >>= 4;  res += 4; }
    if(n >= 8)     { n >>= 2;  res += 2; }
    if(n >= 4)     { n >>= 1;  res += 1; }
    if(n >= 2)     {           res += 1; }
    return res;
}

// Calculates the root index from index
static inline uint32_t calculate_root(uint32_t index) {
    if(!index)
        return 0;
    return (uint32_t) floorlog2(index) + 1;
}


// Tells how long an subarray should be
static inline uint32_t calculate_root_length(uint32_t root_index) {
    if(!root_index)
        return 1;
    return (uint32_t) POWs[root_index];
}

// Finds out the index we need to use in our subarray
static inline uint32_t calculate_subindex(uint32_t index) {
    if(!index)
        return 0;
    uint32_t root_index = calculate_root(index);
    return index % POWs[root_index];
}

void debug_algorithms(int high) {
    printf("Calculate roots:\n");
    for(int i = 0; i < high; i++) {
        printf("  calc root(%i): %i\n", i, calculate_root(i));
    }
    printf("\nCalculate subindexes:\n");
    for(int i = 0; i < high; i++) {
        printf("  calc subindex(%i): %i (root: %i)\n", i, calculate_subindex(i), calculate_root(i));
    }
    printf("\nCalculate root length:\n");
    for(int i = 0; i < high; i++) {
        printf("  calc root length(%i): %i\n", i, calculate_root_length(i));
    }
}

void debug_array(FastDynamicArray* array) {
    printf("Capacity: %i\n", array->capacity);
    uint32_t root_index, subindex, subarray_length, k = 0;
    for(uint32_t i = 0; i < array->roots_length; i++) {
        subarray_length = calculate_root_length(i);
        if(array->subarrays[i] == NULL) {
            printf("  Root[%i]: Null\n", i);
        } else {
            printf("  Root[%i]:\n", i);
            subarray s = array->subarrays[i];
            for(uint32_t j = 0; j < subarray_length; j++, k++) {
                if(k >= array->capacity) {
                    printf("END OF CAPACITY! Rest is random claimed memory!\n");
                    return;
                }
                printf("    %i: %i\n", k, s[j]);
                
            }
        }
    }
}


// Resizes the array, in this case, the worst-ever case would be O(log(n)), which is the point of this library
void fda_push_back(FastDynamicArray* array, END_OBJECT value) {
    uint32_t root_index = calculate_root(array->capacity);
    if(root_index >= array->roots_length)
        add_roots(array, root_index - array->roots_length + 1);
    if(!array->subarrays[root_index])
        array->subarrays[root_index] = new_subarray(calculate_root_length(root_index));
    uint32_t subindex = calculate_subindex(array->capacity);
    subarray root = array->subarrays[root_index];
    END_OBJECT test = root[subindex];
    root[subindex] = value;
    array->capacity++;
}

void fda_set(FastDynamicArray* array, uint32_t index, END_OBJECT value) {
    if(index >= array->capacity)
        return;
    uint32_t root_index = calculate_root(index);
    uint32_t subindex   = calculate_subindex(index);
    subarray s = array->subarrays[root_index];
    s[subindex] = value;
}

END_OBJECT fda_get(FastDynamicArray* array, uint32_t index) {
    if(index >= array->capacity)
        return 0;
    uint32_t root_index = calculate_root(index);
    uint32_t subindex   = calculate_subindex(index);
    subarray s = array->subarrays[root_index];
    return s[subindex];
}
    

#undef END_OBJECT