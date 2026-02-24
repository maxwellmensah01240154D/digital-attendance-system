#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// Student Class
class Student {
public:
    string name;
    string index;
    string department;  // NEW
    int level;          // NEW

    // Constructor with all fields
    Student(string n = "", string idx = "", string dept = "", int lvl = 0) {
        name = n;
        index = idx;
        department = dept;
        level = lvl;
    }

    void display() {
        cout << index << " - " << name << " | " << department << " | Level " << level;
    }
    
    // For saving to CSV
    string toFileString() {
        return index + "," + name + "," + department + "," + to_string(level);
    }
};

// Attendance Session Class
class AttendanceSession {
public:
    string courseCode;
    string date;
    string time;
    int duration;
    vector<string> present;
    vector<string> late;
    vector<string> absent;
    
    AttendanceSession(string code = "", string d = "", string t = "", int h = 1) {
        courseCode = code;
        date = d;
        time = t;
        duration = h;
    }
    
    void markPresent(string idx) { present.push_back(idx); }
    void markLate(string idx) { late.push_back(idx); }
    void markAbsent(string idx) { absent.push_back(idx); }
    
    bool isMarked(string idx) {
        for (string i : present) if (i == idx) return true;
        for (string i : late) if (i == idx) return true;
        for (string i : absent) if (i == idx) return true;
        return false;
    }
    
    void display() {
        cout << "\n=== SESSION ===\n";
        cout << courseCode << " | " << date << " | " << time << " (" << duration << "h)\n";
        cout << "Present: " << present.size() << " | Late: " << late.size() << " | Absent: " << absent.size() << "\n";
    }
    
    void report() {
        cout << "\n=== ATTENDANCE REPORT ===\n";
        cout << courseCode << " - " << date << "\n";
        cout << "PRESENT:";
        for (string i : present) cout << " " << i;
        cout << "\nLATE:";
        for (string i : late) cout << " " << i;
        cout << "\nABSENT:";
        for (string i : absent) cout << " " << i;
        cout << "\n";
    }
    
   void saveToFile() {
    string filename = "session_" + courseCode + "_" + date + ".csv";
    ofstream f(filename);
    
    if (!f.is_open()) {
        cout << "Error: Cannot open " << filename << " for writing!\n";
        return;
    }
    
    // Write session header
    f << "COURSE,DATE,TIME,DURATION\n";
    f << courseCode << "," << date << "," << time << "," << duration << "\n\n";
    
    // Write attendance data with headers
    f << "STATUS,STUDENT_INDEX\n";
    
    // Write present students
    for (string i : present) {
        f << "PRESENT," << i << "\n";
    }
    
    // Write late students
    for (string i : late) {
        f << "LATE," << i << "\n";
    }
    
    // Write absent students
    for (string i : absent) {
        f << "ABSENT," << i << "\n";
    }
    
    f.close();
    cout << "Session saved to " << filename << "\n";
}
// Global Data
vector<Student> students;
vector<AttendanceSession> sessions;

// File Operations


void saveStudents() {
   void loadStudents() {
    ifstream f("students.csv");
    if (!f.is_open()) {
        cout << "No existing students.csv found. Starting fresh.\n";
        return;
    }
    
    string line;
    students.clear();
    
    // Skip the header line
    getline(f, line);
    
    // Read each student record
    while (getline(f, line)) {
        if (line.empty()) continue;
        
        // Parse CSV: index,name,department,level
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            string idx = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string dept = line.substr(pos2 + 1, pos3 - pos2 - 1);
            int level = stoi(line.substr(pos3 + 1));
            
            students.push_back(Student(name, idx, dept, level));
        }
    }
    f.close();
    cout << "Loaded " << students.size() << " students from students.csv\n";
} ofstream f("students.csv");  // Changed to .csv
    
    if (!f.is_open()) {
        cout << "Error: Cannot open students.csv for writing!\n";
        return;
    }
    
    // Write CSV header
    f << "INDEX,NAME,DEPARTMENT,LEVEL\n";
    
    // Write each student's data
    for (Student s : students) {
        f << s.index << "," 
          << s.name << "," 
          << s.department << "," 
          << s.level << "\n";
    }
    
    f.close();
    cout << "Students saved to students.csv (" << students.size() << " records)\n";
}

