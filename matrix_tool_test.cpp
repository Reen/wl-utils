#define BOOST_TEST_MODULE QMatrix
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>

#include "q_matrix.h"

namespace io = boost::iostreams;

BOOST_AUTO_TEST_CASE( serialization_test )
{
  std::size_t outer_size(100);
  std::size_t inner_size(100);
  QMatrix<double> qD1(outer_size,outer_size,inner_size,inner_size);
  std::string filename("matrix_tool_test.dat.gz");
  {
    std::size_t outer_last_index = outer_size-1;
    std::size_t inner_last_index = inner_size-1;
    boost::mt19937 rng;
    boost::uniform_int<> dir(-1,1);
    boost::uniform_int<> outer(0,outer_last_index);
    boost::uniform_int<> inner(0,inner_last_index);
    boost::uniform_real<> value(0.0, 1.0);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die_dir(rng, dir);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die_outer(rng, outer);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die_inner(rng, inner);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<> > die_val(rng, value);

    // set some data
    for (unsigned int i = 0; i < 1000000; ++i) {
      std::size_t a = die_outer();
      std::size_t b = (a > 1 && a < outer_last_index ? a + die_dir() : a);
      std::size_t c = die_inner();
      std::size_t d = die_inner();
      qD1(a,b)(c,d) = die_val();
    }
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

  {
    // clean up afterwards
    system("rm matrix_tool_test.dat.gz");
  }
}

BOOST_AUTO_TEST_CASE( power_iteration_test )
{
  BOOST_CHECK( true );
}
