/*
 *  Game.h
 *  1917 v1.07
 *   edit log -
 *    1.07 badly-drawn map region and dice values comment
 *    1.06 expanded comments on newGame(), explain regionID
 *    1.05 expanded the comments explaining isLegalAction()
 *    1.04 expanded path description, starting direction
 *    1.03 edited comment for getmostpubs() 30-apr-14
 *    1.02 abstract ADT version of Game
 *    1.00 concrete game type version
 *  Do not alter this file
 *
 *  Created by Richard Buckland on 20/04/14.
 *  Licensed under Creative Commons SA-BY-NC 3.0.
 *
 */

#define NUM_UNIS 3

// player ID of each university
#define NO_ONE 0
#define UNI_A 1
#define UNI_B 2
#define UNI_C 3

// contents of an ARC
#define VACANT_ARC 0
#define ARC_A 1
#define ARC_B 2
#define ARC_C 3

// contents of a VERTEX
#define VACANT_VERTEX 0
#define CAMPUS_A 1
#define CAMPUS_B 2
#define CAMPUS_C 3
#define GO8_A 4
#define GO8_B 5
#define GO8_C 6

// action codes
#define PASS 0
#define BUILD_CAMPUS 1
#define BUILD_GO8 2
#define OBTAIN_ARC 3
#define START_SPINOFF 4
#define OBTAIN_PUBLICATION 5
#define OBTAIN_IP_PATENT 6
#define RETRAIN_STUDENTS 7

// disciplines
#define STUDENT_THD 0
#define STUDENT_BPS 1
#define STUDENT_BQN 2
#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5

#define NUM_REGIONS 19
#define PATH_LIMIT 150

#define TRUE 1
#define FALSE 0

typedef struct _game * Game;

// your team designs this type not us
// store in this struct all the things you might want to know about
// the game so you can write the interface functions in this header
// eg you might want to store the current turn number (so i've put
// it in for you as an example but take it out if you don't want it)

// in your Game.c include the details of the data
// you want to store in the _game struct eg

// typedef struct _game {
//   int currentTurn;
//   ... more stuff in here
// } game;

// a path is a sequence of L=left R=right B=back steps
// starting from the initial campus of player 1 / A at the top
// of the map facing inwards represented as a string of length
// PATH_LIMIT or less (including the terminating 0).
// a path can specify a vertex (the vertex at the end of the path)
// and a path can specify an ARC (the last ARC in the path)
// it is fine and legal for a path to not be the shortest path
// to the destination, it can even contain loops if you like.
// The length of a path (including the terminating 0) must never
// exceed PATH_LIMIT.  Every edge in the path must lie on the
// island, paths cannot include edges which are in the sea.
typedef char path[PATH_LIMIT];

// actions are what the player AI returns.  They say the one thing
// the AI wants to do next.  In the playGame logic you'll ask
// a player for their next action, then you'll check it is a legal
// action (using isLegalAction()), then you'll perform that action
// for them (using makeAction()), then you'll ask the same player
// for another action and repeat this over and over again until they
// return PASS at which time you'll throw the dice (using
// throwDice()) and advance the game to the next player.  And repeat.
typedef struct _action {
   int actionCode;  // see #defines above
   path destination; // if the action operates on a vertex or ARC this
                     // specifies *which* vertex or path.  unused
                     // otherwise
   int disciplineFrom;  // used for the retrain students action
   int disciplineTo;    // used for the retrain students action
} action;

/* **** Functions which change the game aka SETTERS **** */
// make a new game, given the disciplines produced by each
// region, and the value on the dice discs in each region.
// note: each array must be NUM_REGIONS long
// eg if you are using my sample game struct above this function
// would need to set the field currentTurn to -1.  (because the turn
// number is -1 at the start of the game)
// the ordering of the regions is column by column left to right,
// going from the top of each column to the bottom before moving
// to the next column to the right.
//
// so to create the default game as shown on the badly drawn map:
//
/*
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ,
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV,
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN,
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ,
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
*/
//
//   int disciplines[] = DEFAULT_DISCIPLINES;
//   int dice[] = DEFAULT_DICE;
//   Game g = newGame (disciplines, dice);
Game newGame (int discipline[], int dice[]);

