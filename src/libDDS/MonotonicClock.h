#pragma once


#include <cstdint>
#include <atomic>


namespace dds
{
	class MonotonicClock
	{
		public:
			/**
			 * @brief Constructor
			 * @param initialTime initial point in time
			 */
			MonotonicClock(uint64_t initialTime=1):
				mNow{initialTime}
			{
			}


			/**
			 * @brief Getter for current time (without increasing the clock)
			 * @return current time
			 */
			uint64_t
			now() const noexcept
			{
				return mNow.load();
			}


			/**
			 * @brief Getter for current time (including clock increase)
			 * @return current time; clock increased
			 */
			uint64_t
			tick() noexcept
			{
				uint64_t current_time;
				do
				{
					current_time = mNow.load();
				}
				while (!mNow.compare_exchange_strong(current_time,current_time+1));
				return current_time;
			}


			/**
			 * @brief Assignment operator
			 * @param time some point in time
			 * @return self-reference
			 */
			dds::MonotonicClock&
			operator=(const uint64_t time)
			{
				mNow.store(time);
				return *this;
			}


			/**
			 * @brief Operator less
			 * @param rhs a right-hand-side for comparison
			 * @return this < rhs
			 */
			bool
			operator<(const dds::MonotonicClock& rhs) const noexcept
			{
				return mNow.load()<rhs.mNow.load();
			}


		private:
			std::atomic<uint64_t> mNow;  ///< current time
	};

}