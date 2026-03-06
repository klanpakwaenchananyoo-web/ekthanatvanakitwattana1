#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// ฟังก์ชันแปลง string ให้เป็นตัวพิมพ์ใหญ่ทั้งหมด เพื่อใช้เปรียบเทียบคำสั่ง
string toUpper(string s) {
    for (auto &c : s) c = toupper(c);
    return s;
}

// ฟังก์ชันตัดเกรดตามเงื่อนไข
char calculateGrade(int score) {
    if (score >= 80) return 'A';
    if (score >= 70) return 'B';
    if (score >= 60) return 'C';
    if (score >= 50) return 'D';
    return 'F';
}

int main() {
    ifstream file("name_score.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open file." << endl;
        return 0;
    }

    vector<string> names;
    vector<int> totalScores;
    vector<char> grades;

    string line;
    // อ่านไฟล์ทีละบรรทัด
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            string scoresPart = line.substr(pos + 1);
            
            stringstream ss(scoresPart);
            int s1, s2, s3;
            ss >> s1 >> s2 >> s3;
            
            int total = s1 + s2 + s3;
            names.push_back(name);
            totalScores.push_back(total);
            grades.push_back(calculateGrade(total));
        }
    }
    file.close();

    string input;
    while (true) {
        cout << "Please input your command: " << endl;
        getline(cin, input);
        
        stringstream ss(input);
        string cmd, key;
        ss >> cmd; // อ่านคำสั่งแรก (name, grade, exit)
        
        // อ่านส่วนที่เหลือเป็น key (รองรับชื่อที่มีเว้นวรรค)
        string temp;
        bool first = true;
        while (ss >> temp) {
            if (!first) key += " ";
            key += temp;
            first = false;
        }

        string upperCmd = toUpper(cmd);

        if (upperCmd == "EXIT") {
            break;
        } 
        else if (upperCmd == "NAME") {
            cout << "---------------------------------" << endl;
            bool found = false;
            for (size_t i = 0; i < names.size(); i++) {
                if (toUpper(names[i]) == toUpper(key)) {
                    cout << names[i] << "'s score = " << totalScores[i] << endl;
                    cout << names[i] << "'s grade = " << grades[i] << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Cannot found." << endl;
            cout << "---------------------------------" << endl;
        } 
        else if (upperCmd == "GRADE") {
            cout << "---------------------------------" << endl;
            bool found = false;
            string upperKey = toUpper(key);
            for (size_t i = 0; i < names.size(); i++) {
                if (string(1, grades[i]) == upperKey) {
                    cout << names[i] << " (" << totalScores[i] << ")" << endl;
                    found = true;
                }
            }
            if (!found) cout << "Cannot found." << endl;
            cout << "---------------------------------" << endl;
        } 
        else {
            cout << "---------------------------------" << endl;
            cout << "Invalid command." << endl;
            cout << "---------------------------------" << endl;
        }
    }

    return 0;
}