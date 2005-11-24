//<<<<<< INCLUDES                                                       >>>>>>

#include "Utilities/RFIOAdaptor/interface/RFIOFile.h"
#include "SealIOTools/StorageStreamBuf.h"
#include "SealBase/Error.h"
#include "SealBase/Signal.h"
#include <iostream>
#include <iomanip>

//<<<<<< PRIVATE DEFINES                                                >>>>>>
//<<<<<< PRIVATE CONSTANTS                                              >>>>>>
//<<<<<< PRIVATE TYPES                                                  >>>>>>
//<<<<<< PRIVATE VARIABLE DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC VARIABLE DEFINITIONS                                    >>>>>>
//<<<<<< CLASS STRUCTURE INITIALIZATION                                 >>>>>>
//<<<<<< PRIVATE FUNCTION DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC FUNCTION DEFINITIONS                                    >>>>>>
//<<<<<< MEMBER FUNCTION DEFINITIONS                                    >>>>>>

using namespace seal;
int main (int, char **argv)
{
    Signal::handleFatal (argv [0]);

    try
    {
	std::string	user (UserInfo::self ()->id ());
	std::string	path (std::string ("/castor/cern.ch/user/")
		       	      + user[0] + "/" + user + "/rfiotest");

	RFIOFile		storage (path.c_str (),
				         IOFlags::OpenRead
				         | IOFlags::OpenWrite
				         | IOFlags::OpenCreate
				         | IOFlags::OpenTruncate);
	StorageStreamBuf	buf (&storage);
	std::ostream		output (&buf);

	for (int i = 0; i < 100; ++i)
	    output << "sample output line " << i << std::endl;

	output.flush ();
	storage.close ();
    }
    catch (Error &e)
    {
	std::cerr << e.explain () << std::endl;
	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