// Improved Loading with Error Handling
void loadSessions() {
    ifstream f("sessions.csv");
    if (!f.is_open()) {
        // Try backup
        ifstream backup("sessions_backup.csv");
        if (backup.is_open()) {
            cout << "Main file not found. Loading from backup...\n";
            f = move(backup);
        } else {
            cout << "No existing sessions. Starting fresh.\n";
            return;
        }
    }
    
    string line;
    sessions.clear();
    
    // Skip header
    getline(f, line);
    
    while (getline(f, line)) {
        if (line.empty()) continue;
        
        size_t p1 = line.find(",");
        size_t p2 = line.find(",", p1+1);
        size_t p3 = line.find(",", p2+1);
        
        if (p1 == string::npos || p2 == string::npos || p3 == string::npos) {
            cout << "Skipping invalid line: " << line << "\n";
            continue;
        }
        
        string code = line.substr(0, p1);
        string date = line.substr(p1+1, p2-p1-1);
        string time = line.substr(p2+1, p3-p2-1);
        
        try {
            int dur = stoi(line.substr(p3+1));
            sessions.push_back(AttendanceSession(code, date, time, dur));
        } catch (...) {
            cout << "Invalid duration in line: " << line << "\n";
        }
    }
    f.close();
    cout << "Loaded " << sessions.size() << " sessions from CSV.\n";
}
// Improved File Operations with Backup
void saveSessions() {
    // Backup old file
    ifstream check("sessions.csv");
    if (check.good()) {
        check.close();
        rename("sessions.csv", "sessions_backup.csv");
    }
    
    // Save new sessions
    ofstream f("sessions.csv");
    if (!f.is_open()) {
        cout << "Error: Cannot save sessions!\n";
        return;
    }
    
    // Write CSV header
    f << "COURSE_CODE,DATE,TIME,DURATION\n";
    
    // Write each session
    for (AttendanceSession s : sessions) {
        f << s.courseCode << "," 
          << s.date << "," 
          << s.time << "," 
          << s.duration << "\n";
        s.saveToFile(); // Save individual session file
    }
    f.close();
    cout << "Sessions saved to sessions.csv (" << sessions.size() << " sessions)\n";
    cout << "Backup created as sessions_backup.csv\n";
}
    
    for (AttendanceSession s : sessions) {
        f << s.courseCode << "," << s.date << "," << s.time << "," << s.duration << "\n";
        s.saveToFile(); // Save individual session file
    }
    f.close();
    cout << "Sessions saved successfully. Backup created.\n";
}
// ============================================
// HELPER FUNCTIONS - IMPROVED READABILITY
// ============================================

// Display a formatted header
void showHeader(string title) {
    cout << "\n========================================\n";
    cout << "   " << title << "\n";
    cout << "========================================\n";
}

// Show success message with checkmark
void showSuccess(string msg) {
    cout << "Successful " << msg << "\n";
}

// Show error message with X mark
void showError(string msg) {
    cout << "An Error " << msg << "\n";
}

// Show warning message
void showWarning(string msg) {
    cout << "Warning " << msg << "\n";
}

// Pause and wait for user to press Enter
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Ask user for confirmation
bool confirm(string msg) {
    char ch;
    cout << msg << " (y/n): ";
    cin >> ch;
    return (ch == 'y' || ch == 'Y');
}
// Validation for 8 digits + 1 letter (e.g., 01240154D)
// Validate index format: 8 digits + 1 letter (e.g., 01240154D)
bool validIndex(string index) {
    // Check length is exactly 9 characters
    if (index.length() != 9) {
        return false;
    }
    
    // Check first 8 characters are digits
    for (int i = 0; i < 8; i++) {
        if (!isdigit(index[i])) {
            return false;
        }
    }
    
    // Check last character is a letter
    if (!isalpha(index[8])) {
        return false;
    }
    
    return true;
}
bool studentExists(string i) { 
    for (Student s : students) if (s.index == i) return true; 
    return false; 
}

void registerStudent() {
    string name, index, department;
    int level;
    
    cout << "\n=== STUDENT REGISTRATION ===\n";
    
    // Get Name
    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, name);
    
    // Get Index Number with validation
    do {
        cout << "Enter Index Number (8 digits + 1 letter, e.g., 01240154D): ";
        cin >> index;
        
        if (!validIndex(index)) {
            cout << "Invalid format! Must be 8 digits followed by a letter.\n";
        } else if (studentExists(index)) {
            cout << "Index already exists! Use another.\n";
            index = "";
        }
    } while (index.empty() || !validIndex(index));
    
    // Get Department
    cout << "Enter Department: ";
    cin.ignore();
    getline(cin, department);
    
    // Get Level
    do {
        cout << "Enter Level (100, 200, 300, 400): ";
        cin >> level;
        if (level != 100 && level != 200 && level != 300 && level != 400) {
            cout << "Invalid level! Must be 100, 200, 300, or 400.\n";
        }
    } while (level != 100 && level != 200 && level != 300 && level != 400);
    
    // Create student with ALL information
    Student newStudent(name, index, department, level);
    students.push_back(newStudent);
    saveStudents();
    
    cout << "\n Student registered successfully!\n";
    cout << "Name: " << name << "\n";
    cout << "Index: " << index << "\n";
    cout << "Department: " << department << "\n";
    cout << "Level: " << level << "\n";
}
void viewStudents() {
    showHeader("STUDENT LIST");
    
    if (students.empty()) {
        showWarning("No students registered.");
        pause();
        return;
    }
    
    for (int i=0; i<students.size(); i++) {
        cout << i+1 << ". ";
        students[i].display();
        cout << "\n";
    }
    
    showSuccess("Total: " + to_string(students.size()) + " student(s)");
    pause();
}

void searchStudent() {
    string i; cout << "Index: "; cin >> i;
    for (Student s : students) if (s.index == i) { 
        cout << "Found: "; s.display(); cout << "\n"; return; 
    }
    cout << "Not found\n";
}

