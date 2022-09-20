# Hi-Tech C cref utility

Decompilation by Mark Ogden, added to  Nikitin Andrey's github site as part of the port of the Hi-Tech C v3.09 tool chain

## Notes

The usage message in the original utility is incorrect, the correct usage is

        cref [switches] [inputfile]+
        
    Where the supported, case insensitive switches are
      -Htext      output header, default is the name of the first inputfile
    			  the c driver uses the outputfile.crf
      -Lnum       set page length to given number, default 66
      -Ofile      sets the output file, if not specified or file == “” then output to stdout
      -P          set page width to given number default 80
      -Xprefix    sets an exclude prefix, note upto 30 can be defined
      -Sfile      reads a stop list from the specified file
    
    Added switch (see below)
      -I		  include references from .h files		

The following minor changed have been incorporated

1) The original set the max field width based on both the token and the file path. This gave very large widths when long filename paths were encountered.
This was probably a bug in the original, masked by the short CP/M filenames. This is now fixed.
2) Function prototypes in include files causes lots of references to unused functions in the cref output. This has been modified to omit such references in .h files by default . In general this also avoids wide file definition columns.
3) There is a new switch -I to include the references from .h files if needed

Note the CP/M version of p1 doesn’t produce any cross reference information under zxcc or the altair simh emulator, possibly due to a missing close to flush the file. The ported version does however work. An explicit close has also been added to the p1 decompilation code.

```
Updated by Mark Ogden 25-Aug-2022
```
