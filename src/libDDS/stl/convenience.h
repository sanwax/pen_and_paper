#pragma once


#include <unordered_map>


namespace dds
{
    /**
     * @brief Some convenience additions for annoying shortcomings of the stl
     */
    namespace stl
    {

        /**
         * @brief Finds a specific pair in a std::unordered_multimap.
         * @tparam K key of multimap
         * @tparam V value of multimap
         * @param [in] map to search
         * @param [in] k stands for the key to search
         * @param [in] v stands for the value to search
         */
        template <typename K,typename V>
        static
        typename std::unordered_multimap<K,V>::const_iterator
        findPair(const std::unordered_multimap<K,V>& map,const K& k,const V& v)
        {
            auto range=map.equal_range(k);
            while (range.first!=range.second && range.first!=map.end())
            {
                if (range.first->second==v)
                {
                    return range.first;
                }
                ++range.first;
            }
            return map.end();
        }


    }

}
