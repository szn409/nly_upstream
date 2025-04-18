// Boost.Geometry (aka GGL, Generic Geometry Library)
// QuickBook Example

// Copyright (c) 2011-2024 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2023 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//[interior_type
//`Shows how to use the interior_type metafunction

#include <deque>
#include <list>
#include <iostream>
#include <typeinfo>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/adapted/boost_array.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_ARRAY_CS(cs::cartesian)

int main()
{
    // Define a polygon storing points in a deque and storing interior rings
    // in a list (note that std::list is not supported by most algorithms
    // because not supporting a random access iterator)
    using polygon = boost::geometry::model::polygon
        <
            boost::array<short, 3>,
            true, true,
            std::deque, std::list
        >;

    std::cout << typeid(boost::geometry::interior_type<polygon>::type).name() << std::endl;

    return 0;
}

//]

//[interior_type_output
/*`
Output (using MSVC) is a long story (part manually replaced with ellipsis):
[pre
class std::list<class boost::geometry::model::ring<class boost::array<short,3>,1,1,class std::deque,class std::allocator>,class std::allocator<...>>>
]
*/
//]
