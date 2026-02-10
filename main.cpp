#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Student class
class Student {
public:
    string name;
    string index;
    
    Student(string n = "", string idx = "") {
        name = n;
        index = idx;
    }
    
    void display() {
        cout << index << " - " << name << endl;
    }
};

// Attendance Session class
class AttendanceSession {
public:
    string courseCode;
    string date;
    string time;
    int duration;
    
    AttendanceSession(string code = "", string d = "", string t = "", int h = 1) {
        courseCode = code;
        date = d;
        time = t;
        duration = h;
    }
    
    void display() {
        cout << courseCode << " on " << date << " at " << time << " (" << duration << " hours)" << endl;
    }
};

// Global lists
vector<Student> students;
vector<AttendanceSession> sessions;

// Save students to file
void saveStudents() {
    ofstream file("students.txt");
    for (Student s : students) {
        file << s.index << "," << s.name << endl;
    }
    file.close();
}

// Load students from file
void loadStudents() {
    ifstream file("students.txt");
    string line;
    while (getline(file, line)) {
        size_t comma = line.find(",");
        if (comma != string::npos) {
            string idx = line.substr(0, comma);
            string name = line.substr(comma + 1);
            students.push_back(Student(name, idx));
        }
    }
    file.close();
}

// Save sessions to file
void saveSessions() {
    ofstream file("sessions.txt");
    for (AttendanceSession ses : sessions) {
        file << ses.courseCode << "," << ses.date << "," << ses.time << "," << ses.duration << endl;
    }
    file.close();
}

// ===== MENU FUNCTIONS =====
void registerStudent() {
    string name, index;
    cout << "\nEnter student index: ";
    cin >> index;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, name);
    students.push_back(Student(name, index));
    saveStudents();
    cout << "Student registered!\n";
}

void viewStudents() {
    cout << "\n=== STUDENTS ===" << endl;
    for (Student s : students) {
        s.display();
    }
}

void createSession() {
    string code, date, time;
    int hours;
    cout << "\nEnter course code: ";
    cin >> code;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter time (HH:MM): ";
    cin >> time;
    cout << "Enter duration (hours): ";
    cin >> hours;
    sessions.push_back(AttendanceSession(code, date, time, hours));
    saveSessions();
    cout << "Session created!\n";
}

void viewSessions() {
    cout << "\n=== SESSIONS ===" << endl;
    for (AttendanceSession ses : sessions) {
        ses.display();
    }
}

// ===== MAIN =====
int main() {
    loadStudents();
    
    int choice;
    do {
        cout << "\n========== ATTENDANCE SYSTEM ==========" << endl;
        cout << "1. Register Student" << endl;
        cout << "2. View Students" << endl;
        cout << "3. Create Lecture Session (WEEK 2)" << endl;
        cout << "4. View Sessions (WEEK 2)" << endl;
        cout << "5. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: createSession(); break;
            case 4: viewSessions(); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    
    return 0;
}
