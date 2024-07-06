Soham Rajesh Pawar
CS22BTECH11055
Set - 1


1.
a)
create table Employees(e_Id int(4) primary key, f_name varchar(15), l_name varchar(15), email varchar(20), pnumber char(10), h_date date, job_id int(3), salary numeric(10, 0), commission numeric(3, 0), m_id int(4), dept_id numeric(3, 0));

insert into Employees values(4523, 'Rama', 'Rao', 'rao@gmail.com', '1234567890', '2000-1-22', 213, 30000, 60, 543, 12);

insert into Employees values(4102, 'Prasad', 'Rao', 'prasad@gmail.com', '5678909012', '1997-7-26', 214, 70000,
40, 543, 12);

insert into Employees values(5123, 'Raja', 'Shekhar', 'raja@gmail.com', '9999999921', '1999-5-21', 213, 55000,
35, 999, 10);

insert into Employees value(3213, 'Ranga', 'Reddy', 'reddy@gmail.com', '3421398763', '1990-9-22', 199, 95000, 45, 213, 11);

insert into Employees values(4213, 'Ravi', 'Kumar', 'kumar@gmail.com', '3421298754', '2000-1-22', 213, 50000, 60, 213, 09);

b)
select f_name, l_name from Employees where salary>50000 or salary=50000;

c)
select dept_id, avg(salary) from Employees group by dept_id;

d)
select m_id, count(e_id) from Employees group by m_id;

2.
1)
select name, dept_name as department, (salary * 12) as annual_salary from instructor;

2)
select s.id, name from student s where id in (select id from takes group by id, semester, year having count(course_id) > 5);

3)
select name from instructor where salary = (select max(salary) from instructor);
