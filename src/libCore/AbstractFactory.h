#pragma once

#include <unordered_set>
#include <libCore/AbstractException.h>


namespace core
{
	typedef core::AbstractException FactoryException;


	/**
	 * @brief Template for all sorts of factories
	 * @tparam KEY - product key
	 * @tparam PRODUCT - product itself
	 */
	template<typename KEY, typename PRODUCT>
	class AbstractFactory
	{
		public:
			/**
			 * @brief Constructor
			 */
			AbstractFactory() = default;


			/**
			 * @brief Destructor
			 */
			virtual
			~AbstractFactory() = default;


			/**
			 * @brief Construct product by key
			 * @param [in] key - identifies the product
			 * @return the product
			 * @throws core::FactoryException - exception when construct function fails (for any reason)
			 */
			virtual
			PRODUCT
			construct(const KEY &key) const=0;


			/**
			 * @brief Getter for constructible capabilities
			 * @return available products (btw. keys)
			 */
			virtual
			std::unordered_set<KEY>
			capabilities() const noexcept =0;
	};

}
