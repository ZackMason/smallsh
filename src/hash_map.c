#include "hash_map.h"
#include <assert.h>

u64 hash_function(char* str)
{
    u64 i = 0;
    for (int j = 0; str[j];j++)
	i += str[j];
    return i;
}

struct HashNode* hash_node_create(char* key, void* data, size_t size)
{
    HashNode* new = calloc(1, sizeof(HashNode));
    new->key = malloc(strlen(key)+1);
    new->value = data;

    strcpy(new->key, key);
    //memcpy(new->value, data, size);

    return new;
}

void hash_node_free(HashNode* node)
{
    free(node->key);
//    free(node->value);
    free(node);
}

void hash_map_free(HashMap* map)
{
    for(int i = 0; i < map->size;i++)
    {
	HashNode* node = map->table[i];
	if(node)
	    hash_node_free(node);
    }
    free(map->table);
    free(map);
}


struct HashMap* hash_map_create(u32 size, u32 data_size)
{
    HashMap* new = calloc(1, sizeof(HashMap));
    new->size = size;
    new->data_size = data_size;
    new->count = 0;
    new->hash_func = hash_function;
    
    new->table = calloc(new->size, sizeof(HashNode*));
    
    return new;
}

i8 hash_map_has(HashMap* map, char* key)
{
    u64 index = map->hash_func(key);

    return !!map->table[index%map->size];
}

void* hash_map_get(HashMap* map, char* key)
{
    u64 index = map->hash_func(key);
    HashNode* node = map->table[index%map->size];
    
    return node && node->hash == index && strcmp(node->key, key)==0 ? node->value : NULL;
}

void hash_map_remove(HashMap* map, char* key)
{
}

void hash_map_add(HashMap* map, char* key, void* data, size_t data_size)
{
    u64 index = map->hash_func(key);

    HashNode* node = map->table[index%map->size];
    if (node)
    {
	// colllision
	assert("ohono");
    }
    
    map->table[index%map->size] = hash_node_create(key, data, data_size);

    node = map->table[index%map->size];
    node->hash = index;
    
}

void hash_map_emplace(char* key, void* value)
{
}

void hash_map_double(HashMap* map)
{
    map->size *= 2;
    
}
