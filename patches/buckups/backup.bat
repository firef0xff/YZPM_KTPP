mysqldump -uroot -p1 --opt -R -B administration billets catalogs constructions equipment instrum manufacture market oasu processed_list sklad technologic temporary_tables  > backup.sql
rar.exe a bacup.rar -ag backup.sql
#erase backup.sql