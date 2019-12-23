#define __HASH_SIZE__ 10000

enum Types {
	INT, CONST_INT, CONST_FLOAT, 
	FLOAT, FUNC, STRING
};

struct Hash_Node {
	enum Types type;
	char key[20];
	union {
		int v1;
		double v2;
		char* v3;
	};
	struct Hash_Node *next;
};

struct Table {
	int size;
	struct Hash_Node **list;
};

struct Table* map;

unsigned long hash_str(char *string);
struct Table* createMap();
void free_table(struct Table* t);
void delete_node(struct Table* t, char* key);


int insert_str(struct Table *t, char* key, char* value);
int insert_int(struct Table *t, char* key, int value);
int insert_float(struct Table *t, char* key, double value);

enum Type check_type(struct Table *t, char *key);

int lookup(struct Table* t, int hash);