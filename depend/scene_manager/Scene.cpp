#include "Scene.hpp"
#include "../../Entity.hpp"

#include <algorithm>

namespace Keiyaku
{
	Scene::Scene() = default;

	void Scene::addEntity(std::shared_ptr<Entity> entity)
	{
		m_entities.push_back(entity);
		entity->setScene(this);
		entity->onSceneEnter();
	}

	void Scene::removeEntity(std::shared_ptr<Entity> entity)
	{
		/*Erase entity*/
		entity->onSceneExit();
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(),
			std::find(m_entities.begin(), m_entities.end(), entity)));
	}

	void Scene::clear()
	{
		for (auto& e : m_entities)
		{
			e->onSceneExit();
		}
		m_entities.clear();
	}

	void Scene::update()
	{
		for (auto& e : m_entities)
		{
			e->update();
		}
	}

	void Scene::draw()
	{
		for (auto& e : m_entities)
		{
			e->draw();
		}
	}
}