//
//  Created by �ض��� on 15/12/10.
//  ������վ��http://www.51work6.com
//  �ǽݿ������߿��ã�http://www.zhijieketang.com/
//  �ǽݿ���΢�Ź����ţ�zhijieketang
//  ����΢����@tony_�ض���
//  ����΢�ţ�tony�ض���
//  QQ��569418560 ���䣺eorient@sina.com
//  QQ����Ⱥ��162030268
//

#ifndef __Select_SCENE_H__
#define __Select_SCENE_H__

#include "cocos2d.h"

class Select : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//�˵���ص�����
	void menuLastToggleCallback(cocos2d::Ref* pSender);
	void menuMap1ToggleCallback(cocos2d::Ref* pSender);
	void menuMap2ToggleCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Select);
};

#endif // __Setting_SCENE_H__

