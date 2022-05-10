# SDF 22 Exercise#1

This exercise deals with making a small version of _mini-AIMS_ (IITH) that includes authentication.

Code was done using VSCode on Ubuntu
Student/Course/Faculty data:
There is only one identifcation mark for student/admin/faculty/course: Their ID
All ID/sernames/names associated with admin/student/course/faculty are 4 characters long.
The students have an id in the format of abxy, where xy ranges from 01 to 99 and ab is any branch code (egs: cs, ep)
The faculties have an id in the format of faxy, where xy ranges from 01 to 99 and each faculty account has only 1 course associated with it
The courses have an id in the similar format to IITH course IDs (egs: CS1023)
The admin has an id in format of adxy where xy ranges from 01 ot 99. 

Data storage:

The code uses text files to store the data."details.txt" stores all the username/password of existing users. "courses.txt" contains all the existing
courses and the students registered for it (space-separated). "floated_courses.txt" contains all floated courses. "records.txt" contains all existing
student IDs along with pairs of (course id,grade) with spaces in between. (grade is "null" by default). There is a "buffer.txt" creating and deleted
everytime a insertion/updation operation occurs.

Logging in:

The code expects role of the user along with username and password to get to the operations.

Menu Options:
Admin Operations-
* Add/Delete course
* Add/Delete user
* Add/Delete students to/from course
* Float/unfloat course
* Logout

Faculty-
* Check students enrolled in course and submit grades
* Logout

Students-
* Register to a course / Deregister from a course
* Check Grades 
* Logout 

The corresponding number has to be entered.
