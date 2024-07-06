--1a)
select i.id as instructor_id,i.name as instructor_name,count(distinct t.course_id) as number_courses from instructor i join teaches t on i.id = t.id group by i.id order by count(distinct t.course_id) desc limit 3;

--1b)
select i.id as instructor_id,i.name as instructor_name,count(distinct t.course_id) as number_courses from instructor i join teaches t on i.id = t.id and i.dept_name = 'Statistics' group by i.id order by count(distinct t.course_id) desc limit 3;

--2)
select i.dept_name as department,c.course_id,c.title,t1.sec_id,t1.semester,t1.year,count(t2.id) as total_enrollments from instructor i join teaches t1 on i.id = t1.id and i.id = (select id from instructor order by salary desc limit 1) join course c on t1.course_id = c.course_id join takes t2 on c.course_id = t2.course_id group by i.dept_name,c.course_id,c.title,t1.sec_id,t1.semester,t1.year order by c.course_id,t1.year;

--3)
select c.course_id, c.title, c.dept_name, i.name as instructor_name, number_registered, t1.sec_id, t1.semester, t1.year, s.time_slot_id
from course c join teaches t1 on c.course_id = t1.course_id join (select course_id, year, semester, count(id) as number_registered
from takes
group by course_id, year, semester) as take
on (take.course_id = c.course_id and take.semester = t1.semester and take.year = t1.year) join instructor i on i.id = t1.id join section s on (c.course_id = s.course_id and t1.sec_id = s.sec_id and t1.semester = s.semester and t1.year = s.year) where c.course_id = '362' order by t1.year desc;

--4)
select count(t.id) as out_of_dept_registered from takes t join student s on t.id = s.id and t.course_id = '319' and t.year = '2003' where s.dept_name <> (select dept_name from course where course_id = '319');

--5)
select s.id,s.name,s.dept_name,sum(c.credits) as total from student s join takes t on s.id = t.id join course c on t.course_id = c.course_id group by s.id order by total desc,s.name limit 3;

--6)
select c.course_id,c.title from course c where course_id not in (select course_id from teaches where year = '2003' or year = '2004') order by course_id;

--7)
select c.course_id,c.title,i.name,t.year from course c join teaches t on t.course_id = c.course_id and c.course_id in (select course_id from teaches group by course_id having min(year) = (select max(year) from teaches)) join instructor i on t.id = i.id order by c.course_id;

--8)
select course_id as id,title from course where length(title) > 15 and lower(title) like '%sys%' order by course_id;

--9)
select dept_name,avg(salary) as average_salary from instructor group by dept_name order by avg(salary) desc limit 1;

--10)
select i.id,i.name,i.dept_name from instructor i left join teaches t on i.id = t.id and t.year = '2003' group by i.id having count(t.course_id) <= 1 order by i.id;
