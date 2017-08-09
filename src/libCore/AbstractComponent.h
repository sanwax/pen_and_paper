#pragma once

#include <list>
#include <string>
#include <cstdint>

namespace core
{

	/**
	 * @brief Defines the interface for plugin-like components shaped as libraries such as chat window/dice roller/...
	 */
	class AbstractComponent
	{
		public:
			/**
			 * @brief Constructor
			 */
			AbstractComponent() = default;


			/**
			 * @brief Destructor
			 */
			virtual
			~AbstractComponent() = default;


			/**
			 * @brief Used for version ordering
			 * @return a monotonically growing version number
			 */
			virtual
			std::uint32_t
			version() const =0;


			/**
			 * @brief Every plugin has a name
			 * @return plugin name
			 * @note Shall be limited to [a-zA-Z0-9]*
			 */
			virtual
			std::string
			name() const =0;


			/**
			 * @brief Getter
			 * @return list of dependencies (shaped as name <,>,=,>=,<= version strings)
			 */
			virtual
			std::list<std::string>
			dependsOn() const=0;
	};

}
