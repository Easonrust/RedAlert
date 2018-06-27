#include "room.h"
#include "extensions\cocos-ext.h"  

USING_NS_CC_EXT;
USING_NS_CC;
using namespace cocos2d::extension;
using namespace CocosDenshion;
//string message;

//extern SOCKET sClient;
//char camp[1] = { '2' };

Scene* Room::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Room::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

	// Print useful error message instead of segfaulting when files are not there.
	static void problemLoading(const char* filename)
	{
		printf("Error while loading: %s\n", filename);
		printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in InputIPScene.cpp\n");
	}

	// on "init" you need to initialize your instance
	bool Room::init()
	{
     /*   //��ʼ��
		if (!InitClient())
		{
			ExitClient();
		}

		//���ӷ�����
		if (ConnectServer())
		{
			ShowConnectMsg(TRUE);
		}
		else
		{
			ShowConnectMsg(FALSE);
			ExitClient();
		}

		int rcamp = recv(sClient, camp, 1, 0);
		if (rcamp>0)
		{
			cout << "camp:" << camp << endl;
		}*/
	auto visibleSize = Director::getInstance()->getVisibleSize();//visiblezSize
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//origm
	/*if (camp[1] == '1')
	{
		Sprite *head = Sprite::create("head1.jpg");
		// position the label on the center of the screen
		head->setPosition(Vec2(origin.x + visibleSize.width *0.7,
			origin.y + visibleSize.height*0.7));
		this->addChild(head);
	}
	else
	{
		Sprite *head = Sprite::create("head2.jpg");
		// position the label on the center of the screen
		head->setPosition(Vec2(origin.x + visibleSize.width *0.9,
			origin.y + visibleSize.height*0.9));
		this->addChild(head);
	}
	//�������������߳�
	_beginthreadex(NULL, 0, clientreceiveThread, &sClient, 0, NULL); //����������Ϣ�߳�
	*/
	//////////////////////////////
	// 1. super init first
	
	if (!Layer::init())
	{
		return false;
	}

	Sprite *bg = Sprite::create("background.jpg");

	// position the label on the center of the screen
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);


	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto gobackItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Room::menuGobackCallback, this));
		float x = origin.x + visibleSize.width - gobackItem->getContentSize().width / 2;
		float y = origin.y + gobackItem->getContentSize().height / 2;
		gobackItem->setPosition(Vec2(x, y));

		// create menu, it's an autorelease object
		auto menu = Menu::create(gobackItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1);

		/////////////////////////////
		// 3. add your codes below...

		// add a label shows "Hello World"
		// create and initialize a label

	/*	auto editbox1 = EditBox::create(Size(300, 55), Scale9Sprite::create("text.png"));
		editbox1->setAnchorPoint(Point(0, 0));
		editbox1->setPosition(Point(visibleSize.width *0.3, visibleSize.height*0.55));
		editbox1->setPlaceHolder("����������Ϣ:");//ռλ�ַ�  
		editbox1->setMaxLength(100);
		editbox1->setFontColor(Color3B::BLACK);//���������������ɫ  
		editbox1->setTag(1);
		this->addChild(editbox1, 2);
		//�һ���ť

		auto Enterbuttom = MenuItemImage::create("enterbutton.png", "enterbutton2.png");
		Enterbuttom->setCallback([&, editbox1](Ref*obj) {

			//ȡ���������������֣����������̨
			message = editbox1->getText();
			cout << "�ѷ�����Ϣ:"<<message;
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
				SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
			}
			log("%s", editbox1->getText());
			auto sc = HelloWorld::createScene();
			Director::getInstance()->pushScene(sc);
			
		});
		Menu* mu = Menu::create(Enterbuttom, NULL);
		mu->setPosition(origin.x + visibleSize.width * 0.3, origin.y + visibleSize.height * 0.2);//(Vec2(400, 260));
		this->addChild(mu);*/
		return true;
}

	void Room::menuGobackCallback(Ref* pSender)
	{
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		Director::getInstance()->popScene();
	}