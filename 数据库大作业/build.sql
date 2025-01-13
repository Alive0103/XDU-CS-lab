create
database if not exists xue;

use
xue;

-- 学生表
CREATE TABLE Student (
     StudentID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
     Name VARCHAR(50) NOT NULL,
     Gender CHAR(1) NOT NULL,
     DateOfBirth DATE NOT NULL,
     ClassID INT
);


-- 专业表
CREATE TABLE Major (
   MajorID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
   MajorName VARCHAR(50) NOT NULL
);

-- 教师表
CREATE TABLE Teacher (
     TeacherID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
     Name VARCHAR(50) NOT NULL,
     Gender CHAR(1) NOT NULL
);

-- 班级-课程-教师关系表
CREATE TABLE Class (
    ClassID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    ClassName VARCHAR(50) NOT NULL,
    MajorID INT NOT NULL,
    CourseID INT NOT NULL,
    TeacherID INT NOT NULL,
    UNIQUE (ClassID, CourseID, TeacherID)
);


-- 课程表
CREATE TABLE Course (
    CourseID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    CourseName VARCHAR(50) NOT NULL,
    CourseType CHAR(1) NOT NULL,   -- 'C' for compulsory, 'E' for elective
    Credits INT NOT NULL
);

-- 成绩表
CREATE TABLE Grade (
   GradeID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
   StudentID INT,
   CourseID INT,
   Grade INT,
   CourseType CHAR(1) ,-- 'C' for compulsory, 'E' for elective
   UNIQUE (StudentID,CourseID)
);

-- 课程-教师
CREATE TABLE Course_Teacher (
    CourseID INT,
    TeacherID INT,
    PRIMARY KEY (CourseID, TeacherID)
);

-- 教学计划表
CREATE TABLE Plan (
      PlanID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
      MajorID INT,
      CompulsoryCredits INT NOT NULL,
      ElectiveCredits INT NOT NULL
);


