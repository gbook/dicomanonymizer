#include <QCoreApplication>
#include <iostream>
#include "main.h"
using namespace std;

bool debug = 0;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /* get command line parameters */
    int level = atoi(argv[1]);
    QString f = argv[2];
    debug = argv[3];

    gdcm::Reader r;
    gdcm::File file;
    gdcm::StringFilter sf;
    gdcm::DataSet ds;
    r.SetFileName(f.toStdString().c_str());
    r.Read();
    sf = gdcm::StringFilter();
    sf.SetFile(r.GetFile());
    file = r.GetFile();
    ds = file.GetDataSet();

    std::vector<gdcm::Tag> empty_tags;
    std::vector<gdcm::Tag> remove_tags;
    std::vector< std::pair<gdcm::Tag, std::string> > replace_tags;
    const char *anonDate = "19000101";
    const char *anonTime = "000000.000000";
    const char *anonString = "Anonymous";

    switch (level) {
        /* full complete anonymization */
        case 1:
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0012))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0012), anonDate) ); /* InstanceCreationDate */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0013))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0013), anonDate) ); /* InstanceCreationTime */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0020))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0020), anonDate) ); /* StudyDate */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0021))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0021), anonDate) ); /* SeriesDate */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0022))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0022), anonDate) ); /* AcquisitionDate */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0023))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0023), anonDate) ); /* ContentDate */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0030))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0030), anonTime) ); /* StudyTime */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0031))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0031), anonTime) ); /* SeriesTime */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0032))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0032), anonTime) ); /* AcquisitionTime */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0033))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0033), anonTime) ); /* ContentTime */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0080))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0080), anonString) ); /* InstitutionName */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0081))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0081), anonString) ); /* InstitutionAddress */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0090))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0090), anonString) ); /* ReferringPhysicianName */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0092))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0092), anonString) ); /* ReferringPhysicianAddress */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0094))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0094), anonString) ); /* ReferringPhysicianTelephoneNumber */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x0096))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0096), anonString) ); /* ReferringPhysicianIDSequence */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x1010))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1010), anonString) ); /* StationName */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x1030))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1030), anonString) ); /* StudyDescription */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x103e))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x103e), anonString) ); /* SeriesDescription */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x1050))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1050), anonString) ); /* PerformingPhysicianName */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x1060))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1060), anonString) ); /* NameOfPhysicianReadingStudy */
            if (ds.FindDataElement(gdcm::Tag(0x0008,0x1070))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1070), anonString) ); /* OperatorsName */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x0010))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0010), anonString) ); /* PatientName */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x0020))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0020), anonString) ); /* PatientID */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x0021))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0021), anonString) ); /* IssuerOfPatientID */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x0030))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0030), anonDate) ); /* PatientBirthDate */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x0032))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0032), anonTime) ); /* PatientBirthTime */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x0050))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0050), anonString) ); /* PatientInsurancePlanCodeSequence */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x1000))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1000), anonString) ); /* OtherPatientIDs */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x1001))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1001), anonString) ); /* OtherPatientNames */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x1005))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1005), anonString) ); /* PatientBirthName */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x1010))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1010), anonString) ); /* PatientAge */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x1020))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1020), anonString) ); /* PatientSize */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x1030))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1030), anonString) ); /* PatientWeight */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x1040))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1040), anonString) ); /* PatientAddress */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x1060))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1060), anonString) ); /* PatientMotherBirthName */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x2154))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x2154), anonString) ); /* PatientTelephoneNumbers */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x21b0))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x21b0), anonString) ); /* AdditionalPatientHistory */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x21f0))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x21f0), anonString) ); /* PatientReligiousPreference */
            if (ds.FindDataElement(gdcm::Tag(0x0010,0x4000))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x4000), anonString) ); /* PatientComments */
            if (ds.FindDataElement(gdcm::Tag(0x0018,0x1030))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0018,0x1030), anonString) ); /* ProtocolName */
            if (ds.FindDataElement(gdcm::Tag(0x0032,0x1032))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0032,0x1032), anonString) ); /* RequestingPhysician */
            if (ds.FindDataElement(gdcm::Tag(0x0032,0x1060))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0032,0x1060), anonString) ); /* RequestedProcedureDescription */
            if (ds.FindDataElement(gdcm::Tag(0x0040,0x0006))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0006), anonString) ); /* ScheduledPerformingPhysiciansName */
            if (ds.FindDataElement(gdcm::Tag(0x0040,0x0244))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0244), anonDate) ); /* PerformedProcedureStepStartDate */
            if (ds.FindDataElement(gdcm::Tag(0x0040,0x0245))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0245), anonTime) ); /* PerformedProcedureStepStartTime */
            if (ds.FindDataElement(gdcm::Tag(0x0040,0x0253))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0253), anonString) ); /* PerformedProcedureStepID */
            if (ds.FindDataElement(gdcm::Tag(0x0040,0x0254))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0254), anonString) ); /* PerformedProcedureStepDescription */
            if (ds.FindDataElement(gdcm::Tag(0x0040,0x4036))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x4036), anonString) ); /* HumanPerformerOrganization */
            if (ds.FindDataElement(gdcm::Tag(0x0040,0x4037))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x4037), anonString) ); /* HumanPerformerName */
            if (ds.FindDataElement(gdcm::Tag(0x0040,0xa123))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0xa123), anonString) ); /* PersonName */
            break;
        default:
            cout<<"Unrecognized anonymization level. Must be 1 (full)"<<endl;
            break;
    }

    gdcm::Anonymizer anon;
    if (AnonymizeOneFileDumb(anon,f.toStdString().c_str(),f.toStdString().c_str(),empty_tags,remove_tags,replace_tags,false)) {
        cout<<"Successfully anonymized"<<endl;
    }
    else {
        cout<<"Error anonymizing"<<endl;
    }

    return a.exec();
}

