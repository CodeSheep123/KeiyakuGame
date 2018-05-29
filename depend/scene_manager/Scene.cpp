#include "Scene.hpp"
#include "../../Entity.hpp"

#include <algorithm>

namespace Keiyaku
{
	Scene::Scene() = default;

	void Scene::addEntity(std::shared_ptr<Entity> entity)
	{
		m_entities.push_back(entity);
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
		std::for_each(std::begin(m_entities), std::end(m_entities), [](std::shared_ptr<Entity> e) {e->onSceneExit(); });
		m_entities.clear();
	}

	void Scene::update()
	{
		std::for_each(std::begin(m_entities), std::end(m_entities), [](std::shared_ptr<Entity> e) {e->update(); });
	}

	void Scene::draw()
	{
		std::for_each(std::begin(m_entities), std::end(m_entities), [](std::shared_ptr<Entity> e) {e->draw(); });
	}
}