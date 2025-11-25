#include<stdio.h>
#include<string.h>

#define MAX_EMP 100
#define MAX_LOG 500

// =====================STRUCT=======================
typedef struct {
char empId[20];
char name[50];
char position[15];
double baseSalary;
int workDay;
} Employee;


typedef struct {
char logId[20];
char empId[20];
char date[20];
char status[10];
} TimeSheet;


//=====================Global Arrays========================
Employee empList[MAX_EMP];
int empCount = 0;

TimeSheet timeList[MAX_LOG];
int logCount = 0;
// Dung de luu tru toan bo nhan vien 



//=====================Funtions============================

// tim kiem bang ID
int findEmpByID(char id[]) {
	for (int i = 0; i < empCount; i++){
		if (strcmp(empList[i].empId, id) == 0)
		return i;
	}
	return -1;
}
// check lai ID xem co trung ko 
int checkDuplicateID (char id[]) {
	return findEmpByID(id) != -1;
	
}
// ma cham cong
void generateLogId(char out[]) {
    sprintf(out, "IDLOG%03d", logCount + 1);
}
// check cham cong trung ngay
int checkDuplicateDate(char id[], char date[]) {
    for (int i = 0; i < logCount; i++) {
        if (strcmp(timeList[i].empId, id) == 0 && strcmp(timeList[i].date, date) == 0)
            return 1;
    }
    return 0;
}

void inputString(char *s, int maxLen) {
    fflush(stdin);
    fgets(s, maxLen, stdin);
    s[strcspn(s, "\n")] = 0; 
}


// F01: Create New Employee
void CreateNewEmployee() {
    Employee newEMP;
    printf("\n-- THEM NHAN VIEN --\n");

    while (1) {
        printf("Nhap ma NV: ");
        inputString(newEMP.empId, 20);

        if (strcmp(newEMP.empId, "") == 0) {
            printf("Ma NV khong duoc rong! Nhap lai!\n");
            continue;
        }

        if (checkDuplicateID(newEMP.empId)) {
            printf("Ma NV da ton tai! Nhap lai!\n");
            continue;
        }

        break; 
    }

    printf("Nhap ten NV: ");
    inputString(newEMP.name, 50);

    printf("Nhap chuc vu: ");
    inputString(newEMP.position, 15);

    printf("Nhap luong co ban: ");
    scanf("%lf", &newEMP.baseSalary);

    newEMP.workDay = 0;
    empList[empCount++] = newEMP;

    printf("Them nhan vien thanh cong!\n");
}



// F02: Update employee
void UpdateProfileEmployee() {
    char id[20];
    int searchEmpID ;

    printf("\n-- CAP NHAT NHAN VIEN --\n");

    while (1) {
        printf("Nhap ma ID NV: ");
        inputString(id, 20);

        searchEmpID = findEmpByID(id);
        if (searchEmpID == -1) {
            printf("Khong tim thay nhan vien! Nhap lai!\n");
            continue;
        }
        break;
    }

    printf("Nhap chuc vu moi: ");
    inputString(empList[searchEmpID].position, 15);

    printf("Nhap luong moi: ");
    scanf("%lf", &empList[searchEmpID].baseSalary);

    printf("Cap nhat thanh cong!\n");
}



// F03: Deleta employee
void DeleteEmployee() {
    char id[20];
	int deleteEmpID;
	printf("\n-- SA THAI NHAN VIEN --\n");
	
    while (1) {
    	
    	printf("Nhap ma ID NV: ");
        inputString( id, 20);

        int deleteEmpID = findEmpByID(id);

        if (deleteEmpID == -1) {
            printf("Khong tim thay nhan vien! Nhap lai.\n");
            continue;
        }

        // Xoa nhan vien khoi empList
        for (int i = deleteEmpID; i < empCount - 1; i++) {
            empList[i] = empList[i + 1];
        }
        empCount--;

        // Xoa het cac cham cong thuoc ve NV nay
        for (int i = 0; i < logCount; i++) {
            if (strcmp(timeList[i].empId, id) == 0) {
                for (int j = i; j < logCount - 1; j++) {
                    timeList[j] = timeList[j + 1];
                }
                logCount--;
                i--; 
            }
        }

        printf("Xoa nhan vien thanh cong!\n");
        break;
    }
}


// F04: Display Employee List
void DisplayEmployees() {
    if (empCount == 0) {
        printf("\nDanh sach nhan vien rong!\n");
        return;
    }

    printf("\n=======================================================================================\n");
    printf("%-15s %-20s %-15s %-15s %-10s\n",
           "Ma NV", "Ten NV", "Chuc vu", "Luong co ban", "Ngay cong");
    printf("---------------------------------------------------------------------------------------\n");

    for (int i = 0; i < empCount; i++) {
        printf("%-15s %-20s %-15s %-15.2lf %-10d\n",
               empList[i].empId,
               empList[i].name,
               empList[i].position,
               empList[i].baseSalary,
               empList[i].workDay);
    }

    printf("=======================================================================================\n");
}


// ================= MENU =================
void menu() {
	int choice;
	do {
		printf("\n+----------------------------------------------------------+\n");
		printf("|          Danh sach quan ly nhan vien va cham cong        | ");
		printf("\n+----------------------------------------------------------+\n");
	    printf("|1. Them moi nhan vien                                     |\n");
	    printf("|2. Cap nhat ho so nhan vien                               |\n");
	    printf("|3. Sa thai / nghi viec                                    |\n");
	    printf("|4. Hien thi danh sach nhan vien                           |\n");
	    printf("|5. Tra cuu thong tin nhan vien                            |\n");
	    printf("|6. Sap xep danh sach nhan vien theo luong co ban          |\n");
	    printf("|7. Cham ngay cong                                         |\n");
	    printf("|8. Xem bang cong                                          |\n");
	    printf("|9. Thoat                                                  |\n");
	    printf("+----------------------------------------------------------+\n");
		
	    printf("Nhap lua chon cua ban : ");
	    scanf("%d" , &choice);

		switch(choice) {
			case 1: CreateNewEmployee(); break;	
			case 2: UpdateProfileEmployee(); break;
			case 3: DeleteEmployee(); break;
			case 4: DisplayEmployees(); break;
		}
	} while(choice != 0);
}

int main() {
	menu();
	return 0;
}
