USE `ssafy`;

CREATE TABLE `todos` (
  `todo_id` int NOT NULL AUTO_INCREMENT,
  `title` varchar(45) NOT NULL,
  `is_completed` tinyint NOT NULL,
  `author` varchar(45) NOT NULL DEFAULT '0',
  PRIMARY KEY (`todo_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

INSERT INTO `todos` (`todo_id`,`title`,`is_completed`,`author`) 
VALUES 
(1,'밥먹기',1,'david')
,(2,'영화보기',1,'tom')
,(3,'커피마시기',0,'tom');
