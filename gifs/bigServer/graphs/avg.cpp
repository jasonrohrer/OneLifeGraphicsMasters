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
    float runningSumC = 0;
    float runningSumPer = 0;
    
    float cValues[500];
    float perValues[500];
    

    int v;
    
    while( numRead == 4 ) {
        numRead = fscanf( inFile, "%d %d %f %f", &i, &p, &c, &per );
        
        if( numRead == 4 ) {
            
            cValues[v] = c;
            perValues[v] = per;
            
            if( numRead == 4 ) {
                runningSumC += c;
                runningSumPer += per;
                if( v >= n ) {
                    runningSumC -= cValues[v-n];
                    runningSumPer -= perValues[v-n];
                    }
                
                fprintf( outFile, "%d %d %f %f %f %f\n", 
                         i, p, c, per, 
                         runningSumC / n,
                         runningSumPer / n );
                }
            v++;
            }
        }
    
    fclose( inFile );
    fclose( outFile );

    }
