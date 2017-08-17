#pragma once

#include <libDDS/Exception.h>
#include <sstream>

namespace dds
{

	/**
	 * @brief Dedicated exception class for unimplemented functions
	 */
	class ExceptionUnimplemented: public dds::Exception
	{
		public:
			/**
			 * @brief Constructor
			 * @param [in] pFunction function where exception originated
			 * @param [in] pFile file name where exception originated
			 * @param [in] iLine line number where exception originated
			 */
			ExceptionUnimplemented(const char* pFunction, const char* pFile, const unsigned int iLine) :
				dds::Exception(formatExceptionMessage(pFunction,pFile,iLine))
			{
			}

		private:
			/**
			 * @brief Formats the error text
			 * @param [in] pFunction function where exception originated
			 * @param [in] pFile file name where exception originated
			 * @param [in] iLine line number where exception originated
			 */
			static
			std::string
			formatExceptionMessage(const char* pFunction,const char* pFile,const unsigned int iLine)
			{
				std::stringstream s;
				s<< "Hit unimplemented function: " << pFunction << " (" << pFile << ":" << iLine << ")";
				return s.str();
			}
	};
}
