# ************************************************************
# Sequel Ace SQL dump
# 版本号： 20067
#
# https://sequel-ace.com/
# https://github.com/Sequel-Ace/Sequel-Ace
#
# 主机: 127.0.0.1 (MySQL 8.3.0)
# 数据库: pokemon
# 生成时间: 2024-06-14 15:24:32 +0000
# ************************************************************


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
SET NAMES utf8mb4;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE='NO_AUTO_VALUE_ON_ZERO', SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


# 转储表 pokemon
# ------------------------------------------------------------

DROP TABLE IF EXISTS `pokemon`;

CREATE TABLE `pokemon` (
  `pokemonID` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `HP` int NOT NULL,
  `ATK` int NOT NULL,
  `DEF` int NOT NULL,
  `EXP` int NOT NULL,
  `LV` int NOT NULL,
  `Speed` int NOT NULL,
  `userID` int NOT NULL,
  PRIMARY KEY (`pokemonID`)
) ENGINE=InnoDB AUTO_INCREMENT=84 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

LOCK TABLES `pokemon` WRITE;
/*!40000 ALTER TABLE `pokemon` DISABLE KEYS */;

INSERT INTO `pokemon` (`pokemonID`, `name`, `HP`, `ATK`, `DEF`, `EXP`, `LV`, `Speed`, `userID`)
VALUES
	(1,'腕力',100,20,10,0,1,2,3),
	(2,'杰尼龟',101,21,12,0,2,3,3),
	(3,'火暴猴',100,20,10,0,1,2,4),
	(4,'皮卡丘',100,20,10,0,1,2,4),
	(5,'怪力',300,45,35,0,15,6,5),
	(6,'飞腿郎',100,20,10,0,1,2,6),
	(8,'腕力',109,29,28,1,5,11,5),
	(9,'小火龙',102,22,14,0,3,4,5),
	(10,'飞腿郎',100,20,10,0,1,2,3),
	(11,'波波',101,22,11,0,2,3,5),
	(12,'火暴猴',100,20,10,0,1,2,3),
	(13,'飞腿郎',100,20,10,0,1,2,3),
	(14,'妙蛙种子',100,20,10,0,1,2,3),
	(15,'波波',100,20,10,0,1,2,3),
	(16,'波波',100,20,10,0,1,2,3),
	(17,'皮卡丘',100,20,10,0,1,2,3),
	(18,'小火龙',100,20,10,0,1,2,3),
	(19,'腕力',100,20,10,0,1,2,3),
	(20,'皮卡丘',100,20,10,0,1,2,3),
	(21,'杰尼龟',100,20,10,0,1,2,3),
	(22,'火暴猴',100,20,10,0,1,2,3),
	(23,'小火龙',100,20,10,0,1,2,3),
	(24,'皮卡丘',100,20,10,0,1,2,3),
	(25,'皮卡丘',100,20,10,0,1,2,3),
	(26,'妙蛙种子',100,20,10,0,1,2,3),
	(27,'妙蛙种子',100,20,10,0,1,2,3),
	(28,'飞腿郎',100,20,10,0,1,2,3),
	(29,'妙蛙种子',100,20,10,0,1,2,3),
	(30,'腕力',100,20,10,0,1,2,3),
	(31,'小火龙',100,20,10,0,1,2,3),
	(32,'波波',100,20,10,0,1,2,3),
	(33,'腕力',100,20,10,0,1,2,3),
	(34,'杰尼龟',100,20,10,0,1,2,3),
	(35,'腕力',100,20,10,0,1,2,3),
	(36,'波波',100,20,10,0,1,2,3),
	(37,'火暴猴',100,20,10,0,1,2,3),
	(38,'飞腿郎',100,20,10,0,1,2,3),
	(39,'波波',100,20,10,0,1,2,3),
	(41,'波波',100,20,10,0,1,2,5),
	(43,'妙蛙种子',100,20,10,0,1,2,5),
	(44,'猴怪',100,20,10,0,1,2,8),
	(45,'皮卡丘',100,20,10,0,1,2,5),
	(47,'腕力',100,20,10,0,1,2,5),
	(48,'火暴猴',100,20,10,0,1,2,5),
	(49,'妙蛙种子',100,20,10,0,1,2,5),
	(50,'小火龙',100,20,10,0,1,2,5),
	(54,'飞腿郎',100,20,10,0,1,2,11),
	(55,'妙蛙种子',100,20,10,0,1,2,11),
	(56,'皮卡丘',100,20,10,0,1,2,11),
	(57,'小火龙',100,20,10,0,1,2,11),
	(58,'火暴猴',100,20,10,0,1,2,11),
	(59,'皮卡丘',100,20,10,0,1,2,12),
	(60,'皮卡丘',100,20,10,0,1,2,12),
	(61,'飞腿郎',100,20,10,0,1,2,13),
	(62,'飞腿郎',100,20,10,0,1,2,13),
	(63,'杰尼龟',100,20,10,0,1,2,14),
	(64,'波波',100,20,10,0,1,2,14),
	(66,'飞腿郎',100,20,10,0,1,2,15),
	(67,'波波',100,20,10,0,1,2,15),
	(68,'猴怪',101,21,12,0,2,3,16),
	(69,'飞腿郎',100,20,10,0,1,2,16),
	(70,'飞腿郎',104,22,12,0,3,4,17),
	(71,'波波',100,20,10,0,1,2,17),
	(72,'皮卡丘',100,20,10,0,1,2,17),
	(73,'皮卡丘',100,20,10,0,1,2,17),
	(75,'波波',100,20,10,0,1,2,17),
	(77,'妙蛙种子',100,20,10,0,1,2,18),
	(78,'皮卡丘',100,20,10,0,1,2,18),
	(81,'火暴猴',100,20,10,0,1,2,19),
	(82,'皮卡丘',100,20,10,0,1,2,19),
	(83,'皮卡丘',100,20,10,0,1,2,19);

