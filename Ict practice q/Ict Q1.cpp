#include <iostream>
#include <string>
#include <map>
using namespace std;

class Person {
	protected:
	    string name;
	    int age;
	    string address;
	
	public:
	    Person(string n, int a, string addr) : name(n), age(a), address(addr) {}
	
	    virtual void displayDetails() {
	        cout << "Name: " << name << ", Age: " << age << ", Address: " << address << endl;
	    }
};

class Student : public Person {
	private:
	    string studentID;
	    map<string, double> grades;
	
	public:
	    Student(string n, int a, string addr, string id) : Person(n, a, addr), studentID(id) {}
	
	    void addGrade(string subject, double grade) {
	        grades[subject] = grade;
	    }
	
	    double calculateGPA() {
	        if (grades.empty())
	            return 0.0;
	
	        double total = 0;
	        for (map<string, double>::iterator it = grades.begin(); it != grades.end(); ++it) {
	            total += it->second;
	        }
	        return total / grades.size();
	    }
	
	    void displayDetails() {
	        Person::displayDetails();
	        cout << "Student ID: " << studentID << ", GPA: " << calculateGPA() << endl;
	    }
};

class Payable {
public:
    virtual double calculateSalary() = 0; 
};

class Teacher : public Person, public Payable {
private:
    string teacherID;
    string subject;
    int classesTaught;
    double ratePerClass;

public:
    Teacher(string n, int a, string addr, string id, string sub, double rate)
        : Person(n, a, addr), teacherID(id), subject(sub), classesTaught(0), ratePerClass(rate) {}

    void assignGrade(Student &student, double grade) {
        student.addGrade(subject, grade);
        classesTaught++;
    }

    double calculateSalary() {
        return classesTaught * ratePerClass;
    }

    void displayDetails() {
        Person::displayDetails();
        cout << "Teacher ID: " << teacherID << ", Subject: " << subject << endl;
    }
};

int main() {
    Teacher teacher("Umer", 30, "Taqi St", "S000", "Math", 50);
    Student student1("Usman", 20, "Khalid ST", "S001");
    Student student2("Hassan", 21, "LISBON ST", "S002");

    teacher.assignGrade(student1, 85);
    teacher.assignGrade(student2, 90);

    cout << "Teacher Details:" << endl;
    teacher.displayDetails();
    cout << "Salary: PKR " << teacher.calculateSalary() << endl;

    cout << "\nStudent Details:" << endl;
    student1.displayDetails();
    student2.displayDetails();

    return 0;
}

