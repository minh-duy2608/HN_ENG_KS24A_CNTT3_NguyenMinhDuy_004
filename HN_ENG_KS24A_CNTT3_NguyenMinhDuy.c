#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Food {
    int id;
    char name[50];
    char category[50];
    float price;
} Food;

typedef struct SingleNode {
    Food data;
    struct SingleNode *next;
} SingleNode;

typedef struct DoubleNode {
    Food data;
    struct DoubleNode *prev;
    struct DoubleNode *next;
} DoubleNode;

SingleNode* head = NULL;
DoubleNode* stoppedHead = NULL;
DoubleNode* stoppedTail = NULL;

void addFood() {
    Food newFood;
    printf("Nhap ID:");
    scanf("%d", &newFood.id);
    printf("Nhap ten mon:");
    getchar();
    gets(newFood.name);
    printf("Nhap danh muc:");
    gets(newFood.category);
    printf("Nhap gia:");
    scanf("%f", &newFood.price);

    SingleNode* newNode = (SingleNode*)malloc(sizeof(SingleNode));
    newNode->data = newFood;
    newNode->next = head;
    head = newNode;
    printf("Them mon an thanh cong\n");
}

void displayFood() {
    SingleNode* current = head;
    if (!current) {
        printf("Danh sach rong\n");
        return;
    }
    printf("Danh sach mon dang ban:\n");
    while (current) {
        printf("ID: %d, Ten: %s, Danh muc: %s, Gia: %.2f\n",
               current->data.id, current->data.name, current->data.category, current->data.price);
                    current = current->next;
    }
}

void updateFood() {
    int id;
    printf("Nhap ID mon can cap nhat: ");
    scanf("%d", &id);
    SingleNode* current = head;
    while (current) {
        if (current->data.id == id) {
            printf("Nhap ten moi: ");
            getchar();
            gets(current->data.name);
            printf("Nhap danh muc moi: ");
            gets(current->data.category);
            printf("Nhap gia moi: ");
            scanf("%f", &current->data.price);
            printf("Cap nhat thanh cong\n");
            return;
        }
        current = current->next;
    }
    printf("Khong tim thay mon co ID %d\n",id);
}

void stoppedFood() {
    int id;
    printf("Nhap ID mon can ngung ban: ");
    scanf("%d", &id);
    SingleNode* current = head, *prev = NULL;
    while (current) {
        if (current->data.id == id) {
            if (prev)
                prev->next = current->next;
            else head = current->next;
            DoubleNode* stoppedNode = (DoubleNode*)malloc(sizeof(DoubleNode));
            stoppedNode->data = current->data;
            stoppedNode->next = NULL;
            stoppedNode->prev = stoppedTail;

            if (stoppedTail) stoppedTail->next = stoppedNode;
            else stoppedHead = stoppedNode;
            stoppedTail = stoppedNode;

            free(current);
            printf("Da ngung ban mon an\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Khong tim thay mon co ID %d\n",id);
}

void displayStoppedFood() {
    DoubleNode* current = stoppedHead;
    if (!current) {
        printf("Khong co mon nao ngung ban.\n");
        return;
    }
    printf("Danh sach mon da ngung ban:\n");
    while (current) {
        printf("ID: %d, Ten: %s, Danh muc: %s, Gia: %.2f\n",
               current->data.id, current->data.name, current->data.category, current->data.price);
                    current = current->next;
    }
}

void searchByName() {
    char name[50];
    printf("Nhap ten mon can tim: ");
    getchar();
    gets(name);
    SingleNode* current = head;
    int found = 0;
    while (current) {
        if (strstr(current->data.name, name)) {
            printf("ID: %d | Ten: %s | Danh muc: %s | Gia: %.2f\n",
                   current->data.id, current->data.name, current->data.category, current->data.price);
            found = 1;
        }
        current = current->next;
    }
    if (!found) printf("Khong tim thay mon nao.\n");
}

void sortByPrice() {
    if (!head || !head->next) return;

    for (SingleNode *i = head; i; i = i->next) {
        for (SingleNode *j = i->next; j; j = j->next) {
            if (i->data.price > j->data.price) {
                Food temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    printf("Da sap xep theo gia tang dan.\n");
}

int main() {
    int choice;
    do {
        printf("- - - RESTAURANT - - - \n");
        printf("1.Them mon an\n");
        printf("2.Hien thi danh sach mon dang ban\n");
        printf("3.Cap nhat thong tin mon an\n");
        printf("4.Danh dau ngung ban\n");
        printf("5.Hien thi danh sach mon ngung ban\n");
        printf("6.Tim kiem theo ten mon\n");
        printf("7.Sap xep mon theo gia tang dan\n");
        printf("8.Thoat chuong trinh\n");
        printf("Chon chuc nang:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addFood();
                break;
            case 2:
                displayFood();
                break;
            case 3:
                updateFood();
                break;
            case 4:
                stoppedFood();
                break;
            case 5:
                displayStoppedFood();
                break;
            case 6:
                searchByName();
                break;
            case 7:
                sortByPrice();
                break;
        }
    }while (choice != 0);

    return 0;
}