	use main.c and makefile to generate sha3 code, then run main.o which is generated by ./make:

	main.c generates the sha3 codes for v1-v3
	main_v4.c generates the sha3 codes for v4
	
	in main.c : Define the raw data source by changing change file name in the line 23
				Change sha3 output bit by editing width number in the line 26 (e.g. #define OUTLEN 12);
				Change output file name in line 27 (e.g. #define FILENAME_OUTPUT "output_shake_12.dat")
		
Collision analizing tool (in python language) and result reports are put in associated folder
