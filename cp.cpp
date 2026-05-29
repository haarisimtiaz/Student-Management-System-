#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>

struct Student {
    int roll;
    char name[30];
    char section;
    float marks[5];
    char grade;
};

const int MAX_STUDENTS = 100;
Student students[MAX_STUDENTS];
int studentCount = 0;
std::string password = "Nate_Diaz";

void loadFromFile();
void saveToFile();
void Main_Menu();
void Student_Login();
void Student_Menu(int index, char sec);
void Profile_Menu(int index, char sec);
void subjectData(int index, char sec);
void calculateData(char sec, int sub, int index);
void Sec_stats(int index, char sec);
void Admin_Login();
void Admin_Menu();
void View_Menu();
void Search_By_Roll_No();
void Search_By_Section();
void Search_By_Grade();
void editMenu();
void EnterNewRecord();
void UpdateRecord();
void DeleteRecord();
void recordFormat();
void showRecord(int index);
char calculate_grade(int i);


int main() {
    loadFromFile();
    Main_Menu();
    saveToFile();
    return 0;
}

void loadFromFile() {

    std::ifstream fin("SampleData.txt");
    studentCount = 0;

    if (!fin) {
        std::cout << "File not found.\n";
        return;
    }

    fin >> studentCount;

    if (studentCount > MAX_STUDENTS) {
        studentCount = MAX_STUDENTS;
    }

    for (int i = 0; i < studentCount; i++) {
        if (!(fin >> students[i].roll
            >> students[i].name
            >> students[i].section
            >> students[i].marks[0]
            >> students[i].marks[1]
            >> students[i].marks[2]
            >> students[i].marks[3]
            >> students[i].marks[4]
            >> students[i].grade)) {
            studentCount = i;
            break;
        }
    }

    fin.close();
}

void saveToFile() {
    std::ofstream fout("SampleData.txt");

    if (!fout) {
        std::cout << "Could not open file for saving.\n";
        return;
    }

    fout << studentCount << '\n';

    for (int i = 0; i < studentCount; i++) {
        fout << students[i].roll << " "
            << students[i].name << " "
            << students[i].section << " "
            << students[i].marks[0] << " "
            << students[i].marks[1] << " "
            << students[i].marks[2] << " "
            << students[i].marks[3] << " "
            << students[i].marks[4] << " "
            << students[i].grade << '\n';
    }

    fout.close();
}
void Main_Menu() {
    system("cls");
    int choice;

    while (true) {
        std::cout << "\n===== MAIN MENU =====\n";
        std::cout << "1. Student Login\n";
        std::cout << "2. Admin Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            Student_Login();
            return;

        case 2:
            Admin_Login();
            return;

        case 3:
            return;

        default:
            system("cls");
            return;
        }
    }
}


void Student_Login() {
    system("cls");
    int choice;

    while (true) {
        std::cout << "\n===== STUDENT LOGIN =====\n";
        std::cout << "1. Enter Roll Number\n";
        std::cout << "2. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int rollNo;
            std::cout << "Enter roll number: ";
            std::cin >> rollNo;

            int index = -1;
            char sec = '\0';

            for (int i = 0; i < studentCount; i++) {
                if (students[i].roll == rollNo) {
                    index = i;
                    sec = students[i].section;
                    break;
                }
            }

            if (index != -1) {
                Student_Menu(index, sec);
                return;
            }
            else {
                system("cls");
                std::cout << "\nRoll number not found !\n";
                std::cout << "1. Try Again\n";
                std::cout << "2. Back\n";
                std::cout << "Enter choice: ";

                int again;
                std::cin >> again;
                switch (again) {
                case 1:
                    system("cls");
                    break;

                default:
                    system("cls");
                    Main_Menu();
                    return;
                }
            }
            break;
        }

        case 2:
            Main_Menu();
            return;

        default:
            system("cls");
        }
    }
}

void Student_Menu(int index, char sec) {
    system("cls");
    int choice;

    while (true) {
        std::cout << "\n===== STUDENT MENU =====\n";
        std::cout << "1. View My Profile\n";
        std::cout << "2. View Section Statistics\n";
        std::cout << "3. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            Profile_Menu(index, sec);
            break;

        case 2:
            Sec_stats(index, sec);
            break;

        case 3:
            Student_Login();
            break;
        default:
            system("cls");
        }
    }
}

