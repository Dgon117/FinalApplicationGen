#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>
#define NUMBER_CHOICES 25
#define CHOICE_LENGTH 25
#define NAME_LENGTH 10
/*generates a random name given the names json object. It must be freed. */char
*generateRandomName(struct json_object*namesDB){struct json_object*firstNames=
json_object_object_get(namesDB,"FIRST");// Gets lengnth of first names array 
int firstCount=json_object_array_length(firstNames);
// Gets seconds names array "Last is key in file"
struct json_object*lastNames=json_object_object_get(namesDB,"LAST");int 
lastCount=json_object_array_length(lastNames);
// String for random name // method funciton convert object to string 
const char*randFirst=json_object_to_json_string(json_object_array_get_idx(
firstNames,rand()%firstCount));const char*randLast=json_object_to_json_string(
json_object_array_get_idx(lastNames,rand()%lastCount));
// get the sizes of each string
size_t len1=strlen(randFirst);size_t len2=strlen(randLast);// get memory
char*s=malloc(len1+len2+2);memcpy(s,randFirst,len1);s[len1]=' ';
// combine the two names
memcpy(s+len1+1,randLast,len2+1);// return it
return s;}/*Show the union data. */void showUnionData(){union Data{int i;int e;
};// create a union
union Data d1;d1.i=10;d1.e=20;// print union data
printf("%d\n",d1.i);printf("%d",d1.e);}/*
Main function for the program - generate random names while the user wants */
int main(void){showUnionData();// load json for the names from test.json
struct json_object*namesJSON=json_object_from_file("test.json");FILE*outputFile
;errno_t err;const char*outputFileName="output.txt";if((err=fopen_s(&outputFile
,outputFileName,"w+"))!=0){printf("Unable to open filename: %s\n",
outputFileName);return-1;}// the user's choice
int pick=1;// loop adds names together
while(pick==1){//Random Name Listed
printf("Random Name: \n");// generate random string from our JSON file
char*randName=generateRandomName(namesJSON);
// print the result to the standard output
printf("%s\n",randName);// write the string to the file
fprintf_s(outputFile,"%s\n",randName);// free the memory from the string
free(randName);// Generate another name
printf("\nYou want to generate another name(1: yes, 2: no): ");scanf_s("%d",&
pick);}// make sure to close the file
fclose(outputFile);return 0;}