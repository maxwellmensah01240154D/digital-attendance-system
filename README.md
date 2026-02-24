# Digital Attendance System

Project Overview
A C++ console-based attendance system for hour-based lectures. Developed for EEE227 - HND Electrical Engineering.

Developer
- Name: Maxwell Mensah
- Index Number: 01240154D
- Programme: HND Electrical Engineering (Level 200)

Project Timeline

Week 1
- GitHub repository setup
- Student class implementation
- Add and view students
- File storage for students

Week 2
- AttendanceSession class
- Create lecture sessions
- Menu-driven interface
- Session file management

Week 3
- Attendance marking (Present/Late/Absent)
- Session reports
- Summary generation
- Input validation

Week 4
- CSV file format implementation
- Improved file handling with backup
- Code refactoring with helper functions
- Complete documentation
- Final testing

Features

Student Management
- Register new students (8-digit index + 1 letter format)
- View all registered students
- Search students by index
- Input validation to prevent duplicates
- Stores: Name, Index Number, Department, Level

Session Management
- Create lecture sessions
  - Course code
  - Date (YYYY-MM-DD)
  - Start time (HH:MM)
  - Duration (1-4 hours)
- View all sessions

Attendance Tracking
- Mark attendance as:
  - Present
  - Late
  - Absent
- Prevent double marking
- Real-time status display

Reports
- Session attendance reports
- Overall summary with percentages
- Save reports to files
- Automatic backup system

File Structure

digital-attendance-system/
├── main.cpp
├── README.md
├── students.csv
├── sessions.csv
├── sessions_backup.csv
├── session_EEE227_2026-02-24.csv
├── session_EEE227_2026-02-25.csv
└── summary_report.txt
