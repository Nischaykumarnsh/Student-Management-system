#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define DATA_FILE "students.dat"

/*
 * Helper Function: isDuplicateId
 * Checks if a given student_id already exists in students.dat.
 * Returns 1 if duplicate exists, 0 otherwise.
 */
int isDuplicateId(int student_id) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        // If file does not exist yet, no records exist, so no duplicate.
        return 0;
    }

    Student s;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.student_id == student_id) {
            fclose(fp);
            return 1; // Duplicate found
        }
    }

    fclose(fp);
    return 0; // No duplicate found
}

/*
 * Helper Function: clearInputBuffer
 * Safely clears standard input buffer to handle newlines and prevent infinite loops on EOF.
 */
static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Function 1: addStudent
 * Asks user for Student ID, Name, and Department ID,
 * checks for duplicate Student IDs, and appends the student to students.dat.
 */
void addStudent(void) {
    Student s;

    printf("\n--- Add New Student ---\n");

    printf("Enter Student ID: ");
    if (scanf("%d", &s.student_id) != 1) {
        printf("Invalid input! Student ID must be an integer.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Prevent duplicate Student IDs
    if (isDuplicateId(s.student_id)) {
        printf("Error: Student ID %d already exists! Duplicate IDs are not allowed.\n", s.student_id);
        return;
    }

    printf("Enter Student Name: ");
    if (fgets(s.name, sizeof(s.name), stdin) != NULL) {
        s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline
    }

    printf("Enter Department ID: ");
    if (scanf("%d", &s.department_id) != 1) {
        printf("Invalid input! Department ID must be an integer.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Store the student in the file
    FILE *fp = fopen(DATA_FILE, "ab");
    if (fp == NULL) {
        printf("Error: Unable to open file for saving student record!\n");
        return;
    }

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("Success: Student added successfully!\n");
}

/*
 * Function 2: viewStudents
 * Reads and displays all stored students clearly from students.dat.
 * If there are no students, displays an appropriate message.
 */
void viewStudents(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo students found.\n");
        return;
    }

    Student s;
    int count = 0;

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (count == 0) {
            printf("\n============================================================\n");
            printf("%-15s %-30s %-15s\n", "Student ID", "Student Name", "Department ID");
            printf("============================================================\n");
        }
        printf("%-15d %-30s %-15d\n", s.student_id, s.name, s.department_id);
        count++;
    }

    fclose(fp);

    if (count == 0) {
        printf("\nNo students found.\n");
    } else {
        printf("============================================================\n");
        printf("Total Students: %d\n", count);
    }
}

/*
 * Function 3: searchStudent
 * Asks for Student ID, searches the file, and displays details if found.
 * If no matching ID exists, displays "Student not found".
 */
void searchStudent(void) {
    int search_id;

    printf("\n--- Search Student ---\n");
    printf("Enter Student ID: ");
    if (scanf("%d", &search_id) != 1) {
        printf("Invalid input! Student ID must be an integer.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("Student not found.\n");
        return;
    }

    Student s;
    int found = 0;

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.student_id == search_id) {
            printf("\n--- Student Found ---\n");
            printf("Student ID   : %d\n", s.student_id);
            printf("Student Name : %s\n", s.name);
            printf("Department ID: %d\n", s.department_id);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Student not found.\n");
    }
}

/*
 * Function 4: updateStudent
 * Asks for a Student ID, searches the file, and if found,
 * allows updating the Student Name and Department ID.
 */
void updateStudent(void) {
    int update_id;

    printf("\n--- Update Student ---\n");
    printf("Enter Student ID to update: ");
    if (scanf("%d", &update_id) != 1) {
        printf("Invalid input! Student ID must be an integer.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("Student not found.\n");
        return;
    }

    FILE *temp_fp = fopen("temp.dat", "wb");
    if (temp_fp == NULL) {
        printf("Error: Unable to open temporary file!\n");
        fclose(fp);
        return;
    }

    Student s;
    int found = 0;

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.student_id == update_id) {
            found = 1;
            printf("\n--- Current Details ---\n");
            printf("Student ID   : %d\n", s.student_id);
            printf("Student Name : %s\n", s.name);
            printf("Department ID: %d\n", s.department_id);

            printf("\nEnter New Student Name: ");
            if (fgets(s.name, sizeof(s.name), stdin) != NULL) {
                s.name[strcspn(s.name, "\n")] = '\0';
            }

            printf("Enter New Department ID: ");
            if (scanf("%d", &s.department_id) != 1) {
                printf("Invalid input! Department ID must be an integer.\n");
                clearInputBuffer();
                fclose(fp);
                fclose(temp_fp);
                remove("temp.dat");
                return;
            }
            clearInputBuffer();

            fwrite(&s, sizeof(Student), 1, temp_fp);
        } else {
            fwrite(&s, sizeof(Student), 1, temp_fp);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(DATA_FILE);
        rename("temp.dat", DATA_FILE);
        printf("Success: Student updated successfully!\n");
    } else {
        remove("temp.dat");
        printf("Student not found.\n");
    }
}

/*
 * Function 5: deleteStudent
 * Asks for a Student ID, searches the file, and if found,
 * deletes the student record from students.dat.
 */
void deleteStudent(void) {
    int delete_id;

    printf("\n--- Delete Student ---\n");
    printf("Enter Student ID to delete: ");
    if (scanf("%d", &delete_id) != 1) {
        printf("Invalid input! Student ID must be an integer.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("Student not found.\n");
        return;
    }

    FILE *temp_fp = fopen("temp.dat", "wb");
    if (temp_fp == NULL) {
        printf("Error: Unable to open temporary file!\n");
        fclose(fp);
        return;
    }

    Student s;
    int found = 0;

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.student_id == delete_id) {
            found = 1;
            // Record is skipped, so it will not be written to temp_fp (deleted)
        } else {
            fwrite(&s, sizeof(Student), 1, temp_fp);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(DATA_FILE);
        rename("temp.dat", DATA_FILE);
        printf("Success: Student deleted successfully!\n");
    } else {
        remove("temp.dat");
        printf("Student not found.\n");
    }
}
