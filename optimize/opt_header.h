#ifndef FDA_OPTIMIZATION_HEADER
#define FDA_OPTIMIZATION_HEADER
#include "../fastdynamicarray.h"
#include <stdint.h>

extern const uint32_t POWs[32];
extern uint32_t floorlog2(uint32_t n);
extern void* fda_asm_get(FastDynamicArray* array, uint32_t n);
extern uint32_t calculate_root_length(uint32_t root_index);
extern uint32_t calculate_subindex(uint32_t index);
extern uint32_t calculate_root(uint32_t index);
#endif