void Profile_Menu(int index, char sec) {
    system("cls");
    int choice;

    while (true) {
        std::cout << "\n===================================================================================================\n";
        recordFormat();
        std::cout << "---------------------------------------------------------------------------------------------------\n";
        showRecord(index);
        std::cout << "===================================================================================================\n";
        std::cout << "\n1. View Subject Data\n";
        std::cout << "2. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            subjectData(index, sec);
            return;

        case 2:
            Student_Menu(index, sec);
            return;

        default:
            system("cls");
        }
    }
}

void subjectData(int index, char sec) {
    int choice;

    while (true) {
        std::cout << "\nSelect Subject:\n";
        std::cout << "1. ENA\n";
        std::cout << "2. CP\n";
        std::cout << "3. Ideology\n";
        std::cout << "4. Quran\n";
        std::cout << "5. Islamiat\n";
        std::cout << "6. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            calculateData(sec, 0, index);
            return;

        case 2:
            calculateData(sec, 1, index);
            return;

        case 3:
            calculateData(sec, 2, index);
            return;

        case 4:
            calculateData(sec, 3, index);
            return;

        case 5:
            calculateData(sec, 4, index);
            return;

        case 6:

            Student_Menu(index, sec);
            return;

        default:
            system("cls");
            Profile_Menu(index, sec);
            return;
        }
    }

}

void calculateData(char sec, int sub, int index) {
    int count = 0;
    float sum = 0;
    int aboveAvg = 0, belowAvg = 0;
    float highest = -1, lowest = 101;
    int highestRoll = -1, lowestRoll = -1;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].section == sec) {
            count++;
            sum += students[i].marks[sub];

            if (students[i].marks[sub] > highest) {
                highest = students[i].marks[sub];
                highestRoll = students[i].roll;
            }

            if (students[i].marks[sub] < lowest) {
                lowest = students[i].marks[sub];
                lowestRoll = students[i].roll;
            }
        }
    }

    float average = sum / count;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].section == sec) {
            if (students[i].marks[sub] >= average) aboveAvg++;
            else if (students[i].marks[sub] < average) belowAvg++;
        }
    }

    std::cout << "\n=====================================================\n";
    std::cout << "Total Students: " << count << '\n';
    std::cout << "Your Marks: " << students[index].marks[sub] << '\n';
    std::cout << "Average Marks: " << std::fixed << std::setprecision(2) << average << '\n';
    std::cout << "Difference from Average: ";
    if (average > students[index].marks[sub])
        std::cout << average - students[index].marks[sub] << " Below\n";
    else
        std::cout << students[index].marks[sub] - average << " Above\n";
    std::cout << "Students Above Average: " << aboveAvg << '\n';
    std::cout << "Students Below Average: " << belowAvg << '\n';
    std::cout << "Highest Marks: " << highest;
    std::cout << "\nLowest Marks: " << lowest;
    std::cout << "\n=====================================================\n";
    std::cout << "\n1) See choose another subject\n2) Go Back\n";

    int ch;
    std::cout << "\nEnter choice : ";
    std::cin >> ch;
    if (ch == 1) {
        int k;
        std::cout << "\nEnter new subject choice: ";
        std::cin >> k;
        calculateData(sec, k, index);

    }
    else
        Student_Menu(index, sec);

}
void Sec_stats(int index, char sec)
{
    system("cls");
    int totalStudents = 0;
    int countA = 0, countB = 0, countC = 0, countD = 0, countF = 0;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].section == sec) {
            totalStudents++;

            if (students[i].grade == 'A') countA++;
            else if (students[i].grade == 'B') countB++;
            else if (students[i].grade == 'C') countC++;
            else if (students[i].grade == 'D') countD++;
            else if (students[i].grade == 'F') countF++;
        }
    }

    std::cout << "\n============================================\n";
    std::cout << "Total Students in Section " << sec << " : " << totalStudents << "\n";
    std::cout << "============================================\n\n";

    std::cout << std::left
        << std::setw(12) << "Grade"
        << std::setw(12) << "Students"
        << std::setw(12) << "Percentage"
        << '\n';

    std::cout << "--------------------------------------------\n";

    auto printRow = [&](char grade, int count) {
        double percent = (totalStudents == 0) ? 0.0 : (count * 100.0 / totalStudents);
        std::cout << std::left
            << std::setw(12) << grade
            << std::setw(12) << count
            << std::setw(12) << std::fixed << std::setprecision(2) << percent << '\n';
        };

    printRow('A', countA);
    std::cout << "--------------------------------------------\n";
    printRow('B', countB);
    std::cout << "--------------------------------------------\n";
    printRow('C', countC);
    std::cout << "--------------------------------------------\n";
    printRow('D', countD);
    std::cout << "--------------------------------------------\n";
    printRow('F', countF);

    std::cout << "--------------------------------------------\n";
    std::cout << "\nEnter any character to go back: ";

    char ch;
    std::cin >> ch;
    system("cls");
    return;
}

