#ifndef STUDENT_H
#define STUDENT_H

/*
 * ============================================================================
 * Smart Student Management System - Student Module
 * Developer: Nischay
 * Assigned Responsibilities:
 *   1. Student structure and data handling
 *   2. Add Student
 *   3. View Students
 *   4. Search Student
 *   5. Update Student
 *   6. Delete Student
 * ============================================================================
 */

// Structure to store Student details
typedef struct {
    int student_id;      // Unique identification number for the student
    char name[50];       // Full name of the student
    int department_id;   // Associated Department ID
} Student;

// Student Module Functions
void addStudent(void);
void viewStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);

// Helper function to prevent duplicate Student IDs
int isDuplicateId(int student_id);

#endif /* STUDENT_H */
