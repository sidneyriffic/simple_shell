#ifndef ALIASH
#define ALIASH
/**
 * struct AliasData - struct for alias function
 * @AliasData - name of struct
 * @name: name of alias value
 * @val: value for alias
 * @next: ptr to next node
 */
typedef struct AliasData
{
	char *name;
	char *val;
	struct AliasData *next;
} AliasData;

#endif