void PrintUsage() {
    cout<<"DicomAnonymizer <level> <filepath>"<<endl;
}


/* ------------------------------------------------- */
/* --------- AnonymizeOneFileDumb ------------------ */
/* ------------------------------------------------- */
/* borrowed in its entirety from gdcmanon.cxx        */
bool AnonymizeOneFileDumb(gdcm::Anonymizer &anon, const char *filename, const char *outfilename, std::vector<gdcm::Tag> const &empty_tags, std::vector<gdcm::Tag> const &remove_tags, std::vector< std::pair<gdcm::Tag, std::string> > const & replace_tags, bool continuemode)
{
    gdcm::Reader reader;
    reader.SetFileName( filename );
    if( !reader.Read() ) {
        cout << "Could not read : " << filename << std::endl;
        if( continuemode ) {
            cout << "Skipping from anonymization process (continue mode)." << std::endl;
            return true;
        }
        else
        {
            cout << "Check [--continue] option for skipping files." << std::endl;
            return false;
        }
    }
    gdcm::File &file = reader.GetFile();

    anon.SetFile( file );

    if( empty_tags.empty() && replace_tags.empty() && remove_tags.empty() ) {
        cout << "No operation to be done." << std::endl;
        return false;
    }

    std::vector<gdcm::Tag>::const_iterator it = empty_tags.begin();
    bool success = true;
    for(; it != empty_tags.end(); ++it) {
        success = success && anon.Empty( *it );
    }
    it = remove_tags.begin();
    for(; it != remove_tags.end(); ++it) {
        success = success && anon.Remove( *it );
    }

    std::vector< std::pair<gdcm::Tag, std::string> >::const_iterator it2 = replace_tags.begin();
    for(; it2 != replace_tags.end(); ++it2) {
        if (debug) cout<<"Replacing tag ["<<it2->first<<"] with value ["<<it2->second.c_str()<<"]";
        success = success && anon.Replace( it2->first, it2->second.c_str());
        if (debug) cout<<" - success: ["<<success<<"]"<<endl;
    }

    gdcm::Writer writer;
    writer.SetFileName( outfilename );
    writer.SetFile( file );
    if( !writer.Write() ) {
        cout << "Could not Write : " << outfilename << std::endl;
        if( strcmp(filename,outfilename) != 0 ) {
            gdcm::System::RemoveFile( outfilename );
        }
        else
        {
            cout << "gdcmanon just corrupted: " << filename << " for you (data lost)." << std::endl;
        }
        return false;
    }

    return success;
}
