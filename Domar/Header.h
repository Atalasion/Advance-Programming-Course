#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_USERNAME_SIZE 20
#define MAX_ID_SIZE 20
#define MAX_PASSWORD_SIZE 20
#define MAX_INPUT_LEN 40
#define ADMIN_STRING "admin\0"
#define LOGIN_STRING "login\0"
#define SIGNUP_STRING "signup"

// define user
struct user {
	char username[MAX_USERNAME_SIZE];
	int id;
	char password[MAX_PASSWORD_SIZE];
};

// define hall
struct hall {
	char name[MAX_USERNAME_SIZE];
	int id, capacity;
};

//define food
struct food {
	char name[MAX_USERNAME_SIZE];
	int id, price, capacity, hall_id, day;
};

//define coupon
struct coupon {
	int id, percentage, capacity;
};

int compare_string(char *a, char *b) {
	if ((a[0] == '\0' || a[0] == '\n') && (b[0] == '\0' || b[0] == '\n')) {
		return 1;
	}
	if (a[0] != b[0]) return 0;
	return compare_string(a + 1, b + 1);
}

int compare_add_hall(char *input) {
	char *cmp = "add_hall\0";
	return compare_string(cmp, input);
}

int compare_login(char *input) {
	char *cmp = "login\0";
	return compare_string(cmp, input);
}

int compare_logout(char *input) {
	char *cmp = "logout\0";
	return compare_string(cmp, input);
}

int compare_add_food(char *input) {
	char *cmp = "add_food\0";
	return compare_string(cmp, input);
}

int compare_signup(char *input) {
	char *cmp = "signup\0";
	return compare_string(cmp, input);
}

int compare_add_coupon(char *input) {
	char *cmp = "add_coupon\0";
	return compare_string(cmp, input);
}

// initialize string
void Reset(char *a, int n) {
	for (int i = 0; i < n; i++) a[i] = NULL;
	return;
}

// check if two strings are equal

struct user* read_users(struct user *users, int *user_counter) {
	FILE *input = fopen("users.txt", "r");
	if (input == NULL) return users;
	int flag = 0;
	// reading input
	while (fgetc(input) != EOF) {
		// change size of array
		(*user_counter)++;
		users = (struct user*)realloc(users, (*user_counter) * sizeof(struct user));
		if (users == NULL) exit(0);
		//initialize
		for (int i = 0; i < MAX_USERNAME_SIZE; i++) {
			users[(*user_counter) - 1].password[i] = NULL;
			users[(*user_counter) - 1].username[i] = NULL;
		}
		fseek(input, -1, SEEK_CUR);
		int pnt = 0;
		//input username
		while (fgetc(input) != ' ') {
			fseek(input, -1, SEEK_CUR);
			users[*user_counter - 1].username[pnt++] = fgetc(input);
		}
		//input id
		int cur = 0;
		while (fgetc(input) != ' ') {
			fseek(input, -1, SEEK_CUR);
			cur = cur * 10 + (fgetc(input) - '0');
		}
		users[*user_counter - 1].id = cur;
		//input password
		pnt = 0;
		while (TRUE) {
			char c = fgetc(input);
			if (c != '\n') {
				users[(*user_counter) - 1].password[pnt++] = c;
				if (fgetc(input) == EOF) {
					flag = 1;
					break;
				}
				else {
					fseek(input, -1, SEEK_CUR);
				}
			}
			else {
				break;
			}
		}
	}
	fclose(input);
	// put \n end of file
	if (flag) {
		FILE *output = fopen("users.txt", "w");
		fprintf(input, "\n");
		fclose(output);
	}
	return users;
}

