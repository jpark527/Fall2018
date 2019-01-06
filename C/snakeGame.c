#include <stdbool.h>
#include <stdlib.h>     // system, random
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#define WIDTH 35
#define HEIGHT 35
#define SLOW_RATE 12
#define MAX_TAIL (WIDTH * HEIGHT)
#define MY_ASCII 128
#define INVALID_TEXT "snake: invalid option\nusage: snake [--help]"
#define HELP_TEXT "i = UP\nk = DOWN\nj = LEFT\nl = RIGHT"

enum DIRECTION {STOP, EAST, WEST, SOUTH, NORTH};

typedef bool (*dirFptr)(enum DIRECTION*);
typedef bool (*MoveHead)(struct position*);

struct position {
    size_t _x, _y;
};

void initialize(struct position *head, dirFptr *dirChanger, MoveHead *moveHead);
bool draw(struct position *head, size_t *score, struct position *fruit, bool *fruitExists, struct position *tails);
bool updateScore(size_t *score);
bool printRest(size_t w, size_t h, size_t *score, struct position *tails);
bool generateFruit(struct position *fruit, bool *fruitExists);
bool printFruit(bool *fruitAlive);
bool checkStatus(struct position *head, struct position *tails, size_t tailSize);
bool isKeyPressed();
void changeDirection(enum DIRECTION *dir, dirFptr *dirChanger);
bool goWest(enum DIRECTION *dir);
bool goEast(enum DIRECTION *dir);
bool goSouth(enum DIRECTION *dir);
bool goNorth(enum DIRECTION *dir);
bool dirDummy(enum DIRECTION *dir);
bool setFirstTail(struct position *head, struct position *tails);
bool setTails(struct position *tails, size_t *tailSize);
void moveSnake(enum DIRECTION *dir, struct position *head, size_t *slowDown, struct position *tails, size_t tailSize, MoveHead *moveHead);
bool headToEast(struct position *head);
bool headToWest(struct position *head);
bool headToSouth(struct position *head);
bool headToNorth(struct position *head);
bool headDummy(struct position *head);
bool checkArgs(int *argc, char **argv);

int main(int argc, char **argv) {
    dirFptr *dirChanger = malloc(sizeof(dirFptr) * MY_ASCII);
    MoveHead *moveHead = malloc(sizeof(MoveHead) * MY_ASCII);
    struct position head, fruit, *tails = malloc(sizeof(struct position) * MAX_TAIL);
    bool fruitExists = false;
    enum DIRECTION dir = STOP;
    size_t count = 0, score = 0;
    if(!checkArgs(&argc, argv)) {
        srand(time(NULL));
        initialize(&head, dirChanger, moveHead);		
        while(draw(&head, &score, &fruit, &fruitExists, tails) && checkStatus(&head, tails, (size_t)(score/10))) {
	    changeDirection(&dir, dirChanger);
            moveSnake(&dir, &head, &count, tails, (size_t)(score/10), moveHead);
            system("clear");
        }
        puts("\n           G A M E  O V E R\n");
        free(tails), free(dirChanger), free(moveHead);
        tails = NULL, dirChanger = NULL, moveHead = NULL;
    }
    return 0;    
}

bool checkArgs(int *argc, char **argv) {
    return *argc!=1 && ((*argc==2 && !strncmp(argv[1],"--help",6) && puts(HELP_TEXT)) ||
    	   (((*argc==2 && strncmp(argv[1],"--help",6)) || (*argc!=2)) && puts(INVALID_TEXT)));
}

void initialize(struct position *head, dirFptr *dirChanger, MoveHead *moveHead) {
    head->_x = (size_t)(WIDTH / 2);
    head->_y = (size_t)(HEIGHT / 2);
    for(size_t i=0; i<MY_ASCII; ++i) {
        dirChanger[i] = dirDummy;
        moveHead[i] = headDummy;
    }
    dirChanger[(size_t)('i')] = goNorth;
    dirChanger[(size_t)('k')] = goSouth;
    dirChanger[(size_t)('j')] = goWest;
    dirChanger[(size_t)('l')] = goEast;
    moveHead[(size_t)(EAST)] = headToEast;
    moveHead[(size_t)(WEST)] = headToWest;
    moveHead[(size_t)(SOUTH)] = headToSouth;
    moveHead[(size_t)(NORTH)] = headToNorth;
}