void Admin_Login() {
    system("cls");
    int choice;

    while (true) {
        std::cout << "\n===== ADMIN LOGIN =====\n";
        std::cout << "1. Enter Password\n";
        std::cout << "2. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string enteredPass;
            std::cout << "Enter password: ";
            std::cin >> enteredPass;

            if (enteredPass == password) {
                Admin_Menu();
            }
            else
            {
                system("cls");
                std::cout << "Incorrect password.\n";
                std::cout << "1. Try Again\n";
                std::cout << "2. Back\n";
                std::cout << "Enter choice: ";

                int again;
                std::cin >> again;
                switch (again) {
                case 1:
                    system("cls");
                    break;

                default:
                    system("cls");
                    Main_Menu();
                    return;
                }
            }
            break;
        }

        case 2:
            system("cls");
            Main_Menu();
            return;

        default:
            system("cls");
        }
    }
}

void Admin_Menu() {
    system("cls");
    int choice;

    while (true) {
        std::cout << "\n===== ADMIN MENU =====\n";
        std::cout << "1. View Records\n";
        std::cout << "2. Edit Records\n";
        std::cout << "3. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            View_Menu();

        case 2:
            editMenu();

        case 3:
            Main_Menu();

        default:
            system("cls");
        }
    }
}

void View_Menu() {
    system("cls");
    int choice;
    while (true) {
        system("cls");
        std::cout << "\n===== VIEW MENU =====\n";
        std::cout << "1) Search by roll no.\n";
        std::cout << "2) Search by section\n";
        std::cout << "3) Search by Grade\n";
        std::cout << "4) Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            Search_By_Roll_No();
            break;
        case 2:
            Search_By_Section();
            break;
        case 3:
            Search_By_Grade();
            break;
        case 4:
            Admin_Menu();
            break;
        default:
            system("cls");
        }
    }
}

