#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	time_t rawtime;
	struct tm * timeinfo;
	struct tm  timeinfoBuffer;
	char *result;

	time(&rawtime);
	/* call localtime */
	timeinfo = localtime_r(&rawtime , &timeinfoBuffer);
	/* allocate memory for the result of asctime call*/
	result = malloc(26 * sizeof(char));
	/* call reentrant asctime function */
	result = asctime_r(timeinfo, result);
	printf("The current date/time is: %s", result);
	/* free allocated memory */
	free(result);

	return 0;
}
