// Boost.Geometry (aka GGL, Generic Geometry Library)
// Unit Test

// This file was modified by Oracle on 2015, 2016.
// Modifications copyright (c) 2015-2016, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/geometry.hpp>
#include <geometry_test_common.hpp>

namespace bg = boost::geometry;

//Testing geographic strategies
template <typename CT>
void test_geo_strategies()
{
    std::string poly = "POLYGON((52 0, 41 -74, -23 -43, -26 28, 52 0))";

    typedef bg::model::point<CT, 2,
            bg::cs::geographic<bg::degree> > pt_geo;

    typedef typename bg::point_type<pt_geo>::type pt_geo_type;

    typedef typename bg::formula::andoyer_inverse
            <
                CT,
                false,
                true,
                true
            > strategy_andoyer;

    typedef typename bg::formula::thomas_inverse
            <
                CT,
                false,
                true,
                true
            > strategy_thomas;

    typedef typename bg::formula::vincenty_inverse
            <
                CT,
                false,
                true,
                true
            > strategy_vincenty;


    bg::srs::spheroid<CT> spheroid;

    bg::strategy::area::area_geographic
            <pt_geo_type> geographic_default;

    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_andoyer,
                1,
                true
            > geographic_andoyer1;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_andoyer,
                2,
                true
            > geographic_andoyer2;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_andoyer,
                3,
                true
            > geographic_andoyer3;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_andoyer,
                4,
                true
            > geographic_andoyer4;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_andoyer,
                5,
                true
            > geographic_andoyer5;

    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_thomas,
                1,
                true
            > geographic_thomas1;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_thomas,
                2,
                true
            > geographic_thomas2;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_thomas,
                3,
                true
            > geographic_thomas3;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_thomas,
                4,
                true
            > geographic_thomas4;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_thomas,
                5,
                true
            > geographic_thomas5;

    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_vincenty,
                1,
                true
            > geographic_vincenty1;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_vincenty,
                2,
                true
            > geographic_vincenty2;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_vincenty,
                3,
                true
            > geographic_vincenty3;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_vincenty,
                4,
                true
            > geographic_vincenty4;
    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_vincenty,
                5,
                true
            > geographic_vincenty5;

    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_vincenty,
                5
            > geographic_vincenty5_default;

    bg::strategy::area::area_geographic
            <
                pt_geo_type,
                strategy_vincenty
            > geographic_vincenty_default;

    bg::model::polygon<pt_geo> geometry_geo;

    //GeographicLib         63316536351834.289
    //PostGIS (v2.2.2)      6.33946+13
    //MS SQL SERVER         632930207487035

    bg::read_wkt(poly, geometry_geo);
    CT area;
    CT err = 0.0000001;

    CT area_default = bg::area(geometry_geo);
    BOOST_CHECK_CLOSE(area_default, 63292982057581.711, err);
    area = bg::area(geometry_geo, geographic_default);
    BOOST_CHECK_CLOSE(area, 63292982057581.711, err);

    CT area_less_accurate = bg::area(geometry_geo, geographic_andoyer1);
    BOOST_CHECK_CLOSE(area_less_accurate, 63292982421447.312, err);
    area = bg::area(geometry_geo, geographic_andoyer2);
    BOOST_CHECK_CLOSE(area, 63292982299473.633, err);
    area = bg::area(geometry_geo, geographic_andoyer3);
    BOOST_CHECK_CLOSE(area, 63292982299578.328, err);
    area = bg::area(geometry_geo, geographic_andoyer4);
    BOOST_CHECK_CLOSE(area, 63292982299578.227, err);
    area = bg::area(geometry_geo, geographic_andoyer5);
    BOOST_CHECK_CLOSE(area, 63292982299578.227, err);

    area = bg::area(geometry_geo, geographic_thomas1);
    BOOST_CHECK_CLOSE(area, 63292982179555.766, err);
    area = bg::area(geometry_geo, geographic_thomas2);
    BOOST_CHECK_CLOSE(area, 63292982057581.711, err);
    area = bg::area(geometry_geo, geographic_thomas3);
    BOOST_CHECK_CLOSE(area, 63292982057686.406, err);
    area = bg::area(geometry_geo, geographic_thomas4);
    BOOST_CHECK_CLOSE(area, 63292982057686.305, err);
    area = bg::area(geometry_geo, geographic_thomas5);
    BOOST_CHECK_CLOSE(area, 63292982057686.305, err);

    area = bg::area(geometry_geo, geographic_vincenty1);
    BOOST_CHECK_CLOSE(area, 63292982178432.859, err);
    area = bg::area(geometry_geo, geographic_vincenty2);
    BOOST_CHECK_CLOSE(area, 63292982056458.805, err);
    area = bg::area(geometry_geo, geographic_vincenty3);
    BOOST_CHECK_CLOSE(area, 63292982056563.5, err);
    area = bg::area(geometry_geo, geographic_vincenty4);
    BOOST_CHECK_CLOSE(area, 63292982056563.398, err);
    CT area_most_accurate = bg::area(geometry_geo, geographic_vincenty5);
    BOOST_CHECK_CLOSE(area, 63292982056563.398, err);

    area = bg::area(geometry_geo, geographic_vincenty5_default);
    BOOST_CHECK_CLOSE(area, 63292982056563.398, err);
    area = bg::area(geometry_geo, geographic_vincenty_default);
    BOOST_CHECK_CLOSE(area, 63292982056458.805, err);

    BOOST_CHECK_CLOSE(area_most_accurate, area_less_accurate, .000001);
    BOOST_CHECK_CLOSE(area_most_accurate, area_default, .00000001);

    /* timings and accuracy
    std::cout.precision(32);
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_andoyer1);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_andoyer2);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_andoyer3);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_andoyer4);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_andoyer5);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_thomas1);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_thomas2);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_thomas3);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_thomas4);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_thomas5);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_vincenty1);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_vincenty2);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_vincenty3);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_vincenty4);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    {   clock_t startTime = clock();
        for (int j=0; j < 100000; j++) area = bg::area(geometry_geo, geographic_vincenty5);
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        std::cout << "area=" << area << std::endl;}
    */
}

int test_main(int, char* [])
{

    test_geo_strategies<double>();

    return 0;
}
