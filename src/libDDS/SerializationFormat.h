#pragma once

namespace dds
{

    /**
     * @brief Different ways of data serialization
     */
    enum class SerializationFormat
    {
        NONE=0,    ///< no serialization possible
        BINARY=1,  ///< serialize as binary
        JSON=2     ///< serialize as json formatted text
    };


}

