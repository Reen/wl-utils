#ifndef _ROOTFINDING_HPP_
#define _ROOTFINDING_HPP_

#include <boost/function.hpp>
#include <stdexcept>
#include <cmath>

namespace RootFinding
{
	struct Range {
		double Min,Max;
		
		Range(double min, double max) : Min(min), Max(max) {}
	};
	
	class RootFinderException : public std::runtime_error
	{
	private:
		int m_Iteration;
		Range m_Range;
		double m_Accuracy;
		
		
	public:
		RootFinderException(const char* message, int iteration, Range range, double accuracy)
		 : std::runtime_error(message), m_Iteration(iteration), m_Range(range), m_Accuracy(accuracy)
		{}
		
		int iteration() {
			return m_Iteration;
		}
		
		Range range() {
			return m_Range;
		}
		
		double accuracy() {
			return m_Accuracy;
		}
		
	};
	
	class RootFinder
	{
	public:
		typedef boost::function<double (double)> function_type;
		
	private:
		static const int m_NbIterDefaultMax = 30;
		static const double m_DefaultAccuracy = 1.0e-4;
		double m_BracketingFactor;
		
	protected:
		static const char* m_InvalidRange;
		static const char* m_AccuracyNotReached;
		static const char* m_RootNotFound;
		static const char* m_RootNotBracketed;
		static const char* m_InadequatedAlgorithm;
		static const double d_Accuracy;
		int m_NbIterMax;
		double m_xmin;
		double m_xmax;
		double m_Accuracy;
		function_type m_f;
		function_type m_Of;
		
		double sign(double a, double b) {
			return (b>= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));
		}
		
		double sign(double x) {
			return (x > 0 ? 1.0 : -1.0);
		}
		
	public:
		RootFinder(function_type f) : m_BracketingFactor(1.6), m_f(f), m_NbIterMax(m_NbIterDefaultMax), m_Accuracy(d_Accuracy) {}
		RootFinder(function_type f, int niter, double acc) : m_BracketingFactor(1.6), m_f(f), m_NbIterMax(niter), m_Accuracy(acc) {}
		
		const double& bracketingFactor() const {
			return m_BracketingFactor;
		}
		
		void bracketingFactor(const double& value) {
			if(value <= 0.0) {
				throw new std::runtime_error("argument out of range");
			}
			m_BracketingFactor = value;
		}
		
		void iterations(int value) {
			if(value <= 0) {
				throw new std::runtime_error("argument out of range");
			}
			m_NbIterMax = value;
		}
		
		const double& accuracy() const{
			return m_Accuracy;
		}
		
		void accuracy(double value) {
			m_Accuracy = value;
		}
		
		bool searchBracketsOutward(double& xmin, double& xmax, double factor) {
			// Check the range
			if(xmin >= xmax) {
				throw new RootFinderException(m_InvalidRange,0,Range(xmin,xmax),0.0);
			}
			double fmin, fmax;
			fmin = m_f(xmin);
			fmax = m_f(xmax);
			int iiter=0;
			do {
				if(sign(fmin) != sign(fmax)) {
					return (true);
				}
				if(fabs(fmin) < fabs(fmax)) {
					fmin = m_f(xmin+=factor*(xmin-xmax));
				}
				else {
					fmax = m_f(xmax+=factor*(xmax-xmin));
				} 
			} while(iiter++ < m_NbIterMax);
			throw new RootFinderException(m_RootNotFound,iiter,Range(fmin,fmax),0.0);
		}
		
		virtual double solve(double x1, double x2, bool bracket) {
			if(bracket) {
				searchBracketsOutward(x1,x2,m_BracketingFactor);
			}
			m_xmin = x1;
			m_xmax = x2;
			return find();
		}
		
		virtual double solve(double x1,double x2,double y,bool bracket) {
			// @todo
			//m_Of=m_f;
			//m_f=UnaryFunctions.Substract(m_Of,UnaryFunctions.Constant(y));
			//double x=Solve(x1,x2,bracket);
			//m_f=m_Of; m_Of=null;
			//return x;
		}
		
		virtual double find() = 0;
		
		
	};
	
	class BisectionRootFinder : public RootFinder
	{
	protected:
		double find() {
			double dx, xmid, x;
			double f(m_f(m_xmin));
			double fmid(m_f(m_xmax));
			if(m_xmin >= m_xmax || sign(f) == sign(fmid))
			{
				throw new RootFinderException(m_InvalidRange,0,Range(m_xmin,m_xmax),0.0);
			}
			if(f < 0.0) {
				dx=m_xmax-m_xmin;
				x=m_xmin;
			} else {
				dx=m_xmin-m_xmax;
				x=m_xmax;
			};
			int iiter=0;
			do {
				fmid=m_f(xmid=x+(dx*=0.5));
				if(fmid<=0.0) x=xmid;
				if(fabs(dx) < m_Accuracy || fmid == 0.0) {
					return (x);
				}
			} while(iiter++ < m_NbIterMax);

			// L'algorithme a dépassé le nombre d'itérations autorisé
			throw new RootFinderException(m_AccuracyNotReached,iiter,Range(std::min(xmid,x),std::max(xmid,x)),fabs(dx));
		}
		
	public:
		BisectionRootFinder(function_type f) : RootFinder(f) {}
		BisectionRootFinder(function_type f, int niter, double pres) : RootFinder(f, niter, pres) {}
		
	};
	
	const double RootFinder::d_Accuracy = 9.99200722162641E-16;
	const char* RootFinder::m_InvalidRange="Invalid range while finding root";
	const char* RootFinder::m_AccuracyNotReached="The accuracy couldn't be reached with the specified number of iterations";
	const char* RootFinder::m_RootNotFound="The algorithm ended without root in the range";
	const char* RootFinder::m_RootNotBracketed="The algorithm could not start because the root seemed not to be bracketed";
	const char* RootFinder::m_InadequatedAlgorithm="This algorithm is not able to solve this equation";
}

#endif /* _ROOTFINDING_HPP_ */
