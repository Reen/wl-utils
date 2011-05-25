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

struct MatrixHeader {
  uint32_t version;
  uint32_t matrix_type;
  uint32_t githead_strlen;
  bool operator==(const MatrixHeader &rhs) const {
    return (version == rhs.version
        && matrix_type == rhs.matrix_type
        && githead_strlen == rhs.githead_strlen);
  }
};

#pragma pack(push)
#pragma pack(1)
struct MatrixSettings {
  uint32_t min_particles;
  uint32_t max_particles;
  uint32_t n_particles;
  double min_energy;
  double max_energy;
  double energy_bin_width;
  uint32_t n_energy;
  double volume;
  bool operator==(const MatrixSettings &rhs) const {
    return (  min_particles == rhs.min_particles
        &&    max_particles == rhs.max_particles
        &&      n_particles == rhs.n_particles
        &&       min_energy == rhs.min_energy
        &&       max_energy == rhs.max_energy
        && energy_bin_width == rhs.energy_bin_width
        &&         n_energy == rhs.n_energy
        &&           volume == rhs.volume);
  }
};
#pragma pack(pop)

struct MatrixDimensions {
  uint32_t outer_cols;
  uint32_t outer_rows;
  uint32_t inner_cols;
  uint32_t inner_rows;
  bool operator==(const MatrixDimensions &rhs) const {
    return (outer_cols == rhs.outer_cols
        &&  outer_rows == rhs.outer_rows
        &&  inner_cols == rhs.inner_cols
        &&  inner_rows == rhs.inner_rows);
  }
};

struct StateData {
public:
  MatrixHeader header;
  char* githead;
  MatrixSettings settings;

  StateData() : githead(NULL) {}

  // destructor deletes githead string
  ~StateData() {
    if (githead != NULL) {
      delete githead;
    }
  }
};

class State : public boost::singleton<State> {
private:
  StateData data;
  double half_energy_bin_width_;
  std::string working_directory_;

  void set_n_particles() {
    data.settings.n_particles =
      data.settings.max_particles - data.settings.min_particles + 1;
  }

  void set_energy_bin_width() {
    data.settings.energy_bin_width = (data.settings.max_energy-data.settings.min_energy)/data.settings.n_energy;
    half_energy_bin_width_ = (data.settings.energy_bin_width/2.0);
  }
public:
  State(boost::restricted) {}

  const uint32_t& min_particles() const { return data.settings.min_particles; }
  const uint32_t& max_particles() const { return data.settings.max_particles; }
  const uint32_t& n_particles() const { return data.settings.n_particles; }
  const double& min_energy() const { return data.settings.min_energy; }
  const double& max_energy() const { return data.settings.max_energy; }
  const uint32_t& n_energy() const { return data.settings.n_energy; }
  const double& energy_bin_width() const { return data.settings.energy_bin_width; }
  const double& half_energy_bin_width() const { return half_energy_bin_width_; }
  const double& volume() const { return data.settings.volume; }
  const std::string& working_directory() const { return working_directory_; }
  bool have_working_directory() const { return (working_directory_.size() != 0); }
  std::string githead() const { return data.githead; }
  const uint32_t& matrix_type() const { return data.header.matrix_type; }

  void set_min_particles(const std::size_t& min_particles) {
    data.settings.min_particles = min_particles;
    set_n_particles();
  }

  void set_max_particles(const std::size_t& max_particles) {
    data.settings.max_particles = max_particles;
    set_n_particles();
  }

  void set_min_energy(const double& min_energy) {
    data.settings.min_energy = min_energy;
    set_energy_bin_width();
  }

  void set_max_energy(const double& max_energy) {
    data.settings.max_energy = max_energy;
    set_energy_bin_width();
  }

  void set_n_energy(const std::size_t& n_energy)
  {
    data.settings.n_energy = n_energy;
    set_energy_bin_width();
  }

  void set_volume(const double& volume) {
    data.settings.volume = volume;
  }

  void set_matrix_type(const std::size_t& mt) {
    data.header.matrix_type = mt;
  }

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
    return (bin * data.settings.energy_bin_width + data.settings.min_energy
            + half_energy_bin_width_);
  }

  void print_to_stream(std::ostream& os) {
    os
    << "# towhee   " << data.githead                   << "\n"
    << "# nmin     " << data.settings.min_particles    << "\n"
    << "# nmax     " << data.settings.max_particles    << "\n"
    << "# emin     " << data.settings.min_energy       << "\n"
    << "# emax     " << data.settings.max_energy       << "\n"
    << "# binwidth " << data.settings.energy_bin_width << "\n"
    << "# N_N      " << data.settings.n_particles      << "\n"
    << "# E_N      " << data.settings.n_energy         << "\n"
    << "# volume   " << data.settings.volume           << "\n";
  }

  void save_to(io::filtering_ostream &out) {
    out.write((char*)&data.header, sizeof(MatrixHeader));
    if (data.header.githead_strlen > 0) {
      out.write(data.githead, data.header.githead_strlen);
    }
    out.write((char*)&data.settings, sizeof(MatrixSettings));
  }

  void load_from(io::filtering_istream &in) {
    in.read((char*)&(data.header), sizeof(MatrixHeader));
    if (data.header.version != 1) {
      throw std::runtime_error("Unknown parq matrix file version.");
    }
    if (data.header.githead_strlen > 0) {
      data.githead = new char[data.header.githead_strlen+1];
      in.read(data.githead, data.header.githead_strlen);
      data.githead[data.header.githead_strlen] = '\0';
    }
    in.read((char*)&(data.settings), sizeof(MatrixSettings));
    set_energy_bin_width();
  }
};

#endif /* _STATE_H_ */
