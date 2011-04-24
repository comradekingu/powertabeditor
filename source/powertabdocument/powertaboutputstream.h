/////////////////////////////////////////////////////////////////////////////
// Name:            powertaboutputstream.h
// Purpose:         Output stream used to serialize MFC based Power Tab data
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 20, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __POWERTABOUTPUTSTREAM_H__
#define __POWERTABOUTPUTSTREAM_H__

#include <cstdint>
#include <ostream>

#include <unordered_map>

#include <string>
#include <vector>

#include "powertabstream.h"
#include "macros.h"

class Rect;
class Colour;
class PowerTabObject;

/// Output stream used to serialize MFC based Power Tab data
class PowerTabOutputStream    
{
    // Member Variables
protected:
    bool                                        m_mapsInitialized;              ///< Determines whether or not the maps have been initialized
    std::unordered_map<std::string, uint32_t>   m_classInfoHashMap;             ///< Map of class Ids to object index
    std::unordered_map<PowerTabObject*, uint32_t>        m_objectHashMap;      ///< Map of object pointers to object index
    uint32_t                                    m_mapCount;                     ///< Internal count of mapped objects
    PowerTabStreamError                         m_lastPowerTabError;            ///< Last Power Tab specific error
    std::ostream& m_stream;

    // Constructor/Destructor
public:
    PowerTabOutputStream(std::ostream& stream);

    // Write Functions
    bool WriteCount(uint32_t count);
    bool WriteMFCString(const std::string& string);
    bool WriteWin32ColorRef(const Colour& colour);
    bool WriteMFCRect(const Rect& rect);
    bool WriteObject(PowerTabObject* object);

protected:
    bool WriteClassInformation(const PowerTabObject* object);
    bool WriteMFCStringLength(uint32_t length, bool unicode);

    // Error Checking Functions
public:
    /// Checks the current state of the stream
    /// @return True if the stream is OK, false if an error has occurred
    bool CheckState()
    {return (!fail() && (m_lastPowerTabError == POWERTABSTREAM_NO_ERROR));}
    std::string GetLastErrorMessage();

protected:
    bool CheckCount();

    // Operations
    bool MapObject(const PowerTabObject* object);

public:
    /// Gets the current stream position, in bytes
    /// @return The current stream position, in bytes
    long TellO()
    {
        return (long)m_stream.tellp();
    }

    bool fail()
    {
        return m_stream.fail();
    }

    template <class T>
    bool WriteVector(const std::vector<T>& vect)
    {
        const size_t count = vect.size();
        WriteCount(count);

        CHECK_THAT(CheckState(), false);
        for (uint32_t i = 0; i < count; i++)
        {
            assert(vect[i]);

            // the '&*' is used to get a raw PowerTabObject pointer,
            // regardless of whether T is a raw pointer, shared_ptr, etc
            WriteObject(&*vect[i]);
            CHECK_THAT(CheckState(), false);
        }
        return true;
    }

    template<class T>
    PowerTabOutputStream& operator<<(const T& data)
    {
        m_stream.write((char *)&data, sizeof(data));
        return *this;
    }

    /// Serializes a small vector (size < 255) by writing the size as one byte,
    /// followed by each element of the vector.
    /// This function takes advantage of std::vector's contiguous storage to avoid manually
    /// looping through each element
    template <class T>
    void WriteSmallVector(const std::vector<T> &vect)
    {
        const uint8_t count = vect.size();
        *this << count;

        m_stream.write((char*)&vect[0], count * sizeof(T));
    }

};

#endif
