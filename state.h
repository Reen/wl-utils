#ifndef _STATE_H_
#define _STATE_H_

#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/utility/singleton.hpp>

class State : public boost::singleton<State> {
private:
	std::size_t min_particles_;
	std::size_t max_particles_;
	std::size_t n_particles_;
	double min_energy_;
	double max_energy_;
	double energy_bin_width_;
	std::size_t n_energy_;
  int threads_;
	
	void set_n_particles() {
		n_particles_ = max_particles_ - min_particles_ + 1;
	}
	
	void set_energy_bin_width() {
		energy_bin_width_ = (max_energy_-min_energy_)/n_energy_;
	}
public:
	State(boost::restricted) : n_energy_(1) {}
	
	const std::size_t & min_particles() const { return min_particles_; }
	const std::size_t & max_particles() const { return max_particles_; }
	const std::size_t & n_particles() const { return n_particles_; }
	const double & min_energy() const { return min_energy_; }
	const double & max_energy() const { return max_energy_; }
	const std::size_t & n_energy() const { return n_energy_; }
	const double & energy_bin_width() const { return energy_bin_width_; }
  const int & threads() const { return threads_; }
	
	void set_min_particles(const std::size_t & min_particles) { min_particles_ = min_particles; set_n_particles(); }
	void set_max_particles(const std::size_t & max_particles) { max_particles_ = max_particles; set_n_particles(); }
	void set_min_energy(const double & min_energy) { min_energy_ = min_energy; set_energy_bin_width(); }
	void set_max_energy(const double & max_energy) { max_energy_ = max_energy; set_energy_bin_width(); }
	void set_n_energy(const std::size_t & n_energy) { n_energy_ = n_energy; set_energy_bin_width(); }
  void set_threads(const int& threads) { threads_ = threads; }
	
private:
  friend class boost::serialization::access;
  
  template<class Archive>
  void save(Archive &ar, const unsigned int /* version */) const {
    ar << min_particles_;
  	ar << max_particles_;
  	ar << n_particles_;
  	ar << min_energy_;
  	ar << max_energy_;
  	ar << energy_bin_width_;
  	ar << n_energy_;
  }
  
  template<class Archive>
  void load(Archive &ar, const unsigned int /* version */) {
    ar >> min_particles_;
  	ar >> max_particles_;
  	ar >> n_particles_;
  	ar >> min_energy_;
  	ar >> max_energy_;
  	ar >> energy_bin_width_;
  	ar >> n_energy_;
  }

public:
  BOOST_SERIALIZATION_SPLIT_MEMBER()

  template<class Archive>
  void save_to(Archive &ar) {
    ar & (*this);
  }

  template<class Archive>
  void load_from(Archive &ar) {
    ar & (*this);
  }
};

#endif /* _STATE_H_ */
