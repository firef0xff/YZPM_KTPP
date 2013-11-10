use sklad;
begin;
ALTER TABLE `materials`
ADD COLUMN `bs`  varchar(2) NULL AFTER `sklad`,
ADD COLUMN `ss`  varchar(2) NULL AFTER `bs`,
ADD COLUMN `cena` double NOT NULL DEFAULT '0';
commit;

use administration;
begin;
	insert into rights (Name,progName) values ('Запуск в производство','Run_at_manufacture');
commit;

