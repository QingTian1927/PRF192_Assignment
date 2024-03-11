#include <stdio.h>
#include <stdlib.h>

void lv2chinhsua(){
    printf("\n MASTERCHEFS MANAGEMENT SOFTWARE");
    printf("\n 1. THAY DOI TEN");
    printf("\n 2. THAY DOI NGAY, THANG, NAM SINH");
    printf("\n 3. THAY DOI CHUYEN MON");
    printf("\n 4. THAY DOI TIEN LUONG");
    printf("\n 0. BACK TO MAIN MENU");
}

void mainmenu(){
	printf("\nMASTERCHEFS MANAGEMENT SOFTWARE");
    printf("\n 1. HIEN THI DANH SACH DAU BEP");
    printf("\n 2. TIM KIEM DAU BEP");
    printf("\n 3. THEM DAU BEP");
    printf("\n 4. CHINH SUA THONG TIN DAU BEP");
    printf("\n 5. XOA DAU BEP");
    printf("\n 6. TINH TONG TIEN LUONG");
    printf("\n 0. EXIT TO DESKTOP");
    printf("\n Enter your choice: ");
}


int main() {
    int choice, subchoice;

    do {
    	mainmenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
            	system("cls");
                printf("\n MASTERCHEFS MANAGEMENT SOFTWARE");
                //chuc nang phan mem
                break;
            case 2:
            	system("cls");
                printf("\n MASTERCHEFS MANAGEMENT SOFTWARE");
                //chuc nang phan mem
                break;
            case 3:
            	system("cls");
                printf("\n MASTERCHEFS MANAGEMENT SOFTWARE");
                //chuc nang phan mem
                break;
            case 4:
                do{
                	system("cls");
                    lv2chinhsua();
                    scanf("%d", &subchoice);
                    getchar();
                    switch (subchoice){
                    case 1:
                    printf("\nMASTERCHEFS MANAGEMENT SOFTWARE");
                    //chuc nang phan mem
                    break;
                    case 2:
                    printf("\nMASTERCHEFS MANAGEMENT SOFTWARE");
                    //chuc nang phan mem
                    break;
                    case 3:
                    printf("\nMASTERCHEFS MANAGEMENT SOFTWARE");
                    //chuc nang phan mem
                    break;
                    case 4:
                    printf("\nMASTERCHEFS MANAGEMENT SOFTWARE");
                    //chuc nang phan mem
                    break;
                    default:
                    printf("\n RETURNING TO MAIN MENU");
                    break;
                    }
                }while (subchoice != 0);
                system("cls");
                break;
            case 5:
                printf("\nMASTERCHEFS MANAGEMENT SOFTWARE");
                //chuc nang phan mem
                break;
            case 6:
                printf("\nMASTERCHEFS MANAGEMENT SOFTWARE");
                //chuc nang phan mem
                break;
            default:
                printf("\n RETURNING TO DESKTOP");
                break;
        }
    } while (choice != 0);

    return 0;
}

