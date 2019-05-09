
#include "syllablesLength.cpp"

#include "startingConsonantClusters.cpp"
#include "endingConsonantClusters.cpp"
#include "vowelClusters.cpp"
#include "middleConsonantClusters.cpp"

#include <limits.h>

#define NUM_CLUSTER_SETS 4

#define START_I 0
#define END_I 1
#define VOWEL_I 2
#define MID_I 3


const int allClusterSizes[ NUM_CLUSTER_SETS ] = 
{ NUM_STARTING_CONSONANT_CLUSTERS,
  NUM_ENDING_CONSONANT_CLUSTERS,
  NUM_VOWEL_CLUSTERS,
  NUM_MIDDLE_CONSONANT_CLUSTERS };


const char **allClusters[ NUM_CLUSTER_SETS ] = 
{ startingConsonantClusters,
  endingConsonantClusters,
  vowelClusters,
  middleConsonantClusters };


typedef struct ClusterIndex {
        int setIndex;
        int index;
    } ClusterIndex;


const char *startingMapping[ NUM_STARTING_CONSONANT_CLUSTERS ];
const char *endingMapping[ NUM_ENDING_CONSONANT_CLUSTERS ];
const char *vowelMapping[ NUM_VOWEL_CLUSTERS ];
const char *middleMapping[ NUM_MIDDLE_CONSONANT_CLUSTERS ];


const char **allMappings[ NUM_CLUSTER_SETS ] = { startingMapping,
                                                 endingMapping,
                                                 vowelMapping,
                                                 middleMapping };


const char *startingBackMapping[ NUM_STARTING_CONSONANT_CLUSTERS ];
const char *endingBackMapping[ NUM_ENDING_CONSONANT_CLUSTERS ];
const char *vowelBackMapping[ NUM_VOWEL_CLUSTERS ];
const char *middleBackMapping[ NUM_MIDDLE_CONSONANT_CLUSTERS ];

const char **allBackMappings[ NUM_CLUSTER_SETS ] = { startingBackMapping,
                                                     endingBackMapping,
                                                     vowelBackMapping,
                                                     middleBackMapping };







#include "minorGems/util/SimpleVector.h"
#include "minorGems/util/stringUtils.h"
#include "minorGems/util/random/CustomRandomSource.h"

#include <string.h>


#define NUM_VOWELS 6

const char vowels[ NUM_VOWELS ] = { 'a', 'e', 'i', 'o', 'u', 'y' };







static char isVowelStart( const char *inSyllable, char inAllowY = false ) {
    // y not vowel at start
    int limit = NUM_VOWELS - 1;
    
    if( inAllowY ) {
        limit ++;
        }

    for( int i=0; i<limit; i++ ) {
        if( inSyllable[0] == vowels[i] ) {
            return true;
            }
        }
    return false;
    }



static char isVowelEnd( const char *inSyllable ) {
    // y IS a vowel at end
    int lastIndex = strlen( inSyllable ) - 1;
    
    for( int i=0; i<NUM_VOWELS; i++ ) {
        if( inSyllable[lastIndex] == vowels[i] ) {
            return true;
            }
        }
    return false;
    }



// Fisher–Yates shuffle
/*
  -- To shuffle an array a of n elements (indices 0..n-1):
  for i from n−1 downto 1 do
      j ← random integer such that 0 ≤ j ≤ i
      exchange a[j] and a[i]
*/        
CustomRandomSource randSource( 12483 );

void shuffle( SimpleVector<int> *inIndexList ) {
    int len = inIndexList->size();
    
    for( int i=len-1; i >= 1; i-- ) {
        int j = randSource.getRandomBoundedInt( 0, i );
        
        // swap
        int temp = inIndexList->getElementDirect( i );
        *( inIndexList->getElement( i ) ) = inIndexList->getElementDirect( j );
        *( inIndexList->getElement( j ) ) = temp;
        }
    }


