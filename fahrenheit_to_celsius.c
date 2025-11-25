#include <stdio.h>

int main() {
    float fahrenheit, celsius;
    
    printf("Enter temperature in Fahrenheit: ");
    scanf("%f", &fahrenheit);
    
    // Convert Fahrenheit to Celsius using formula: C = (F - 32) * 5/9
    celsius = (fahrenheit - 32) * 5.0 / 9.0;
    
    printf("%.2f°F = %.2f°C\n", fahrenheit, celsius);
    
    return 0;
}
