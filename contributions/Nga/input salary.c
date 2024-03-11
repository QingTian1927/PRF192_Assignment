void salaryStdin( struct chefObj list[], int n){
	int i;
	for( i = 0; i < n; i++){
		printf("\nNhap luong cua nhan vien thu %d: ", i+1);
		scanf("%f", &list[i].salary);
		if(list[i].salary<=0){
			printf("\nLuong nhap vao khong hop le, vui long nhap lai\n");
			i--;
		}
	}
}

