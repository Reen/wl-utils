#ifndef MISC_1ZUMG4QW

#define MISC_1ZUMG4QW
#include <string>
#include <boost/iostreams/filtering_stream.hpp>


enum CompressionType { CT_NONE, CT_GZIP, CT_BZIP2 };
CompressionType getFileCompression(std::string filepath);

void openMatrixFileRead(boost::iostreams::filtering_istream &in, std::string filepath, CompressionType ct);
void openMatrixFileWrite(boost::iostreams::filtering_ostream &out, std::string filepath, CompressionType ct);
std::string generateOutputFilename(std::string infile);

#endif /* end of include guard: MISC_1ZUMG4QW */
