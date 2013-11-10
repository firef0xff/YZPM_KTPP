-- MySQL dump 10.13  Distrib 5.5.23, for Win64 (x86)
--
-- Host: 192.168.1.10    Database: administration
-- ------------------------------------------------------
-- Server version	5.5.32-0ubuntu0.13.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `administration`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `administration` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `administration`;

--
-- Dumping events for database 'administration'
--

--
-- Dumping routines for database 'administration'
--
/*!50003 DROP PROCEDURE IF EXISTS `GetUserAccess` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `GetUserAccess`(User int(11),id int(11) unsigned)
    COMMENT 'проверка доступа у пользователя'
BEGIN
	#Routine body goes here...
select
b.LogIn as UserName,
if (c.IdGroup is null or (a.UserID is not null and a.UserID!=user)or d.arhive=1,0,1)as Access
from constructions.det_names a
join logins b on b.logId=user
left join gtucond c on c.IdCond=a.state and c.IdGroup=b.levelacss
left join conditions d on d.idsost=c.IdCond
where a.id=id ;
#	 DtInfo::DtInfo(cSQL *db, int _id,const int &_User)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_GroupsRights` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_GroupsRights`(groupid smallint(6))
BEGIN
	#Routine body goes here...
select d.Name,d.progname from `privileges` a 
join privilegesrights c on c.PrivilegeID=a.GroupID
join rights d on d.ID=c.RidhtID 
where a.GroupID=groupid; 
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_MinState` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_MinState`(User int(11))
BEGIN
	#Routine body goes here...
select a.IdCond as IdCond,c.`name` as CondName 
from `gtucond` a 
join `logins` b on a.IdGroup=b.Levelacss  
join conditions c on a.IdCond=c.idsost
where b.LogID=User order by IdCond limit 0,1;
#int TSPEditor::GetMinState (void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Name` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Name`(id int(11))
BEGIN
	#Routine body goes here...
	select if(trim(CONCAT(a.Family,' ',left(a.`Name`,1),'.',left(a.Otch,1),'.'))!='..',trim(CONCAT(a.Family,' ',left(a.`Name`,1),'.',left(a.Otch,1),'.')),a.login) as `name` from logins a where a.LogID=ID;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_new_Group_right` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_new_Group_right`(GroupID text)
BEGIN
	#Routine body goes here...
DROP TEMPORARY TABLE IF EXISTS tmp;
CREATE TEMPORARY TABLE if NOT EXISTS tmp
(
id SMALLINT(6) not null,
key(id)
)ENGINE=MEMORY as 
select id from rights a 
inner join privilegesrights b on a.ID=b.RidhtID and b.PrivilegeID=GroupID; 

select a.name,a.progName FROM rights a 
left join tmp b on a.ID=b.id
where b.id is null;

DROP TEMPORARY TABLE IF EXISTS tmp;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Rights` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Rights`(logID int(11))
BEGIN
	#Routine body goes here...
select d.Name,d.progname from `privileges` a 
join logins b on b.Levelacss=a.GroupID
join privilegesrights c on c.PrivilegeID=a.GroupID
join rights d on d.ID=c.RidhtID 
where b.logID=logID ; 
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_SpRazd` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_SpRazd`()
BEGIN
	#Routine body goes here...
Select RazdID,Razdname from sprazd /*where RazdID>0*/ ORDER BY RazdID;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `billets`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `billets` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `billets`;

--
-- Dumping events for database 'billets'
--

--
-- Dumping routines for database 'billets'
--
/*!50003 DROP PROCEDURE IF EXISTS `Get_vzName` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_vzName`(vz char(3))
BEGIN
	#Routine body goes here...
select trim(name) as vzName from vz_tree a where a.kod=vz;
#void 	DtInfo::Set_vz(int r)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `catalogs`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `catalogs` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `catalogs`;

--
-- Dumping events for database 'catalogs'
--

--
-- Dumping routines for database 'catalogs'
--
/*!50003 DROP PROCEDURE IF EXISTS `Get_control` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_control`()
BEGIN
	#Routine body goes here...
SELECT 
ko69 as ID,
te69 as `text`
from control ORDER BY ko69;
#void  TTechWnd::Load_support_info(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_eiName` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_eiName`(ei char(3))
BEGIN
	#Routine body goes here...
select trim(snameei) as eiName from dimensionality where kodei=ei;
#void 	DtInfo::Set_ei(int r)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_ei_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_ei_list`(type int(11))
BEGIN
	#Routine body goes here...
CASE type
when 0 THEN
	SELECT a.kodei as id,a.snameei as `text` FROM `dimensionality` a
	join sklad.materials b on b.eic=a.kodei GROUP BY a.kodei;
when 1 THEN
	SELECT a.kodei as id,a.snameei as `text` FROM `dimensionality` a
	join technologic.det_info b on b.ei=a.kodei GROUP BY a.kodei;
when 2 THEN
	SELECT a.kodei as id,a.snameei as `text` FROM `dimensionality` a
  GROUP BY a.kodei;
WHEN 3 THEN 
	SELECT a.kodei as id,a.snameei as `text` FROM `dimensionality` a
	join constructions.det_tree b on b.ei=a.kodei GROUP BY a.kodei;
end case;
#void  TTechWnd::Load_support_info(void)
#int	 TSPEditor::LoadComboData(int type)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_ioht` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_ioht`(param1 int(11),param2 text)
BEGIN
	#Routine body goes here...
case param1 
WHEN 0 then
	BEGIN
	select * from `instruc_tb` order by kop,ioht,nioht;
	end;
WHEN 1 then
	BEGIN
	set @sq=CONCAT("select * from `instruc_tb` where kop like '%",param2,"%' order by kop,ioht,nioht");
	prepare init from @sq;
	EXECUTE init;
	end;
WHEN 2 then
	BEGIN
	set @sq=CONCAT("select * from `instruc_tb` where ioht in ('",param2,"') order by kop,ioht,nioht");
	prepare init from @sq;
	EXECUTE init;
	end;
end case;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_ppName` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_ppName`(pp char(2))
BEGIN
	#Routine body goes here...
select trim(napp) as ppName from proizv_prizn a where a.pp=pp;
#void 	SpRow::Set_pp 			(const int &r)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_pp_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_pp_list`()
BEGIN
	#Routine body goes here...
Select pp as kod,CONCAT (pp," ",napp) as `text` from proizv_prizn; 
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_proff` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_proff`(filter TINYINT(4), ceh char(2),utch char(2))
BEGIN
	#Routine body goes here...
case filter
	WHEN 0 then 
		BEGIN
		Select DISTINCT a.kodp,a.prof from prof_list a
			join technologic.operation_norms b on  a.kodp=b.prof
			join podr_prof b1 on a.kodp=b1.prof
			join podr_list c on c.cex=b1.cex and c.utch=b1.utch 
			where b1.cex=ceh and b1.utch=utch 
			order by c.npodr;	
		end;
	when 1 then
		BEGIN	
		SELECT DISTINCT a.kodp,a.prof FROM prof_list a
			join podr_prof b on a.kodp=b.prof
			join podr_list c on c.cex=b.cex and c.utch=b.utch 
			where b.cex=ceh and b.utch=utch 
			order by c.npodr;
		end;
	WHEN 2 THEN
		BEGIN
		Select DISTINCT a.kodp,a.prof from prof_list a
			join technologic.operation_norms b on  a.kodp=b.prof
			left join podr_prof b1 on a.kodp=b1.prof
			left join podr_list c on c.cex=b1.cex and c.utch=b1.utch 
			order by c.npodr;	
		end;
	WHEN 3 THEN
		BEGIN
		SELECT DISTINCT a.kodp,a.prof FROM prof_list a
			left join podr_prof b on a.kodp=b.prof
			left join podr_list c on c.cex=b.cex and c.utch=b.utch 
			order by c.npodr;
		end;
end case;
#void __fastcall TProfessinos::SG2SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `constructions`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `constructions` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `constructions`;

--
-- Dumping events for database 'constructions'
--

--
-- Dumping routines for database 'constructions'
--
/*!50003 DROP PROCEDURE IF EXISTS `AddFile` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `AddFile`(DetID int, inBasePath text, fpart text, FileName text, FileInBase text, UserID int)
    COMMENT 'команда на внесени записи о файле в базу'
BEGIN
	#Routine body goes here...
if EXISTS (select a.FileInsert from administration.`privileges` a join administration.logins b on a.GroupID=b.levelacss and b.logid=UserID where a.FileInsert)
	then
	insert into files 
	( `idDet`,`FileInBase`,`FileInProj`,`InProjName`,`InBaseName`,`Creator`,`DateOfCreate`,`Updater`,`DateOfUpdate`)
		(SELECT DetID,inBasePath,fpart,FileName,FileInBase,LogIn,CURRENT_TIMESTAMP(),LogIn,CURRENT_TIMESTAMP() from administration.logins where LogID=UserID );
	SELECT 1 `return`;
	ELSE
	select 0 `return`;
end if;
#FRowData::SaveToBase(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `block` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `block`(ids text, User int)
    COMMENT 'блокировка всех указанных деталей если есть доступ'
BEGIN
set @sq=CONCAT('
update det_names a 
inner join administration.logins g1 on g1.logId=',User,'
inner join administration.gtucond g on g.IdCond=a.state and g.IdGroup=g1.levelacss
set a.UserID=',User,'
where a.id in (',ids,') and a.userID is null
');
prepare init from @sq;
EXECUTE init;
/*
TSpTree::Block(String &ids)
void  TTechWnd::Load (const Obd *const det)
*/
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `BlockAll` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `BlockAll`(ids text, User int)
    COMMENT 'блокировка всех деталей входящих в указанные узлы'
BEGIN
declare lvl int;
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS output;
call GetDet(ids);

update det_names a 
inner join output b on a.id=b.idc
inner join administration.logins g1 on g1.logId=User
inner join administration.gtucond g on g.IdCond=a.state and g.IdGroup=g1.levelacss
set a.UserID=User
where a.userID is null;

Drop TEMPORARY TABLE if EXISTS output;
/*
TSpTree::Block(String &ids)
*/
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `ChangeState` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `ChangeState`(id text,state smallint(6))
    COMMENT 'смена состояния указанного объекта'
BEGIN
	#Routine body goes here...
update det_names a set a.state=state,a.UserID=null where a.id=id;
#TCond::ChangeCondition(CRowData *row)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `ChangeStates` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `ChangeStates`(ids text,old smallint(6),new smallint(6),action int(2))
    COMMENT 'процедура управления массовой сменой сосяний'
BEGIN
	#Routine body goes here...
CASE `action`
	when 0 THEN
			BEGIN # заполение предварительной таблицы состояний
			Create TEMPORARY table if not EXISTS conds 
			(
			old int(11) not null,
			new int(11) not null
			) ENGINE=memory;
			insert into conds select old as `old`,new as `new`;
			END;
	when 1 THEN	#смена состояний
			BEGIN #смена состояний на всех деталях
			Call Changing_States_for_All_Details(ids);
			drop TEMPORARY table if EXISTS conds; 
			END;
	when 2 THEN
			BEGIN	#смена состояний на нестандартныйх деталях
			Call Changing_States_for_All_Non_Standard(ids);
			drop TEMPORARY table if EXISTS conds; 
			END;
	when 3 then 
			BEGIN #смена состояний только на оригинальных деталях
			Call Changing_States_for_All_Original(ids);
			drop TEMPORARY table if EXISTS conds; 
			END;
END case;
#TCond::BitBtn3Click(TObject *Sender) TCond::ChangeCondition(CRowData *row)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Changing_States_for_All_Details` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Changing_States_for_All_Details`(ids text)
    COMMENT '#смена состояний на всех деталях'
BEGIN
	#Routine body goes here...
Call GetDet(ids);
update det_names a 
inner join output b on a.id=b.idc 
inner join conds c on c.old=a.state
set a.state=c.new,a.UserID=null;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Changing_States_for_All_Non_Standard` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Changing_States_for_All_Non_Standard`(ids text)
    COMMENT '#смена состояний на нестандартныйх деталях'
BEGIN
	#Routine body goes here...
Call GetDet(ids);
update det_names a 
inner join output b on a.id=b.idc 
inner join conds c on c.old=a.state
set a.state=c.new,a.UserID=null where a.razdspid not in(7,5,6);
Drop TEMPORARY TABLE if EXISTS output;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Changing_States_for_All_Original` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Changing_States_for_All_Original`(ids text)
    COMMENT '#смена состояний только на оригинальных деталях'
BEGIN
	#Routine body goes here...