// self-reversing shuffle
// A maps to B and B maps to A
// pairs of indices switch places
void mirrorShuffle( SimpleVector<int> *inIndexList ) {
    int len = inIndexList->size();
    
    // indexes into inIndexList that haven't been swapped yet
    SimpleVector<int> spotsLeft;

    for( int i=0; i<len; i++ ) {
        spotsLeft.push_back( i );
        }
    
    // if odd, one spot remains unswapped
    int numPairs = len / 2;
    for( int p=0; p<numPairs; p++ ) {
        
        int aLoc = 
            randSource.getRandomBoundedInt( 0, spotsLeft.size() -1 );
        int indA = spotsLeft.getElementDirect( aLoc );
        
        spotsLeft.deleteElement( aLoc );
        
        
        int bLoc = 
            randSource.getRandomBoundedInt( 0, spotsLeft.size() -1 );
        int indB = spotsLeft.getElementDirect( bLoc );

        spotsLeft.deleteElement( bLoc );
        
        // swap A and B in main vector
        int temp = inIndexList->getElementDirect( indA );
        
        *( inIndexList->getElement( indA ) ) =
            inIndexList->getElementDirect( indB );
        
        *( inIndexList->getElement( indB ) ) = temp;
        }
    
    }




// self-reversing shuffle that keeps elements close
// to their original position in the list
// inCloseWindow defines how far apart they can get
void closeMirrorShuffle( SimpleVector<int> *inIndexList,
                         int inCloseWindow ) {

    int len = inIndexList->size();
    
    // indexes into inIndexList that haven't been swapped yet
    SimpleVector<int> spotsLeft;

    for( int i=0; i<len; i++ ) {
        spotsLeft.push_back( i );
        }
    
    // if odd, one spot remains unswapped
    int numPairs = len / 2;
    for( int p=0; p<numPairs; p++ ) {

        int aLoc = 0;
        int indA = spotsLeft.getElementDirect( aLoc );
        
        spotsLeft.deleteElement( aLoc );
        
        SimpleVector<int> closeBLoc;
        SimpleVector<int> closeBInd;
        
        int thisWindSize = inCloseWindow;
        if( thisWindSize > spotsLeft.size() ) {
            thisWindSize = spotsLeft.size();
            }

        int closeDist = 0;
        while( closeBLoc.size() < thisWindSize ) {
            int minLoc = -1;
            int minInd = -1;
            int minDist = INT_MAX;
            
            for( int m=0; m<spotsLeft.size(); m++ ) {
                
                int testInd = spotsLeft.getElementDirect( m );
                
                int dist = abs( testInd - indA );
                
                if( dist > closeDist && dist < minDist ) {
                    minLoc = m;
                    minInd = testInd;
                    minDist = dist;
                    }
                }

            if( minLoc == -1 ) {
                // none found
                printf( "Non found!\n" );
                break;
                }

            closeDist = minDist;
            closeBLoc.push_back( minLoc );
            closeBInd.push_back( minInd );
            }
        
        
        if( closeBInd.size() > 0 ) {
        
            int closePick = 
                randSource.getRandomBoundedInt( 0, closeBInd.size() -1 );
            int indB = closeBInd.getElementDirect( closePick );
            
            spotsLeft.deleteElement( 
                closeBLoc.getElementDirect( closePick ) );
        
            printf( "Swapping index %d with %d\n", indA, indB );
            

            // swap A and B in main vector
            int temp = inIndexList->getElementDirect( indA );
            
            *( inIndexList->getElement( indA ) ) =
                inIndexList->getElementDirect( indB );
            
            *( inIndexList->getElement( indB ) ) = temp;
            }
        }
    
    }






const char *syllableMapping[ NUM_SYLLABLES ];
    

static void mapByShuffle( SimpleVector<int> *inOrig,
                          SimpleVector<int> *inShuff ) {
                          
    for( int i=0; i<inShuff->size(); i++ ) {
        
        int source = inOrig->getElementDirect( i );
        int dest = inShuff->getElementDirect( i );
        
        syllableMapping[ source ] = syllablesByLengthList[ dest ];
        }
    }



