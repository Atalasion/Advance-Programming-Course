#include "Header.h"

int main() {
	// define arrays and sizes
	int user_counter = 0, food_counter = 0, hall_counter = 0, coupon_counter = 0;
	struct hall *halls = (struct hall*)malloc(sizeof(struct hall));
	if (halls == NULL) {
		exit(0);
	}
	struct food *foods = (struct food*)malloc(sizeof(struct food));
	if (foods == NULL) {
		exit(0);
	}
	struct user *users = (struct user*)malloc(sizeof(struct user));
	if (users == NULL) {
		exit(0);
	}
	struct coupon *coupons = (struct coupon*)malloc(sizeof(struct coupon));
	if (coupons == NULL) {
		exit(0);
	}
	// read users data from file
	users = read_users(users, &user_counter);
	while (TRUE) {
		//input
		char Input[MAX_INPUT_LEN];
		Reset(Input, MAX_INPUT_LEN);
		scanf("%s", Input);
		// login command
		if (compare_login(Input)) user_login(users, &user_counter, &halls, &hall_counter, &foods, &food_counter, &coupons, &coupon_counter);
		// signup command
		else if (compare_signup(Input)) {
			users = user_signup(users, &user_counter);
		}
		else {
			char Input[MAX_INPUT_LEN];
			gets(Input);
			printf("access denied\n");
		}
	}
}