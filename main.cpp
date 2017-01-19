#include <QCoreApplication>
#include <iostream>
#include "main.h"
using namespace std;

bool debug = 0;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if ((argc != 7) && (argc != 8)) {
        PrintUsage(QString("Incorrect number of parameters [%1]. Should be 6 or 7").arg(argc));
        exit(0);
    }

    /* get command line parameters */
    int PatientInfoName = 0;
    int PatientInfoNonName = 0;
    int InstitutionInfo = 0;
    int DatesOfService = 0;
    int ScanInfo = 0;
    QString f = "";

    PatientInfoName = atoi(argv[1]);
    PatientInfoNonName = atoi(argv[2]);
    InstitutionInfo = atoi(argv[3]);
    DatesOfService = atoi(argv[4]);
    ScanInfo = atoi(argv[5]);
    f = argv[6];
    debug = argv[7];

    /* validate the input parameters */
    QString msg = CheckInputParams(PatientInfoName,PatientInfoNonName,InstitutionInfo,DatesOfService,ScanInfo,f,debug);
    if (msg != "") {
        PrintUsage(msg);
    }

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

    if (PatientInfoName) {
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x0010))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0010), anonString) ); /* PatientName */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x0030))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0030), anonDate) ); /* PatientBirthDate */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x0032))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0032), anonTime) ); /* PatientBirthTime */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x1001))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1001), anonString) ); /* OtherPatientNames */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x1005))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1005), anonString) ); /* PatientBirthName */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x1060))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1060), anonString) ); /* PatientMotherBirthName */
        if (ds.FindDataElement(gdcm::Tag(0x0040,0xa123))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0xa123), anonString) ); /* PersonName */
    }
    if (PatientInfoNonName) {
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x0020))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0020), anonString) ); /* PatientID */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x0050))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0050), anonString) ); /* PatientInsurancePlanCodeSequence */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x1000))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1000), anonString) ); /* OtherPatientIDs */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x1010))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1010), anonString) ); /* PatientAge */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x1020))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1020), anonString) ); /* PatientSize */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x1030))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1030), anonString) ); /* PatientWeight */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x1040))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x1040), anonString) ); /* PatientAddress */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x2154))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x2154), anonString) ); /* PatientTelephoneNumbers */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x21b0))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x21b0), anonString) ); /* AdditionalPatientHistory */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x21f0))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x21f0), anonString) ); /* PatientReligiousPreference */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x4000))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x4000), anonString) ); /* PatientComments */
    }
    if (InstitutionInfo) {
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x0080))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0080), anonString) ); /* InstitutionName */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x0081))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0081), anonString) ); /* InstitutionAddress */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x0090))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0090), anonString) ); /* ReferringPhysicianName */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x0092))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0092), anonString) ); /* ReferringPhysicianAddress */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x0094))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0094), anonString) ); /* ReferringPhysicianTelephoneNumber */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x0096))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x0096), anonString) ); /* ReferringPhysicianIDSequence */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x1010))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1010), anonString) ); /* StationName */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x1050))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1050), anonString) ); /* PerformingPhysicianName */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x1060))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1060), anonString) ); /* NameOfPhysicianReadingStudy */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x1070))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1070), anonString) ); /* OperatorsName */
        if (ds.FindDataElement(gdcm::Tag(0x0010,0x0021))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0010,0x0021), anonString) ); /* IssuerOfPatientID */
        if (ds.FindDataElement(gdcm::Tag(0x0040,0x4036))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x4036), anonString) ); /* HumanPerformerOrganization */
        if (ds.FindDataElement(gdcm::Tag(0x0040,0x4037))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x4037), anonString) ); /* HumanPerformerName */
        if (ds.FindDataElement(gdcm::Tag(0x0032,0x1032))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0032,0x1032), anonString) ); /* RequestingPhysician */
        if (ds.FindDataElement(gdcm::Tag(0x0040,0x0006))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0006), anonString) ); /* ScheduledPerformingPhysiciansName */
    }
    if (DatesOfService) {
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
        if (ds.FindDataElement(gdcm::Tag(0x0040,0x0244))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0244), anonDate) ); /* PerformedProcedureStepStartDate */
        if (ds.FindDataElement(gdcm::Tag(0x0040,0x0245))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0245), anonTime) ); /* PerformedProcedureStepStartTime */
    }
    if (ScanInfo) {
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x1030))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x1030), anonString) ); /* StudyDescription */
        if (ds.FindDataElement(gdcm::Tag(0x0008,0x103e))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0008,0x103e), anonString) ); /* SeriesDescription */
        if (ds.FindDataElement(gdcm::Tag(0x0018,0x1030))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0018,0x1030), anonString) ); /* ProtocolName */
        if (ds.FindDataElement(gdcm::Tag(0x0032,0x1060))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0032,0x1060), anonString) ); /* RequestedProcedureDescription */
        if (ds.FindDataElement(gdcm::Tag(0x0040,0x0253))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0253), anonString) ); /* PerformedProcedureStepID */
        if (ds.FindDataElement(gdcm::Tag(0x0040,0x0254))) replace_tags.push_back( std::make_pair(gdcm::Tag(0x0040,0x0254), anonString) ); /* PerformedProcedureStepDescription */
    }

    gdcm::Anonymizer anon;
    if (AnonymizeOneFileDumb(anon,f.toStdString().c_str(),f.toStdString().c_str(),empty_tags,remove_tags,replace_tags,false)) {
        cout<<"Successfully anonymized ["<<f.toStdString().c_str()<<"]"<<endl;
    }
    else {
        cout<<"Error anonymizing"<<endl;
    }
    exit(0);

    return a.exec();
}


