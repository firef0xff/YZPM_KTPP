
DROP TEMPORARY TABLE if EXISTS t1;
CREATE TEMPORARY table t1 as SELECT id,zaka FROM `zakaz` a GROUP BY a.id,a.zaka HAVING count(a.id)!=1;
delete from market.zakaz where (id,zaka) in (SELECT id,zaka FROM t1) limit 1;
DROP TEMPORARY TABLE if EXISTS t1;

CREATE TABLE `Orders` (
  `zakaz` varchar(6) NOT NULL,
  `zakaz_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `description` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`zakaz_id`)
) ENGINE=InnoDB DEFAULT CHARSET=cp1251

INSERT into Orders (zakaz) (select zaka from zakaz group by zaka);

ALTER TABLE `zakaz`
DROP COLUMN `zakaz_id`,
ADD COLUMN `zakaz_id`  unsigned NOT NULL AFTER `id`;

update `zakaz` a join `Orders` b on a.zaka=b.zakaz set a.zakaz_id=b.zakaz_id;

ALTER TABLE `zakaz` ADD FOREIGN KEY (`zakaz_id`) REFERENCES `Orders` (`zakaz_id`) ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE `zakaz`
DROP COLUMN `zaka`,
MODIFY COLUMN `kol`  double NOT NULL DEFAULT 1 COMMENT 'количество заказанных изделий' AFTER `zakaz_id`;

INSERT INTO `rights` (Name,progName) VALUES ('–едактирование заказов', 'OrderEdit');
INSERT INTO `rights` (Name,progName) VALUES ('ѕросмотр заказов', 'OrderView');