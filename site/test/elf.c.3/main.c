#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[], char *envp[])
{
	//int (*ptr)(int, char *[], char *[]);
	int fd;
	void *addr;
	unsigned char buff [2084696/* File size*/];
	char addr_str [8 + 1];
	char jmp_str [8 + 4 + 1];
	
	if (argc < 2)
	{
		fprintf (stderr, "%s <file>\n", argv [0]);
		
		return EXIT_FAILURE;
	}
	
	// Open the file.
	fd = open (argv [1], O_RDONLY);
	// Verify that it is open.
	assert (fd > 0);
	
	// Read the first LOAD directive.
	assert (read (fd, buff, 2084696) == 2084696);
	
	// Close the file.
	assert (close (fd) == 0);
	
	// Reserve/Allocate a RAM region from the OS.
	addr1 = mmap (NULL, 2084696, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
	assert (addr != MAP_FAILED);
	
	printf ("addr[%x]\n", addr);
	
	// Copy the contents of the buffers into the newly allocated memory.
	memcpy (addr/* Destination*/, buff/* Source*/, 2084696/* Size (bytes)*/);
	
	
	// Jump to the entry point.
	//ptr = 0x400d70;
	//asm ("ldr r0, =0x400d70");
	//asm ("blx r0");
	//asm ("movl $0x400d70, .");
	//asm ("jmp 0x400d70");
	
	/*
	snprintf (addr_str, 9, "0x%x", addr + 0x400d70);
	printf ("addr[0x%x] + 0x%x = addr_str[%s]\n", addr, 0x400d70, addr_str);
	
	strcpy (jmp_str, "jmp ");
	strcat (jmp_str, addr_str);
	
	printf ("jmp_str[%s]\n", jmp_str);
	asm (jmp_str);
	*/
	
	return EXIT_SUCCESS;
}
