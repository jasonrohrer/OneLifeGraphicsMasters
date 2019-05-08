
const char *vowelClusters[72] = {
    "e",
    "i",
    "a",
    "o",
    "u",
    "y",
    "ou",
    "ea",
    "io",
    "oo",
    "ee",
    "ie",
    "ai",
    "au",
    "ay",
    "ui",
    "ue",
    "oa",
    "oi",
    "ia",
    "ua",
    "ei",
    "ey",
    "oy",
    "eu",
    "iou",
    "oe",
    "ae",
    "ya",
    "eye",
    "eau",
    "eo",
    "yo",
    "ye",
    "uo",
    "eou",
    "yea",
    "you",
    "uy",
    "uea",
    "aye",
    "yu",
    "uee",
    "ieu",
    "aa",
    "uai",
    "iu",
    "yi",
    "uoi",
    "uoy",
    "yie",
    "ooe",
    "eoi",
    "ayo",
    "ao",
    "yeu",
    "yeo",
    "uu",
    "uey",
    "ueu",
    "uay",
    "oye",
    "oua",
    "oeu",
    "uie",
    "ueue",
    "oui",
    "oue",
    "iao",
    "aue",
    "aou",
    "aie" };

const char *consonantClusters[272] = {
    "r",
    "n",
    "t",
    "l",
    "d",
    "s",
    "c",
    "m",
    "p",
    "b",
    "g",
    "f",
    "v",
    "ng",
    "st",
    "h",
    "w",
    "ss",
    "bl",
    "nt",
    "sh",
    "k",
    "tr",
    "ch",
    "pr",
    "z",
    "th",
    "ck",
    "x",
    "nd",
    "gr",
    "j",
    "pl",
    "cr",
    "br",
    "ll",
    "cl",
    "q",
    "fl",
    "sp",
    "nc",
    "ph",
    "rd",
    "dr",
    "rt",
    "fr",
    "gl",
    "sm",
    "sc",
    "rs",
    "rn",
    "str",
    "sl",
    "ct",
    "ght",
    "nk",
    "ld",
    "ns",
    "rk",
    "mp",
    "wh",
    "tch",
    "sk",
    "rm",
    "dg",
    "sw",
    "lt",
    "wn",
    "sn",
    "scr",
    "tl",
    "dl",
    "ff",
    "gh",
    "ft",
    "wr",
    "rg",
    "gn",
    "nch",
    "lk",
    "thr",
    "pt",
    "ps",
    "kn",
    "tt",
    "sq",
    "rv",
    "rth",
    "cs",
    "mb",
    "rch",
    "lv",
    "rl",
    "tw",
    "ts",
    "rh",
    "spr",
    "rc",
    "wl",
    "lm",
    "ws",
    "rb",
    "ls",
    "chr",
    "sch",
    "rr",
    "lf",
    "shr",
    "rp",
    "ms",
    "pp",
    "ngs",
    "nn",
    "spl",
    "zl",
    "nth",
    "sph",
    "lp",
    "kl",
    "ds",
    "rst",
    "mpt",
    "lth",
    "gg",
    "wk",
    "mn",
    "zz",
    "wd",
    "nx",
    "nds",
    "tz",
    "cks",
    "rf",
    "phr",
    "rds",
    "kr",
    "nct",
    "bt",
    "rts",
    "lg",
    "dd",
    "chl",
    "nts",
    "mm",
    "dw",
    "dh",
    "rsh",
    "rks",
    "ngth",
    "kh",
    "gs",
    "nks",
    "lls",
    "lch",
    "wz",
    "hn",
    "bs",
    "sth",
    "rld",
    "phl",
    "mps",
    "xt",
    "rtz",
    "ntz",
    "ghts",
    "cz",
    "wns",
    "tts",
    "rnt",
    "mph",
    "lms",
    "lb",
    "dth",
    "wth",
    "vr",
    "thw",
    "rrh",
    "rq",
    "rns",
    "rms",
    "rgh",
    "hm",
    "gm",
    "ffs",
    "bb",
    "thm",
    "sv",
    "scl",
    "schl",
    "rps",
    "pn",
    "nz",
    "ltz",
    "lsh",
    "ln",
    "ks",
    "hs",
    "hr",
    "hl",
    "fts",
    "wp",
    "vt",
    "tsch",
    "sz",
    "schn",
    "schm",
    "rct",
    "ngst",
    "mt",
    "lts",
    "lft",
    "kw",
    "hns",
    "fs",
    "dst",
    "cht",
    "bh",
    "zw",
    "xth",
    "wt",
    "wnst",
    "wls",
    "ttn",
    "sts",
    "sf",
    "schw",
    "rz",
    "rw",
    "rsts",
    "rscht",
    "rsch",
    "rpt",
    "rmth",
    "rgn",
    "rcs",
    "rck",
    "rbs",
    "pth",
    "psh",
    "phs",
    "pf",
    "nstr",
    "nst",
    "nq",
    "nns",
    "nkh",
    "nh",
    "ndth",
    "ncts",
    "mnd",
    "mbs",
    "lq",
    "lpt",
    "lph",
    "lfth",
    "lfs",
    "ldt",
    "lds",
    "lct",
    "lc",
    "kj",
    "ht",
    "ghth",
    "fth",
    "fj",
    "dz",
    "dn",
    "dj",
    "dds",
    "cts",
    "chs",
    "bw" };

#include "syllablesLength.cpp"

#include "minorGems/util/SimpleVector.h"
#include "minorGems/util/stringUtils.h"
#include "minorGems/util/random/CustomRandomSource.h"

#include <string.h>


#define NUM_VOWELS 6

const char vowels[ NUM_VOWELS ] = { 'a', 'e', 'i', 'o', 'u', 'y' };







static char isVowelStart( const char *inSyllable ) {
    // y not vowel at start
    for( int i=0; i<NUM_VOWELS - 1; i++ ) {
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




int main() {
    
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
