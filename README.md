# RedAlert
	本游戏是一款模仿红色警戒的RTS类游戏，以1V1真人在线对战为主要内容，
共有“丛林”，“雪地”两种地图可供选择，可玩度较高，但由于临近期末，有些地方尚待改进。
游戏玩法：
	1.游戏双方初始金币为5000，电力为0。我方金币与电力在屏幕右上角状态栏显示。
	2.游戏内共有六种建筑，分别是：基地、发电厂、矿场、兵营、战车工厂，防御围墙，共有三种作战单位，分别是：士兵、仿生机器人、坦克。所有单位均有一定的物理体积。游戏中建筑永久显示血量，作战单位在收到攻击或选中状态时显示血量。我方单位血条为红色，地方单位血条为深蓝色。。
	3.金币：建造单位需要消耗一定的金币
	4.电力：除基地和防御围墙外的四种建筑都会消耗电力，电力就是一切
	5.单位属性详细介绍：
		(1)基地：初始生成，不可变形，生命值3000，
		(2)发电厂：建造需要800金币，提供250单位的电力，生命值1200，建造条件是拥有基地
		(3)矿场：建造需要2500金币，消耗150单位电力，生命值2000，在电力充足的情况下每秒产生100金币，电力提供不足时停止产生金币，建造条件是拥有基地和发电厂
		(4)兵营：建造需要1000金币，消耗100单位电力，生命值1400，可产生士兵，电力不足不会产生不良影响，建造条件是拥有基地和发电厂
		(5)战车工厂：建造需要2000金币，消耗120单位电力，生命值1900，可产生机器人和坦克，电力不足不会产生不良影响，建造条件是拥有基地和发电厂和兵营和矿场
        (6)防御围墙：建造需要400金币，消耗电力为0，具有物理体积可阻挡地方单位前进。
		(7)士兵：建造需要100金币，生命值100，攻击力1
		(8)机器人：建造需要300金币，生命值200，攻击力10
		(9)坦克：建造需要800金币，生命值500，攻击力10
	6.游戏内地图全开，无战争迷雾
	7.基本操作：本游戏无键盘操作，下方按钮右侧为单位所需金币。下方建筑按钮和兵种按钮在不符合建筑条件时有红色叉，此时点击会有提醒玩家不符合条件的音效。在符合建筑条件时，点击下方建筑按钮再点击地图上相应位置，可建造建筑；在符合条件时，点击下方兵种按钮可在兵营或战车工厂处生产士兵，机器人或坦克，此时会有相应音效。 在地图上拖动鼠标会出现引导矩形框，框选作战单位可进行选中（选中状态会显示血条），选中状态点击空地能移动到相应位置，点击敌方单位可前往攻击。当鼠标移动到屏幕边界时可以移动屏幕视角，查看地图其他位置。
8.输赢判断：游戏开始时敌我阵营在地图对角线位置(两张地图位置有差别)，阵营位置由服务器随机分配，敌我初始仅有双方基地。当一方将另一方的单位全部消灭后，便取得胜利，胜利者的屏幕中央会出现黄色“you win”字样，失败者会出现“you lose”字样。
游戏启动方式：远程服务器IP地址已内嵌，所以只需选择地图进入游戏即可，支持双人对战。
