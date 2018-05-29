#include "Entity.hpp"
#include "depend/scene_manager/Scene.hpp"
#include "ErrorHandler.hpp"

namespace Keiyaku
{

	Entity::Entity() : m_manager(nullptr)
	{}

	Entity::Entity(Scene* manager) : m_manager(manager)
	{
		ErrorHandler::assert(manager != nullptr, "Entity::Entity(): Scene is nullptr");
	}

	void Entity::setScene(Scene* scene)
	{
		if (scene != nullptr)
			m_manager = scene;
		else ErrorHandler::reportError("Entity::setScene(): Scene is nullptr");
	}

	Scene* Entity::getScene()
	{
		return m_manager;
	}

	void Entity::destroy()
	{
		m_manager->removeEntity(shared_from_this());
	}

}