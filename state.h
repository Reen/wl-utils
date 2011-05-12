#ifndef _STATE_H_
#define _STATE_H_

#include <stdexcept>
#include <iostream>

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
  double half_energy_bin_width_;
  std::size_t n_energy_;
  double volume_;
  std::string working_directory_;
  std::string githead_;
  std::size_t matrix_type_;

  void set_n_particles() {
    n_particles_ = max_particles_ - min_particles_ + 1;
  }

  void set_energy_bin_width() {
    energy_bin_width_ = (max_energy_-min_energy_)/n_energy_;
    half_energy_bin_width_ = (energy_bin_width_/2.0);
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
  const double& half_energy_bin_width() const { return half_energy_bin_width_; }
  const double& volume() const { return volume_; }
  const std::string& working_directory() const { return working_directory_; }
  bool have_working_directory() const { return (working_directory_.size() != 0); }
  const std::string& githead() const { return githead_; }
  const std::size_t& matrix_type() const { return matrix_type_; }

  void set_min_particles(const std::size_t& min_particles) { min_particles_ = min_particles; set_n_particles(); }
  void set_max_particles(const std::size_t& max_particles) { max_particles_ = max_particles; set_n_particles(); }
  void set_min_energy(const double& min_energy) { min_energy_ = min_energy; set_energy_bin_width(); }
  void set_max_energy(const double& max_energy) { max_energy_ = max_energy; set_energy_bin_width(); }
  void set_n_energy(const std::size_t& n_energy) { n_energy_ = n_energy; set_energy_bin_width(); }
  void set_volume(const double& volume) { volume_ = volume; }
  void set_matrix_type(const std::size_t& mt) { matrix_type_ = mt; }

  void set_working_directory(const std::string& working_directory) {
    if(working_directory == "") { return; }

    using namespace boost::filesystem;
    using namespace boost::system;
    path w_dir(working_directory);
    if (!exists(w_dir)) {
      create_directory(w_dir);
    }

    if (!is_directory(w_dir)) {
      throw filesystem_error(std::string("Working directory could not be created."),
          w_dir, error_code(errc::not_a_directory, generic_category()));
    }

    working_directory_ = working_directory;

    if (*(working_directory_.rbegin()) != '/') {
      working_directory_ += '/';
    }
  }

  double bin_to_energy(const std::size_t& bin) {
    return (bin * energy_bin_width_ + min_energy_
            + half_energy_bin_width_);
  }

  void print_to_stream(std::ostream& os) {
    os
    << "# towhee   " << githead_          << "\n"
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
    uint32_t min_p(min_particles_), max_p(max_particles_);
    uint32_t n_p(n_particles_), n_e(n_energy_);
    uint32_t version = 1;
    uint32_t type = 2;
    uint32_t githeadstrlen = githead_.size();
    out.write((char*)&version,sizeof(version));
    out.write((char*)&type,sizeof(type));
    out.write((char*)&githeadstrlen,sizeof(githeadstrlen));
    if (githeadstrlen > 0) {
      out.write(githead_.c_str(), githeadstrlen);
    }
    out.write((char*)&min_p,sizeof(min_p));
    out.write((char*)&max_p,sizeof(max_p));
    out.write((char*)&n_p,sizeof(n_p));
    out.write((char*)&min_energy_,sizeof(min_energy_));
    out.write((char*)&max_energy_,sizeof(max_energy_));
    out.write((char*)&energy_bin_width_,sizeof(energy_bin_width_));
    out.write((char*)&n_e,sizeof(n_e));
    out.write((char*)&volume_,sizeof(volume_));
  }

  void load_from(io::filtering_istream &in) {
    uint32_t min_p, max_p, n_p, n_e, version, type, githeadstrlen;
    char * githead;
    in.read((char*)&version,sizeof(version));
    if (version != 1) {
      throw std::runtime_error("Unknown parq matrix file version.");
    }
    in.read((char*)&type,sizeof(type));
    in.read((char*)&githeadstrlen, sizeof(githeadstrlen));
    if (githeadstrlen > 0) {
      githead = new char[githeadstrlen+1];
      in.read(githead, githeadstrlen);
      githead[githeadstrlen] = '\0';
      githead_ = githead;
      delete githead;
    }
    in.read((char*)&min_p,sizeof(min_p));
    in.read((char*)&max_p,sizeof(max_p));
    in.read((char*)&n_p,sizeof(n_p));
    in.read((char*)&min_energy_,sizeof(min_energy_));
    in.read((char*)&max_energy_,sizeof(max_energy_));
    in.read((char*)&energy_bin_width_,sizeof(energy_bin_width_));
    in.read((char*)&n_e,sizeof(n_e));
    in.read((char*)&volume_,sizeof(volume_));
    matrix_type_ = type;
    min_particles_ = min_p;
    max_particles_ = max_p;
    n_particles_ = n_p;
    n_energy_ = n_e;
    std::cout << "settings: " << min_p << " " << max_p << " " << n_p << " "
      << min_energy_ << " " << max_energy_ << " " << energy_bin_width_ << " "
      << n_e << " "
      << volume_ << std::endl;
    set_energy_bin_width();
  }
};

#endif /* _STATE_H_ */