const char *findMatchingSyllable( char *inPiece, char **outLoc,
                                  int *outIndex,
                                  const char *inSource[] ) {
    for( int i=0; i<NUM_SYLLABLES; i++ ) {
        char *loc = strstr( inPiece, inSource[ i ] );
        
        if( loc != NULL ) {
            *outLoc = loc;
            *outIndex = i;
            return inSource[ i ];
            }
        }
    return NULL;
    }



// result destroyed by caller
char *remapWord( char *inWord, 
                 const char *inSource[],
                 const char *inDest[] ) {
    SimpleVector<char *> pieces;
    
    pieces.push_back( stringDuplicate( inWord ) );
    
    SimpleVector<char> piecesDone;
    
    piecesDone.push_back( false );

    SimpleVector<int> pieceMapping;
    
    pieceMapping.push_back( -1 );
    
    char allPiecesDone = false;
    
    while( ! allPiecesDone ) {
        allPiecesDone = true;
        
        for( int p=0; p<pieces.size(); p++ ) {
            if( ! piecesDone.getElementDirect( p ) ) {
                allPiecesDone = false;

                char *piece = pieces.getElementDirect( p );
                
                char *matchLoc = NULL;
                int matchIndex = -1;
                
                const char *syl =
                    findMatchingSyllable( piece, &matchLoc, &matchIndex,
                                          inSource );
                
                if( syl == NULL ) {
                    // no match, nonsense syllable, mark as done
                    *( piecesDone.getElement( p ) ) = true;
                    }
                else {
                    // match
                    if( matchLoc == piece &&
                        strlen( syl ) == strlen( piece ) ) {
                        // exact match
                        *( piecesDone.getElement( p ) ) = true;
                        *( pieceMapping.getElement( p ) ) = matchIndex;
                        }
                    else {
                        // mid-piece match

                        pieces.deleteElement( p );
                        piecesDone.deleteElement( p );
                        pieceMapping.deleteElement( p );
                        
                        int insertLoc = p;

                        if( matchLoc != piece ) {
                            char *before = stringDuplicate( piece );
                            int beforeLen = matchLoc - piece;
                            before[ beforeLen ] = '\0';
                            pieces.push_middle( before, insertLoc );
                            piecesDone.push_middle( false, insertLoc );
                            pieceMapping.push_middle( -1, insertLoc );
                            insertLoc++;
                            }
                        pieces.push_middle( stringDuplicate( syl ),
                                            insertLoc );
                        // syllable is exact match, so done
                        piecesDone.push_middle( true, insertLoc );
                        pieceMapping.push_middle( matchIndex, insertLoc );
                        insertLoc++;
                        
                        if( matchLoc - piece + strlen( syl ) < 
                            strlen( piece ) ) {
                            
                            char *after = stringDuplicate(
                                &( matchLoc[ strlen( syl ) ] ) );
                            pieces.push_middle( after, insertLoc );
                            piecesDone.push_middle( false, insertLoc );
                            pieceMapping.push_middle( -1, insertLoc );
                            insertLoc++;
                            }
                        delete [] piece;
                        }
                    }
                }
            }
        }


    SimpleVector<char> together;
    
    for( int p=0; p<pieces.size(); p++ ) {
        char *piece = pieces.getElementDirect( p );
    
        const char *mappedPiece = piece;
        
        int map = pieceMapping.getElementDirect( p );
        
        if( map != -1 ) {
            mappedPiece = inDest[ map ];
            }

        together.appendElementString( mappedPiece );
        
        delete [] piece;
        }
    
    return together.getElementString();
    }



