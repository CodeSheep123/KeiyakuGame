#ifndef KEIYAKU_PATH_DATABASE_HPP_
#define KEIYAKU_PATH_DATABASE_HPP_

#include <string_view>
#include <unordered_map>

namespace Keiyaku
{
	class PathDatabase
	{
	public:
		PathDatabase() = default;
		PathDatabase(std::string_view path);
		PathDatabase(PathDatabase const& other) = default;
		PathDatabase(PathDatabase&& other) = default;

		PathDatabase& operator=(PathDatabase const& other) = default;
		PathDatabase& operator=(PathDatabase&& other) = default;

		~PathDatabase() = default;

		std::string getPath(std::string_view id) const;
		std::string getID(std::string_view path) const;

		void set(std::string_view id, std::string_view path);

		void load(std::string_view path);
		void save(std::string_view path) const;

	private:
		//map from Path -> ID
		std::unordered_map<std::string, std::string> m_ids;

		//map from ID -> Path
		std::unordered_map<std::string, std::string> m_paths;
	};
}

#endif