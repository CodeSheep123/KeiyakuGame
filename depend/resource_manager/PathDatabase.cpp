#include "PathDatabase.hpp"

#include "../../ErrorHandler.hpp"

#include <fstream>
#include <string>

namespace Keiyaku
{
	PathDatabase::PathDatabase(std::string_view path)
	{
		load(path);
	}

	std::string PathDatabase::getID(std::string_view path) const
	{
		return m_ids.at(path.data());
	}

	std::string PathDatabase::getPath(std::string_view id) const
	{
		return m_paths.at(id.data());
	}

	void PathDatabase::set(std::string_view id, std::string_view path)
	{
		m_ids[path.data()] = id.data();
		m_paths[id.data()] = path.data();
	}

	void PathDatabase::load(std::string_view path)
	{
		std::ifstream in(path.data());
		if (!in.good())
		{
			ErrorHandler::reportError("PathDatabase::load(): Failed to open file: " + std::string(path));
		}

		std::string path_, id;

		while (in >> id >> path_)
		{
			m_paths.emplace(id, path_);
			m_ids.emplace(path_, id);
		}
	}

	void PathDatabase::save(std::string_view path) const
	{
		std::ofstream out(path.data(), std::ofstream::out | std::ostream::trunc);

		for (auto const&[id, data] : m_paths)
		{
			out << id << ' ' << data << '\n';
		}
	}
}