// returns pointer to remainder of word after cluster removed
// outClustIndex = -1 if none found
char *findInitialCluster( char *inWord,
                          int inNumSourceClusters,
                          const char *inSourceClusters[],
                          int *outClustIndex ) {
    
    for( int c=0; c<inNumSourceClusters; c++ ) {
            
        const char *clust = inSourceClusters[c];
            
        char *loc = strstr( inWord, clust );
            
        if( loc == inWord ) {
            // found at start;
            *outClustIndex = c;
                
            // skip it
            return &( inWord[ strlen( clust ) ] );
            }
        }

    *outClustIndex = -1;
    return inWord;
    }




char *remapWordNew( char *inWord, 
                    const char **inSourceClusters[ NUM_CLUSTER_SETS ],
                    const char **inDestClusters[ NUM_CLUSTER_SETS ] ) {
    
    char *wordWorkingOrig = stringDuplicate( inWord );

    char *wordWorking = wordWorkingOrig;
    

    // first, find start cons cluster, if there is one

    int startClusterIndex = -1;
    
    if( ! isVowelStart( wordWorking ) ) {
        wordWorking = findInitialCluster( wordWorking, 
                                          allClusterSizes[ START_I ],
                                          inSourceClusters[ START_I ],
                                          &startClusterIndex );
        }
    

    // now longest consonant end cluster
    int endClusterIndex = -1;
    
    int remainLen = strlen( wordWorking );

    for( int c=0; c<allClusterSizes[ END_I ]; c++ ) {
        
        const char *clust = inSourceClusters[ END_I ][c];
        
        char *loc = strstr( wordWorking, clust );
        
        if( loc != NULL &&
            strlen( clust ) ==
            ( remainLen - ( loc - wordWorking ) ) ) {
            
            // match, and at end of word
            endClusterIndex = c;
            
            // terminate here to skip it
            loc[0] = '\0';
            }
        }
    
    // now search middle for vowel and consonant clusters

    SimpleVector<ClusterIndex> middleClusterIndices;
    
    while( strlen( wordWorking ) > 0 ) {
        // some letters left
        
        int setIndex = -1;
        int midIndex = -1;
        
        if( isVowelStart( wordWorking, true ) ) {
            setIndex = VOWEL_I;
            }
        else {
            setIndex = MID_I;
            }
        
        wordWorking = findInitialCluster( wordWorking, 
                                          allClusterSizes[ setIndex ],
                                          inSourceClusters[ setIndex ],
                                          &midIndex );
            
        if( midIndex != -1 ) {
            ClusterIndex ci = { setIndex, midIndex };
            middleClusterIndices.push_back( ci );
            }
        else {
            // none found?
            printf( "No mid cluster found in remainder of word %s\n",
                    wordWorking );
            break;
            }
        }
    
    
    SimpleVector<char> mappedWord;
    
    if( startClusterIndex != -1 ) {
        mappedWord.appendElementString( 
            inDestClusters[ START_I ][ startClusterIndex ] );
        }
    
    for( int m=0; m < middleClusterIndices.size(); m++ ) {
        ClusterIndex ci = middleClusterIndices.getElementDirect( m );
        
        mappedWord.appendElementString(
            inDestClusters[ ci.setIndex ][ ci.index ] );
        }
    // add any remaining portion of the word, which could not
    // be matched to mid clusters
    // (this is an error condition)
    if( strlen( wordWorking ) > 0 ) {
        mappedWord.appendElementString( wordWorking );
        }
    if( endClusterIndex != -1 ) {
        mappedWord.appendElementString( 
            inDestClusters[ END_I ][ endClusterIndex ] );
        }
    
    delete [] wordWorkingOrig;
    
    return mappedWord.getElementString();
    }

                    



