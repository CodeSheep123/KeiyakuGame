#ifndef KEIYAKU_SCENE_HPP_
#define KEIYAKU_SCENE_HPP_

#include <list>

namespace Keiyaku
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		
		void addEntity(std::shared_ptr<Entity> entity);
		void removeEntity(std::shared_ptr<Entity> entity);

		void clear();

		void update();
		void draw();

	protected:
		std::list<std::shared_ptr<Entity>> m_entities;
	};
}

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                     