// Boost.Geometry (aka GGL, Generic Geometry Library)
// QuickBook Example

// Copyright (c) 2014-2024 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//[buffer_join_round
//` Shows how the join_round strategy can be used as a JoinStrategy to create rounded corners

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/geometries.hpp>
/*<-*/ #include "../examples_utils/create_svg_buffer.hpp" /*->*/

int main()
{
    using point = boost::geometry::model::d2::point_xy<double>;
    using polygon = boost::geometry::model::polygon<point>;

    // Declare the join_round strategy with 72 points for a full circle
    boost::geometry::strategy::buffer::join_round join_strategy(72);

    // Declare other strategies
    boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(1.0);
    boost::geometry::strategy::buffer::end_flat end_strategy;
    boost::geometry::strategy::buffer::side_straight side_strategy;
    boost::geometry::strategy::buffer::point_circle point_strategy;

    // Declare/fill a multi polygon
    boost::geometry::model::multi_polygon<polygon> mp;
    boost::geometry::read_wkt("MULTIPOLYGON(((5 5,7 8,9 5,5 5)),((8 7,8 10,11 10,11 7,8 7)))", mp);

    // Create the buffered geometry with rounded corners
    boost::geometry::model::multi_polygon<polygon> result;
    boost::geometry::buffer(mp, result,
                distance_strategy, side_strategy,
                join_strategy, end_strategy, point_strategy);
    /*<-*/ create_svg_buffer("buffer_join_round.svg", mp, result); /*->*/

    return 0;
}

//]

