-- MySQL dump 10.13  Distrib 5.5.23, for Win64 (x86)
--
-- Host: 192.168.1.11    Database: manufacture
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
-- Current Database: `manufacture`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `manufacture` /*!40100 DEFAULT CHARACTER SET cp1251 */;

USE `manufacture`;

--
-- Table structure for table `det_names`
--

DROP TABLE IF EXISTS `det_names`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `det_names` (
  `det_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT 'идентификатор объекта спецификации',
  `id` bigint(20) unsigned NOT NULL,
  `obd` varchar(100) NOT NULL DEFAULT '' COMMENT 'обозначение объекта спецификации',
  `name` varchar(255) NOT NULL DEFAULT '' COMMENT 'наименование объекта спецификации',
  `pp` varchar(2) NOT NULL DEFAULT '00' COMMENT 'производственный признак (исптся только на асу)',
  `format` varchar(5) NOT NULL DEFAULT '' COMMENT 'формат- поле спецификации',
  `sp_id` smallint(6) unsigned NOT NULL DEFAULT '4' COMMENT 'идентификатор раздела спецификации',
  `state` smallint(6) unsigned NOT NULL DEFAULT '0' COMMENT 'идентификатор состояния объекта спецификации',
  `sp_name` varchar(255) NOT NULL,
  PRIMARY KEY (`det_id`)
) ENGINE=InnoDB AUTO_INCREMENT=303 DEFAULT CHARSET=cp1251 ROW_FORMAT=COMPACT COMMENT='таблица со списком всех объектов спецификации';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `det_names`
--

LOCK TABLES `det_names` WRITE;
/*!40000 ALTER TABLE `det_names` DISABLE KEYS */;
/*!40000 ALTER TABLE `det_names` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `det_tree`
--

DROP TABLE IF EXISTS `det_tree`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `det_tree` (
  `det_idp` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'идентификатор родительского объекта спецификации',
  `det_idc` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'идентификатор объекта спецификации',
  `ei` char(3) NOT NULL DEFAULT '' COMMENT 'идентификатор кода едениц измерения',
  `kol_sp` double unsigned NOT NULL DEFAULT '0' COMMENT 'количество',
  `kol_using` double unsigned NOT NULL DEFAULT '0' COMMENT 'количество',
  `zona` varchar(5) NOT NULL DEFAULT '' COMMENT 'зона- поле спецификации',
  `pos` char(11) NOT NULL DEFAULT '0' COMMENT 'позиция - поле спецификации',
  `prim` varchar(255) NOT NULL DEFAULT '' COMMENT 'примечание- поле спецификации',
  `using` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`det_idp`,`det_idc`),
  KEY `det_idc` (`det_idc`),
  CONSTRAINT `det_tree_ibfk_1` FOREIGN KEY (`det_idp`) REFERENCES `det_names` (`det_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `det_tree_ibfk_2` FOREIGN KEY (`det_idc`) REFERENCES `det_names` (`det_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=cp1251 ROW_FORMAT=COMPACT COMMENT='Таблица со спецификациями';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `det_tree`
--

LOCK TABLES `det_tree` WRITE;
/*!40000 ALTER TABLE `det_tree` DISABLE KEYS */;
/*!40000 ALTER TABLE `det_tree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `manufacture_orders`
--

DROP TABLE IF EXISTS `manufacture_orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `manufacture_orders` (
  `zap_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `begin` date NOT NULL,
  `end` date NOT NULL,
  `user` varchar(255) NOT NULL,
  `in_work` datetime DEFAULT NULL,
  PRIMARY KEY (`zap_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `manufacture_orders`
--

LOCK TABLES `manufacture_orders` WRITE;
/*!40000 ALTER TABLE `manufacture_orders` DISABLE KEYS */;
INSERT INTO `manufacture_orders` VALUES (1,'12454555','2013-10-07','2013-10-07','user',NULL);
/*!40000 ALTER TABLE `manufacture_orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `part_content`
--

DROP TABLE IF EXISTS `part_content`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `part_content` (
  `part_id` bigint(20) unsigned NOT NULL,
  `det_id` bigint(20) unsigned NOT NULL,
  `in_work` datetime NOT NULL,
  `kol` int(10) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`part_id`,`det_id`),
  KEY `det_id` (`det_id`),
  CONSTRAINT `part_content_ibfk_1` FOREIGN KEY (`det_id`) REFERENCES `det_names` (`det_id`) ON UPDATE CASCADE,
  CONSTRAINT `part_content_ibfk_2` FOREIGN KEY (`part_id`) REFERENCES `parts` (`part_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `part_content`
--

LOCK TABLES `part_content` WRITE;
/*!40000 ALTER TABLE `part_content` DISABLE KEYS */;
/*!40000 ALTER TABLE `part_content` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `parts`
--

DROP TABLE IF EXISTS `parts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `parts` (
  `part_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `zap_id` bigint(20) unsigned NOT NULL,
  `zak_id` bigint(20) unsigned NOT NULL,
  `part_no` int(10) unsigned NOT NULL,
  `in_work` datetime DEFAULT NULL,
  PRIMARY KEY (`part_id`),
  KEY `zap_id` (`zap_id`),
  KEY `zak_id` (`zak_id`),
  CONSTRAINT `parts_ibfk_1` FOREIGN KEY (`zap_id`) REFERENCES `manufacture_orders` (`zap_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `parts_ibfk_2` FOREIGN KEY (`zak_id`) REFERENCES `zakaz_list` (`zak_id`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `parts`
--

LOCK TABLES `parts` WRITE;
/*!40000 ALTER TABLE `parts` DISABLE KEYS */;
INSERT INTO `parts` VALUES (1,1,6284,1,NULL);
/*!40000 ALTER TABLE `parts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `zakaz_list`
--

DROP TABLE IF EXISTS `zakaz_list`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `zakaz_list` (
  `zakaz` varchar(6) NOT NULL,
  `zak_id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `description` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`zak_id`)
) ENGINE=InnoDB AUTO_INCREMENT=6285 DEFAULT CHARSET=cp1251;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `zakaz_list`
--

LOCK TABLES `zakaz_list` WRITE;
/*!40000 ALTER TABLE `zakaz_list` DISABLE KEYS */;
INSERT INTO `zakaz_list` VALUES ('124564',6284,'');
/*!40000 ALTER TABLE `zakaz_list` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'manufacture'
--
/*!50003 DROP PROCEDURE IF EXISTS `AddIzd` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `AddIzd`(id bigint(20) unsigned, kol int(11) unsigned, part_id bigint(20) unsigned)
BEGIN
	#Routine body goes here...
# добавить вхождение поставить метку редактирования списка

declare lvl int;
set @sidc=0;

select IFNULL(max(det_id),0)+1 into @sidc from det_names a;


Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;

set @sq=CONCAT('CREATE TEMPORARY TABLE IF NOT EXISTS res(
	det_idc  BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
	det_idp  BIGINT UNSIGNED,
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
	idci int(11)unsigned DEFAULT null,
  kol_using double NOT NULL,
	kol_sp double NOT NULL,
	ei	char(3) NOT NULL,
	zona varchar(5) NOT NULL DEFAULT "",
  pos char(11) NOT NULL DEFAULT "0",
  prim varchar(255) NOT NULL DEFAULT "",
	lvl int not null,

	PRIMARY KEY (`det_idc`),
	key `det_idp`(`det_idp`),
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM AUTO_INCREMENT=',@sidc,';');
prepare init from @sq;
EXECUTE init;

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl(
	det_idc  BIGINT UNSIGNED NOT NULL,
	det_idp  BIGINT UNSIGNED,
	idp  int(11)unsigned ,
	idc	 int(11)unsigned not NULL,
	idci int(11)unsigned DEFAULT null,
  kol_using double NOT NULL,
	kol_sp double NOT NULL,
	ei	char(3) NOT NULL,
	zona varchar(5) NOT NULL DEFAULT "",
  pos char(11) NOT NULL DEFAULT "0",
  prim varchar(255) NOT NULL DEFAULT "",
	lvl int not null,

	PRIMARY KEY (`det_idc`),
	key `det_idp`(`det_idp`),
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM; 

#инициализация 
insert into res (det_idp,idp,idc,idci,kol_using,kol_sp,ei,lvl)
	select null,null as idp,a.id as idc,d.id00 as idci,kol as kol_using,kol kol_sp,401,0 as lvl
		from constructions.det_names a 
		left join constructions.basik_performance d on d.id=a.id
		where a.id=id;
set lvl=0;
#развертка
while EXISTS (select idc from res where res.lvl=lvl)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res (det_idp,idp,idc,idci,kol_using,kol_sp,ei,lvl,zona,pos,prim)
			(
			select b.det_idc as eidp, a.idparent as idp, a.idchild as idc, d.id00 as idci, a.kol*b.kol_using as kol_using, a.kol kol_sp, a.ei, lvl+1 as lvl , a.zona, a.pos, a.prim
			from constructions.det_tree a 
						join `obd_lvl` b on a.idparent=b.idc and b.lvl=lvl
						left join constructions.basik_performance d on d.id=a.idchild
			);
	insert into res (det_idp,idp,idc,idci,kol_using,kol_sp,ei,lvl,zona,pos,prim)
			(
			select b.det_idc as eidp, a.idparent as idp, a.idchild as idc, d.id00 as idci, a.kol*b.kol_using as kol_using, a.kol kol_sp, a.ei, lvl+1 as lvl , a.zona, a.pos, a.prim
			from constructions.det_tree a 
						join `obd_lvl` b on (a.idparent=b.idci and a.ppp=0) and b.lvl=lvl
						left join constructions.basik_performance d on d.id=a.idchild
			);
	set lvl=lvl+1;
	select * from obd_lvl;
END while;

#Вставка имен
insert into det_names (`det_id`,`id`,`obd`,`name`,`pp`,`format`,`sp_id`,`sp_name`)
	select `a`.`det_idc`, `a`.`idc`, `b`.`obd`, `b`.`namd`, `b`.`pp`, `b`.`format`, `c`.`RazdID`, `c`.`Razdname`
	from res a 
	join constructions.det_names b on a.idc = b.id
	left join administration.sprazd c on b.razdSPID = c.RazdID;
  
#Вставка в список
insert into det_tree (`det_idp`,`det_idc`,`ei`,`kol_sp`,`kol_using`,`zona`,`pos`,`prim`,`using`)
	select `a`.`det_idp`,`a`.`det_idc`,`a`.`ei`,`a`.`kol_sp`,`a`.`kol_using`,`a`.`zona`,`a`.`pos`,`a`.`prim`, 1 `using` from res a where a.lvl != 0;

#регистрация точки входа в дерево
insert into part_content (part_id, det_id, kol)
	select part_id, a.det_idc, a.kol_using from res a where a.lvl=0;
Drop TEMPORARY TABLE if EXISTS obd_lvl;
#Drop TEMPORARY TABLE if EXISTS res;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `DeleteIzd` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `DeleteIzd`(id bigint(20) unsigned)
BEGIN
	#Routine body goes here...
call GetContent(id);
delete from part_content where det_id = id;
delete from det_names where det_id in (select idc from output);
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `GetContent` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `GetContent`(id bigint(20) unsigned)
    COMMENT 'получение развертки состава по номерам заказов'
BEGIN
declare lvl int;
	
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
CREATE TEMPORARY TABLE IF NOT EXISTS res(
	idp  int(11)unsigned,
	idc	 int(11)unsigned not NULL,
	lvl int not null,
	key `idc`(`idc`),
	key `idp`(`idp`),
	key `lvl`(`lvl`)
) ENGINE=MYISAM;
TRUNCATE TABLE res; 

CREATE TEMPORARY TABLE IF NOT EXISTS obd_lvl as select * from res where 0;
TRUNCATE TABLE obd_lvl; 

insert into res	VALUES (null,id,0);
set lvl=0;

while (EXISTS (select idc from res where res.lvl=lvl) and lvl<1000)do
  TRUNCATE TABLE obd_lvl; 
  insert into `obd_lvl` select * from res where res.lvl=lvl;
	insert into res 
			(
			select a.det_idp as idp, a.det_idc as idc,lvl+1 as lvl
			from manufacture.det_tree a 
						join `obd_lvl` b on a.det_idp = b.idc and b.lvl=lvl
			);
	set lvl=lvl+1;
END while;
drop TEMPORARY table if EXISTS output;

create TEMPORARY TABLE if NOT EXISTS output as select a.idc  from res a GROUP BY a.idc;
Drop TEMPORARY TABLE if EXISTS obd_lvl;
Drop TEMPORARY TABLE if EXISTS res;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `SetUsage` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`%`*/ /*!50003 PROCEDURE `SetUsage`(id bigint(20) unsigned, us tinyint(4))
BEGIN
	#Routine body goes here...
call GetContent(id);
update det_tree a join output b on a.det_idc = b.idc set `using` = us;
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

-- Dump completed on 2013-10-22 21:21:03
