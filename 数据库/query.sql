-- 获取指定学号的学生信息
SELECT * FROM Student WHERE StudentID = 1;

-- 获取指定专业的所有学生（例如：计算机科学与技术）
SELECT S.*
FROM Student S
         JOIN Class C ON S.ClassID = C.ClassID
         JOIN Major M ON C.MajorID = M.MajorID
WHERE M.MajorName = '计算机科学与技术';

-- 为任意学号的学生录入成绩
-- 检查是否已经存在成绩记录
SELECT * FROM Grade WHERE StudentID = 1 AND CourseID = 1;

-- 插入成绩
INSERT INTO Grade (StudentID, CourseID, Grade, CourseType)
VALUES (1, 1, 11, 'E');

-- 查询指定学号学生的课程信息
SELECT
    C.CourseName,
    G.CourseType,
    C.Credits,
    G.Grade
FROM Grade G
         JOIN Course C ON G.CourseID = C.CourseID
WHERE G.StudentID = 1;

SELECT
    S.StudentID,
    S.Name,
    S.Gender,
    S.DateOfBirth,
    C.ClassName,
    M.MajorName
FROM
    Student S
        JOIN
    Class C ON S.ClassID = C.ClassID
        JOIN
    Major M ON C.MajorID = M.MajorID
WHERE
    S.Name = '张三';  -- 替换为需要查询的姓名

SELECT
    S.StudentID,
    S.Name,
    S.Gender,
    S.DateOfBirth,
    C.ClassName,
    M.MajorName
FROM
    Student S
        JOIN
    Class C ON S.ClassID = C.ClassID
        JOIN
    Major M ON C.MajorID = M.MajorID
WHERE
    M.MajorName = '计算机科学与技术';  -- 替换为需要查询的专业名称

-- 计算任意学号学生的必修课加权平均成绩
SELECT
    SUM(C.Credits * G.Grade) / SUM(C.Credits) AS AvgCompulsoryGrade
FROM Grade G
         JOIN Course C ON G.CourseID = C.CourseID
WHERE G.StudentID = 1 AND G.CourseType = 'C';

-- 计算任意学号学生的所有课程加权平均成绩
SELECT
    SUM(C.Credits * G.Grade) / SUM(C.Credits) AS AvgAllCoursesGrade
FROM Grade G
         JOIN Course C ON G.CourseID = C.CourseID
WHERE G.StudentID = 1;

-- 查询任意学号学生的教师信息
SELECT DISTINCT T.Name AS TeacherName
FROM Grade G
         JOIN Course_Teacher CT ON G.CourseID = CT.CourseID
         JOIN Teacher T ON CT.TeacherID = T.TeacherID
WHERE G.StudentID = 1;

-- 查询学分差距不超过3分的学生信息
SELECT
    s.StudentID,  -- 学生ID
    s.Name AS StudentName,  -- 学生姓名
    compulsory.CompulsoryCredits AS EarnedCompulsoryCredits,  -- 已修的必修学分
    elective.ElectiveCredits AS EarnedElectiveCredits,  -- 已修的选修学分
    p.CompulsoryCredits,  -- 专业要求的必修学分
    p.ElectiveCredits,  -- 专业要求的选修学分
    (p.CompulsoryCredits - IFNULL(compulsory.CompulsoryCredits, 0)) AS CompulsoryCreditDifference,  -- 必修学分差距，NULL按0计算
    (p.ElectiveCredits - IFNULL(elective.ElectiveCredits, 0)) AS ElectiveCreditDifference  -- 选修学分差距，NULL按0计算
FROM
    Student s
        JOIN Class c ON s.ClassID = c.ClassID  -- 连接班级表
        JOIN Major m ON c.MajorID = m.MajorID  -- 连接专业表
        JOIN Plan p ON m.MajorID = p.MajorID  -- 连接教学计划表
        LEFT JOIN
    (  -- 计算每个学生已修的必修学分，成绩>=60的才计入学分
        SELECT g.StudentID, SUM(co.Credits) AS CompulsoryCredits
        FROM Grade g
                 JOIN Course co ON g.CourseID = co.CourseID  -- 连接课程表
        WHERE co.CourseType = 'C'  -- 仅计算必修课程
          AND g.Grade >= 60  -- 仅计算成绩大于等于60的课程
        GROUP BY g.StudentID  -- 按学生ID分组
    ) compulsory ON s.StudentID = compulsory.StudentID  -- 将必修学分与学生信息连接
        LEFT JOIN
    (  -- 计算每个学生已修的选修学分，成绩>=60的才计入学分
        SELECT g.StudentID, SUM(co.Credits) AS ElectiveCredits
        FROM Grade g
                 JOIN Course co ON g.CourseID = co.CourseID  -- 连接课程表
        WHERE co.CourseType = 'E'  -- 仅计算选修课程
          AND g.Grade >= 60  -- 仅计算成绩大于等于60的课程
        GROUP BY g.StudentID  -- 按学生ID分组
    ) elective ON s.StudentID = elective.StudentID  -- 将选修学分与学生信息连接
HAVING
    (p.CompulsoryCredits - IFNULL(compulsory.CompulsoryCredits, 0)) BETWEEN 0 AND 3  -- 必修学分差距不超过 3 分
    OR
    (p.ElectiveCredits - IFNULL(elective.ElectiveCredits, 0)) BETWEEN 0 AND 3;  -- 选修学分差距不超过 3 分
