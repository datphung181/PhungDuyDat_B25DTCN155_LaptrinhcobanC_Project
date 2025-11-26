#include <stdio.h>
#include <string.h>

#define MAX_EMP 100 
#define MAX_LOG 500
 
// ===================== STRUCT =====================
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


// ===================== Global =====================
Employee empList[MAX_EMP];
int empCount = 0;

TimeSheet timeList[MAX_LOG];
int logCount = 0;


// ===================== Function Prototypes =====================
void menu();
void CreateNewEmployee();
void UpdateProfileEmployee();
void DeleteEmployee();
void DisplayEmployees();
void SearchEmployeeByName();
void printEmployee(Employee emp);
void toLowerCase(char *str);
void sortEmployeeBySalary();


int findEmpByID(char id[]);
int checkDuplicateID(char id[]);
void inputString(char *s, int maxLen);


// ===================== Support Functions =====================
int findEmpByID(char id[]) {
    for (int i = 0; i < empCount; i++) {
        if (strcmp(empList[i].empId, id) == 0)
            return i;
    }
    return -1;
}

int checkDuplicateID(char id[]) {
    return findEmpByID(id) != -1;
}

void inputString(char *s, int maxLen) {
    fflush(stdin);
    fgets(s, maxLen, stdin);
    s[strcspn(s, "\n")] = '\0';
}

int findEmpByName(char name[]) {
    for (int i = 0; i < empCount; i++) {
        if (strcasecmp(empList[i].name, name) == 0) {
            return i;   // tr? v? v? trí đ?u tiên trùng tên
        }
    }
    return -1;
}



// ===================== MAIN =====================
int main() {
    menu();
    return 0;
}


