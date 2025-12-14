
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

void addPatient();
void viewPatients();
void searchPatient();
void deletePatient();
void updatePatient();
void doctorList();
void bookAppointment();

FILE *fp;

int main() {
    int choice;

    while (1) {
        printf("\n===== HOSPITAL MANAGEMENT SYSTEM =====\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Update Patient\n");
        printf("6. Doctor List\n");
        printf("7. Book Appointment\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume leftover newline

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: updatePatient(); break;
            case 6: doctorList(); break;
            case 7: bookAppointment(); break;
            case 8: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}

void addPatient() {
    struct Patient p;
    fp = fopen("patients.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    getchar(); // consume leftover newline
    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0; // remove newline

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar(); // consume leftover newline

    printf("Enter Disease: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0; // remove newline

    fprintf(fp, "%d|%s|%d|%s\n", p.id, p.name, p.age, p.disease);
    fclose(fp);

    printf("Patient Added Successfully!\n");
}

void viewPatients() {
    struct Patient p;
    char line[200];
    fp = fopen("patients.txt", "r");
    if (!fp) {
        printf("No patient records found.\n");
        return;
    }

    printf("\n--- Patient Records ---\n");
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%[^|]|%d|%[^\n]", &p.id, p.name, &p.age, p.disease);
        printf("ID: %d | Name: %s | Age: %d | Disease: %s\n",
               p.id, p.name, p.age, p.disease);
    }
    fclose(fp);
}

void searchPatient() {
    struct Patient p;
    char line[200];
    int id, found = 0;

    printf("Enter Patient ID to Search: ");
    scanf("%d", &id);
    getchar(); // consume newline

    fp = fopen("patients.txt", "r");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%[^|]|%d|%[^\n]", &p.id, p.name, &p.age, p.disease);
        if (p.id == id) {
            printf("Record Found!\n");
            printf("ID: %d | Name: %s | Age: %d | Disease: %s\n",
                   p.id, p.name, p.age, p.disease);
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (!found) printf("Patient not found.\n");
}

void deletePatient() {
    struct Patient p;
    char line[200];
    int id, found = 0;

    printf("Enter Patient ID to Delete: ");
    scanf("%d", &id);
    getchar();

    FILE *temp = fopen("temp.txt", "w");
    fp = fopen("patients.txt", "r");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%[^|]|%d|%[^\n]", &p.id, p.name, &p.age, p.disease);
        if (p.id != id) {
            fprintf(temp, "%d|%s|%d|%s\n", p.id, p.name, p.age, p.disease);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found) printf("Patient Deleted.\n");
    else printf("Record Not Found.\n");
}

void updatePatient() {
    struct Patient p;
    char line[200];
    int id, found = 0;

    printf("Enter Patient ID to Update: ");
    scanf("%d", &id);
    getchar();

    FILE *temp = fopen("temp.txt", "w");
    fp = fopen("patients.txt", "r");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%[^|]|%d|%[^\n]", &p.id, p.name, &p.age, p.disease);
        if (p.id == id) {
            found = 1;
            printf("Enter New Name: ");
            fgets(p.name, sizeof(p.name), stdin);
            p.name[strcspn(p.name, "\n")] = 0;

            printf("Enter New Age: ");
            scanf("%d", &p.age);
            getchar();

            printf("Enter New Disease: ");
            fgets(p.disease, sizeof(p.disease), stdin);
            p.disease[strcspn(p.disease, "\n")] = 0;
        }
        fprintf(temp, "%d|%s|%d|%s\n", p.id, p.name, p.age, p.disease);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found) printf("Patient Updated!\n");
    else printf("Record Not Found.\n");
}

void doctorList() {
    printf("\n--- Doctor List ---\n");
    printf("1. Dr. Rajesh (Cardiologist)\n");
    printf("2. Dr. Anita (Neurologist)\n");
    printf("3. Dr. Mehta (Orthopedic)\n");
    printf("4. Dr. Priya (General Physician)\n");
}

void bookAppointment() {
    int doc, id;

    printf("Enter Patient ID: ");
    scanf("%d", &id);
    getchar();

    printf("\nSelect Doctor:\n");
    printf("1. Dr. Rajesh\n");
    printf("2. Dr. Anita\n");
    printf("3. Dr. Mehta\n");
    printf("4. Dr. Priya\n");
    printf("Enter choice: ");
    scanf("%d", &doc);
    getchar();

    printf("Appointment booked successfully!\n");
}