bool draw(struct position *head, size_t *score, struct position *fruit, bool *fruitExists, struct position *tails) {
    bool fruitAlive = false;
    !*fruitExists && generateFruit(fruit, fruitExists);
    printf("SCORE: %i\n", *score);
    for(register size_t i=0; i<WIDTH+2; ++i)
        fputs("#", stdout);
    for(register size_t h=0; h<HEIGHT; ++h){
        fputs("\n#", stdout);
        for(register size_t w=0; w<WIDTH; ++w)
            ((head->_x==w && head->_y==h && fputs("O", stdout)) ||
            (*fruitExists && fruit->_x==w && fruit->_y==h && printFruit(&fruitAlive)))
            || printRest(w, h, score, tails);
	fputs("#", stdout);
    }
    puts("");
    for(register size_t i=0; i<WIDTH+2; ++i)
        fputs("#", stdout);
    puts("");
    *fruitExists = fruitAlive;
    !*fruitExists && updateScore(score);		
    return head->_x<WIDTH && head->_y<HEIGHT; 
}

bool updateScore(size_t *score) {   
    *score += 10; 			
    return true;
}

bool printRest(size_t w, size_t h, size_t *score, struct position *tails) {
    bool blank = true;
    for(register size_t i=0; i<(size_t)(*score/10); ++i)
        if(tails[i]._x==w && tails[i]._y==h) {
            fputs("o", stdout), blank=false;
	    break;
	}
    blank && fputs(" ", stdout);
    return true;
}

bool generateFruit(struct position *fruit, bool *fruitExists) {
    fruit->_x = (size_t)(rand() % WIDTH);		
    fruit->_y = (size_t)(rand() % HEIGHT);
    *fruitExists = true;
    return true;
}

bool printFruit(bool *fruitAlive) {
    *fruitAlive = true;
    return fputs("E", stdout);
}

bool checkStatus(struct position *head, struct position *tails, size_t tailSize) {
    for(register size_t i=0; i<tailSize; ++i)
        if(tails[i]._x==head->_x && tails[i]._y==head->_y)
            return false;
    return true;
}

bool isKeyPressed() {
    struct termios oldt, newt;
    int ch;
    int oldf;
 
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
    ch = getchar();
 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    (ch != EOF) && ungetc(ch, stdin);
    return ch != EOF;
}

void changeDirection(enum DIRECTION *dir, dirFptr *dirChanger) {
    isKeyPressed() && dirChanger[getchar()](dir);
}

bool goWest(enum DIRECTION *dir) {
    *dir = WEST;
    return true;
}

bool goEast(enum DIRECTION *dir) {
    *dir = EAST;    
    return true;
}

bool goSouth(enum DIRECTION *dir) {
    *dir = SOUTH;
    return true;
}

bool goNorth(enum DIRECTION *dir) {
    *dir = NORTH;    
    return true;
}

bool dirDummy(enum DIRECTION *dir) {
    return true;
}

bool setFirstTail(struct position *head, struct position *tails) {
    tails[0]._x = head->_x;
    tails[0]._y = head->_y;
    return true;
}

bool setTails(struct position *tails, size_t *tailSize) {
    for(size_t i=*tailSize-1; i; --i) {	
        tails[i]._x = tails[i-1]._x;
        tails[i]._y = tails[i-1]._y;
    }
    return true;
}

void moveSnake(enum DIRECTION *dir, struct position *head, size_t *slowDown, struct position *tails, size_t tailSize, MoveHead *moveHead) {
    !*slowDown && (tailSize > 1) && setTails(tails, &tailSize);
    !*slowDown && setFirstTail(head, tails) && moveHead[(size_t)(*dir)](head); 
    *slowDown = (*slowDown+1) % SLOW_RATE;       
}  

bool headToEast(struct position *head) {
    ++head->_x;
    return true;
}

bool headToWest(struct position *head) {
    --head->_x;
    return true;
}

bool headToSouth(struct position *head) {
    ++head->_y;
    return true;
}

bool headToNorth(struct position *head) {
    --head->_y;
    return true;
}

bool headDummy(struct position *head) {
    return true;
}
