#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int main(){
FILE *fp, *newFp;
char filename[20];
char line[1024];
int index;
char newFilename[20];

printf("Enter input filename: ");
scanf("%s", filename);


fp = fopen(filename, "r");

if(fp == NULL){
printf("ERROR: could not open input file %s\n",filename);
return 1;
}
while(fgets(line, 1024, fp)){
for(index = 0; line[index] != '\0'; index++){
if(!isalpha(line[index])) //found a non-letter char
break;
}

//get all characters upto index as the filename to be created
strncpy(newFilename, line, index);
newFilename[index] = '\0';
strcat(newFilename, ".txt");
newFp = fopen(newFilename, "a"); //creates a file, overwrites existing contents
fputs(line, newFp);
fclose(newFp);
printf("created file %s\n", newFilename);
}


fclose(fp);
}

