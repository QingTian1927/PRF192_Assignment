#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NAME_LEN 30
struct chefObj{
	char name[MAX_NAME_LEN];
	int salary;
};
void swap(int *a, int *b){
	int t = *a;
	*a = *b;
	*b = t;
}
struct chefObj* salaryRearange(struct chefObj list[], int n){
	struct chefObj* arr =(struct chefObj*)malloc(n* sizeof(struct chefObj));
	if(arr==NULL){
        exit(1);
    }
	int i, j;
	char t[MAX_NAME_LEN];
	for( i = 0; i < n; i++){
		for( j = i; j < n; j++){
			if(list[i].salary<list[j].salary){
				swap(&list[i].salary, &list[j].salary);
                strcpy(t, list[i].name);
                strcpy(list[i].name, list[j].name);
                strcpy(list[j].name, t);
			}
		}
	}for( i = 0; i < n; i++){
	strcpy(arr[i].name,list[i].name);
		arr[i].salary = list[i].salary;
	}
	return arr;
}
int main(){
	int n; 
	scanf("%d", &n);
	getchar();
	struct chefObj list[n];
	for( int i = 0; i < n; i++){
		fgets(list[i].name, 30, stdin);
		list[i].name[strcspn(list[i].name, "\n")] = '\0';
		scanf("%d", &list[i].salary);
		getchar();
	}
	struct chefObj *topslr = salaryRearange(list, n);
	for( int i = 0; i < n ; i++){
		printf("\n%s : %d", topslr[i].name, topslr[i].salary);
	}
	free(topslr);
	return 0;
}
