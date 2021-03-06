#pragma once

#include <map>

#include <noware/str_nsigned.hxx>

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
				
				static noware::str_nsigned const read (std::string const &/* file_name*/);
				virtual bool const load (noware::str_nsigned const &/* content as a string*/);
				virtual bool const & loaded (void) const;
				virtual bool const clear (void);
				
				// concatenate a char array of hex ints to one int
				static unsigned long int const integer (const noware::str_nsigned &/* block*/, bool const &/* swap the ends of the array (for endianness) */ = false);
				
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
