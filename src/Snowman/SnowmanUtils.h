#ifndef SNOWMAN_UTILS_H__
#define SNOWMAN_UTILS_H__

#include <ctime>
#include <sstream>
#include <unordered_map>
#include <map>

#include "SnowTools/BamWalker.h"
#include "SnowTools/BWAWrapper.h"
#include "SnowTools/RefGenome.h"

namespace SnowmanUtils {

// make a structure to store timing opt
struct SnowTimer {
  
  SnowTimer();

  std::unordered_map<std::string, double> times;
  std::vector<std::string> s;

  clock_t curr_clock;

  void stop(const std::string& part);

  void start();
  
  // print it
  friend std::ostream& operator<<(std::ostream &out, const SnowTimer st);
};
 
 int overlapSize(const SnowTools::BamRead& query, const SnowTools::BamReadVector& subject);
 bool hasRepeat(const std::string& seq);
 std::string runTimeString(int num_t_reads, int num_n_reads, int contig_counter, 
			   const SnowTools::GenomicRegion& region, const bam_hdr_t * h, const SnowTimer& st, 
			   const timespec& start);
 int countJobs(const std::string& regionFile, SnowTools::GRC &file_regions, SnowTools::GRC &run_regions, 
	       bam_hdr_t * h, int chunk, int window_pad);
 
  template <typename T>
  void fopen(const std::string& s, T& o) {
    o.open(s.c_str(), std::ios::out);
  }

  void print(std::stringstream& s, std::ofstream& log, bool cerr);

  std::string fileDateString();

  std::string __bamOptParse(std::map<std::string, std::string>& obam, std::istringstream& arg, int sample_number, const std::string& prefix);

  void __openWriterBam(const SnowTools::BamWalker& bwalker, const std::string& name, SnowTools::BamWalker& wbam);

  void __open_bed(const std::string& f, SnowTools::GRC& b, bam_hdr_t* h);

  bool __header_has_chr_prefix(bam_hdr_t * h);

  void __open_index_and_writer(const std::string& index, SnowTools::BWAWrapper * b, const std::string& wname, SnowTools::BamWalker& writer, SnowTools::RefGenome *&  r, bam_hdr_t *& bwa_header);

}


#endif
