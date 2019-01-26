#include <stdio.h>

int main( int inNumArgs, char **inArgs ) {
    
    if( inNumArgs != 3 ) {
        printf( "Needs two args\n" );
        return 1;
        }
    
    FILE *inFile = fopen( inArgs[1], "r" );
    
    FILE *outFile = fopen( inArgs[2], "w" );
    
    int i, p;
    float c, per;
    
    int numRead = 4;


    int n = 4;
    float runningSum = 0;
    
    float cValues[500];
    

    int v;
    
    while( numRead == 4 ) {
        numRead = fscanf( inFile, "%d %d %f %f", &i, &p, &c, &per );
        
        if( numRead == 4 ) {
            
            cValues[v] = c;
            
            if( numRead == 4 ) {
                runningSum += c;
                if( v >= n ) {
                    runningSum -= cValues[v-n];
                    }
                
                fprintf( outFile, "%d %d %f %f %f\n", 
                         i, p, c, per, runningSum / n );
                }
            v++;
            }
        }
    
    fclose( inFile );
    fclose( outFile );

    }
