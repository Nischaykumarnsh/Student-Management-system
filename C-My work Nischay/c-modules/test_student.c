/*
 * Standalone Test Driver for Student Module
 * NOTE: This is for local testing and demonstration only.
 * The core module remains modular in student.h and student.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include "student.h"

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    int choice;

    while (1) {
        printf("\n====================================\n");
        printf("   TEST DRIVER: STUDENT MODULE\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit Test\n");
        printf("------------------------------------\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            break;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Exiting test driver. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please choose 1 to 6.\n");
        }
    }

    return 0;
}
