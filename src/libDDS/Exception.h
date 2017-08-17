#pragma once


#include <string>
#include <exception>


namespace dds
{

    /**
     * @brief Exception base class for any DDS exception
     */
    class Exception : public std::exception
    {
        public:
            /**
             * @brief Constructor
             * @param [in] sWhat - human readable reason
             */
            Exception(const std::string &sWhat) :
                            msWhat(std::string("[Factory Exception] ") + sWhat)
            {
            }


            /**
             * @brief Destructor
             */
            virtual
            ~Exception()=default;

            
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
