#pragma once
#include <libCore/dds/SerializationMode.h>
#include <libCore/dds/Operation.h>


namespace core
{
  namespace dds
  {

    /**
     * @brief Base class for all kinds of distributed topics
     */
    class AbstractTopic
    {
      public:
        AbstractTopic()=default;


        virtual
        ~AbstractTopic()=default;


        virtual
        core::dds::Operation
        operation() const noexcept =0;


        virtual
        core::dds::SerializationMode
        canSerialize() const noexcept =0;


        virtual
        bool
        hasKey() const noexcept =0;


        virtual
        std::uint64_t
        key() const noexcept =0;

    };

  }
}
