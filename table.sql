CREATE TABLE IF NOT EXISTS `traffic` (
    `date` date NOT NULL,
    `domain` varchar(50) NOT NULL,
    `proxy_pass` tinyint(1) unsigned NOT NULL default '0',
    `servername` varchar(50) NOT NULL,
    `logname` varchar(50) default NULL,
    `bytes_in` int(10) unsigned NOT NULL,
    `bytes_out` int(10) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