void Search_By_Roll_No()
{
    while (true)
    {
        system("cls");

        int choice;
        std::cout << "\n--- Search by Roll No ---\n";
        std::cout << "1) Enter roll no\n";
        std::cout << "2) Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int r;
            std::cout << "Enter roll no: ";
            std::cin >> r;

            bool found = false;
            std::cout << "\n";
            for (int i = 0; i < studentCount; i++) {
                if (students[i].roll == r) {
                    std::cout << "===================================================================================================\n";
                    recordFormat();
                    std::cout << "---------------------------------------------------------------------------------------------------\n";
                    showRecord(i);
                    std::cout << "===================================================================================================\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "Record not found!\n";
            }

            int nextChoice;
            std::cout << "\n1) View another\n";
            std::cout << "2) Back\n";
            std::cout << "Enter choice: ";
            std::cin >> nextChoice;

            switch (nextChoice)
            {
            case 1:
                break;

            case 2:
                return;

            default:
                return;
            }
            break;
        }

        case 2:
            system("cls");
            View_Menu();
            return;

        default:
            system("cls");
            break;
        }
    }
}
void Search_By_Section() {
    while (true) {
        system("cls");
        char sec;

        std::cout << "\nEnter Section A or B: ";
        std::cin >> sec;

        if (sec != 'A' && sec != 'B') {
            system("cls");
            continue;
        }

        bool found = false;
        int totalStudents = 0;

        std::cout << "\n";
        std::cout << "=======================================================================================\n";
        std::cout << std::left
            << std::setw(12) << "Roll No"
            << std::setw(20) << "Name"
            << std::setw(10) << "ENA"
            << std::setw(10) << "CP"
            << std::setw(10) << "Ideology"
            << std::setw(10) << "Quran"
            << std::setw(10) << "Islamiat"
            << std::setw(10) << "Grade"
            << '\n';
        std::cout << "---------------------------------------------------------------------------------------\n";

        for (int i = 0; i < studentCount; i++) {
            if (students[i].section == sec) {
                std::cout << std::left
                    << std::setw(12) << students[i].roll
                    << std::setw(20) << students[i].name
                    << std::setw(10) << students[i].marks[0]
                    << std::setw(10) << students[i].marks[1]
                    << std::setw(10) << students[i].marks[2]
                    << std::setw(10) << students[i].marks[3]
                    << std::setw(10) << students[i].marks[4]
                    << std::setw(10) << students[i].grade
                    << '\n';
                std::cout << "---------------------------------------------------------------------------------------\n";
                found = true;
                totalStudents++;
            }
        }

        if (!found) {
            std::cout << "No students found in section " << sec << "!\n";
            std::cout << "---------------------------------------------------------------------------------------\n";
        }

        std::cout << std::setw(20) << "Total Students : " << totalStudents << "\n";
        std::cout << "=======================================================================================\n";
        std::cout << "\nEnter any character to go back: ";

        char ch;
        std::cin >> ch;
        return;
    }
}
void Search_By_Grade() {
    while (1) {
        system("cls");
        char g;

        std::cout << "Enter Grade ( A, B , C , D , F ): ";
        std::cin >> g;
        if (g != 'A' && g != 'B' && g != 'C' && g != 'D' && g != 'F') {
            system("cls");
            continue;
        }

        bool found = false;
        int totalStudents = 0;

        std::cout << "\n";
        std::cout << "============================================================================================\n";
        std::cout << std::left
            << std::setw(12) << "Roll No"
            << std::setw(20) << "Name"
            << std::setw(12) << "Section"
            << std::setw(10) << "ENA"
            << std::setw(10) << "CP"
            << std::setw(10) << "Ideology"
            << std::setw(10) << "Quran"
            << std::setw(10) << "Islamiat"
            << '\n';
        std::cout << "--------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < studentCount; i++) {
            if (students[i].grade == g) {
                std::cout << std::left
                    << std::setw(12) << students[i].roll
                    << std::setw(20) << students[i].name
                    << std::setw(12) << students[i].section
                    << std::setw(10) << students[i].marks[0]
                    << std::setw(10) << students[i].marks[1]
                    << std::setw(10) << students[i].marks[2]
                    << std::setw(10) << students[i].marks[3]
                    << std::setw(10) << students[i].marks[4]
                    << '\n';
                std::cout << "--------------------------------------------------------------------------------------------\n";
                found = true;
                totalStudents++;
            }
        }

        if (!found) {
            std::cout << "No students found with grade " << g << "!\n";
            std::cout << "---------------------------------------------------------------\n";
        }

        std::cout << std::left
            << std::setw(12) << "Total"
            << std::setw(20) << "Students"
            << std::setw(12) << totalStudents
            << '\n';

        std::cout << "============================================================================================\n";
        std::cout << "\nEnter any character to go back: ";
        char ch;
        std::cin >> ch;
        system("cls");
        return;
    }

}
void editMenu() {
    system("cls");
    int choice;

    while (true) {
        std::cout << "\n===== EDIT MENU =====\n";
        std::cout << "1. Enter new record\n";
        std::cout << "2. Update record\n";
        std::cout << "3. Delete record\n";
        std::cout << "4. Back\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            EnterNewRecord();
            break;
        case 2:
            UpdateRecord();
            break;
        case 3:
            DeleteRecord();
            break;
        case 4:
            Admin_Menu();
            break;
        default:
            system("cls");
        }
    }
}
void EnterNewRecord() {
    while (true) {
        system("cls");

        if (studentCount >= MAX_STUDENTS) {
            std::cout << "\nError: Maximum student capacity reached.\n";
            std::cout << "Press any key to go back...";
            char ch;
            std::cin >> ch;
            system("cls");
            editMenu();
        }

        std::cout << "\n===== ADD RECORD =====\n";

        int rollNo;
        bool duplicate;

        while (true) {
            std::cout << "\nEnter 6-digit Roll Number: ";
            if (!(std::cin >> rollNo) || rollNo < 100000 || rollNo > 999999) {
                std::cout << "\n\nInvalid entry. Try again.\n\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            duplicate = false;
            for (int i = 0; i < studentCount; i++) {
                if (students[i].roll == rollNo) {
                    duplicate = true;
                    break;
                }
            }

            if (duplicate) {
                std::cout << "\n\nInvalid entry. Try again.\n\n";
                continue;
            }

            break;
        }

        students[studentCount].roll = rollNo;

        std::cout << "\nEnter Name: ";
        std::cin >> std::ws;
        std::cin.getline(students[studentCount].name, 30);

        char sec;
        std::cout << "Enter Section (A or B): ";
        std::cin >> sec;
        while (sec != 'A' && sec != 'B') {
            std::cout << "\nInvalid section. Enter A or B: ";
            std::cin >> sec;
        }
        students[studentCount].section = sec;
        for (int i = 0; i < 5; i++) {
            std::cout << "Enter marks (1-100) for ";
            if (i == 0) std::cout << "ENA: ";
            else if (i == 1) std::cout << "CP: ";
            else if (i == 2) std::cout << "Ideology: ";
            else if (i == 3) std::cout << "Quran: ";
            else std::cout << "Islamiat: ";

            while (!(std::cin >> students[studentCount].marks[i])) {
                std::cout << "\nInvalid input.\nEnter marks again: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }

            while (students[studentCount].marks[i] < 0 || students[studentCount].marks[i] > 100) {
                std::cout << "INVALID MARKS. Enter again: ";
                std::cin >> students[studentCount].marks[i];
            }
        }

        calculate_grade(studentCount);
        studentCount++;
        saveToFile();

        std::cout << "\nNew record successfully added!\n";
        std::cout << "===================================================================================================\n";
        recordFormat();
        std::cout << "---------------------------------------------------------------------------------------------------\n";
        showRecord(studentCount - 1);
        std::cout << "===================================================================================================\n";
        std::cout << "\nPress any key to go back...";
        char ch;
        std::cin >> ch;
        system("cls");
        editMenu();

    }
}

void UpdateRecord() {
    while (true) {
        system("cls");

        int searchRoll;
        std::cout << "\n===== UPDATE RECORD =====\n";
        std::cout << "\nEnter Roll Number to update: ";
        while (!(std::cin >> searchRoll)) {
            std::cout << "\nInvalid input.\n\nEnter Roll Number again: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        int index = -1;
        for (int i = 0; i < studentCount; i++) {
            if (students[i].roll == searchRoll) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            std::cout << "\nError: Roll number not found.\n";
            std::cout << "1) Retry\n";
            std::cout << "2) Go back\n";
            std::cout << "Enter choice: ";

            int ch;
            std::cin >> ch;

            if (ch == 1) {
                continue;
            }
            else {
                system("cls");
                return;
            }
        }

        std::cout << "\nRecord found!\n";
        std::cout << "\n===================================================================================================\n";
        recordFormat();
        std::cout << "---------------------------------------------------------------------------------------------------\n";
        showRecord(index);
        std::cout << "===================================================================================================\n";

        std::cout << "\nDo you want to edit this record?\n";
        std::cout << "1) Yes\n";
        std::cout << "2) No / Go back\n";
        std::cout << "Enter choice: ";

        int confirm;
        std::cin >> confirm;

        if (confirm == 2) {
            system("cls");
            return;
        }
        else if (confirm != 1) {
            continue;
        }

        std::cout << "\nEnter new details:\n";

        std::cout << "\nEnter New Name: ";
        std::cin >> std::ws;
        std::cin.getline(students[index].name, 30);

        char sec;
        std::cout << "\nEnter New Section (A or B): ";
        std::cin >> sec;
        while (sec != 'A' && sec != 'B') {
            std::cout << "Invalid section. Enter A or B: ";
            std::cin >> sec;
        }
        students[index].section = sec;

        for (int i = 0; i < 5; i++) {
            std::cout << "\nEnter new marks for ";
            if (i == 0) std::cout << "ENA: ";
            else if (i == 1) std::cout << "CP: ";
            else if (i == 2) std::cout << "Ideology: ";
            else if (i == 3) std::cout << "Quran: ";
            else std::cout << "Islamiat: ";

            while (!(std::cin >> students[index].marks[i])) {
                std::cout << "Invalid input. Enter marks again: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }

            while (students[index].marks[i] < 0 || students[index].marks[i] > 100) {
                std::cout << "Marks must be between 0 and 100. Enter again: ";
                std::cin >> students[index].marks[i];
            }
        }

        calculate_grade(index);
        saveToFile();

        std::cout << "\nRecord successfully updated!\n";
        std::cout << "\n===================================================================================================\n";
        recordFormat();
        std::cout << "---------------------------------------------------------------------------------------------------\n";
        showRecord(index);
        std::cout << "===================================================================================================\n";
        std::cout << "\nPress any key to go back...";

        char ch;
        std::cin >> ch;
        system("cls");
        return;
    }
}

void DeleteRecord() {
    while (true) {
        system("cls");

        int deleteRoll;
        std::cout << "\n===== DELETE RECORD =====\n";
        std::cout << "\nEnter Roll Number to delete: ";
        while (!(std::cin >> deleteRoll)) {
            std::cout << "Invalid input. Enter Roll Number again: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        int index = -1;
        for (int i = 0; i < studentCount; i++) {
            if (students[i].roll == deleteRoll) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            std::cout << "Error: Roll number not found.\n";
            std::cout << "1) Retry\n";
            std::cout << "2) Go back\n";
            std::cout << "Enter choice: ";

            int ch;
            std::cin >> ch;

            if (ch == 1) {
                continue;
            }
            else {
                system("cls");
                return;
            }
        }

        std::cout << "\nRecord found!\n";
        std::cout << "===================================================================================================\n";
        recordFormat();
        std::cout << "---------------------------------------------------------------------------------------------------\n";
        showRecord(index);
        std::cout << "===================================================================================================\n";

        std::cout << "\nAre you sure you want to delete this record?\n";
        std::cout << "1) Yes\n";
        std::cout << "2) No / Go back\n";
        std::cout << "Enter choice: ";

        int confirm;
        std::cin >> confirm;

        if (confirm == 2) {
            system("cls");
            return;
        }
        else if (confirm != 1) {
            continue;
        }

        for (int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }

        studentCount--;
        saveToFile();

        std::cout << "\nRecord successfully deleted!\n";
        std::cout << "\nPress any key to go back...";

        char ch;
        std::cin >> ch;
        system("cls");
        return;
    }
}

void recordFormat() {
    std::cout << std::left
        << std::setw(12) << "Roll No"
        << std::setw(20) << "Name"
        << std::setw(12) << "Section"
        << std::setw(10) << "ENA"
        << std::setw(10) << "CP"
        << std::setw(10) << "Ideology"
        << std::setw(10) << "Quran"
        << std::setw(10) << "Islamiat"
        << std::setw(10) << "Grade"
        << '\n';
}
void showRecord(int index) {
    std::cout << std::left
        << std::setw(12) << students[index].roll
        << std::setw(20) << students[index].name
        << std::setw(12) << students[index].section
        << std::setw(10) << students[index].marks[0]
        << std::setw(10) << students[index].marks[1]
        << std::setw(10) << students[index].marks[2]
        << std::setw(10) << students[index].marks[3]
        << std::setw(10) << students[index].marks[4]
        << std::setw(10) << students[index].grade
        << '\n';
}
char calculate_grade(int i) {
    float sum = (0.4f * students[i].marks[0]) +
        (0.3f * students[i].marks[1]) +
        (0.1f * students[i].marks[2]) +
        (0.1f * students[i].marks[3]) +
        (0.1f * students[i].marks[4]);

    if (sum >= 90 && sum <= 100)
        students[i].grade = 'A';
    else if (sum >= 80 && sum < 90)
        students[i].grade = 'B';
    else if (sum >= 60 && sum < 80)
        students[i].grade = 'C';
    else if (sum >= 40 && sum < 60)
        students[i].grade = 'D';
    else
        students[i].grade = 'F';

    return students[i].grade;
}