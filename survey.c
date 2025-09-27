/* survey.c */
#include <stdio.h>

int main() {
	char buffer[300];

	printf("(Taking input from file) \n");

	while(fgets(buffer, sizeof(buffer), stdin) !=NULL){
		printf("%s", buffer);
	}
	return 0;
}