struct user* user_signup(struct user *users, int *user_counter) {
	// change array's size
	(*user_counter)++;
	users = (struct user*)realloc(users, (*user_counter) * sizeof(struct user));
	if (users == NULL) exit(0);
	//initialize
	for (int i = 0; i < MAX_USERNAME_SIZE; i++) {
		users[(*user_counter) - 1].password[i] = NULL;
		users[(*user_counter) - 1].username[i] = NULL;
	}
	//input 
	char input_id[MAX_ID_SIZE];
	Reset(input_id, MAX_ID_SIZE);
	scanf("%s", users[(*user_counter) - 1].username);
	scanf("%s", input_id);
	scanf("%s", users[(*user_counter) - 1].password);
	// change string to int
	int cur = 0;
	for (int i = 0; i < MAX_ID_SIZE; i++) {
		if (input_id[i] == NULL) break;
		cur = cur * 10 + (input_id[i] - '0');
	}
	users[(*user_counter) - 1].id = cur;
	//check if user alreay exists
	for (int i = 0; i < (*user_counter) - 1; i++) {
		if (compare_string(users[i].username, users[(*user_counter) - 1].username) || users[i].id == users[(*user_counter) - 1].id) {
			(*user_counter)--;
			printf("user already exists\n");
			users = (struct user*)realloc(users, (*user_counter) * sizeof(struct user));
			if (users == NULL) exit(0);
			return users;
		}
	}
	// write user on file
	FILE *output = fopen("users.txt", "a");
	// write username
	for (int i = 0; i < MAX_USERNAME_SIZE; i++) {
		if (users[(*user_counter) - 1].username[i] == NULL) {
			fputc(' ', output);
			break;
		}
		fputc(users[(*user_counter) - 1].username[i], output);
	}
	// write id
	for (int i = 0; i < MAX_ID_SIZE; i++) {
		if (input_id[i] == NULL) {
			fputc(' ', output);
			break;
		}
		fputc(input_id[i], output);
	}
	// writer password
	for (int i = 0; i < MAX_PASSWORD_SIZE; i++) {
		if (users[(*user_counter) - 1].password[i] == NULL) {
			fputc('\n', output);
			break;
		}
		fputc(users[(*user_counter) - 1].password[i], output);
	}
	fclose(output);
	printf("done\n");
	return users;
}

void add_hall(struct hall **halls, int *hall_counter) {
	// change array's size
	(*hall_counter)++;
	(*halls) = (struct hall*)realloc(*halls, (*hall_counter) * sizeof(struct hall));
	if ((*halls) == NULL) exit(0);
	// input
	Reset((*halls)[(*hall_counter) - 1].name, MAX_USERNAME_SIZE);
	scanf("%s", (*halls)[(*hall_counter) - 1].name);
	scanf("%d", &(*halls)[(*hall_counter) - 1].id);
	scanf("%d", &(*halls)[(*hall_counter) - 1].capacity);
	// check if hall id is unique
	for (int i = 0; i < (*hall_counter) - 1; i++) {
		if ((*halls)[i].id == (*halls)[(*hall_counter) - 1].id) {
			// hall id is not unique
			printf("hall id is not unique\n");
			(*hall_counter)--;
			(*halls) = (struct hall*)realloc(*halls, (*hall_counter) * sizeof(struct hall));
			if ((*halls) == NULL) exit(0);
			return;
		}
	}
	// hall id is unique
	printf("done\n");
	return;
}

void add_food(struct hall **halls, int *hall_counter, struct food **foods, int *food_counter) {
	// change array's size
	(*food_counter)++;
	(*foods) = (struct food*)realloc(*foods, (*food_counter) * sizeof(struct food));
	if ((*foods) == NULL) exit(0);
	// input
	Reset((*foods)[(*food_counter) - 1].name, MAX_USERNAME_SIZE);
	scanf("%s", (*foods)[(*food_counter - 1)].name);
	scanf("%d", &(*foods)[(*food_counter - 1)].id);
	scanf("%d", &(*foods)[(*food_counter - 1)].price);
	scanf("%d", &(*foods)[(*food_counter - 1)].capacity);
	scanf("%d", &(*foods)[(*food_counter - 1)].hall_id);
	scanf("%d", &(*foods)[(*food_counter - 1)].day);
	// check if hall id exists
	int flag = 0;
	for (int i = 0; i < *hall_counter; i++) {
		if ((*halls)[i].id == (*foods)[(*food_counter) - 1].hall_id) flag = 1;
	}
	if (flag == 0) {
		printf("wrong hall id\n");
		return;
	}

	//check food id is unique

	for (int i = 0; i < (*food_counter) - 1; i++) {
		if ((*foods)[i].id == (*foods)[(*food_counter) - 1].id) {
			// food id is not unique
			printf("food id is not unique\n");
			(*food_counter)--;
			(*foods) = (struct food*) realloc(*foods, (*food_counter) * sizeof(struct food));
			if ((*foods) == NULL) exit(0);
			return;
		}
	}
	// food id is unique
	printf("done\n");
	return;
}

