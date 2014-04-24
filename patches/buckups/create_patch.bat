mysqldump -uroot -pq23s10z56 -h192.168.1.11 --no-create-info --no-data --triggers --routines --events -B administration billets catalogs constructions equipment instrum manufacture market oasu processed_list sklad technologic temporary_tables  > patch.sql
rar.exe a patch.rar -ag patch.sql
erase patch.sql