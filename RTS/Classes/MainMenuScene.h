//
//  Created by 关东升 on 15/12/10.
//  本书网站：http://www.51work6.com
//  智捷课堂在线课堂：http://www.zhijieketang.com/
//  智捷课堂微信公共号：zhijieketang
//  作者微博：@tony_关东升
//  作者微信：tony关东升
//  QQ：569418560 邮箱：eorient@sina.com
//  QQ交流群：162030268
//

#ifndef __MainMenu_SCENE_H__
#define __MainMenu_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "Selectscene.h"

class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	//菜单项回调函数
    void menuItemExitCallback(cocos2d::Ref* pSender);
    void menuItemStartCallback(cocos2d::Ref* pSender);
	void menuItemSettingCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif // __MainMenu_SCENE_H__