void add_coupon(struct coupon **coupons, int *coupon_counter) {
	// change array's size
	(*coupon_counter)++;
	(*coupons) = (struct coupon*)realloc(*coupons, (*coupon_counter) * sizeof(struct coupon));
	if ((*coupons) == NULL) exit(0);
	// input
	scanf("%d", &(*coupons)[(*coupon_counter) - 1].id);
	scanf("%d", &(*coupons)[(*coupon_counter) - 1].percentage);
	scanf("%d", &(*coupons)[(*coupon_counter) - 1].capacity);
	// check if id is unique
	for (int i = 0; i < (*coupon_counter) - 1; i++) {
		if ((*coupons)[i].id == (*coupons)[(*coupon_counter) - 1].id) {
			(*coupon_counter)--;
			(*coupons) = (struct coupon*)realloc(*coupons, (*coupon_counter) * sizeof(struct coupon));
			if ((*coupons) == NULL) exit(0);
			printf("coupon id is not unique\n");
			return;
		}
	}
	// coupon id is unique
	printf("done\n");
	return;
}

void admin_login(struct hall **halls, int *hall_counter, struct food **foods, int *food_counter, struct coupon **coupons, int *coupon_counter) {
	while (TRUE) {
		// input
		char Input[MAX_INPUT_LEN];
		Reset(Input, MAX_INPUT_LEN);
		scanf("%s", Input);
		// if command is add_hall
		if (compare_add_hall(Input)) {
			add_hall(halls, hall_counter);
			continue;
		}
		// if command is add_food
		else if (compare_add_food(Input)) {
			add_food(halls, hall_counter, foods, food_counter);
			continue;
		}
		// if command is add coupon
		else if (compare_add_coupon(Input)) {
			add_coupon(coupons, coupon_counter);
			continue;
		}
		// if command id logout
		else if (compare_logout(Input)) {
			printf("done\n");
			break;
		}
		// other commands
		else {
			char Input[MAX_INPUT_LEN];
			gets(Input);
			printf("access denied\n");
		}
	}
	return;
}

void user_login(struct user *users, int *user_counter, struct hall **halls, int *hall_counter, struct food **foods, int *food_counter, struct coupon **coupons, int *coupon_counter) {
	struct user Input;
	Reset(Input.password, MAX_PASSWORD_SIZE);
	Reset(Input.username, MAX_USERNAME_SIZE);
	char *admin_string = "admin\0";
	// input login data 
	scanf("%s", Input.username);
	scanf("%s", Input.password);
	// check admin login
	if (compare_string(Input.username, admin_string) && compare_string(Input.password, admin_string)) {
		//admin access
		printf("welcome admin\n");
		admin_login(halls, hall_counter, foods, food_counter, coupons, coupon_counter);
		return;
	}
	// other users
	int flag = 0;
	int user_number = 0;
	// check if login data exists
	for (int i = 0; i < (*user_counter); i++) {
		if (compare_string(users[i].username, Input.username) && compare_string(users[i].password, Input.password)) {
			// exists
			flag = 1;
			user_number = i;
		}
	}
	if (flag == 0) {
		// doesn't exist
		printf("wrong user or pass\n");
		return;
	}
	if (flag == 1) {
		printf("welcome ");
		for (int i = 0; i < MAX_USERNAME_SIZE; i++) {
			if (users[user_number].username[i] == NULL) break;
			printf("%c", users[user_number].username[i]);
		}
		printf("\n");
		while (TRUE) {
			char command[MAX_INPUT_LEN];
			Reset(command, MAX_INPUT_LEN);
			scanf("%s", command);
			// logout command
			if (compare_logout(command)) {
				printf("done\n");
				break;
			}
			// admind commands
			else if (compare_add_food(command) || compare_add_hall(command) || compare_add_coupon(command)) {
				char Input[MAX_INPUT_LEN];
				gets(Input);
				printf("permission denied\n");
			}
			else {
				char Input[MAX_INPUT_LEN];
				gets(Input);
				printf("access denied\n");
			}
		}
	}
	return;
}