#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 50
#define MAX_ENTRIES 100

// 通讯录条目
typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} Entry;

// 通讯录
typedef struct {
    Entry entries[MAX_ENTRIES];
    int num_entries;
} AddressBook;

// 添加通讯录条目
void add_entry(AddressBook* address_book) {
    if (address_book->num_entries >= MAX_ENTRIES) {
        printf("通讯录已满，无法添加条目。\n");
        return;
    }
    Entry* entry = &address_book->entries[address_book->num_entries];
    printf("请输入姓名：");
    scanf("%s", entry->name);
    printf("请输入电话号码：");
    scanf("%s", entry->phone);
    printf("请输入电子邮件：");
    scanf("%s", entry->email);
    address_book->num_entries++;
    printf("添加成功。\n");
}

// 删除通讯录条目
void delete_entry(AddressBook* address_book) {
    char name[MAX_NAME_LENGTH];
    printf("请输入要删除的姓名：");
    scanf("%s", &name);
    int found_index = -1;
    int i; 
    for ( i = 0; i < address_book->num_entries; i++) {
        if (strcmp(address_book->entries[i].name, name) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1) {
        printf("未找到匹配条目。\n");
        return;
    }
    for (i = found_index; i < address_book->num_entries - 1; i++) {
        address_book->entries[i] = address_book->entries[i + 1];
    }
    address_book->num_entries--;
    printf("删除成功。\n");
}

// 显示所有通讯录条目
void show_all_entries(AddressBook* address_book) {
    printf("姓名\t\t电话号码\t\t电子邮件\n");
    int i;
    for ( i = 0; i < address_book->num_entries; i++) {
        Entry* entry = &address_book->entries[i];
        printf("%s\t\t%s\t\t%s\n", entry->name, entry->phone, entry->email);
    }
}

// 查找通讯录条目
void find_entry(AddressBook* address_book) {
    char name[MAX_NAME_LENGTH];
    printf("请输入要查找的姓名：");
    scanf("%s", &name);
    int found_index = -1;
    int i;
    for (i = 0; i < address_book->num_entries; i++) {
        if (strcmp(address_book->entries[i].name, name) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1) {
        printf("未找到匹配条目。\n");
        return;
    }
    Entry* entry = &address_book->entries[found_index];
    printf("姓名：%s\n电话号码：%s\n电子邮件：%s\n", entry->name, entry->phone, entry->email);
}

// 保存通讯录到文件

void save_address_book(AddressBook* address_book, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("无法打开文件。\n");
		return;
	}
	int i;
	for (i = 0; i < address_book->num_entries; i++) {
		Entry* entry = &address_book->entries[i];
		fprintf(file, "%s %s %s\n", entry->name, entry->phone, entry->email);
	}
	fclose(file);
	printf("保存成功。\n");
}

// 从文件加载通讯录
void load_address_book(AddressBook* address_book, const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件。\n");
		return;
	}
	address_book->num_entries = 0;
	char line[100];
	while (fgets(line, sizeof(line), file) != NULL) {
		char name[MAX_NAME_LENGTH];
		char phone[MAX_PHONE_LENGTH];
		char email[MAX_EMAIL_LENGTH];
		sscanf(line, "%s %s %s", name, phone, email);
		Entry* entry = &address_book->entries[address_book->num_entries];
		strncpy(entry->name, name, MAX_NAME_LENGTH);
		strncpy(entry->phone, phone, MAX_PHONE_LENGTH);
		strncpy(entry->email, email, MAX_EMAIL_LENGTH);
		address_book->num_entries++;
	}
	fclose(file);
	printf("加载成功。\n");
}

// 主函数
int main() {
	AddressBook address_book = {0};
	char filename[] = "address_book.txt";
	int choice;
	while (1) {
		printf("请选择要执行的操作：\n");
		printf("1. 添加条目\n");
		printf("2. 删除条目\n");
		printf("3. 显示所有条目\n");
		printf("4. 查找条目\n");
		printf("5. 保存通讯录\n");
		printf("6. 加载通讯录\n");
		printf("7. 退出\n");
		printf("请输入选项编号：");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				add_entry(&address_book);
				break;
			case 2:
				delete_entry(&address_book);
				break;
			case 3:
				show_all_entries(&address_book);
				break;
			case 4:
				find_entry(&address_book);
				break;
			case 5:
				save_address_book(&address_book, filename);
				break;
			case 6:
				load_address_book(&address_book, filename);
				break;
			case 7:
				return 0;
			default:
			printf("无效选项。\n");
		}
	}
}

