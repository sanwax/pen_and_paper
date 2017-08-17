#pragma once

#include <cstdint>

namespace dds
{

	typedef uint64_t TopicType;


	/**
	 * @brief Hash function converting a topic name into a topic type numeric
	 * @tparam LEN length of character array
	 * @param [in] typeName name of type to convert
	 * @return djb2 hash of the name
	 * @ref http://www.cse.yorku.ca/~oz/hash.html
	 */
	template <unsigned int LEN>
	static
	constexpr
	dds::TopicType
	topicTypeNameToNumeric(const char (&typeName)[LEN])
	{
		dds::TopicType hash = 5381;
		for (auto c:typeName)
		{
			hash = ((hash << 5) + hash) + c;
		}
		return hash;
	}


}
