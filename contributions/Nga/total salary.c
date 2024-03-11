float totalSalary(struct chefObj list[], int n){
	float sum = 0;
	for(int i = 0; i < n; i++){
		sum+= list[i].salary;
	}return sum;
}
