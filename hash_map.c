#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define DEFAULT_SIZE 100

extern uint64_t time33(char* str, size_t len);

typedef struct _hash_map_entry hash_map_entry;
typedef struct _hash_map hash_map;

struct _hash_map_entry
{
	char* key;
	int value;
	hash_map_entry *pre;
	hash_map_entry *next;
	hash_map_entry *hnext;
};

struct _hash_map
{
	int size;
	int used_size;
	double factor;

	hash_map_entry *head;

	hash_map_entry** map;	// 存储的具体数据的节点位置
	// hash_map_entry* list;	// 真实的数据存储, 为了达到使用固定内存的目的, 这个是否需要呢

	int(*get)(hash_map *map, char* str, size_t len, int value);
	int(*set)(hash_map *map, char* str, size_t len, int value);
	int(*delete)(hash_map *map,char* str);
	int(*index)(hash_map* map, char* str, size_t len);
	int(*each)(hash_map* map);
};

uint64_t hash_map_code(char* str, size_t len)
{
	return time33(str, len);
}

int hash_map_index(hash_map *map, char* str, size_t len)
{
	uint64_t hash_value = hash_map_code(str, len);
	return hash_value % map->size;
}

/*
 *
 */
int hash_map_get(hash_map *map, char* str, size_t len, int* out)
{
	int index = hash_map_index(map, str, len);
	hash_map_entry* entry = map->map[index];
	if (!entry)
	{
		return -1;
	}
	while (entry && strcmp(entry->key, str))
	{
		entry = entry->hnext;
	}
	if (!entry)
	{
		return -1;
	}
	*out = entry->value;
	return index;
}

int hash_map_delete(hash_map *map, char* str, size_t len)
{
	int index = hash_map_index(map, str, len);
	hash_map_entry* entry = map->map[index];
	if (!entry)
	{
		return 0;
	}
	while (entry && strcmp(entry->key, str))
	{
		entry = entry->hnext;
	}
	if (!entry) {
		return 0;
	}
	entry->next ? entry->next->pre = entry->pre : 1;
	entry->pre ? entry->pre->next = entry->next : 1;
	map->map[index] = entry->hnext;
	free(entry);
	return 1;
}

// 
int hash_map_entry_set(hash_map* map, hash_map_entry* new)
{
	int index = hash_map_index(map, new->key, strlen(new->key));
	hash_map_entry* entry = map->map[index];
	new->hnext = map->map[index];
	map->map[index] = new;
}

/*
 * return 0 不需要扩容, 1 扩容成功, -1 扩容失败
 */
int hash_map_scale(hash_map *map)
{
	if ((double)map->used_size / map->size < map->factor)
	{
		return 0;
	}
	hash_map_entry** map_list = calloc(sizeof(hash_map_entry*), map->size * 2);
	if (!map_list)
	{
		return -1;
	}
	free(map->map);
	map->map = map_list;
	hash_map_entry* entry = map->head;
	while (entry)
	{
		hash_map_entry_set(map, entry);
		entry = entry->next;
	}
	map->size = map->size * 2;
	return 1;
}

hash_map_entry* hash_map_init_entry(char* str, size_t len, int value, hash_map_entry* next)
{
	hash_map_entry* entry = malloc(sizeof(hash_map_entry));
	if (!entry)
	{
		return 0;
	}
	memset(entry, 0, sizeof(hash_map_entry));
	char *key = calloc(sizeof(char), len + 1);
	if (!key) {
		return 0;
	}
	memcpy(key, str, len);
	entry->key = key;
	entry->value = value;
	entry->next = next;
	return entry;
}

int hash_map_set(hash_map *map, const char* str, size_t len, int value)
{
	int index = hash_map_index(map, str, len);
	hash_map_entry* entry = map->map[index];
	if (!entry)
	{
		int  r = hash_map_scale(map);
		if (r < 0)
		{
			return r;
		}
	}
	while (entry && strcmp(entry->key, str))
	{
		entry = entry->hnext;
	}
	if (!entry)
	{		
		entry = hash_map_init_entry(str, len, value, map->head);
		if (!entry)
		{
			return 0;
		}
		map->map[index] = entry;
		map->head ? map->head->pre = entry : 1 ;
		map->head = entry;
		++map->used_size;
	} else {
		entry->value = value;
	}
	return 1;
}

void hash_map_each(hash_map* map)
{
	hash_map_entry* entry = map->head;
	while (entry)
	{
		printf("key: %s, value: %d\n", entry->key, entry->value);
		entry = entry->next;
	}
}

hash_map* init_hash_map()
{
	hash_map* map = malloc(sizeof(hash_map));
	if (!map)
	{
		return NULL;
	}
	hash_map_entry** map_list = calloc(sizeof(hash_map_entry*), DEFAULT_SIZE);
	if (!map)
	{
		return NULL;
	}
	map->map = map_list;
	map->size = DEFAULT_SIZE;
	map->used_size = 0;
	map->head = NULL;
	map->factor = 0.75;

	map->get = hash_map_get;
	map->set = hash_map_set;
	map->index = hash_map_index;
	map->delete = hash_map_delete;
	map->each = hash_map_each;
	return map;
}


void test_hash_map_delete(void)
{
	hash_map* map = init_hash_map();
	char str[] = "acfa";
	for (char i = 'a'; i <= 'z'; i++)
	{
		int value;
		int error;
		map->set(map, str, sizeof(str) - 1, (int)i);

		map->delete(map, str, sizeof(str) -1);

		error = map->get(map, str, sizeof(str) - 1, &value);
		assert(error == -1);
		str[0] += 1;
	}
}

void test_hash_map_get(void)
{
	hash_map* map = init_hash_map();
	map->set(map, "a", 1, 'a');
	int value;
	int error;
	error = map->get(map, "a", 1, &value);
	assert(error >= 0);
	assert(value == 'a');
}

void test_hash_map_set(void)
{
	hash_map* map = init_hash_map();
	char str[] = "acfa";
	for (char i = 'a'; i <= 'z'; i++)
	{
		int value;
		int error;
		map->set(map, str, sizeof(str) - 1, (int)i);
		error = map->get(map, str, sizeof(str) - 1, &value);
		assert(error >= 0);
		assert(value == (int)i);
		str[0] += 1;
	}
}

void test_hash_map(void)
{
	test_hash_map_delete();
	test_hash_map_get();
	test_hash_map_set();
}



