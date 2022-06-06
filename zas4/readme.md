# Hi-Tech Zas

The files in this repository are my attempts at decompiling the Ms-Dos version of the Hi-Tech version 4.11 ZAS.EXE tool and porting it to work on a 32/64 bit OS. It is known to compile using Visual studio 2022 and with GCC 10.2, although it should work on other versions of both compilers providing they support C11 or later.

Much of the work is based on the previous decompilation of the CP/M-80 ZAS.COM version 3.09. 

Based on my decompilation efforts it is clear that the assembler was in a state of transition and although it fixed some bugs, it introduced others, including some in the new functionality it added. There are also several unused functions and functionality, likely from an 8086 assembler using shared code.

I have corrected the bugs that I could identify, although some certainly remain, including those introduced as part of my decompilation effort. If you spot any please contact me and I will aim to fix them.

Some of the main changes I spotted are

## New functionality

Macro processing added support LOCAL. Note auto generated labels have the format ??nnnn, where n is a digit. I would strongly recommend you don't use this format for your own labels. See also bug fixes.

REPT, IRP and IRPC support has been added.

Macro arguments now allow ''!'' to escape the next character

Macro body allows ''&'' to join expanded arguments.

Macro body allows ''%'' to expand argument as a number

IF ELSE ENDIF support added.

LINE and FILE support added

Paging functionality was added, however it could not be used.

I added support in DEFB for simple strings, but note single character strings are still handled as an integer, allowing expressions such as 'A' + 20h.



## Bugs fixes

- The ENDC/ENDM bugs from version 3.09 were fixed in 4.11- there were missing breaks in a switch.
- LOCAL, the auto generated label number was not reset between passes, leading to errors of unknown labels. This has been fixed.
- The test for more arguments for IRP only checked the low byte of the string pointer. It now checks for full pointer.
- Processing of nested macro arguments using < and >, was broken. An uninitialised variable was used, the opening < of nested arguments were removed and the ! escape character was removed  within nested arguments. The uninitialised variable also caused ''!'' to junk the intended escaped character and to escape the one following it. These have now been fixed.
- Paging now works. There is a new -p option which takes the form -p0 or -pnum, where num is >= 15, to support paging. -p0 turns off all paging, including the spurious paging the original added at the start of the symbols. -pnum sets the page length to num, if the -p option isn't used the page length is set to 66.
- DEFF gave a warning for overflow, but didn't check underflow, which could lead to very large negative numbers being used. A check for underflow is now included and both overflow and underflow give an error message and set the number to 0.0.
- The symbol table did not reflect the size of areas like bss as the size wasn't updated as new DEFS pseudo ops were used. It now does.
- The expression evaluation function "binary", had an incorrect test for relocation error for operators that do not support relocatable values. Specifically it tested the left hand side twice rather than left and right hand sides. This is now fixed.
- Although the "jr"opcode correctly checked for the -126 to + 129 jump range, it then used the "djnz" shared code which checked the jump range -128 to +128. This is now fixed.

```
Mark Ogden last updated 6-Jun-2022
```

