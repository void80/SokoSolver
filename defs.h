#ifndef defs_h_in_SokoSolver_c_by_Myself
#define defs_h_in_SokoSolver_c_by_Myself

//#define MAX_MOVINGS 10
/*
#define BALL	'$'
#define GOAL	'.'
#define BOTH	'*'
#define WALL	'#'
#define EMPTY	' '
#define MEGOAL	':'
#define MEEMPTY	'@'
*/
//#define LEFT	1
//#define UP		2
//#define DOWN	3
//#define RIGHT	4

//#define MINDIR	1
//#define MAXDIR	4


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


#define PRINT_NOT_POSSIBLE   0
#define PRINT_STEP           1
#define PRINT_SAME_CONFIG    0
#define PRINT_TOO_MUCH_STEPS 0

#define TEST_FIELD_AT_START       0
#define TEST_FIELD_AFTER_CREATION 1

#endif // !defined defs_h_in_SokoSolver_c_by_Myself