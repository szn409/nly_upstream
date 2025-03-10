// Boost.Geometry (aka GGL, Generic Geometry Library)
// QuickBook Example

// Copyright (c) 2011-2024 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//[coordinate_system
//` Examine the coordinate system of a point

#include <iostream>
#include <typeinfo>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

int main()
{
    using point_type = boost::geometry::model::d2::point_xy<double>;
    using polygon_type = boost::geometry::model::polygon<point_type>;

    using system = boost::geometry::coordinate_system<polygon_type>::type;

    std::cout << "system: " << typeid(system).name() << std::endl;

    return 0;
}

//]


//[coordinate_system_output
/*`
Output (using MSVC):
[pre
system: struct boost::geometry::cs::cartesian
]
*/
//]
