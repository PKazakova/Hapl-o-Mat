#ifndef DataProcessing_header
#define DataProcessing_header

#include <string>

#include "Glid.h"
#include "Typedefs.h"
#include "Allele.h"

class DataProcessing{

 public:
  explicit DataProcessing(const std::string in_inputFileName,
			  const Allele::codePrecision in_wantedPrecision,
			  const double in_minimalFrequency)
    : inputFileName(in_inputFileName),
    wantedPrecision(in_wantedPrecision),
    minimalFrequency(in_minimalFrequency){}
  virtual ~DataProcessing(){}

  virtual void dataProcessing() = 0;



 protected:
  std::string inputFileName;
  size_t numberLoci;
  Allele::codePrecision wantedPrecision;
  double minimalFrequency;
};

class GLDataProcessing : public DataProcessing{

 public:
  explicit GLDataProcessing(const std::string in_inputFileName,
			    const std::string in_glidFileName,
			    const strVec_t & in_lociToDo,
			    const Allele::codePrecision in_wantedPrecision,
			    const double in_minimalFrequency)
    : DataProcessing(in_inputFileName, in_wantedPrecision, in_minimalFrequency),
    glidFileName(in_glidFileName),
    lociToDo(in_lociToDo),
    glid(glidFileName)
    {
      for(auto locus : in_lociToDo){
	if(locus != "None")
	  booleanLociToDo.push_back(true);
	else
	  booleanLociToDo.push_back(false);
      }
    }

  virtual void dataProcessing();

 private:
  std::string glidFileName;
  strVec_t lociToDo;
  std::vector<bool> booleanLociToDo;
  GlidFile glid;
};

class DKMSDataProcessing : public DataProcessing{

 public:
  explicit DKMSDataProcessing(const std::string in_inputFileName,
			      const Allele::codePrecision in_wantedPrecision,
			      const double in_minimalFrequency)
    : DataProcessing(in_inputFileName, in_wantedPrecision, in_minimalFrequency){}

  virtual void dataProcessing();

  void readLociNames(const std::string line);

 private:
  strVec_t lociNames;
};

#endif
