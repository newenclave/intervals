
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "intervals/set.h"
#include "intervals/map.h"

namespace {
    using u64 = std::uint64_t;
    using ival_type = intervals::interval<u64>;
    using ival_set  = intervals::set<u64>;
    using ival_map  = intervals::map<u64, std::string>;
}

int main( int argc, char* argv[ ] )
{
    int result = Catch::Session( ).run( argc, argv );
    return ( result < 0xff ? result : 0xff );
}

