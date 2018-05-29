#ifndef KEIYAKU_ENTITY_HPP_
#define KEIYAKU_ENTITY_HPP_

#include <memory>

namespace Keiyaku
{
	class Scene;

	class Entity : public std::enable_shared_from_this<Entity>
	{
	public:
		Entity();
		Entity(Scene* manager);
		virtual ~Entity() = default;

		void setScene(Scene* scene);
		Scene* getScene();

		void destroy();

		virtual void update() = 0;
		virtual void draw() = 0;

		/*Called when an object enters the scene*/
		virtual void onSceneEnter();
		/*Called when an object exits the scene*/
		virtual void onSceneExit();
	private:
		Scene* m_manager;
	};
}

#endif