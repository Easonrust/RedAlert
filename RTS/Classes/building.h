#include"cocos2d.h"
#include"iostream"
#include<algorithm>
USING_NS_CC;
using namespace std;
class building :public cocos2d::Sprite
{
private:
public:
	int health = 1000;
	bool Selected = 0;
	static building*create(const std::string& filename);
	static void judge_seleted(Vector<building*>vec,Vec2 mouse_down,Vec2 mouse_up);
	static bool isTap(cocos2d::Vec2 mouselocation, cocos2d::Node*node);
	static void clear(Vector<building*>vec);
	Node*buildingnode;//取得该建筑的节点
};
