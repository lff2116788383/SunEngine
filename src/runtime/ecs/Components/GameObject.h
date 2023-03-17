#pragma once
#include "entt/entt.hpp"
class GameObject
{
public:
	GameObject();
	~GameObject();

	//template<class T, class... Args>
	//// 应该返回创建的Component, 模板函数都应该放到.h文件里
	//T& AddComponent(Args&& ...args)
	//{
	//	//auto s = new T(args...);
	//	std::shared_ptr<Scene> p = m_Scene.lock();

	//	if (p)
	//		return p->GetRegistry().emplace<T>(m_InsanceId, std::forward<Args>(args)...);
	//}

	//template<class T>
	//bool HasComponent()
	//{
	//	std::shared_ptr<Scene> p = m_Scene.lock();

	//	if (p)
	//		return p->GetRegistry().all_of<T>(m_InstanceId);

	//	return false;
	//}

	//template<class T>
	//T& GetComponent()
	//{
	//	HAZEL_ASSERT(HasComponent<T>(), "GameObject Does Not Have The Specified Component!")

	//		std::shared_ptr<Scene> p = m_Scene.lock();

	//	return p->GetRegistry().get<T>(m_InsanceId);
	//}

	operator entt::entity() { return m_pChild; }
	operator entt::entity() const { return m_pChild; }

private:
	entt::entity m_pChild;
};

