#ifndef _STATE_H_
#define _STATE_H_

#include "boost/filesystem.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/utility/singleton.hpp>

#include <boost/iostreams/filtering_stream.hpp>

namespace io = boost::iostreams;

class State : public boost::singleton<State> {
private:
  std::size_t min_particles_;
  std::size_t max_particles_;
  std::size_t n_particles_;
  double min_energy_;
  double max_energy_;
  double energy_bin_width_;
  std::size_t n_energy_;
  double volume_;
  std::string working_directory_;

  void set_n_particles() {
    n_particles_ = max_particles_ - min_particles_ + 1;
  }

  void set_energy_bin_width() {
    energy_bin_width_ = (max_energy_-min_energy_)/n_energy_;
  }
public:
  State(boost::restricted) : n_energy_(1) {}

  const std::size_t& min_particles() const { return min_particles_; }
  const std::size_t& max_particles() const { return max_particles_; }
  const std::size_t& n_particles() const { return n_particles_; }
  const double& min_energy() const { return min_energy_; }
  const double& max_energy() const { return max_energy_; }
  const std::size_t& n_energy() const { return n_energy_; }
  const double& energy_bin_width() const { return energy_bin_width_; }
  const double& volume() const { return volume_; }
  const std::string& working_directory() const { return working_directory_; }

  void set_min_particles(const std::size_t& min_particles) { min_particles_ = min_particles; set_n_particles(); }
  void set_max_particles(const std::size_t& max_particles) { max_particles_ = max_particles; set_n_particles(); }
  void set_min_energy(const double& min_energy) { min_energy_ = min_energy; set_energy_bin_width(); }
  void set_max_energy(const double& max_energy) { max_energy_ = max_energy; set_energy_bin_width(); }
  void set_n_energy(const std::size_t& n_energy) { n_energy_ = n_energy; set_energy_bin_width(); }
  void set_volume(const double& volume) { volume_ = volume; }

  void set_working_directory(const std::string& working_directory) {
    if(working_directory == "") { return; }

    using namespace boost::filesystem;
    path w_dir(working_directory);
    if(!exists(w_dir) || !is_directory(w_dir)) {
      create_directory(w_dir);
    }

    working_directory_ = working_directory;

    if(*(working_directory_.rbegin()) != '/') {
      working_directory_ += '/';
    }
  }

  double bin_to_energy(const std::size_t& bin) {
    return (bin * energy_bin_width_ - min_energy_);
  }

  void print_to_stream(std::ostream& os) {
    os
    << "# nmin     " << min_particles_    << "\n"
    << "# nmax     " << max_particles_    << "\n"
    << "# emin     " << min_energy_       << "\n"
    << "# emax     " << max_energy_       << "\n"
    << "# binwidth " << energy_bin_width_ << "\n"
    << "# N_N      " << n_particles_      << "\n"
    << "# E_N      " << n_energy_         << "\n"
    << "# volume   " << volume_           << "\n";
  }

  void save_to(io::filtering_ostream &out) {
    out.write((char*)&min_particles_,sizeof(min_particles_));
    out.write((char*)&max_particles_,sizeof(max_particles_));
    out.write((char*)&n_particles_,sizeof(n_particles_));
    out.write((char*)&min_energy_,sizeof(min_energy_));
    out.write((char*)&max_energy_,sizeof(max_energy_));
    out.write((char*)&energy_bin_width_,sizeof(energy_bin_width_));
    out.write((char*)&n_energy_,sizeof(n_energy_));
    out.write((char*)&volume_,sizeof(volume_));
  }

  void load_from(io::filtering_istream &in) {
    in.read((char*)&min_particles_,sizeof(min_particles_));
    in.read((char*)&max_particles_,sizeof(max_particles_));
    in.read((char*)&n_particles_,sizeof(n_particles_));
    in.read((char*)&min_energy_,sizeof(min_energy_));
    in.read((char*)&max_energy_,sizeof(max_energy_));
    in.read((char*)&energy_bin_width_,sizeof(energy_bin_width_));
    in.read((char*)&n_energy_,sizeof(n_energy_));
    in.read((char*)&volume_,sizeof(volume_));
  }
};

#endif /* _STATE_H_ */
