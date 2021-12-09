#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_FILE "hash.txt"

typedef char *string;

FILE *fp;

struct alphasWithNum {
    char alpha[32];
    char code[32];
};

typedef struct alphasWithNum t_alpha;