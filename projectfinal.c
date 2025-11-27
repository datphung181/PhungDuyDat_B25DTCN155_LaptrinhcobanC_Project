#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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
void DisplayEmployeesPaginated();
void SearchEmployeeByName();
void printEmployee(Employee emp);
void toLowerCase(char *str);
void sortEmployeeBySalary();
void ViewPersonalTimeSheet();

int findEmpByID(char id[]);
int checkDuplicateID(char id[]);
void inputString(char *s, int maxLen);

int validateDate(char date[]);
int isFutureDate(int d, int m, int y);
int checkDuplicateTimeSheet(char empId[], char date[]);
void CheckInWorkDay();


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
    if (fgets(s, maxLen, stdin) != NULL) {
        s[strcspn(s, "\n")] = '\0';
    } else {
        s[0] = '\0';
    }
}

int findEmpByName(char name[]) {
    for (int i = 0; i < empCount; i++) {
        if (strcasecmp(empList[i].name, name) == 0) {
            return i;   
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
        if (scanf("%d" , &choice) != 1) {
            while (getchar() != '\n'); // clear bad input
            printf("Lua chon khong hop le!\n");
            continue;
        }
        getchar(); // clear newline left

        switch (choice) {
            case 1: CreateNewEmployee(); break;
            case 2: UpdateProfileEmployee(); break;
            case 3: DeleteEmployee(); break;
            case 4: DisplayEmployeesPaginated(); break;
            case 5: SearchEmployeeByName(); break;
            case 6: sortEmployeeBySalary(); break;
            case 7: CheckInWorkDay(); break;
            case 8: ViewPersonalTimeSheet(); break; 
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
        
        if (newEMP.empId[0] == '-') {
            printf("Ma nhan vien khong hop le! Khong duoc bat dau bang dau '-'.\n");
            continue;
        }

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
        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            printf("Lua chon khong hop le!\n");
            continue;
        }
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
            printf("? Luong phai lon hon 0! Nhap lai.\n");
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
    char confirm; 

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
    
    // ===== XAC NHAN XOA =====
    while (1) {
        printf("Ban co chac chan muon xoa nhan vien %s? (Y/N): ", id);
        scanf(" %c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            break;
        } 
        else if (confirm == 'N' || confirm == 'n') {
            printf("? Da huy thao tac xoa.\n");
            return;
        }
        else {
            printf("? Chi duoc nhap Y hoac N.\n");
        }
    }

    // ===== TIEN HANH XOA =====
    for (int i = deleteEmpID; i < empCount - 1; i++)
        empList[i] = empList[i + 1];

    empCount--;

    printf(" Xoa nhan vien co ID [%s] thanh cong!\n",id);
}


// ===================== FUNC 4: Display Employees (Paginated) =====================
void DisplayEmployeesPaginated() {
    if (empCount == 0) {
        printf("\nDanh sach nhan vien rong!\n");
        return;
    }

    int perPage = 5;
    int totalPage = (empCount + perPage - 1) / perPage;
    int currentPage = 1;
    int choice;

    while (1) {

        int start = (currentPage - 1) * perPage;
        int end = start + perPage;
        if (end > empCount) end = empCount;

        printf("\n==================== TRANG %d / %d ====================\n", currentPage, totalPage);
        printf("%-15s %-20s %-15s %-15s %-10s\n",
            "Ma NV", "Ten NV", "Chuc vu", "Luong", "Ngay cong");
        printf("-------------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            printf("%-15s %-20s %-15s %-15.2lf %-10d\n",
                empList[i].empId,
                empList[i].name,
                empList[i].position,
                empList[i].baseSalary,
                empList[i].workDay);
        }

        printf("=======================================================\n");
        printf("1. Trang truoc | 2. Trang sau | 0. Thoat\n");
        printf("Nhap lua chon: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Lua chon khong hop le!\n");
            continue;
        }
        getchar();

        if (choice == 1) {
            if (currentPage > 1) currentPage--;
            else printf("Ban dang o trang dau!\n");
        }
        else if (choice == 2) {
            if (currentPage < totalPage) currentPage++;
            else printf("Ban dang o trang cuoi!\n");
        }
        else if (choice == 0) {
            break;
        }
        else {
            printf("Lua chon khong hop le!\n");
        }
    }
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
        str[i] = (char)tolower((unsigned char)str[i]);
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
        if (scanf("%d", &sortOrder) != 1) {
            while (getchar() != '\n');
            sortOrder = 0;
        }
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

// ===================== FUNC 7: Time Keeping =====================

int validateDate(char date[]) {
    int d, m, y;
    if (sscanf(date, "%d/%d/%d", &d, &m, &y) != 3) return 0;
    if (y < 1900 || y > 2100) return 0;
    if (m < 1 || m > 12) return 0;

    int dayMax;
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            dayMax = 31; break;
        case 4: case 6: case 9: case 11:
            dayMax = 30; break;
        case 2:
            dayMax = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 29 : 28;
            break;
        default:
            return 0;
    }
    if (d < 1 || d > dayMax) return 0;
    return 1;
}