// ===================== MENU =====================
void menu() {
    int choice;

    do {
        printf("\n+----------------------------------------------------------+\n");
        printf("|          Danh sach quan ly nhan vien va cham cong        |\n");
        printf("+----------------------------------------------------------+\n");
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
        getchar(); // clear buffer

        switch (choice) {
            case 1: CreateNewEmployee(); break;
            case 2: UpdateProfileEmployee(); break;
            case 3: DeleteEmployee(); break;
            case 4: DisplayEmployees(); break;
            case 5: SearchEmployeeByName(); break;
            case 6: sortEmployeeBySalary(); break;
            case 9: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (choice != 9);
}


// ===================== FUNC 1: Create New Employee =====================
void CreateNewEmployee() {
    Employee newEMP;


    printf("\n-- THEM NHAN VIEN --\n");

    // ===== NHAP MA NV =====
    while (1) {
        printf("Nhap ma NV: ");
        inputString(newEMP.empId, 20);

        if (strlen(newEMP.empId) == 0) {
            printf("? Ma NV khong duoc rong!, Nhap lai\n");
            continue;
        }

        if (checkDuplicateID(newEMP.empId)) {
            printf("? Ma NV da ton tai! Nhap lai.\n");
            continue;
        } 
        break;
    }

    // ===== NHAP TEN =====
    while (1) {
        printf("Nhap ten NV: ");
        inputString(newEMP.name, 50);

        if (strlen(newEMP.name) == 0) {
            printf("? Ten khong duoc rong!, Nhap lai\n");
            continue;
        }
        break;
    }

    // ===== NHAP CHUC VU =====
    while (1) {
        printf("Nhap chuc vu: ");
        inputString(newEMP.position, 15);

        if (strlen(newEMP.position) == 0) {
            printf("? Chuc vu khong duoc rong!, Nhap lai\n");
            continue;
        }
        break;
    }

    // ===== NHAP LUONG CO BAN =====
    while (1) {
        printf("Nhap luong co ban: ");
        if (scanf("%lf", &newEMP.baseSalary) != 1) {
            printf("? Luong phai la so! Nhap lai.\n");
            while (getchar() != '\n');
            continue;
        }
        if (newEMP.baseSalary <= 0) {
            printf("? Luong phai la so duong! Nhap lai.\n");
            continue;
        }
        while (getchar() != '\n');
        break;
    }

    // ===== NHAP NGAY CONG =====
    int option;
    while (1) {
        printf("\nChon cach them so ngay cong:\n");
        printf("1. Mac dinh (0 ngay)\n");
        printf("2. Tu nhap ngay cong\n");
        printf("Lua chon: ");
        scanf("%d", &option);
        getchar();

        if (option == 1) {
            newEMP.workDay = 0;
            break;
        } 
        else if (option == 2) {
            while (1) {
                printf("Nhap so ngay cong: ");
                if (scanf("%d", &newEMP.workDay) != 1) {
                    printf("? Phai nhap so nguyen! Nhap lai.\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (newEMP.workDay < 0) {
                    printf("? Ngay cong phai >= 0\n");
                    continue;
                }
                getchar();
                break;
            }
            break;
        }
        else {
            printf("? Lua chon khong hop le!\n");
        }
    }

    empList[empCount++] = newEMP;

    printf("? Them nhan vien thanh cong!\n");
}



// ===================== FUNC 2: Update Employee =====================
void UpdateProfileEmployee() {
    char id[20];
    int searchEmpID;
    if (empCount == 0) {
        printf("\nDanh sach nhan vien rong!\n");
        return;
    }

    printf("\n-- CAP NHAT NHAN VIEN --\n");

    // ===== NHAP MA NV CAN CAP NHAT =====
    while (1) {
        printf("Nhap ma NV: ");
        inputString(id, 20);

        searchEmpID = findEmpByID(id);
        if (searchEmpID == -1) {
            printf(" Khong tim thay nhan vien co ID la %s! Nhap lai.\n",id);
            continue;
        }
        break;
    }

    // ===== CAP NHAT CHUC VU =====
    while (1) {
        printf("Nhap chuc vu moi: ");
        inputString(empList[searchEmpID].position, 15);

        if (strlen(empList[searchEmpID].position) == 0) {
            printf("? Chuc vu khong duoc rong!, Nhap lai\n");
            continue;
        }
        break;
    }

    // ===== CAP NHAT LUONG =====
    while (1) {
        printf("Nhap luong moi: ");
        if (scanf("%lf", &empList[searchEmpID].baseSalary) != 1) {
            printf("? Luong phai la so! Nhap lai.\n");
            while (getchar() != '\n');
            continue;
        }
        if (empList[searchEmpID].baseSalary <= 0) {
            printf("? Luong phai > 0! Nhap lai.\n");
            continue;
        }
        getchar();
        break;
    }

    printf("? Cap nhat thanh cong!\n");
}



// ===================== FUNC 3: Delete Employee =====================
void DeleteEmployee() {
    char id[20];
    int deleteEmpID;

    printf("\n-- SA THAI NHAN VIEN --\n");

    while (1) {
        printf("Nhap ma NV: ");
        inputString(id, 20);

        deleteEmpID = findEmpByID(id);
        if (deleteEmpID == -1) {
            printf(" Khong tim thay nhan vien co ID la %s! Nhap lai!\n",id);
            continue;
        }
        break;
    }

    // ===== TIEN HANH XOA =====
    for (int i = deleteEmpID; i < empCount - 1; i++)
        empList[i] = empList[i + 1];

    empCount--;

    printf(" Xoa nhan vien co ID [%s] thanh cong!\n",id);
}



// ===================== FUNC 4: Display Employees =====================
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

// ===================== FUNC 5: Search Employee by Name =====================
void printEmployee(Employee emp) {
    printf("Ma NV: %s\n", emp.empId);
    printf("Ten NV: %s\n", emp.name);
    printf("Chuc vu: %s\n", emp.position);
    printf("Luong co ban: %.2lf\n", emp.baseSalary);
    printf("Ngay cong: %d\n", emp.workDay);
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void SearchEmployeeByName() {
    if (empCount == 0) {
        printf("\nDanh sach nhan vien dang rong!\n");
        return;
    }

    char keyword[50];
    char tempName[50];
    char tempKeyword[50];
    int foundAny = 0;

    printf("\n=== TIM KIEM NHAN VIEN THEO TEN ===\n");
    printf("Nhap mot phan hoac toan bo ten NV: ");
    inputString(keyword, 50);

    strcpy(tempKeyword, keyword);
    toLowerCase(tempKeyword);

    printf("\n===== KET QUA KIEM TRA TUNG NHAN VIEN =====\n");

    int foundIndex[MAX_EMP];
    int foundCount = 0;

    for (int i = 0; i < empCount; i++) {

        strcpy(tempName, empList[i].name);
        toLowerCase(tempName);

        if (strstr(tempName, tempKeyword) != NULL) {
            printf("%s -> Tim thay\n", empList[i].name);
            foundIndex[foundCount++] = i;
            foundAny = 1;
        } else {
            printf("%s -> Khong tim thay\n", empList[i].name);
        }
    }

    if (!foundAny) {
        printf("\nKhong co nhan vien nao chua tu khoa '%s'\n", keyword);
        return;
    }

    printf("\n===== THONG TIN CHI TIET CAC NHAN VIEN TIM THAY =====\n");

    for (int i = 0; i < foundCount; i++) {
        printEmployee(empList[foundIndex[i]]);
        printf("-------------------------\n");
    }
}
// ===================== FUNC 6: Sort Employee List by Base Salary =====================
void sortEmployeeBySalary() {
    if (empCount == 0) {
        printf("\nDanh sach nhan vien hien dang trong!\n");
        return;
    }

    int sortOrder;
    do {
        printf("\nChon kieu sap xep theo luong co ban:\n");
        printf("1. Tang dan\n");
        printf("2. Giam dan\n");
        printf("Nhap lua chon: ");
        scanf("%d", &sortOrder);

        if (sortOrder != 1 && sortOrder != 2) {
            printf("Lua chon khong hop le! Vui long nhap lai.\n");
        }
    } while (sortOrder != 1 && sortOrder != 2);

    // ----------------- SORT -----------------
    for (int i = 0; i < empCount - 1; i++) {
        for (int j = i + 1; j < empCount; j++) {
            if ((sortOrder == 1 && empList[i].baseSalary > empList[j].baseSalary) ||
                (sortOrder == 2 && empList[i].baseSalary < empList[j].baseSalary)) {

                Employee temp = empList[i];
                empList[i] = empList[j];
                empList[j] = temp;
            }
        }
    }

    // ----------------- OUTPUT -----------------
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

    printf("\nSap xep thanh cong!\n");
}


