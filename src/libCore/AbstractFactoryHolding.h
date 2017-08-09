#pragma once

#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <libCore/AbstractFactory.h>
#include <libCore/AbstractException.h>


namespace core
{

	typedef core::AbstractException FactoryHoldingException;


	/**
	 * @brief Combines multiple factories which share key and product types into a 'holding'
	 * @tparam KEY factory key
	 * @tparam PRODUCT factory product
	 * @todo Add thread-safety.
	 */
	template<typename KEY, typename PRODUCT>
	class AbstractFactoryHolding
	{
		public:
			/**
			 * @brief Constructor
			 */
			AbstractFactoryHolding() = default;


			/**
			 * @brief Destructor
			 */
			~AbstractFactoryHolding() = default;


			/**
			 * @brief Register a factory at the holding
			 * @param pFactory - factory to register
			 */
			void
			registerFactory(typename std::shared_ptr<core::AbstractFactory<KEY, PRODUCT>> pFactory)
			{
				//factory must be valid
				if (!pFactory)
				{
					throw core::FactoryHoldingException("Null factory registration attempt.");
					return;
				}
				//factory must not yet be registered
				if (mFactorySet.find(pFactory) != mFactorySet.end())
				{
					throw core::FactoryHoldingException("Double registration attempt.");
					return;
				}
				//add factory
				mFactorySet.insert(pFactory);
				//add keys to Production map
				for (auto key:pFactory->capabilities())
				{
					if (mProductionMap.find(key) != mProductionMap.end())
					{
						mProductionMap.insert(std::make_pair(key, pFactory));
					}
				}
			}


			/**
			 * @brief Construct product by key
			 * @param [in] key - identifies the product
			 * @return the product
			 * @throws core::FactoryException - exception when construct function fails (for any reason)
			 */
			virtual
			PRODUCT
			construct(const KEY &key) const
			{
				auto iter = mProductionMap.find(key);
				if (iter != mProductionMap.end())
				{
					return iter->second->construct(key);
				}
				else
				{
					throw core::FactoryHoldingException("Unsupported key.");
				}
				return PRODUCT();
			}


			/**
			 * @brief Getter for constructible capabilities
			 * @return available products (btw. keys)
			 */
			virtual
			std::unordered_set<KEY>
			capabilities() const noexcept
			{
				std::unordered_set<KEY> res;
				for (auto factory:mFactorySet)
				{
					res |= factory->capabilities();
				}
				return res;
			}


		private:
			typename std::unordered_set<std::shared_ptr<core::AbstractFactory<KEY, PRODUCT>>> mFactorySet;        ///< registered factories
			typename std::unordered_map<KEY, std::shared_ptr<core::AbstractFactory<KEY, PRODUCT>>> mProductionMap; ///< maps keys to factories
	};

}