int isFutureDate(int d, int m, int y) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    int curD = t->tm_mday;
    int curM = t->tm_mon + 1;
    int curY = t->tm_year + 1900;

    if (y > curY) return 1;
    if (y == curY && m > curM) return 1;
    if (y == curY && m == curM && d > curD) return 1;
    return 0;
}

int checkDuplicateTimeSheet(char empId[], char date[]) {
    for (int i = 0; i < logCount; i++) {
        if (strcmp(timeList[i].empId, empId) == 0 &&
            strcmp(timeList[i].date, date) == 0) {
            return 1;
        }
    }
    return 0;
}

void CheckInWorkDay() {
    char checkInEmpId[20];
    char checkInDate[20];

    printf("\n=== CHAM NGAY CONG ===\n");

    // ================== NHAP VA KIEM TRA MA NV ==================
    int idx;
    while (1) {
        printf("Nhap ma nhan vien: ");
        inputString(checkInEmpId, 20);

        if (strlen(checkInEmpId) == 0) {
            printf("? Ma nhan vien khong duoc rong!\n");
            continue;
        }

        idx = findEmpByID(checkInEmpId);
        if (idx == -1) {
            printf("? Khong ton tai nhan vien nay! Nhap lai.\n");
            continue;
        }

        break;
    }

    // ================== NHAP VA KIEM TRA NGAY ==================
    int d, m, y;

    while (1) {
        printf("Nhap ngay cham cong (dd/mm/yyyy): ");
        inputString(checkInDate, 20);

        if (strlen(checkInDate) == 0) {
            printf("? Ngay cham cong khong duoc rong!\n");
            continue;
        }

        if (!validateDate(checkInDate)) {
            printf("? Ngay khong hop le! (vd: 22/11/2025)\n");
            continue;
        }

        sscanf(checkInDate, "%d/%d/%d", &d, &m, &y);

        if (isFutureDate(d, m, y)) {
            printf("? Khong the cham cong cho ngay trong tuong lai!\n");
            continue;
        }

        break;
    }

    // ================== KIEM TRA TRUNG TIMESHEET ==================
    if (checkDuplicateTimeSheet(checkInEmpId, checkInDate)) {
        printf("? Nhan vien da duoc cham cong vao ngay %s!\n", checkInDate);
        return;
    }

    // ================== TANG WORKDAY ==================
    empList[idx].workDay++;

    // ================== TAO LOG TIMESHEET ==================
    TimeSheet ts;
    sprintf(ts.logId, "LOG%03d", logCount + 1);
    strcpy(ts.empId, checkInEmpId);
    strcpy(ts.date, checkInDate);
    strcpy(ts.status, "Di lam");

    timeList[logCount++] = ts;

    printf("? Cham cong thanh cong cho NV [%s] ngay [%s]\n",
           checkInEmpId, checkInDate);
}

// ===================== FUNC 8: View Personal TimeSheet =====================
void ViewPersonalTimeSheet() {
    if (empCount == 0) {
        printf("\nDanh sach nhan vien trong! Khong the xem bang cong.\n");
        return;
    }

    if (logCount == 0) {
        printf("\nChua co du lieu cham cong nao trong he thong!\n");
        return;
    }

    char viewEmpId[20];
    int empIndex;
    
    printf("\n=== XEM BANG CONG CA NHAN ===\n");

  
    while (1) {
        printf("Nhap ma nhan vien can xem bang cong: ");
        inputString(viewEmpId, 20);

        if (strlen(viewEmpId) == 0) {
            printf("? Ma nhan vien khong duoc rong! Nhap lai.\n");
            continue;
        }

        empIndex = findEmpByID(viewEmpId);
        if (empIndex == -1) {
            printf("? Khong tim thay nhan vien co ma [%s]! Nhap lai.\n", viewEmpId);
            continue;
        }
        break; 
    }

    
    int found = 0;
    printf("\n");
    printf("==================================================\n");
    printf("         BANG CONG CA NHAN CUA NHAN VIEN          \n");
    printf("==================================================\n");
    printf("Ma NV     : %s\n", empList[empIndex].empId);
    printf("Ho ten    : %s\n", empList[empIndex].name);
    printf("Chuc vu   : %s\n", empList[empIndex].position);
    printf("--------------------------------------------------\n");
    printf("%-10s %-15s %-12s\n", "Ma Log", "Ngay cham", "Trang thai");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < logCount; i++) {
        if (strcmp(timeList[i].empId, viewEmpId) == 0) {
            printf("%-10s %-15s %-12s\n",
                   timeList[i].logId,
                   timeList[i].date,
                   timeList[i].status);
            found = 1;
        }
    }

    if (!found) {
        printf("    ---> Chua co lan cham cong nao!\n");
    } else {
        printf("--------------------------------------------------\n");
        printf("Tong cong: %d ngay da cham\n", empList[empIndex].workDay);
    }
    printf("==================================================\n");
}
