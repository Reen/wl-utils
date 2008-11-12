#define BOOST_TEST_MODULE QMatrix
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include "q_matrix.h"

namespace io = boost::iostreams;

BOOST_AUTO_TEST_CASE( serialization_test )
{
  QMatrix<double> qD1(100,100,100,100);
  std::string filename("matrix_tool_test.dat.gz");
  {
    // set some data
    qD1(42,43)(31,26) = 3.41;
    qD1(4,4)(31,26)   = 13.41;
    qD1(2,3)(31,26)   = 5.41;
    qD1(72,71)(91,26) = 3.51;
    qD1(99,99)(31,96)= 3.91;
  }
  {
    // writing test
    io::filtering_ostream out;
    out.push(io::gzip_compressor());
    out.push(io::file_sink(filename));
    boost::archive::text_oarchive oa(out);
    oa & qD1;
  }
  
  QMatrix<double> qD2;
  {
    // reading test
    io::filtering_istream in;
    in.push(io::gzip_decompressor());
    in.push(io::file_source(filename));
    boost::archive::text_iarchive ia(in);
    
    ia & qD2;
  }
  BOOST_CHECK( qD1 == qD2 );
  BOOST_CHECK_EQUAL( qD2(99,99)(31,96) , 3.91 );

  {
    system("rm matrix_tool_test.dat.gz");
  }
}

BOOST_AUTO_TEST_CASE( power_iteration_test )
{
  BOOST_CHECK( true );
}
