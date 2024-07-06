CREATE TABLE Faculty(
    f_id VARCHAR(20) PRIMARY KEY,
    f_name VARCHAR(50),
    salary int,
    post VARCHAR(90)
    );

CREATE TABLE Student(
    s_id VARCHAR(20) PRIMARY KEY,
    s_name VARCHAR(50),
    dept_name VARCHAR(50),
    f_id VARCHAR(20),
    FOREIGN KEY(f_id) references
    Faculty(f_id)
    );


create procedure decompose()
    begin
    declare done int default false;
    declare stud_id VARCHAR(20);
    declare inst_id VARCHAR(20);
    declare stud_name VARCHAR(50);
    declare inst_name VARCHAR(50);
    declare dept VARCHAR(50);
    declare sal int;
    declare type VARCHAR(90);
    declare cur1 CURSOR FOR select f_id, f_name, salary, post from projects;
    declare cur2 CURSOR FOR select s_id, s_name, dept_name, f_id from student;
    declare CONTINUE HANDLER FOR NOT FOUND set done = true;
    read1 : LOOP
    fetch cur1 into inst_id, inst_name, sal, type;
    if done then LEAVE LOOP; end if;
    set @present = 0;
    set @query = CONCAT('select count(*) into @present from Faculty where f_id = ', inst_id);
    PREPARE stmt FROM @query;
    EXECUTE stmt;
    set @query = CONCAT('insert into Faculty values(', inst_id,',', inst_name ,',', sal,',', type,')');
    PREPARE stmt FROM @query;
    if @present = 0 then EXECUTE stmt; end if;
    end LOOP;
    
    read2 : LOOP
    fetch cur2 into stud_id, stud_name, dept, inst_id;
    if done then LEAVE LOOP; end if;
    set @query = CONCAT('insert into Student values(', stud_id,',', stud_name ,',', dept,',', inst_id,')');
    PREPARE stmt FROM @query;
    EXECUTE stmt;
    end LOOP;
    close cur1;
    close cur2;
    deallocate prepare stmt;
    end //
    delimiter;

