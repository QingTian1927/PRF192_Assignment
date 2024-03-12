void inThongTinNhanVien(struct chefObj employees[], int soLuongNhanVien) {
    printf("Danh sach nhan vien:\n");
    for (int i = 0; i < soLuongNhanVien; ++i) {
        printf("Nhan vien %d:\n", i+1);
        printf("Ho va ten: %s\n", employees[i].name);
        printf("Vi tri cong viec: %s\n", employees[i].role);
        printf("Ngay sinh: %s\n", employees[i].dateOfBirth);
        printf("Luong: %ld\n", employees[i].salary);
        printf("\n");
    }
