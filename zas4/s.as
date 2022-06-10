        psect data
buf:    defs   20
recptr: defs 2
        psect text

first   defl    1

        sbmac macro var
            ld a,var
            call subr
            if first
first defl 0
            jp skipsubr
        subr:
            inc a
            ret
        skipsubr:
            endc
            endm

        sbmac   10
        sbmac   b

        m127:
            defs 127
            djnz m127
        m126:
            defs 126
            djnz m126
            djnz p129
            defs 127
        p129:
            djnz p130
            defs 128
        p130:


        copy MACRO source,dest,count 
            LOCAL nocopy 
            push af 
            push bc 
            ld bc,source 
            ld a,b 
            or c 
            jr z,nocopy 
            push de 
            push hl 
            ld de,dest 
            ld hl,source 
            ldir 
            pop hl 
            pop de 
    nocopy: pop bc 
            pop af 
        ENDM

        copy (recptr),buf,20

        IRP string,<'hello world',13,10>,'arg2' 
            LOCAL str 
            psect data 
    str:    defb string,'$' 
            psect text 
            ld c,9 
            ld de,str 
            call 5 
        ENDM 

        IRPC char,ABC 
            ld c,2 
            ld e,'char' 
            call 5 
        ENDM 

        REPT 3 
            ld (hl),0 
            inc hl 
        ENDM


        complex macro irparg
            irp string,irparg
            psect data
            defb string
            endm
        endm

        complex <<'hello world',13,10>,'arg2'>
        end


