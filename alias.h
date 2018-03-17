#ifndef ALIASH
#define ALIASH

typedef struct AliasData
{
	char *name;
	char *val;
	struct AliasData *next;
} AliasData;

#endif