Call GetDet(ids);
Drop TEMPORARY TABLE if EXISTS tmp;
Set @com=concat
	("
	CREATE TEMPORARY TABLE if NOT EXISTS tmp as select left(obd,6) as org from det_names where id in (",ids,")
	");
prepare sel from @com;
EXECUTE sel;
update det_names a 
inner join output b on a.id=b.idc 
inner join conds c on c.old=a.state
inner join tmp c1 on left(a.obd,6)=c1.org
set a.state=c.new,a.UserID=null;

Drop TEMPORARY TABLE if EXISTS tmp;
Drop TEMPORARY TABLE if EXISTS output;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Clear_base` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Clear_base`()
BEGIN
	#Routine body goes here...
delete from market.zakaz;
delete from technologic.det_info;
delete from det_names;
delete from files;
delete from equipment.obor_list;
delete from equipment.opr_names;
alter table det_names AUTO_INCREMENT=1;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `convert_old_base` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `convert_old_base`()
BEGIN
	#Routine body goes here...
#чистка
delete from market.zakaz;
delete from technologic.det_info;
delete from det_names;
delete from files;
delete from equipment.obor_list;
delete from equipment.opr_names;
alter table det_names AUTO_INCREMENT=1;
#пренос деталей 

Call equipment.convert_old_base();
insert into det_names (obd,namd,base,CreateDate,CreateUser,UpdateDate,UpdateUser,razdspid)
	select if (obm not like 'NA%',CONCAT('000000000',obm),obm),CONCAT(trim(nama),' ',trim(goma),' ',trim(prma),' ',trim(gopr)),'oasu',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd",5 
	from temporary_tables.nsi032 
	#where CONCAT('000000000',obm) not in (select distinct obd from `det_names`)
	GROUP BY obm;
insert into det_names 
(obd,namd,razdSPID,state,base,CreateUser,UpdateUser,CreateDate,UpdateDate)
select obd,namd,razdSPID,state,'oasu','upd','upd',CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP() from temporary_tables.det_names
where obd not in (select distinct obd from `det_names`);
update det_names a join temporary_tables.det_names_new b on a.obd=b.obd set a.base='mysql';
# обновить рр,format в детнеймсах
drop TEMPORARY table if EXISTS tmp;
create TEMPORARY table if not EXISTS tmp as select obd,pp from temporary_tables.det_tree GROUP BY obd;
update det_names a  
join tmp b on a.obd = b.obd
join catalogs.proizv_prizn c on c.pp=b.pp
set a.pp=c.pp;
drop TEMPORARY table if EXISTS tmp;

drop TEMPORARY table if EXISTS tmp;
create TEMPORARY table if not EXISTS tmp as select obd,format from temporary_tables.det_tree GROUP BY obd;
update det_names a  
join tmp b on a.obd = b.obd
set a.format=b.format;
drop TEMPORARY table if EXISTS tmp;

#получения списков исполнений
insert into basik_performance (id,id00) 
select a.id,b.id 
	FROM `det_names` a 
	inner join det_names b on CONCAT(left(a.obd,LENGTH(a.obd)-2),'00')=b.obd 
where (b.razdSPID not in (1,5,6,7) and a.id!=b.id and left(a.obd,6)!='000000');

#перенос заказов !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! база маркет !!!!!!!!!!!!!!!!!!!!!!!!

Drop temporary table if exists t1;
Create temporary table t1 as 
	select a.zaka
	from temporary_tables.zakaz a 
	left join market.Orders b on a.zaka=b.zakaz 
	where b.zakaz_id is null
	group by a.zaka;
insert into market.Orders (zakaz) (select zaka from t1);
Drop temporary table if exists t1;

insert into market.zakaz (zakaz_id,id,base) 
	select c.zakaz_id,b.id,'oasu' 
	from temporary_tables.zakaz a 
	join det_names b on a.obd=b.obd
	join market.Orders c on a.zaka=c.zakaz;
update market.zakaz a 
	join market.Orders c on a.zakaz_id = c.zakaz_id
	join temporary_tables.zakaz_new b on c.zakaz=b.zaka 
	set base='mysql';

#перенос дерева
delete from det_tree where base='oasu';                                              
#дерево

insert into `det_tree` (idparent,idchild,ppp,ei,kol,zona,pos,prim,base,CreateDate,CreateUser,UpdateDate,UpdateUser)
	select distinct c.id,b.id,a.ppp,if (d.kodei is not null,d.kodei,'401'),a.kol,a.zona,a.pos,a.prim,'oasu',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd"
	from temporary_tables.det_tree a 
		INNER join det_names b on a.obd=b.obd
		inner join det_names c on a.obu=c.obd
		left join catalogs.dimensionality d on a.ei=d.kodei;
update det_tree a 
join det_names b on a.idparent=b.id
join det_names c on a.idchild=c.id
join temporary_tables.det_tree_new d on d.obu=b.obd and d.obd=c.obd
set a.base='mysql';
update det_tree set ppp=0 where ppp!='0' and ppp!='1';

#во всех новых назначить разделы спецификации
#распознавание резделов спецификации
#изделия
update `det_names` set razdspid=0 where (id in (select distinct idparent from `det_tree`) and id not in (select idchild from `det_tree`));
# узлы
update `det_names` set razdspid=3 where (id in (select idparent from `det_tree`) and id in (select idchild from `det_tree`)or pp>='40');
# выделяем среди узлов комплекты		
update `det_names` set razdspid=8 where namd like '%КОМПЛЕКТ%' and razdspid=3;

#стандартные материалы 
update `det_names` set razdspid=7 where (left(obd,9)='000000000' and right(obd,6) in (select distinct obm from temporary_tables.nsi010))or (left(obd,2)="NA"and length(obd)=6); 
#файлы
insert into files (idDet,FileInBase,FileInProj,InProjName,InBaseName,Creator,Updater,DateOfCreate,DateOfUpdate)
select b.id,a.FileInBase,a.FileInProj,fname,pname,'upd','upd',CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP() FROM temporary_tables.files a
join det_names b on b.obd=a.obd;
#корректировка материалов
update det_names a join temporary_tables.det_tree b on a.obd=b.obd and b.razdid=5 and a.razdSPID=7 set a.razdSPID=b.razdid;

call technologic.convert_old_base();
call sklad.Update();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `DelFile` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `DelFile`(path text,name text,User int)
    COMMENT 'команда на удаление записи о файле из базы'
BEGIN
	#Routine body goes here...
delete from files where InBaseName=`name` and FileInBase=path;
# событие отправить в лог
#FRowData::Delete(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `FindObdForFile` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `FindObdForFile`(obd text,FileName text,user int)
    COMMENT 'получение данных о файле по его названию и обозначению детали'
BEGIN
	#Routine body goes here...
select 
if(a.id is not null,a.id,-1) as id,
a.razdSPID,
if(a.obd is not null,a.obd,'') as obd,
if(a.namd is not null,Trim(a.namd),'') as DetName,
a1.Razdname,
if(b.FileInBase is not null,trim(b.FileInBase),'') as FileInBase,
if(b.InBaseName is not null,trim(b.InBaseName),'') as InBaseName,
if(b.InProjName is not null,trim(b.InProjName),'') as InProjName,
if(b.FileInProj is not null,trim(b.FileInProj),'') as FileInProj,

if (g3.id is not null,g3.id,0)as icoID,
if(b.Creator is not null,trim(b.Creator),'')as Creator,
b.DateOfCreate as	DateOfCreate,
if(b.Updater is not null,b.Updater,'')as Updater,
b.DateOfUpdate as DateOfUpdate,
if (d.IdGroup is null or (a.UserID!=-1 and a.UserID!=user)or f.arhive!=0,0,1)as Accept
from det_names a
join administration.sprazd a1 on a.razdSPID=a1.RazdID
left join files b on a.id=b.idDet and b.inprojname=FileName 
join administration.logins c on c.logid=USER
join administration.gtucond d on d.IDGroup=c.levelacss and d.IdCond=a.state
left join administration.files_and_types g3 on Locate(g3.FileType,FileName)  
join administration.conditions f on f.idsost=a.state
where a.obd=obd;
#FRowData::UpdateVal(String obd)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Find_loop` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Find_loop`()
BEGIN
	#Routine body goes here...
declare lvl int;
set lvl=0;
drop TEMPORARY table if EXISTS res; 
drop TEMPORARY table if EXISTS obd_lvl; 
CREATE TEMPORARY table if not EXISTS RES
(
ids text,
id int(11)unsigned,
lvl INT,
key (id)
) ENGINE=MYISAM;
CREATE TEMPORARY table if not EXISTS obd_lvl
(
ids text,
id int(11)unsigned,
lvl INT,
key (id)
) ENGINE=INNODB;

#наполенение таблицы всеми сборками и исполнениями к ним
insert into res 
select a.idparent,a.idparent,lvl FROM det_tree a join det_tree b on a.idparent=b.idchild #сужение круга поиска по наличию узлов в составе других узлов
union
select a.id,a.id,lvl 
	from basik_performance a 
	join det_tree b on b.idparent=a.id00 
	join det_tree c on b.idparent=c.idchild;

#крутим развертку вверх пока не упремся в петлю
while EXISTS (select id from res where res.lvl=lvl) and lvl<5 do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			select CONCAT(b.ids,' ',a.idparent),a.idparent,lvl+1 as lvl
			from `det_tree` a 
						inner join `obd_lvl` b on a.idchild=b.id and b.lvl=lvl;
	insert into res		
			select CONCAT(b.ids,' ',c.id),c.id,lvl+1 as lvl
			from `det_tree` a 
						join `obd_lvl` b on a.idchild=b.id and b.lvl=lvl
						JOIN	basik_performance c on c.id00=a.idparent;
	set lvl=lvl+1;
END while;

select * from res a where INSTR(ids,id) and a.lvl!=0;

drop TEMPORARY table if EXISTS res; 
drop TEMPORARY table if EXISTS obd_lvl; 
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetAllUzel` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetAllUzel`(ids text)
    COMMENT 'получает полный состав списка узлов'
BEGIN
declare lvl int;
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
CREATE TEMPORARY TABLE IF NOT EXISTS res(
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
	idci int(11)unsigned DEFAULT null,
  kol double NOT NULL,
	lvl int not null,
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
TRUNCATE TABLE res; 

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl as select * from res where 0;
TRUNCATE TABLE obd_lvl; 
#инициализация 
set @sq=CONCAT('insert into res 
	select null as idp,a.id as idc,d.id00 as idci,1 as kol,0 as lvl
from det_names a 
	left join basik_performance d on d.id=a.id
where a.id in (',ids,')');
set lvl=0;
prepare init from @sq;
EXECUTE init;
#развертка
while (EXISTS (select idc from res where res.lvl=lvl) and lvl<1000)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select b.idc as idp,a.idchild as idc,d.id00 as idci,a.kol*b.kol as kol,lvl+1 as lvl
			from `det_tree` a 
						inner join `obd_lvl` b on (a.idparent=b.idc or (a.idparent=b.idci and a.ppp=0)) and b.lvl=lvl
						left join basik_performance d on d.id=a.idchild
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if NOT EXISTS output as select a.idp,a.idc,a.kol,a.lvl from res a;
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetAllZak` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetAllZak`(zakaz text)
    COMMENT 'получение развертки состава по номерам заказов'
BEGIN
declare lvl int;
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
CREATE TEMPORARY TABLE IF NOT EXISTS res(
	idp  int(11)unsigned,
	idc	 int(11)unsigned not NULL,
	idci int(11)unsigned DEFAULT null,
  kol double NOT NULL,
	lvl int not null,
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
TRUNCATE TABLE res; 

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl as select * from res where 0;
TRUNCATE TABLE obd_lvl; 
#инициализация 
set @sq=CONCAT('insert into res
	select null as idp,c.id as idc,d.id00 as idci,c.kol as kol,0 as lvl
from market.zakaz c
	join market.Orders c1 on c.zakaz_id=c1.zakaz_id
	left join basik_performance d on d.id=c.id
where c1.zakaz in (',zakaz,')');
set lvl=0;
prepare init from @sq;
EXECUTE init;

#развертка
while (EXISTS (select idc from res where res.lvl=lvl) and lvl<1000)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select b.idc as idp,a.idchild as idc,d.id00 as idci,a.kol*b.kol as kol,lvl+1 as lvl
			from `det_tree` a 
						inner join `obd_lvl` b on (a.idparent=b.idc or (a.idparent=b.idci and a.ppp=0)) and b.lvl=lvl
						left join basik_performance d on d.id=a.idchild
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if NOT EXISTS output as select a.idp,a.idc,kol from res a;
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetAvailableConditions` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetAvailableConditions`(`ids` text,User int(11))
    COMMENT 'получает доступые состояния для пользователя'
BEGIN
	#Routine body goes here...
set @stat=concat('
SELECT
if (f1.idsost is not null,f1.idsost,-1) AS PrevState,if (f1.`name` is not null,f1.`name`,"") as PrevName,
if (b.idsost is not null,b.idsost,-1) AS CurrState,if (b.`name` is not null,b.`name`,"") as CurrName,
b.arhive as Arhive,
if (e1.idsost is not null,e1.idsost,-1) AS NextState,if (e1.`name` is not null,e1.`name`,"") as NextName,
if (a2.IdCond is not null,1,0) as PrevAccept,
if (a3.IdCond is not null,1,0) as NextAccept
FROM
administration.logins a 																																#подключение информации о пользователе
Inner Join administration.gtucond a1 ON a1.IdGroup = a.Levelacss  											#проверка наличия доступа у группы пользователя
Inner Join administration.conditions b ON b.idsost in (',ids,') and b.idsost=a1.IdCond	#получение доступных состояний из входного списка

Left Join administration.treeconds c ON c.IdCond = b.idsost AND c.type = "Basic"				#получение базовых состояний стоящих на уровень выше
Left Join administration.treeconds d ON d.IdNextCond = b.idsost AND d.type = "Basic"		#получение базовых состояний стоящих на уровень ниже

Left Join administration.gtscond e ON e.IdGroup = a.Levelacss AND e.IdCond = c.IdNextCond #Получение списка состояний стоящих на уровень выше корорые могут быть установлены пользователем
Left Join administration.gtscond f ON f.IdGroup = a.Levelacss AND f.IdCond = d.IdCond			#Получение списка состояний стоящих на уровень ниже корорые могут быть установлены пользователем

LEFT join administration.conditions e1 on e1.idsost=e.IdCond #получение информации о находящемся выше состоянии
Left join administration.conditions f1 on f1.idsost=f.IdCond #получение информации о находящемся ниже состоянии

left join administration.gtucond a2 on a2.IdGroup= a.Levelacss and a2.IdCond=f1.idsost #проверка на доступность стояний находящихся выше
left join administration.gtucond a3 on a3.IdGroup= a.Levelacss and a3.IdCond=e1.idsost #проверка на доступность стояний находящихся ниже
where a.LogID=',User);
PREPARE stl from @stat;
EXECUTE stl;
#TCond::TCond(TComponent* Owner,TTreeView &Tree,const bool &_MassAction,cSQL *db,IconsData *_IcoData,const int &User)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetDataForFileAndID` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetDataForFileAndID`(id int,FileName text,user int)
    COMMENT 'получение иннформации о файле по его названию и ид детали'
BEGIN
	#Routine body goes here...
select 
if(a.id is not null,a.id,-1) as id,
a.razdSPID,
if(a.obd is not null,a.obd,'') as obd,
if(a.namd is not null,Trim(a.namd),'') as DetName,
a1.Razdname,
if(b.FileInBase is not null,trim(b.FileInBase),'') as FileInBase,
if(b.InBaseName is not null,trim(b.InBaseName),'') as InBaseName,
if(b.InProjName is not null,trim(b.InProjName),'') as InProjName,
if(b.FileInProj is not null,trim(b.FileInProj),'') as FileInProj,

if (g3.id is not null,g3.id,0)as icoID,
if(b.Creator is not null,trim(b.Creator),'')as Creator,
b.DateOfCreate as	DateOfCreate,
if(b.Updater is not null,b.Updater,'')as Updater,
b.DateOfUpdate as DateOfUpdate,
if (d.IdGroup is null or (a.UserID!=-1 and a.UserID!=user)or f.arhive!=0,0,1)as Accept

from det_names a
join administration.sprazd a1 on a.razdSPID=a1.RazdID
left join files b on a.id=b.idDet and b.inprojname=FileName 
join administration.logins c on c.logid=USER
join administration.gtucond d on d.IDGroup=c.levelacss and d.IdCond=a.state
left join administration.files_and_types g3 on Locate(g3.FileType,FileName)  
join administration.conditions f on f.idsost=a.state

where a.id=id;
#FRowData::UpdateVal(int id)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetDet` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetDet`(ids text)
    COMMENT 'получение списка деталей с пересчитанным кол-вом по сборкам на 1'
BEGIN
declare lvl int;
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
CREATE TEMPORARY TABLE IF NOT EXISTS res(
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
	idci int(11)unsigned DEFAULT null,
  kol double NOT NULL,
	lvl int not null,
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
TRUNCATE TABLE res; 

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl as select * from res where 0;
TRUNCATE TABLE obd_lvl; 

#инициализация 
set @sq=CONCAT('insert into res 
	select null as idp,a.id as idc,d.id00 as idci,1 as kol,0 as lvl
from det_names a 
	left join basik_performance d on d.id=a.id
where a.id in (',ids,')');
set lvl=0;
prepare init from @sq;
EXECUTE init;
#развертка
while (EXISTS (select idc from res where res.lvl=lvl) and lvl<1000)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select b.idc as idp,a.idchild as idc,d.id00 as idci,(a.kol*b.kol) as kol,lvl+1 as lvl
			from `det_tree` a 
						inner join `obd_lvl` b on (a.idparent=b.idc or (a.idparent=b.idci and a.ppp=0)) and b.lvl=lvl
						left join basik_performance d on d.id=a.idchild
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
CREATE TEMPORARY TABLE IF NOT EXISTS output as select a.idc,sum(a.kol) as kol from res a
GROUP BY a.idc order by a.idc;
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetDetInUzel` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetDetInUzel`(id int,kol int)
    COMMENT 'получение списка деталей по одному узлу пересчет колва на указан'
BEGIN
declare lvl int;
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
CREATE TEMPORARY TABLE IF NOT EXISTS res(
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
	idci int(11)unsigned DEFAULT null,
  kol double NOT NULL,
	lvl int not null,
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
TRUNCATE TABLE res; 

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl as select * from res where 0;
TRUNCATE TABLE obd_lvl; 
set lvl=0;

insert into res #инициализация 
	select null as idp,a.id as idc,d.id00 as idci,kol as kol,lvl as lvl
from det_names a 
	left join basik_performance d on d.id=a.id
where a.id=id;
#развертка
while (EXISTS (select idc from res where res.lvl=lvl) and lvl<1000)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select b.idc as idp,a.idchild as idc,d.id00 as idci,(a.kol*b.kol) as kol,lvl+1 as lvl
			from `det_tree` a 
						inner join `obd_lvl` b on (a.idparent=b.idc or (a.idparent=b.idci and a.ppp=0)) and b.lvl=lvl
						left join basik_performance d on d.id=a.idchild
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if NOT EXISTS output as select a.idc,sum(a.kol) as kol from res a
GROUP BY a.idc order by a.idc;

Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetDetInZakaz` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetDetInZakaz`(zakaz text,ids text)
    COMMENT 'получение списка деталей по одному заказу (опред и все узлы)'
BEGIN
declare lvl int;
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
CREATE TEMPORARY TABLE IF NOT EXISTS res(
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
	idci int(11)unsigned DEFAULT null,
  kol double NOT NULL,
	lvl int not null,
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
TRUNCATE TABLE res; 

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl as select * from res where 0;
TRUNCATE TABLE obd_lvl; 
set lvl=0;

#инициализация 
if (ids='all') 
	then 
		set @sq=CONCAT('insert into res
			select null as idp,c.id as idc,d.id00 as idci,c.kol as kol,0 as lvl
		from market.zakaz c
			join market.Orders c1 on c.zakaz_id=c1.zakaz_id
			left join basik_performance d on d.id=c.id
		where c1.zakaz in (',zakaz,')');
	ELSE
		set @sq=CONCAT('insert into res
			select null as idp,c.id as idc,d.id00 as idci,c.kol as kol,0 as lvl
		from market.zakaz c
			join market.Orders c1 on c.zakaz_id=c1.zakaz_id
			left join basik_performance d on d.id=c.id
		where c1.zakaz in (',zakaz,') and c.id in (',ids,')');
end if;

set lvl=0;
prepare init from @sq;
EXECUTE init;
#развертка
while (EXISTS (select idc from res where res.lvl=lvl) and lvl<1000)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select b.idc as idp,a.idchild as idc,d.id00 as idci,(a.kol*b.kol) as kol,lvl+1 as lvl
			from `det_tree` a 
						inner join `obd_lvl` b on (a.idparent=b.idc or (a.idparent=b.idci and a.ppp=0)) and b.lvl=lvl
						left join basik_performance d on d.id=a.idchild
			);
	set lvl=lvl+1;
END while;

drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if NOT EXISTS output as select a.idc,sum(a.kol) as kol from res a
GROUP BY a.idc order by a.idc;

Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetFiles` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetFiles`(id int)
    COMMENT 'загрузка файлов для одной детали'
BEGIN
	#Routine body goes here...
select idDet,InProjName as `Name` from files where iddet=id;
#TFileDisigner::LoadFiles(const Obd *const det,bool MassAction)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetFilesForTree` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetFilesForTree`(id int)
    COMMENT 'зарузка файлов для узла и всех входящих деталей'
BEGIN
	#Routine body goes here...
call GetDetInUzel(id,1);
select idDet,InProjName as `Name` from files where iddet in (select idc from output) ORDER BY iddet,InBaseName;
drop TEMPORARY table if EXISTS output;
#TFileDisigner::LoadFiles(const Obd *const det,bool MassAction)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetNextStates` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetNextStates`(state smallint(6),User int(11))
    COMMENT 'получение списка возможных состояний для смены текущего'
BEGIN
	#Routine body goes here...
SELECT
if (b.idsost is not null,b.idsost,-1) AS CurrState,if (b.`name` is not null,b.`name`,"") as CurrName,
b.arhive as Arhive,
if (e1.idsost is not null,e1.idsost,-1) AS NextState,if (e1.`name` is not null,e1.`name`,"") as NextName,
if (a3.IdCond is not null,1,0) as NextAccept
FROM
administration.logins a																																		#подключение информации о пользователе
Inner Join administration.gtucond a1 ON a1.IdGroup = a.Levelacss													#проверка наличия доступа у группы пользователя
Inner Join administration.conditions b ON b.idsost=state and b.idsost=a1.IdCond						#получение доступных состояний из входного списка

Left Join administration.treeconds c ON c.IdCond = b.idsost #AND c.type = "Basic"  				#получение состояний стоящих на уровень выше
Left Join administration.gtscond e ON e.IdGroup = a.Levelacss AND e.IdCond = c.IdNextCond #Получение списка состояний стоящих на уровень выше корорые могут быть установлены пользователем
LEFT join administration.conditions e1 on e1.idsost=e.IdCond															#получение информации о находящемся выше состоянии
left join administration.gtucond a3 on a3.IdGroup= a.Levelacss and a3.IdCond=e1.idsost    #проверка на доступность стояний находящихся выше

where a.LogID=User ORDER BY NextState;
#TStSelect::TStSelect(TComponent* Owner,cSQL *db,IconsData *_IcoData,const int &State,const int &User)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetParents` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `GetParents`(ids text, lim1 int(11), lim2 int(11))
    COMMENT 'функция для получения списка входимости'
BEGIN
	#Routine body goes here...
drop TEMPORARY table if EXISTS tmp;
create TEMPORARY table tmp
(
idp int(11)unsigned,
ppp varchar(1),
key `idp` (`idp`)
)ENGINE MEMORY;
set @sq=CONCAT('insert into tmp select idparent,ppp from det_tree where idchild in (',ids,')');
prepare step1 from @sq;
execute step1;

set @sq=CONCAT('
select a.id,a.obd,a.namd,a.razdSPID,c.Razdname 
from constructions.det_names a 
join constructions.det_tree b on b.idparent=a.id and b.idchild in (',ids,') 
join administration.sprazd c on c.RazdID=a.razdSPID 
UNION
select b.id,b.obd,b.namd,b.razdSPID,c.Razdname 
from constructions.tmp a
join constructions.det_names b on a.idp=b.id
join constructions.basik_performance b1 on b1.id00=a.idp	
join administration.sprazd c on c.RazdID=b.razdSPID 
UNION
select a.id,a.obd,a.namd,a.razdSPID,c.Razdname 
from constructions.det_names a 
join technologic.det_info d on d.id=a.id and d.obmid in (',ids,') 
join administration.sprazd c on c.RazdID=a.razdSPID 
order by obd limit ',lim1,',',lim2);
prepare step2 from @sq;#and(b.idparent is not null or d.obmid is not null)
EXECUTE step2;
drop TEMPORARY table if EXISTS tmp;
#TSearch::GetParents(Obd *data,TTreeNode *Node,bool AsChild)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetTreeConditions` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetTreeConditions`(ids text,User int(11))
    COMMENT 'определяет возможное следующее и предыдущее состояние'
BEGIN
	#Routine body goes here...
call GetDet(ids);
SELECT
if (f1.idsost is not null,f1.idsost,-1) AS PrevState,if (f1.`name` is not null,f1.`name`,"") as PrevName,
if (b.idsost is not null,b.idsost,-1) AS CurrState,if (b.`name` is not null,b.`name`,"") as CurrName,
b.arhive as Arhive,
if (e1.idsost is not null,e1.idsost,-1) AS NextState,if (e1.`name` is not null,e1.`name`,"") as NextName,
if (a2.IdCond is not null,1,0) as PrevAccept,
if (a3.IdCond is not null,1,0) as NextAccept
FROM
administration.logins a#подключение информации о пользователе
Inner Join administration.gtucond a1 ON a1.IdGroup = a.Levelacss#проверка наличия доступа у группы пользователя
Inner Join administration.conditions b ON b.idsost in (Select b.state from output a inner join det_names b on a.idc=b.id group by b.state) and b.idsost=a1.IdCond#получение доступных состояний из входного списка

Left Join administration.treeconds c ON c.IdCond = b.idsost AND c.type = "Basic"#получение базовых состояний стоящих на уровень выше
Left Join administration.treeconds d ON d.IdNextCond = b.idsost AND d.type = "Basic"#получение базовых состояний стоящих на уровень ниже

Left Join administration.gtscond e ON e.IdGroup = a.Levelacss AND e.IdCond = c.IdNextCond#Получение списка состояний стоящих на уровень выше корорые могут быть установлены пользователем
Left Join administration.gtscond f ON f.IdGroup = a.Levelacss AND f.IdCond = d.IdCond#Получение списка состояний стоящих на уровень ниже корорые могут быть установлены пользователем

LEFT join administration.conditions e1 on e1.idsost=e.IdCond#получение информации о находящемся выше состоянии
Left join administration.conditions f1 on f1.idsost=f.IdCond#получение информации о находящемся ниже состоянии

left join administration.gtucond a2 on a2.IdGroup= a.Levelacss and a2.IdCond=f1.idsost#проверка на доступность стояний находящихся выше
left join administration.gtucond a3 on a3.IdGroup= a.Levelacss and a3.IdCond=e1.idsost#проверка на доступность стояний находящихся ниже
where a.LogID=User;
drop TEMPORARY table if EXISTS output;
#TCond::TCond(TComponent* Owner,TTreeView &Tree,const bool &_MassAction,cSQL *db,IconsData *_IcoData,const int &User)

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_id` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_id`(obd text)
    COMMENT 'функция для соспоставления идентификатора и обозначения'
BEGIN
	#Routine body goes here...
select 
a.id,
trim(a.obd)as obd,
trim(a.namd)as namd,
a.razdSPID,
b.Razdname 
from constructions.det_names a 
left join administration.sprazd b on RazdID=razdSPID where
a.obd=obd;
#void 	DtInfo::Set_obm(String r)
#void  	SPEditor::LoadFromBase	(String obd)
#int 		SpRow::Get_id	(const String &obd)
#void			TSPEditor::CompareSP	(void)
#bool			TSPEditor::SaveToBase	(void)
#Tree_data::Tree_data(cSQL *const db,...)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_isp_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_isp_list`(id int)
    COMMENT 'загрузка списка исполнений'
BEGIN
	#Routine body goes here...
drop TEMPORARY table if EXISTS tmp;
create TEMPORARY table if not EXISTS tmp
(
id int(11)UNSIGNED,
main tinyint(4)UNSIGNED,
obd VARCHAR(255),
key id (id)
)ENGINE=MEMORY;
insert into tmp 
select a.id,if (b.id is null,1,0),a.obd 
	from det_names a left 
	JOIN basik_performance b on a.id=b.id 
where a.id=id;#проверка исполнения по которому идет запрос

insert into tmp select k1.id,0,a.obd from basik_performance k 
								join basik_performance k1 on k.id00=k1.id00  
								join det_names a on a.id=k1.id
								where k.id=id;#зацепление всех остальных исполнений
insert into tmp select k.id,0,a.obd from basik_performance k 
								join det_names a on a.id=k.id 
								where k.id00=id; #поиск входящих исполнений
insert into tmp select k.id00,1,a.obd from basik_performance k 
								join det_names a on a.id=k.id00 
								where k.id=id;#поиск базового исполнения
select * from tmp a GROUP BY a.id;
drop TEMPORARY table if EXISTS tmp;
#void  			TSPEditor::LoadFromBase	(String obd)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_obd` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_obd`(id int)
BEGIN
	#Routine body goes here...
select 
a.id,
trim(a.obd)as obd,
trim(a.namd)as namd,
a.razdSPID,
b.Razdname 
from constructions.det_names a 
left join administration.sprazd b on RazdID=razdSPID 
where a.id=id;
#bool 	Obd::Get_Val (char type)


END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_uzel_list_by_det` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_uzel_list_by_det`(id int)
    COMMENT 'получение списка узлов по одному детали'
BEGIN
declare lvl int;
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
CREATE TEMPORARY TABLE IF NOT EXISTS res(
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
	lvl int not null,
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=memory;
TRUNCATE TABLE res; 

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl as select * from res where 0;
TRUNCATE TABLE obd_lvl; 
set lvl=0;

insert into res #инициализация 
	select a.id,a.id,lvl as lvl
from det_names a 
where a.id=id;
#развертка
while(EXISTS (select idc from res where res.lvl=lvl) and lvl<1000)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select a.idparent as idp,a.idchild as idc,lvl+1 as lvl
			from `det_tree` a 
						inner join `obd_lvl` b on (a.idchild=b.idp) and b.lvl=lvl
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if NOT EXISTS output as select a.idp from res a
GROUP BY a.idp order by a.idp;

Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `LoadDet` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `LoadDet`(id int,user int)
    COMMENT 'загрузка одной детали(развертываемая деталь спецификации)'
BEGIN
	#Routine body goes here...
SELECT 
-1 as idparent,
'' as obu,
b.id as idchild,
b.obd,
trim(b.namd) as `name`,
b.format,b.pp,
if (g3.napp is not null,g3.napp,'') as ppname,
0 as kol,
'-1' as ppp,
'-1' as ei,
'' as eiName,
0 as pos,
'' as zona,
'' as prim,
b.razdSPID,
e.Razdname,
b.state,
f.`name` as CondName,
if (b.UserID is not null,b.UserID,-1)as UserID,
if (g2.LogIn is not null,g2.LogIn,'')as User,#спецполя!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#инфо поля
b.CreateDate as DetCreated,if (b.CreateUser is not null,b.CreateUser,'') as DetCreator,
b.UpdateDate as DetUpdated,if (b.UpdateUser is not null,b.UpdateUser,'') as DetUpdater,
null as RowCreated,'' as RowCreator,
null as RowUpdated,'' AS RowUpdater,
#разрешения
e.CanChild,
f.arhive,
if (g.IdGroup is null or (b.UserID is not null and b.UserID!=user),0,1)as Accept
FROM  det_names b 
join administration.sprazd e on  e.RazdID=b.razdSPID
join administration.conditions f on f.idsost=b.state
join administration.logins g1 on g1.logId=user
left join administration.logins g2 on g2.logId=b.UserID#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
join catalogs.proizv_prizn g3 on g3.pp=b.pp
left join administration.gtucond g on g.IdCond=b.state and g.IdGroup=g1.levelacss
where b.id=id order by b.razdSPID,b.obd;
#TreeRow::UpdateVal 		(void)
#TSpTree::LoadTree (int _id)
#bool 	SpRow::Load_data	()
#void  	TSPEditor::LoadFromBase	(String obd)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `LoadFiles` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `LoadFiles`(idDet int,user int)
    COMMENT 'загрузка списока файлов прикрепленных к детали'
BEGIN
	#Routine body goes here...
SELECT 
b.id,
b.razdSPID,
b.obd,
Trim(b.namd) as namd,
b1.Razdname,
a.InProjName as FileName,
a.FileInProj as FilePath,
if (g3.id is not null,g3.id,0)as icoID,
#инфо поля
a.DateOfCreate as DateOfCreate,
if (a.Creator is not null,a.Creator,'') as Creator,
a.DateOfUpdate as DateOfUpdate,
if (a.Updater is not null,a.Updater,'') as Updater,
#разрешения
if (g.IdGroup is null or (b.UserID!=-1 and b.UserID!=user)or f.arhive!=0,0,1)as Accept
FROM  
files a
join det_names b on a.iddet=b.id
join administration.sprazd b1 on b.razdSPID=b1.RazdID
join administration.conditions f on f.idsost=b.state
join administration.logins g1 on g1.logId=user
left join administration.gtucond g on g.IdCond=b.state and g.IdGroup=g1.levelacss
left join administration.files_and_types g3 on Locate(g3.FileType,a.`InProjName`)  
where a.idDet=idDet order by a.`InProjName`;
#TSpTree::LoadFiles(TTreeNode *Node)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `LoadFullSP` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `LoadFullSP`(id int,user int)
    COMMENT 'загрузка составной спецификации'
BEGIN
	#Routine body goes here...
drop TEMPORARY table if EXISTS tmp;
drop TEMPORARY table if EXISTS output;
create TEMPORARY table if not EXISTS tmp
(
id int(11)UNSIGNED,
key id (id)
)ENGINE=MEMORY;

insert into tmp 
select a.id
	from det_names a 
	left JOIN basik_performance b on a.id=b.id 
where a.id=id;#проверка исполнения по которому идет запрос

insert into tmp select k1.id from basik_performance k 
								join basik_performance k1 on k.id00=k1.id00  
								where k.id=id;#зацепление всех остальных исполнений
insert into tmp select k.id from basik_performance k 
								where k.id00=id; #поиск входящих исполнений
insert into tmp select k.id00 from basik_performance k 
								where k.id=id;#поиск базового исполнения

create TEMPORARY table if not EXISTS output AS
 select * from tmp a GROUP BY a.id;

select
a.idparent,
c.obd as obu,
a.idchild,
b.obd,
trim(b.namd) as `name`,
b.format,
b.pp,
if (g3.napp is not null,g3.napp,'') as ppname,
a.kol,
a.ppp,a.ei,d.snameei as eiName,
a.pos,
a.zona,
a.prim,
b.razdSPID,
e.Razdname,
b.state,
f.`name` as CondName,
if (b.UserID is not null,b.UserID,-1)as UserID,#спецполя
if (g2.LogIn is not null,g2.LogIn,'')as User,#спецполя!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#инфо поля
b.CreateDate as DetCreated,
if (b.CreateUser is not null,b.CreateUser,'')  as DetCreator,

b.UpdateDate as DetUpdated,
if (b.UpdateUser is not null,b.UpdateUser,'') as DetUpdater,

a.CreateDate as RowCreated,
if (a.CreateUser is not null,a.CreateUser,'') as RowCreator,

a.UpdateDate as RowUpdated,
if (a.UpdateUser is not null,a.UpdateUser,'') as RowUpdater,
#разрешения
e.CanChild,
f.arhive,
if (g.IdGroup is null or (b.UserID is not null and b.UserID!=user),0,1)as Accept
FROM   `det_tree` a 
join det_names b on a.idchild=b.id
join output c1 on a.idparent=c1.id #and if (c1.id!=id,a.ppp=0,1)
join det_names c on a.idparent=c.id
join catalogs.dimensionality d on a.ei=d.kodei
join administration.sprazd e on  e.RazdID=b.razdSPID
join administration.conditions f on f.idsost=b.state
join administration.logins g1 on g1.logId=user
left join administration.logins g2 on g2.logId=b.UserID#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
join catalogs.proizv_prizn g3 on g3.pp=b.pp
left join administration.gtucond g on g.IdCond=b.state and g.IdGroup=g1.levelacss
order by a.ppp,c.obd,b.razdSPID,b.obd;
drop TEMPORARY table if EXISTS tmp;
drop TEMPORARY table if EXISTS output;
#void  			TSPEditor::LoadFromBase	(String obd)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `LoadTree` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `LoadTree`(id int,user int)
    COMMENT 'загрузка списока объектов прикрепленных к узлу'
BEGIN
	#Routine body goes here...
drop TEMPORARY table if EXISTS tmp;
create TEMPORARY table if not EXISTS tmp
(
id int(11)UNSIGNED,
key id (id)
)ENGINE=MEMORY;
insert into tmp select k.id00 from basik_performance k where k.id=id;
insert into tmp VALUES (id);
select
a.idparent,
c.obd as obu,
a.idchild,
b.obd,
trim(b.namd) as `name`,
b.format,
b.pp,
if (g3.napp is not null,g3.napp,'') as ppname,
a.kol,
a.ppp,a.ei,d.snameei as eiName,
a.pos,
a.zona,
a.prim,
b.razdSPID,
e.Razdname,
b.state,
f.`name` as CondName,
if (b.UserID is not null,b.UserID,-1)as UserID,#спецполя
if (g2.LogIn is not null,g2.LogIn,'')as User,#спецполя!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#инфо поля
b.CreateDate as DetCreated,
if (b.CreateUser is not null,b.CreateUser,'')  as DetCreator,

b.UpdateDate as DetUpdated,
if (b.UpdateUser is not null,b.UpdateUser,'') as DetUpdater,

a.CreateDate as RowCreated,
if (a.CreateUser is not null,a.CreateUser,'') as RowCreator,

a.UpdateDate as RowUpdated,
if (a.UpdateUser is not null,a.UpdateUser,'') as RowUpdater,
#разрешения
e.CanChild,
f.arhive,
if (g.IdGroup is null or (b.UserID is not null and b.UserID!=user),0,1)as Accept
FROM   `det_tree` a 
join det_names b on a.idchild=b.id
join tmp c1 on a.idparent=c1.id and if (c1.id!=id,a.ppp=0,1)
join det_names c on a.idparent=c.id
join catalogs.dimensionality d on a.ei=d.kodei
join administration.sprazd e on  e.RazdID=b.razdSPID
join administration.conditions f on f.idsost=b.state
join administration.logins g1 on g1.logId=user
left join administration.logins g2 on g2.logId=b.UserID#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
join catalogs.proizv_prizn g3 on g3.pp=b.pp
left join administration.gtucond g on g.IdCond=b.state and g.IdGroup=g1.levelacss
order by b.razdSPID,b.obd;
drop TEMPORARY table if EXISTS tmp;
#TSpTree::LoadBranch(TTreeNode *Node)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `SpDel` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `SpDel`(ids text,param text)
    COMMENT 'Удаление информации по детали/ям из базы'
BEGIN
#Routine body goes here...

CASE param
	WHEN "sp_only" THEN
		BEGIN
		set @sq=CONCAT('delete from det_tree where idparent in(',ids,')');#только указанные спецификации без вложений
		prepare init from @sq;
		EXECUTE init;		
		END;
	WHEN "det" THEN
		BEGIN
		set @sq=CONCAT('delete from det_names where id in(',ids,')');#удалить всю информацию по деталям
		prepare init from @sq;
		EXECUTE init;		
		END;
	WHEN "sp_and_all_det" THEN
		BEGIN
		call GetAllUzel(ids);
		/*удалить все кроме стандартных если больше нигде не используется*/
		drop TEMPORARY table if EXISTS out1;
		drop TEMPORARY table if EXISTS out2;
		drop TEMPORARY table if exists out3;
		create TEMPORARY table out1
		(
		idp  int(11)unsigned,
		key `idp`(`idp`) 
		)ENGINE=memory;
insert into out1  select DISTINCT idp from output where idp is not null;#все узлы
		create TEMPORARY table out2
		(
		idc  int(11)unsigned,
		key `idc`(`idc`)
		)ENGINE=memory;
insert into out2 select DISTINCT idc from output;#все входящие
		create TEMPORARY table out3
		(
		idc  int(11)unsigned,
		key `idc`(`idc`)
		)ENGINE=memory;
insert into out3 select DISTINCT idchild as idc from det_tree where idchild in #все применяемые еще гдето
		(select idc from out2) and idparent not in(select idp from out1);
		delete from det_names where id in (select idc from out2) and id not in (select idc from out3) and id not in (select id from market.zakaz) and razdSPID not in(5,6,7);
		delete from det_tree where idparent in (select idp from out1); 
		END;
end CASE;

#TSpTree::SpDel(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `unblock` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `unblock`(ids text, User int)
    COMMENT 'разблокировка всех указанных деталей'
BEGIN
set @sq=CONCAT('update det_names a 
set a.UserID=null
where a.id in (',ids,') and a.userID=',User);
prepare init from @sq;
EXECUTE init;
/*
TSpTree::UnBlock(String &ids)
bool  TTechWnd::Close_teh(void)
*/
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `UnBlockAll` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `UnBlockAll`(ids text, User int)
    COMMENT 'разблокировка всех деталей входящих в указанные узлы'
BEGIN
declare lvl int;
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS output;
call GetDet(ids);

update det_names a 
inner join output b on a.id=b.idc
set a.UserID=null
where a.userID=User;

Drop TEMPORARY TABLE if EXISTS output;
#TSpTree::UnBlock(String &ids)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Update`()
BEGIN
	#Routine body goes here...
#спецификация
#пренос деталей 
#апдейт старых
update det_names a 
	inner join temporary_tables.nsi003 b on a.obd=b.obd 
	set a.namd=trim(b.namd),
	a.base='new'
	where a.base='oasu';

update det_names a 
	inner join temporary_tables.nsi032 b on a.obd=CONCAT('000000000',b.obm) 
	set a.namd=trim(CONCAT(trim(b.nama),' ',trim(b.goma))),
	a.base='new'
	where a.base='oasu';
#вставка новых
insert into det_names (obd,namd,base,CreateDate,CreateUser,UpdateDate,UpdateUser) 
	select DISTINCT a.obd,trim(a.namd),'new',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd"
	from temporary_tables.nsi003 a 
	where a.obd not in (select distinct obd from det_names) group by a.obd order by a.obd;

/*insert into det_names (obd,namd,base,CreateDate,CreateUser,UpdateDate,UpdateUser) 
	select DISTINCT obd,trim(namd),'new',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd" 
	from temporary_tables.ogt803 a 
	where a.obd not in (select distinct obd from det_names) group by a.obd order by a.obd;*/

insert into det_names (obd,namd,base,CreateDate,CreateUser,UpdateDate,UpdateUser)
	select DISTINCT a.obd,'','new',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd"  
	from temporary_tables.nsi001 a 
	where a.obd not in (select distinct obd from det_names) and left(obd,9)!='000000000';

insert into `det_names` (obd,namd,base,CreateDate,CreateUser,UpdateDate,UpdateUser)
	select DISTINCT obu,'','new',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd"
	from temporary_tables.nsi001 
	where obu not in (select distinct obd from det_names);

insert into `det_names` (obd,namd,base,CreateDate,CreateUser,UpdateDate,UpdateUser) 
	select obd,'','new',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd"
	from temporary_tables.nsi006
	where obd not in (select distinct obd from `det_names`)and trim(obd)!=''GROUP BY obd ORDER BY obd;

insert into det_names (obd,namd,base,CreateDate,CreateUser,UpdateDate,UpdateUser,razdspid)
	select CONCAT('000000000',obm),CONCAT(trim(nama),' ',trim(goma),' ',trim(prma),' ',trim(gopr)),'new',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd",5 
	from temporary_tables.nsi032 
	where CONCAT('000000000',obm) not in (select distinct obd from `det_names`)
	GROUP BY obm;

# обновить рр в детнеймсах
drop TEMPORARY table if EXISTS tmp;
create TEMPORARY table if not EXISTS tmp as select obd,pp from temporary_tables.nsi001 where pp in (select pp from catalogs.proizv_prizn) GROUP BY obd;
update det_names a inner join tmp b on a.obd = b.obd and a.pp!=b.pp
set a.pp=b.pp,base='new';# where a.base!='mysql';
drop TEMPORARY table if EXISTS tmp;

#получения списков исполнений
delete FROM basik_performance where id00 in(select id from det_names where base='new') or id in(select id from det_names where base='new');
insert into basik_performance (id,id00) 
select a.id,b.id 
	FROM `det_names` a 
	inner join det_names b on CONCAT(left(a.obd,LENGTH(a.obd)-2),'00')=b.obd 
where (b.razdSPID not in (1,5,6,7) and a.id!=b.id and left(a.obd,6)!='000000') and (a.base='new' or b.base='new');

#перенос заказов !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! база маркет !!!!!!!!!!!!!!!!!!!!!!!!

Drop temporary table if exists t1;
Create temporary table t1 as 
	select a.zaka
	from temporary_tables.nsi006 a 
	left join market.Orders b on a.zaka=b.zakaz 
	where b.zakaz_id is null
	group by a.zaka;
insert into market.Orders (zakaz) (select zaka from t1);
Drop temporary table if exists t1;

delete from market.zakaz where base='OASU';
insert into market.zakaz (zakaz_id,id,base) 
	select c.zakaz_id,b.id,'oasu' 
	from temporary_tables.nsi006 a join det_names b on a.obd=b.obd
	join market.Orders c on a.zaka=c.zakaz
	where c.zakaz_id not in (select DISTINCT zakaz_id from market.zakaz); 
#перенос дерева
delete from det_tree where base='oasu';                                              
#дерево
insert into `det_tree` (idparent,idchild,ppp,ei,kol,base,CreateDate,CreateUser,UpdateDate,UpdateUser)
	select distinct c.id,b.id,a.ppp,if (d.kodei is not null,d.kodei,'401'),sum(a.kol),'oasu',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd"
	from temporary_tables.nsi001 a 
		INNER join det_names b on a.obd=b.obd
		inner join det_names c on a.obu=c.obd
		left join catalogs.dimensionality d on a.ei=d.kodei
		left join temporary_tables.nsi010 e on a.obu=e.obu and a.obd=CONCAT('000000000',e.obm)
		left join det_tree e1 on e1.idparent=c.id and e1.idchild=b.id
	WHERE e.obu is null and e1.idparent is null
	group by c.id,b.id;
#матиериалы 
insert into `det_tree` (idparent,idchild,ppp,ei,kol,base,CreateDate,CreateUser,UpdateDate,UpdateUser)
	select c.id,b.id,0,if (d.kodei is not null,d.kodei,'401'),sum(a.nrm),'oasu',CURRENT_TIMESTAMP(),"upd",CURRENT_TIMESTAMP(),"upd"
	from temporary_tables.nsi010 a 
		join det_names b on CONCAT('000000000',a.obm)=b.obd
		join det_names c on a.obu=c.obd
		left join catalogs.dimensionality d on a.ei=d.kodei
		left join det_tree e on e.idparent=c.id and e.idchild=b.id
	WHERE e.idparent is null
	group by c.id,b.id;

#во всех новых назначить разделы спецификации
#распознавание резделов спецификации
#изделия
update `det_names` set razdspid=0 where (id in (select distinct idparent from `det_tree`) and id not in (select idchild from `det_tree`)) and base='new';
# узлы
update `det_names` set razdspid=3 where (id in (select idparent from `det_tree`) and id in (select idchild from `det_tree`)or pp>='40')and base='new';
# выделяем среди узлов комплекты		
update `det_names` set razdspid=8 where namd like '%КОМПЛЕКТ%' and razdspid=3 and base='new';

#стандартные материалы 
update det_names a join temporary_tables.nsi010 b on a.obd=concat('000000000',b.obm) set a.razdspid=7 where base="new"; 

#перекрасить new в oasu
update det_names set base="oasu" where base="new";
call sklad.Update();

#расстановка меток

update det_names set razdSPID=6 
where 
(RIGHT(obd,6)like '34%' #энергетич электротехн оборудование/
or RIGHT(obd,6)like '35%' #измерительные приборы/
or RIGHT(obd,6)like '36%' #электровакуумные/
or RIGHT(obd,6)like '37%' #электровакуумные/
or RIGHT(obd,6)like '39%') #прочие покупные/
and LENGTH(obd)=15 and left(obd,9)='000000000';

update det_names set razdSPID=7 
where 
(RIGHT(obd,6)like '0%' #черные металлы/
or RIGHT(obd,6)like '1%' #цветные металлы/
or RIGHT(obd,6)like '2%' #неметалически и прочие материалы/
or RIGHT(obd,6)like '30%' #покупные полуфабрикаты/
or RIGHT(obd,6)like '52%' #изделия из проволоки/
or RIGHT(obd,6)like '58%') #лента стальная холоднокатанная/
and LENGTH(obd)=15 and left(obd,9)='000000000';

update det_names set razdSPID=5 
where 
(RIGHT(obd,6)like '233%' #шнуры трубки кольца манжеты воротники /
or RIGHT(obd,6)like '232%' #шнуры трубки кольца манжеты воротники /
or RIGHT(obd,6)like '31%' #радиодетали и радио компоненты /
or RIGHT(obd,6)like '32%' #радиодетали и радио компоненты /
or RIGHT(obd,6)like '33%' #арматура промышленная трубопроводная/
or RIGHT(obd,6)like '38%' #подшипники и цепи/
or RIGHT(obd,6)like '53%' #изделия крепежные машиностроительные/
or RIGHT(obd,6)like '54%' #изделия крепежные машиностроительные/
or RIGHT(obd,6)like '55%' #изделия крепежные машиностроительные/
or RIGHT(obd,6)like '56%') #изделия крепежные машиностроительные/
and LENGTH(obd)=15 and left(obd,9)='000000000';

update det_names set razdSPID=9 
where 
(
RIGHT(obd,6)like '020%' #Химическая продукция
or RIGHT(obd,6)like '034%' #!Энергетич.. электротехнич. оборудование. машины. телефон.изделия
or RIGHT(obd,6)like '116%' #Олово
or RIGHT(obd,6)like '117%' #Баббиты и прочие
or RIGHT(obd,6)like '120%' #Висмут
or RIGHT(obd,6)like '162%' #Припой серебряный
or RIGHT(obd,6)like '200%' #Пр-ты неорг..хим. и горнохим. Сырье(газы.кислоты.окислы.соли.пр.)
or RIGHT(obd,6)like '201%' #Пр-ты неорг..хим. и горнохим. Сырье(газы.кислоты.окислы.соли.пр.)
or RIGHT(obd,6)like '204%' #Химреактивы неорганические
or RIGHT(obd,6)like '206%' #Химреактивы органические
or RIGHT(obd,6)like '208%' #Hефтепродукты (топливо. масла. парафины. церезины. воск. составы)
or RIGHT(obd,6)like '210%' #Краски сухие. пигменты. глазури
or RIGHT(obd,6)like '211%' #Лаки на конденсационных смолах. сиккативы и растворители
or RIGHT(obd,6)like '212%' #Эмали. грунтовки и шпатлевки на конденсационных смолах
or RIGHT(obd,6)like '213%' #Лаки. эмали. гр-ки и шп-ки на полимериз. смолах. растворит. к ним
or RIGHT(obd,6)like '214%' #Лаки. эмали. гр-ки. шп-ки на эфирах целлюлозы и растворит. к ним
or RIGHT(obd,6)like '220%' #Смолы природные. полимеры. пластмассы
or RIGHT(obd,6)like '222%' #Листовые и пленочные материалы. пластикаты
or RIGHT(obd,6)like '224%' #Пенопласт. поропласты. прессматериалы
or RIGHT(obd,6)like '230%' #Клеи. герметики. резины сырые. товарные
or RIGHT(obd,6)like '232%' #!Шнуры. трубки. кольца. манжеты. воротники
or RIGHT(obd,6)like '234%' #!Рукава и рукавные изделия
or RIGHT(obd,6)like '235%' #!Ленты конвейерные. ремни. ткани прорезиненные
or RIGHT(obd,6)like '236%' #!Шины и изделия шинной промышленности
or RIGHT(obd,6)like '238%' #Асбестовые технические изделия (паронит)
#or RIGHT(obd,6)like '239%' #Изделия эбонитовые
or RIGHT(obd,6)like '243%' #Лакоткани
or RIGHT(obd,6)like '244%' #Трубки электроизоляционные
or RIGHT(obd,6)like '245%' #Материалы электроизоляционные разные
or RIGHT(obd,6)like '246%' #Миканиты. слюдиниты. слюдопласты
#or RIGHT(obd,6)like '250%' #Лесоматериалы круглые
#or RIGHT(obd,6)like '253%' #Фанера. шпон. плиты
#or RIGHT(obd,6)like '257%' #Фибра. картон и изделия из них
or RIGHT(obd,6)like '260%' #Ткани (х/б. льняные. шелковые. шерстяные. капроновые и др.)
or RIGHT(obd,6)like '262%' #Ткани технические и изделия из них
or RIGHT(obd,6)like '264%' #Обтирочные материалы. вата. войлок и изделия из них
or RIGHT(obd,6)like '265%' #Hитки. тесьма. шнуры. шпагат
or RIGHT(obd,6)like '267%' #Кожевенные материалы и изделия
or RIGHT(obd,6)like '271%' #Материалы неметаллорудные (асбест. слюда. кварц. тальк. гравий)
or RIGHT(obd,6)like '273%' #Материалы стеновые. известь. гипс
or RIGHT(obd,6)like '274%' #Материалы отделочные и облицовочные. изделия из стекла
or RIGHT(obd,6)like '275%' #Материалы кровельные. тепло-. звуко-. гидроизоляционные
or RIGHT(obd,6)like '281%' #Провода обмоточные и эмальпровода
or RIGHT(obd,6)like '290%' #Уголь
or RIGHT(obd,6)like '291%' #Абразивные материалы. твердые сплавы
or RIGHT(obd,6)like '296%' #Разные материалы (клей конторский. мыло хоз. и другие)
#or RIGHT(obd,6)like '302%' #Прочие полуфабрикаты
#or RIGHT(obd,6)like '500%' #Проволока обыкновенного качества
#or RIGHT(obd,6)like '501%' #Проволока обыкновенного качества
#or RIGHT(obd,6)like '505%' #Проволока стальная разного назначения
or RIGHT(obd,6)like '523%' #Электроды разного назначения
or RIGHT(obd,6)like '528%' #!Канаты стальные
#or RIGHT(obd,6)like '585%' #Лента стальная холоднокатаная разного назначения
or RIGHT(obd,6)like '710%' #Малоценное оборудование
or RIGHT(obd,6)like '722%' #Изделия из пластмасс. щетины. волоса
#or RIGHT(obd,6)like '727%' #Изделия народного потребления
or RIGHT(obd,6)like '730%' #Чертежные принадлежности
or RIGHT(obd,6)like '731%' #Канцелярские и чертежные принадлежности
or RIGHT(obd,6)like '743%' #Головн.уборы. очки. рукавицы.нарукавн..перчатки.щитки.маски и др.
or RIGHT(obd,6)like '771%' #Тара металлическая
or RIGHT(obd,6)like '774%' #Тара бумажная. картонная. текстильная

or RIGHT(obd,6)like '50%' #проволока стальная/
or RIGHT(obd,6)like '51%' #проволока стальная?
) #изделия крепежные машиностроительные/
and LENGTH(obd)=15 and left(obd,9)='000000000';

#call market.update();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `UpdateFile` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `UpdateFile`(inBasePath text,FileInBase text,UserID int)
    COMMENT 'обновление информации в базе (замена файла)'
BEGIN
	#Routine body goes here...
update files a 
join administration.logins b on b.LogID=UserID set a.Updater=b.LogIn,a.DateOfUpdate=CURRENT_TIMESTAMP() 
where a.FileInBase=inBasePath and a.InBaseName=FileInBase;
#FRowData::SaveToBase(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `UpdateFileInfo` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `UpdateFileInfo`(idDet int,Name varchar(255),user int)
    COMMENT 'Обновление информации в троке данных файла'
BEGIN
	#Routine body goes here...
SELECT 
b.id,
b.razdSPID,
b.obd,
Trim(b.namd) as namd,
b1.Razdname,
a.InProjName as FileName,
a.FileInProj as FilePath,
if (g3.id is not null,g3.id,0)as icoID,
#инфо поля
a.DateOfCreate as DateOfCreate,
if (a.Creator is not null,a.Creator,'') as Creator,
a.DateOfUpdate as DateOfUpdate,
if (a.Updater is not null,a.Updater,'') as Updater,
#разрешения
if (g.IdGroup is null or (b.UserID!=-1 and b.UserID!=user)or f.arhive!=0,0,1)as Accept
FROM  
files a
join det_names b on a.iddet=b.id
join administration.sprazd b1 on b.razdSPID=b1.RazdID
join administration.conditions f on f.idsost=b.state
join administration.logins g1 on g1.logId=user
left join administration.gtucond g on g.IdCond=b.state and g.IdGroup=g1.levelacss
left join administration.files_and_types g3 on Locate(g3.FileType,`Name`)  
where a.idDet=idDet and a.InProjName=`Name`;
#FileRow::UpdateVal (void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `UpdateRowInfo` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `UpdateRowInfo`(IDp int,IDc int,user int)
    COMMENT 'Функция для обновления данных класса дерева спецификации'
BEGIN
	#Routine body goes here...
SELECT 
a.idparent,
c.obd as obu,
a.idchild,
b.obd,
trim(b.namd) as `name`,
b.format,
b.pp,
if (g3.napp is not null,g3.napp,'') as ppname,
a.kol,
a.ppp,
a.ei,
d.snameei as eiName,
a.pos,a.zona,a.prim,
b.razdSPID,
e.Razdname,
b.state,
f.`name` as CondName,
if (b.UserID is not null,b.UserID,-1)as UserID,#спецполя
if (g2.LogIn is not null,g2.LogIn,'')as User,#спецполя!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#инфо поля
b.CreateDate as DetCreated,
if (b.CreateUser is not null,b.CreateUser,'') as DetCreator,
b.UpdateDate as DetUpdated,
if (b.UpdateUser is not null,b.UpdateUser,'') as DetUpdater,
a.CreateDate as RowCreated,
if (a.CreateUser is not null,a.CreateUser,'') as RowCreator,
a.UpdateDate as RowUpdated,
if (a.UpdateUser is not null,a.UpdateUser,'') AS RowUpdater,
#разрешения
e.CanChild,
f.arhive,
if (g.IdGroup is null or (b.UserID!=-1 and b.UserID!=user),0,1)as Accept
FROM   `det_tree` a 
join det_names b on a.idchild=b.id
join det_names c on a.idparent=c.id 
join catalogs.dimensionality d on a.ei=d.kodei
join administration.sprazd e on  e.RazdID=b.razdSPID
join administration.conditions f on f.idsost=b.state
join administration.logins g1 on g1.logId=user
left join administration.logins g2 on g2.logId=b.UserID#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
join catalogs.proizv_prizn g3 on g3.pp=b.pp
left join administration.gtucond g on g.IdCond=b.state and g.IdGroup=g1.levelacss
where c.id=IDp and b.id=IDc;
#TreeRow::UpdateVal 		(void)
#SpRow::Load_data	(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `equipment`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `equipment` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `equipment`;

--
-- Dumping events for database 'equipment'
--

--
-- Dumping routines for database 'equipment'
--
/*!50003 DROP PROCEDURE IF EXISTS `convert_old_base` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `convert_old_base`()
    COMMENT 'получение списка цехов'
BEGIN
	#Routine body goes here...
insert into obor_list select obo,kobo,ksme,trim(nobo),chpu from temporary_tables.oborud_names group by obo;
insert into opr_names select kop,trim(nop) from temporary_tables.operations_names group by kop;
insert into podr_obor select distinct left(podr,2),RIGHT(podr,2),obo from temporary_tables.oborud_names;
insert into obor_operations select distinct a.obo,b.kop
from temporary_tables.oborud_names a 
join temporary_tables.`operations_names` b on if (left(b.obo,3)='000',b.obo=a.obo,left(b.obo,3)=left(a.obo,3));
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_ceh_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_ceh_list`(type int(11),OprKode char(2),oboid char(5))
    COMMENT 'получение списка цехов'
BEGIN
	#Routine body goes here...
case type 
 WHEN 0 then 
	BEGIN
		select distinct ceh 
		from podr_obor 
		order by ceh;
	END;
 WHEN 1 THEN
	BEGIN
		if oboid!='0'
			THEN
				BEGIN
				select distinct c.ceh 
				from opr_names a 
				join obor_operations b on b.operID=a.OprID and b.oboID=oboid
				join podr_obor c on c.OboID=b.oboID
				where a.OprID=OprKode
				group by c.ceh; 
				end;
			ELSE
				BEGIN
				select distinct c.ceh 
				from opr_names a 
				join obor_operations b on b.operID=a.OprID
				join podr_obor c on c.OboID=b.oboID
				where a.OprID=OprKode
				group by c.ceh; 
				END;
			end if;

	END;
end case;
#void __fastcall TTechWnd::operationsDblClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Obor_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_Obor_list`(type int(11),ceh char(2),utch char(2),OprID char(2))
    COMMENT 'получение списка цехов'
BEGIN
	
case type 
 WHEN 0 then 
	BEGIN
		select distinct concat(a.ceh,' | ',a.utch,' | ',a.oboID,' | ',b.`name`) as `name`
		from podr_obor a
		join obor_list b on b.oboID=a.oboID 
		join obor_operations c on c.oboID=a.OboID and c.operID=OprID
		order by a.ceh,a.utch,a.oboID;
	END;
 WHEN 1 THEN
	BEGIN
		select distinct concat(a.ceh,' | ',a.utch,' | ',a.oboID,' | ',b.`name`) as `name`
		from podr_obor a
		join obor_list b on b.oboID=a.oboID 
		join obor_operations c on c.oboID=a.OboID and c.operID=OprID
		where a.ceh=ceh and a.utch=utch
		order by a.ceh,a.utch,a.oboID;	
	END;
end case;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Opreations_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_Opreations_list`(type int(11),ceh char(2),utch char(2))
    COMMENT 'получение списка цехов'
BEGIN
	#Routine body goes here...
case type 
 WHEN 0 then 
	BEGIN
		select CONCAT(a.OprID,' ',a.`name`)as `value` 
		from opr_names a
		order by a.`name`;
	END;
 WHEN 1 THEN
	BEGIN
		select distinct CONCAT(a.OprID,' ',a.`name`)as `value` 
		from opr_names a 
		join obor_operations b on b.operID=a.OprID
		join podr_obor c on c.OboID=b.oboID
		where c.ceh=ceh and c.utch=utch
		order by a.`name`;
	END;
end case;
#void __fastcall TTechWnd::operationsDblClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_utch_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Get_utch_list`(type int(11),OprKode char(2),ceh char(2),oboid char(5))
    COMMENT 'получение списка цехов'
BEGIN
	#Routine body goes here...
case type 
 WHEN 0 then 
	BEGIN
		select distinct a.utch 
		from podr_obor a
		WHERE a.ceh=ceh 
		order by a.utch;
	END;
 WHEN 1 THEN
	BEGIN
		if oboid!='0'
			THEN
				BEGIN
				select distinct c.utch 
				from opr_names a 
				join obor_operations b on b.operID=a.OprID and b.oboID=oboid
				join podr_obor c on c.OboID=b.oboID
				where a.OprID=OprKode and c.ceh=ceh
				group by c.utch; 
				END;
			ELSE
				BEGIN
				select distinct c.utch 
				from opr_names a 
				join obor_operations b on b.operID=a.OprID
				join podr_obor c on c.OboID=b.oboID
				where a.OprID=OprKode and c.ceh=ceh
				group by c.utch; 
				END;
		end if;

	END;
end case;
#void __fastcall TTechWnd::operationsDblClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `instrum`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `instrum` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `instrum`;

--
-- Dumping events for database 'instrum'
--

--
-- Dumping routines for database 'instrum'
--

--
-- Current Database: `manufacture`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `manufacture` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `manufacture`;

--
-- Dumping events for database 'manufacture'
--

--
-- Dumping routines for database 'manufacture'
--
/*!50003 DROP PROCEDURE IF EXISTS `Del_Entrance` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Del_Entrance`(eid int,  list_no bigint unsigned, user int)
BEGIN
	#Routine body goes here...
# удалить вхождение поставить метку редактирования списка

#delete from prymary_entry where prymary_entry.List_no=list_no and prymary_entry.eid=eid;
call Reverse_Entries(eid);
delete from entries where eidc in (select a.eid from output a where a.eidp is null);
DROP TEMPORARY TABLE IF EXISTS output;
#void __fastcall TList_Editor::TreeItems_del_Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Del_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Del_list`(Order_no bigint unsigned)
BEGIN
	#Routine body goes here...
	delete from entries where entries.eidc in (select eid from prymary_entry where prymary_entry.List_no=list_no);
	delete from started_zak  where started_zak.`Order`=Order_no;
#TList_Editor::N12Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Find` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Find`(zapr text,param int, limit_str text)
BEGIN
	#Routine body goes here...
DROP TEMPORARY TABLE IF EXISTS f_tmp;
#подготовка запроса
CASE param#поиск по
	WHEN 0 THEN #Обозначению
		BEGIN 
			set @_sql=CONCAT("
					CREATE TEMPORARY TABLE IF NOT EXISTS f_tmp as
					SELECT a.eidc FROM `entries` a 
					join constructions.det_names b on a.idc=b.id and b.obd like '%",zapr,"%'");
		END;
	WHEN 1 THEN #Наименованию
		BEGIN
			set @_sql=CONCAT("
					CREATE TEMPORARY TABLE IF NOT EXISTS f_tmp as
					SELECT a.eidc FROM `entries` a 
					join constructions.det_names b on a.idc=b.id and b.namd like '%",zapr,"%'");
		END;
	WHEN 2 THEN #Заказу
		BEGIN
			set @_sql=CONCAT(" 
					select zakaz from started_zak where zakaz like '%",zapr,"%' ",limit_str,"
					");
		END;
	WHEN 3 THEN #Материалу
		BEGIN
			set @_sql=CONCAT("
					CREATE TEMPORARY TABLE IF NOT EXISTS f_tmp as
					SELECT DISTINCT
					a.eidc
					FROM `entries` a 
					join constructions.det_tree b on b.idparent=a.idc
					join constructions.det_names c on c.id=b.idchild and c.obd like '%",zapr,"%'union 
					SELECT DISTINCT
					a.eidc
					FROM `entries` a 
					join technologic.det_info b on b.id=a.idc
					join constructions.det_names c on c.id=b.obmid and c.obd like '%",zapr,"%';
					");
		END;
END CASE;

#получить список деталей удолетворяющих условию
prepare init from @_sql;
EXECUTE init;	

IF param!=2	THEN
	begin
		#получить корневой элемент
		DROP TEMPORARY TABLE IF EXISTS f1_tmp;
		CREATE TEMPORARY TABLE IF NOT EXISTS f1_tmp as
		select a.eidp,a.eidc from entries a 
			join f_tmp b on b.eidc=a.eidc;
		While EXISTS (select eidp from f1_tmp where eidp is not null) DO
			UPDATE f1_tmp a join entries b on a.eidp=b.eidc set a.eidc=b.eidc, a.eidp=b.eidp;
		end while;
		DROP TEMPORARY TABLE IF EXISTS f2_tmp;
		CREATE TEMPORARY TABLE IF NOT EXISTS f2_tmp as
			select DISTINCT eidc from f1_tmp;
		#сделать вывод данных по связве корневого и заказов
		set @_sql=CONCAT("
		select a.zakaz from started_zak a
			join prymary_entry b on a.`Order`=b.`Order`
			join f2_tmp c on c.eidc=b.eid group by a.zakaz ",limit_str,"
		");
		prepare init from @_sql;
		EXECUTE init;			
	end;
end if;

DROP TEMPORARY TABLE IF EXISTS f_tmp;
DROP TEMPORARY TABLE IF EXISTS f1_tmp;
DROP TEMPORARY TABLE IF EXISTS f2_tmp;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Entrance_lvl` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Entrance_lvl`(eid BIGINT UNSIGNED, Type int,val text)
BEGIN
	#Routine body goes here...
/*получает уровень развертки для построения древа*/
CASE Type
	WHEN 0 THEN
		BEGIN
			call reverse_entries(eid);
			set @id=0;
			CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.eid from output a where a.eidp is null;#получение id 
			DROP TEMPORARY TABLE if EXISTS tmp;

			call Get_Entries(@id);
			drop temporary TABLE if EXISTS prep_kol;
			CREATE TEMPORARY table if not EXISTS prep_kol as 
				select a.id,sum(a.tree_kol) kol from output a group by a.id;
			drop temporary TABLE if EXISTS output;

			select 
			a.idc 			id,
			a.idp 			idp,
			a.eidc 			eid,
			a.eidp 			eidp,
			a.sp_kol 	 	sp_kol,#b.kol
			a.tree_kol 	abs_kol,
			a1.kol			all_kol,
			c.namd 			`Name`,
			c.obd				Obd,
			c.razdSPID 	SpRazd,
			if (d.obd is not null,d.obd,'')							Obu,
			if (c1.Razdname is not null,c1.Razdname,'')	SpRazdName,
			if (e.snameei is not null,e.snameei,'') ei,
			0 Type,
			'' val,
			'1899-01-01' as create_date 
			from entries a
			join prep_kol a1 on a.idc=a1.id
			#join constructions.det_tree b on a.idc=b.idchild and a.idp=b.idparent
			join constructions.det_names c on c.id=a.idc
			left join administration.sprazd c1 on c1.RazdID=c.razdSPID
			left join constructions.det_names d on d.id=a.idp
			left join catalogs.dimensionality e on e.kodei=a.ei
			where a.eidp=eid
			ORDER BY c.razdSPID,c.obd;
			drop temporary TABLE if EXISTS prep_kol;
		END;
	WHEN 1 THEN
		BEGIN
			select 
			-1 	id,
			0 	idp,
			0 	eid,
			0 	eidp,
			0 	sp_kol,
			0	 	abs_kol,
			0		all_kol,
			'' 	`Name`,
			''	Obd,
			-1 	SpRazd,
			''	Obu,
			''	SpRazdName,
			'' 	ei, 

			2 			Type,
			a.part 	val,
			a.date as create_date 
			from started_zak a 
			where a.zakaz=val;
		END;
	WHEN 2 THEN
		BEGIN
			set @_sql=concat("
												select 
												a.idc 			id,
												if (a.idp is not null,a.idp,0)idp,
												a.eidc 			eid,
												if (a.eidp is not null,a.eidp,0)eidp,
												a.sp_kol 	 	sp_kol,#b.kol
												a.tree_kol 	abs_kol,
												a.tree_kol	all_kol,
												c.namd 			`Name`,
												c.obd				Obd,
												c.razdSPID 	SpRazd,
												if (d.obd is not null,d.obd,'')							Obu,
												if (c1.Razdname is not null,c1.Razdname,'')	SpRazdName,
												if (e.snameei is not null,e.snameei,'') ei,
												0 Type,
												'' val,
												'1899-01-01' as create_date 
												from entries a
												join prymary_entry a1 on a1.eid=a.eidc
												join started_zak 	a2 on a2.`order`=a1.`order`
												#join constructions.det_tree b on a.idc=b.idchild and a.idp=b.idparent
												join constructions.det_names c on c.id=a.idc
												left join administration.sprazd c1 on c1.RazdID=c.razdSPID
												left join constructions.det_names d on d.id=a.idp
												left join catalogs.dimensionality e on e.kodei=a.ei
												where ",val," 
												ORDER BY c.razdSPID,c.obd;
											");
			prepare init from @_sql;
			execute init;
		END;
END CASE;
#void __fastcall TMaterials_Need::TreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Entries` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Entries`(eid bigint unsigned)
BEGIN
	#Routine body goes here...
/*получение списка входящих*/
declare lvl int;
drop TEMPORARY table if EXISTS res;
drop TEMPORARY table if EXISTS t_res;
create TEMPORARY table if not EXISTS res(
	eidp  bigint unsigned ,
	eidc	bigint unsigned not NULL,
	id		int unsigned not NULL,
	idp		int unsigned,
	sp_kol		double not NULL,
	tree_kol	double not NULL,
	ei		varchar(3) not null,
	lvl int not null,
	key `eidc`(`eidc`),
	key `eidp`(`eidp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
CREATE TEMPORARY TABLE IF NOT EXISTS t_res as select * from res where 0;
#подготовка
insert into res 
	select a.eidp,a.eidc,a.idc,a.idp,a.sp_kol,a.tree_kol,a.ei,0 from entries a where a.eidc=eid;
set lvl=0;
#развертка
while EXISTS (select eidc from res where res.lvl=lvl)do
  TRUNCATE TABLE t_res; 
  insert into `t_res` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select 
				b.eidc as eidp,
				a.eidc as eidc,
				a.idc as id,
				b.id	as idp,
				a.sp_kol as sp_kol,
				a.tree_kol as tree_kol,
				a.ei as ei,
				lvl+1 as lvl
			from `entries` a 
			join `t_res` b on a.eidp=b.eidc and b.lvl=lvl
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if not EXISTS output as select * from res order by lvl;

drop TEMPORARY table if EXISTS res;
#Set_Active
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_list_Entries` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_list_Entries`(eids text)
BEGIN
	#Routine body goes here...
/*получение списка входящих по всему листу обработки*/
declare lvl int;
drop TEMPORARY table if EXISTS res;
drop TEMPORARY table if EXISTS t_res;
create TEMPORARY table if not EXISTS res(
	eidp  bigint unsigned ,
	eidc	bigint unsigned not NULL,
	id		int unsigned not NULL,
	idp		int unsigned,
	sp_kol		double not NULL,
	tree_kol	double not NULL,
	ei		varchar(3) not null,
	lvl int not null,
	key `eidc`(`eidc`),
	key `eidp`(`eidp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
CREATE TEMPORARY TABLE IF NOT EXISTS t_res as select * from res where 0;
#подготовка
set @_sql=CONCAT("
	insert into res 
		select a.eidp,a.eidc,a.idc,a.idp,a.sp_kol,a.tree_kol,a.ei,0 from entries a where a.eidc in (",eids,");
								");
prepare init from @_sql;
EXECUTE init;

set lvl=0;
#развертка
while EXISTS (select eidc from res where res.lvl=lvl)do
  TRUNCATE TABLE t_res; 
  insert into `t_res` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select 
				b.eidc as eidp,
				a.eidc as eidc,
				a.idc as id,
				b.id	as idp,
				a.sp_kol as sp_kol,
				a.tree_kol as tree_kol,
				a.ei as ei,
				lvl+1 as lvl
			from `entries` a 
			join `t_res` b on a.eidp=b.eidc and b.lvl=lvl
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if not EXISTS output as select * from res order by lvl;

drop TEMPORARY table if EXISTS res;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Material_Info` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Material_Info`(eid BIGINT UNSIGNED, Type int,val text)
BEGIN
	#Routine body goes here...
/*План действия
	#в зависимости от типа получить список начальных eid 
	#по eid получить развертки
	#из разверток собрать все идентификаторы и количества (сумма)
	дополнить идентификаторами материалов с расчитанным количеством
	в зависимости от раздела спецификации проставить группу вывода
	вуаля
*/
SET @eids='';
CASE Type
	WHEN 0 THEN
		BEGIN
			SET @eids=eid;
		END;
	WHEN 1 THEN
		BEGIN
		DROP TEMPORARY TABLE IF EXISTS gm_tmp;
		CREATE TEMPORARY TABLE IF NOT EXISTS gm_tmp as
		select @eids:=CONCAT(@eids,if(LENGTH(@eids)>0,", '","'"),b.eid,"'") from started_zak a 
				join prymary_entry b on a.`order`=b.`order` and a.zakaz=val;
		DROP TEMPORARY TABLE IF EXISTS gm_tmp;
		END;
	WHEN 2 THEN
		BEGIN
		set @_sql=CONCAT("
		CREATE TEMPORARY TABLE IF NOT EXISTS gm_tmp as
		select @eids:=CONCAT(@eids,if(LENGTH(@eids)>0,\", \'\",\"\'\"),b.eid,\"\'\") from started_zak a 
				join prymary_entry b on a.`order`=b.`order`
				where ",val,";
										");
		prepare init from @_sql;
		DROP TEMPORARY TABLE IF EXISTS gm_tmp;
		EXECUTE init;
		DROP TEMPORARY TABLE IF EXISTS gm_tmp;
		END;
END CASE;

if (@eids!='')
	THEN
		BEGIN
		call Get_list_Entries(@eids);
		DROP TEMPORARY TABLE IF EXISTS gm_tmp;
		CREATE TEMPORARY TABLE IF NOT EXISTS gm_tmp
		(
		id 	int unsigned,
		kol double,
		ei  varchar(3),
		key id (id)
		)ENGINE=MYISAM;
		INSERT into gm_tmp (id,kol,ei)
			select a.id,sum(a.tree_kol) kol,a.ei from output a group by a.id;
		INSERT into gm_tmp (id,kol,ei)
			select c.obmid,round(sum(a.tree_kol*c.nrm),4),c.ei from output a
			join constructions.det_names b on b.id=a.id and b.razdSPID in (0,2,3,4)
			JOIN technologic.det_info c on c.id=a.id
			JOIN constructions.det_names d on d.id=c.obmid and d.obd!='000000000000000'
			group by c.obmid;
		#
		Set @tmp_sklad=0;
		select 
		b.id		id,
		if(b.razdSPID 			in (0,2,3,4),	0,
			if(b.razdSPID 		in (5,6),			1,
				if(b.razdSPID 	in (7),				2,
					if(b.razdSPID in (9),				3,-1)))) Type,
		a.kol Need_kol,
		@tmp_sklad Sklad_kol,
		if (a.kol>@tmp_sklad,a.kol-@tmp_sklad,0)	Lacking_kol,
		if (a.kol>@tmp_sklad,if (a.kol-@tmp_sklad!=0,0,1),2)Lacking_priority,				
		b.namd	`Name`,
		b.obd		Obd,
		if (c.snameei is not null,c.snameei,'') ei
		FROM gm_tmp a
		join constructions.det_names b on a.id=b.id
		left join catalogs.dimensionality c on c.kodei=a.ei
		order by Lacking_priority ,b.razdspid,b.obd; 
		END;
end if;
#44,0,''
DROP TEMPORARY TABLE IF EXISTS output;
DROP TEMPORARY TABLE IF EXISTS gm_tmp;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_node` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_node`(eid bigint unsigned)
BEGIN
	#Routine body goes here...
/*получение данных об узлах первого уровня и обновление данных в узлах*/

call reverse_entries(eid);
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.eid from output a where a.eidp is null;#получение id 
DROP TEMPORARY TABLE if EXISTS tmp;

call Get_Entries(@id);
drop temporary TABLE if EXISTS prep_kol;
CREATE TEMPORARY table if not EXISTS prep_kol as 
	select a.id,sum(a.tree_kol) kol from output a group by a.id;
drop temporary TABLE if EXISTS output;

select 
if (a.idp is not null,a.idp,0)idp,
a.idc,
if (c.obd is not null,c.obd,'') obu,
c1.obd obd,
c1.namd `Name`,
c1.razdSPID razdSPID,
if (c2.Razdname is not null,c2.Razdname,'')	SpRazdName,
#if (b.kol is not null,b.kol,0) sp_kol,
a.sp_kol   	sp_kol,
a.tree_kol 	abs_kol,
a1.kol 			all_kol,
a.eidc,
if (a.eidp is not null,a.eidp,0)eidp,
if (d.snameei is not null,d.snameei,0) ei, 
'1899-01-01' as create_date 
from entries a 
join prep_kol a1 on a1.id=a.idc
#left join constructions.det_tree b on a.idp=b.idparent and a.idc=b.idchild
left join constructions.det_names c on a.idp=c.id
join constructions.det_names c1 on a.idc=c1.id
left join administration.sprazd c2 on c2.RazdID=c1.razdSPID
left join catalogs.dimensionality d on d.kodei=a.ei
where a.eidc=eid;

drop temporary TABLE if EXISTS prep_kol;
#TMaterials_Need::Tree_data::Update()
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Order_Entries` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Order_Entries`(Order_no bigint unsigned)
BEGIN
	#Routine body goes here...
/*получение списка входящих по всему листу обработки*/
declare lvl int;
drop TEMPORARY table if EXISTS res;
drop TEMPORARY table if EXISTS t_res;
create TEMPORARY table if not EXISTS res(
	eidp  bigint unsigned ,
	eidc	bigint unsigned not NULL,
	id		int unsigned not NULL,
	idp		int unsigned,
	sp_kol		double not NULL,
	tree_kol	double not NULL,
	ei		varchar(3) not null,
	lvl int not null,
	key `eidc`(`eidc`),
	key `eidp`(`eidp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
CREATE TEMPORARY TABLE IF NOT EXISTS t_res as select * from res where 0;
#подготовка
insert into res 
	select a.eidp,a.eidc,a.idc,a.idp,a.sp_kol,a.tree_kol,a.ei,0 from entries a join prymary_entry b on a.eidc=b.eid where b.`Order`=Order_no;
set lvl=0;
#развертка
while EXISTS (select eidc from res where res.lvl=lvl)do
  TRUNCATE TABLE t_res; 
  insert into `t_res` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select 
				b.eidc as eidp,
				a.eidc as eidc,
				a.idc as id,
				b.id	as idp,
				a.sp_kol as sp_kol,
				a.tree_kol as tree_kol,
				a.ei as ei,
				lvl+1 as lvl
			from `entries` a 
			join `t_res` b on a.eidp=b.eidc and b.lvl=lvl
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if not EXISTS output as select * from res order by lvl;

drop TEMPORARY table if EXISTS res;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Reverse_Entries` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Reverse_Entries`(eid bigint unsigned)
BEGIN
	#Routine body goes here...
declare lvl int;
set lvl=0;
DROP TEMPORARY TABLE IF EXISTS res;
DROP TEMPORARY TABLE IF EXISTS t_res;

CREATE TEMPORARY TABLE IF NOT EXISTS res
(
eid BIGINT UNSIGNED,
eidp BIGINT UNSIGNED,
lvl int,
key `eid`(`eid`),
key `eidp`(`eidp`)
)ENGINE=MYISAM;
CREATE TEMPORARY TABLE IF NOT EXISTS t_res as select * from res where 0;
insert into res 
	SELECT eidc,eidp,lvl from entries a where a.eidc=eid;
WHILE EXISTS (select eid from res where res.lvl=lvl) do
	TRUNCATE table t_res;
	insert into `t_res` select * from res where res.lvl=lvl;
	insert into res (eid,eidp,lvl)
		select b.eidp,a.eidp,lvl+1 
						from entries a 
						join t_res b on a.eidc=b.eidp;
	set lvl=lvl+1;
end WHILE;
DROP TEMPORARY TABLE IF EXISTS output;
CREATE TEMPORARY TABLE IF NOT EXISTS output as select * from res a ORDER BY a.lvl;
DROP TEMPORARY TABLE IF EXISTS res;
DROP TEMPORARY TABLE IF EXISTS t_res;
#Del Entrace
#Get_Entrance_lvl
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `market`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `market` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `market`;

--
-- Dumping events for database 'market'
--

--
-- Dumping routines for database 'market'
--
/*!50003 DROP PROCEDURE IF EXISTS `contractor_del` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `contractor_del`(id int(20) unsigned)
    COMMENT 'удаление контрагентов'
BEGIN
	#Routine body goes here...
#void __fastcall TContragents::DELClick(TObject *Sender)

IF not exists (select * from market.contractors a where a.id=id)
	then
		begin
			select "Неизвестный идентификатор" as msg;
		end;
	ELSE
		BEGIN
			IF not exists (select * from market.contractors a where a.id=id and id1c='')
				then
				begin
					select "Нельзя удалить контрагента 1С" as msg;
				end;
				else 
				BEGIN
					select "функция не работает" as msg;
				end;
			end if;
		end;
end if;
#void __fastcall TContragents::DELClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `delZakaz` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`ffroot`@`%`*/ /*!50003 PROCEDURE `delZakaz`(zakaz_id int(11))
BEGIN
	#Routine body goes here...
	delete from Orders where Orders.zakaz_id = zakaz_id ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `delZakazContent` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`ffroot`@`%`*/ /*!50003 PROCEDURE `delZakazContent`(zakaz_id int, det_id int)
BEGIN
	#Routine body goes here...
	delete from zakaz where zakaz.zakaz_id=zakaz_id and zakaz.id = det_id ; 

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `dog_del` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `dog_del`(id int(20) unsigned)
    COMMENT 'удаление контрагентов'
BEGIN
	#Routine body goes here...
#void __fastcall TContragents::DELClick(TObject *Sender)

IF not exists (select * from market.dog_list a where a.id=id)
	then
		begin
			select "Неизвестный идентификатор" as msg;
		end;
	ELSE
		BEGIN
			select "функция не работает" as msg;
		end;
end if;
#void __fastcall TAgreements::DelClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `getZakazContent` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `getZakazContent`(zakaz_id int)
BEGIN
	#Routine body goes here...
		SELECT
		b.kol,c.obd,c.namd,c.id,a.zakaz_id
		from Orders a 
		join zakaz b on a.zakaz_id = b.zakaz_id
		join constructions.det_names c on b.id = c.id
		where a.zakaz_id = zakaz_id;	
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `getZakazes` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `getZakazes`(str varchar(255),  type tinyint(1), pg_num int, pg_size int)
BEGIN
	#Routine body goes here...
set @sq="";
	if (type = 0)
		THEN 
			BEGIN
				set @sq=CONCAT("
				SELECT
				a.zakaz,a.description,a.zakaz_id
				from Orders a 
				where a.zakaz like '%",str,"%' 
				LIMIT ",pg_num,",", pg_size,";");
			END;
	end if;

	if (type = 1)
		THEN 
			BEGIN
				set @sq=CONCAT("
				SELECT
				a.zakaz,a.description,a.zakaz_id
				from Orders a 
				join zakaz b on a.zakaz_id = b.zakaz_id
				join constructions.det_names c on b.id = c.id
				where c.obd like '%",str,"%' 
				group by a.zakaz_id
				LIMIT ",pg_num,",", pg_size,";");
			END;
	end if;		
	if (@sq!="")
	then 
		BEGIN
			prepare init from @sq;
			EXECUTE init;
		END;
	end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_dog_num` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_dog_num`()
BEGIN
	#Routine body goes here...
select CONCAT('15/',YEAR(CURDATE()),'/',max(indication2)+1) as num,max(indication2)+1 as num_ch from dog_list where YEAR(DogDate)=YEAR(CURDATE());
#void __fastcall TAgreements::CB1Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_isp_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_isp_list`(p_id tinyint(4))
    COMMENT 'получение списка исполнителей'
BEGIN
	#Routine body goes here...
select a.LogID,a.LogIn from administration.logins a 
join market.market_users b on a.LogID=b.Logid
where b.podrID=p_id order by a.LogIn;
#void __fastcall TAgreements::podr_listClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_isp_list_u` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_isp_list_u`(user int(11))
    COMMENT 'получение списка исполнителей'
BEGIN
	#Routine body goes here...
select a.LogID,a.LogIn from administration.logins a 
join market.market_users b on a.LogID=b.Logid
join market.market_users c on b.podrID=c.podrID
where c.Logid=user GROUP BY a.Logid order by a.LogIn;
#__fastcall TSel_params::TSel_params(TComponent* Owner,const int &_LUser,cSQL *db)
#void __fastcall TAgreements::podr_listClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_leaders_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_leaders_list`(user int (11))
    COMMENT 'получение списка начальаства'
BEGIN

declare lvl int;
	#Routine body goes here...
drop temporary TABLE if EXISTS rez;
drop temporary TABLE if EXISTS rez_copy;
create TEMPORARY table if not EXISTS rez
(
idp int(11) DEFAULT null,
idc int(11) not null,
lvl int (11) DEFAULT 0,
key idp(idp),
key idc(idc)
);
create TEMPORARY table if not EXISTS rez_copy
(
idp int(11) DEFAULT null,
idc int(11) not null,
lvl int (11) DEFAULT 0,
key idp(idp),
key idc(idc)
);
set lvl=0;
insert into rez 
	SELECT a.logid,a.subordinate,lvl from subordinates a where a.subordinate=user;
while EXISTS (select * from rez a where a.lvl=lvl) do
	BEGIN
	delete from rez_copy;
	INSERT into rez_copy select * from rez;
	insert into rez 
			select a.logid,a.subordinate,lvl+1 
			from subordinates a 
			join rez_copy b on a.subordinate=b.idp and b.lvl=lvl;
	set lvl=lvl+1;
	END;
end WHILE;
select a.LogIn,a.LogID
from administration.logins a 
join rez b on a.LogID=b.idp 
GROUP BY b.idp
ORDER BY b.lvl DESC,a.login,a.logid;
#void __fastcall TAgreements::isp_listClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_leaders_list_f` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_leaders_list_f`()
    COMMENT 'получение полного списка начальаства'
BEGIN
select a.LogIn,a.LogID
from administration.logins a 
join subordinates b on a.LogID=b.logid 
GROUP BY b.logid
ORDER BY a.login,a.logid;
#void __fastcall TAgreements::isp_listClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_market_productions` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_market_productions`(podrids text,where_text text,order_text text,lim_str int(11),lim_count int(11))
BEGIN
	#Routine body goes here...
/*
функция для получения данных для модуля продукция ппо
*/
drop TEMPORARY TABLE if EXISTS stage1;
drop TEMPORARY TABLE if EXISTS stage2;
drop TEMPORARY TABLE if EXISTS stage3;
drop TEMPORARY TABLE if EXISTS stage4;
drop TEMPORARY TABLE if EXISTS stage5;
create TEMPORARY TABLE if not EXISTS stage1
(																										#---------пользовательские данные------------------------
ca_name 		VARCHAR(50) not null default '', 				#название  контарента договора (покупатель)
dog_type 		VARCHAR(1) not NULL,										#тип документа (д/п/к)
dog_number 	VARCHAR(1024) not null DEFAULT '',			#номер документа
dog_Date 		DATE not null,													#дата оформления 
cancel			TINYINT(1) unsigned DEFAULT 0,					#метка отмены спецификции
cancel_Date DATE,																		#дата отмены спецификации
cancel_why	VARCHAR(512) not null,									#причина отмены 
sp_num			int(11),																#номер спецификации (dcnhtxf.ncz 0 и -1 потому не ансигнутый)
sp_Date			DATE,																		#дата оформления спецфикации
sp_Sign			DATE,																		#дата подписи спецификации
sp_valute		varchar(5)  not null,										#валюта спецификации
sp_prim			LONGTEXT NOT NULL,											#примечание к спецификации
gr_name 		VARCHAR(50) not null default '', 				#название  контарента спецификации (грузополучатель)
pl_name 		VARCHAR(50) not null default '', 				#название  контарента спецификации (плательщик)
lz_name 		VARCHAR(50) not null default '', 				#название  контарента спецификации (лизинг получатель)
																										#---------технические данные------------------------------
dog_id			bigint(20) unsigned not null DEFAULT 0,	#идентификатор документа
sp_id				bigint(20) unsigned not null DEFAULT 0,	#идентификатор спецификации
ca_id 			bigint(20) unsigned not null DEFAULT 0,	#идентификатор контарента договора (покупатель)
gr_id 			bigint(20) unsigned not null DEFAULT 0,	#идентификатор контарента спецификации (грузополучатель)
pl_id 			bigint(20) unsigned not null DEFAULT 0,	#идентификатор контарента спецификации (плательщик)
lz_id 			bigint(20) unsigned not null DEFAULT 0,	#идентификатор контарента спецификации (лизинг получатель)
nds					tinyint	unsigned not null DEFAULT 0, 		#ставка ндс спецификации
key sp_id(sp_id)
)ENGINE=MYISAM;
#этап 1 отбор заказов по WHERE
set @sq=CONCAT('
insert into stage1 (ca_name,dog_type,dog_number,dog_Date,cancel,cancel_Date,cancel_why,sp_num,sp_Date,sp_Sign,sp_valute,sp_prim,gr_name,pl_name,lz_name,
										dog_id,sp_id,ca_id,gr_id,pl_id,lz_id,nds)
select 
if (c.sname is not null,c.sname,"") ca_name,#ca_name
a.type dog_type,#dog_type
trim(concat(a.indication1," ",if (a.indication3!=""or a.indication2!=0,
																if(a.indication3="",
																	CONCAT("15/",YEAR(a.DogDate),"/",a.indication2),
																	CONCAT(a.indication2,"-",a.indication3)),
															"")," ",a.indication4)) dog_number,#dog_number
a.DogDate dog_Date,#dog_Date
if (b.cancelDate is not null,1,0) as cansel,#cancel
b.cancelDate cancel_Date,#cancel_Date
if (b.cancelreason is not null,b.cancelreason,"") cancel_why,#cancel_why
b.spnum sp_num,#sp_num
b.CreateDate sp_Date,#sp_Date
b.Signdate sp_Sign,#sp_Sign
e.name sp_valute,#sp_valute
if (b.prim is not null,b.prim,"") sp_prim,#sp_prim
if (c1.sname is not null,c1.sname,"") gr_name,#gr_name
if (c2.sname is not null,c2.sname,"") pl_name,#pl_name
if (c3.sname is not null,c3.sname,"") lz_name,#lz_name
a.id,#dog_id
b.id,#sp_id
c.id,#ca_id
if (c1.id is not null,c1.id,0),#gr_id
if (c2.id is not null,c2.id,0),#pl_id
if (c3.id is not null,c3.id,0),#lz_id
b.nds #nds
FROM dog_list a																	#договора и контрагент
join specifications b on a.id=b.iddog						#спецификации и получатели/плательщики
join contractors c on a.contractor_id=c.id			#вход для идентификации контрагента
left join contractors c1 on b.gruz_ca_id=c1.id	#вход для идентификации контрагента
left join contractors c2 on b.plat_ca_id=c2.id	#вход для идентификации контрагента
left join contractors c3 on b.liz_ca_id=c3.id		#вход для идентификации контрагента
left join spcontent d on b.id=d.id_spec					#для поиска по номеру заказа 
left join Valute_list e on e.id=b.valute				#для подключения валюты
where a.podrid in (',podrids,')
');
if (where_text!='') #цепляем условия поиска
	THEN
	BEGIN
	set @sq=CONCAT(@sq,' ',where_text);
	end;
end if;
set @sq=CONCAT(@sq,' group by b.id');#включение группировки т.к. список заказов сейчас не нужен
if (order_text!='') # цепляем параметры сортировки
	THEN
	BEGIN
	set @sq=CONCAT(@sq,' ',order_text);
	end;
end if;
set @sq:=CONCAT(@sq,' limit ',lim_str,', ',lim_count); #лимиты отображения данных
prepare init from @sq;
EXECUTE init;

#этап 2 подсчеты суммы спецификации
create TEMPORARY TABLE if not EXISTS stage2
(
sp_id				bigint(20) unsigned not null DEFAULT 0,
sp_sum			double not null DEFAULT 0, #сумма спецификации
sp_sum_nds 	double not null DEFAULT 0, #сумма сп с ндс
key sp_id(sp_id)
)ENGINE=MYISAM;
insert into stage2
select 
a.sp_id,
round(sum(b.price*b.kol),2),
round(sum(b.price*b.kol)*(1+a.nds/100),2)
from stage1 a
join spcontent b on a.sp_id=b.id_spec group by a.sp_id;

#этап 3 подсчеты выпусков
create TEMPORARY TABLE if not EXISTS stage3
(
sp_id					bigint(20) unsigned not null DEFAULT 0,
out_sum				double not null DEFAULT 0, #сумма выпуска
out_sum_nds		double not null DEFAULT 0, #сумма выпуска с ндс 
key sp_id(sp_id)
);
insert into stage3
select 
a.sp_id,
round(sum(b.price*c.kol),2),
round(sum(b.price*c.kol)*(1+a.nds/100),2)
from stage1 a
join spcontent b on a.sp_id=b.id_spec 
join production c on c.id_content=b.id
group by a.sp_id;

#этап 4 подсчеты отгрузок
create TEMPORARY TABLE if not EXISTS stage4
(
sp_id					bigint(20) unsigned not null DEFAULT 0,
ot_sum_nds		double not null DEFAULT 0, #сумма с ндс
ot_sum_nds_v 	double not null DEFAULT 0, #сумма с ндс в валюте
key sp_id(sp_id)
);
insert into stage4
SELECT
a.sp_id,
ROUND(sum(c.kol*b.price*(1+c.nds/100)),2),
round(sum(if(snrub is not null,snrub,0)),2)
FROM stage1 a
join spcontent b on a.sp_id=b.id_spec
join shipment c on c.id_content=b.id
group by a.sp_id;

#этап 5 подсчеты оплат
create TEMPORARY TABLE if not EXISTS stage5
(
sp_id					bigint(20) unsigned not null DEFAULT 0,
opl_sum				double not null DEFAULT 0, #сумма оплат по спецификации
key sp_id(sp_id)
);
insert into stage5 
SELECT
a.sp_id,
round(sum(c.sum),2)
FROM stage1 a
join payment c on c.id_spec=a.sp_id
group by a.sp_id;

#этап 6 складывание информации
select 
a.ca_name,				#название  контарента договора (покупатель)
a.dog_type,				#тип документа (д/п/к)
a.dog_number,			#номер документа
a.dog_Date,				#дата оформления 
a.cancel,					#метка отмены спецификции
a.cancel_Date,		#дата отмены спецификации
a.cancel_why,			#причина отмены 
a.sp_num,					#номер спецификации (dcnhtxf.ncz 0 и -1 потому не ансигнутый)
a.sp_Date,				#дата оформления спецфикации
a.sp_Sign,				#дата подписи спецфикации
a.sp_valute,			#валюта спецификации
a.sp_prim,				#примечание спецификации
a.gr_name, 				#название  контарента спецификации (грузополучатель)
a.pl_name,				#название  контарента спецификации (плательщик)
a.lz_name,				#название  контарента спецификации (лизинг получатель)
									#---------технические данные------------------------------
a.dog_id,					#идентификатор документа
a.sp_id,					#идентификатор спецификации
a.ca_id,					#идентификатор контарента договора (покупатель)
a.gr_id,					#идентификатор контарента спецификации (грузополучатель)
a.pl_id,					#идентификатор контарента спецификации (плательщик)
a.lz_id,					#идентификатор контарента спецификации (лизинг получатель)
a.nds,						#ставка ндс спецификации

b.sp_sum, 				#сумма спецификации
b.sp_sum_nds, 		#сумма сп с ндс

c.out_sum, 				#сумма выпуска
c.out_sum_nds, 		#сумма выпуска с ндс 

d.ot_sum_nds, 		#сумма отгрузок с ндс
d.ot_sum_nds_v, 	#сумма отгрузок с ндс в валюте

e.opl_sum 				#сумма оплат по спецификации
from 
stage1 a 
left join stage2 b on a.sp_id=b.sp_id
left join stage3 c on a.sp_id=c.sp_id
left join stage4 d on a.sp_id=d.sp_id
left join stage5 e on a.sp_id=e.sp_id;

drop TEMPORARY TABLE if EXISTS stage1;
drop TEMPORARY TABLE if EXISTS stage2;
drop TEMPORARY TABLE if EXISTS stage3;
drop TEMPORARY TABLE if EXISTS stage4;
drop TEMPORARY TABLE if EXISTS stage5;
#void Tprod::Find(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_podr_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_podr_list`(user int(11))
BEGIN
	#Routine body goes here...
#нач-во
declare lvl int;
	#Routine body goes here...
drop temporary TABLE if EXISTS rez;
drop temporary TABLE if EXISTS rez_copy;
create TEMPORARY table if not EXISTS rez
(
idp int(11) DEFAULT null,
idc int(11) not null,
lvl int (11) DEFAULT 0,
key idp(idp),
key idc(idc)
);
create TEMPORARY table if not EXISTS rez_copy
(
idp int(11) DEFAULT null,
idc int(11) not null,
lvl int (11) DEFAULT 0,
key idp(idp),
key idc(idc)
);
set lvl=0;
insert into rez 
	SELECT a.logid,a.subordinate,lvl from subordinates a where a.logid=user;
while EXISTS (select * from rez a where a.lvl=lvl) do
	BEGIN
	delete from rez_copy;
	INSERT into rez_copy select * from rez;
	insert into rez 
			select a.logid,a.subordinate,lvl+1 
			from subordinates a 
			join rez_copy b on a.logid=b.idc and b.lvl=lvl;
	set lvl=lvl+1;
	END;
end WHILE;

select a.podrid as id,d.fname as `name`
from market_users a
join rez b on a.LogID=b.idc 
join podr_list d on d.podrID=a.podrID
union 
select a.podrid as id,d.fname  as `name` 
from market_users a
join podr_list d on d.podrID=a.podrID
where Logid=user;
#void 			TAgreements::init (void)
#void Tprod::init(void)
#__fastcall TSel_params::TSel_params(TComponent* Owner,const int &_LUser,cSQL *db)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_sp_content` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_sp_content`(sp_id bigint(20) unsigned,lim_str int(11),lim_count int(11))
BEGIN
	#Routine body goes here...
drop TEMPORARY TABLE if EXISTS stage1;
drop TEMPORARY TABLE if EXISTS stage2;
drop TEMPORARY TABLE if EXISTS stage3;
drop TEMPORARY TABLE if EXISTS stage4;
drop TEMPORARY TABLE if EXISTS stage5;
# стадия 1 сбор общих сведений
create TEMPORARY TABLE if not EXISTS stage1
(																										#---------пользовательские данные------------------------
zak_no 			VARCHAR(6) not null default '', 				#номер заказа
name 				varchar(255) not NULL,									#название заказа
obi 				varchar(100) not null DEFAULT '',				#обозначение заказа
obivin 			varchar(15)	not null DEFAULT '',				#обозначение заказа формат асу 
supply			char(5) not null DEFAULT '',						#срок поставки
z_kol 			int(11)  not null,							#количество заказанных
price				double NOT NULL,												#цена одной штуки
prim				longtext NOT NULL,											#примечание к заказу
prime_cost	double not null default 0, 						#себестоимость
pc_date			DATE,																		#дата расчета себестоимости
																										#---------технические данные------------------------------
id_content	bigint(20) unsigned not null DEFAULT 0,	#идентификатор заказа
sp_id				bigint(20) unsigned not null DEFAULT 0,	#идентификатор спецификации
nds					tinyint	unsigned not null DEFAULT 0, 		#ставка ндс спецификации
																										#----------прочие данные для работы-----------------------
zkom 							tinyint(4) NOT NULL DEFAULT '0', 	# 'признак состава zkom'
pos 							smallint(6) unsigned NOT NULL, 		# 'позиция в спецификации договора zpoz'
ei_id 						char(3) NOT NULL, 								# 'zgrs ед изм 0=401 1=419 штуки и комплекты'
razd 							smallint(5) unsigned NOT NULL, 		# 'раздел по которому определяется начало номера заказа razd'
calc_id 					bigint(20) unsigned DEFAULT NULL, # 'идентификатор калькуляции заказа nklk'
demand_id 				bigint(20) DEFAULT NULL, 					# 'идентификатор заявки nzav'
ppo_vz 						smallint(6) DEFAULT NULL,					# 'вид заготовки zvid'
ppo_resurs 				double NOT NULL DEFAULT '0', 			# 'количество необходимых ресурсов zves (кг или нормочасы)'
ppo_price_resurs 	double NOT NULL DEFAULT '0', 			# 'цена еденицы ресурса zckg (1 кг и 1 н/ч соответственно)'
ppo_cex 					char(2) DEFAULT NULL, 						# 'цех выпускающий заказ zceu'
ppf_r 						varchar(6) NOT NULL DEFAULT '0', 	# 'радиус пресформы zrad'
ppf_size 					varchar(25) NOT NULL DEFAULT '', 	# 'размер пресформы zraz'
ppf_vid 					tinyint(4) unsigned DEFAULT NULL, # 'вид продукции zvid'
ppf_type_pf 			tinyint(4) unsigned DEFAULT NULL, # 'тип пресформы zpvd'
ppf_isp 					varchar(2) NOT NULL DEFAULT '', 	# 'исполнение zisp'
ppf_model 				varchar(20) NOT NULL DEFAULT '', 	# 'модель формы znos'
ppf_ves 					double NOT NULL DEFAULT '0', 			# 'zves'

key id_content(id_content)
)ENGINE=MYISAM;

set @sq=CONCAT("
insert into stage1
select 
a.zakaz,
a.`name`,
a.obi,
a.obivin,
a.per_suppl,
a.kol,
a.price,
a.prim,
a.prime_cost,
a.PC_Get_Date,
a.id,
b.id,
b.nds,
a.zkom,
a.pos,
a.ei_id,
a.razd,
a.calc_id,
a.demand_id,
a.ppo_vz,
a.ppo_resurs,
a.ppo_price_resurs,
a.ppo_cex,
a.ppf_r,
a.ppf_size,
a.ppf_vid,
a.ppf_type_pf,
a.ppf_isp,
a.ppf_model,
a.ppf_ves
from spcontent a 
	join specifications b on a.id_spec=b.id and b.id=",sp_id,"
	limit ",lim_str,", ",lim_count,"
");
prepare init from @sq;
EXECUTE init;

#стадия 2 подключение данных по выпускам
create TEMPORARY TABLE if not EXISTS stage2
(
id_content					bigint(20) unsigned not null DEFAULT 0,
ex_kol							int(11)  not null DEFAULT 0, #количество выпущенных
key id_content(id_content)
);
insert into stage2
select 
a.id_content,
sum(b.kol)
from stage1 a
join production b on b.id_content=a.id_content
group by a.id_content;

#стадия 3 информация отгрузки
create TEMPORARY TABLE if not EXISTS stage3
(
id_content					bigint(20) unsigned not null DEFAULT 0,
ship_kol						int(11) not null DEFAULT 0, #количество отгруженных
ship_sum						double not null default 0,#сумма отгрузок
ship_nds						double not null default 0,
key id_content(id_content)
);
insert into stage3
select 
a.id_content,
sum(b.kol),
round(sum(round(b.kol*a.price*(1+b.nds/100),2)),2),
b.nds
from stage1 a
join shipment b on b.id_content=a.id_content
group by a.id_content;

#стадия 4 запуски
create TEMPORARY TABLE if not EXISTS stage4
(
id_content					bigint(20) unsigned not null DEFAULT 0,
s_kol								int(11)  not null DEFAULT 0, #количество запущенных
key id_content(id_content)
);
insert into stage4
select 
a.id_content,
sum(b.kol)
from stage1 a
join plan_zap b on b.id_content=a.id_content
group by a.id_content;

#стадия 5 компиляция и выдача данных

SELECT 
																	#---------пользовательские данные------------------------
a.zak_no, 												#0#номер заказа
a.name,														#1#название заказа
a.obi,														#2#обозначение заказа
a.obivin,													#3#обозначение заказа формат асу 
a.supply,													#4#срок поставки
																	#количества
a.z_kol,													#5#количество заказанных
b3.s_kol, 												#10#количество запущенных
b1.ex_kol, 												#11#количество выпущенных
b2.ship_kol, 											#12#количество отгруженных
																	#стоимости
a.price,													#6#цена одной штуки
a.price*a.z_kol summ,							#7#сумма (по спецификации)
round(round((a.z_kol-b2.ship_kol)
*a.price*(1+b2.ship_nds/100),2)
+b2.ship_sum,2) summ_nds,					#8#сумма с ндс и учетом отгрузок
trim(a.prim) prim,								#9#примечание к заказу
a.prime_cost, 										#13#себестоимость
a.pc_date,												#14#дата расчета себестоимости
																	#15#номер строки в источнике данных
																	#---------технические данные------------------------------
a.id_content,											#16#идентификатор заказа
a.sp_id,													#17#идентификатор спецификации
a.nds, 														#18#ставка ндс спецификации
b2.ship_nds,											#19#ставка ндс отгрузок
																	#----------прочие данные для работы-----------------------
a.zkom, 													#20# 'признак состава zkom'
a.pos, 														#21# 'позиция в спецификации договора zpoz'
a.ei_id, 													#22# 'zgrs ед изм 0=401 1=419 штуки и комплекты'
a.razd, 													#23# 'раздел по которому определяется начало номера заказа razd'
a.calc_id, 												#24# 'идентификатор калькуляции заказа nklk'
a.demand_id, 											#25# 'идентификатор заявки nzav'
a.ppo_vz, 												#26# 'вид заготовки zvid'
a.ppo_resurs,											#27# 'количество необходимых ресурсов zves (кг или нормочасы)'
a.ppo_price_resurs, 							#28# 'цена еденицы ресурса zckg (1 кг и 1 н/ч соответственно)'
a.ppo_cex, 												#29# 'цех выпускающий заказ zceu'
a.ppf_r, 													#30# 'радиус пресформы zrad'
a.ppf_size, 											#31# 'размер пресформы zraz'
a.ppf_vid, 												#32# 'вид продукции zvid'
a.ppf_type_pf, 										#33# 'тип пресформы zpvd'
a.ppf_isp, 												#34# 'исполнение zisp'
a.ppf_model, 											#35# 'модель формы znos'
a.ppf_ves 												#36# 'zves'
from stage1 a
  left join stage2 b1 on b1.id_content=a.id_content 
	left join stage3 b2 on b2.id_content=a.id_content 
	left join stage4 b3 on b3.id_content=a.id_content;
 
drop TEMPORARY TABLE if EXISTS stage1;
drop TEMPORARY TABLE if EXISTS stage2;
drop TEMPORARY TABLE if EXISTS stage3;
drop TEMPORARY TABLE if EXISTS stage4;
drop TEMPORARY TABLE if EXISTS stage5;
#void Tprod::sp_Find(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_valute_curs` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_valute_curs`(id tinyint(4))
BEGIN
	#Routine body goes here...
select cours 
	from valute_curs a 
	where a.id=id and a.date in	(
															select max(a1.date) 
																from valute_curs a1 
																where a1.id=id
															);
#void __fastcall Tprod::valuteChange(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `refresh_contractors` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `refresh_contractors`()
    COMMENT 'чистка после обновления контрагентов'
BEGIN
	#Routine body goes here...
while exists (select a.id from market.contractors a where a.address_yur like '%,,%' or a.address_fiz like '%,,%') do
	BEGIN
	update market.contractors a 
		set a.address_yur=REPLACE(a.address_yur,',,',','), a.address_fiz=REPLACE(a.address_fiz,',,',',') 
		where a.address_yur like '%,,%' or a.address_fiz like '%,,%';
	END;
end WHILE;
update market.contractors a 
	set a.address_yur=SUBSTR(address_yur,2,LENGTH(address_yur)-1) 
	where SUBSTR(address_yur,1,1)=',';
update market.contractors a 
	set a.address_fiz=SUBSTR(address_fiz,2,LENGTH(address_fiz)-1) 
	where SUBSTR(address_fiz,1,1)=',';

update market.contractors a 
	set a.address_yur=CONCAT(SUBSTR(address_yur,1,LENGTH(address_yur)-1),'.')
	where SUBSTR(address_yur,LENGTH(address_yur),1)=',';
update market.contractors a 
	set a.address_fiz=CONCAT(SUBSTR(address_fiz,1,LENGTH(address_fiz)-1),'.')  
	where SUBSTR(address_fiz,LENGTH(address_fiz),1)=',';

update market.contractors a 
	set a.address_yur=REPLACE(a.address_yur,',',', '), a.address_fiz=REPLACE(a.address_fiz,',',', ');
#void __fastcall TContragents::SaveClick(TObject *Sender)
#void 			TContragents::Update_contractors(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `setZakaz` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `setZakaz`(zakaz varchar(6),  description varchar(255))
BEGIN
	#Routine body goes here...
	DECLARE id int;
	set id=0;
	select a.zakaz_id into id from Orders a where a.zakaz = zakaz limit 1;
	IF (id!=0)
	THEN
		BEGIN
			update Orders a set a.zakaz=zakaz, a.description=description where a.zakaz_id=id; 
		END;
	ELSE
		BEGIN
			INSERT into Orders (zakaz,description) values(zakaz,description);
		END;
	end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `setZakazContent` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `setZakazContent`(zakaz_id int, det_id int, kol int)
BEGIN
	#Routine body goes here...
	if (EXISTS (select zakaz_id a from zakaz a where a.zakaz_id=zakaz_id and a.id=det_id ) )
	THEN 
		BEGIN
			UPDATE zakaz a set a.kol=kol,a.base='mysql'  where a.zakaz_id=zakaz_id and a.id = det_id ; 
		END;
	ELSE
		BEGIN
			INSERT into zakaz (zakaz_id,id,kol,base) VALUES (zakaz_id,det_id,kol,'mysql');
		END;
	end if;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_del` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `sp_del`(id int(20) unsigned)
    COMMENT 'удаление контрагентов'
BEGIN
	#Routine body goes here...
#void __fastcall TContragents::DELClick(TObject *Sender)

IF not exists (select * from market.specifications a where a.id=id)
	then
		begin
			select "Неизвестный идентификатор" as msg;
		end;
	ELSE
		BEGIN
			select "функция не работает" as msg;
		end;
end if;
#void __fastcall TAgreements::DelClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Update`()
BEGIN
	#Routine body goes here...
#обновление списка контрагентов
delete FROM market.plan_zap;
delete from market.payment;
delete from market.shipment;
delete FROM market.production;
delete from market.spcontent;
delete FROM market.specifications;
delete from market.valute_list;
delete from market.dog_list ;#where base='oasu';
delete from market.contractors where base='oasu';

insert into market.contractors (sname,base)
SELECT trim(dgkn),'oasu' from temporary_tables.dg1du a
left join market.contractors b on trim(a.dgkn)=b.sname
where trim(a.dgkn)!='' and b.sname is null GROUP BY dgkn;

insert into market.valute_list (id,name)
select vkod,vnaim from temporary_tables.dg0val group by vkod;
insert into market.valute_list (id,name)values(2,'$');

insert into market.valute_curs (id,cours,date)
select vkod,vkur,vdat from temporary_tables.dg0val;
#обновление договоров
drop TEMPORARY TABLE if EXISTS dog_ids;
create TEMPORARY TABLE if not EXISTS dog_ids
(
id_new BIGINT(20) UNSIGNED not null AUTO_INCREMENT,
id_old BIGINT(20) UNSIGNED not null,
PRIMARY KEY (`id_new`),
key id_old(id_old)
)ENGINE=MYISAM AUTO_INCREMENT=1;
insert into dog_ids (id_old) select a.regd from temporary_tables.dg1du a group by a.regd;
ALTER TABLE market.dog_list AUTO_INCREMENT=1;

INSERT into market.dog_list
(
id,type,predm,podrid,StartDate,EndDate,SignDate,Summ,DogDate,Isp,leader,
contractor_id,prim,indication1,indication2,indication3,indication4,CreateUser,
UpdateUser,CreateDate,UpdateDate,base
)
SELECT 
a1.id_new id,
dogv type, 
dgpd predm,
if (vidp is not null and vidp>=0,vidp,null) podrid,
if (dgtn!='1899-12-30',dgtn,null) StartDate,
if (dgtk!='1899-12-30',dgtk,null) EndDate,
if (dogp!='1899-12-30',dogp,null) SignDate,
dgsum Summ,
if (dogd!='1899-12-30',dogd,null) DogDate,
dgisp Isp,
dgrf leader,
b.id contractor_id,
dgpr prim,
dgnl indication1,
dgnn indication2,
dgnv indication3,
dgnr indication4,
'upd' CreateUser,
'upd' UpdateUser,
CURRENT_TIMESTAMP() CreateDate,
CURRENT_TIMESTAMP() UpdateDate,
'oasu' base
FROM temporary_tables.dg1du a
join dog_ids a1 on a.regd=a1.id_old
left join market.contractors b on if (trim(a.ckod)!='',trim(a.ckod)=b.id1c,trim(a.dgkn)=b.sname);
#обновлние cпецификаций
drop TEMPORARY TABLE if EXISTS sp_ids;
create TEMPORARY TABLE if not EXISTS sp_ids
(
id_new BIGINT(20) UNSIGNED not null AUTO_INCREMENT,
id_old BIGINT(20) UNSIGNED not null,
PRIMARY KEY (`id_new`),
key id_old(id_old)
)ENGINE=MYISAM AUTO_INCREMENT=1;
insert into sp_ids (id_old) select a.regs from temporary_tables.dg1st a group by a.regs;
ALTER TABLE market.specifications AUTO_INCREMENT=1;
insert into market.specifications 
(
id,iddog,spNum,prim,nds,valute,gruz_ca_id,plat_ca_id,liz_ca_id,SignDate,CreateDate,UpdateDate,
CreateUser,UpdateUser,cancelDate,cancelreason,base
)
select 
b1.id_new,
b.id_new,
a.spcn,
a.sppr,
a.snds,
a.vkod,
c1.id,
c2.id,
c3.id,
if (a.spdp!='1899-12-30',a.spdp,null),
if (a.spdz!='1899-12-30',a.spdz,null),
CURRENT_TIMESTAMP(),
"upd",
"upd",
if (a.spdo!='1899-12-30',a.spdo,null),
a.spo,
"oasu"
from temporary_tables.dg1st a 
	join dog_ids b on a.regd=b.id_old
	join sp_ids b1 on b1.id_old=a.regs
	 left join market.contractors c1 on if (TRIM(a.gkod)!="",c1.id1c=trim(a.gkod),null)
	 left join market.contractors c2 on if (TRIM(a.pkod)!="",c2.id1c=trim(a.pkod),null)
	 left join market.contractors c3 on if (TRIM(a.lkod)!="",c3.id1c=trim(a.lkod),null);

#заказы в спецификациях
drop TEMPORARY TABLE if EXISTS content_ids;
create TEMPORARY TABLE if not EXISTS content_ids
(
id_new BIGINT(20) UNSIGNED not null AUTO_INCREMENT,
id_old BIGINT(20) UNSIGNED not null,
podr 	 CHAR(2),
PRIMARY KEY (`id_new`),
key id_old(id_old)
)ENGINE=MYISAM AUTO_INCREMENT=1;
insert into content_ids (id_old,podr) select a.regz,'00' from temporary_tables.dg1zt a group by a.regz;
insert into content_ids (id_old,podr) select a.regz,'12' from temporary_tables.dg1zt12 a group by a.regz;
ALTER TABLE market.specifications AUTO_INCREMENT=1;
#кроме ппф
insert INTO market.spcontent
(
id,id_spec,zkom,zakaz,pos,name,obi,obivin,kol,price,per_suppl,ppo_vz,razd,ei_id,
ppo_resurs,ppo_price_resurs,prim,ppo_cex,prime_cost,PC_Get_Date,
calc_id,demand_id,CreateDate,UpdateDate,CreateUser,UpdateUser,base
)
SELECT
b1.id_new,
b.id_new,
zkom,
zakn,
zpoz,
znai,
zobi,
znos,
zksp,
zcsh,
zsrs,
if (trim(zvid)!='',
		if (trim(zvid) in ('п1з','п1п','п2з','п2п'),
				'241',
				if(trim(zvid) in ('прз','прп'),
					'215',
					if(trim(zvid) in ('инз','инп'),
						'216',
						if(trim(zvid) in ('штз','штп'),
							'22',
							if(trim(zvid) in ('зсз','зсп'),
								null,
								trim(zvid)
								)
							)
						)	
					)
				),
		null),
razd,
if (trim(zgrs)!='',if (trim(zgrs)='0','401','419'),null),
zves,
zckg,
zpri,
zceu,
sklk,
if (a.dklk!='1899-12-30',a.dklk,null),
if (trim(nklk)!=0 and trim(nklk)!='',nklk,null),
if (trim(nzav)!=0 and trim(nzav)!='',nklk,null),
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
'upd',
'upd',
'oasu'
from temporary_tables.dg1zt a 
	join sp_ids b on b.id_old=a.regs
	join content_ids b1 on b1.id_old=a.regz and podr='00'
	join market.specifications c on c.id=b.id_new;
#ппф
insert INTO market.spcontent
(
id,id_spec,zkom,zakaz,pos,name,obi,obivin,kol,price,per_suppl,ei_id,razd,prim,prime_cost,
PC_Get_Date,calc_id,demand_id,ppf_r,ppf_size,ppf_vid,ppf_type_pf,ppf_isp,ppf_model,ppf_ves,
CreateDate,UpdateDate,CreateUser,UpdateUser,base
)
SELECT
b1.id_new,
b.id_new,
zkom,
zakn,
zpoz,
znai,
zobi,
'',
zksp,
zcsh,
zsrs,
if (trim(zeiz)!='',if (trim(zeiz)='0','401','419'),null),
razd,
zpri,
0,
NULL,
NULL,
NULL,
zrad,
zraz,
if (zvid!='',zvid,null),
if (zpvd!='',zpvd,null),
zisp,
znos,
zves,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
'upd',
'upd',
'oasu'
from temporary_tables.dg1zt12 a 
	join sp_ids b on b.id_old=a.regs
	join content_ids b1 on b1.id_old=a.regz and podr='12'
	join market.specifications c on c.id=b.id_new;
# доп состав заказа
insert into order_composition
(
id_content,name,obi,kol,prim,pos
)#ппо
SELECT
c.id,
trim(a.knai),
trim(a.kobi),
a.kkol,
trim(a.kpri),
a.kpoz
from temporary_tables.dg1zk a 
join content_ids b on b.id_old=a.regs and b.podr='00'
join market.spcontent c on b.id_new=c.id_spec and a.zpoz=c.pos;
insert into order_composition
(
id_content,name,obi,kol,prim,pos
)#ппф
SELECT
c.id,
trim(a.knai),
trim(a.kobi),
a.kkol,
trim(a.kpri),
a.kpoz
from temporary_tables.dg1zk12 a 
join content_ids b on b.id_old=a.regs and b.podr='12'
join market.spcontent c on b.id_new=c.id_spec and a.zpoz=c.pos;
#выпуски
#общая
insert into production
(
id_content,
podrid,
cex,
fvnd,
fdoc,
fdtd,
kol,
ksum,
kves,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
SELECT
b.id_new,
vidp,
fceu,
fvnd,
if (fdoc>0,fdoc,null),
if (fdtd!='1899-12-30',fdtd,null),
fkol,
ksum,
kves,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
"upd",
"upd",
'oasu'
from temporary_tables.dg1ft a 
join content_ids b on b.id_old=a.regz and b.podr='00'
join market.spcontent c on c.id=b.id_new;
#ппо
insert into production
(
id_content,
podrid,
cex,
fvnd,
fdoc,
fdtd,
kol,
ksum,
kves,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
SELECT
b.id_new,
vidp,
fceu,
fvnd,
if (fdoc>0,fdoc,null),
if (fdtd!='1899-12-30',fdtd,null),
fkol,
ksum,
0,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
"upd",
"upd",
'oasu'
from temporary_tables.dg1ft11 a 
join content_ids b on b.id_old=a.regz and b.podr='00'
join market.spcontent c on c.id=b.id_new;
#ппф
insert into production
(
id_content,
podrid,
cex,
fvnd,
fdoc,
fdtd,
kol,
ksum,
kves,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
SELECT
b.id_new,
vidp,
00,
fvnd,
if (fdoc>0,fdoc,null),
if (a.fdtd!='1899-12-30',a.fdtd,null),
fkol,
ksum,
0,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
"upd",
"upd",
'oasu'
from temporary_tables.dg1ft12 a 
join content_ids b on b.id_old=a.regz and b.podr='12'
join market.spcontent c on c.id=b.id_new;
#отгрузки
#общая
insert into shipment
(
id_content,
ovnd,
kol,
nds,
crub,
srub,
snrub,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
select 
b.id_new,
ovnd,
okol,
onds,
0,
0,
0,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
"upd",
"upd",
'oasu'
FROM temporary_tables.dg1ot a 
join content_ids b on b.id_old=a.regz and b.podr='00'
join market.spcontent c on c.id=b.id_new;
#ппо
insert into shipment
(
id_content,
ovnd,
kol,
nds,
crub,
srub,
snrub,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
select 
b.id_new,
ovnd,
okol,
onds,
crub,
srub,
snrub,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
"upd",
"upd",
'oasu'
FROM temporary_tables.dg1ot11 a 
join content_ids b on b.id_old=a.regz and b.podr='00'
join market.spcontent c on c.id=b.id_new;
#ппф
insert into shipment
(
id_content,
ovnd,
kol,
nds,
crub,
srub,
snrub,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
select 
b.id_new,
ovnd,
okol,
onds,
crub,
srub,
snrub,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
"upd",
"upd",
'oasu'
FROM temporary_tables.dg1ot12 a 
join content_ids b on b.id_old=a.regz and b.podr='12'
join market.spcontent c on c.id=b.id_new;
#оплаты
#общая
insert into payment 
(
id_spec,
sum,
date,
ovnd,
rvnd,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
SELECT
b.id_new,
zsum,
rzdat,
ovnd,
rvnd,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
"upd",
"upd",
'oasu'
from temporary_tables.dg1rz a 
join sp_ids b on b.id_old=a.regs
join specifications c on b.id_new=c.id;
#ппо
insert into payment 
(
id_spec,
sum,
date,
ovnd,
rvnd,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
SELECT
b.id_new,
zsum,
rzdat,
ovnd,
rvnd,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
"upd",
"upd",
'oasu'
from temporary_tables.dg1rz11 a 
join sp_ids b on b.id_old=a.regs
join specifications c on b.id_new=c.id;
#ппф
insert into payment 
(
id_spec,
sum,
date,
ovnd,
rvnd,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
SELECT
b.id_new,
zsum,
rzdat,
ovnd,
rvnd,
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
"upd",
"upd",
'oasu'
from temporary_tables.dg1rz12 a 
join sp_ids b on b.id_old=a.regs
join specifications c on b.id_new=c.id;
#запуски
#ппо
insert into plan_zap
(
id_content,
zvnd,
doc_title,
dok_date,
part,
kol,
zcen,
zceb,
zckg,
znch,
type,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
SELECT 
b.id_new,
zvnd,
zdoc,
zdat,
zpar,
zkol,
zcen,
zceb,
zckg,
znch,
if (zapv='рз','рз','мз'),
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
'upd',
'upd',
'oasu'
from temporary_tables.dg1pz11 a 
join content_ids b on b.id_old=a.regz and b.podr='00'
join market.spcontent c on c.id=b.id_new;
#ппф
insert into plan_zap
(
id_content,
zvnd,
doc_title,
dok_date,
part,
kol,
zcen,
zceb,
zckg,
znch,
type,
CreateDate,
UpdateDate,
CreateUser,
UpdateUser,
base
)
SELECT 
b.id_new,
zvnd,
zdoc,
zdat,
zpar,
zkol,
zcen,
zceb,
0,
znch,
if (zapv='рз','рз','мз'),
CURRENT_TIMESTAMP(),
CURRENT_TIMESTAMP(),
'upd',
'upd',
'oasu'
from temporary_tables.dg1pz12 a 
join content_ids b on b.id_old=a.regz and b.podr='12'
join market.spcontent c on c.id=b.id_new;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `oasu`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `oasu` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `oasu`;

--
-- Dumping events for database 'oasu'
--

--
-- Dumping routines for database 'oasu'
--
/*!50003 DROP PROCEDURE IF EXISTS `AddToJournal` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `AddToJournal`()
BEGIN
	#Routine body goes here...
insert into nsi001j(`obu`,`obd`,`pp`,`ppp`,`ei`,`kol`,`action`,`date`) select `obu`,`obd`,`pp`,`ppp`,`ei`,`kol`,`action`,CURRENT_TIMESTAMP() from nsi001 where `action`!='no';
insert into nsi002j(`obd`,`obm`,`ei`,`vz`,`kdz`,`masd`,`masz`,`nrm`,`razz`,`action`,`date`) select `obd`,`obm`,`ei`,`vz`,`kdz`,`masd`,`masz`,`nrm`,`razz`,`action`,CURRENT_TIMESTAMP() from nsi002 where `action`!='no';
insert into nsi003j(`obd`,`namd`,`rsp`,`action`,`date`) select `obd`,`namd`,`rsp`,`action`,CURRENT_TIMESTAMP() from nsi003 where `action`!='no';
insert into nsi004j(`OBD`,`CEU`,`OPR`,`OBO`,`KSHT`,`PROF`,`KROP`,`RR`,`KOLOD`,`EN`,`KTS`,`KVN`,`TPZ`,`TSHT`,`action`,`date`) select `OBD`,`CEU`,`OPR`,`OBO`,`KSHT`,`PROF`,`KROP`,`RR`,`KOLOD`,`EN`,`KTS`,`KVN`,`TPZ`,`TSHT`,`action`,CURRENT_TIMESTAMP() from nsi004 where `action`!='no';
insert into nsi005j(`obd`,`napr`,`pn`,`action`,`date`) select `obd`,`napr`,`pn`,`action`,CURRENT_TIMESTAMP() from nsi005 where `action`!='no';
insert into nsi006j(`obd`,`zaka`,`action`,`date`) select `obd`,`zaka`,`action`,CURRENT_TIMESTAMP() from nsi006 where `action`!='no';
insert into nsi009j(`OBD`,`CEU`,`OPR`,`OBO`,`KSHT`,`PROF`,`KROP`,`RR`,`KOLOD`,`EN`,`KTS`,`KVN`,`TPZ`,`TSHT`,`ttp`,`action`,`date`) select `OBD`,`CEU`,`OPR`,`OBO`,`KSHT`,`PROF`,`KROP`,`RR`,`KOLOD`,`EN`,`KTS`,`KVN`,`TPZ`,`TSHT`,`ttp`,`action`,CURRENT_TIMESTAMP() from nsi009 where `action`!='no';
insert into nsi010j(`obu`,`obm`,`isp`,`podr`,`ei`,`nrm`,`action`,`date`) select `obu`,`obm`,`isp`,`podr`,`ei`,`nrm`,`action`,CURRENT_TIMESTAMP() from nsi010 where `action`!='no';

delete from nsi001;
delete from nsi002;
delete from nsi003;
delete from nsi004;
delete from nsi005;
delete from nsi006;
delete from nsi009;
delete from nsi010;
delete from sended_dets;
delete from oasu.Transfers;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `CheckChenges` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `CheckChenges`()
BEGIN
# простановка признака действия над строкой
delete from nsi001 where `action`='del';
delete from nsi002 where `action`='del';
delete from nsi003 where `action`='del';
delete from nsi004 where `action`='del';
delete from nsi005 where `action`='del';
delete from nsi006 where `action`='del';
delete from nsi009 where `action`='del';
delete from nsi010 where `action`='del';

update nsi001 set `action`='no';
update nsi002 set `action`='no';
update nsi003 set `action`='no';
update nsi004 set `action`='no';
update nsi005 set `action`='no';
update nsi006 set `action`='no';
update nsi009 set `action`='no';
update nsi010 set `action`='no';

update oasu.nsi006 b 
	left join temporary_tables.nsi006 a  on a.zaka=b.zaka and a.obd=b.obd 
	set b.`action`='ins' 
	where a.obd is null;
insert into oasu.nsi006 (obd,zaka,`action`) 
select distinct a1.obd,a1.zaka,"del" 
	from oasu.nsi006 a
	join temporary_tables.nsi006 a1 on a1.zaka=a.zaka
	left join oasu.nsi006 b on b.zaka=a1.zaka and b.obd=a1.obd
	where b.zaka is null;
#имена nsi003+
update oasu.nsi003 b 
left join temporary_tables.nsi003 a  on a.obd=b.obd 
set b.`action`='ins' where a.obd is null; #новые

update oasu.nsi003 b 
join temporary_tables.nsi003 a  on a.obd=b.obd and a.namd!=b.namd 
set b.`action`='upd' where b.`action`!='ins'; #обновление
#дерево nsi001+
update oasu.nsi001 b left join temporary_tables.nsi001 a 
	on a.obu=b.obu 
		and a.obd=b.obd 
	set b.`action`='ins' 
	where a.obu is null;#новые
/*update oasu.nsi001 b 
join temporary_tables.nsi001 a 	on a.obu=b.obu 	and a.obd=b.obd and (a.pp!=b.pp or a.ppp!=b.ppp  or a.ei!=b.ei or a.kol!=b.kol)
	set b.`action`='upd' 
	where b.`action`!='ins';#обновление*/
#удаление!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
DROP TEMPORARY TABLE IF EXISTS tmp;
CREATE TEMPORARY TABLE IF NOT EXISTS tmp AS
 select distinct obu obd FROM oasu.nsi001 UNION
 select distinct obd obd FROM oasu.nsi001 UNION
 select DISTINCT obd obd from oasu.nsi003;

/*insert into oasu.nsi001(obu,obd,pp,ppp,ei,kol,`action`)
SELECT   a.`obu`,a.`obd`,a.`pp`,
  a.`ppp`,a.`ei`,a.`kol`,
  'del' as `action` 
	FROM temporary_tables.nsi001 a
	join tmp b on b.obd=a.obu
	left join oasu.nsi001 c on c.obu=a.obu and c.obd=a.obd
	where c.obd is null;*/

#дерево nsi010?
update oasu.nsi010 b left join temporary_tables.nsi010 a  
	on a.obu=b.obu 
		and a.obm=b.obm 
	set b.`action`='ins' 	
where a.obu is null;#новые
update oasu.nsi010 b inner join temporary_tables.nsi010 a 
	on a.obu=b.obu 
		and a.obm=b.obm 
		and (a.isp!=b.isp or a.podr!=b.podr  or a.ei!=b.ei or a.nrm!=b.nrm)
	set b.`action`='upd' 
	where b.`action`!='ins';#обновление
update oasu.nsi010 b inner join temporary_tables.nsi010 a 
	on a.obu=b.obu 
		and a.obm=b.obm 
		and (a.ei=b.ei or a.nrm=b.nrm) #временная проверка не по всей строке 
	set b.`action`='no', b.isp=a.isp, b.podr=a.podr
	where b.`action`!='ins';#обновление
#удаление
/*insert into oasu.nsi010(obu,obm,isp,ei,nrm,podr,`action`)
SELECT   
  a.obu,a.obm,a.isp,a.ei,a.nrm,a.podr,
  'del' as `action` 
	FROM  temporary_tables.nsi010 a 
	join  tmp b on b.obd=a.obu
	left join oasu.nsi010 c on c.obu=a.obu and c.obm=a.obm
where 
c.obu is null;
*/

#направления nsi005+
update oasu.nsi005 b 
left join temporary_tables.nsi005 a  on a.obd=b.obd 
set b.`action`='ins' 
where a.obd is null;

update oasu.nsi005 b 
join temporary_tables.nsi005 a  on a.obd=b.obd and a.napr!=b.napr 
set b.`action`='upd' 
where b.`action`!='ins'; #обновление

#materials nsi002+
update oasu.nsi002 b 
left join temporary_tables.nsi002 a  on a.obd=b.obd 
set b.`action`='ins' 
where a.obd is null;

update oasu.nsi002 b inner join temporary_tables.nsi002 a  on a.obd=b.obd 
and (a.obm!=b.obm or a.ei!=b.ei or a.vz!=b.vz or a.kdz!=b.kdz or a.masd!=b.masd or a.masz!=b.masz or a.nrm!=b.nrm or a.razz!=b.razz)
set b.`action`='upd' 
where b.`action`!='ins';


#nsi004+#nsi009+
#проверка наличия в ттп если есть то no action
update oasu.nsi004 b left join temporary_tables.nsi004 a  
on a.obd=b.obd 	and a.opr=b.opr and a.PROF=b.prof and a.rr=b.rr#ключ
	set b.`action`='ins' 
	where a.obd is null;

update oasu.nsi004 b inner join temporary_tables.nsi004 a  
on a.obd=b.obd  and a.opr=b.opr and a.PROF=b.prof and a.rr=b.rr #ключ
	and (a.obo!=b.obo or a.ceu!=b.ceu or a.ksht!=b.ksht or a.KROP!=b.KROP 
	or a.KOLOD!=b.KOLOD or a.en!=b.en or a.kts!=b.kts or a.kvn!=b.kvn 
	or a.tpz!=b.tpz or a.tsht!=b.tsht)
	set b.`action`='upd' 
	where b.`action`!='ins';

update oasu.nsi004 b inner join temporary_tables.nsi004 a  
	on a.obd=b.obd and a.opr=b.opr and a.obo=b.obo 
		and a.ceu=b.ceu and a.ksht=b.ksht and a.KROP=b.KROP 
		and a.KOLOD=b.KOLOD and a.en=b.en and a.kts=b.kts 
		and a.kvn=b.kvn and a.tpz=b.tpz and a.tsht=b.tsht
	set b.`action`='no';
#из 009 удалить детали которые переводятся в 4ю
insert into oasu.nsi009 (obd,ceu,opr,obo,ksht,prof,krop,rr,kolod,EN,kts,KVN,TPZ,TSHT,ttp,`action` )
	select b.obd,b.ceu,b.opr,b.obo,b.ksht,b.prof,b.krop,b.rr,b.kolod,b.EN,b.kts,b.KVN,b.TPZ,b.TSHT,b.ttp,'del'
	from oasu.nsi004 a
	inner join temporary_tables.nsi009 b on a.obd=b.obd and a.opr=b.opr# and a.prof=b.prof and a.krop=b.krop
	where a.`action`='ins'
	union
	SELECT a.obd,a.ceu,a.opr,a.obo,a.ksht,a.prof,a.krop,a.rr,a.kolod,a.EN,a.kts,a.KVN,a.TPZ,a.TSHT,ttp,'del' as `action` 
	FROM  temporary_tables.nsi009 a 
	join 	oasu.sended_dets b on b.obd=a.obd
	left join  oasu.nsi004 b1 on b1.obd=a.obd and b1.opr=a.opr and b1.PROF=a.PROF and b1.rr=a.rr
	where 
	b1.obd is null;

insert into oasu.nsi004 (obd,ceu,opr,obo,ksht,prof,krop,rr,kolod,EN,kts,KVN,TPZ,TSHT,`action` )#строки на удаление
	SELECT a.obd,a.ceu,a.opr,a.obo,a.ksht,a.prof,a.krop,a.rr,a.kolod,a.EN,a.kts,a.KVN,a.TPZ,a.TSHT,'del' as `action` 
	FROM  temporary_tables.nsi004 a 
	join 	oasu.sended_dets b on b.obd=a.obd
	left join  oasu.nsi004 b1 on b1.obd=a.obd and b1.opr=a.opr and b1.PROF=a.PROF and b1.rr=a.rr
	where 
	b1.obd is null ORDER BY a.obd,a.opr,a.prof,a.rr;
#nsi009

#корректировка действия для деталей внесенных больше чем 1 раз в день
#вставка
update nsi001 a 
	join nsi001j b on a.obu=b.obu and a.obd=b.obd and b.date>CURDATE() and b.`action`="ins"
	set a.`action`="upd";
update nsi002 a 
	join nsi002j b on a.obd=b.obd and b.date>CURDATE() and b.`action`="ins"
	set a.`action`="upd";
update nsi003 a 
	join nsi003j b on a.obd=b.obd and b.date>CURDATE() and b.`action`="ins"
	set a.`action`="upd";
update nsi004 a 
	join nsi004j b on a.obd=b.obd  and a.opr=b.opr and a.PROF=b.prof and a.rr=b.rr and b.date>CURDATE() and b.`action`="ins"
	set a.`action`="upd";
update nsi005 a 
	join nsi005j b on a.obd=b.obd and b.date>CURDATE() and b.`action`="ins"
	set a.`action`="upd";
update nsi006 a 
	join nsi006j b on a.zaka=b.zaka and a.obd=b.obd and b.date>CURDATE() and b.`action`="ins"
	set a.`action`="upd";
update nsi009 a 
	join nsi009j b on a.obd=b.obd  and a.opr=b.opr and a.PROF=b.prof and a.rr=b.rr and b.date>CURDATE() and b.`action`="ins"
	set a.`action`="upd";
update nsi010 a 
	join nsi010j b on a.obu=b.obu and a.obm=b.obm and b.date>CURDATE() and b.`action`="ins"
	set a.`action`="upd";
#удаление
update nsi001 a 
	join nsi001j b on a.obu=b.obu and a.obd=b.obd and b.date>CURDATE() and b.`action`="del"
	set a.`action`="no";
update nsi002 a 
	join nsi002j b on a.obd=b.obd and b.date>CURDATE() and b.`action`="del"
	set a.`action`="no";
update nsi003 a 
	join nsi003j b on a.obd=b.obd and b.date>CURDATE() and b.`action`="del"
	set a.`action`="no";
update nsi004 a 
	join nsi004j b on a.obd=b.obd  and a.opr=b.opr and a.PROF=b.prof and a.rr=b.rr and b.date>CURDATE() and b.`action`="del"
	set a.`action`="no";
update nsi005 a 
	join nsi005j b on a.obd=b.obd and b.date>CURDATE() and b.`action`="del"
	set a.`action`="no";
update nsi006 a 
	join nsi006j b on a.zaka=b.zaka and a.obd=b.obd and b.date>CURDATE() and b.`action`="del"
	set a.`action`="no";
update nsi009 a 
	join nsi009j b on a.obd=b.obd  and a.opr=b.opr and a.PROF=b.prof and a.rr=b.rr and b.date>CURDATE() and b.`action`="del"
	set a.`action`="no";
update nsi010 a 
	join nsi010j b on a.obu=b.obu and a.obm=b.obm and b.date>CURDATE() and b.`action`="del"
	set a.`action`="no";
# коррерктировки размеров заготовок
update oasu.nsi002 set razz=REPLACE(razz,' < ','<');
update oasu.nsi002 set razz=REPLACE(razz,'< ','<');
update oasu.nsi002 set razz=REPLACE(razz,' <','<');
update oasu.nsi002 set razz=REPLACE(razz,' > ','>');
update oasu.nsi002 set razz=REPLACE(razz,'> ','>');
update oasu.nsi002 set razz=REPLACE(razz,' >','>');
update oasu.nsi002 set razz=REPLACE(razz,' - ','-');
update oasu.nsi002 set razz=REPLACE(razz,'- ','-');
update oasu.nsi002 set razz=REPLACE(razz,' -','-');
update oasu.nsi002 set razz=REPLACE(razz,' + ','+');
update oasu.nsi002 set razz=REPLACE(razz,'+ ','+');
update oasu.nsi002 set razz=REPLACE(razz,' +','+');
update oasu.nsi002 set razz=REPLACE(razz,' * ','*');
update oasu.nsi002 set razz=REPLACE(razz,'* ','*');
update oasu.nsi002 set razz=REPLACE(razz,' *','*');
update oasu.nsi002 set razz=REPLACE(razz,' / ','/');
update oasu.nsi002 set razz=REPLACE(razz,'/ ','/');
update oasu.nsi002 set razz=REPLACE(razz,' /','/');
update oasu.nsi002 set razz=REPLACE(razz,' = ','=');
update oasu.nsi002 set razz=REPLACE(razz,'= ','=');
update oasu.nsi002 set razz=REPLACE(razz,' =','=');

DROP TEMPORARY TABLE IF EXISTS tmp;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Clear_Incoming` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Clear_Incoming`()
BEGIN
	#Routine body goes here...
delete from planz;
delete from poli;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Finalize_Sending` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Finalize_Sending`()
BEGIN
	#Routine body goes here...
declare lvl int;
#получить список деталей
Drop TEMPORARY TABLE IF EXISTS f_tmp;
CREATE TEMPORARY TABLE IF NOT EXISTS f_tmp as 
	select obd from planz GROUP BY obd;
insert into f_tmp (obd)
	select a.obi from poli a 
	left join planz b on a.Obi=b.obd
	where b.obd is null;
insert into f_tmp (obd)
	select a.obu from poli a 
	left join poli b on a.Obu=b.obi 
	where b.obd is null;
insert into f_tmp (obd)
	select a.obd from poli a 
	left join poli b on a.Obd=b.obu
	where b.obd is null;
#добавить недастающие в names 
insert into constructions.det_names (obd,namd,pp,format,UserID,razdSPID,state,base,CreateDate,CreateUser,UpdateDate,UpdateUser)
select a.obd,'','00','',null,4,4,'oasu',CURRENT_TIMESTAMP(),'manufacturing',CURRENT_TIMESTAMP(),'manufacturing' from f_tmp a
	left join constructions.det_names b on a.obd=b.obd
	where b.obd is null;
#добавить записи в started_zak
insert into manufacture.started_zak (zakaz,part,Date)
select a.zakaz,a.part,max(a.Date)
  from planz a 
	left join manufacture.started_zak b on b.zakaz=a.zakaz and b.part=a.part
	where b.zakaz is null and a.part!='99' GROUP BY zakaz,part;

#удаление существующих копий разверток
DROP TEMPORARY TABLE IF EXISTS fs_tmp;
CREATE TEMPORARY TABLE IF NOT EXISTS fs_tmp as
select distinct c.eidc from manufacture.prymary_entry a 
	join manufacture.started_zak b on a.`order`=b.`order`
	join manufacture.entries c on c.eidc=a.eid
	join planz d on d.zakaz=b.zakaz and d.part=b.part
	join constructions.det_names e on e.obd=d.obd;
delete from manufacture.entries where eidc in (select eidc from fs_tmp);

#собрать развертки для запускаемых
set @sidc=0;
DROP TEMPORARY TABLE IF EXISTS tmp;
CREATE TEMPORARY TABLE IF NOT EXISTS tmp as
select @sidc:=if (max(eidc) is not null,max(eidc),0)+1 from manufacture.entries a;
DROP TEMPORARY TABLE IF EXISTS tmp;

Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;

set @sq=CONCAT('CREATE TEMPORARY TABLE IF NOT EXISTS res(
	entry BIGINT UNSIGNED NOT NULL,
	eidc  BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
	eidp  BIGINT UNSIGNED,
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
  sp_kol double NOT NULL,
	tree_kol double NOT NULL,
	ei	char(3) NOT NULL,
	lvl int not null,
		PRIMARY KEY (`eidc`),
		key `entry`(`entry`),
		key `eidp`(`eidp`),
		key `idc`(`idc`),
		key `idp`(`idp`),
		key `lvl`(`lvl`)
) ENGINE=MYISAM AUTO_INCREMENT=',@sidc,';');
prepare init from @sq;
EXECUTE init;

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl(
	entry BIGINT UNSIGNED NOT NULL,
	eidc  BIGINT UNSIGNED,
	eidp  BIGINT UNSIGNED,
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
  sp_kol double NOT NULL,
	tree_kol double NOT NULL,
	ei	char(3) NOT NULL,
	lvl int not null,
		PRIMARY KEY (`eidc`),
		key `entry`(`entry`),
		key `eidp`(`eidp`),
		key `idc`(`idc`),
		key `idp`(`idp`),
		key `lvl`(`lvl`)
) ENGINE=MYISAM; 

#инициализация 
set lvl=0;
insert into res (entry,idc,idp,eidp,sp_kol,tree_kol,ei,lvl)
select b.id,b.id,null,null,a.kol,a.kolp,a.ei,lvl from poli a
	join constructions.det_names b on a.obd=b.obd
	join planz c on c.obd=a.obd and c.part!=99
	where a.obd=a.obu and a.obd=a.obi;
#развертка
while EXISTS (select lvl from res where res.lvl=lvl)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res (entry,idc,idp,eidp,sp_kol,tree_kol,ei,lvl)
			(
			select b.entry,a3.id,b.idc,b.eidc,a.kol,a.kolp,a.ei,lvl+1
			from poli a 
				join constructions.det_names a1 on a1.obd=a.Obi
				join constructions.det_names a2 on a2.obd=a.Obu
				join constructions.det_names a3 on a3.obd=a.Obd
				join `obd_lvl` b on b.entry=a1.id and a2.id=b.idc and b.lvl=lvl
				where !(a3.id=a2.id and a3.id=a1.id)
			);
	set lvl=lvl+1;
END while;

#вставка данных по разверткам
insert into manufacture.entries (eidp,idp,eidc,idc,sp_kol,tree_kol,ei)
select eidp,idp,eidc,idc,sp_kol,tree_kol,ei from res;
#зарегистрировать entry point`s
insert into manufacture.prymary_entry (`Order`,eid)
select b.`order`,d.eidc FROM planz a
	JOIN manufacture.started_zak b on b.zakaz=a.zakaz and b.part=a.part
	join constructions.det_names c on c.obd=a.obd
	join res d on d.idc=c.id AND d.lvl=0;

#Call Clear_Incoming();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Send_Plan_Row` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Send_Plan_Row`(zakaz varchar(6),part varchar(2),obd varchar(15),kol double)
BEGIN
	#Routine body goes here...
insert into planz (zakaz,part,obd,kol,date)
	select zakaz,part,obd,kol,CURRENT_TIMESTAMP();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Send_Poli_Row` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Send_Poli_Row`(obi varchar(15),obu varchar(15),obd varchar(15),kol double,kolp double,ei varchar(3))
BEGIN
	#Routine body goes here...
insert into Poli (Obi,Obu,Obd,kol,kolp,ei,date)
	select Obi,Obu,Obd,kol,kolp,ei,CURRENT_TIMESTAMP();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `processed_list`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `processed_list` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `processed_list`;

--
-- Dumping events for database 'processed_list'
--

--
-- Dumping routines for database 'processed_list'
--
/*!50003 DROP PROCEDURE IF EXISTS `Add_Entrance` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Add_Entrance`(id int,kol double ,  list_no bigint unsigned, user int)
BEGIN
	#Routine body goes here...
# добавить вхождение поставить метку редактирования списка

declare lvl int;
set @sidc=0;
DROP TEMPORARY TABLE IF EXISTS tmp;
CREATE TEMPORARY TABLE IF NOT EXISTS tmp as
select @sidc:=if (max(eidc) is not null,max(eidc),0)+1 from entries a;
DROP TEMPORARY TABLE IF EXISTS tmp;

Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;

set @sq=CONCAT('CREATE TEMPORARY TABLE IF NOT EXISTS res(
	eidc  BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
	eidp  BIGINT UNSIGNED,
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
	idci int(11)unsigned DEFAULT null,
  kol double NOT NULL,
	ei	char(3) NOT NULL,
	lvl int not null,
	PRIMARY KEY (`eidc`),
	key `eidp`(`eidp`),
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM AUTO_INCREMENT=',@sidc,';');
prepare init from @sq;
EXECUTE init;

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl(
	eidc  BIGINT UNSIGNED,
	eidp  BIGINT UNSIGNED,
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
	idci int(11)unsigned DEFAULT null,
  kol double NOT NULL,
	ei	char(3) NOT NULL,
	lvl int not null,
	PRIMARY KEY (`eidc`),
	key `eidp`(`eidp`),
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM; 

#инициализация 
insert into res (eidp,idp,idc,idci,kol,ei,lvl)
	select null,null as idp,a.id as idc,d.id00 as idci,kol as kol,401,0 as lvl
		from constructions.det_names a 
		left join constructions.basik_performance d on d.id=a.id
		where a.id=id;
set lvl=0;
#развертка
while EXISTS (select idc from res where res.lvl=lvl)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res (eidp,idp,idc,idci,kol,ei,lvl)
			(
			select b.eidc as eidp,a.idparent as idp,a.idchild as idc,d.id00 as idci,a.kol*b.kol as kol,a.ei,lvl+1 as lvl
			from constructions.det_tree a 
						inner join `obd_lvl` b on (a.idparent=b.idc or (a.idparent=b.idci and a.ppp=0)) and b.lvl=lvl
						left join constructions.basik_performance d on d.id=a.idchild
			);
	set lvl=lvl+1;
END while;
#Вставка в список
insert into entries (idp,idc,kol,eidc,eidp,active,ei)
	select a.idp,a.idc,a.kol,a.eidc,a.eidp,1 as active,a.ei from res a;
#регистрация точки входа в дерево
insert into prymary_entry 
	select list_no, a.eidc from res a where a.lvl=0;
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;

#call list_modifi_mark(list_no,user);
#void __fastcall TList_Editor::TreeItems_Add_Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Add_List` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Add_List`(Type smallint(5) unsigned, User int)
BEGIN
	#Routine body goes here...
/*
set @sidc=0;
select @sidc:=if (max(List_No) is not null,max(List_No),0)+1 from lists a;
//если решу что автоинкремент ненужен )) использую эту переменную для задания номера листа
*/
	insert into lists (/*list_no*/Type,CreateDate,UpdateDate,CreateUser,UpdateUser,User)
		select /*@sidc,*/Type,CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP(),a.LogIn,a.LogIn,"" 
		from administration.logins a 
		where a.logid=User;
#void __fastcall TListAdd::OKClick(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Check_errs` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Check_errs`(list_no bigint unsigned)
BEGIN
	#Routine body goes here...
Drop TEMPORARY table if EXISTS Det_IDS;
Drop TEMPORARY TABLE IF EXISTS Tree_RowS;

call Get_list_Entries(list_no);
Create TEMPORARY TABLE IF NOT EXISTS Det_IDS as select a.id from output a WHERE a.active!=0 group by a.id;
Create TEMPORARY TABLE IF NOT EXISTS Tree_RowS as select a.id,a.idp,a.eidc,a.eidp from output a WHERE a.active!=0 group by a.id,a.idp;

DELETE from `errors` where `errors`.list_no=list_no;

#отсутствие направления
insert into `errors` (list_no,Det_id,Err_no)
SELECT DISTINCT list_no,a.id,1
	FROM Det_IDS a
	left join technologic.det_info b on b.id=a.id
	left join sklad.materials c on c.obmid=a.id
	left join catalogs.podr_list d on CONCAT(d.cex,d.utch)=b.napr
	where d.npodr is null and c.obmid is null ;

#Проверка количетва
insert into `errors` (list_no,Det_id,Err_no)
SELECT DISTINCT list_no,a.id,2
	FROM Tree_RowS a
	left join constructions.det_tree b on a.id=b.idchild and a.idp=b.idparent
	left join entries c on a.id=c.idc and a.idp=c.idp
	where ((b.kol is null or b.kol<=0)or(c.kol is null or c.kol<=0))and a.idp is not null ;

insert into `errors` (list_no,Det_id,Err_no)
SELECT DISTINCT list_no,a.id,2
	FROM 	Tree_RowS a,entries c
	where a.id=c.idc and a.idp is null and c.idp is null and (c.kol is null or c.kol<=0) ;

 #проверка ниаменования
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,3 
	from Det_IDS a
	join constructions.det_names b on a.id=b.id
	where trim(b.namd)='' ;

#проверка материалки
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,4 
	FROM Det_IDS a
	left join technologic.det_info b on b.id=a.id
	left join sklad.materials c on c.obmid=a.id
	WHERE b.id is null and c.obmid is null ;

#проверка ед. изм c нормах
insert into `errors` (list_no,Det_id,Err_no)
select list_no,a.id,5 
	FROM Det_IDS a
	join technologic.det_info b on a.id=b.id
	left join catalogs.dimensionality c on b.ei=c.kodei
	WHERE c.kodei is null ;

#проверка размера заготовки c нормах 
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,6 
	FROM Det_IDS a
	join technologic.det_info b on a.id=b.id
	join constructions.det_names c on c.id=a.id
	WHERE
	c.razdSPID=4 and trim(b.razz)='' ;

#проверка кода материала в нормах 
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,7 
	FROM Det_IDS a
	join technologic.det_info b on a.id=b.id
	join constructions.det_names c on c.id=a.id
	left join constructions.det_names c1 on c1.id=b.obmid
	WHERE
	c.razdSPID in (0,4) and (c1.id is null or left(c1.obd,2)="NA" or (c1.obd="000000000000000"and b.vz not in ('580')and b.vz not like '6__')) ;

# проверка наличия кода материала на АСУ
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,8
	FROM Det_IDS a
	join technologic.det_info b on a.id=b.id
	left join sklad.materials c on c.obmid=b.obmid
	join constructions.det_names c1 on c1.id=b.obmid	
	where c.obmid is null and c1.obd!="000000000000000" and left(c1.obd,2)!="NA"  ;

#проверка правильности назначения норм и масс
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,9 
	FROM Det_IDS a
	join technologic.det_info b on a.id=b.id
	join constructions.det_names c on c.id=b.obmid
	where c.razdSPID=4 and (b.masd=0 or b.masz=0 or b.nrm=0)and b.vz not in ('580')and b.vz not like '6__' ;
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,9 
	FROM Det_IDS a
	join technologic.det_info b on a.id=b.id
	join constructions.det_names c on c.id=b.obmid
	where (b.masd>b.masz or b.masd>b.nrm)and b.vz not in ('580')and b.vz not like '6__' ;

#неверный вид заготовки
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,10 
	FROM Det_IDS a
	join technologic.det_info b on a.id=b.id
	left join billets.vz_tree c on c.kod=b.vz
	left join sklad.materials d on d.obmid=a.id
	where (c.kod is null and d.obmid is null) or LENGTH(c.kod)<3 ;

#проверка трудовых норм 
# нет технологии
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,11 
	from Det_IDS a
	left join technologic.operation_list b on b.id=a.id
	left join sklad.materials c on c.obmid=a.id
	WHERE b.id is null and c.obmid is null ;

# Нет норм
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,12 
	from Det_IDS a
	join technologic.operation_list b on b.id=a.id
	left join technologic.operation_norms b1 on b1.OpUUID=b.OpUUID
	WHERE b1.OpUUID is null ;

#Опаcное количество записей норм
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,13 
	from Det_IDS a
	join technologic.operation_list b on b.id=a.id
	left join technologic.operation_norms b1 on b1.OpUUID=b.OpUUID
	GROUP BY a.id,b.opr HAVING count(b.opr)!=1 ;

#пропущены нормы
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,14 
	from Det_IDS a
	join technologic.operation_list b on b.id=a.id
	join technologic.operation_norms b1 on b1.OpUUID=b.OpUUID
	where (	b1.KSHT=0 or trim(b1.PROF)='' or 
					trim(b1.KROP)='' or trim(b1.RR)='' or 
					b1.KOLOD=0 or trim(b1.EN)='' or 
					trim(b1.KTS)='' or trim(b1.KVN)='' or 
					(b1.TSHT=0 and b.oboID not in('00069'))
				)and b.cex!=16 ;

#не верное количество знаков в професии
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,15 
	from Det_IDS a
	join technologic.operation_list b on b.id=a.id
	join technologic.operation_norms b1 on b1.OpUUID=b.OpUUID
	where LENGTH(b1.prof)!=4 ;

#не верное количество знаков в ЕН
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,16 
	from Det_IDS a
	join technologic.operation_list b on b.id=a.id
	join technologic.operation_norms b1 on b1.OpUUID=b.OpUUID
	where LENGTH(trim(b1.en))!=2 ;

#нет ктс
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,17 
	from Det_IDS a
	join technologic.operation_list b on b.id=a.id
	join technologic.operation_norms b1 on b1.OpUUID=b.OpUUID
	where LENGTH(trim(b1.kts))!=2 or b1.kts=0 or b1.kvn=0 or LENGTH(trim(b1.kvn))!=1;
# нет кшт.
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,18 
	from Det_IDS a
	join technologic.operation_list b on b.id=a.id
	join technologic.operation_norms b1 on b1.OpUUID=b.OpUUID
	where LENGTH(trim(b1.ksht))<1 or b1.ksht=0;
# нет kolod.
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,19 
	from Det_IDS a
	join technologic.operation_list b on b.id=a.id
	join technologic.operation_norms b1 on b1.OpUUID=b.OpUUID
	where LENGTH(trim(b1.kolod))<1 or b1.kolod=0;
# Неверное количество деталей в заготовке
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,20 
	FROM Det_IDS a
	join technologic.det_info b on a.id=b.id
	where b.kdz=0;
# устаревший код тарифной сетки
insert into `errors` (list_no,Det_id,Err_no)
select DISTINCT list_no,a.id,21 
	from Det_IDS a
	join technologic.operation_list b on b.id=a.id
	join technologic.operation_norms b1 on b1.OpUUID=b.OpUUID
	where b1.kts in (13,17,19,60);
SELECT count(a.list_no) result from `errors` a where a.list_no=list_no;

#size_t 			TList_Editor::CheckErrors		(unsigned __int64 list_no)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Del_Entrance` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Del_Entrance`(eid int,  list_no bigint unsigned, user int)
BEGIN
	#Routine body goes here...
# удалить вхождение поставить метку редактирования списка

#delete from prymary_entry where prymary_entry.List_no=list_no and prymary_entry.eid=eid;
call Reverse_Entries(eid);
delete from entries where eidc in (select a.eid from output a where a.eidp is null);
call list_modifi_mark(list_no,user);
DROP TEMPORARY TABLE IF EXISTS output;
#void __fastcall TList_Editor::TreeItems_del_Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Del_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Del_list`(list_no bigint unsigned)
BEGIN
	#Routine body goes here...
	delete from entries where entries.eidc in (select eid from prymary_entry where prymary_entry.List_no=list_no);
	delete from lists  where lists.List_No=list_no;
#TList_Editor::N12Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Active` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Active`(eid bigint unsigned)
BEGIN
	#Routine body goes here...
/*
проверка активности указанного узла
*/
	select a.active from entries a where a.eidc=eid;
#Tree_data::Set_active
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_aval_States` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_aval_States`(User bigint(20) unsigned)
BEGIN
	#получение списка доступных типов списков
select 	a.Name as State_Name,
				a.State_ID as State_ID from states a where a.State_ID=1;
#void  			TList_Editor::init 		(void)
# TList_sel_params::TList_sel_params(TComponent *Owner,const int &_LUser, cSQL *db)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_aval_types` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_aval_types`(User bigint(20) unsigned)
BEGIN
	#получение списка доступных типов списков
select 	a.Type_Name as Type_Name,
				a.Type_id as Type_ID from types a where a.Type_id=1;
#void  			TList_Editor::init 		(void)
# TList_sel_params::TList_sel_params(TComponent *Owner,const int &_LUser, cSQL *db)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Entrance_lvl` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Entrance_lvl`(eid BIGINT UNSIGNED)
BEGIN
	#Routine body goes here...
/*получает уровень развертки для построения древа*/
call reverse_entries(eid);
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.eid from output a where a.eidp is null;#получение id 
DROP TEMPORARY TABLE if EXISTS tmp;

call Get_Entries(@id);
drop temporary TABLE if EXISTS prep_kol;
CREATE TEMPORARY table if not EXISTS prep_kol as 
	select a.id,sum(a.kol) kol from output a group by a.id;
drop temporary TABLE if EXISTS output;

select 
a.idc 			id,
a.idp 			idp,
a.eidc 			eid,
a.eidp 			eidp,
b.kol 	 		sp_kol,
a.kol 	 		abs_kol,
a1.kol			all_kol,
a.active		active,
c.namd 			`Name`,
c.obd				Obd,
c.razdSPID 	SpRazd,
if (d.obd is not null,d.obd,'')							Obu,
if (c1.Razdname is not null,c1.Razdname,'')	SpRazdName,
if (e.snameei is not null,e.snameei,0) ei 
from entries a
join prep_kol a1 on a.idc=a1.id
join constructions.det_tree b on a.idc=b.idchild and a.idp=b.idparent
join constructions.det_names c on c.id=a.idc
left join administration.sprazd c1 on c1.RazdID=c.razdSPID
left join constructions.det_names d on d.id=a.idp
left join catalogs.dimensionality e on e.kodei=a.ei
where a.eidp=eid
ORDER BY c.razdSPID,c.obd;
drop temporary TABLE if EXISTS prep_kol;
#void __fastcall TList_Editor::TreeExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
/*
int &_id,
int &_idp,
int &_SpRazd
unsigned __int64 &_eid,
unsigned __int64 &_eidp,
double &_sp_kol,
double &_abs_kol,
bool &_active,
const String &_Name,
const String &_V_Obd,
const String &_V_Obu,
const String &_SpRazdName
*/
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Entries` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Entries`(eid bigint unsigned)
BEGIN
	#Routine body goes here...
/*получение списка входящих*/
declare lvl int;
drop TEMPORARY table if EXISTS res;
drop TEMPORARY table if EXISTS t_res;
create TEMPORARY table if not EXISTS res(
	eidp  bigint unsigned ,
	eidc	bigint unsigned not NULL,
	id		int unsigned not NULL,
	idp		int unsigned,
	kol		double not NULL,
	Active SMALLINT not null,
	lvl int not null,
	key `eidc`(`eidc`),
	key `eidp`(`eidp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
CREATE TEMPORARY TABLE IF NOT EXISTS t_res as select * from res where 0;
#подготовка
insert into res 
	select a.eidp,a.eidc,a.idc,a.idp,a.kol,a.active,0 from entries a where a.eidc=eid;
set lvl=0;
#развертка
while EXISTS (select eidc from res where res.lvl=lvl)do
  TRUNCATE TABLE t_res; 
  insert into `t_res` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select 
				b.eidc as eidp,
				a.eidc as eidc,
				a.idc as id,
				a.idp	as idp,
				a.kol as kol,
				a.active as active,
				lvl+1 as lvl
			from `entries` a 
			join `t_res` b on a.eidp=b.eidc and b.lvl=lvl
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if not EXISTS output as select * from res order by lvl;

drop TEMPORARY table if EXISTS res;
#Set_Active
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_err_data` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_err_data`(list_no bigint unsigned)
BEGIN
	#Routine body goes here...
Select a.Det_id id from `errors` a 
join constructions.det_names b on a.Det_id=b.id 
where a.list_no=list_no group by a.Det_id 
ORDER BY b.razdSPID,b.obd;
#void			TList_Editor::ShowData			(size_t row)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_err_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_err_list`(list_no bigint unsigned, id int unsigned)
BEGIN
	#Routine body goes here...
	select a.Err_Name 
	from err_list a 
	join `errors` b on a.Err_no=b.Err_no 
	where b.Det_id=id and b.list_no=list_no;

#void __fastcall TList_Editor::ErrsMouseDown(TObject *Sender, TMouseButton Button,TShiftState Shift, int X, int Y)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Excel_err_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Excel_err_list`(list_no bigint unsigned)
BEGIN
	#Routine body goes here...
Select b.obd,c.Err_Name err
from `errors` a 
join constructions.det_names b on a.Det_id=b.id 
join err_list c on a.Err_no=c.Err_no
where a.list_no=list_no ORDER BY b.razdSPID,c.err_no;
#void			TList_Editor::ShowData			(size_t row)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_list_data` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_list_data`(list_no bigint unsigned)
BEGIN
	#Routine body goes here...
/*
получаем список узлов входящих в список напрямую
*/
	select eid from prymary_entry a where a.List_no=list_no; 
#void			TList_Editor::ShowData(size_t row)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_list_Entries` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_list_Entries`(list_no bigint unsigned)
BEGIN
	#Routine body goes here...
/*получение списка входящих по всему листу обработки*/
declare lvl int;
drop TEMPORARY table if EXISTS res;
drop TEMPORARY table if EXISTS t_res;
create TEMPORARY table if not EXISTS res(
	eidp  bigint unsigned ,
	eidc	bigint unsigned not NULL,
	id		int unsigned not NULL,
	idp		int unsigned,
	kol		double not NULL,
	Active SMALLINT not null,
	lvl int not null,
	key `eidc`(`eidc`),
	key `eidp`(`eidp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
CREATE TEMPORARY TABLE IF NOT EXISTS t_res as select * from res where 0;
#подготовка
insert into res 
	select a.eidp,a.eidc,a.idc,a.idp,a.kol,a.active,0 from entries a join prymary_entry b on a.eidc=b.eid where b.List_no=list_no;
set lvl=0;
#развертка
while EXISTS (select eidc from res where res.lvl=lvl)do
  TRUNCATE TABLE t_res; 
  insert into `t_res` select * from res where res.lvl=lvl;
	insert into res #вариант с джоинами
			(
			select 
				b.eidc as eidp,
				a.eidc as eidc,
				a.idc as id,
				a.idp	as idp,
				a.kol as kol,
				a.active as active,
				lvl+1 as lvl
			from `entries` a 
			join `t_res` b on a.eidp=b.eidc and b.lvl=lvl
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;
create TEMPORARY TABLE if not EXISTS output as select * from res order by lvl;

drop TEMPORARY table if EXISTS res;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_node` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_node`(eid bigint unsigned)
BEGIN
	#Routine body goes here...
/*получение данных об узлах первого уровня и обновление данных в узлах*/

call reverse_entries(eid);
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.eid from output a where a.eidp is null;#получение id 
DROP TEMPORARY TABLE if EXISTS tmp;

call Get_Entries(@id);
drop temporary TABLE if EXISTS prep_kol;
CREATE TEMPORARY table if not EXISTS prep_kol as 
	select a.id,sum(a.kol) kol from output a group by a.id;
drop temporary TABLE if EXISTS output;

select 
if (a.idp is not null,a.idp,0)idp,
a.idc,
if (c.obd is not null,c.obd,'') obu,
c1.obd obd,
c1.namd `Name`,
c1.razdSPID razdSPID,
if (c2.Razdname is not null,c2.Razdname,'')	SpRazdName,
if (b.kol is not null,b.kol,0) sp_kol,
a.kol abs_kol,
a1.kol all_kol,
a.eidc,
if (a.eidp is not null,a.eidp,0)eidp,
a.active,
if (d.snameei is not null,d.snameei,0) ei 
from entries a 
join prep_kol a1 on a1.id=a.idc
left join constructions.det_tree b on a.idp=b.idparent and a.idc=b.idchild
left join constructions.det_names c on a.idp=c.id
join constructions.det_names c1 on a.idc=c1.id
left join administration.sprazd c2 on c2.RazdID=c1.razdSPID
left join catalogs.dimensionality d on d.kodei=a.ei
where a.eidc=eid;

drop temporary TABLE if EXISTS prep_kol;
#Tree_data::Update()
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `List_modifi_mark` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `List_modifi_mark`(list_no bigint unsigned,user int)
BEGIN
	#Routine body goes here...
# ставит метку изменения по ид и ид пользователя
	update lists a,administration.logins b 
		set a.UpdateUser=b.LogIn, a.UpdateDate=CURRENT_TIMESTAMP
		where a.List_No=list_no and b.LogID=user;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `reCalk_kol` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `reCalk_kol`(eid bigint unsigned,kol double, refresh tinyint,list_no bigint unsigned,user int unsigned)
BEGIN
	#Routine body goes here...
/*пересчет количества у входящих относительно узла*/
declare lvl int;

drop TEMPORARY table if EXISTS t_out;

set lvl=0;
case refresh
	when 0 THEN 
		BEGIN#персчет
			drop TEMPORARY table if EXISTS tmp;
			call Get_Entries(eid);
			Create TEMPORARY table if NOT EXISTS t_out as select * from output where 0;
			set @top_lvl=0;#получаем максимальный уровень вложения
			Create TEMPORARY table if NOT EXISTS tmp as SELECT @top_lvl:=max(a.lvl) from output a;
			drop TEMPORARY table if EXISTS tmp;

			#обратный пересчет количества
			while exists (select lvl from output a where a.lvl=@top_lvl) DO

				TRUNCATE t_out;
				insert into t_out select * from output a where a.lvl=@top_lvl-1;
				update output a join t_out b on a.eidp=b.eidc set a.kol=a.kol/b.kol where a.lvl=@top_lvl;
			set	@top_lvl=@top_lvl-1;
			end while;
			#установка нового количества базового узла
			update output a set a.kol=kol where a.lvl=0;
			#пересчет количества
			set lvl=0;
			while exists (select lvl from output a where a.lvl=lvl) DO
				TRUNCATE t_out;
				insert into t_out select * from output a where a.lvl=lvl-1;
				update output a join t_out b on a.eidp=b.eidc set a.kol=a.kol*b.kol where a.lvl=lvl;
			set	lvl=lvl+1;
			end while;

			#вывод результата
			update entries a join output b on a.eidc=b.eidc and (a.eidp=b.eidp or a.eidp is null) set a.kol=round(b.kol,3);
		END;
	when 1 THEN
		BEGIN	#сборос на изначальные данные
			
			call Get_Entries(eid);
			update output a left join constructions.det_tree b on a.id=b.idchild and a.idp=b.idparent
				set a.kol=if (b.kol is null and a.idp is null,1,b.kol);

			drop TEMPORARY table if EXISTS t_out;
			Create TEMPORARY table if NOT EXISTS t_out as select * from output;

			while exists (select lvl from output a where a.lvl=lvl) DO
				update output a join t_out b on a.eidp=b.eidc set a.kol=a.kol*b.kol where a.lvl=lvl;
			set	lvl=lvl+1;
			end while;

			update entries a join output b on a.eidc=b.eidc and (a.eidp=b.eidp or a.eidp is null) set a.kol=b.kol;
		END;
END CASE;
call list_modifi_mark(list_no,user);

drop TEMPORARY table if EXISTS t_out;
drop TEMPORARY table if EXISTS output;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Reverse_Entries` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Reverse_Entries`(eid bigint unsigned)
BEGIN
	#Routine body goes here...
declare lvl int;
set lvl=0;
DROP TEMPORARY TABLE IF EXISTS res;
DROP TEMPORARY TABLE IF EXISTS t_res;

CREATE TEMPORARY TABLE IF NOT EXISTS res
(
eid BIGINT UNSIGNED,
eidp BIGINT UNSIGNED,
lvl int,
key `eid`(`eid`),
key `eidp`(`eidp`)
)ENGINE=MYISAM;
CREATE TEMPORARY TABLE IF NOT EXISTS t_res as select * from res where 0;
insert into res 
	SELECT eidc,eidp,lvl from entries a where a.eidc=eid;
WHILE EXISTS (select eid from res where res.lvl=lvl) do
	TRUNCATE table t_res;
	insert into `t_res` select * from res where res.lvl=lvl;
	insert into res (eid,eidp,lvl)
		select b.eidp,a.eidp,lvl+1 
						from entries a 
						join t_res b on a.eidc=b.eidp;
	set lvl=lvl+1;
end WHILE;
DROP TEMPORARY TABLE IF EXISTS output;
CREATE TEMPORARY TABLE IF NOT EXISTS output as select * from res a ORDER BY a.lvl;
DROP TEMPORARY TABLE IF EXISTS res;
DROP TEMPORARY TABLE IF EXISTS t_res;
#Del Entrace
#Get_Entrance_lvl
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Set_Active` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Set_Active`(eid bigint unsigned, active int(1), mass int(1),list_no bigint unsigned, user int unsigned)
BEGIN
	#Routine body goes here...
/*
установка активности на узел и все входящие
*/
CASE mass
	WHEN 0 THEN#единичная смена состояния
		BEGIN
				update entries a 	
				set a.active=active
				where a.eidc=eid;
		END;
	WHEN 1 THEN#массовая смена состояния
		BEGIN
			#получить список входящих
			call Get_entries(eid);
			#установить метку
			update entries a 
				join output b on a.eidc=b.eidc 	
				set a.active=active; 
			drop TEMPORARY table if EXISTS output;
		END;
END CASE;
/*поидее  list_no может быть вычеслен... но нахрен это надо если прога его уже знает???*/
call list_modifi_mark(list_no,user);
#Tree_data Set_active
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Set_list_block` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Set_list_block`(list_no bigint unsigned, _block tinyint(2), user_id int(11))
BEGIN
	#Routine body goes here...
	#проверить заблокированна ли деталь для пользователя
	#установить статус блокировки разблокировки
IF (EXISTS (select List_No from lists a 
						join administration.logins b on b.logid=user_id 
						where (a.User=b.login or a.User="") and a.List_No=list_no))
	THEN
		BEGIN	
			CASE _block
				when 0
					THEN
						BEGIN
							#сбросить блок
							update lists a, administration.logins b 
							set a.User=""
							where a.List_No=list_no and b.LogID=user_id and a.User=b.LogIN;
						END;
				when 1
					THEN
						BEGIN
							#поставить блок
							update lists a, administration.logins b 
							set a.User=b.LogIn  
							where a.List_No=list_no and b.LogID=user_id and a.User="";
						END;
			end CASE;
			select 0 as result;
		END;
	ELSE
		BEGIN
			#отсылаем метку блокировки
			select 1 as result;
		END;
end if;
#TList_Editor::Set_list_Block (TMenuItem *it,int row,bool free)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `test` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `test`(kol double,eid bigint unsigned)
BEGIN
	#Routine body goes here...
declare lvl int;

drop TEMPORARY table if EXISTS tmp;
drop TEMPORARY table if EXISTS t_out;

call Get_Entries(eid);

Create TEMPORARY table if NOT EXISTS t_out as select * from output where 0;

set @top_lvl=0;#получаем максимальный уровень вложения
Create TEMPORARY table if NOT EXISTS tmp as SELECT @top_lvl:=max(a.lvl) from output a;
drop TEMPORARY table if EXISTS tmp;

#обратный пересчет количества
select a.eidp,a.eidc,a.id,a.idp,a.kol,b.kol,a.lvl  from output a left join constructions.det_tree b on a.id=b.idchild and a.idp=b.idparent;# where a.kol!=b.kol; 

while exists (select lvl from output a where a.lvl=@top_lvl) DO

	TRUNCATE t_out;
	insert into t_out select * from output a where a.lvl=@top_lvl-1;
	update output a join t_out b on a.eidp=b.eidc set a.kol=a.kol/b.kol where a.lvl=@top_lvl;
set	@top_lvl=@top_lvl-1;
end while;
#установка нового количества базового узла
update output a set a.kol=kol where a.lvl=0;
#пересчет количества
set lvl=0;

while exists (select lvl from output a where a.lvl=lvl) DO
	TRUNCATE t_out;
	insert into t_out select * from output a where a.lvl=lvl-1;
	update output a join t_out b on a.eidp=b.eidc set a.kol=a.kol*b.kol where a.lvl=lvl;
set	lvl=lvl+1;
end while;

#вывод результата
select a.eidp,a.eidc,a.id,a.idp,round(a.kol,3),b.kol,a.lvl from output a left join constructions.det_tree b on a.id=b.idchild and a.idp=b.idparent; 

update entries a join output b on a.eidc=b.eidc and (a.eidp=b.eidp or a.eidp is null) set a.kol=round(b.kol,3);

drop TEMPORARY table if EXISTS t_out;
drop TEMPORARY table if EXISTS output;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `ToOasu` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `ToOasu`(list_no bigint unsigned)
BEGIN
	#Routine body goes here...
Drop TEMPORARY table if EXISTS Det_IDS;
Drop TEMPORARY TABLE IF EXISTS Tree_RowS;

call Get_list_Entries(list_no);
Create TEMPORARY TABLE IF NOT EXISTS Det_IDS as 
	select a.id,b.obd 
		from output a 
		join constructions.det_names b on a.id=b.id
		WHERE a.active!=0 
		group by a.id;

#nsi001 - спецификация

Create TEMPORARY TABLE IF NOT EXISTS Tree_RowS as 
	select a.id,a.idp,a.eidc,a.eidp ,
			b.obd 	obu,
			b1.obd 	obd,
			a1.ppp 	ppp,
			if (b2.pp is null, b1.pp,b2.pp) pp,
			a1.ei		ei,
			a1.kol	kol
		from output a 
		JOIN constructions.det_tree a1 on a.idp=a1.idparent and a.id=a1.idchild
		JOIN constructions.det_names b on a.idp = b.id
		JOIN constructions.det_names b1 on a.id = b1.id
		left join temporary_tables.nsi001 b2 on b2.obd=b1.obd and b2.obu=b.obd
		WHERE /*a.active!=0 and */(b1.razdSPID!=9 or b2.obd is not null)
		group by a.id,a.idp;

delete from oasu.nsi001 where (oasu.nsi001.obu,oasu.nsi001.obd)in (select a.obu,a.obd from Tree_RowS a);
insert into oasu.nsi001 (obu,obd,ppp,pp,ei,kol)
	select obu,obd,ppp,pp,ei,kol    #b2.pp вместо b1.pp
	from Tree_RowS a;

#nsi002 - Свойства детали
delete from oasu.nsi002 where obd in (select DISTINCT a.obd from Det_IDS a);
insert into oasu.nsi002 (obd,obm,ei,vz,kdz,masd,masz,nrm,razz)
	select 
	a.obd,
	if (d.obd is null,'000000',if (left(d.obd,9)='000000000' AND LENGTH(d.obd)=15,right(d.obd,6),'000000')) as obm,
	if (b.ei is not null,b.ei,'')as ei,
	if (b.vz is not null,b.vz,0),
	b.kdz,b.masd,b.masz,b.nrm,UPPER(left(b.razz,30)) 
	from Det_IDS a
	join technologic.det_info b on a.id=b.id 
	left join constructions.det_names d on b.obmid=d.id
	order by a.obd,d.obd;

#nsi003 - Наименования
delete from oasu.nsi003 where obd in (select DISTINCT a.obd from Det_IDS a);
insert into oasu.nsi003 (obd,namd,rsp) 
	select a.obd,LEFT(UPPER(trim(b.namd)),70)as namd,b.razdSPID 
	from Det_IDS a 
	join constructions.det_names b on a.id=b.id
	left join sklad.materials c on c.obmid=a.id
	where c.obmid is null;
#nsi004
delete from oasu.nsi004 where obd in (select DISTINCT a.obd from Det_IDS a);
insert into oasu.nsi004  (OBD,CEU,OPR,OBO,KSHT,PROF,KROP,RR,KOLOD,EN,KTS,KVN,TPZ,TSHT)
	select a.OBD,concat(c.CEx,c.utch) as ceu,c.OPR,c.OBOID,d.KSHT,d.PROF,d.KROP,d.RR,d.KOLOD,if (d.EN='1','01',d.en),d.KTS,d.KVN,d.TPZ,d.TSHT
	from Det_IDS a
	join technologic.operation_list c on c.id=a.id
	join technologic.operation_norms d on d.OpUUID=c.OpUUID
	order by a.obd,c.opr,d.prof,d.rr;
#nsi005
delete from oasu.nsi005 where obd in (select DISTINCT a.obd from Det_IDS a);
insert into oasu.nsi005 (obd,napr)
	select a.obd,b.napr
	from Det_IDS a
	join technologic.det_info b on b.id=a.id
	left join sklad.materials c on c.obmid=a.id
	where c.obmid is null and trim(b.napr)!='' ORDER BY a.obd;
#nsi006
delete from oasu.nsi006 where obd in (select DISTINCT a.obd from Det_IDS a);
insert into oasu.nsi006 (zaka,obd) 
	select b2.zakaz,c.obd 
	from prymary_entry a
	join entries a1 on a.eid=a1.eidc
	join market.zakaz b on b.id=a1.idc
	join market.zakaz b1 on b1.zakaz_id=b.zakaz_id
  join market.Orders b2 on b1.zakaz_id = b2.zakaz_id
	join constructions.det_names c on b1.id=c.id  
	where a.list_no=list_no group by b2.zakaz,c.obd ;
#nsi010
/*delete from oasu.nsi010 where obu in (select DISTINCT a.obd from Det_IDS a);
insert into oasu.nsi010 (obu,obm,ei,nrm)
	select b.obd,RIGHT(b1.obd,6),a1.ei,a1.kol 
from output a
join constructions.det_tree a1 on a.id=a1.idchild and a.idp=a1.idparent 
join constructions.det_names b on a.idp = b.id
join constructions.det_names b1 on a.id=b1.id
where b1.razdSPID=9 and left(b1.obd,9)='000000000'  order by b.obd,b1.obd;*/

#Senden Dets 
insert into oasu.sended_dets (id,obd) 
	select a.id,a.obd from Det_IDS a
	left JOIN oasu.sended_dets b on a.id=b.id 
	where b.id is null;

call oasu.CheckChenges();

UPDATE constructions.det_names a join Det_IDS b on a.id=b.id set a.state=4;# отправка в архив;

Drop TEMPORARY table if EXISTS Det_IDS;
Drop TEMPORARY TABLE IF EXISTS Tree_RowS;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `TurnToNextStep` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `TurnToNextStep`(list_no bigint unsigned,user int)
BEGIN
	#Routine body goes here...
#выяснение следующего состояния, в зависиомости от состояния выполнить процедуру 
set @func="";
set @nstate=0;
DROP TEMPORARY TABLE IF EXISTS tmp;
CREATE TEMPORARY TABLE IF NOT EXISTS tmp as
select @func:=b.Function,@nstate:=b.Nstate  from lists a 
join states_tree b on a.Type=b.type and a.State_id=b.CState;
DROP TEMPORARY TABLE IF EXISTS tmp;
#select @_func,@nstate;
if @nstate!=0
	THEN
		BEGIN
				if @func!="" 
					then 
						BEGIN
							set @_sql=concat("Call ",@func,"(",list_no,")");
							PREPARE init from @_sql;
								#select @_sql;
							EXECUTE init;
						END;
				end if;
				update lists a set a.State_id=@nstate where a.List_No=list_no;
				call List_modifi_mark(list_no,user);
		END;
end if;
#void __fastcall TList_Editor::Next_Step_Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `sklad`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `sklad` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `sklad`;

--
-- Dumping events for database 'sklad'
--

--
-- Dumping routines for database 'sklad'
--
/*!50003 DROP PROCEDURE IF EXISTS `Get_Conturs` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Conturs`()
BEGIN
	#Routine body goes here...
	select Countur_name from conturs;
#void TwndEntarseMaterial::init (void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Material` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Material`(obm text)
BEGIN
	#Routine body goes here...
select 
if (c.kodei is not null,c.kodei,'0')as ei,
if (c.snameei is not null,c.snameei,"")as einame,
if (a.prma is null and a.gopr is null,if (a.nama is null and a.goma is null,b.namd,a.nama),a.prma)as l1,
if (a.prma is null and a.gopr is null,"",a.gopr)as l3,
if (a.prma is null and a.gopr is null,"",trim(CONCAT(a.nama,' ',a.goma)))as l4

from constructions.det_names b
left join materials a on a.obmid=b.id
left join catalogs.dimensionality c on c.kodei=eic
where b.obd=obm;
#void __fastcall TTechWnd::obmChange(TObject *Sender)
#void	SpRow::Set_ei		(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `save_tmp_material` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `save_tmp_material`(Userid int(11) ,obd varchar(100),nama varchar(70),goma varchar(40),prma varchar(45),gopr varchar(40),eic char(3))
BEGIN
	#Routine body goes here...
insert into constructions.det_names (obd,namd,pp,razdSPID,state,base,CreateDate,CreateUser,UpdateDate,UpdateUser)
select obd,CONCAT(trim(nama),' ',trim(goma),' ',trim(prma),' ',trim(gopr)),7,4,"mysql",CURRENT_TIMESTAMP(),a.LogIn,CURRENT_TIMESTAMP(),a.LogIn 
from administration.logins a where a.logID=Userid;
insert into materials (obmid,eic,nama,goma,prma,gopr)
select a.id,eic,nama,goma,prma,gopr from constructions.det_names a where a.obd=obd;
#void __fastcall TMater_add::BitBtn1Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Update`()
BEGIN
	#Routine body goes here...
delete from materials;
insert into materials (obmid,eic,nama,goma,prma,gopr,ves,eiv,sklad,bs,ss,cena)
SELECT b.id,c.kodei,trim(a.nama),trim(a.goma),trim(a.prma),trim(a.gopr),a.ves,d.kodei,a.sklad,a.bs,a.ss,a.cena from temporary_tables.nsi032 a
join constructions.det_names b on b.obd=CONCAT("000000000",a.obm)
left join catalogs.dimensionality c on a.eic=c.kodei
left join catalogs.dimensionality d on a.eiv=d.kodei;

update `materials` set goma=REPLACE(goma,' ',''),gopr=REPLACE(gopr,' ','');
update `materials` set goma=REPLACE(goma,'АТК','АТК '),gopr=REPLACE(gopr,'АТК','АТК ');
update `materials` set goma=REPLACE(goma,'ТУ','ТУ '),gopr=REPLACE(gopr,'ТУ','ТУ ');
update `materials` set goma=REPLACE(goma,'ОСТ','ОСТ '),gopr=REPLACE(gopr,'ОСТ','ОСТ ');
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `technologic`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `technologic` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `technologic`;

--
-- Dumping events for database 'technologic'
--

--
-- Dumping routines for database 'technologic'
--
/*!50003 DROP PROCEDURE IF EXISTS `convert_old_base` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `convert_old_base`()
BEGIN
	#Routine body goes here...
#предварительная чистка базы
delete from det_info;
alter table operation_list AUTO_INCREMENT=1;
#1 перенос det_info
insert into det_info (id,ei,masd,obmid,vz,kdz,masz,nrm,razz,pm,napr,CreateUser,CreateDate,ChangeUser,ChangeDate,base)
select b.id,d.kodei,a.masd,c.id,f.kod,a.kdz,a.masz,a.nrm,trim(a.razz),trim(a.pm),a.napr,
if(e.fam is not null,concat(trim(fam),' ',left(trim(ima),1),'. ',left(trim(otc),1),'.'),''),
a.dnte,
if(e.fam is not null,concat(trim(fam),' ',left(trim(ima),1),'. ',left(trim(otc),1),'.'),''),
a.dnte,'oasu'  
from temporary_tables.det_info a
join constructions.det_names b on a.obd=b.obd
left join constructions.det_names c on CONCAT('000000000',a.obm)=c.obd
left join catalogs.dimensionality d on a.ei=d.kodei
left join temporary_tables.ogts01 e on a.liteh=e.linn
left join billets.vz_tree f on a.vz=f.kod;

update det_info a 
join constructions.det_names c on a.id=c.id
join temporary_tables.detinfo_new b on b.obd=c.obd set a.base='mysql';
#2 перенос operation_list 
insert into operation_list (id,cex,utch,opr,oboID,ioht,stro,ktar,ok69,CreateUser,UpdateUser,CreateDate,UpdateDate,base)
select b.id,left(a.ceu,2),RIGHT(a.ceu,2),a.opr,d.oboID,trim(a.ioht),trim(a.stro),a.ktar,a.ok69,
if(e.fam is not null,concat(trim(fam),' ',left(trim(ima),1),'. ',left(trim(otc),1),'.'),''),
if(e.fam is not null,concat(trim(fam),' ',left(trim(ima),1),'. ',left(trim(otc),1),'.'),''),
dnte,
dnte,'oasu'
from temporary_tables.operation_list a
join constructions.det_names b on a.obd=b.obd
left join equipment.obor_list d on a.obo=d.oboID
left join temporary_tables.ogts01 e on a.liteh=e.linn;
update operation_list a join equipment.obor_operations b on a.oboID=b.oboID set a.oprid=b.operID;
update operation_list a
join constructions.det_names b on b.id=a.id
join temporary_tables.operations_new c on c.obd=b.obd and c.ceu=CONCAT(a.cex,a.utch) and c.opr=a.opr and c.obo=a.oboID
set a.base='mysql';
#3 перенос operation_norms
insert into operation_norms (OpUUID,ksht,prof,krop,rr,kolod,EN,kts,kvn,tpz,ttp,tsht,CreateUser,UpdateUser,CreateDate,UpdateDate,base)
select b.OpUUID,a.ksht,a.prof,a.krop,a.rr,a.kolod,a.EN,a.kts,a.kvn,a.tpz,trim(a.ttp),a.tsht,
if(e.fam is not null,concat(trim(fam),' ',left(trim(ima),1),'. ',left(trim(otc),1),'.'),''),
if(e.fam is not null,concat(trim(fam),' ',left(trim(ima),1),'. ',left(trim(otc),1),'.'),''),
a.dnno,
a.dnno,'oasu'  
from temporary_tables.operation_norms a
join constructions.det_names a1 on a.obd=a1.obd
join operation_list b on a1.id=b.id and a.ceu=CONCAT(b.cex,b.utch) and a.opr=b.opr and a.obo=b.oboID
left join temporary_tables.ogts01 e on a.linor=e.linn;

update operation_norms a 
join operation_list b on b.OpUUID=a.OpUUID
join constructions.det_names c on c.id=b.id
join temporary_tables.operations_new d on d.obd=c.obd and d.ceu=CONCAT(b.cex,b.utch) and d.opr=b.opr and d.obo=b.oboID
set a.base='mysql';
#4 перенос perexod
insert into perexod (OpUUID,strk,tpe,base)
select b.OpUUID,a.strk,trim(a.tpe),'oasu'  
from temporary_tables.perexod a
join constructions.det_names a1 on a.obd=a1.obd
join operation_list b on a1.id=b.id and a.ceu=CONCAT(b.cex,b.utch) and a.opr=b.opr and a.obo=b.oboID;

update perexod a 
join operation_list b on b.OpUUID=a.OpUUID
join constructions.det_names c on c.id=b.id
join temporary_tables.perexod_new d on d.obd=c.obd and d.ceu=CONCAT(b.cex,b.utch) and d.opr=b.opr and d.obo=b.oboID
set a.base='mysql';
#5 перенос instrum
insert into instrum (OpUUID,strk,nain,koin,base)
select b.OpUUID,a.strk,trim(a.nain),trim(a.koin),'oasu'  
from temporary_tables.instrum a
join constructions.det_names a1 on a.obd=a1.obd
join operation_list b on a1.id=b.id and a.ceu=CONCAT(b.cex,b.utch) and a.opr=b.opr and a.obo=b.oboID;

update instrum a 
join operation_list b on b.OpUUID=a.OpUUID
join constructions.det_names c on c.id=b.id
join temporary_tables.instrum_new d on d.obd=c.obd and d.ceu=CONCAT(b.cex,b.utch) and d.opr=b.opr and d.obo=b.oboID
set a.base='mysql';

#исправление ошибок
create temporary table if not EXISTS defect_rows
(
OpUUID BIGINT(20) UNSIGNED,
key OpUUID (OpUUID)
) as select OpUUID from perexod where strk='0';

update perexod a join defect_rows b on a.opuuid=b.opuuid set a.strk=a.strk+1;
drop TEMPORARY table if EXISTS defect_rows;

create temporary table if not EXISTS defect_rows
(
OpUUID BIGINT(20) UNSIGNED,
key OpUUID (OpUUID)
) as select OpUUID from instrum where strk='0';

update instrum a join defect_rows b on a.opuuid=b.opuuid set a.strk=a.strk+1;
drop TEMPORARY table if EXISTS defect_rows;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetDetInfo` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `GetDetInfo`(DetID int(11) unsigned)
    COMMENT 'дописать'
BEGIN
	#Routine body goes here...
select
  a.id,
	if (a.ei is not null,a.ei,0) as ei,
	if (a.ei is not null,b.snameei,'') as eiName,
  a.masd,
	if (a.obmid is not null,d.obd,"") as obm,
	if (a.obmid is not null,a.obmid,0) as obmid,
	if (a.vz is not null,a.vz,0) as vz,
	if (a.vz is not null,c.`name`,"") as vzName,
  a.kdz,
  a.masz,
  a.nrm,
  trim(a.razz) as razz,
  trim(a.pm) as pm,
  a.napr,
  a.CreateUser,
  a.CreateDate,
  a.ChangeUser,
  a.ChangeDate
from det_info a 
	left join catalogs.dimensionality b on a.ei=b.kodei
	left join billets.vz_tree c on a.vz=c.kod
	left join constructions.det_names d on d.id=a.obmid 
where a.id=DetID;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetInstrum` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `GetInstrum`(OpID int)
    COMMENT 'Загрузка инструмента'
BEGIN
	#Routine body goes here...
select
a.OpuuID,
a.strk,
a.nain,
a.koin
from instrum a 
where a.OpuuID=OpID ORDER BY strk;
#void OperRow::Load_Oper_Data (void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetNorms` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `GetNorms`(OpID int)
    COMMENT 'Загрузка норм'
BEGIN
	#Routine body goes here...
select
a.OpuuID,
a.kolod,
a.prof,
a.krop,
a.rr,
a.en,
a.kts,
a.kvn,
a.ttp,
a.ksht,
a.tpz,
a.tsht,
a.CreateUser,
a.UpdateUser,
a.CreateDate,
a.UpdateDate
from operation_norms a 
where a.OpuuID=OpID ORDER BY a.prof,a.rr;
#void OperRow::Load_Oper_Data (void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetOperations` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `GetOperations`(DetID int)
    COMMENT 'дописать\r\nзагрузка операций'
BEGIN
	#Routine body goes here...
select
a.id,
a.OpUUID,
a.cex,
a.utch,
a.opr,
if (a.oboID is not null,a.oboID,"") as oboID,
a.ioht,
if (a.stro is not null and a.stro!="нет"and trim(a.stro)!="",trim(a.stro),"")as stro,
a.ktar,
if (c.obta is not null,CONCAT('Тара ',trim(c.obta)),"")as tara,
a.ok69,
if (b.te69 is not null,trim(b.te69),"") as control,
a.CreateUser,
a.UpdateUser,
a.CreateDate,
a.UpdateDate,
if (a.oprid is not null,if (e1.name is not null,trim(e1.name),''),'') as OprName,
if (a.oprid is not null,a.oprid,'') as OprCode,
if (f.name is not null,trim(f.name),"") as OboName
from operation_list a 
left join catalogs.control b on a.ok69=b.ko69
left join catalogs.tara c on a.ktar=c.kota
left join equipment.obor_list f on f.oboid=a.oboid
left join equipment.opr_names e1 on e1.oprID=a.oprid

where a.id=DetID ORDER BY opr;
#void DtInfo::LoadData(int _id)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetPerexods` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `GetPerexods`(OpID int)
    COMMENT 'загрузка переходов'
BEGIN
	#Routine body goes here...
select
a.OpuuID,
a.strk,
a.tpe
from perexod a 
where a.OpuuID=OpID ORDER BY a.strk;
#void OperRow::Load_Oper_Data (void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_New_OPUUID` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_New_OPUUID`()
BEGIN
	#Routine body goes here...
SELECT max(opUUID)+1 as OpUUID from operation_list;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `TechDel` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `TechDel`(ids text)
    COMMENT 'написать, функция пустая'
BEGIN
	#Routine body goes here...
set @sq=CONCAT('delete from operation_list
where id in (',ids,')');
prepare init from @sq;
EXECUTE init;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `tmp` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `tmp`(DetID int)
    COMMENT 'дописать\r\nзагрузка операций'
BEGIN
	#Routine body goes here...
select
*
from operation_list a 
left join catalogs.control b on a.ok69=b.ko69
left join catalogs.tara c on a.ktar=c.kota
left join equipment.obor_list f on f.oboid=a.oboid
left join equipment.opr_names e1 on e1.oprID=a.oprid

where a.id=DetID ORDER BY opr;
#void DtInfo::LoadData(int _id)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Update` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `Update`()
BEGIN
	#Routine body goes here...
#1 перенос det_info
	#удаление повторяющихся обозначений
drop TEMPORARY table if EXISTS tmp; 
create temporary table if not EXISTS tmp as select * from temporary_tables.nsi005 GROUP BY obd;
delete from temporary_tables.nsi005;
insert into temporary_tables.nsi005 select * from tmp; 
	#удаление записей которые более не используются на АСУ 
drop TEMPORARY table if EXISTS tmp;
	drop TEMPORARY table if EXISTS idt; 
	CREATE TEMPORARY table idt
	(
	id int(11)UNSIGNED,
	key id (id)
	) as 
	select b.id from det_info a
	join constructions.det_names b on a.id=b.id
	left join temporary_tables.nsi002 c on c.obd=b.obd 
	where b.obd is null and a.base='oasu';

	delete from det_info where id in (select id FROM idt);
	drop TEMPORARY table if EXISTS idt; 
	#обновление записей пришедших с АСУ
	update det_info a
	join constructions.det_names b on a.id=b.id
	join temporary_tables.nsi002 c on c.obd=b.obd
	left join catalogs.dimensionality d on c.ei=d.kodei
	left join billets.vz_tree e on c.vz=e.kod
	set a.ei=d.kodei,a.vz=e.kod,a.kdz=c.kdz,a.masd=c.masd,a.masz=c.masz,a.nrm=c.nrm,a.razz=c.razz,a.ChangeUser='upd',a.ChangeDate=CURRENT_TIMESTAMP()
	where a.base='oasu'and(a.ei!=d.kodei or a.vz!=e.kod or a.kdz!=c.kdz or a.masd!=c.masd or a.masz!=c.masz or a.nrm!=c.nrm or a.razz!=c.razz);
	#вставка новых записей
	insert into det_info (id,ei,masd,obmid,vz,kdz,masz,nrm,razz,napr,CreateUser,CreateDate,ChangeUser,ChangeDate,base)
	select b.id,d.kodei,a.masd,c.id,f.kod,a.kdz,a.masz,a.nrm,trim(a.razz),if (e.napr is not null,e.napr,''),
	'upd',
	CURRENT_TIMESTAMP(),
	'upd',
	CURRENT_TIMESTAMP(),'oasu'  
	from temporary_tables.nsi002 a
	join constructions.det_names b on a.obd=b.obd
	left join constructions.det_names c on CONCAT('000000000',a.obm)=c.obd
	left join catalogs.dimensionality d on a.ei=d.kodei
	join temporary_tables.nsi005 e on a.obd=e.obd
	left join billets.vz_tree f on a.vz=f.kod 
	left join det_info g on g.id=b.id
	where g.id is null;
	
#подготовка ис
drop TEMPORARY table if EXISTS tmp;
CREATE TEMPORARY TABLE if not EXISTS tmp
(#подготовка сводных данных 
	`obd` char(15) NOT NULL DEFAULT '',
	`cex` char(2) NOT NULL DEFAULT '',
	`utch` char(2) NOT NULL DEFAULT '',
	`opr` char(3) NOT NULL DEFAULT '',
	`obo` char(5) NOT NULL DEFAULT '',
	`ksht` double NOT NULL DEFAULT '0',
	`prof` char(4) NOT NULL DEFAULT '',
	`krop` char(1) NOT NULL DEFAULT '',
	`rr` char(1) NOT NULL DEFAULT '',
	`kolod` double NOT NULL DEFAULT '0',
	`en` char(2) NOT NULL DEFAULT '',
	`kts` char(2) NOT NULL DEFAULT '',
	`kvn` char(1) NOT NULL DEFAULT '',
	`tpz` double NOT NULL DEFAULT '0',
	`tsht` double NOT NULL DEFAULT '0',
	`ttp` char(10) NOT NULL DEFAULT '',
PRIMARY KEY (obd,cex,utch,opr,obo,prof,rr)
)ENGINE=MYISAM ;
insert into tmp
select obd,left(ceu,2),RIGHT(ceu,2),opr,obo,ksht,prof,krop,rr,kolod,en,kts,kvn,tpz,tsht,'' as ttp from temporary_tables.nsi004
GROUP BY obd,ceu,opr,obo,prof,rr;
insert into tmp 
select a.obd,left(a.ceu,2),RIGHT(a.ceu,2),a.opr,a.obo,a.ksht,a.prof,a.krop,a.rr,a.kolod,a.en,a.kts,a.kvn,a.tpz,a.tsht,trim(a.ttp) 
	from temporary_tables.nsi009 a
	left join temporary_tables.nsi004 b on a.obd=b.obd and a.ceu=b.ceu and a.opr=b.opr and a.obo=b.obo and a.prof=b.prof and a.rr=b.rr
	where b.obd is null
GROUP BY a.obd,a.ceu,a.opr,a.obo,a.prof,a.rr; 

DROP TEMPORARY TABLE IF EXISTS idMYSQL;
CREATE TEMPORARY TABLE IF NOT EXISTS idMYSQL
(#1 таблица с идентификаторами / обозначениями которые принадлежат асу (хотябы одна строка не из асу значит все технология не обновляется)
id int(11)UNSIGNED,
obd VARCHAR(100),
key id(id),
key obd(obd)
)ENGINE=MYISAM as 
Select b.id,b.obd from technologic.operation_list a 
join constructions.det_names b on a.id=b.id
where a.base='mysql' group by a.id;
 
DROP TEMPORARY TABLE IF EXISTS idASU;
CREATE TEMPORARY TABLE IF NOT EXISTS idASU
(#2 таблица с идентификаторми и обозначениями которые принадлежат асу (общая база с исключением того что было на этапе 1)
id int(11)UNSIGNED,
obd VARCHAR(100),
key id(id),
key obd(obd)
)ENGINE=MYISAM as 
Select b.id,b.obd from technologic.operation_list a 
join constructions.det_names b on a.id=b.id
left join idMYSQL c on c.id=a.id 
where c.id is null group by a.id;
#этапы обновления 
#1 удалить только те записи оторые имеют пометку асу и не встречаются в асу
	drop TEMPORARY table if EXISTS idt;  #список ключей для удаления
	CREATE TEMPORARY table idt
	(
	id int(11)UNSIGNED,
	opr VARCHAR(3) DEFAULT '',
	cex  CHAR(2) DEFAULT '',
	utch char(2) DEFAULT '', 
	obo VARCHAR(5) DEFAULT '',
	key id (id)
	)ENGINE=MYISAM as 
	select a.id,a.opr,a.cex,a.utch,a.oboID obo from operation_list a 
	join idASU b on a.id=b.id
	left join tmp c on b.obd=c.obd and a.opr=c.opr and a.cex=c.cex and a.utch=c.utch and a.oboID=c.obo
	where c.obd is null;
  delete from operation_list where (id,opr,cex,utch,oboid) in (select id,opr,cex,utch,obo FROM idt);
	drop TEMPORARY table if EXISTS idt;
#2 обновить записи которые имеют пометку асу 
	update operation_list a 
	join idASU b on a.id=b.id
	join tmp c on c.obd=b.obd and c.opr=a.opr
	left join equipment.obor_list d on c.obo=d.oboID
	set 
		a.cex=c.cex,
		a.utch=c.utch,
		a.oboID=if(d.oboid is null,a.oboID,c.obo),
		a.UpdateUser="upd",
		a.UpdateDate=CURRENT_TIMESTAMP()
	where a.cex!=c.cex or a.utch!=c.utch or a.oboID!=c.obo;

#3 вставить новые записи не имеющие отметку mysql
	insert into operation_list (id,cex,utch,opr,oboID,ioht,base,CreateUser,UpdateUser,CreateDate,UpdateDate)
	select b.id,a.cex,a.utch,a.opr,c.oboID,'',
	'oasu',
	'upd',
	'upd',
  CURRENT_TIMESTAMP(),
	CURRENT_TIMESTAMP()  
	from tmp a
	join constructions.det_names b on a.obd=b.obd
	left join equipment.obor_list c on c.oboID=a.OBO
	left join idMYSQL d on b.id=d.id  
	left join operation_list e on e.id=b.id and e.cex=a.cex and e.utch=a.utch and e.opr=a.opr and if (e.oboID is null,true,e.oboID=c.oboID)
	where d.id is null and e.id is null;

	update operation_list a join equipment.obor_operations b on a.oboID=b.oboID set a.oprid=b.operID where a.base='oasu';
#4 обновить нормы
	#обновление методом полной перезапии для асу меток и для вствленных операций
	delete from technologic.operation_norms where opuuid in #удаление ном технологий из асу и толькочто вставленных
		(
		select a.opuuid from operation_list a
		left join idMYSQL d on a.id=d.id
		where d.id is null
		);
	insert into operation_norms 
	(OpUUID,ksht,prof,krop,rr,kolod,EN,kts,kvn,tpz,ttp,tsht,base,CreateUser,UpdateUser,CreateDate,UpdateDate)

	select c.OpUUID,a.ksht,a.prof,a.krop,a.rr,a.kolod,a.EN,a.kts,a.kvn,a.tpz,a.ttp,a.tsht,'oasu','upd','upd',CURRENT_TIMESTAMP(),CURRENT_TIMESTAMP()
		from tmp a
		join constructions.det_names b on b.obd=a.obd
		join operation_list c on c.id=b.id and c.opr=a.opr and c.oboID=a.obo and a.cex=c.cex and a.utch=c.utch
		left join idMYSQL d on b.id=d.id
	where d.id is null; 

DROP TEMPORARY TABLE IF EXISTS idASU;
DROP TEMPORARY TABLE IF EXISTS idMYSQL;
drop TEMPORARY table if EXISTS tmp;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Current Database: `temporary_tables`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `temporary_tables` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `temporary_tables`;

--
-- Dumping events for database 'temporary_tables'
--

--
-- Dumping routines for database 'temporary_tables'
--
/*!50003 DROP PROCEDURE IF EXISTS `boiler_assemblies` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `boiler_assemblies`(obd text,kol int)
BEGIN  
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
set @id=0;
select @id:=a.id into @id from constructions.det_names a where a.obd=obd;#получение id 

Call constructions.GetAllUzel(@id);#получим состав и количество с учетом заказанных узлов

update constructions.output a set a.kol=a.kol*kol;

#сгруппировать данные по вхождениям по idp/idc для подсчета реального количества
DROP TEMPORARY TABLE IF EXISTS tmp1;
CREATE TEMPORARY TABLE IF NOT EXISTS tmp1 
(
idp BIGINT(21) UNSIGNED NOT NULL,
idc BIGINT(21) UNSIGNED NOT NULL,
kol double,
KEY `idp`(`idp`),
KEY `idc`(`idc`)
)ENGINE=MEMORY;
insert into tmp1 
select a.idp,a.idc,SUM(a.kol) 
from constructions.output a
group by a.idp,a.idc; 
#получить только узлы с операцией котельной сборки
DROP TEMPORARY TABLE IF EXISTS tmp2;
CREATE TEMPORARY TABLE IF NOT EXISTS tmp2 
(
idp BIGINT(21) UNSIGNED NOT NULL,
idc BIGINT(21) UNSIGNED NOT NULL,
kol double,
part tinyint(1),
KEY `idp`(`idp`),
KEY `idc`(`idc`)
)ENGINE=MEMORY;
insert into tmp2 
select a.idp,a.idc,a.kol,1 
from tmp1 a
join technologic.operation_list b on b.id=a.idp
where b.oprid in(19) 
group by a.idp,a.idc; 

DROP TEMPORARY TABLE IF EXISTS tmp3;
CREATE TEMPORARY TABLE IF NOT EXISTS tmp3 as
select idp from tmp2 group by idp;

DROP TEMPORARY TABLE IF EXISTS tmp4;
CREATE TEMPORARY TABLE IF NOT EXISTS tmp4 as
select a.idc idp,a.idc,sum(a.kol),0 
from tmp1 a 
join tmp3 b on b.idp=a.idc
group by a.idc;
 
insert into tmp2 select * from tmp4;

DROP TEMPORARY TABLE IF EXISTS tmp5;
CREATE TEMPORARY TABLE IF NOT EXISTS tmp5 
(
idp BIGINT(21) UNSIGNED NOT NULL,
idc BIGINT(21) UNSIGNED NOT NULL,
kol double,
part tinyint(1),
ed_trud double,
summ_trud double,
KEY `idp`(`idp`),
KEY `idc`(`idc`)
)ENGINE=MEMORY;
insert into tmp5(idp,idc,kol,part,ed_trud,summ_trud) 
select a.idp,a.idc,a.kol,a.part,sum(c.tsht+c.tpz/c.kolod),sum(c.tsht+c.tpz/c.kolod)*a.kol 
from tmp2 a
left join technologic.operation_list b on a.idc=b.id
left join technologic.operation_norms c on c.opuuid=b.opuuid
group by a.idp,a.idc;

select 
a.idp,a.idc,a.kol,a.ed_trud,a.summ_trud,a.part,
IFNULL(b.vz,'') vz,b.razz,b.pm,b.napr,b.masd,b.nrm,
c.obd,c.namd,
d.nama,d.goma,d.prma,d.gopr,d1.namd mat_name
from tmp5 a
join technologic.det_info b on a.idc=b.id 
join constructions.det_names c on c.id=a.idc 
left join sklad.materials d on d.obmid=b.obmid
left join constructions.det_names d1 on d1.id=b.obmid
order by idp,c.obd,part;



Drop TEMPORARY TABLE if EXISTS constructions.output;
DROP TEMPORARY TABLE IF EXISTS tmp1;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `bordereau_all` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `bordereau_all`(obd text, kol int)
BEGIN
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS itog;

set @id=0;
select @id:=a.id into @id from constructions.det_names a where a.obd=obd;#получение id 

call constructions.GetAllUzel(@id);#получение развертки заказа

update constructions.output a set a.kol=a.kol*kol;

CREATE TEMPORARY table itog as 
	select a.idc,SUM(a.kol) as kol 
	from constructions.output a 
	GROUP BY a.idc;

select b.obd as `Обозначение`,
if (b.namd is not null,b.namd,'') as `Наименование`,-- 22
if (a.kol is not null,a.kol,0) as `Кол-во`,
if (g.kodei is not null,g.kodei,'') as `Ед. изм.`,
if (c.masd is not null,c.masd,if (left(b.obd,9)='000000000',if (d.ves is not null,d.ves,0),0)) as `Масса детали`,--
if (e.obd is not null,e.obd,'') as obm,
if (g.snameei is not null,g.snameei,'') as snameei,
if (concat(d.nama,' ',d.prma) is not null,concat(trim(d.nama),' ',trim(d.prma)),if(e.namd is not null,e.namd,'')) as `Материал`,
if (c.vz is not null,c.vz,0) as `Код заготовки`,
if (c.kdz is not null,c.kdz,1) as `Кол-во дет. в заг.`,
if (c.masz is not null,c.masz,if (left(b.obd,9)='000000000',if (d.ves is not null,d.ves,0),0)) as `Масса заг.`,
if (c.razz is not null,c.razz,'') as `Размеры заг.`,
if (c.nrm is not null,c.nrm,if (left(b.obd,9)='000000000',if (d.ves is not null,d.ves,0),0)) as `Норма расхода`,
if (left(b.obd,9)='000000000'and d.sklad is not null,if (concat(trim(c.pm),' ',trim(c.napr))  is not null,
	trim(concat(trim(c.pm),' ',trim(c.napr),' ',trim(d.sklad))),trim(d.sklad)),
	if (concat(trim(c.pm),' ',trim(c.napr))  is not null,trim(concat(trim(c.pm),' ',trim(c.napr))),''))as `Рассцеховка`,
if (b.razdSPID is not NULL,b.razdSPID,5) as rsp,
if (b.obd=obd,0,if(b.razdspid in (5,6,7),1,if(left(b.obd,6)!=left(obd,6),2,3)))as ochered

from itog a
join constructions.det_names b on a.idc=b.id 
left join technologic.det_info c on a.idc=c.id
left JOIN	sklad.materials d on d.obmid=c.obmid
left join constructions.det_names e on e.id=c.obmid
left join catalogs.dimensionality g on g.kodei=c.ei
order BY /*rsp,a.lvl,*/ochered,b.obd;


Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS itog;
#void cReports::Mat_Ved_Komplect    (String obd,String zak,int kol)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `bordereau_cooperation` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `bordereau_cooperation`(obd text, kol int)
BEGIN
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS itog;
Drop TEMPORARY TABLE if EXISTS opr_l_filter;
set @id=0;
select @id:=a.id into @id from constructions.det_names a where a.obd=obd;#получение id 

call constructions.GetAllUzel(@id);#получение развертки заказа

update constructions.output a set a.kol=a.kol*kol;

CREATE TEMPORARY table itog as 
	select a.idc,SUM(a.kol)as kol 
	from constructions.output a
	GROUP BY a.idc;

create TEMPORARY table if not exists opr_l_filter
as SELECT a.idc
		from itog a 
		JOIN technologic.operation_list b on a.idc = b.id and b.cex='16' and b.utch!='25' and b.utch!='63'#фильтрация по операциям
		GROUP BY a.idc;

select b.obd as `Обозначение`,
if (b.namd is not null,b.namd,'') as `Наименование`,
if (a.kol is not null,a.kol,0) as `Кол-во`,
if (c.ei is not null,c.ei,'') as `Ед. изм.`,
if (c.masd is not null,c.masd,0) as `Масса детали`,
if (e.obd is not null,e.obd,'') as obm,
if (g.snameei is not null,snameei,'') as snameei,
if (concat(d.nama,' ',d.prma) is not null,concat(trim(d.nama),' ',trim(d.prma)),if(e.namd is not null,e.namd,'')) as `Материал`,
if (c.vz is not null,c.vz,0) as `Код заготовки`,
if (c.kdz is not null,c.kdz,0) as `Кол-во дет. в заг.`,
if (c.masz is not null,c.masz,0) as `Масса заг.`,
if (c.razz is not null,c.razz,'') as `Размеры заг.`,
if (c.nrm is not null,c.nrm,0) as `Норма расхода`,
if (c.pm is not null,c.pm,'') as `Рассцеховка`
from itog a 
join constructions.det_names b on a.idc=b.id 
left join technologic.det_info c on a.idc=c.id
left JOIN	sklad.materials d on d.obmid=c.obmid
left join constructions.det_names e on e.id=c.obmid
left join catalogs.dimensionality g on g.kodei=c.ei
where b.id in (select idc from opr_l_filter) 
			or c.vz in ('144','146','141','142','126','121','122','589','716','742','744','241','242') #фильтрация по виду заготовки
order BY b.obd;

Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS itog;
Drop TEMPORARY TABLE if EXISTS opr_l_filter;
#void cReports::Mat_Ved_Komplect    (String obd,String zak,int kol)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `bordereau_litho` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `bordereau_litho`(obd varchar(100), kol int)
BEGIN
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS itog;
set @id=0;
select @id:=a.id into @id from constructions.det_names a where a.obd=obd;#получение id 

call constructions.GetAllUzel(@id);#получение развертки заказа

update constructions.output a set a.kol=a.kol*kol;

CREATE TEMPORARY table itog as 
	select a.idc,SUM(a.kol)as kol 
	from constructions.output a
	GROUP BY a.idc;

select b.obd as `Обозначение`,
if (b.namd is not null,b.namd,'') as `Наименование`,
if (a.kol is not null,a.kol,0) as `Кол-во`,
if (c.ei is not null,c.ei,'') as `Ед. изм.`,
if (c.masd is not null,c.masd,0) as `Масса детали`,
if (e.obd is not null,e.obd,'') as obm,
if (g.snameei is not null,snameei,'') as snameei,
if (concat(d.nama,' ',d.prma) is not null,concat(trim(d.nama),' ',trim(d.prma)),if(e.namd is not null,e.namd,'')) as `Материал`,
if (c.vz is not null,c.vz,0) as `Код заготовки`,
if (c.kdz is not null,c.kdz,0) as `Кол-во дет. в заг.`,
if (c.masz is not null,c.masz,0) as `Масса заг.`,
if (c.razz is not null,c.razz,'') as `Размеры заг.`,
if (c.nrm is not null,c.nrm,0) as `Норма расхода`,
if (c.pm is not null,c.pm,'') as `Рассцеховка`
from itog a
join constructions.det_names b on a.idc=b.id 
left join technologic.det_info c on a.idc=c.id
left JOIN	sklad.materials d on d.obmid=c.obmid
left join constructions.det_names e on e.id=c.obmid
left join catalogs.dimensionality g on g.kodei=c.ei
where c.vz like '1__'
order BY b.obd;

Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS itog;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `bordereau_stamping` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `bordereau_stamping`(obd varchar(100), kol int)
BEGIN
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS itog;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

call constructions.GetAllUzel(@id);#получение развертки заказа

update constructions.output a set a.kol=a.kol*kol;

CREATE TEMPORARY table itog as 
	select a.idc,SUM(a.kol)as kol 
	from constructions.output a
	GROUP BY a.idc;

select b.obd as `Обозначение`,
if (b.namd is not null,b.namd,'') as `Наименование`,
if (a.kol is not null,a.kol,0) as `Кол-во`,
if (c.ei is not null,c.ei,'') as `Ед. изм.`,
if (c.masd is not null,c.masd,0) as `Масса детали`,
if (e.obd is not null,e.obd,'') as obm,
if (g.snameei is not null,snameei,'') as snameei,
if (concat(d.nama,' ',d.prma) is not null,concat(trim(d.nama),' ',trim(d.prma)),if(e.namd is not null,e.namd,'')) as `Материал`,
if (c.vz is not null,c.vz,0) as `Код заготовки`,
if (c.kdz is not null,c.kdz,0) as `Кол-во дет. в заг.`,
if (c.masz is not null,c.masz,0) as `Масса заг.`,
if (c.razz is not null,c.razz,'') as `Размеры заг.`,
if (c.nrm is not null,c.nrm,0) as `Норма расхода`,
if (c.pm is not null,c.pm,'') as `Рассцеховка`
from itog a
join constructions.det_names b on a.idc=b.id 
left join technologic.det_info c on a.idc=c.id
left JOIN	sklad.materials d on d.obmid=c.obmid
left join constructions.det_names e on e.id=c.obmid
left join catalogs.dimensionality g on g.kodei=c.ei
where c.vz like '21_' or c.vz like '24_'
order BY b.obd;

Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS itog;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `det_inside` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `det_inside`(obd text)
BEGIN
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

call constructions.GetAllUzel(@id);

select b.obd,b.namd,b1.obd as obu,a.kol as kol,b.razdSPID 
from constructions.output a 
join constructions.det_names b on a.idc=b.id
join constructions.det_names b1 on a.idp=b1.id
order by razdSPID,b.obd;


Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
#bool cReports::CreateReport(int type, String param)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `det_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `det_list`(obd text)
BEGIN
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

call constructions.GetAllUzel(@id);

select if (c.obd is not null,c.obd,"")as obu,b.obd as obd,b.namd,a.kol,a.lvl,b.razdSPID as rsp 
	from constructions.output a 
	join constructions.det_names b on a.idc=b.id
	left join constructions.det_names c on a.idp=c.id
	order BY a.lvl,c.obd,rsp,b.obd;
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
#bool cReports::CreateReport(int type, String param)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Materials_Order` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Materials_Order`(obd text,kol int,cex varchar(2), utch varchar(2))
BEGIN
#строка с головным изделием не обрабатывается 
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;


set @id=0;
select a.id into @id from constructions.det_names a where a.obd=obd;#получение id 

#этап 1 получить развертку узла
Call constructions.GetAllUzel(@id);#получим состав и количество с учетом заказанных узлов
#этап 2 произвести правку количества
update constructions.output a set a.kol=a.kol*kol;#правка количества
#этап 3 отобрать детали изготавливаемые на участке
Drop TEMPORARY TABLE if EXISTS tmp;
CREATE TEMPORARY TABLE tmp as select a.cex,a.utch,min(a.opr),a.id from technologic.operation_list a 
	join constructions.output b on a.id = b.idc
	GROUP BY a.id having a.cex=cex and a.utch=utch;
#этап 4 отобрать материалы и комплектующие по сп необходимые для изготовления детали
Drop TEMPORARY TABLE if EXISTS tmp_kompl;
CREATE TEMPORARY TABLE tmp_kompl as
select a.idp,a.idc from constructions.output a 
	join tmp b on a.idp=b.id
	join constructions.det_names c on c.id=a.idc
	where c.razdSPID in (5,6,7);
Drop TEMPORARY TABLE if EXISTS tmp_mater;
CREATE TEMPORARY TABLE tmp_mater as
select b.id,a.obmid from technologic.det_info a 
	join tmp b on a.id=b.id;

DROP TEMPORARY TABLE if EXISTS summary;
create TEMPORARY table if not EXISTS summary(
	id	int(11)unsigned not NULL,
  #kol double NOT NULL,
	ei  char(3) DEFAULT null,
	nrm double NOT NULL,
	ei_d  char(3) DEFAULT null,
	nrm_d double NOT NULL,
	tag tinyint(1), #0 - комплектующие 1- материалы
	key `id`(`id`)
) ENGINE=memory;
#для элементов спецификации (5,6,7) взять ei из спецификации 
#для элементов технологии взять ei из технологии 
#Null заменить на 401 для сп и 203 для технологии
#количество унаследовать от парент детали
insert into summary 
select a.idc,/*sum(b.kol),*/IFNULL(c.ei,'401'),sum(b.kol),IFNULL(c.ei,'401'),sum(b.kol),0
from tmp_kompl a 
join constructions.output b on a.idp=b.idp and a.idc=b.idc
join constructions.det_tree c on c.idchild=a.idc and c.idparent=a.idp
GROUP BY a.idc;

insert into summary 
select a.obmid,/*sum(b.kol),*/IFNULL(c.ei,'203'),sum(b.kol*c.nrm),IFNULL(c.ei,'203'),sum(b.kol*c.nrm),1
from tmp_mater a 
join constructions.output b on a.id=b.idc
join technologic.det_info c on c.id=a.id 
GROUP BY a.obmid;

update summary a join sklad.materials b on a.id=b.obmid set a.nrm=a.nrm*b.ves, a.ei=b.eic where a.ei!=b.eic and b.eic=b.eiv; 
update summary a join sklad.materials b on a.id=b.obmid set a.nrm=a.nrm/b.ves, a.ei=b.eic where a.ei!=b.eic and b.eic!=b.eiv; 
#этап5 получить данные по материалу 

select 
IFNULL(c.sklad,'')'Склад',
IFNULL(c.bs,'') 	'Балансовый счет',
IFNULL(c.ss,'') 	'Субсчет',
IFNULL(c.cena,0)	'Цена',
IFNULL(round(a.nrm,3),0)   'Норма на изделие',
IFNULL(round(a.nrm*c.cena,3),0) 'Сумма',
IFNULL(b.obd,'')  'Код',

IFNULL(Concat(Trim(c.prma),' ',trim(c.gopr)),if(b.razdSPID in(5,6,7),IFNULL(trim(b.namd),''),'')) 'Сортамент',
IFNULL(Concat(Trim(c.nama),' ',trim(c.goma)),'') 'Материал',

a.ei,
a.ei_d,
a.nrm_d,
d.snameei 'Единицы измерения',

b.razdSPID 
from summary a
join constructions.det_names b on b.id=a.id
left join sklad.materials c on c.obmid=a.id
left JOIN catalogs.dimensionality d on a.ei=d.kodei
where c.sklad is not null
order by c.sklad,b.razdSPID,c.prma,`Код`,c.nama;

Drop TEMPORARY TABLE if EXISTS constructions.output;
DROP TEMPORARY TABLE if EXISTS tmp;
Drop TEMPORARY TABLE if EXISTS tmp_kompl;
Drop TEMPORARY TABLE if EXISTS tmp_mater;
DROP TEMPORARY TABLE if EXISTS summary;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_obd_from_zaka` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_obd_from_zaka`(zak text)
BEGIN
	#Routine body goes here...
select b.obd from market.zakaz a 
	join constructions.det_names b on a.id=b.id 
	join market.Orders c on a.zakaz_id=c.zakaz_id	
where c.zakaz=zak;
#void __fastcall Tkoldet::CB2Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_Start_Podr_for_uzel` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_Start_Podr_for_uzel`(obd text)
    COMMENT 'получение списка подразделений в которых начинается производство'
BEGIN
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
set @id=0;
select a.id into @id from constructions.det_names a where a.obd=obd;#получение id 

Call constructions.GetAllUzel(@id);#получим состав и количество с учетом заказанных узлов

DROP TEMPORARY TABLE IF EXISTS tmp;
CREATE TEMPORARY TABLE tmp as  
select a.cex,a.utch,min(a.opr),a.id from technologic.operation_list a 
	join constructions.output b on a.id = b.idc
	GROUP BY a.id;
SELECT a.cex,a.utch,count(1) as count FROM tmp a GROUP BY a.cex,a.utch; 
DROP TEMPORARY TABLE IF EXISTS tmp;
Drop TEMPORARY TABLE if EXISTS constructions.output;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Get_zakaz_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Get_zakaz_list`(obd text)
BEGIN
	#Routine body goes here...
select c.zakaz 
from market.zakaz a 
	join constructions.det_names b on a.id=b.id
	join market.Orders c on a.zakaz_id=c.zakaz_id
where b.obd=obd;
#void __fastcall Tkoldet::CB1Click(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Kol_det` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Kol_det`(`zakaz` text, obd  text)
BEGIN
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;

call constructions.GetAllZak(zakaz);#получение развертки заказа

select b.obd,SUM(kol) as kol 
		from constructions.output a 
		join constructions.det_names b on b.id=a.idc 
		where a.obd=obd 
		GROUP BY a.idc;#подсчет и вывод

Drop TEMPORARY TABLE if EXISTS constructions.output;
#void __fastcall Tkoldet::GetKol(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Kol_det_obu` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Kol_det_obu`(obu text, obd text)
BEGIN
#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obu;#получение id 

call constructions.GetAllUzel(@id);#получение развертки заказа

select b.obd,SUM(kol) as kol 
		from constructions.output a 
		join constructions.det_names b on b.id=a.idc 
		where b.obd=obd 
		GROUP BY a.idc;#подсчет и вывод

Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
#void __fastcall Tkoldet::GetKol(void)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Marsh_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Marsh_list`(obd text)
Begin
Drop TEMPORARY TABLE if EXISTS tmp;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

select 
if (a.vz is not null,a.vz ,0) as vz,
if (a.kdz is not null,a.kdz,0) as kdz,
if (a.masz is not null,a.masz,0) as masz,
if (a.nrm is not null,a.nrm,0) as nrm,
if (a.razz is not null,a.razz,'') as razz,
if (Concat(a.pm,' ',a.napr) is not null,trim(concat(trim(a.pm),' ',trim(a.napr))),'') as pm,
if (d.cex is not null,concat(d.cex,d.utch),'') as ceu,
if (d.opr is not null,d.opr,'') as opr,
if (d.oboid is not null,d.oboid,'') as obo,
if (b.rr is not null,b.rr,0) as rr,
if (b.kvn is not null,b.kvn,0) as kvn,
if (b.tpz is not null,b.tpz,0) as tpz,
if (b.tsht/b.kolod is not null,round(b.tsht/b.kolod,5) ,0) as tsht,
if (c.oprid is not null,c.oprid,'') as kop,
if (c.`name` is not null,c.`name`,'') as nop
from constructions.det_names e
 join technologic.operation_list d on d.id=e.id
 left join technologic.operation_norms b on b.opuuid=d.opuuid
 left join equipment.opr_names c on c.oprid=d.oprid
 left join technologic.det_info a  on a.id=e.id

where e.id=@id /*and e.razdspid not in (5,7,1)*/order by d.opr,d.oboid DESC;
Drop TEMPORARY TABLE if EXISTS tmp;
#int  cReports::AddML		(String obd,String name,String name_mat,String prof_mat,int kol,int Lcount,int mlnumber)
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Mat_report` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Mat_report`(obd text,kol int)
BEGIN
#строка с головным изделием не обрабатывается 
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS stage2;
Drop TEMPORARY TABLE if EXISTS tmp;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

Call constructions.GetAllUzel(@id);#получим состав и количество с учетом заказанных узлов

update constructions.output a set a.kol=a.kol*kol;

create TEMPORARY table if not EXISTS stage2(
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
  kol double NOT NULL,
	ei char(3)  not null DEFAULT '401',
	key `idc`(`idc`),
	key `idp`(`idp`)
) ENGINE=memory;
insert into stage2 (idp,idc,kol,ei)  (select a.idp,a.idc,a.kol,401 from constructions.output a);

update stage2 a 
		join constructions.det_tree b on a.idc=b.idchild and a.idp=b.idparent
		set a.ei=b.ei;

select 
c.ei,
if (c.obmid is not null and d.obd not like '%NA%' and d.obd!='000000000000000' and trim(d.obd)!='',
		d.obd,
		if(left(b1.obd,9)='000000000' and (b1.razdSPID in(5,6,7) ),
				b1.obd,
				'')) as 'Код',
if (c.obmid is not null and d.obd!='000000000000000' and trim(d.obd)!='',
		d.id,
		if(left(b1.obd,9)='000000000' and (b1.razdSPID in(5,6,7) ),
				b1.id,
				'')) as kod, #поле для группировки результатов
if (Concat(Trim(e.prma),' ',trim(e.gopr)) is not null,
		Concat(Trim(e.prma),' ',trim(e.gopr)),
		if(b1.razdSPID in(5,6,7) and trim(b1.namd) is not null,trim(b1.namd),'')) 'Сортамент',
if (Concat(Trim(e.nama),' ',trim(e.goma)) is not null,Concat(Trim(e.nama),' ',trim(e.goma)),'') 'Материал',
if (c.nrm is not null,c.nrm,0) AS nrm,
if (c.nrm is not null,sum(c.nrm*a.kol),0) 'Норма на изделие',
if (b1.razdSPID not in(5,6,7),
		if (
				f.snameei is not null,
				f.snameei,
				if(trim(c.ei) is not null,trim(c.ei),'')
				),
		if (
				f.snameei is not null,
				concat(f.snameei,'(',sum(a.kol),if (f1.snameei is not null,f1.snameei,''),')'),
				concat(if(trim(c.ei) is not null,trim(c.ei),''),'(',sum(a.kol),if (f1.snameei is not null,concat(' ',f1.snameei),''),')')
				)
    )as 'Единицы измерения',
b1.razdSPID 
FROM stage2 a
join constructions.det_names b1 on b1.id=a.idc
left JOIN technologic.det_info c on c.id=a.idc
left join constructions.det_names d on d.id=c.obmid 
left JOIN sklad.materials e on e.obmid=c.obmid 
left JOIN catalogs.dimensionality f on c.ei=f.kodei
join catalogs.dimensionality f1 on a.ei=f1.kodei
GROUP BY kod
order by b1.razdSPID,e.prma,`Код`,e.nama;


Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
Drop TEMPORARY TABLE if EXISTS stage2;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `Mat_report_detail` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `Mat_report_detail`(obd text,kol int)
BEGIN
#строка с головным изделием не обрабатывается 
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS stage2;
Drop TEMPORARY TABLE if EXISTS tmp;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

Call constructions.GetAllUzel(@id);#получим состав и количество с учетом заказанных узлов

update constructions.output a set a.kol=a.kol*kol;

create TEMPORARY table if not EXISTS stage2(
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
  kol double NOT NULL,
	ei char(3)  not null DEFAULT '401',
	key `idc`(`idc`),
	key `idp`(`idp`)
) ENGINE=memory;
insert into stage2 (idp,idc,kol,ei)  (select a.idp,a.idc,a.kol,401 from constructions.output a);

update stage2 a 
		join constructions.det_tree b on a.idc=b.idchild and a.idp=b.idparent
		set a.ei=b.ei;

select b1.obd ,b1.namd,sum(a.kol) kol,
if (c.obmid is not null and d.obd not like '%NA%' and d.obd!='000000000000000' and trim(d.obd)!='',
		d.obd,
		if(left(b1.obd,9)='000000000' and (b1.razdSPID in(5,6,7) ),
				b1.obd,
				'')) as Код,
if (Concat(Trim(e.prma),' ',trim(e.gopr)) is not null,
		Concat(Trim(e.prma),' ',trim(e.gopr)),
		if(b1.razdSPID in(5,6,7) and trim(b1.namd) is not null,trim(b1.namd),'')) 'Сортамент',
if (Concat(Trim(e.nama),' ',trim(e.goma)) is not null,Concat(Trim(e.nama),' ',trim(e.goma)),'') 'Материал',
if (c.nrm is not null,c.nrm,0) as nrm,
if (c.masd is not null,c.masd,0) as mass,
if (c.masz is not null,c.masz,0) as masz,
if (c.vz is not null,c.vz,0) as vz,
if (c.razz is not null,c.razz,"") as razz,
if (ceil(sum(a.kol)/c.kdz) is not null,ceil(sum(a.kol)/c.kdz),0) as kolzag,
if (c.nrm is not null,round(sum(c.nrm*a.kol),4),0) as 'Норма на изделие',
if (b1.razdSPID not in(5,6,7),
		if (
				f.snameei is not null,
				f.snameei,
				if(trim(c.ei) is not null,trim(c.ei),'')
				),
		if (
				f.snameei is not null,
				concat(f.snameei,'(',sum(a.kol),if (f1.snameei is not null,f1.snameei,''),')'),
				concat(if(trim(c.ei) is not null,trim(c.ei),''),'(',sum(a.kol),if (f1.snameei is not null,concat(' ',f1.snameei),''),')')
				)
    )as 'Единицы измерения',
if (round(c.masd/c.nrm,4) is not null,round(c.masd/c.nrm,4),0) as 'КИМ',b1.razdSPID
FROM stage2 a
join constructions.det_names b1 on b1.id=a.idc
left JOIN technologic.det_info c on c.id=a.idc
left join constructions.det_names d on d.id=c.obmid 
left JOIN sklad.materials e on e.obmid=c.obmid 
left JOIN catalogs.dimensionality f on c.ei=f.kodei
join catalogs.dimensionality f1 on a.ei=f1.kodei
#where a.spid not in (/*0,*/1,2,3,8)  
group by b1.obd
order by Код,b1.razdSPID,b1.obd;

Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
Drop TEMPORARY TABLE if EXISTS stage2;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `obu_list` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `obu_list`(obd varchar(30))
BEGIN
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
set @id=0;

create TEMPORARY TABLE if not EXISTS tmp as 
select @id:=a.id from constructions.det_names a WHERE a.obd=obd;

call constructions.Get_uzel_list_by_det(@id);

select b.obd as obu from constructions.output a JOIN constructions.det_names b on a.idp=b.id;

Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
#void __fastcall Tkoldet::FormShow(TObject *Sender)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `plan_pr_det` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `plan_pr_det`(obd text,kol int)
BEGIN  
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
Drop TEMPORARY TABLE if EXISTS out_table;
Drop TEMPORARY TABLE if EXISTS norms;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

Call constructions.GetDetInUzel(@id,kol);#получим состав и количество с учетом заказанных узлов


CREATE TEMPORARY TABLE IF NOT EXISTS out_table as
select 
b.id,
b.obd,
if(b.namd is not null,b.namd,'') as namd,
a.kol,
c1.obd as obm,
if (d.nama is not null,TRIM(d.nama),'') as nama,
if(d.prma is not null,TRIM(d.prma),'') as prma,
if (c.pm is not null or c.napr is not NULL,concat(TRIM(c.pm),' ',TRIM(c.napr)),'') as pm,
if (c.nrm!=0,ROUND(c.nrm-c.masd,3),0) as ost,
if (left(concat(c.pm,' ',c.napr),4)='0303'or right(concat(c.pm,' ',c.napr),4)='0303',1,2) as prizn 
from
constructions.output a 
join constructions.det_names b on a.idc=b.id 
left join technologic.det_info c on a.idc=c.id
left join constructions.det_names c1 on c1.id=c.obmid
left join sklad.materials d on c.obmid=d.obmid
where b.razdSPID not in (1,7)
order by b.razdSPID,b.obd;

Drop TEMPORARY TABLE if EXISTS norms;
CREATE TEMPORARY TABLE IF NOT EXISTS norms as 
select b.id,c.tsht,c.tpz, c.kolod 
	from out_table a 
	left join technologic.operation_list b on b.id=a.id
	left join technologic.operation_norms c on c.OpUUID=b.OpUUID;
  
select a.obd,a.namd,a.kol,a.nama,a.prma,
if (f.kolod is not null,f.kolod,0) as kolod,
if (sum(f.tsht/f.kolod/*+f.tpz*/) is not null,ROUND(sum(f.tsht/f.kolod/*+f.tpz*/),3),0) as tsht, 
if (sum(f.tsht/f.kolod/*+f.tpz*/)*a.kol is not null,ROUND(sum(f.tsht/f.kolod/*+f.tpz*/)*a.kol,3),0) as tpart,
if (sum(f.tpz/f.kolod) is not null,ROUND(sum(f.tpz/f.kolod),3),0) as tpz, 
if (sum(f.tpz/f.kolod)/a.kol is not null,ROUND(sum(f.tpz/f.kolod)/a.kol,3),0) as tpzpart,
a.pm,a.ost,a.prizn 
from out_table a 
left join norms f on a.id=f.id group by a.obd order by a.prizn,a.obd;

Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
Drop TEMPORARY TABLE if EXISTS out_table;
Drop TEMPORARY TABLE if EXISTS norms;
#void cReports::PlanPrDet   	(String obd,String kol)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `plan_pr_det_times_by_ceu` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `plan_pr_det_times_by_ceu`(obd text,kol int)
BEGIN  
	#Routine body goes here...

Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
Drop TEMPORARY TABLE if EXISTS out_table;
Drop TEMPORARY TABLE if EXISTS norms;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

Call constructions.GetDetInUzel(@id,kol);#получим состав и количество с учетом заказанных узлов

CREATE TEMPORARY TABLE IF NOT EXISTS out_table as
select 
b.id,
b.obd,
if(b.namd is not null,b.namd,'') as namd,
a.kol,
c1.obd as obm,
if (d.nama is not null,TRIM(d.nama),'') as nama,
if(d.prma is not null,TRIM(d.prma),'') as prma,
if (c.pm is not null or c.napr is not NULL,concat(TRIM(c.pm),' ',TRIM(c.napr)),'') as pm,
if (c.nrm!=0,ROUND(c.nrm-c.masd,3),0) as ost,
if (left(concat(c.pm,' ',c.napr),4)='0303'or right(concat(c.pm,' ',c.napr),4)='0303',1,2) as prizn 
from
constructions.output a 
join constructions.det_names b on a.idc=b.id 
left join technologic.det_info c on a.idc=c.id
left join constructions.det_names c1 on c1.id=c.obmid
left join sklad.materials d on c.obmid=d.obmid
where b.razdSPID not in (1,7)
order by b.razdSPID,b.obd;

CREATE TEMPORARY TABLE IF NOT EXISTS norms as 
select b.id,b.cex,b.utch,c.tsht,c.tpz, c.kolod 
	from out_table a 
	left join technologic.operation_list b on b.id=a.id
	left join technologic.operation_norms c on c.OpUUID=b.OpUUID;

select 
if (f.cex is not null,CONCAT(f.cex,f.utch),'')  as `Участок`,
if (sum(f.tsht/(f.kolod/*+f.tpz*/)*a.kol) is not null,ROUND(sum(f.tsht/(f.kolod/*+f.tpz*/)*a.kol),3),0)as `Загрузка`
from out_table a 
join norms f on a.id=f.id where f.cex is not null group by f.cex,f.utch  order by f.cex,f.utch ;

Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
Drop TEMPORARY TABLE if EXISTS out_table;
Drop TEMPORARY TABLE if EXISTS norms;
#int  cReports::AddReport	(String obd,String kol,int Lcount)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `plan_pr_det_times_by_obo` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `plan_pr_det_times_by_obo`(obd text,kol int)
BEGIN  
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
Drop TEMPORARY TABLE if EXISTS out_table;
Drop TEMPORARY TABLE if EXISTS norms;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

Call constructions.GetDetInUzel(@id,kol);#получим состав и количество с учетом заказанных узлов

CREATE TEMPORARY TABLE IF NOT EXISTS out_table as
select 
b.id,
b.obd,
if(b.namd is not null,b.namd,'') as namd,
a.kol,
c1.obd as obm,
if (d.nama is not null,TRIM(d.nama),'') as nama,
if(d.prma is not null,TRIM(d.prma),'') as prma,
if (c.pm is not null or c.napr is not NULL,concat(TRIM(c.pm),' ',TRIM(c.napr)),'') as pm,
if (c.nrm!=0,ROUND(c.nrm-c.masd,3),0) as ost,
if (left(concat(c.pm,' ',c.napr),4)='0303'or right(concat(c.pm,' ',c.napr),4)='0303',1,2) as prizn 
from
constructions.output a 
join constructions.det_names b on a.idc=b.id 
left join technologic.det_info c on a.idc=c.id
left join constructions.det_names c1 on c1.id=c.obmid
left join sklad.materials d on c.obmid=d.obmid
where b.razdSPID not in (1,7)
order by b.razdSPID,b.obd;

CREATE TEMPORARY TABLE IF NOT EXISTS norms as 
select b.id,b.cex,b.oboid,b.utch,c.tsht,c.tpz,c.kolod 
	from out_table a 
	left join technologic.operation_list b on b.id=a.id
	left join technologic.operation_norms c on c.OpUUID=b.OpUUID;

select 
#,f.opr,f.tsht,a.kol,f.kolod,
if (f.cex is not null,concat(f.cex,f.utch),'') as `Участок`,
if (f.oboid is not null,f.oboid,'') as `Оборудование`,
if (sum(f.tsht/(f.kolod/*+f.tpz*/)*a.kol) is not null,ROUND(sum(f.tsht/(f.kolod/*+f.tpz*/)*a.kol),3),0) as `Загрузка`,
if (d.name is not null,d.name,'') as `Наименование оборудования`,
if (a.obd is not null,a.obd,'') as `Обозначение`,
if (a.namd is not null,a.namd,'') as `Наименование`
from out_table a 
join norms f on f.id=a.id
join equipment.obor_list d on d.oboID=f.oboid
group by f.oboid,f.cex,f.utch 
order by f.cex,f.utch,f.oboid;

Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
Drop TEMPORARY TABLE if EXISTS out_table;
Drop TEMPORARY TABLE if EXISTS norms;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `report_by_raccex` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `report_by_raccex`(obd text,cex varchar(4))
BEGIN  
	#Routine body goes here...
Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
set @id=0;
CREATE TEMPORARY table if not EXISTS tmp as select @id:=a.id from constructions.det_names a where a.obd=obd;#получение id 

call constructions.GetDet(@id);#получение развертки заказа


set @sq=CONCAT("select b.obd AS 'Обозначение',if(b.namd is not null,b.namd,'') as 'Наименование',
if (c.pm is not null or c.napr is not NULL,concat(concat(trim(c.pm),' '),trim(c.napr)),'') as 'Расцеховка'
from constructions.output a 
join constructions.det_names b on a.idc=b.id
left join technologic.det_info c on a.idc=c.id
where pm like '%",cex,"%' order by b.obd;");
prepare init from @sq;
EXECUTE init;

Drop TEMPORARY TABLE if EXISTS constructions.output;
Drop TEMPORARY TABLE if EXISTS tmp;
#bool cReports::CreateReport(int type, String param)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `teh_dt_info` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `teh_dt_info`(obd text)
BEGIN
	#Routine body goes here...
select distinct
b.obd,
trim(b.namd) as namd,
if (a.ei is not null,a.ei,'') as ei,
if (b1.obd is not null,b1.obd,'') as obm,
if (a.vz is not null,a.vz,0) as vz,
if (a.napr is not null,a.napr,'') as napr,
if (a.kdz is not null,a.kdz,1) as kdz,
if (a.nrm is not null,a.nrm,0) as nrm,
if (a.masz is not null,a.masz,0) as masz,
if (a.masd is not null,a.masd,0) as masd,
if (a.razz is not null,trim(a.razz),'') as razz,
if(a.kdz*a.masz/a.nrm is not null,ROUND(a.masd/a.nrm,3),0)as kim,
if (a.ChangeDate is not null,date_format(a.ChangeDate,'%d.%m.%Y'),'') as dnte,
if (CONCAT(trim(c.prma),' ',trim(c.gopr),' / ',trim(c.nama),' ',trim(c.goma)) is not null,CONCAT(trim(c.prma),' ',trim(c.gopr),' / ',trim(c.nama),' ',trim(c.goma)),'') as material 
from 
constructions.det_names b left join
technologic.det_info a  on a.id=b.id left join
constructions.det_names b1 on a.obmid=b1.id left join
sklad.materials c on c.obmid=a.obmid
where b.obd=obd;
#void cReports::Texnologic	(String obd)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `teh_instr` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `teh_instr`(obd text, opr varchar(3))
BEGIN
	#Routine body goes here...
select trim(c.koin) as koin,trim(c.nain) as nain 
	from constructions.det_names a
	join technologic.operation_list b on a.id=b.id and b.opr=opr
	join technologic.instrum c on c.opuuid=b.opuuid
	where a.obd=obd
order by b.opr,b.oboid,c.strk;
#void cReports::Texnologic	(String obd)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `teh_oper` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `teh_oper`(obd text)
BEGIN
	#Routine body goes here...

select distinct 
a.obd,concat(b.cex,b.utch) as ceu,b.opr,
if (concat(e.oboid,'      ',e.`name`)is not null,concat(e.oboid,'      ',e.`name`),'') as obo,
if (concat(f.oprid,' ',f.`name`) is not null,concat(f.oprid,' ',f.`name`) ,'') as oper,
trim(b.ioht) as ioht,
if (trim(b.stro)!='нет'and trim(b.stro)!='',concat('Строповка по РТМ 2103-11-75 чертеж ',trim(b.stro)),'') as stro,
#b.stro as ert,
if (b.ktar!='0',concat(g.tara,' ',g.obta),'') as tara,
if (d.te69 is not null,if(d.ko69!='0',d.te69,''),'') as control,

if (c.ksht is not null,c.ksht,0) as ksht,
if (c.prof is not null,c.prof,"") as prof,
if (c.krop is not null,c.krop,"") as krop,
if (c.rr is not null,c.rr,"") as rr,
if (c.kolod is not null,c.kolod,0) as kolod,
if (c.en is not null,c.en,"") as en,
if (concat(c.kts,"/",c.kvn) is not null and c.kts!="0"and c.kvn!="0",concat(c.kts,"/",c.kvn),"") as kvn,
if (c.tpz is not null,c.tpz,0) as tpz,
if (c.ttp is not null,c.ttp,"") as ttp,
if (c.tsht is not null,c.tsht,0) as tsht
from 
constructions.det_names a 
JOIN technologic.operation_list b on a.id=b.id 
left join technologic.operation_norms c on c.opuuid=b.opuuid  
left JOIN catalogs.control d on b.ok69=d.ko69 
left JOIN equipment.obor_list e on b.oboid=e.oboid 
left join equipment.opr_names f on f.oprid=b.oprid 
left JOIN catalogs.tara g on g.kota=b.ktar
where
a.obd=obd
order by opr,obo;
#void cReports::Texnologic	(String obd)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `teh_per` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `teh_per`(obd text, opr varchar(3))
BEGIN
	#Routine body goes here...
select trim(c.tpe) as tpe 
	from constructions.det_names a
	join technologic.operation_list b on a.id=b.id and b.opr=opr
	join technologic.perexod c on c.opuuid=b.opuuid
	where a.obd=obd
order by b.opr,b.oboid,c.strk;
#void cReports::Texnologic	(String obd)
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-08-15 22:33:28