// free all the memory malloced for the game
void disposeGame (Game g);

// make the specified action for the current player and update the
// game state accordingly.
// The function may assume that the action requested is legal.
// START_SPINOFF is not a legal action here
void makeAction (Game g, action a);

// advance the game to the next turn,
// assuming that the dice has just been rolled and produced diceScore
// the game starts in turn -1 (we call this state "Terra Nullis") and
// moves to turn 0 as soon as the first dice is thrown.
void throwDice (Game g, int diceScore);

/* **** Functions which GET data about the game aka GETTERS **** */

// what type of students are produced by the specified region?
// regionID is the index of the region in the newGame arrays (above)
// see discipline codes above
int getDiscipline (Game g, int regionID);

// what dice value produces students in the specified region?
// 2..12
int getDiceValue (Game g, int regionID);

// which university currently has the prestige award for the most ARCs?
// this is NO_ONE until the first arc is purchased after the game
// has started.
int getMostARCs (Game g);

// which university currently has the prestige award for the most pubs?
// this is NO_ONE until the first publication is made.
int getMostPublications (Game g);

// return the current turn number of the game -1,0,1, ..
int getTurnNumber (Game g);

// return the player id of the player whose turn it is
// the result of this function is NO_ONE during Terra Nullis
int getWhoseTurn (Game g);

// return the contents of the given vertex (ie campus code or
// VACANT_VERTEX)
int getCampus(Game g, path pathToVertex);

// the contents of the given edge (ie ARC code or vacent ARC)
int getARC(Game g, path pathToEdge);

// returns TRUE if it is legal for the current
// player to make the specified action, FALSE otherwise.
//
// "legal" means everything is legal:
//   * that the action code is a valid action code which is legal to
//     be made at this time
//   * that any path is well formed and legal ie consisting only of
//     the legal direction characters and of a legal length,
//     and which does not leave the island into the sea at any stage.
//   * that disciplines mentioned in any retraining actions are valid
//     discipline numbers, and that the university has sufficient
//     students of the correct type to perform the retraining
//
// eg when placing a campus consider such things as:
//   * is the path a well formed legal path
//   * does it lead to a vacent vertex?
//   * under the rules of the game are they allowed to place a
//     campus at that vertex?  (eg is it adjacent to one of their ARCs?)
//   * does the player have the 4 specific students required to pay for
//     that campus?
// It is not legal to make any action during Terra Nullis ie
// before the game has started.
// It is not legal for a player to make the moves OBTAIN_PUBLICATION
// or OBTAIN_IP_PATENT (they can make the move START_SPINOFF)
// you can assume that any pths passed in are NULL terminated strings.
int isLegalAction (Game g, action a);

// --- get data about a specified player ---

// return the number of KPI points the specified player currently has
int getKPIpoints (Game g, int player);

// return the number of ARC grants the specified player currently has
int getARCs (Game g, int player);

// return the number of GO8 campuses the specified player currently has
int getGO8s (Game g, int player);

// return the number of normal Campuses the specified player currently has
int getCampuses (Game g, int player);

// return the number of IP Patents the specified player currently has
int getIPs (Game g, int player);

// return the number of Publications the specified player currently has
int getPublications (Game g, int player);

// return the number of students of the specified discipline type
// the specified player currently has
int getStudents (Game g, int player, int discipline);

// return how many students of discipline type disciplineFrom
// the specified player would need to retrain in order to get one
// student of discipline type disciplineTo.  This will depend
// on what retraining centers, if any, they have a campus at.
int getExchangeRate (Game g, int player,
                     int disciplineFrom, int disciplineTo);

