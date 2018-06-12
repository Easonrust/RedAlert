#include"building.h"
building* building::create(const std::string& filename)
{
	building *sprite = new building();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();//����������ڴ��Զ�����
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void building::judge_seleted(Vector<building*>vec, Vec2 mouse_down, Vec2 mouse_up)
{
	if (mouse_up == mouse_down)
	{
		for (int i = 0; i < vec.size(); i++) {
			auto node = vec.at(i)->buildingnode;
			//auto location = vec[i]->getPosition();//��������
			//auto p_size = vec[i]->getContentSize();
			if (isTap(mouse_down, node))//����Ƿ�㵽ͼƬ��,�������Զ���ĺ���isTap
			{
				vec.at(i)->Selected = 1;
			}
		}
	}
	if (mouse_up != mouse_down)
	{
		float x_min = min(mouse_up.x, mouse_down.x);
		float x_max = max(mouse_up.x, mouse_down.x);
		float y_min = min(mouse_up.y, mouse_down.y);
		float y_max = max(mouse_up.y, mouse_down.y);
		for (int i = 0; i < vec.size(); i++)
		{
			auto location = vec.at(i)->getPosition();//��������
			if (location.x >= x_min&&location.x <= x_max&& location.y >= y_min && location.y <= y_max)//����û�п���ͼƬ��С��������Ҫ�Ż�
			{
				vec.at(i)->Selected = 1;
			}
		}
	}
}
void building::clear(Vector<building*>vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		vec.at(i)->Selected = 0;
		//Ѫ����ʧ
	}
}
bool building::isTap(cocos2d::Vec2 mouselocation, cocos2d::Node*node)
{
	
	//location1.y = 900 - location1.y;
	Vec2 locationInNode = node->convertToNodeSpace(mouselocation);
	Size s = node->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.width);
	if (rect.containsPoint(locationInNode))
	{
		return true;
	}
	return false;
}