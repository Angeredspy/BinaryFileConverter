#include <stdio.h>  
#include <stdlib.h>
#include <string.h>  
#include <ctype.h>

int todecimal(int num)

{

int decimal_val=0,rem,base=1;

int binary_val = num;

while (num > 0)

{

rem = num % 10;

decimal_val = decimal_val + rem * base;

num = num / 10 ;

base = base * 2;

}

return decimal_val;

} 

//method to extract the date field from line and store in date parameter

void extractDate(char *line,char *date){

              //finding the last index

              int lastIndex=strlen(line)-1;

              int startIndex=0;

              int numSpaces=0;

              //finding the index of second space from the last index

              for(int i=lastIndex;i>=0;i--){

                           if(line[i]==' '){

                                         numSpaces++;

                                         if(numSpaces==2){

                                                       //found, setting this as the start index

                                                       startIndex=i;

                                                       break;

                                         }

                           }

              }

              int index=0;

              //copying characters between startIndex+1 and lastIndex, storing it in date

              for(int i=startIndex+1;i<=lastIndex;i++){

                           date[index]=line[i];                     

                           index++;

              }

              //null terminating the date

              date[index]='\0';

} 

//method to sort the lines and dates parallel arrays of size count

void sort(char lines[100][80], char dates[100][20], int count){

              //looping through all rows

              for(int i=0;i<count;i++){

                           //looping through all columns

                           for(int j=0;j<count-1;j++){

                                         //comparing two dates (yyyy-mm-dd format is easy to sort lexicographically )

                                         if(strcmp(dates[j],dates[j+1])>0){

                                                       char temp[100];

                                                       //swapping dates at j and j+1

                                                       strcpy(temp,dates[j]);

                                                       strcpy(dates[j],dates[j+1]);

                                                       strcpy(dates[j+1],temp);

                                                       //swapping lines at j and j+1

                                                       strcpy(temp,lines[j]);

                                                       strcpy(lines[j],lines[j+1]);

                                                       strcpy(lines[j+1],temp);

                                         }

                           }

              }

}


int main(){
// FILE *foo = NULL; 
 
// foo = fopen("textFile.txt" ,"a"); STUFF WE PROBABLY DONT EVEN NEED 

//  mkdir("testdir", 0750);

int i;

char ch;

char str[9];

int n;

FILE *ipFile = fopen("test.bin", "rb");

FILE *opFile = fopen("result.txt", "w");

while(fread(str,1,8,ipFile)==8)//Reads Exactly 8 bits

{

str[8]= '\n';

n=atoi(str);//Converts String To Integer

n= todecimal(n);//Converts Binary To Decimal

printf("%c",n);//prints Decimal Equavalent To ASCII Character

//Note We Are Using %c

fprintf(opFile,"%c",n);//print To File

}   

fclose(opFile);

fclose(ipFile); 

              FILE *fp;

              char filename[20];

              //prompting for an input file name

              

              strcpy(filename, "result.txt"); // ScanF? 

              //opening file for reading

              fp=fopen(filename,"r");

             

              if(fp==NULL){

                           //file not opened properly

                           printf("File not found!\n");

                           return 0;

              }

              //defining two parallel arrays for storing lines and dates upto 100 lines

              char lines[100][80];

              char dates[100][20];

              int count=0; //current count of records

              char line[80]; //current line under process

              char date[20]; //current date under process

              //looping until the end of file

              while(fgets(line,sizeof(line),fp)!=NULL){

                           //null terminating line

                            line[strlen(line)-1]='\0';

                           //extracting date from line

                           extractDate(line,date);

                           //storing line and date to the arrays

                           strcpy(lines[count],line);

                           strcpy(dates[count],date);

                           count++;

              }

              //closing input file

              fclose(fp);

              //sorting lines

              sort(lines,dates,count);

               strcpy(filename, "BigResult.txt"); // ScanF? 

              //opening file for writing

              FILE *ofp=fopen(filename,"w+");

              //writing all lines to the output file

              for(int i=0;i<count;i++){

                           fprintf(ofp,"%s\n",lines[i]);

              }

              //closing output file

              fclose(ofp);

              printf("\nSorted result has been stored in output file\n");  

             
             // New Portion for files with the line duplication problem
FILE *fap, *newFp;
char failename[20];
char linez[1024];
int index;
char newFilename[20];

printf("Enter input filename: ");
scanf("%s", failename);


fap = fopen(failename, "r");

if(fap == NULL){
printf("ERROR: could not open input file %s\n",failename);
return 1;
}
while(fgets(linez, 1024, fap)){
for(index = 0; linez[index] != '\0'; index++){
if(!isalpha(linez[index])) //found a non-letter char
break;
}
//get all characters upto index as the filename to be created
strncpy(newFilename, linez, index);
newFilename[index] = '\0';
strcat(newFilename, ".txt");
newFp = fopen(newFilename, "a"); //creates a file, overwrites existing contents
fputs(linez, newFp);
fclose(newFp);
printf("created file %s\n", newFilename);
}
fclose(fap);
}
