#include <jsonparser_utils.h>
#include <string.h>
#include <math.h>

double custom_atof(const char *str, unsigned long long str_length) {
    const char numbers[10] = "0123456789";
    
    double result = 0.0;
    int signCondition = 1;
    int decimalNumber = index_of(str, '.', strlen(str));
    
    if (str[0] == '-') {
        signCondition *= -1;
    } 
    
    int i = 0;
    int updatedStep = 0;
    int step = str_length - 1;
    if (decimalNumber != -1) {
        step = decimalNumber - 1;
    }
 
    while (i < str_length) {        
        int condition = decimalNumber != -1 && i > decimalNumber;
        if (step < 0 && condition && updatedStep == 0) {
            step += 1;
            updatedStep = 1;
        }
     
        if (index_of(numbers, str[i], 10) != -1) {
            result += pow(10, step) * index_of(numbers, str[i], 10);
        }

        step--;
        i++;
    }
    
    return result * signCondition;
}