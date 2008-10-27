// std includes
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/banded.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

namespace bio = boost::iostreams;

template<class T, class U, class V, class W> void printDoS(boost::numeric::ublas::matrix<T,U,V>& dos, std::size_t i, W extension, double minEnergy, double energyBinWidth, std::size_t minParticles)
{
	using namespace std;
	ostringstream o;
	bio::filtering_ostream og;
	o << "dos_" << std::setw(15) << std::right << std::setfill('0') << i << "." << extension;
	og.push(bio::file_sink(o.str()));
	og << setprecision(10);

	T zero(0);
	for (std::size_t i = 0; i < dos.size1(); ++i)
	{
		std::size_t N = i+minParticles;
		for (std::size_t j = 0; j < dos.size2(); ++j)
		{
			if (dos(i, j)> zero)
			{
				double E = minEnergy+energyBinWidth/2.0+j*energyBinWidth;
				og
				<< setw(20) << right << N
				<< setw(20) << right << E
				<< setprecision(14) << setw(20) << right << log(dos(i, j))
				<< setprecision(14) << setw(20) << right << dos(i,j) << "\n";
			}
		}
	}
}


template<class T> void setupMatrix(T& mat, std::size_t n1, std::size_t n2, std::size_t n3, std::size_t n4)
{
	mat.resize(n1,n1,1,1);
	for (signed i = 0; i < signed (mat.size1 ()); ++ i)
	{
		for (signed j = std::max (i - 1, 0); j < std::min (i + 2, signed (mat.size2 ())); ++ j)
		{
			mat(i, j).resize(n3,n4);
			mat(i, j).clear();
		}
	}
}

int main (int argc, char const *argv[])
{
	using namespace boost::numeric;

	typedef ublas::matrix<std::size_t, ublas::column_major > q_inner_matrix_type;
	typedef ublas::banded_matrix< q_inner_matrix_type , ublas::column_major > q_matrix_type;

	typedef ublas::matrix< double, ublas::column_major > qD_inner_matrix_type;
	typedef ublas::banded_matrix< qD_inner_matrix_type, ublas::column_major > qD_matrix_type;

	typedef ublas::matrix< double, ublas::row_major > dos_matrix_type;


	q_matrix_type q;
	qD_matrix_type qD;
	std::size_t nParticles(111), nEnergy(500), minParticles(0);
	double minEnergy(-700.0), maxEnergy(20), energyBinWidth((maxEnergy-minEnergy)/nEnergy);

	setupMatrix(q, nParticles,nParticles,nEnergy,nEnergy);
	setupMatrix(qD, nParticles,nParticles,nEnergy,nEnergy);
	int N1,N2;
	double E1,E2;
	std::cout << "Reading from stdin." << std::endl;
	while(EOF != scanf("%i %i %lf %lf", &N1,&N2,&E1,&E2)) {
		std::size_t i1 = static_cast<size_t>((E1-minEnergy)/energyBinWidth);
		std::size_t i2 = static_cast<size_t>((E2-minEnergy)/energyBinWidth);
		std::size_t ni1 = N1-minParticles;
		std::size_t ni2 = N2-minParticles;
		q(ni1,ni2)(i1,i2)++;
	}

	std::cout << "Converting matrix to double." << std::endl;
	for (std::size_t ni = 0; ni < qD.size1(); ++ni)
	{
		int s_ni = int(ni);
		// minor column
		for (std::size_t ei = 0; ei < nEnergy; ++ei)
		{
			q_inner_matrix_type::value_type i_sum(0);
			// major row
			for (std::size_t nj = std::max(s_ni-1, 0); nj < std::min(ni+2, qD.size2()); ++nj)
			{
				// minor row
				for (std::size_t ej = 0; ej < nEnergy; ++ej)
				{
					i_sum += q(ni, nj)(ei, ej);
				}
			}
			if (i_sum > 0)
			{
				double d_sum(i_sum);
				// major row
				for (std::size_t nj = std::max(s_ni-1, 0); nj < std::min(ni+2, qD.size2()); ++nj)
				{
					// minor row
					for (std::size_t ej = 0; ej < nEnergy; ++ej)
					{
						// copy and divide by column sum
						qD(ni, nj)(ei, ej) = q(ni, nj)(ei, ej) / d_sum;
					}
				}
			} // else -> all values in the column are zero so we do nothing
		}
	}

	std::cout << "Starting power method iteration." << std::endl;
	dos_matrix_type dos(nParticles,nEnergy);
	dos_matrix_type dos_old(nParticles,nEnergy);
	std::fill(dos_old.data().begin(), dos_old.data().end(), 1.0/dos_old.data().size());

	/* ### 2 ### Power Iteration
	 * Power Iteration to calculate the eigenvector to the largest eigenvalue, which is 1, as the matrix is stochastic.
	 *
	 * We have iterations over columns in the inner loop, thus we have to use ublas::column_major order in the Q matrix.
	 * @todo: eventually parallize this iteration for maximum speed on SMP machines
	 * @todo: compare the precision of float/double/mpfr::Real DoSes
	 */
	double zero(0), one(1), crit(1.0e-7), dist(0);
	std::size_t i(0);
	while (true)
	{
		i++;
		dos.clear();
		// do the matrix-vector-multiplication
		double n(0);
#pragma omp parallel for reduction(+:n)
		for (std::size_t nj = 0; nj < qD.size2(); ++nj)
		{
			int s_nj = int(nj);
			for (std::size_t ej = 0; ej < nEnergy; ++ej)
			{
				for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, qD.size1()); ++ni)
				{
					ublas::matrix_column< qD_inner_matrix_type > m1(qD(ni, nj), ej);
					ublas::matrix_row< dos_matrix_type > m2(dos_old, ni);
					double incr(0);
					incr = std::inner_product(m1.begin(), m1.end(), m2.begin(), incr);
					dos(nj, ej) += incr;
					n += incr;
				}
				//std::cout << std::endl;
			}
		}
		// check wether the iteration has converged
		bool converged = true;
		for (dos_matrix_type::array_type::iterator i1(dos.data().begin()), i2(dos_old.data().begin()); i1 < dos.data().end(); ++i1, ++i2)
		{
			if (*i1 > zero)
			{
				if (fabs((*i2)/(*i1)-one) > crit)
				{
					dist = (*i2)/(*i1);
					converged = false;
					break;
				}
			}
		}
		// norm eigenvector
		dos /= n;

		dos_old = dos;
		if(converged)
		{
			printDoS(dos,i, "parq", minEnergy, energyBinWidth, minParticles);
			break;
		}

		if (i%1000 == 1)
		{
			std::cout << "Writing DOS of iteration " << i << " to disk." << std::endl;
			printDoS(dos,i, "parq", minEnergy, energyBinWidth, minParticles);
		}
	}

	return 0;
}
