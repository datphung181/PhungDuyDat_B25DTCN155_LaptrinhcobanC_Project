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
        printf("|9. Thoat                                                  |\n");
        printf("+----------------------------------------------------------+\n");

        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1: CreateNewEmployee(); break;
            case 2: UpdateProfileEmployee(); break;
            case 3: DeleteEmployee(); break;
            case 4: DisplayEmployees(); break;
            case 9: printf("Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (choice != 9);
}


// ===================== FUNC 1: Create New Employee =====================
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
    getchar();

    newEMP.workDay = 0;

    empList[empCount++] = newEMP;

    printf("Them nhan vien thanh cong!\n");
}


// ===================== FUNC 2: Update Employee =====================
void UpdateProfileEmployee() {
    char id[20];
    int idx;

    printf("\n-- CAP NHAT NHAN VIEN --\n");

    while (1) {
        printf("Nhap ma NV: ");
        inputString(id, 20);

        idx = findEmpByID(id);
        if (idx == -1) {
            printf("Khong tim thay nhan vien! Nhap lai!\n");
            continue;
        }
        break;
    }

    printf("Nhap chuc vu moi: ");
    inputString(empList[idx].position, 15);

    printf("Nhap luong moi: ");
    scanf("%lf", &empList[idx].baseSalary);
    getchar();

    printf("Cap nhat thanh cong!\n");
}


// ===================== FUNC 3: Delete Employee =====================
void DeleteEmployee() {
    char id[20];
    int idx;

    printf("\n-- SA THAI NHAN VIEN --\n");

    while (1) {
        printf("Nhap ma NV: ");
        inputString(id, 20);

        idx = findEmpByID(id);
        if (idx == -1) {
            printf("Khong tim thay nhan vien! Nhap lai!\n");
            continue;
        }
        break;
    }

    for (int i = idx; i < empCount - 1; i++)
        empList[i] = empList[i + 1];

    empCount--;

    printf("Xoa nhan vien thanh cong!\n");
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
