#ifndef _HASH_MAP_H
#define _HASH_MAP_H

#include "core.h"

u64 hash_function(char* str);

typedef struct HashNode {
    void* value;
    char* key;
    u64 hash; // for fast comparision
    //struct HashNode* next;
} HashNode;

typedef struct HashMap {
    u64 (*hash_func)(char*);

    size_t data_size;
    u32 count;
    u32 size;
    struct HashNode** table;
    
} HashMap;

struct HashNode* hash_node_create(char* key, void* value, size_t size);

void hash_node_free(HashNode* node);

struct HashMap* hash_map_create(u32 size, u32 data_size);
i8 hash_map_has(HashMap* map, char* key);
void* hash_map_get(HashMap* map, char* key);
void hash_map_remove(HashMap* map, char* key);
void hash_map_add(HashMap* map, char* key, void* data, size_t data_size);
void hash_map_emplace(char* key, void* value);
void hash_map_double(HashMap* map);
void hash_map_free(HashMap* map);


#endif
