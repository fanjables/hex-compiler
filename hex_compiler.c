#include <stdio.h>
#include <string.h>

unsigned char byteConstructor(unsigned char a, unsigned char b);

FILE *fileptr;  //a pointer to a file
int main(){
    unsigned char address[251] = {0};
    unsigned char newAddress[254] = {0};
    unsigned char data[8192] = {0};
    unsigned char compiledData[4096] = {0};
    unsigned char currentData[2] = {0};
    printf("Enter directory of input file, remember double backslashes\n");
    scanf("%250s", address);
    printf("\n");
    fileptr = fopen(address, "r");  //opent the file into fileptr in read mode
    if(fileptr == NULL){
        printf("File doesn't exist\n");
        return -1;
    }
    fgets(data, 8192, fileptr); //reads 8kb of hex data 
    if(strlen(data) % 2 != 0){
        printf("Odd number of characters in source file\n");
        return -1;
    }
    unsigned int counter = 0;
    for(int i = 0; i < strlen(data); i += 2){   //constructs the 4kb binary
        currentData[0] = data[i];
        currentData[1] = data[i + 1];
        compiledData[i / 2] = byteConstructor(currentData[0], currentData[1]);
        counter++;
    }
    strcpy(newAddress, address);
    strcat(newAddress, ".bin");
    fileptr = fopen(newAddress, "w");
    if(fileptr == NULL){
        printf("Cant create file\n");
        return -1;
    }
    fwrite(compiledData, 1, counter, fileptr);
    fclose(fileptr);
    return 0;
}

unsigned char byteConstructor(unsigned char a, unsigned char b){
    unsigned char result;
    if(a >= 65 && a <= 70){   //handles letters
        a -= 55;    //turns from letter into number
    }
    else if(a >= 48 && a <= 57){ //handles numbers
        a -= 48;    //turns from character to number
    }
    else{
        printf("Not an allowable character %c\n", a);
        return 0;
    }

    if(b >= 65 && b <= 70){   //handles letters
        b -= 55;    //turns from letter into number
    }
    else if(b >= 48 && b <= 57){ //handles numbers
        b -= 48;    //turns from character to number
    }
    else{
        printf("Not an allowable character %c\n", b);
        return 0;
    }

    if(a > 15 || b > 15){
        printf("Too big value");
        return 0;
    }

    result = (a << 4) | b;
    return result;
}
