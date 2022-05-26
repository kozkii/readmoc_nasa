# readmoc mirror

General usage: > readmoc xx0202.imq xx0202.img

readmoc will decompress a MOC SDP image and format it into a
decompressed PDS image file with PDS labels and an image object.

The readmoc executable was generated for a Windows 95 system using
Microsoft Visual C++ 4.0.  It was also tested under Windows 98.

To extract the source and compile it, use the following commands:

1) unzip readmoc.zip

2) run Visual C++, define a new console application, load all of the
.c and .h files into the project, add the Binmode.obj file from
msdev\lib to force binary file I/O, and do a build.

Then open a MS/DOS window and run readmoc on the command line.
The program takes two command-line arguments:

   readmoc input-file output-file

There are no other options.

For images that were predictively compressed and then suffered
uncorrectable memory loss buffer errors and/or downlink data loss, 
the error messages

"lost sync, line <number> -- restart at <hex number>"

or

"lost sync, line <number> -- aborting"

may be encountered.  This message indicates that the program is trying
to resynchronize to the compressed bit stream, and that the loss of
sync was first noticed at the given line number.  Depending on the
success of the resynchronization algorithm, there may or may not be
valid image data after that line.

In the case of uncorrectable buffer errors causing this error message,
the DATA_QUALITY_DESC field in the imgindex.tab file may still have a
value of OK, as these errors cannot be easily detected without
decompressing the data.  Conversely, errors other than the one
described above may have been detected during the processing of an
image leading to a DATA_QUALITY_DESC value of ERRORS.


Updates and fixes to the code may be found at the MSSS Web site at
"www.msss.com/mocsoft/".  

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
