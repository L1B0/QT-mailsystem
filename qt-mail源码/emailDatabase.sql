
CREATE SCHEMA IF NOT EXISTS `email_schema` DEFAULT CHARACTER SET latin1 ;
USE `email_schema` ;


CREATE TABLE IF NOT EXISTS `email_schema`.`user` (
  `username` VARCHAR(45) NOT NULL,
  `password` VARCHAR(16) NOT NULL,
  `phone` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`username`))
ENGINE = INNODB
DEFAULT CHARACTER SET = utf8;



CREATE TABLE IF NOT EXISTS `email_schema`.`email_deletebox` (
  `idemail_deletebox` INT(11) NOT NULL AUTO_INCREMENT,
  `user_username` VARCHAR(45) NOT NULL,
  `mail_name` VARCHAR(45) NOT NULL,
  `mail_byUser` VARCHAR(45) NOT NULL,
  `mail_byTime` CHAR(20) NULL DEFAULT NULL,
  `mail_content` VARCHAR(2000) NULL DEFAULT NULL,
  `mail_status` INT(11) NULL DEFAULT NULL,
  PRIMARY KEY (`idemail_deletebox`),
  INDEX `fk_email_deletebox_user1` (`user_username` ASC),
  CONSTRAINT `fk_email_deletebox_user1`
    FOREIGN KEY (`user_username`)
    REFERENCES `email_schema`.`user` (`username`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = INNODB
DEFAULT CHARACTER SET = utf8;



CREATE TABLE IF NOT EXISTS `email_schema`.`email_draftbox` (
  `idemail_draftbox` INT(11) NOT NULL AUTO_INCREMENT,
  `user_username` VARCHAR(45) NOT NULL,
  `mail_name` VARCHAR(45) NULL DEFAULT NULL,
  `mail_receiptUser` VARCHAR(45) NULL DEFAULT NULL,
  `mail_byTime` CHAR(20) NULL DEFAULT NULL,
  `mail_content` VARCHAR(2000) NULL DEFAULT NULL,
  PRIMARY KEY (`idemail_draftbox`),
  INDEX `fk_email_draftbox_user1` (`user_username` ASC),
  CONSTRAINT `fk_email_draftbox_user1`
    FOREIGN KEY (`user_username`)
    REFERENCES `email_schema`.`user` (`username`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = INNODB
DEFAULT CHARACTER SET = utf8;



CREATE TABLE IF NOT EXISTS `email_schema`.`email_inbox` (
  `idemail_inbox` INT(11) NOT NULL AUTO_INCREMENT,
  `user_username` VARCHAR(45) NOT NULL,
  `mail_name` VARCHAR(45) NOT NULL,
  `mail_byUser` VARCHAR(45) NOT NULL,
  `mail_byTime` CHAR(20) NOT NULL,
  `mail_content` VARCHAR(2000) NULL DEFAULT NULL,
  `mail_status` INT(11) NULL DEFAULT NULL,
  PRIMARY KEY (`idemail_inbox`),
  INDEX `fk_email_inbox_user_idx` (`user_username` ASC),
  CONSTRAINT `fk_email_inbox_user`
    FOREIGN KEY (`user_username`)
    REFERENCES `email_schema`.`user` (`username`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = INNODB
DEFAULT CHARACTER SET = utf8;



CREATE TABLE IF NOT EXISTS `email_schema`.`email_outbox` (
  `idemail_outbox` INT(11) NOT NULL AUTO_INCREMENT,
  `user_username` VARCHAR(45) NOT NULL,
  `mail_name` VARCHAR(45) NOT NULL,
  `mail_receiptUser` VARCHAR(45) NOT NULL,
  `mail_byTime` CHAR(20) NOT NULL,
  `mail_content` VARCHAR(2000) NULL DEFAULT NULL,
  `mail_status` INT(11) NOT NULL,
  PRIMARY KEY (`idemail_outbox`),
  INDEX `fk_email_outbox_user1` (`user_username` ASC),
  CONSTRAINT `fk_email_outbox_user1`
    FOREIGN KEY (`user_username`)
    REFERENCES `email_schema`.`user` (`username`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = INNODB
DEFAULT CHARACTER SET = utf8;