/*!40000 ALTER TABLE `pokemon` ENABLE KEYS */;
UNLOCK TABLES;


# 转储表 user
# ------------------------------------------------------------

DROP TABLE IF EXISTS `user`;

CREATE TABLE `user` (
  `userID` int NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `online` tinyint(1) DEFAULT '0',
  `pokemonCnt` int DEFAULT NULL,
  `highPokemonCnt` int DEFAULT NULL,
  `battleCnt` int DEFAULT NULL,
  `battleWinCnt` int DEFAULT NULL,
  PRIMARY KEY (`userID`)
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;

INSERT INTO `user` (`userID`, `username`, `password`, `online`, `pokemonCnt`, `highPokemonCnt`, `battleCnt`, `battleWinCnt`)
VALUES
	(1,'ttt','用户名：',0,NULL,NULL,NULL,NULL),
	(2,'test','用户名：',0,NULL,NULL,NULL,NULL),
	(3,'testt','12345',0,30,NULL,NULL,NULL),
	(4,'1','1',0,1,NULL,NULL,NULL),
	(5,'q','q',0,16,NULL,23,12),
	(6,'t','t',0,1,NULL,NULL,NULL),
	(7,'2','2',0,1,NULL,NULL,NULL),
	(8,'12345','123',0,1,NULL,NULL,NULL),
	(9,'qwer','qwer',0,1,NULL,1,NULL),
	(10,'99','99',0,1,NULL,4,2),
	(11,'55','55',0,5,NULL,4,4),
	(12,'44','44',0,2,NULL,1,1),
	(13,'33','33',0,2,NULL,1,1),
	(14,'78','78',0,2,NULL,1,1),
	(15,'23','23',0,2,NULL,2,1),
	(16,'zf','zf',0,3,NULL,2,2),
	(17,'9999','99999',0,1,NULL,9,7),
	(18,'testttt','12345',0,2,NULL,4,2),
	(19,'123','123',0,1,NULL,4,2);

/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;



/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
