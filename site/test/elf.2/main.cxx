//#include <Poco/any.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
//#include <algorithm>	// For for_each ()
//#include <omp.h>
//#include <unordered_map>
//#include <typeinfo>
//#include <list>
//#include <string>
//#include <stack>

// #include <cln/cln.h>

//
//// Boost:
//#include <boost/any.hpp>
//#include <boost/thread.hpp>
//// Boost serialization:
//#include <boost/serialization/serialization.hpp>
//#include <boost/serialization/split_member.hpp>	// For separating reading and writing.
//#include <boost/serialization/list.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
////#include <boost/archive/binary_oarchive.hpp>
////#include <boost/archive/binary_iarchive.hpp>

//#include <noware/array>
//#include <noware/var>
//#include <noware/machine>
//#include <noware/container/entity.h++>

//////#include <noware/containers/entity.h++>
////#include <noware/containers/variable-undefine.h++>
//#include <noware/math.h++>
//#include <noware/serialization.h++>

//#include <noware/containers/text.h++>
//#include <noware/containers/any.hpp>
//#include <NoWare/Container/Variable.h>
//#include <noware/containers/array.hpp>
//#include <NoWare/Containers/Dynamic.h>
//#include <NoWare/Containers/Dynamic.cpp>
//#include "MPI.h"
//#include <noware/cluster.h++>
//#include "Memory.h"
//#include "HPC.cpp"
//#include "Numerical Strings.h"
#include <noware/misc/elf>
#include <noware/unsigned_string>

//#include <vector>
//struct My
//{
//	int x, y;
//};

/*
const unsigned int str_int (const std::string & block, const bool & swap = false)
{
	unsigned int val;
	unsigned int size;
	std::stringstream ss;
	
	//val = 0;
	size = block.size ();
	ss << std::hex;
	
	if (swap)
	{
		for (signed int ndx = size; ndx >= 0; --ndx)
		{
			//std::cout << "ndx:" << ndx << std::endl;
			ss << int (block [ndx]);
		}
	}
	else
	{
		for (unsigned int ndx = 0; ndx < size; ++ndx)
		{
			//std::cout << "ndx:" << ndx << std::endl;
			ss << int (block [ndx]);
		}
	}
	
	ss >> val;
	
	return val;
}
*/

int main (int argc, char * argv [])
{
	//using boost::any_cast;
	//using namespace std;
	//using boost;
	//using namespace noware;
	
	std::cout << std::boolalpha;
	//std::cout << std::hex;
	std::cout << std::showbase;
	
	for (/*unsigned long long*/ int i = 0; i < argc; ++ i)
		std::cout << argv [i] << ' ';
	std::cout << std::endl;
	std::cout << "argument count [" << argc << ']' << std::endl;
	
	if (argc < 2)
	{
		std::cout << "'" << argv [0] << "'" << " '<file.elf>'" << std::endl;
		
		return EXIT_FAILURE;
	}
	
	noware::elf file;
	noware::unsigned_string content;
	
	content = file.read (argv [1]);
	
	if (content.empty ())
	{
		std::cout << "'" << argv [0] << "': error: could not read file '" << argv [1] << "'" << std::endl;
		return EXIT_FAILURE;
	}
	
	std::cout << "'" << argv [0] << "': success: read file '" << argv [1] << "'" << std::endl;
	
	if (!file.load (content))
	{
		std::cout << "'" << argv [0] << "': error: could not load file '" << argv [1] << "'" << std::endl;
		
		std::cout << "the content was:" << std::endl;
		//std::cout << content << std::endl;
		return EXIT_FAILURE;
	}
	
	std::cout << "'" << argv [0] << "': success: loaded file '" << argv [1] << "'" << std::endl;
}
