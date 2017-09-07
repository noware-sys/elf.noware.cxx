#pragma once

#include "elf.hxx"

#include <fstream>
#include <iostream>
#include <iomanip>

#include "../unsigned_string.cxx"

noware::elf::elf (void)
{
	//_loaded = false;
}

noware::elf::~elf (void)
{
}

const bool noware::elf::load (const noware::unsigned_string & data)
{
	bool x64;
	unsigned long int offset;
	unsigned long int offset_section;
	unsigned long int section_size;
	unsigned long int offset_segment;
	unsigned long int segment_size;
	unsigned long int e_shnum;
	unsigned long int e_phnum;
	std::cerr << std::boolalpha;
	std::cerr << std::hex;
	std::cerr << std::showbase;
	
	// there should be at least the magic number present,
	// I guess
	// . E L F
	// 0x7F 0x45 0x4C 0x46
	if (data.size () < 4)
	{
		std::cerr << "debug::noware::elf::load::(data.size () < 4)::true" << std::endl;
		return false;
	}
	
	// read the ELF fields and save them
	// in the appropriate class fields
	offset = 0;
	//offset_section = 0;
	
	// e_ident[EI_MAG]
	// the magic number
	hdr.id_sign.data = data.substr (offset, 4);
	hdr.id_sign.offset = offset;
	//std::cerr << "debug::noware::elf::header::ELF=" << "[" << hdr.id_sign.data << "]" << std::endl;
	offset += 4;
	
	// e_ident[EI_CLASS]
	// the processing architecture's number of bits
	hdr.id_class.data = data.substr (offset, 1);
	hdr.id_class.offset = offset;
	offset += 1;
	
	// save the architecture bit count
	//x64 = hdr.id_class.data [1] == 0x2;
	x64 = str_int (hdr.id_class.data, true) == 0x2;
	
	// e_ident[EI_DATA]
	// the endianness
	hdr.id_data.data = data.substr (offset, 1);
	hdr.id_data.offset = offset;
	offset += 1;
	
	// e_ident[EI_VERSION]
	// the version of the ELF
	hdr.id_version.data = data.substr (offset, 1);
	hdr.id_version.offset = offset;
	offset += 1;
	
	// e_ident[EI_OSABI]
	// the target OS ABI
	hdr.id_osabi.data = data.substr (offset, 1);
	hdr.id_osabi.offset = offset;
	offset += 1;
	
	// e_ident[EI_ABIVERSION]
	// the ABI version
	hdr.id_abiversion.data = data.substr (offset, 1);
	hdr.id_abiversion.offset = offset;
	offset += 1;
	
	// e_ident[EI_PAD]
	// unused
	hdr.id_pad.data = data.substr (offset, 7);
	hdr.id_pad.offset = offset;
	offset += 7;
	
	// e_type
	hdr.type.data = data.substr (offset, 2);
	hdr.type.offset = offset;
	offset += 2;
	
	// e_machine
	hdr.mach.data = data.substr (offset, 2);
	hdr.mach.offset = offset;
	offset += 2;
	
	// e_version
	hdr.version.data = data.substr (offset, 4);
	hdr.version.offset = offset;
	offset += 4;
	
	if (x64)
	{
		std::cerr << "debug::noware::elf::load::(x64)::true" << std::endl;
		
		// e_entry
		// the entry point of the program
		hdr.entry.data = data.substr (offset, 8);
		hdr.entry.offset = offset;
		offset += 8;
		
		// e_phoff
		// the program header table location
		hdr.phoff.data = data.substr (offset, 8);
		hdr.phoff.offset = offset;
		std::cerr << "debug::noware::elf::load::e_phoff=" << "[" << offset << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::e_phoff.value=" << "[" << str_int (hdr.phoff.data, true) << "]" << std::endl;
		offset += 8;
		
		// e_shoff
		// the section header table location
		hdr.shoff.data = data.substr (offset, 8);
		/*
		hdr.shoff.data = std::string (1, char (0x58));
		hdr.shoff.data += std::string (1, char (0xC6));
		hdr.shoff.data += std::string (1, char (0x1F));
		hdr.shoff.data += std::string (1, char (0x00));
		hdr.shoff.data += std::string (1, char (0x00));
		hdr.shoff.data += std::string (1, char (0x00));
		hdr.shoff.data += std::string (1, char (0x00));
		hdr.shoff.data += std::string (1, char (0x00));
		*/
		hdr.shoff.offset = offset;
		/*
		std::cerr << "debug::noware::elf::load::e_shoff=" << "[" << offset << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::hdr.shoff.data=" << "[" << hdr.shoff.data << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::hdr.shoff.data[1]=" << "[" << ((unsigned long int) (hdr.shoff.data [1])) << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::data[offset+1]=" << "[" << ((unsigned long int) (data [offset + 1])) << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::e_shoff.value=" << "[" << str_int (hdr.shoff.data, true) << "]" << std::endl;
		*/
		offset += 8;
		
		// e_flags
		hdr.flag.data = data.substr (offset, 4);
		hdr.flag.offset = offset;
		offset += 4;
	}
	else
	{
		std::cerr << "debug::noware::elf::load::(x64)::false" << std::endl;
		
		return false;
	}
	
	// e_ehsize
	hdr.ehsize.data = data.substr (offset, 2);
	hdr.ehsize.offset = offset;
	offset += 2;
	
	// e_phentsize
	hdr.phentsize.data = data.substr (offset, 2);
	hdr.phentsize.offset = offset;
	offset += 2;
	
	// e_phnum
	hdr.phnum.data = data.substr (offset, 2);
	hdr.phnum.offset = offset;
	offset += 2;
	
	// e_shentsize
	hdr.shentsize.data = data.substr (offset, 2);
	hdr.shentsize.offset = offset;
	offset += 2;
	
	// e_shnum
	hdr.shnum.data = data.substr (offset, 2);
	hdr.shnum.offset = offset;
	offset += 2;
	
	// e_shstrndx
	hdr.shstrndx.data = data.substr (offset, 2);
	hdr.shstrndx.offset = offset;
	offset += 2;
	
	
	if (!x64)
	{
		std::cerr << "debug::noware::elf::load::(!x64)::true" << std::endl;
		
		return false;
	}
	
	// now, the section header table
	offset = str_int (hdr.shoff.data, true);
	e_shnum = str_int (hdr.shnum.data, true);
	
	std::cerr << "debug::noware::elf::load::shoff==" << "[" << offset << "]" << std::endl;
	std::cerr << std::dec;
	std::cerr << "debug::noware::elf::load::shnum==" << "[" << e_shnum << "]" << std::endl;
	std::cerr << std::hex;
	
	for (unsigned long int i = 0; i < e_shnum; ++i)
	{
		// sh_name
		sect [i].name.data = data.substr (offset, 4);
		sect [i].name.offset = offset;
		offset += 4;
		
		// sh_type
		sect [i].type.data = data.substr (offset, 4);
		sect [i].type.offset = offset;
		offset += 4;
		
		// sh_flags
		sect [i].flag.data = data.substr (offset, 8);
		sect [i].flag.offset = offset;
		offset += 8;
		
		// sh_addr
		sect [i].addr.data = data.substr (offset, 8);
		sect [i].addr.offset = offset;
		offset += 8;
		
		// sh_offset
		sect [i].offset.data = data.substr (offset, 8);
		sect [i].offset.offset = offset;
		offset += 8;
		
		// sh_size
		sect [i].size.data = data.substr (offset, 8);
		sect [i].size.offset = offset;
		offset += 8;
		
		// sh_link
		sect [i].link.data = data.substr (offset, 4);
		sect [i].link.offset = offset;
		offset += 4;
		
		// sh_info
		sect [i].info.data = data.substr (offset, 4);
		sect [i].info.offset = offset;
		offset += 4;
		
		// sh_addralign
		sect [i].addralign.data = data.substr (offset, 8);
		sect [i].addralign.offset = offset;
		offset += 8;
		
		// sh_entsize
		sect [i].entsize.data = data.substr (offset, 8);
		sect [i].entsize.offset = offset;
		offset += 8;
		
		// the actual section
		// which is referred by this header entry
		offset_section = str_int (sect [i].offset.data, true);
		section_size = str_int (sect [i].size.data, true);
		sect [i].data.offset = offset_section;
		sect [i].data.data = data.substr (offset_section, section_size);
		std::cerr << "debug::noware::elf::load::sect[" << i << "]::offset[" << offset_section << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::sect[" << i << "]::size[" << section_size << "]" << std::endl;
	}
	
	// now, the program header table
	offset = str_int (hdr.phoff.data, true);
	e_phnum = str_int (hdr.phnum.data, true);
	
	std::cerr << "debug::noware::elf::load::phoff==" << "[" << offset << "]" << std::endl;
	std::cerr << std::dec;
	std::cerr << "debug::noware::elf::load::phnum==" << "[" << e_phnum << "]" << std::endl;
	std::cerr << std::hex;
	
	for (unsigned long int i = 0; i < e_phnum; ++i)
	{
		//std::cerr << "debug::noware::elf::load::e_phnum==" << "[" << i << "]" << std::endl;
		
		// p_type
		prog [i].type.data = data.substr (offset, 4);
		prog [i].type.offset = offset;
		offset += 4;
		
		// p_flags
		prog [i].flag.data = data.substr (offset, 4);
		prog [i].flag.offset = offset;
		offset += 4;
		
		// p_offset
		prog [i].offset.data = data.substr (offset, 8);
		prog [i].offset.offset = offset;
		offset += 8;
		
		// p_vaddr
		prog [i].vaddr.data = data.substr (offset, 8);
		prog [i].vaddr.offset = offset;
		offset += 8;
		
		// p_paddr
		prog [i].paddr.data = data.substr (offset, 8);
		prog [i].paddr.offset = offset;
		offset += 8;
		
		// p_filesz
		prog [i].filesz.data = data.substr (offset, 8);
		prog [i].filesz.offset = offset;
		offset += 8;
		
		// p_memsz
		prog [i].memsz.data = data.substr (offset, 8);
		prog [i].memsz.offset = offset;
		offset += 8;
		
		// p_align
		prog [i].align.data = data.substr (offset, 8);
		prog [i].align.offset = offset;
		//std::cerr << "debug::noware::elf::load::p_align==" << "[" << str_int (prog [i].align.data, true) << "]" << std::endl;
		offset += 8;
		
		// the actual segment
		// which is referred by this header entry
		offset_segment = str_int (prog [i].offset.data, true);
		segment_size = str_int (prog [i].filesz.data, true);
		prog [i].data.offset = offset_segment;
		prog [i].data.data = data.substr (offset_segment, segment_size);
		std::cerr << "debug::noware::elf::load::prog[" << i << "]::offset[" << offset_segment << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::prog[" << i << "]::size[" << segment_size << "]" << std::endl;
		
		/*
		//std::cerr << "debug::noware::elf::load::prog[" << i << "]::vaddr.data[" << prog [i].vaddr.data << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::prog[" << i << "]::vaddr.data[";
		std::cerr << "h";
		//std::cerr << std::dec;
		std::cerr << std::noshowbase;
		for (unsigned int ndx = prog [i].vaddr.data.size () - 1; ndx > 0; --ndx)
		{
			std::cerr << ",";
			std::cerr << ((unsigned int) (prog [i].vaddr.data [ndx]));
		}
		std::cerr << ",";
		std::cerr << ((unsigned int) (prog [i].vaddr.data [0]));
		std::cerr << "]";
		std::cerr << std::endl;
		//std::cerr << std::hex;

		std::cerr << "debug::noware::elf::load::prog[" << i << "]::memsz.data[";
		std::cerr << "h";
		//std::cerr << std::dec;
		std::cerr << std::noshowbase;
		for (unsigned int ndx = prog [i].memsz.data.size () - 1; ndx > 0; --ndx)
		{
			std::cerr << ",";
			std::cerr << ((unsigned int) (prog [i].memsz.data [ndx]));
		}
		std::cerr << ",";
		std::cerr << ((unsigned int) (prog [i].memsz.data [0]));
		std::cerr << "]";
		std::cerr << std::endl;
		//std::cerr << std::hex;
		
		std::cerr << std::showbase;
		*/
		
		std::cerr << "debug::noware::elf::load::prog[" << i << "]::vaddr.data.size[" << prog [i].vaddr.data.size () << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::prog[" << i << "]::vaddr[" << str_int (prog [i].vaddr.data, true) << "]" << std::endl;
		std::cerr << "debug::noware::elf::load::prog[" << i << "]::memsz[" << str_int (prog [i].memsz.data, true) << "]" << std::endl;
	}
	
	return true;
}

