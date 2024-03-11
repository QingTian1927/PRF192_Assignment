#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
void upper1stltr(char arr[]){
	int i;
	strlwr(arr);
	for( i = 0; i < strlen(arr); i++){
		if(arr[i] == ' ' && isalpha(arr[i+1])!=0){
			arr[i+1] = toupper(arr[i+1]);
		}else if(i==0 && isalpha(arr[i])!=0){
			arr[i] = toupper(arr[i]);
		}
		else continue;
	}
}
int main(){
	char arr[100];
	gets(arr);
	upper1stltr(arr);
	printf("%s", arr);
}
