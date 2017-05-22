// See LICENSE_CELLO file for license and copyright information

/// @file     io_OutputData.hpp 
/// @author   James Bordner (jobordner@ucsd.edu) 
/// @date     2011-09-19
/// @brief    [\ref Io] Declaration of the OutputData class

#ifndef IO_OUTPUT_DATA_HPP
#define IO_OUTPUT_DATA_HPP

class Factory;
class Hierarchy;
class FieldDescr;
class ParticleDescr;
class Config;

class OutputData : public Output {

  /// @class    OutputData
  /// @ingroup  Io
  /// @brief    [\ref Io] define interface for data I/O

public: // functions

  /// Empty constructor for Charm++ pup()
  OutputData() throw() : text_block_count_(0) {}

  /// Create an uninitialized OutputData object
  OutputData(int index,
	     const Factory * factory,
	     const FieldDescr * field_descr,
	     const ParticleDescr * particle_descr,
	     Config * config) throw();

  /// Close the file if it is open
  virtual ~OutputData() throw();

  /// Charm++ PUP::able declarations
  PUPable_decl(OutputData);

  /// Charm++ PUP::able migration constructor
  OutputData (CkMigrateMessage *m) : Output (m) {}

  /// CHARM++ Pack / Unpack function
  void pup (PUP::er &p);

public: // virtual functions

  /// Initialize next output
  virtual void init () throw()
  {} ;

  /// Open (or create) a file for IO
  virtual void open () throw();

  /// Close file for IO
  virtual void close () throw();

  /// Finalize output
  virtual void finalize () throw ();

  /// Write hierarchy data to disk
  virtual void write_hierarchy
  ( const Hierarchy * hierarchy,
    const FieldDescr * field_descr,
    const ParticleDescr * particle_descr) throw();

  /// Write block data to disk
  virtual void write_block
  ( const Block      * block,
    const FieldDescr * field_descr,
    const ParticleDescr * particle_descr) throw();


  /// Write local field to disk
  virtual void write_field_data
  ( const FieldData * field_data,
    const FieldDescr * field_descr,
    int index_field) throw();

  /// Write local particle to disk
  virtual void write_particle_data
  ( const ParticleData * particle_data,
    const ParticleDescr * particle_descr,
    int index_particle) throw();

protected:

  /// Count of number of Blocks sent from local process for text file
  /// output
  int text_block_count_;
};

#endif /* IO_OUTPUT_DATA_HPP */