/*
Navicat MySQL Data Transfer

Source Server         : wsj
Source Server Version : 50728
Source Host           : localhost:3306
Source Database       : communitymanagement

Target Server Type    : MYSQL
Target Server Version : 50728
File Encoding         : 65001

Date: 2024-07-10 22:46:43
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for activityinfo
-- ----------------------------
DROP TABLE IF EXISTS `activityinfo`;
CREATE TABLE `activityinfo` (
  `activity_id` int(11) NOT NULL AUTO_INCREMENT,
  `activity_name` varchar(100) NOT NULL,
  `application_date` date DEFAULT NULL,
  `location` varchar(100) DEFAULT NULL,
  `club_id` int(11) DEFAULT NULL,
  `approval_date` date DEFAULT NULL,
  `approval_status` varchar(20) DEFAULT NULL,
  `introduction` text,
  `organizer` varchar(100) DEFAULT NULL,
  `scale` varchar(50) DEFAULT NULL,
  `budget` decimal(10,2) DEFAULT NULL,
  `start_time` datetime DEFAULT NULL,
  `end_time` datetime DEFAULT NULL,
  `join_num` int(10) unsigned zerofill DEFAULT NULL,
  PRIMARY KEY (`activity_id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of activityinfo
-- ----------------------------
INSERT INTO `activityinfo` VALUES ('1', '篮球比赛', '2024-05-01', '体育馆', '1', '2024-05-05', '待审核', '本次篮球比赛是为了丰富同学们的课余生活，提高体育运动参与度。', '篮球社', '大型', '5000.00', '2024-05-10 09:00:00', '2024-05-10 18:00:00', '0000000062');
INSERT INTO `activityinfo` VALUES ('2', '音乐会', '2024-04-25', '礼堂', '2', '2024-04-30', '已通过', '音乐会将邀请各种乐器演奏，展示学生的音乐才华。', '音乐社', '中型', '3000.00', '2024-05-15 19:00:00', '2024-05-15 21:00:00', '0000000001');
INSERT INTO `activityinfo` VALUES ('3', '舞蹈表演', '2024-05-03', '多功能厅', '3', '2024-05-07', '已通过', '舞蹈表演将展示多种风格的舞蹈，吸引广大观众欣赏。', '舞蹈社', '小型', '1500.00', '2024-05-20 18:30:00', '2024-05-20 20:30:00', '0000000001');
INSERT INTO `activityinfo` VALUES ('4', '乒乓球友谊赛', '2024-04-28', '体育馆', '4', '2024-05-02', '已通过', '乒乓球友谊赛将邀请周边学校参与，增进学校间的交流。', '乒乓球社', '中型', '2000.00', '2024-05-25 08:00:00', '2024-05-25 12:00:00', '0000000001');
INSERT INTO `activityinfo` VALUES ('5', '摄影展览', '2024-05-05', '学生活动中心', '5', '2024-05-09', '已通过', '摄影展览将展示学生们的摄影作品，分享摄影经验。', '摄影社', '小型', '1000.00', '2024-05-30 10:00:00', '2024-05-30 16:00:00', '0000000000');
INSERT INTO `activityinfo` VALUES ('6', '篮球友谊赛', '2024-05-02', '体育馆', '6', '2024-05-06', '已通过', '篮球友谊赛将邀请周边学校参与，增进学校间的交流。', '篮球社', '中型', '2000.00', '2024-06-05 14:00:00', '2024-06-05 18:00:00', '0000000001');
INSERT INTO `activityinfo` VALUES ('7', '游戏竞赛', '2024-05-04', '多功能厅', '7', '2024-05-08', '已通过', '游戏竞赛将举办各种类型的游戏比赛，欢迎广大同学参与。', '游戏社', '小型', '1000.00', '2024-06-10 13:00:00', '2024-06-10 17:00:00', '0000000000');
INSERT INTO `activityinfo` VALUES ('8', '英语角', '2024-04-30', '学生活动中心', '8', '2024-05-04', '已通过', '英语角将提供一个练习英语口语的平台，鼓励学生积极参与。', '英语社', '小型', '1000.00', '2024-06-15 15:00:00', '2024-06-15 17:00:00', '0000000000');
INSERT INTO `activityinfo` VALUES ('9', '篮球训练营', '2024-05-10', '体育馆', '9', '2024-05-14', '已通过', '篮球训练营将邀请专业教练指导，提高学生的篮球技术。', '篮球社', '大型', '8000.00', '2024-06-20 08:00:00', '2024-06-21 18:00:00', '0000000002');
INSERT INTO `activityinfo` VALUES ('10', '摄影活动', '2024-05-06', '学生活动中心', '10', '2024-05-10', '已通过', '摄影活动将举办户外摄影活动，拍摄美丽的风景。', '摄影社', '中型', '3000.00', '2024-06-25 09:00:00', '2024-06-25 16:00:00', '0000000001');

-- ----------------------------
-- Table structure for admin
-- ----------------------------
DROP TABLE IF EXISTS `admin`;
CREATE TABLE `admin` (
  `admin_id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `name` varchar(100) NOT NULL,
  `gender` varchar(10) DEFAULT NULL,
  `contact` varchar(20) DEFAULT NULL,
  `privilege_level` int(11) DEFAULT NULL,
  `join_date` date DEFAULT NULL,
  `managed_club_name` varchar(100) DEFAULT '篮球社',
  PRIMARY KEY (`admin_id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of admin
-- ----------------------------
INSERT INTO `admin` VALUES ('1', '1000', '1111', '王苏杰', '女', '13987654321', '2', '2024-01-02', '篮球社');
INSERT INTO `admin` VALUES ('2', '1001', '1111', '王翠花', '女', '13678901234', '2', '2023-07-25', '音乐社');
INSERT INTO `admin` VALUES ('3', '1002', '1111', '赵龙', '男', '13567890123', '2', '2024-05-09', '舞蹈社');
INSERT INTO `admin` VALUES ('4', '1003', '1111', '钱多多', '男', '13789012345', '2', '2024-05-24', '摄影社');
INSERT INTO `admin` VALUES ('5', '1004', '1111', '李金龙', '男', '13890123456', '2', '2024-05-29', '乒乓球社');
INSERT INTO `admin` VALUES ('6', '1005', '1111', '周丽', '女', '13901234567', '2', '2024-05-27', '英语交流社');
INSERT INTO `admin` VALUES ('7', '1006', '1111', '吴香香', '女', '13876543210', '2', '2024-05-31', '书法社');

-- ----------------------------
-- Table structure for announcement
-- ----------------------------
DROP TABLE IF EXISTS `announcement`;
CREATE TABLE `announcement` (
  `announcement_id` int(11) NOT NULL AUTO_INCREMENT,
  `announcement_name` varchar(100) NOT NULL,
  `announcement_content` text,
  `publish_date` datetime DEFAULT NULL,
  `publisher` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`announcement_id`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of announcement
-- ----------------------------
INSERT INTO `announcement` VALUES ('1', '校园篮球赛通知', '校园篮球赛将于5月20日在体育馆举行，请各班组织队伍报名参加。', '2024-06-03 10:48:54', '篮球社');
INSERT INTO `announcement` VALUES ('2', '音乐会通知', '本学期音乐会将于5月15日晚在礼堂举行，欢迎各位同学前来观赏。', '2024-05-05 09:30:00', '音乐社');
INSERT INTO `announcement` VALUES ('3', '校园环保活动通知', '为了提高环保意识，校园环保活动将于5月25日上午在操场举行，请各班班级积极参与。', '2024-05-15 10:00:00', '系统管理员1');
INSERT INTO `announcement` VALUES ('4', '招聘会通知', '本学期招聘会将于5月30日上午在学生活动中心举行，欢迎各位同学前来参加。', '2024-05-20 13:00:00', '系统管理员1');
INSERT INTO `announcement` VALUES ('5', '暑期社会实践招募通知', '暑期社会实践活动即将开始，现在开始招募志愿者，有意愿者请前往学生会报名。', '2024-05-25 14:00:00', '系统管理员1');
INSERT INTO `announcement` VALUES ('6', '书法招新', '新学期新气象，书法社欢迎同学们加入。', '2024-09-01 15:00:00', '书法社');
INSERT INTO `announcement` VALUES ('7', '图书馆借阅规定变更通知', '为了更好地管理图书馆资源，现对图书借阅规定进行了调整，请同学们遵守。', '2024-08-25 09:00:00', '系统管理员1');
INSERT INTO `announcement` VALUES ('8', '学校防疫措施调整通知', '根据最新疫情情况，学校将对防疫措施进行调整，请同学们注意查看并遵守。', '2024-07-15 11:30:00', '校医院');
INSERT INTO `announcement` VALUES ('9', '暑期学术会议通知', '本学期暑期学术会议将于7月20日在学术报告厅举行，欢迎各位同学前来参加。', '2024-07-05 08:30:00', '学术部');
INSERT INTO `announcement` VALUES ('10', '学期末考试安排通知', '本学期学期末考试安排已出，请同学们及时查看考试时间及考场安排。', '2024-06-30 10:00:00', '教务处');
INSERT INTO `announcement` VALUES ('11', '开展摄影知识辩论赛', '通过会员间对摄影理论的辩论，达到对摄影理论的深入思考，从而更深的认识摄影哲学。通过这种活跃的形式可以增加会员的积极性和对摄影的兴趣。', '2024-05-19 01:18:21', '摄影社团');
INSERT INTO `announcement` VALUES ('12', '举办摄影展', '我们协会会将整个上学期会员在采风过程中的拍摄优秀作品进行展示。不仅为学院增加一道亮丽的风景线，同时也可以让我们对自己有一个全新的定位和认识，从而去更好的学习，弥补自己的不足，不断发现自己不足，不断继续深入解析摄影。', '2024-05-19 01:19:07', '摄影社团');
INSERT INTO `announcement` VALUES ('13', '乒乓球社团简介', '社团活动目标：促进同学们对国球的了解和热爱，培养竞争意识，发展我校乒乓球运动，创建乒乓球队员之间相互学习，共同进步的优良环境。我们社团是一个14位同学的组成大家庭，夏老师耐心组织指导社团活动，不断激发更多的同学投身其中，强身健体，提高乒乓球技术水平，树立顽强拼搏的精神，并在活动中逐渐形成团队意识。', '2024-05-28 21:55:45', '乒乓球社');
INSERT INTO `announcement` VALUES ('14', '招聘舞蹈员', '诚信招聘有舞蹈经验的舞蹈者，这里需要你，如果看到本篇公告，请与我们联系，联系电话：12345676', '2024-05-28 23:52:09', '舞蹈社');
INSERT INTO `announcement` VALUES ('15', '招聘舞蹈员', '诚信招聘有舞蹈经验的舞蹈者，这里需要你，如果看到本篇公告，请与我们联系，联系电话：12345676', '2024-05-28 23:52:28', '舞蹈社');
INSERT INTO `announcement` VALUES ('16', '篮球社招新', '欢迎爱好篮球、会玩篮球的同学加入社团。加入社团后能够一起打篮球', '2024-05-30 10:37:49', '篮球社');
INSERT INTO `announcement` VALUES ('17', '音乐活动', '音乐节到了，音乐社将举办音乐欢乐节，请同学们积极投稿', '2024-05-30 23:37:07', '音乐社');
INSERT INTO `announcement` VALUES ('18', '乒乓球活动', '为加强与其他社团的交流，响应学院社团文化艺术巡礼，融合学院多年艺术巡礼文化，加深各学院同学对乒乓球协会的认识。同时让同学们有机会认识乒乓球技术，增长对乒乓球的认识。', '2024-05-31 23:29:05', '乒乓球社');
INSERT INTO `announcement` VALUES ('19', '英语单词竞赛', '本月底将进行英语单词竞赛，请参加本次比赛的同学进行准备。', '2024-05-01 23:32:05', '英语交流社');
INSERT INTO `announcement` VALUES ('20', '校园篮球赛通知111', '校园篮球赛将于5月20日在体育馆举行，请各班组织队伍报名参加。', '2024-06-02 21:21:33', '篮球社');
INSERT INTO `announcement` VALUES ('22', '音乐会举办', '学校将举办音乐活动', '2024-06-03 10:56:51', '音乐社');
INSERT INTO `announcement` VALUES ('24', '教育局发布通知', '我们需要将毕业论文在2024年6月15日之前整理完毕，希望大家能够顺利毕业。', '2024-06-03 11:00:10', '教务处');

-- ----------------------------
-- Table structure for apply_join
-- ----------------------------
DROP TABLE IF EXISTS `apply_join`;
CREATE TABLE `apply_join` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `applicant_name` varchar(255) NOT NULL,
  `club_name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=26 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of apply_join
-- ----------------------------
INSERT INTO `apply_join` VALUES ('1', '2000', '篮球社');
INSERT INTO `apply_join` VALUES ('4', '2002', '篮球社');
INSERT INTO `apply_join` VALUES ('6', '2008', '音乐社');
INSERT INTO `apply_join` VALUES ('7', '2009', '舞蹈社');
INSERT INTO `apply_join` VALUES ('9', '2011', '舞蹈社');
INSERT INTO `apply_join` VALUES ('24', '2000', '篮球社');
INSERT INTO `apply_join` VALUES ('25', '2000', '书法社');

-- ----------------------------
-- Table structure for clubinfo
-- ----------------------------
DROP TABLE IF EXISTS `clubinfo`;
CREATE TABLE `clubinfo` (
  `club_id` int(11) NOT NULL AUTO_INCREMENT,
  `club_name` varchar(100) NOT NULL,
  `category` varchar(50) DEFAULT NULL,
  `establishment_date` date DEFAULT NULL,
  `leader` varchar(100) DEFAULT NULL,
  `contact` varchar(50) DEFAULT NULL,
  `introduction` text,
  `remarks` text,
  `picture` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`club_id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of clubinfo
-- ----------------------------
INSERT INTO `clubinfo` VALUES ('1', '篮球社', '体育运动', '2024-01-02', '王苏杰', '13812345678', '篮球社是一个致力于推广篮球运动的社团。是一项运动活动。篮球是一项运动', '', 'C:/Users/18358/Desktop/work/community/images/15.jpg');
INSERT INTO `clubinfo` VALUES ('2', '音乐社', '艺术文化', '2023-07-25', '王翠花', '13987654321', '音乐社致力于提高学生的音乐素养，举办各种音乐活动。', '', 'C:/Users/18358/Desktop/work/community/images/img2.jpg');
INSERT INTO `clubinfo` VALUES ('3', '舞蹈社', '艺术文化', '2024-05-09', '赵龙', '13678901234', '舞蹈社是一个跳舞的社团', '', 'C:/Users/18358/Desktop/work/community/images/img5.jpg');
INSERT INTO `clubinfo` VALUES ('4', '摄影社', '艺术文化', '2024-05-24', '钱多多', '13567890123', '摄影社致力于培养学生的摄影技能，举办各种摄影活动。', '', 'C:/Users/18358/Desktop/work/community/images/img4.jpg');
INSERT INTO `clubinfo` VALUES ('5', '乒乓球社', '艺术文化', '2024-05-29', '李金龙', '13789012345', '乒乓球社是一个致力于推广乒乓球运动的社团。', '', 'C:/Users/18358/Desktop/work/community/images/img7.jpg');
INSERT INTO `clubinfo` VALUES ('6', '英语交流社', '艺术文化', '2024-05-27', '周丽', '123123', '英语交流社致力于提高学生的英语口语和交流能力，举办英语角和英语沙龙。', '', 'C:/Users/18358/Desktop/work/community/images/img9.jpg');
INSERT INTO `clubinfo` VALUES ('7', '书法社', '艺术文化', '2024-05-31', '吴香香', '13876543210', '书法社致力于培养学生的书法技能，举办各种书法活动。', '', 'C:/Users/18358/Desktop/work/community/images/img6.jpg');
INSERT INTO `clubinfo` VALUES ('8', '飞棋社', '艺术文化', null, '王苏杰', '178389344', '是公司上班方便', null, 'C:/Users/18358/Desktop/work/community/images/12.jpg');

-- ----------------------------
-- Table structure for students
-- ----------------------------
DROP TABLE IF EXISTS `students`;
CREATE TABLE `students` (
  `student_id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `student_number` varchar(20) NOT NULL,
  `club_name` varchar(100) DEFAULT NULL,
  `contact` varchar(50) DEFAULT NULL,
  `class` varchar(50) DEFAULT NULL,
  `department` varchar(100) DEFAULT NULL,
  `club_role` varchar(50) DEFAULT NULL,
  `join_date` date DEFAULT NULL,
  `join_action` text,
  `password` varchar(50) DEFAULT '123456',
  `application_status` tinyint(1) DEFAULT '0',
  `gender` varchar(10) DEFAULT '男',
  `age` int(11) DEFAULT '18',
  `avatar_path` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`student_id`),
  UNIQUE KEY `student_number` (`student_number`)
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of students
-- ----------------------------
INSERT INTO `students` VALUES ('1', '王苏杰', '1000', '篮球社', '13987654321', '2班', '计科111', '社团管理员', '2024-01-02', '篮球比赛', '1111', '0', '女', '18', 'C:/Users/18358/Pictures/OIP-C (4).jpg');
INSERT INTO `students` VALUES ('2', '王翠花', '1001', '音乐社', '13678901234', '3班', '计科223', '社团管理员', '2023-07-25', null, '1111', '0', '女', '18', 'C:/Users/18358/Desktop/work/community/images/img2.jpg');
INSERT INTO `students` VALUES ('3', '赵龙', '1002', '舞蹈社', '13567890123', '1班', '会计221', '社团管理员', '2024-05-09', null, '1111', '0', '男', '18', 'C:/Users/18358/Desktop/work/community/images/img5.jpg');
INSERT INTO `students` VALUES ('4', '钱多多', '1003', '摄影社', '13789012345', '2班', '市场营销111', '社团管理员', '2024-05-24', null, '1111', '0', '男', '18', 'C:/Users/18358/Desktop/work/community/images/img4.jpg');
INSERT INTO `students` VALUES ('5', '李金龙', '1004', '乒乓球社', '13890123456', '3班', '电气112', '社团管理员', '2024-05-29', null, '1111', '0', '男', '21', 'C:/Users/18358/Desktop/work/community/images/img7.jpg');
INSERT INTO `students` VALUES ('6', '周丽', '1005', '英语交流社', '13901234567', '4班', '护理222', '社团管理员', '2024-06-03', null, '1111', '0', '女', '22', 'C:/Users/18358/Desktop/work/community/images/img9.jpg');
INSERT INTO `students` VALUES ('7', '吴香香', '1006', '书法社', '13876543210', '5班', '计科224', '社团管理员', '2024-05-31', null, '1111', '0', '女', '18', 'C:/Users/18358/Desktop/work/community/images/img6.jpg');
INSERT INTO `students` VALUES ('8', '许甜甜', '2000', '', '13654321098', '6班', '计科202', '', '2024-06-03', null, '1111', '0', '男', '20', 'C:/Users/18358/Pictures/R-C.jpg');
INSERT INTO `students` VALUES ('9', '王珂', '2001', '篮球社', '13543210987', '7班', '会计223', '', '2024-06-04', null, '1111', '0', '男', '23', 'C:/Users/18358/Desktop/work/community/images/11.jpg');
INSERT INTO `students` VALUES ('10', '张华华', '2002', '', '13812345678', '1班', '市场营销221', '', '2024-06-03', null, '1111', '0', '男', '18', 'C:/Users/18358/Desktop/work/community/images/img2.jpg');
INSERT INTO `students` VALUES ('11', '王龙龙', '2003', '篮球社', '13987654321', '2班', '大数据191', '成员', '2024-04-24', null, '1111', '0', '女', '25', 'C:/Users/18358/Desktop/work/community/images/img4.jpg');
INSERT INTO `students` VALUES ('12', '王健康', '2004', '摄影社', '13678901234', '3班', '计科224', '成员', '2024-03-19', null, '1111', '0', '男', '19', 'C:/Users/18358/Desktop/work/community/images/img4.jpg');
INSERT INTO `students` VALUES ('13', '王淑杰', '2005', '篮球社', '12345345644', '3班', '酒店管理212', '成员', '2024-05-30', null, '1111', '0', '男', '22', 'C:/Users/18358/Desktop/work/community/images/11.jpg');
INSERT INTO `students` VALUES ('14', '庞芳芳', '2006', '', '19863728393', '6班', '电气223', '', '2024-06-03', null, '1111', '0', '女', '23', 'C:/Users/18358/Desktop/work/community/images/img11.jpg');
INSERT INTO `students` VALUES ('15', '王光杰', '2007', '乒乓球社', '15225724464', '2班', '软件工程', '成员', '2024-06-01', null, '1111', '0', '男', '18', 'C:/Users/18358/Desktop/work/community/images/img4.jpg');
INSERT INTO `students` VALUES ('16', '李欣欣', '2008', null, '14543475469', '4班', '护理223', null, '2024-06-03', null, '1111', '0', '男', '25', null);
INSERT INTO `students` VALUES ('17', '张华华', '2009', null, '18765737538', '3班', '土木221', null, '2024-04-17', null, '1111', '0', '男', '18', null);
INSERT INTO `students` VALUES ('18', '章子怡', '2010', null, '18537546687', '1班', '土木223', null, '2024-04-04', null, '1111', '0', '女', '22', null);
INSERT INTO `students` VALUES ('19', '郑兰兰', '2011', null, '18768543335', '5班', '软件工程1', null, '2024-03-12', null, '1111', '0', '男', '24', null);
INSERT INTO `students` VALUES ('20', '欧阳兰', '2012', '篮球社', '15357544357', '6班', '计科112', '成员', '2024-04-18', null, '1111', '0', '男', '19', null);
INSERT INTO `students` VALUES ('21', '上官宏', '2013', '篮球社', '16548654456', '7班', '小学教育1', '成员', '2024-02-29', null, '1111', '0', '男', '18', null);
INSERT INTO `students` VALUES ('22', '高瀚宇', '2024', '篮球社', '17657475334', '2班', '学前教育', '成员', '2024-02-13', null, '1111', '0', '男', '26', null);

-- ----------------------------
-- Table structure for superadmin
-- ----------------------------
DROP TABLE IF EXISTS `superadmin`;
CREATE TABLE `superadmin` (
  `admin_id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `name` varchar(100) NOT NULL,
  `gender` varchar(10) DEFAULT NULL,
  `contact` varchar(20) DEFAULT NULL,
  `privilege_level` int(11) DEFAULT NULL,
  `join_date` date DEFAULT NULL,
  PRIMARY KEY (`admin_id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of superadmin
-- ----------------------------
INSERT INTO `superadmin` VALUES ('6', '0000', '0000', '超级管理员', '男', '13800000000', '10', '2024-05-06');

-- ----------------------------
-- Table structure for user_permissions
-- ----------------------------
DROP TABLE IF EXISTS `user_permissions`;
CREATE TABLE `user_permissions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `permissions` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=583 DEFAULT CHARSET=utf8mb4;

-- ----------------------------
-- Records of user_permissions
-- ----------------------------
INSERT INTO `user_permissions` VALUES ('582', '0000', '1');