const noware::unsigned_string noware::elf::read (const std::string & file_name)
{
	std::ifstream file;
	std::streampos size;
	unsigned char * data;
	noware::unsigned_string value;
	
	file.open (file_name, std::ios::in | std::ios::binary | std::ios::ate);
	
	if (!file.is_open ())
		return ((unsigned char *) (""));
	
	size = file.tellg ();
	file.seekg (0, std::ios::beg);
	data = new unsigned char [size];
	file.read (data, size);
	file.close ();
	
	value = noware::unsigned_string (data, size);
	//std::cerr << std::hex;
	//std::cerr << "debug::noware::elf::read::data[0x29]=" << "[" << ((unsigned long int) (data [0x29])) << "]" << std::endl;
	//std::cerr << "debug::noware::elf::read::value[0x29]=" << "[" << ((unsigned long int) (value [0x29])) << "]" << std::endl;
	delete [] data;
	return value;
}

const unsigned long int noware::elf::str_int (const noware::unsigned_string & data, const bool & swap)
{
	unsigned long int value;
	unsigned long int size;
	std::stringstream ss;
	
	//val = 0;
	size = data.size ();
	ss << std::hex;
	//ss << std::showbase;
	//ss << std::noshowbase;
	//ss << std::setw (2);
	//ss << std::setfill ('0');
	
	if (swap)
	{
		for (unsigned long int ndx = size - 1; ndx > 0; --ndx)
		{
			//std::cerr << "ndx:" << ndx << std::endl;
			//std::cerr << "(data[" << ndx << "]):" << (data [ndx]) << std::endl;
			//std::cerr << "((unsigned int) (data[" << ndx << "])):" << ((unsigned int) (data [ndx])) << std::endl;
			ss << std::setw (2) << std::setfill ('0') << ((unsigned int) (data [ndx]));
		}
		//std::cerr << "ndx:" << 0 << std::endl;
		//std::cerr << "(data[" << 0 << "]):" << (data [0]) << std::endl;
		//std::cerr << "((unsigned int) (data[" << 0 << "])):" << ((unsigned int) (data [0])) << std::endl;
		ss << std::setw (2) << std::setfill ('0') << ((unsigned int) (data [0]));
	}
	else
	{
		for (unsigned long int ndx = 0; ndx < size; ++ndx)
		{
			//std::cerr << "ndx:" << ndx << std::endl;
			ss << std::setw (2) << std::setfill ('0') << ((unsigned int) (data [ndx]));
		}
	}
	
	ss >> value;
	
	return value;
}
/*
const bool noware::elf::loaded (void) const
{
	return _loaded;
}

const bool noware::elf::clear (void)
{
	return false;
}
*/