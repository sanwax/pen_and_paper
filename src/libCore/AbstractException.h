#pragma once


#include <string>
#include <exception>


namespace core
{

	/**
	 * @brief Exception class for exceptions raised by the factory
	 */
	class AbstractException : public std::exception
	{
		public:
			/**
			 * @brief Constructor
			 * @param [in] sWhat - human readable reason
			 */
			AbstractException(const std::string &sWhat) :
					msWhat(std::string("[Factory Exception] ") + sWhat)
			{
			}


			/**
			 * @brief Getter for reason
			 * @return reason
			 */
			const char *
			what() const noexcept
			{
				return msWhat.c_str();
			}

		private:
			const std::string msWhat;  ///< human readable error text
	};

}
