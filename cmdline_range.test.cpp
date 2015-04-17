/* Unit test for the class cmdline::range_parser.
 */
#include "cmdline/args.h"
#include <catch.hpp>
#include <sstream>

TEST_CASE( "range_parser with integers at beginning", "[range_parser]" ) {
    const char * argv[] = {
        "program",
        "42",
    };
    cmdline::args args( 2, argv );
    std::stringstream log;
    args.log(log);
    int i;

    SECTION( "Inside [min, \\infty)" ) {
        args.range(40) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "" );
    }
    SECTION( "Outside [min, \\infty)" ) {
        args.range(50) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "Error: number must be greater than 50.\n" );
    }
    SECTION( "Inside [min, max]" ) {
        args.range(40, 50) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "" );
    }
    SECTION( "Below [min, max]" ) {
        args.range(50, 60) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "Error: number must be greater than 50.\n" );
    }
    SECTION( "Above [min, max]" ) {
        args.range(30, 40) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "Error: number must be smaller than 40.\n" );
    }
}

TEST_CASE( "range_parser with integers at middle", "[range_parser]" ) {
    const char * argv[] = {
        "program",
        "--value",
        "42",
    };
    cmdline::args args( 3, argv );
    std::stringstream log;
    args.log(log);
    args.next();
    int i;

    SECTION( "Inside [min, \\infty)" ) {
        args.range(40) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "" );
    }
    SECTION( "Outside [min, \\infty)" ) {
        args.range(50) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "Error: argument to --value must be greater than 50.\n" );
    }
    SECTION( "Inside [min, max]" ) {
        args.range(40, 50) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "" );
    }
    SECTION( "Below [min, max]" ) {
        args.range(50, 60) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "Error: argument to --value must be greater than 50.\n" );
    }
    SECTION( "Above [min, max]" ) {
        args.range(30, 40) >> i;
        CHECK( i == 42 );
        CHECK( log.str() == "Error: argument to --value must be smaller than 40.\n" );
    }
}

TEST_CASE( "range_parser with double at beginning", "[range_parser]" ) {
    const char * argv[] = {
        "program",
        "42.0",
    };
    cmdline::args args( 2, argv );
    std::stringstream log;
    args.log(log);
    double d;

    SECTION( "Inside [min, \\infty)" ) {
        args.range(40) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "" );
    }
    SECTION( "Outside [min, \\infty)" ) {
        args.range(50) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "Error: number must be greater than 50.\n" );
    }
    SECTION( "Inside [min, max]" ) {
        args.range(40, 50) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "" );
    }
    SECTION( "Below [min, max]" ) {
        args.range(50, 60) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "Error: number must be greater than 50.\n" );
    }
    SECTION( "Above [min, max]" ) {
        args.range(30, 40) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "Error: number must be smaller than 40.\n" );
    }
}

TEST_CASE( "range_parser with double at middle", "[range_parser]" ) {
    const char * argv[] = {
        "program",
        "--value",
        "42",
    };
    cmdline::args args( 3, argv );
    std::stringstream log;
    args.log(log);
    args.next();
    double d;

    SECTION( "Inside [min, \\infty)" ) {
        args.range(40) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "" );
    }
    SECTION( "Outside [min, \\infty)" ) {
        args.range(50) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "Error: argument to --value must be greater than 50.\n" );
    }
    SECTION( "Inside [min, max]" ) {
        args.range(40, 50) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "" );
    }
    SECTION( "Below [min, max]" ) {
        args.range(50, 60) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "Error: argument to --value must be greater than 50.\n" );
    }
    SECTION( "Above [min, max]" ) {
        args.range(30, 40) >> d;
        CHECK( d == 42 );
        CHECK( log.str() == "Error: argument to --value must be smaller than 40.\n" );
    }
}