int main() {
    
    SimpleVector<int> shuffles[4];
    

    for( int s=0; s<NUM_CLUSTER_SETS; s++ ) {
        for( int c=0; c<allClusterSizes[s]; c++ ) {
            shuffles[s].push_back( c );
            }
        closeMirrorShuffle( &( shuffles[s] ), 10 );
        
        for( int c=0; c<allClusterSizes[s]; c++ ) {            
            allMappings[s][ shuffles[s].getElementDirect( c ) ] = 
                allClusters[s][ c ];
            allBackMappings[s][ c ] =
                allClusters[s][ shuffles[s].getElementDirect( c ) ];
            }
        }


    int numRead = 1;
    char nextWord[100];
    
    while(numRead > 0 ) {
        numRead = scanf( "%99s", nextWord );
        
        if( numRead > 0 ) {
            char *lower = stringToLowerCase( nextWord );

            char *newWord = remapWordNew( lower, 
                                          allClusters,
                                          allMappings);
            
            char *backMap = remapWordNew( newWord,
                                          allClusters,
                                          allBackMappings );
            
            //printf( "%s (%s)", newWord, backMap );
            printf( "%s ", newWord );
            
            delete [] lower;
            delete [] newWord;
            delete [] backMap;
            }
        }
    
    

    return 0;
    }




int mainOld() {
    
    //SimpleVector<const char*> allSyllables;
    

    // these all contain indices into syllablesByLengthList

    SimpleVector<int> syllablesWithVowelBoth;
    SimpleVector<int> syllablesWithVowelBothShuff;

    SimpleVector<int> syllablesWithVowelStart;
    SimpleVector<int> syllablesWithVowelStartShuff;

    SimpleVector<int> syllablesWithVowelEnd;
    SimpleVector<int> syllablesWithVowelEndShuff;

    SimpleVector<int> syllablesWithBothConsonants;
    SimpleVector<int> syllablesWithBothConsonantsShuff;
    

    for( int i=0; i<NUM_SYLLABLES; i++ ) {
        const char *syl = syllablesByLengthList[i];
        
        char vAtStart = isVowelStart( syl );
        char vAtEnd = isVowelEnd( syl );
        
        if( vAtStart && vAtEnd ) {
            syllablesWithVowelBoth.push_back( i );
            syllablesWithVowelBothShuff.push_back( i );
            }
        else if( vAtStart ) {
            syllablesWithVowelStart.push_back( i );
            syllablesWithVowelStartShuff.push_back( i );
            }
        else if( vAtEnd ) {
            syllablesWithVowelEnd.push_back( i );
            syllablesWithVowelEndShuff.push_back( i );
            }
        else {
            syllablesWithBothConsonants.push_back( i );
            syllablesWithBothConsonantsShuff.push_back( i );
            }
        
        }
    
    // now we have them split into sets based on these linkage
    // characteristics


    shuffle( &syllablesWithVowelBothShuff );
    shuffle( &syllablesWithVowelStartShuff );
    shuffle( &syllablesWithVowelEndShuff );
    shuffle( &syllablesWithBothConsonantsShuff );
    
    
    mapByShuffle( &syllablesWithVowelBoth, &syllablesWithVowelBothShuff );
    mapByShuffle( &syllablesWithVowelStart, &syllablesWithVowelStartShuff );
    mapByShuffle( &syllablesWithVowelEnd, &syllablesWithVowelEndShuff );
    mapByShuffle( &syllablesWithBothConsonants, 
                  &syllablesWithBothConsonantsShuff );
    

    for( int i=0; i<500; i++ ) {
        printf( "%d %s => %s\n", i, 
                syllablesByLengthList[i], syllableMapping[i] );
        }

    char nextWord[100];
    

    int numRead = 1;
    
    while(numRead > 0 ) {
        numRead = scanf( "%99s", nextWord );
        
        if( numRead > 0 ) {
            char *lower = stringToLowerCase( nextWord );
            
            char *newWord = remapWord( lower, 
                                       syllablesByLengthList,
                                       syllableMapping );
            
            char *backMap = remapWord( newWord,
                                       syllableMapping, syllablesByLengthList );
            
            printf( "%s (%s)", newWord, backMap );
            
            delete [] lower;
            delete [] newWord;
            delete [] backMap;
            }
        }
    
    

    return 0;
    }
