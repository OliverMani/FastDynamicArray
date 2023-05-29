#ifndef FAST_DYNAMIC_ARRAY_H
#define FAST_DYNAMIC_ARRAY_H

#include <stdint.h>

#define FDA_END_OBJECT void*

/**
 * The data structure the library is about, it is similar to a dynamic array, where the worst case time complexity for resizing is O(log(n)) instead of O(n).
 * This is done by splitting the array into multiple different arrays, that we can call "subarrays", and keep the memory addresses of the "subarrays" in a array
 * we can call "roots array", so when we need to resize the array, we just resize the "roots array" and memory allocate a new subarray.
 * The struct also keeps track of how many roots are in the array and how many nodes are being used (capacity).
*/
typedef struct fda FastDynamicArray;

/**
 *  Returns the value of index from array, time complexity: O(1)
 *  The function is a bit slower than accessing from a regular array due to calculations but the calculations should be almost as fast as accessing from an regular array.
 */
FDA_END_OBJECT fda_get(FastDynamicArray* array, uint32_t index);

/**
 * Sets a value to the array, using the index
*/
void  fda_set(FastDynamicArray* array, uint32_t index, FDA_END_OBJECT value);

/**
 * Resizes the array, in this case, the worst-ever case would have the time complexity of O(log(n)), which is the point of this library
*/
void  fda_push_back(FastDynamicArray* array, FDA_END_OBJECT value);

/**
 * Removes the array object from the memory.
*/
void  fda_free(FastDynamicArray* array);
#endif