#include <stdio.h>

int main(void) {
    int day, month, year, hour, minute, second;

    printf("Enter date and time (DD MM YYYY HH MM SS):\n");
    if (scanf("%d %d %d %d %d %d", &day, &month, &year, &hour, &minute, &second) != 6) {
        fprintf(stderr, "Invalid input. Expected 6 integers.\n");
        return 1;
    }

    printf("You entered: %02d-%02d-%04d %02d:%02d:%02d\n",
           day, month, year, hour, minute, second);

    return 0;
}
