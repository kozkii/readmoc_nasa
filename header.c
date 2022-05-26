/*
NOTICE

The software accompanying this notice (the "Software") is provided to you
free of charge to facilitate your use of the data collected by the Mars
Orbiter Camera (the "MOC Data").  Malin Space Science Systems ("MSSS")
grants to you (either as an individual or entity) a personal,
non-transferable, and non-exclusive right (i) to use and reproduce the
Software solely for the purpose of accessing the MOC Data; (ii) to modify
the source code of the Software as necessary to maintain or adapt the
Software to run on alternate computer platforms; and (iii) to compile, use
and reproduce the modified versions of the Software solely for the purpose
of accessing the MOC Data.  In addition, you may distribute the Software,
including any modifications thereof, solely for use with the MOC Data,
provided that (i) you must include this notice with all copies of the
Software to be distributed; (ii) you may not remove or alter any
proprietary notices contained in the Software; (iii) you may not charge any
third party for the Software; and (iv) you will not export the Software
without the appropriate United States and foreign government licenses.  

You acknowledge that no title to the intellectual property in the Software
is transferred to you.  You further acknowledge that title and full
ownership rights to the Software will remain the exclusive property of MSSS
or its suppliers, and you will not acquire any rights to the Software
except as expressly set forth above.  The Software is provided to you AS
IS.  MSSS MAKES NO WARRANTY, EXPRESS OR IMPLIED, WITH RESPECT TO THE
SOFTWARE, AND SPECIFICALLY DISCLAIMS THE IMPLIED WARRANTIES OF
NON-INFRINGEMENT OF THIRD PARTY RIGHTS, MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE.  SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OR
LIMITATION OF INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO SUCH LIMITATIONS OR
EXCLUSIONS MAY NOT APPLY TO YOU.  

Your use or reproduction of the Software constitutes your agreement to the
terms of this Notice.  If you do not agree with the terms of this notice,
promptly return or destroy all copies of the Software in your possession.  

Copyright (C) 1999 Malin Space Science Systems.  All Rights Reserved.
*/
static char *sccsid = "@(#)header.c	1.2 10/06/99";
#include <stdio.h>
#include "image_io.h"

int prefix(s, pre)
char *s, *pre;
{
    return strncmp(s, pre, strlen(pre)) == 0;
}

/* write the image header and return the file descriptor to the open file */
int write_header(width, height, infile, outfname)
FILE *infile;
char *outfname;
{
    static int out = -1;
    int pos;
    FILE *outf;
    char line[256];
    int nrec;
    int i, pad;

    if(out < 0) {
	if((out = creat(outfname, 0666)) < 0) {
	    fprintf(stderr, "can't create %s\n", outfname);
	    exit(1);
	}
    }
    lseek(out, 0l, 0);
    outf = fdopen(dup(out), "r+");

    nrec = 2048/width+(2048%width?1:0);
    
    /* copy the PDS header with a few modifications */
    pos = ftell(infile);
    fseek(infile, 0, 0);
    while(fgets(line, sizeof(line), infile)) {
	if(prefix(line, "RECORD_BYTES")) {
	    fprintf(outf, "RECORD_BYTES = %d\r\n", width);
	}
	else if(prefix(line, "FILE_RECORDS")) {
	    fprintf(outf, "FILE_RECORDS = %d\r\n", height+nrec);
	}
	else if(prefix(line, "^IMAGE")) {
	    fprintf(outf, "^IMAGE = %d\r\n", nrec+1);
	}
	else if(prefix(line, "LABEL_RECORDS")) {
	    fprintf(outf, "LABEL_RECORDS = %d\r\n", nrec);
	}
	else if(prefix(line, "ENCODING_TYPE")) {
	    ; /* skip this in output */
	}
	else if(prefix(line, "FILE_NAME")) {
	    fprintf(outf, "FILE_NAME = \"%s\"\r\n", outfname);
	}
	else if(prefix(line, "LINES")) {
	    fprintf(outf, "LINES = %d\r\n", height);
	}
	else if(prefix(line, "END\r")) {
	    fputs(line, outf);
	    break;
	}
	else {
	    fputs(line, outf);
	}
    }
    pad = nrec*width-ftell(outf);
    if(pad < 0) {
	fprintf(stderr, "Error: header too large\n");
	exit(1);
    }
    
    for(i = 0; i < pad; i++) fputc(' ', outf);

    fclose(outf);
    lseek(out, nrec*width, 0);
    fseek(infile, pos, 0);
    return out;
}    
