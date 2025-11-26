/**
MIT License

Copyright (c) 2025 PSD Authors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

**/

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
