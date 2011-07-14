#ifndef _ROOTFINDING_HPP_
#define _ROOTFINDING_HPP_

#include <boost/function.hpp>
#include <stdexcept>
#include <cmath>

// Taken from http://www.codeproject.com/KB/recipes/root_finding_algorithms.aspx
// Translated from C# to C++. Only slight changes were necessary.

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
		RootFinder(function_type f) : m_BracketingFactor(1.6), m_NbIterMax(m_NbIterDefaultMax), m_Accuracy(d_Accuracy), m_f(f) {}
		RootFinder(function_type f, int niter, double acc) : m_BracketingFactor(1.6), m_NbIterMax(niter), m_Accuracy(acc), m_f(f) {}

		const double& bracketingFactor() const {
			return m_BracketingFactor;
		}

		void bracketingFactor(const double& value) {
			if(value <= 0.0) {
				throw std::runtime_error("argument out of range");
			}
			m_BracketingFactor = value;
		}

		void iterations(int value) {
			if(value <= 0) {
				throw std::runtime_error("argument out of range");
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
				throw RootFinderException(m_InvalidRange,0,Range(xmin,xmax),0.0);
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
			throw RootFinderException(m_RootNotFound,iiter,Range(fmin,fmax),0.0);
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
      return 0.0;
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
				throw RootFinderException(m_InvalidRange,0,Range(m_xmin,m_xmax),0.0);
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
			throw RootFinderException(m_AccuracyNotReached,iiter,Range(std::min(xmid,x),std::max(xmid,x)),fabs(dx));
		}

	public:
		BisectionRootFinder(function_type f) : RootFinder(f) {}
		BisectionRootFinder(function_type f, int niter, double pres) : RootFinder(f, niter, pres) {}
	};

	class SecantRootFinder : public RootFinder
	{
	protected:
		double find() {
			double x1(m_xmin), x2(m_xmax), fl(m_f(x1)), f(m_f(x2));
			double dx,xl,rts;
			if (fabs(fl) < fabs(f)) {
				rts=x1;
				xl=x2;
				std::swap(fl,f);
			} else {
				xl=x1;
				rts=x2;
			}
			int iiter=0;
			for (; iiter < m_NbIterMax; ++iiter) {
				if (f==fl) {
					throw RootFinderException(m_InadequatedAlgorithm,iiter,Range(x1,x2),fabs(x1-x2));
				}
				dx=(xl-rts)*f/(f-fl);
				xl=rts;
				fl=f;
				rts += dx;
				f=m_f(rts);
				if (fabs(dx) < m_Accuracy || f == 0.0) {
					return rts;
				}
			}
			throw RootFinderException(m_RootNotFound,iiter,Range(xl,x2),m_Accuracy);
		}

	public:
		SecantRootFinder(function_type f) : RootFinder(f) {}
		SecantRootFinder(function_type f,int niter,double accuracy) : RootFinder(f,niter,accuracy) {}
	};

	class RidderRootFinder : public RootFinder {
	protected:
		double find() {
			// Vérifications d'usage
			if (m_xmin >= m_xmax) {
				throw RootFinderException(m_InvalidRange,0,Range(m_xmin,m_xmax),0.0);						// Mauvaise plage de recherche
			}
			double ans(-1.11e30), xh(m_xmax),xl(m_xmin);
			double fh(m_f(m_xmax)),fl(m_f(m_xmin)),fm,fnew,s,xm,xnew;
			int iiter=0;
			if (sign(fl) != sign(fh)) {
				for (; iiter < m_NbIterMax; ++iiter) {
					// Compute the mid point
					xm=0.5*(xl+xh);
					fm=m_f(xm);
					s=sqrt(fm*fm-fl*fh);
					if(s==0.0) {
						return (ans);
					}
					// Updating formula
					xnew=xm+(xm-xl)*((fl>=fh?1.0:-1.0)*fm/s);
					// Maybe the new value is the good one
					if(fabs(xnew-ans) <= m_Accuracy) {
						return (ans);
					}
					// Store this new point
					ans=xnew;
					fnew=m_f(ans);
					if (sign(fm,fnew) != fm) {
						xl=xm;
						fl=fm;
						xh=ans;
						fh=fnew;
					} else if (sign(fl,fnew) != fl) {
						xh=ans;
						fh=fnew;
					} else if(sign(fh,fnew) != fh) {
						xl=ans;
						fl=fnew;
					} else {
						throw RootFinderException(m_RootNotFound, iiter, Range(m_xmin,m_xmax), 0.0);
					}
					if(fabs(xh-xl) <= m_Accuracy) {
						return (ans);
					}
				}
				throw RootFinderException(m_AccuracyNotReached,iiter,Range(m_xmin,m_xmax),fabs(xh-xl));									// nombre d'itérations autorisé dépassé
			} else {
				if(fl==0.0) {
					return (m_xmin);
				}
				if(fh==0.0) {
					return (m_xmax);
				}
			}
			throw RootFinderException(m_AccuracyNotReached,iiter,Range(m_xmin,m_xmax),fabs(xh-xl));									// nombre d'itérations autorisé dépassé
		}
	public:
		RidderRootFinder(function_type f) : RootFinder(f) {}
		RidderRootFinder(function_type f,int niter,double pres) : RootFinder(f,niter,pres) {}
	};

	class NewtonRootFinder : public RootFinder
	{
	protected:
		function_type m_df;

		double find() {
			double dx(0.0),x;
			const double xacc(1.0e-5);
			if (m_xmin >= m_xmax) {
				throw RootFinderException(m_RootNotFound,0,Range(m_xmin, m_xmax), 0.0);
			}
			x=0.5*(m_xmin+m_xmax);
			int iiter=0;
			for (; iiter < m_NbIterMax; ++iiter) {
				dx=m_f(x)/m_df(x);
				x-=dx;
				if (sign(m_xmin-x) != sign(x-m_xmax)) {
					throw RootFinderException(m_InvalidRange,iiter,Range(x,x+dx),fabs(dx));
				}
				if (fabs(dx) < xacc) return x;
			}
			// L'algorithme a dépassé le nombre d'itérations autorisé
			throw RootFinderException(m_InvalidRange,iiter,Range(x,x+dx),fabs(dx));
		}
	public:
		NewtonRootFinder(function_type f, function_type df) : RootFinder(f) {
			m_df=df;
		}

		NewtonRootFinder(function_type f, function_type df,int niter,double pres) : RootFinder(f,niter,pres) {
			m_df=df;
		}
	};

	class FalsePositionRootFinder : public RootFinder {
	protected:
		double find() {
			double x1=m_xmin,x2=m_xmax,fl=m_f(x1),fh=m_f(x2),xl,xh,dx,del,f,rtf;
			if(fl*fh>0.0) throw RootFinderException(m_RootNotBracketed,0,Range(x1,x2),0.0);
			if(fl<0.0) {
				xl=x1;
				xh=x2;
			} else {
				xl=x2;
				xh=x1;
				std::swap(fl, fh);
			}
			dx=xh-xl;
			int iiter=0;
			for(;iiter<m_NbIterMax;iiter++) {
				rtf=xl+dx*fl/(fl-fh);
				f=m_f(rtf);
				if(f < 0.0) {
					del=xl-rtf;
					xl=rtf;
					fl=f;
				} else {
					del=xh-rtf;
					xh=rtf;
					fh=f;
				}
				dx=xh-xl;
				if(fabs(del)<m_Accuracy||f==0.0) return rtf;
			}
			throw RootFinderException(m_RootNotFound,iiter,Range(xl,xh),m_Accuracy);
		}
	public:
		FalsePositionRootFinder(function_type f) : RootFinder(f) {}
		FalsePositionRootFinder(function_type f,int niter,double pres) : RootFinder(f,niter,pres) {}
	};

	class BrentRootFinder : public RootFinder {
	protected:
		double find() {
			double a(m_xmin), b(m_xmax), c(m_xmax), d(0.0), e(0.0);
			double min1, min2, p, q, r, s, tol1;
			double fa(m_f(a)), fb(m_f(b)), fc(fb), xm(std::numeric_limits<double>::signaling_NaN());

			// Vérifications d'usage
			if (m_xmin >= m_xmax || sign(fa) == sign(fb)) {
				throw RootFinderException(m_InvalidRange,0,Range(m_xmin,m_xmax),0.0);
			}
			int iiter=0;
			for (; iiter < m_NbIterMax; ++iiter) {
				if (sign(fb) == sign(fc)) { c=a; fc=fa; e=d=b-a; }
				if (fabs(fc) <  fabs(fb)) { a=b; fa=fb; b=c; fb=fc; c=a; fc=fa; }
				tol1=2.0*std::numeric_limits<double>::epsilon()*fabs(b)+0.5*m_Accuracy;
				xm=0.5*(c-b);
				if (fabs(xm) <= tol1 || fb == 0.0) return (b);
				if (fabs(e)  >= tol1 && (fabs(fa) >= fabs(fa))) {
					s=fb/fa;
					if (a == c) {
						p=2.0*xm*s;
						q=1.0-s;
					} else {
						q=fa/fc;
						r=fb/fc;
						p=s*(2.0*xm*q*(q-r)-(b-a)*(r-1.0));
						q=(q-1.0)*(r-1.0)*(s-1.0);
					}
					if (p > 0.0) q=-q;
					p=fabs(p);
					min1=3.0*xm*q-fabs(tol1*q);
					min2=fabs(e*q);
					if (2.0*p < std::min(min1,min2)) {
						// On applique l'interpolation
						e=d;
						d=p/q;
					} else {
						// L'interpolation a échoué; on applique la méthode de bisection
						d=xm;
						e=d;
					}
				} else {
					// La décroissance est trop lente, on applique la méthode de bisection
					d=xm;
					e=d;
				}
				a=b; fa=fb;
				b+=(fabs(d) > tol1 ? d : tol1*sign(xm));
				fb=m_f(b);
			}
			// L'algorithme a dépassé le nombre d'itérations autorisé
			throw RootFinderException(m_AccuracyNotReached,iiter,Range(a,b),fabs(xm));
		}
	public:
		BrentRootFinder(function_type f) : RootFinder(f) {}
		BrentRootFinder(function_type f,int niter,double pres) : RootFinder(f,niter,pres) {}
	};

	const double RootFinder::d_Accuracy = 9.99200722162641E-16;
	const char* RootFinder::m_InvalidRange="Invalid range while finding root";
	const char* RootFinder::m_AccuracyNotReached="The accuracy couldn't be reached with the specified number of iterations";
	const char* RootFinder::m_RootNotFound="The algorithm ended without root in the range";
	const char* RootFinder::m_RootNotBracketed="The algorithm could not start because the root seemed not to be bracketed";
	const char* RootFinder::m_InadequatedAlgorithm="This algorithm is not able to solve this equation";
}

#endif /* _ROOTFINDING_HPP_ */
