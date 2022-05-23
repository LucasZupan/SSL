Conversion: Conversion.o ConversionTest.o
	gcc Conversion.o ConversionTest.o -o Conversion

TablasDeConversion: Conversion.o TablasDeConversion.o FuncionesPrint.o
	gcc Conversion.o TablasDeConversion.o FuncionesPrint.o -o TablasDeConversion

TablasDeConversion.o: TablasDeConversion.c Conversion.h
	gcc -c TablasDeConversion.c -std=c18

Conversion.o: Conversion.c Conversion.h
	gcc -c Conversion.c -std=c18

ConversionTest.o: ConversionTest.c Conversion.h
	gcc -c ConversionTest.c -std=c18

FuncionesPrint.o: FuncionesPrint.c FuncionesPrint.h Conversion.h
	gcc -c FuncionesPrint.c -std=c18

.PHONY: clean
clean: 
	DEL *.o Conversion.exe TablasDeConversion.exe