/* ------------------------------------------------- */
/* --------- CheckInputParams ---------------------- */
/* ------------------------------------------------- */
QString CheckInputParams(int PatientInfoName, int PatientInfoNonName, int InstitutionInfo, int DatesOfService, int ScanInfo, QString f, int dbg) {

    if ((PatientInfoName != 0) && (PatientInfoName != 1))
        return "PatientInfoName parameter is not valid";
    if ((PatientInfoNonName != 0) && (PatientInfoNonName != 1))
        return "PatientInfoNonName parameter is not valid";
    if ((InstitutionInfo != 0) && (InstitutionInfo != 1))
        return "InstitutionInfo parameter is not valid";
    if ((DatesOfService != 0) && (DatesOfService != 1))
        return "DatesOfService parameter is not valid";
    if ((ScanInfo != 0) && (ScanInfo != 1))
        return "ScanInfo parameter is not valid";

    QFileInfo checkFile(f);
    if (!checkFile.exists() || !checkFile.isFile())
        return "Filename is not valid";

    if ((dbg != 0) && (dbg != 1))
        return "Debug parameter is not valid";


    return "";
}


/* ------------------------------------------------- */
/* --------- PrintUsage ---------------------------- */
/* ------------------------------------------------- */
void PrintUsage(QString msg) {

    cout<<"Tag Listing for anonymization groups\n\nPatientInfoName\n \
    0010,0010 - PatientName\n \
    0010,0030 - PatientBirthDate\n \
    0010,0032 - PatientBirthTime\n \
    0010,1001 - OtherPatientNames\n \
    0010,1005 - PatientBirthName\n \
    0010,1060 - PatientMotherBirthName\n \
    0040,a123 - PersonName\n \
    \n\
    PatientInfoNonName\n \
    0010,0020 - PatientID\n \
    0010,0050 - PatientInsurancePlanCodeSequence\n \
    0010,1000 - OtherPatientIDs\n \
    0010,1010 - PatientAge\n \
    0010,1020 - PatientSize\n \
    0010,1030 - PatientWeight\n \
    0010,1040 - PatientAddress\n \
    0010,2154 - PatientTelephoneNumbers\n \
    0010,21b0 - AdditionalPatientHistory\n \
    0010,21f0 - PatientReligiousPreference\n \
    0010,4000 - PatientComments\n \
    \n\
    InstitutionInfo\n \
    0008,0080 - InstitutionName\n \
    0008,0081 - InstitutionAddress\n \
    0008,0090 - ReferringPhysicianName\n \
    0008,0092 - ReferringPhysicianAddress\n \
    0008,0094 - ReferringPhysicianTelephoneNumber\n \
    0008,0096 - ReferringPhysicianIDSequence\n \
    0008,1010 - StationName\n \
    0008,1050 - PerformingPhysicianName\n \
    0008,1060 - NameOfPhysicianReadingStudy\n \
    0008,1070 - OperatorsName\n \
    0010,0021 - IssuerOfPatientID\n \
    0040,4036 - HumanPerformerOrganization\n \
    0040,4037 - HumanPerformerName\n \
    0032,1032 - RequestingPhysician\n \
    0040,0006 - ScheduledPerformingPhysiciansName\n \
    \n\
    DatesOfService\n \
    0008,0012 - InstanceCreationDate\n \
    0008,0013 - InstanceCreationTime\n \
    0008,0020 - StudyDate\n \
    0008,0021 - SeriesDate\n \
    0008,0022 - AcquisitionDate\n \
    0008,0023 - ContentDate\n \
    0008,0030 - StudyTime\n \
    0008,0031 - SeriesTime\n \
    0008,0032 - AcquisitionTime\n \
    0008,0033 - ContentTime\n \
    0040,0244 - PerformedProcedureStepStartDate\n \
    0040,0245 - PerformedProcedureStepStartTime\n \
    \n\
    ScanInfo\n \
    0008,1030 - StudyDescription\n \
    0008,103e - SeriesDescription\n \
    0018,1030 - ProtocolName\n \
    0032,1060 - RequestedProcedureDescription\n \
    0040,0253 - PerformedProcedureStepID\n \
    0040,0254 - PerformedProcedureStepDescription\n";

    cout<<"Usage:\n\n\tDicomAnonymizer <PatientInfoName> <PatientInfoNonName> <InstitutionInfo> <DatesOfService> <ScanInfo> <filepath> <debug(optional)>\n\n";
    cout<<"Examples:\n\n";
    cout<<"\tDicomAnonymizer 1 1 1 0 0 TheDicomfile.dcm\n";
    cout<<"\tDicomAnonymizer 1 0 1 0 1 TheDicomfile.dcm 1\n";

    qDebug()<<"\nERROR: ["<<msg<<"]\n";
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
            //cout << "Check [--continue] option for skipping files." << std::endl;
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
