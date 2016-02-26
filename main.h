#ifndef MAIN_H
#define MAIN_H

#endif // MAIN_H

#include <QString>
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmAttribute.h"
#include "gdcmStringFilter.h"
#include "gdcmAnonymizer.h"

#ifdef _WIN32_
    #include <cstdlib>
#elif __linux
    #include <unistd.h>
#endif

void PrintUsage();
bool AnonymizeOneFileDumb(gdcm::Anonymizer &anon, const char *filename, const char *outfilename, std::vector<gdcm::Tag> const &empty_tags, std::vector<gdcm::Tag> const &remove_tags, std::vector< std::pair<gdcm::Tag, std::string> > const & replace_tags, bool continuemode);
