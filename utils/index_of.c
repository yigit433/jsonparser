int index_of(const char *str, const char target, unsigned long long str_length) {
    int result = -1;

    int i = 0;
    while (i < str_length) {
        if (str[i] == target) {
            result = i;
        }
        
        i++;
    }
    
    return result;
}