#pragma once

#include <map>

#include <noware/unsigned_string.hxx>

namespace noware
{
	//namespace misc
	//{
		class elf
		{
			public:
				#include ".elf/.hxx"
				
				elf (void);
				virtual ~elf (void);
				
				static noware::unsigned_string const read (std::string const &/* file_name*/);
				virtual bool const load (noware::unsigned_string const &/* content as a string*/);
				virtual bool const & loaded (void) const;
				virtual bool const clear (void);
				
				// concatenate a char array of hex ints to one int
				static unsigned long int const integer (const noware::unsigned_string &/* block*/, bool const &/* swap the ends of the array (for endianness) */ = false);
				
				virtual unsigned short int const & bits (void);
			//protected:
			//	header _header;
				header hdr;
				//body data;
				// the program header table (the segments)
				std::map <unsigned int, program> prog;
				// the section header table (the sections)
				std::map <unsigned int, section> sect;
			protected:
				bool _loaded;
				//virtual const bool load_file_header_x86 (std::ifstream &/* file*/, const std::streampos &/* size*/);
				//virtual const bool load_file_header_x64 (std::ifstream &/* file*/, const std::streampos &/* size*/);
				
				unsigned short int _bits;
		};
	//}
}
