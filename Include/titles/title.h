#pragma once

#include <iostream>

/* Defines the Title structure
    id: the title ID
    name: the title Name

    This overloads operators too, so that sorting and comparison can be done.
*/
struct Title {
    u64 id;
    std::string name;
    u32 Version;
    NcmContentMetaKey Record;

    bool operator ==(const Title&x) const {
        return id == x.id;
    }

    bool operator <(const Title&x) const {
        return id < x.id;
    }
};

