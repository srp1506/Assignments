#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
typedef long long int ll;

int base = 61;
ll p_key;
double max = 9999999999;
int* p_key_converted;

typedef struct node  {

	ll key;
	char* f_name;
	char* email;
	char* gender;
	struct node* next;
}node;

node* Init_node(ll key, char* fname, char* email, char* gender) {

	node* new = (node*)malloc(sizeof(node));
	new->key = key;
	new->f_name = strdup(fname);
	new->email = strdup(email);
	new->gender = strdup(gender);
	new->next = NULL;
	return new;
}

int* Convert (ll key, int digits) {

	int* array = (int*)malloc(base * sizeof(int));

	for (int i = 0 ; i < digits ; i++) {

		if (key) {

			array[i] = key % base;
			key = key / base;
		}

		else array[i] = 0;
	}

	return array;
}

int Hash (ll key, int* p_key_converted, int digits) {

	int pos = 0;
	int* key_converted = Convert(key, digits);

	for (int i = 0 ; i < digits ; i++) pos += p_key_converted[i] * key_converted[i];

	return pos % base;
}

void Insert (node* new, int* p_key_converted, node** data, int digits) {

	int pos;
	pos = Hash(new->key, p_key_converted, digits);

	if (data[pos] == NULL) data[pos] = new;

	else {

		node* trav;
		trav = data[pos];

		while (trav->next != NULL) trav = trav->next;

		trav->next = new;
	}
}

int Search (int key, node** data, int digits) {

	int pos;
	node* trav;
	pos = Hash(key, p_key_converted, digits);
	trav = data[pos];

	while (trav != NULL) {

		if (trav->key == key) return 1;
		trav = trav->next;	
	}

	return 0;
}

void Delete (int key, node** data, int digits) {

	int pos;
	node* trav;
	pos = Hash(key, p_key_converted, digits);
	trav = data[pos];	

	while (trav != NULL && trav->next != NULL) {

		if (trav->next->key == key) {

			node* temp = trav->next;
			trav->next = temp->next;
			free(temp);
			return;
		}

		trav = trav->next;
	}

	printf("Key not present\n");
}

void Print_histogram (node** data) {

	int total;
	total = 0 ;
	printf("Histogram of Entries:\n\n");

	for (int i = 0 ; i < base ; i++) {

		int count = 0;
		node* current = data[i];

		printf("\nList %d : ", i + 1);

		if (current != NULL) printf("Header Node : key = %lld, First Name = %s, Email = %s, Gender = %s", current->key, current->f_name, current->email, current->gender);

		while (current != NULL) {
			count++;
			total++;
			current = current->next;
		}

		for (int j = 0 ; j < count ; j++) printf("*");

		printf("\n(%d entries)\n\n", count);
	}

	printf("\n(%d total entries)\n", total);
}

int main() {

	FILE* file = fopen("Data.csv", "r");
	node* data[base];
	srand(time(0));
	int digits;
	digits = ceil(log(max)/log(base));
	p_key = rand() % 9000000000 + 1000000000;
	p_key_converted = Convert(p_key, digits);

	for (int i = 0 ; i < base ; i++) data[i] = NULL;


	char line[1024];
	fgets(line, sizeof(line), file);

	while (fgets(line, sizeof(line), file)) {

		char *token;

		token = strtok(line, ",");
		token = strtok(NULL, ",");

		if (token == NULL) continue;

		ll key = atoll(token);

		token = strtok(NULL, ",");

		if (token == NULL) continue;

		char* fname = token;

		token = strtok(NULL, ",");

		if (token == NULL) continue;

		char* email = token;

		token = strtok(NULL, ",");

		if (token == NULL) continue;

		char* gender = token;

		node* new = Init_node(key, fname, email, gender);
		Insert(new, p_key_converted, data, digits);
	}
	Print_histogram(data);
	fclose(file);
	return 0;
}
