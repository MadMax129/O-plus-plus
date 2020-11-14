/** @file memory.h
 * 
 * @brief Memory pool implementation
 *      
 * Copyright (c) 2020 Maks S
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */ 

#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#define BLOCK_SIZE 64000

struct Block_Header {
    struct Block_Header *next;
    char *block, *free, *end;
};

struct Allocator {
	size_t used_mem;
    struct Block_Header* first;
    struct Block_Header* current;
};

bool allocator_init();
char* alloc(size_t size);
void allocator_free();
void allocator_reset();