#include <stdio.h>

int main(int argc, char** argv) {
    FILE* data = fopen("day_1_data.txt", "r");
    char hate[256];
    unsigned char num1, num2, search = '\0';
    unsigned char num1found = 0, num2found = 0;
    unsigned long sum = 0, totalNumsThisLine = 0;
    do {
        search = fgetc(data);
        if ('0' <= search && search <= '9') { // '0' and '9'
            totalNumsThisLine++;
            if (num1found == 0) {
                num1found = 1;
                num1 = search;
            }
        }
        if (search == '\n' || feof(data)) {
            if (totalNumsThisLine == 0) goto ignoreline;
            while (num2found == 0) {
                size_t savedpos = ftell(data);
                fseek(data, -2, SEEK_CUR);
                search = fgetc(data);
                if ('0' <= search && search <= '9') {
                    num2found = 1;
                    num2 = search;
                }
                if (ftell(data) == 0) printf("SHIT");
            }
            int currNum = ((num1 % 0x30) * 10 + (num2 % 0x30));
            sum += currNum;
            ignoreline:
            num1found = 0; num1 = 0;
            num2found = 0; num2 = 0;
            totalNumsThisLine = 0;
            printf("current number: %i, running total: %lu\n", currNum, sum);
            (void)fgets(hate, 255, data); // goes to next line
        }
    } while (!feof(data));
    printf("\nsum: %lu\n", sum);
    return 0;
}