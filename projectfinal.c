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

// F01: Add employee
void addEmployee() {
	Employee newEMP;
	printf("\n-- THEM NHAN VIEN --\n");
	
	
	printf("Nhap ma NV: ");
	fflush(stdin);
	gets(newEMP.empId);
	
	
	if (strcmp(newEMP.empId, "") == 0 || checkDuplicateID(newEMP.empId)) {
	printf("Ma NV bi rong hoac da ton tai!\n");
	return;
	}
	
	
	printf("Nhap ten NV: ");
	gets(newEMP.name);
	printf("Nhap chuc vu: ");
	gets(newEMP.position);
	printf("Nhap luong co ban: ");
	scanf("%lf", &newEMP.baseSalary);
	
	
	newEMP.workDay = 0;
	empList[empCount++] = newEMP;	
	
	
	printf("Them nhan vien thanh cong!\n");
}


// F02: Update employee
void updateEmployee() {
	char id[20];
	printf("\n-- CAP NHAT NHAN VIEN --\n");
	printf("Nhap ma NV: ");
	fflush(stdin);
	gets(id);
	
	
	int idx = findEmpByID(id);
	if (idx == -1) {
	printf("Khong tim thay nhan vien!\n");
	return;
	}
	
	
	printf("Nhap chuc vu moi: ");
	gets(empList[idx].position);
	printf("Nhap luong moi: ");
	scanf("%lf", &empList[idx].baseSalary);
	
	
	printf("Cap nhat thanh cong!\n");
}



// ================= MENU =================
void menu() {
	int choice;
	do {
		printf("\n===== MENU =====\n");
		printf("1. Them nhan vien\n");
		printf("2. Cap nhat nhan vien\n");
		printf("3. Xoa nhan vien\n");
		printf("4. Hien thi danh sach\n");
		printf("5. Tim kiem nhan vien\n");
		printf("6. Sap xep luong\n");
		printf("7. Cham cong\n");
		printf("8. Xem bang cong\n");
		printf("0. Thoat\n");
		printf("Chon: ");
		scanf("%d", &choice);

		switch(choice) {
			case 1: addEmployee(); break;
			case 2: updateEmployee(); break;
		}
	} while(choice != 0);
}

int main() {
	menu();
	return 0;
}