// Session Functions
void createSession() {
    string c, d, t; int h;
    cout << "Course: "; cin >> c;
    cout << "Date (YYYY-MM-DD): "; cin >> d;
    cout << "Time (HH:MM): "; cin >> t;
    cout << "Hours (1-4): "; cin >> h;
    if (h<1 || h>4) { cout << "Invalid hours\n"; return; }
    sessions.push_back(AttendanceSession(c, d, t, h));
    saveSessions();
    cout << "Session created!\n";
}

void viewSessions() {
    if (sessions.empty()) cout << "\nNo sessions\n";
    else for (int i=0; i<sessions.size(); i++) {
        cout << "\n" << i+1 << "."; sessions[i].display();
    }
}

// Attendance Marking
void markAttendance() {
    if (sessions.empty()) { cout << "\nNo sessions\n"; return; }
    if (students.empty()) { cout << "\nNo students\n"; return; }
    
    cout << "\nSelect session:\n";
    for (int i=0; i<sessions.size(); i++) cout << i+1 << ". " << sessions[i].courseCode << "\n";
    int s; cin >> s; s--;
    if (s<0 || s>=sessions.size()) { cout << "Invalid\n"; return; }
    
    sessions[s].display();
    cout << "\nStudents:\n";
    for (Student stu : students) {
        cout << stu.index << " - " << stu.name;
        if (sessions[s].isMarked(stu.index)) cout << " [DONE]";
        cout << "\n";
    }
    
    string idx; int st;
    cout << "\nEnter index (0 to finish): ";
    while (cin >> idx, idx != "0") {
        if (!studentExists(idx)) { cout << "Not found. Try: "; continue; }
        if (sessions[s].isMarked(idx)) { cout << "Already marked. Next: "; continue; }
        cout << "1=Present 2=Late 3=Absent: "; cin >> st;
        if (st==1) { sessions[s].markPresent(idx); cout << "Present\n"; }
        else if (st==2) { sessions[s].markLate(idx); cout << "Late\n"; }
        else if (st==3) { sessions[s].markAbsent(idx); cout << "Absent\n"; }
        else cout << "Invalid\n";
        cout << "Next index (0 to finish): ";
    }
    saveSessions();
    sessions[s].report();
}

// Summary Function (this is the good one - keep it!)
void summary() {
    if (sessions.empty()) { cout << "\nNo sessions\n"; return; }
    int p=0, l=0, a=0;
    for (auto ses : sessions) { 
        p += ses.present.size(); 
        l += ses.late.size(); 
        a += ses.absent.size(); 
    }
    int t = p+l+a;
    cout << "\n=== SUMMARY ===\n";
    cout << "Sessions: " << sessions.size() << "\n";
    cout << "Total marks: " << t << "\n";
    if (t>0) {
        cout << "Present: " << p << " (" << (p*100/t) << "%)\n";
        cout << "Late: " << l << " (" << (l*100/t) << "%)\n";
        cout << "Absent: " << a << " (" << (a*100/t) << "%)\n";
    }
    
    char save;
    cout << "\nSave summary to file? (y/n): ";
    cin >> save;
    if (save == 'y' || save == 'Y') {
        ofstream file("summary_report.txt");
        file << "ATTENDANCE SUMMARY REPORT\n";
        file << "=========================\n";
        
        // Get current date
        time_t now = time(0);
        char* dt = ctime(&now);
        file << "Date: " << dt;
        
        file << "Sessions: " << sessions.size() << "\n";
        file << "Total Marks: " << t << "\n\n";
        file << "Present: " << p;
        if (t>0) file << " (" << (p*100/t) << "%)";
        file << "\nLate: " << l;
        if (t>0) file << " (" << (l*100/t) << "%)";
        file << "\nAbsent: " << a;
        if (t>0) file << " (" << (a*100/t) << "%)";
        file << "\n";
        file.close();
        cout << "Summary saved to summary_report.txt\n";
    }
}

// MAIN FUNCTION
int main() {
    loadStudents(); 
    loadSessions();
    
    int ch;
    do {
        cout << "\n=== WEEK 3 ATTENDANCE ===\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Create Session\n";
        cout << "5. View Sessions\n";
        cout << "6. Mark Attendance\n";
        cout << "7. Session Report\n";
        cout << "8. Overall Summary\n";
        cout << "9. Exit\n";
        cout << "Choice: ";
        cin >> ch;
        
        if (ch==1) registerStudent();
        else if (ch==2) viewStudents();
        else if (ch==3) searchStudent();
        else if (ch==4) createSession();
        else if (ch==5) viewSessions();
        else if (ch==6) markAttendance();
        else if (ch==7) {
            if (sessions.empty()) cout << "No sessions\n";
            else { 
                int s; 
                cout << "Session (1-" << sessions.size() << "): "; 
                cin >> s; 
                sessions[s-1].report(); 
            }
        }
        else if (ch==8) summary();
        else if (ch==9) { 
            saveStudents(); 
            saveSessions(); 
            cout << "Goodbye!\n"; 
        }
        else cout << "Invalid choice\n";
        
    } while (ch != 9);
    
    return 0;
}
