mysqldump -uroot -p1 --no-create-info --no-data --triggers --routines --events -B administration billets catalogs constructions equipment instrum manufacture market oasu processed_list sklad technologic temporary_tables  > patch.sql
rar.exe a patch.rar -ag patch.sql
erase patch.sql