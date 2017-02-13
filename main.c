/*
    Bintoh - Binary to c header file converter
    Rodrigo Feliciano - 08/02/2017
*/
#include <stdio.h>

#define MAX_FILE_SIZE   524288  /* bytes */

int main(int argc, char *argv[]) {
    FILE *infile;   /* Binary file - input */
    FILE *outfile;  /* Header file - output */
    int chrin = 0;  /* Temp char input */
    int bytecount = 0;
    int i = 0;
    
    if(argc == 4)
    {
        infile = fopen(argv[2],"rb");   /* open input file for binary read */
    
        if(infile == 0)
        {
            printf("\n\nInput file error...\n\n");    /* No file... */
        }else
        {
            fseek(infile, 0L, SEEK_END);
            bytecount = ftell(infile);      /* Get the number of bytes in the file */
            rewind(infile);
            
            if(bytecount <= MAX_FILE_SIZE)
            {
                outfile = fopen(argv[3],"w");   /* Open the output file for write */
                
                if(outfile == 0)
                {
                    printf("Output file error...");
                }else
                {
                    fprintf(outfile,"/* Bintoh - Bin to Header file converter */\n");
                    fprintf(outfile,"\n#ifndef %s_H_",argv[1]);
                    fprintf(outfile,"\n#define %s_H_\n",argv[1]);
                    fprintf(outfile,"\n#define    FTABLE_SIZE    %i",bytecount);
                
                    fprintf(outfile,"\n\nconst unsigned char %s[%i] = \n{\n",argv[1],bytecount);
                
                    while((chrin = fgetc(infile)) != EOF)
                    {
                        if(i >= 7)  /* Number of items in a row - 1 */
                        {
                            fprintf(outfile,"0x%02x,\n",chrin); /* Last item in a row */
                            i=0;
                        }else if(i == 0)
                        {
                            fprintf(outfile,"    0x%02x,",chrin);   /* first item in a row */
                            i++;
                        }else
                        {
                            fprintf(outfile,"0x%02x,",chrin);   /* item in a row */
                            i++;
                        }
                    }
                
                    fprintf(outfile,"};\n\n\n#endif /* %s_H_ */",argv[1]);
                    fclose(outfile);
                }
            }else
            {
                printf("\nInput file too big!");
                printf("\nMaximum file size: %i bytes",MAX_FILE_SIZE);
                printf("\nInput file size: %i bytes\n\n",bytecount);
            }
            fclose(infile);
        }
    }else
    {
        printf("\nCreate a C Header file from a binary file\n");
        printf("\nusage: bintoh [table_name] [input_filename] [output_filename]\n\n");
    }
    
    return 0;
}
