#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#define GRADE_A 90
#define GRADE_B 80
#define GRADE_C 70
#define GRADE_D 60
#define INPUT “students.txt”
#define OUTPUT “grades.txt”
intnumOfStudent = 0;
string IDS[100];
string NAMES[100];
double SCORES[100][3];
voidprintMenu();
voidreadListOfStudent();
voiddisplayAllStudentRecords();
voiddisplayOneStudentRecords();
voidsortStudentRecords();
voidaddNewStudentRecords();
voidproduceGradeReport();
stringcalculateLetterGrade(intstudentIndex);
doublecalculateAverageOneExam(intExamIndex);
doublecalculateAverageOneStudent(intstudentIndex);
doublecalculateAverageAllExam();
voidparseOneStudent(intstudentIndex, string line);
int main(intagrc, char* agrv[])
{
int choice = 0;
cout.precision(1);
cout<< fixed;
while (choice != 7)
{
cout<<endl<<endl;
printMenu();
cout<< “Choice: “;
cin>> choice;
cin.ignore();
switch (choice)
{
case 1:
// Read from file
readListOfStudent();
break;
case 2:
// Display all student
displayAllStudentRecords();
break;
case 3:
// Display one student
displayOneStudentRecords();
break;
case 4:
// sort student
sortStudentRecords();
cout<< “Affter sort:” <<endl;
displayAllStudentRecords();
break;
case 5:
// add new student
addNewStudentRecords();
break;
case 6:
//procude grade report
produceGradeReport();
break;
case 7:
// quit
return 0;
break;
default:
cout<< “Invalid choice. Please choice again.” <<endl;
break;
}
}
return 0;
}
/*
Print the menu
*/
voidprintMenu()
{
cout<< “1. Read List of Students Records” <<endl;
cout<< “2. Display All Students Records” <<endl;
cout<< “3. Display One Students Records” <<endl;
cout<< “4. Sort Student Records” <<endl;
cout<< “5. Add a new Student Records” <<endl;
cout<< “6. ProduceGradeReport” <<endl;
cout<< “7. Exit” <<endl;
}
/*
Read from an input file “students.txt” a list of student records. The
input file contains an unknown number of student records. Each line in the input file includes the
following information about one student: student id, student name (first and last), and exam scores
(maximum 3 scores). The student ids must be stored in an array called IDS. The student names must
be stored in an array called NAMES. The exam scores must be stored in a two-dimensional array
called SCORES
*/
voidreadListOfStudent()
{
string line;
ifstreaminputFile(INPUT);
if (inputFile.is_open())
{
while (getline(inputFile, line))
{
parseOneStudent(numOfStudent, line);
numOfStudent++;
}
inputFile.close();
}
else
{
cout<< “Unable to open file: ” << INPUT <<endl;
}
}
/*Display all student records (id, name, and all exam scores).*/
voiddisplayAllStudentRecords()
{
cout<< “ID\tNAME\t\tEXAM1\tEXAM2\tEXAM3” <<endl;
for (int i = 0; i <numOfStudent; ++i)
{
cout<< IDS[i] << “\t” << NAMES[i] << “\t\t” << SCORES[i][0] << “\t” << SCORES[i][1] << “\t” << SCORES[i][2] <<endl;
}
}
/*
Search for a given student id (entered by the user) and display the
corresponding student record (id, name, and all exam scores) if found, otherwise student not found is
displayed.
*/
voiddisplayOneStudentRecords()
{
string id;
cout<< “Enter the student ID want to display: “;
getline(cin, id);
int i = 0;
int count = 0;
for (i = 0; i <numOfStudent; ++i)
{
if (IDS[i] == id)
{
cout<< “ID\tNAME\t\tEXAM1\tEXAM2\tEXAM3” <<endl;
cout<< IDS[i] << “\t” << NAMES[i] << “\t\t” << SCORES[i][0] << “\t” << SCORES[i][1] << “\t” << SCORES[i][2] <<endl;
count++;
}
}
if (count == 0)
{
cout<< “The sudent with ID ” << id << ” did NOT exist” <<endl;
}
}
/*Sort the arrays IDS, NAMES, and SCORES by increasing student id.*/
voidsortStudentRecords()
{
for (int i = 0; i <numOfStudent; ++i)
{
for (int j = i; j <numOfStudent; ++j)
{
if (IDS[i] > IDS[j])
{
//swap ID
string temp = IDS[i];
IDS[i] = IDS[j];
IDS[j] = temp;
//swap NAME
temp = NAMES[i];
NAMES[i] = NAMES[j];
NAMES[j] = temp;
//swap SCORES
double score1, score2, score3;
score1 = SCORES[i][0];
score2 = SCORES[i][1];
score3 = SCORES[i][2];
SCORES[i][0] = SCORES[j][0];
SCORES[i][1] = SCORES[j][1];
SCORES[i][2] = SCORES[j][2];
SCORES[j][0] = score1;
SCORES[j][1] = score2;
SCORES[j][2] = score3;
}
}
}
}
/*Add a new student record at the end of the lists.*/
voidaddNewStudentRecords()
{
cout<< “Enter ID of student: “;
getline(cin, IDS[numOfStudent]);
cout<< “Enter Name of student: “;
getline(cin, NAMES[numOfStudent]);
cout<< “Enter score of EXAM1: “;
string temp;
getline(cin, temp);
SCORES[numOfStudent][0] = stod(temp);
cout<< “Enter score of EXAM2: “;
temp.clear();
getline(cin, temp);
SCORES[numOfStudent][1] = stod(temp);
cout<< “Enter score of EXAM3: “;
temp.clear();
getline(cin, temp);
SCORES[numOfStudent][2] = stod(temp);
numOfStudent++;
}
/*
Produce a grade report in an output file called “grades.txt” in the format
shown below. The report must be sorted by increasing student id and must include the student letter
grades and average exam scores
*/
voidproduceGradeReport()
{
//sort first
sortStudentRecords();
ofstreamoutputFile(OUTPUT);
if (outputFile.is_open())
{
outputFile.precision(1);
outputFile<< fixed;
outputFile<< “ID\t\t\tNAME\t\tEXAM1\tEXAM2\tEXAM3\t\tAVG\tGRAGE” <<endl;
outputFile<< “——————————————————————————————-” <<endl;
for (int i = 0; i <numOfStudent; ++i)
{
outputFile<< IDS[i] << “\t” << NAMES[i] << “\t\t” << SCORES[i][0] << “\t” << SCORES[i][1] << “\t” << SCORES[i][2] << “\t\t” <<calculateAverageOneStudent(i) << “\t\t” <<calculateLetterGrade(i) <<endl;
}
outputFile<< “——————————————————————————————-” <<endl;
outputFile<< “Averages:” << “\t\t\t\t\t\t” <<calculateAverageOneExam(0) << “\t\t” <<calculateAverageOneExam(1) << “\t\t” <<calculateAverageOneExam(2) << “\t\t” <<calculateAverageAllExam() <<endl;
outputFile.close();
}
else
{
cout<< “Unable open to write file: ” << OUTPUT <<endl;
}
}
/*Parse all infor of student from line*/
voidparseOneStudent(intstudentIndex, string line)
{
intindex_holder = 0;
string student[5];
int index = 0;
for (size_t i = 0; i <line.size(); ++i)
{
if (line[i] == ‘\t’ || (i == line.size() – 1))
{
if (i != index_holder)
{
student[index] = line.substr(index_holder, i – index_holder); // Parse all to array string.
index_holder = i + 1;
index = index + 1;
}
else
{
index_holder = i + 1;
}
}
}
IDS[studentIndex] = student[0]; // id
NAMES[studentIndex] = student[1]; //name
SCORES[studentIndex][0] = stod(student[2]); //score 1
SCORES[studentIndex][1] = stod(student[3]); //score 2
SCORES[studentIndex][2] = stod(student[4]); //score 3
}
/*Calculate Averages of One Student*/
doublecalculateAverageOneStudent(intstudentIndex)
{
inttotalEXAM = 0;
if (SCORES[studentIndex][0] != 0)
totalEXAM++;
if (SCORES[studentIndex][1] != 0)
totalEXAM++;
if (SCORES[studentIndex][2] != 0)
totalEXAM++;
return (SCORES[studentIndex][0] + SCORES[studentIndex][1] + SCORES[studentIndex][2]) / totalEXAM;
}
/*Calculate Letter Grade of Student*/
stringcalculateLetterGrade(intstudentIndex)
{
double averages = calculateAverageOneStudent(studentIndex);
if (averages >= 90)
return “A”;
else if (averages >= 80)
return “B”;
else if (averages >= 70)
return “C”;
else if (averages >= 60)
return “D”;
return “F”;
}
/*Calculate Average One Exam*/
doublecalculateAverageOneExam(intexamIndex)
{
intcountExam = 0;
double total = 0;
for (int i = 0; i <numOfStudent; ++i)
{
if (SCORES[i][examIndex] != 0)
{
countExam++;
total += SCORES[i][examIndex];
}
}
return total / countExam;
}
/*Calculate Average All Exam*/
doublecalculateAverageAllExam()
{
int count = 0;
double total = 0;
for (int i = 0; i < 3; ++i)
{
double temp = calculateAverageOneExam(i);
if (temp != 0)
{
count++;
total += temp;
}
}
return total / count;
}
