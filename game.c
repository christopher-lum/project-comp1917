// Knowledge_Island_Lachlan_Gareth_Chris_Akila_Kae 
// Last Edited: 12/05/2016

/*  Game.c
 *  Drawn from Game.h
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "Game.h"

//deonotes top left corner of hex in grid form for all regions
int getActionCode(action a);
int getDisciplineFrom(action a);
int getDisciplineTo(action a);
void newCampus(Game g, path pathToVertex, int player);
void newGO8(Game g, path pathToVertex, int player);
void newARC(Game g, path pathToVertex, int player);
void convertVerticeXYToSide(int dir, int *x, int *y);
int convertPathToXY(path p, int*x, int*y);
int getVertex(Game g, int x, int y);
void setVertex(Game g, int x, int y, int type);
int getSide(Game g, int x, int y);
void setSide(Game g, int x, int y, int type);
void setDiceValue(Game g, int index, int diceValue);
void setDiscipline(Game g, int index, int type);
int hasTrainingCentre(Game g, int player, int discipline);
void newIP (Game g, int player);
void newPublication (Game g, int player);
void newTurnNumber (Game g);
void setTurnNumber (Game g, int value);
void setStudents(Game g, int player, int discipline, int amount);
void modifyIncrementStudents(Game g, int player, int discipline, int increment);
int pathLegality(path p);

typedef struct _game {
    int TurnNumber; 
    int discipline[19];
    int dice[19];
    int gridVertices[6][11]; //gridVertices[0][0].player   .type
    int gridSides[11][11];  //gridVertices[0][0].player   .type
    int students[3][6];
    int IPs[3];
    int Publications[3];
} game;
void disposeGame (Game g) {
    free(g);
}
Game newGame (int discipline[], int dice[]) {
    Game g = malloc (sizeof(game));

    setTurnNumber(g, -1);
    int counter = 0;
    while (counter < 19) {
        setDiscipline(g, counter, discipline[counter]);
        setDiceValue(g, counter, dice[counter]);
        counter++;
    }
    setStudents(g, UNI_A, STUDENT_MJ, 1);
    setStudents(g, UNI_B, STUDENT_MJ, 1);
    setStudents(g, UNI_C, STUDENT_MJ, 1);

    setStudents(g, UNI_A, STUDENT_MTV, 1);
    setStudents(g, UNI_B, STUDENT_MTV, 1);
    setStudents(g, UNI_C, STUDENT_MTV, 1);

    setStudents(g, UNI_A, STUDENT_BPS, 3);
    setStudents(g, UNI_B, STUDENT_BPS, 3);
    setStudents(g, UNI_C, STUDENT_BPS, 3);

    setStudents(g, UNI_A, STUDENT_BQN, 1);
    setStudents(g, UNI_B, STUDENT_BQN, 1);
    setStudents(g, UNI_C, STUDENT_BQN, 1);

    setStudents(g, UNI_A, STUDENT_MMONEY, 1);
    setStudents(g, UNI_B, STUDENT_MMONEY, 1);
    setStudents(g, UNI_C, STUDENT_MMONEY, 1);


    newCampus(g, "", UNI_A);
    newCampus(g, "RRLRL", UNI_C);
    newCampus(g, "LRLRL", UNI_B);
    newCampus(g, "RRLRLRRLRL", UNI_B);
    newCampus(g, "LRLRLLRLRL", UNI_C);
    newCampus(g, "RRRLRLRLRLR", UNI_A);

    assert(getStudents (g, UNI_A, STUDENT_THD) == 0);
    assert(getStudents (g, UNI_A, STUDENT_BPS) == 3);
    assert(getStudents (g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents (g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents (g, UNI_A, STUDENT_MTV) == 1);

    assert(getStudents (g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents (g, UNI_B, STUDENT_THD) == 0);
    assert(getStudents (g, UNI_B, STUDENT_BPS) == 3);
    assert(getStudents (g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents (g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents (g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents (g, UNI_B, STUDENT_MMONEY) == 1);

    assert(getStudents (g, UNI_C, STUDENT_THD) == 0);
    assert(getStudents (g, UNI_C, STUDENT_BPS) == 3);
    assert(getStudents (g, UNI_C, STUDENT_BQN) == 1);
    assert(getStudents (g, UNI_C, STUDENT_MJ) == 1);
    assert(getStudents (g, UNI_C, STUDENT_MTV) == 1);
    assert(getStudents (g, UNI_C, STUDENT_MMONEY) == 1);


    assert(getPublications (g, UNI_A) == 0);
    assert(getPublications (g, UNI_B) == 0);
    assert(getPublications (g, UNI_C) == 0);


    assert(getIPs (g, UNI_A) == 0);
    assert(getIPs (g, UNI_B) == 0);
    assert(getIPs (g, UNI_C) == 0);


    assert(getCampuses (g, UNI_A) == 2);
    assert(getCampuses (g, UNI_B) == 2);
    assert(getCampuses (g, UNI_C) == 2);


    assert(getGO8s (g, UNI_A) == 0);
    assert(getGO8s (g, UNI_B) == 0);
    assert(getGO8s (g, UNI_C) == 0);


    assert(getARCs (g, UNI_A) == 0);
    assert(getARCs (g, UNI_B) == 0);
    assert(getARCs (g, UNI_C) == 0);


    assert(getKPIpoints (g, UNI_A) == 20);
    assert(getKPIpoints (g, UNI_B) == 20);
    assert(getKPIpoints (g, UNI_C) == 20);


    assert(getWhoseTurn (g) == NO_ONE);


    assert(getTurnNumber (g) == -1);


    assert(getMostPublications (g) == NO_ONE);


    assert(getMostARCs (g) == NO_ONE);

    
    return g;
}

int getActionCode(action a) {
    return a.actionCode;
}

int getDisciplineFrom(action a) {
    return a.disciplineFrom;
}
int getDisciplineTo(action a) {
    return a.disciplineTo;
}

int isLegalAction (Game g, action a) {
    int legality = 0;
    int p, q, r, t, u, f, e, h, l, s;
    if (getTurnNumber(g) == -1) {
        //nothing since 0 is assumed
        //nothing is legal in this case
    } else if (getActionCode(a) == PASS) {
        legality = 1;
    } else if (getActionCode(a) == BUILD_CAMPUS) {
        //Player Has Resources
        p = (getStudents(g, getWhoseTurn(g), STUDENT_BPS) >= 1);
        q = (getStudents(g, getWhoseTurn(g), STUDENT_BQN) >= 1);
        r = (getStudents(g, getWhoseTurn(g), STUDENT_MJ) >= 1);
        t = (getStudents(g, getWhoseTurn(g), STUDENT_MTV) >= 1);
        assert(strlen(a.destination) != PATH_LIMIT);

        //Check the path is legal
        s = pathLegality(a.destination);

        //player is building on empty spot
        u = (getCampus(g, a.destination) == VACANT_VERTEX);

        path new;
        strcpy(new, a.destination);
        strcat(new, "R\0");   //There is no campus next to this one
        
        f = (getCampus(g, new) == VACANT_VERTEX);

        strcpy(new, a.destination);
        strcat(new, "L\0");
        e = (getCampus(g, new) == VACANT_VERTEX);
        
        strcpy(new, a.destination);
        strcat(new, "B\0");
        h = (getCampus(g, new) == VACANT_VERTEX);

        if (p && r && q && t && u && f && e && h && s) {
            legality = 1;
        }
    } else if (getActionCode(a) == BUILD_GO8) {
        //Player Has Resources
        p = (getStudents(g, getWhoseTurn(g), STUDENT_MJ) >= 2);
        q = (getStudents(g, getWhoseTurn(g), STUDENT_MTV) >= 3);
        assert(strlen(a.destination) != PATH_LIMIT);

        //Check the path is legal
        s = pathLegality(a.destination);

        //Player does not have 8 campuses
        l = (getGO8s(g, getWhoseTurn(g)) < 8);

        //Player is building over own campus
        u = (getCampus(g, a.destination) == getWhoseTurn(g));

        path new;
        strcpy(new, a.destination);
        strcat(new, "R\0");   //There is no campus next to this one
        
        f = (getCampus(g, new) == VACANT_VERTEX);

        strcpy(new, a.destination);
        strcat(new, "L\0");
        e = (getCampus(g, new) == VACANT_VERTEX);
        
        strcpy(new, a.destination);
        strcat(new, "B\0");
        h = (getCampus(g, new) == VACANT_VERTEX);

        if (p && q && u && f && e && h && l && s) {
            legality = 1;
        }
    } else if (getActionCode(a) == OBTAIN_ARC) {
        //Player Has Resources
        p = (getStudents(g, getWhoseTurn(g), STUDENT_BPS) >= 1);
        q = (getStudents(g, getWhoseTurn(g), STUDENT_BQN) >= 1);
        assert(strlen(a.destination) != PATH_LIMIT);

        //Check the path is legal
        s = pathLegality(a.destination);

        //Building on vacant arc
        u = (getARC(g, a.destination) == VACANT_ARC);

        path new;
        strcpy(new, a.destination);
        strcat(new, "R\0");   //There is no campus next to this one
        
        f = (getARC(g, new) == VACANT_ARC);

        strcpy(new, a.destination);
        strcat(new, "L\0");
        e = (getARC(g, new) == VACANT_ARC);
        
        strcpy(new, a.destination);
        strcat(new, "B\0");
        h = (getARC(g, new) == VACANT_ARC);

        if (p && q && u && f && e && h && s) {
            legality = 1;
        }
    } else if (getActionCode(a) == OBTAIN_PUBLICATION || getActionCode(a) == OBTAIN_IP_PATENT) {
        //Player Has Resources
        p = (getStudents(g, getWhoseTurn(g), STUDENT_MJ) >= 1);
        q = (getStudents(g, getWhoseTurn(g), STUDENT_MTV) >= 1);
        r = (getStudents(g, getWhoseTurn(g), STUDENT_MMONEY) >= 1);
        if (p && q && r) {
            legality = 1;
        }
    } else if (getActionCode(a) == RETRAIN_STUDENTS) {
        //Player Has Resources
        p = (getStudents(g, getWhoseTurn(g), getDisciplineFrom(a)) >= getExchangeRate(g, getWhoseTurn(g), getDisciplineFrom(a), getDisciplineTo(a))); 
        if (p) {
            legality = 1;
        }
    }
    return legality;
}

void makeAction (Game g, action a) {

    
    if (getActionCode(a) == PASS) {
        //ThrowDice(g);
    } else if (getActionCode(a) == BUILD_CAMPUS) {
        assert(getStudents(g, getWhoseTurn(g), STUDENT_BPS) >= 1);
        assert(getStudents(g, getWhoseTurn(g), STUDENT_BQN) >= 1);
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MJ) >= 1);
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MTV) >= 1);

        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_BPS, -1);
        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_BQN, -1);
        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MJ, -1);
        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MTV, -1);

        newCampus(g, a.destination, getWhoseTurn(g));
    } else if (getActionCode(a) == BUILD_GO8) {
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MJ) >= 2);
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MMONEY) >= 3);

        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MJ, -2);
        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MMONEY, -3);

        newGO8(g, a.destination, getWhoseTurn(g));
    } else if (getActionCode(a) == OBTAIN_ARC) {
        assert(getStudents(g, getWhoseTurn(g), STUDENT_BPS) >= 1);
        assert(getStudents(g, getWhoseTurn(g), STUDENT_BQN) >= 1);

        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_BPS, -1);
        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_BQN, -1);

        newARC(g, a.destination, getWhoseTurn(g));
    } else if (getActionCode(a) == OBTAIN_PUBLICATION) {
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MJ) >= 1);
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MTV) >= 1);
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MMONEY) >= 1);

        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MJ, -1);
        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MTV, -1);
        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MMONEY, -1);

        newPublication(g, getWhoseTurn(g));
    } else if (getActionCode(a) == OBTAIN_IP_PATENT) {
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MJ) >= 1);
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MTV) >= 1);
        assert(getStudents(g, getWhoseTurn(g), STUDENT_MMONEY) >= 1);

        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MJ, -1);
        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MTV, -1);
        modifyIncrementStudents(g, getWhoseTurn(g), STUDENT_MMONEY, -1);

        newIP(g, getWhoseTurn(g));
    } else if (getActionCode(a) == RETRAIN_STUDENTS) {
        assert(getStudents(g, getWhoseTurn(g), getDisciplineFrom(a)) >= getExchangeRate(g, getWhoseTurn(g), getDisciplineFrom(a), getDisciplineTo(a))); 

        modifyIncrementStudents(g, getWhoseTurn(g), getDisciplineFrom(a), -1*getExchangeRate(g, getWhoseTurn(g), getDisciplineFrom(a), getDisciplineTo(a)));

        modifyIncrementStudents(g, getWhoseTurn(g), getDisciplineTo(a), 1);
    }

}



void throwDice (Game g, int diceScore) {
    newTurnNumber(g);
    int counter = 0;
    int player;
    int increment;
    int i = 0, j = 0;
    int regionIndex[19][2] ={ {0, 2}, {0, 4}, {0, 6}, {1, 1}, {1, 3}, {1, 5}, {1,7}, {2,0}, {2,2},  {2,4}, {2,6}, {2,8}, {3,1}, {3,3}, {3,5}, {3,7}, {4,2}, {4,4}, {4,6}}; 
    
    while (counter < 19) { //ADDS RESOURCES
        if (getDiceValue(g, counter) == diceScore) {
            j = 0;
    //        printf("%d\n",getKPIpoints(g, 1));
            while (j < 3) {
                i = 0;
                while (i < 2) {
                    if (getVertex(g, regionIndex[counter][0] + i, regionIndex[counter][1] + j) != 0) {
                        player = (((getVertex(g, regionIndex[counter][0] + i, regionIndex[counter][1] + j) -1)%3)+1);

                        increment = ((int)((getVertex(g, regionIndex[counter][0] + i, regionIndex[counter][1] + j) +2)/3));
//printf("increment: %d", increment);
                        modifyIncrementStudents(g, player, getDiscipline(g, counter), increment);
                        
                    }
                    i++;
                }
                j++;
            }
        }
        counter++;
    }
    if (diceScore == 7) {
    counter = 1;
    while (counter < 4) { //CONVERS MMONEY and MTV to THD
        modifyIncrementStudents(g, counter, STUDENT_THD, getStudents(g, counter, STUDENT_MTV) + getStudents(g, counter, STUDENT_MMONEY));
        setStudents(g, counter, STUDENT_MMONEY, 0);
        setStudents(g, counter, STUDENT_MTV, 0);   
        counter++; 
    }
    }

}

int getKPIpoints (Game g, int player) {
    int KPI = 0;    
    if (getMostARCs(g) == player) {
        KPI += 10;
    }
    if (getMostPublications(g) == player) {
        KPI += 10;
    }
    KPI += 20*getGO8s(g, player);
    KPI += 10*getCampuses(g, player);
    KPI += 2*getARCs(g, player);
    KPI += 10*getIPs(g,player);
    return KPI;
}

int getMostARCs (Game g) {
    int answer;
    if (getARCs(g, UNI_A) > getARCs(g, UNI_B) && getARCs(g, UNI_A) > getARCs(g, UNI_C)) {
        answer = UNI_A;
    } else if (getARCs(g, UNI_B) > getARCs(g, UNI_A) && getARCs(g, UNI_B) > getARCs(g, UNI_C)) {
        answer = UNI_B;
    } else if (getARCs(g, UNI_C) > getARCs(g, UNI_A) && getARCs(g, UNI_C) > getARCs(g, UNI_B)) {
        answer = UNI_C;
    } else {
        answer = NO_ONE;
    }
    return answer;  
}

// return the number of GO8 campuses the specified player currently has
int getGO8s (Game g, int player) {
    int i= 0, j = 0;
    int answer = 0;
    while (j < 11) {
        i = 0;
        while (i < 6) {
            if (getVertex(g, i, j) == player + 3) {
                answer++;
            }
            i++;
        }
    j++;
    }
    return answer;
}
// return the number of normal Campuses the specified player currently has
int getCampuses (Game g, int player) {
    int i = 0, j = 0;
    int answer = 0;
//printf("\n");
//printf("\n");
    while (j < 11) {
        i = 0;
        while (i < 6) {
           // printf("%d", getVertex(g, i, j));
            if (getVertex(g, i, j) == player) {
                answer++;
            }
            i++;
        }
   // printf("\n");
    j++;
    }
    return answer;
}

// return the number of IP Patents the 
int getARCs (Game g, int player) {
    int i= 0, j = 0;
    int answer = 0;
    while (j < 11) {
        i = 0;
        while (i < 11) {
            if (getSide(g, i, j) == player) {
                answer++;
            }
            i++;
        }
    j++;
    }
    return answer;
}

int getWhoseTurn (Game g) {
    int answer;
    if (getTurnNumber(g) != -1) {
        answer = (getTurnNumber(g) % 3) + 1;
    } else {
        answer = NO_ONE;
    }
    return answer;
}

int getExchangeRate (Game g, int player,int disciplineFrom, int disciplineTo) {
    int answer = 3;
    if (hasTrainingCentre(g, player, disciplineFrom)) {
        answer = 2;
    }
    return answer;
}
    
int getMostPublications (Game g) {
    int answer;
    if (getPublications(g, UNI_A) > getPublications(g, UNI_B) && getPublications(g, UNI_A) > getPublications(g, UNI_C)) {
        answer = UNI_A;
    } else if (getPublications(g, UNI_B) > getPublications(g, UNI_A) && getPublications(g, UNI_B) > getPublications(g, UNI_C)) {
        answer = UNI_B;
    } else if (getPublications(g, UNI_C) > getPublications(g, UNI_B) && getPublications(g, UNI_C) > getPublications(g, UNI_A)) {
        answer = UNI_C;
    } else {
        answer = NO_ONE;
    }
    return answer;
}
int getCampus(Game g, path pathToVertex) {
    int x;
    int y;
    convertPathToXY(pathToVertex,&x, &y);
    return getVertex(g, x, y);
}
void newCampus(Game g, path pathToVertex, int player) {
    int x, y;
    convertPathToXY(pathToVertex,&x, &y);

    setVertex(g, x, y, player); //whose turn = campus code
}

void newGO8(Game g, path pathToVertex, int player) {
    int x, y;
    convertPathToXY(pathToVertex,&x, &y);

    setVertex(g, x, y, player+3); //whose turn + 3 = GO8 code
}

void newARC(Game g, path pathToVertex, int player) {
    int x, y;
    int dir = convertPathToXY(pathToVertex,&x, &y);
    convertVerticeXYToSide(dir, &x, &y);
    setSide(g, x, y, player); //whose turn = ARC code
}

int getARC(Game g, path pathToEdge) {
    int x, y;
    int dir = convertPathToXY(pathToEdge,&x, &y);

    //converts the vertix x,y into side x,y 
    convertVerticeXYToSide(dir, &x, &y);

    return getSide(g, x, y);
}

void convertVerticeXYToSide(int dir, int *x, int *y) {
      *x = (*x)*2;
    if (dir == 3 || dir == 4) {
        *y += 1;
    } else if (dir == 5) {
        *x+= 1;
    } else if (dir == 2) {
        *x += -1;
    }
}

int convertPathToXY(path p, int*x, int*y) {
    int counter = 0;
    *x = 2;
    *y = 0;
    int dir = -1;
    //printf("start\n");
    while (counter < strlen(p)) {
       // printf("%d, %d, %d\n", *x, *y, dir);
        if (dir == -1) {
            if (p[counter] == 'R') {
                *x+= 1;
                dir = 2;
            } else if (p[counter] == 'L') {
                *y+= 1;
                dir = 4;
            } else if (p[counter] == 'B') {
                assert(FALSE);
            }
        } else if (dir == 0) {
            if (p[counter] == 'R') {
                *y+= -1;
                dir = 1;
            } else if (p[counter] == 'L') {
                *x+= -1;
                dir = 5;
            } else if (p[counter] == 'B') {
                *y+= 1;
                dir = 3;
            }
        } else if (dir == 1) {
            if (p[counter] == 'R') {
                *x+= 1;
                dir = 2;
            } else if (p[counter] == 'L') {
                *y+= -1;
                dir = 0;
            } else if (p[counter] == 'B') {
                *y+= 1;
                dir = 4;
            }
        } else if (dir == 2) {
            if (p[counter] == 'R') {
                *y+= 1;
                dir = 3;
            } else if (p[counter] == 'L') {
                *y+= -1;
                dir = 1;
            } else if (p[counter] == 'B') {
                *x+= -1;
                dir = 5;
            }
        } else if (dir == 3) {
            if (p[counter] == 'R') {
                *y+= 1;
                dir = 4;
            } else if (p[counter] == 'L') {
                *x+= 1;
                dir = 2;
            } else if (p[counter] == 'B') {
                *y+= -1;
                dir = 0;
            }
        } else if (dir == 4) {
            if (p[counter] == 'R') {
                *x+= -1;
                dir = 5;
            } else if (p[counter] == 'L') {
                *y+= 1;
                dir = 3;
            } else if (p[counter] == 'B') {
                *y+= -1;
                dir = 1;
            }
        } else if (dir == 5) {
            if (p[counter] == 'R') {
                *y+= -1;
                dir = 0;
            } else if (p[counter] == 'L') {
                *y+= 1;
                dir = 4;
            } else if (p[counter] == 'B') {
                *x+= 1;
                dir = 2;
            }
        }
        counter++;
    }
   // printf("end\n");
  //  printf("%dx  %dy", *x, *y);
    return dir;
}

int pathLegality(path p) {
    int counter = 0;
    int x = 2;
    int y = 0;
    int dir = -1;
    int legality = 1;
    while (counter < strlen(p) && legality) {
        if (dir == -1) {
            if (p[counter] == 'R') {
                x+= 1;
                dir = 2;
            } else if (p[counter] == 'L') {
                y+= -1;
                dir = 4;
            } else if (p[counter] == 'B') {
                assert(FALSE);
            }
        } else if (dir == 0) {
            if (p[counter] == 'R') {
                y+= 1;
                dir = 1;
            } else if (p[counter] == 'L') {
                x+= -1;
                dir = 5;
            } else if (p[counter] == 'B') {
                y+= -1;
                dir = 3;
            }
        } else if (dir == 1) {
            if (p[counter] == 'R') {
                x+= 1;
                dir = 2;
            } else if (p[counter] == 'L') {
                y+= 1;
                dir = 0;
            } else if (p[counter] == 'B') {
                y+= -1;
                dir = 4;
            }
        } else if (dir == 2) {
            if (p[counter] == 'R') {
                y+= -1;
                dir = 3;
            } else if (p[counter] == 'L') {
                y+= 1;
                dir = 1;
            } else if (p[counter] == 'B') {
                x+= -1;
                dir = 5;
            }
        } else if (dir == 3) {
            if (p[counter] == 'R') {
                y+= -1;
                dir = 4;
            } else if (p[counter] == 'L') {
                x+= 1;
                dir = 2;
            } else if (p[counter] == 'B') {
                y+= 1;
                dir = 0;
            }
        } else if (dir == 4) {
            if (p[counter] == 'R') {
                x+= -1;
                dir = 5;
            } else if (p[counter] == 'L') {
                y+= -1;
                dir = 3;
            } else if (p[counter] == 'B') {
                y+= 1;
                dir = 1;
            }
        } else if (dir == 5) {
            if (p[counter] == 'R') {
                y+= 1;
                dir = 0;
            } else if (p[counter] == 'L') {
                y+= -1;
                dir = 4;
            } else if (p[counter] == 'B') {
                x+= 1;
                dir = 2;
            }
        }
        if ((x < 0 || x > 5) || ((y < 2 || y > 8) && (x == 0 || x == 5)) || ((y < 1 || y > 9) && (x == 1 || x == 4)) || ((y < 0 || y > 5) && (x == 2 || x == 3))) {
            legality = 0;
        }
        counter++;
    }
    return legality;
}

int getVertex(Game g, int x, int y) {
    return (g->gridVertices[x][y]);
}

void setVertex(Game g, int x, int y, int type) {
//    printf("ap, ");
    g->gridVertices[x][y] = type;
}

int getSide(Game g, int x, int y) {
    //assert((x%4 != 1 || y%2 != 1) && (x%4 != 3 || y%2 != 0));          //valid tile
    
    return g->gridSides[x][y];
}
void setSide(Game g, int x, int y, int type) {
    assert((x%4 != 1 || y%2 != 1) && (x%4 != 3 || y%2 != 0));          //valid tile
    
    g->gridSides[x][y] = type;
}

void setDiscipline(Game g, int index, int type) {

    g->discipline[index] = type;
}

void setDiceValue(Game g, int index, int diceValue) {

    g->dice[index] = diceValue;
}

int getDiscipline (Game g, int regionID) {
    return g->discipline[regionID];
}

int getDiceValue (Game g, int regionID) {
    return g->dice[regionID];
}

int hasTrainingCentre(Game g, int player, int discipline) {
   
    int answer = 0;
    //write code to say
    if ( discipline == STUDENT_BPS) {
        if (getVertex(g, 1, 8) == player || getVertex(g, 1, 8) == player + 3 || getVertex(g, 1, 9) == player || getVertex(g, 1, 9) == player + 3) {
            answer = 1;
        }
    } else if ( discipline == STUDENT_BQN) {
        if (getVertex(g, 5, 5) == player || getVertex(g, 5, 5) == player + 3 || getVertex(g, 5, 6) == player || getVertex(g, 5, 6) == player + 3) {
            answer = 1;
        }
    } else if ( discipline == STUDENT_MJ) {
        if (getVertex(g, 4, 8) == player || getVertex(g, 4, 8) == player + 3 || getVertex(g, 4, 9) == player || getVertex(g, 4, 9) == player + 3) {
            answer = 1;
        }
    } else if ( discipline == STUDENT_MTV) {
        if (getVertex(g, 1, 1) == player || getVertex(g, 1, 1) == player + 3 || getVertex(g, 2, 1) == player || getVertex(g, 2, 1) == player + 3) {
            answer = 1;
        }
    } else if ( discipline == STUDENT_MMONEY) {
        if (getVertex(g, 3, 1) == player || getVertex(g, 3, 1) == player + 3 || getVertex(g, 4, 1) == player || getVertex(g, 4, 1) == player + 3) {
            answer = 1;
        }
    } 
    return answer;
}

int getIPs (Game g, int player) {
    return g->IPs[player-1];
}
void newIP (Game g, int player) {
    g->IPs[player-1] += 1;
}

int getPublications (Game g, int player) {
    return g->Publications[player-1];
}
void newPublication (Game g, int player) {
    g->Publications[player-1] += 1;
}
int getTurnNumber (Game g) {
    return g->TurnNumber;
}
void newTurnNumber (Game g) {
    g->TurnNumber++;
}
void setTurnNumber (Game g, int value) {
    g->TurnNumber = value;
}
int getStudents(Game g, int player, int discipline) {
    return g->students[player - 1][discipline];
}
void setStudents(Game g, int player, int discipline, int amount) {
    g->students[player - 1][discipline] = amount;
}
void modifyIncrementStudents(Game g, int player, int discipline, int increment)  {
    g->students[player - 1][discipline] += increment;
}


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
//typedef char path[PATH_LIMIT];

// actions are what the player AI returns.  They say the one thing
// the AI wants to do next.  In the playGame logic you'll ask
// a player for their next action, then you'll check it is a legal
// action (using isLegalAction()), then you'll perform that action
// for them (using makeAction()), then you'll ask the same player
// for another action and repeat this over and over again until they 
// return PASS at which time you'll throw the dice (using 
// throwDice()) and advance the game to the next player.  And repeat.
/*typedef struct _action {
   int actionCode;  // see #defines above
   path destination; // if the action operates on a vertex or ARC this
                     // specifies *which* vertex or path.  unused 
                     // otherwise
   int disciplineFrom;  // used for the retrain students action
   int disciplineTo;    // used for the retrain students action
} action;*/

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
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
*/
//
//   int disciplines[] = DEFAULT_DISCIPLINES;
//   int dice[] = DEFAULT_DICE;
//   Game g = newGame (disciplines, dice);

// free all the memory malloced for the game


// make the specified action for the current player and update the 
// game state accordingly.  
// The function may assume that the action requested is legal.
// START_SPINOFF is not a legal action here


// advance the game to the next turn, 
// assuming that the dice has just been rolled and produced diceScore
// the game starts in turn -1 (we call this state "Terra Nullis") and 
// moves to turn 0 as soon as the first dice is thrown. 
//void throwDice (Game g, int diceScore);

/* **** Functions which GET data about the game aka GETTERS **** */

// what type of students are produced by the specified region?
// regionID is the index of the region in the newGame arrays (above) 
// see discipline codes above
//int getDiscipline (Game g, int regionID);

// what dice value produces students in the specified region?
// 2..12
//int getDiceValue (Game g, int regionID);

// which university currently has the prestige award for the most ARCs?
// this is NO_ONE until the first arc is purchased after the game 
// has started.  
//int getMostARCs (Game g);

// which university currently has the prestige award for the most pubs?
// this is NO_ONE until the first publication is made.

// return the current turn number of the game -1,0,1, ..
//int getTurnNumber (Game g);

// return the player id of the player whose turn it is 
// the result of this function is NO_ONE during Terra Nullis

// return the contents of the given vertex (ie campus code or 
// VACANT_VERTEX)
//int getCampus(Game g, path pathToVertex);

// the contents of the given edge (ie ARC code or vacent ARC)
//int getARC(Game g, path pathToEdge);

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


// --- get data about a specified player ---

// return the number of KPI points the specified player currently has


// return the number of ARC grants the specified player currently has
//int getARCs (Game g, int player);

// return the number of GO8 campuses the specified player currently has
//int getGO8s (Game g, int player);

// return the number of normal Campuses the specified player currently has
//int getCampuses (Game g, int player);

// return the number of IP Patents the specified player currently has
//int getIPs (Game g, int player);

// return the number of Publications the specified player currently has
//int getPublications (Game g, int player);

// return the number of students of the specified discipline type 
// the specified player currently has
//int getStudents (Game g, int player, int discipline);

// return how many students of discipline type disciplineFrom
// the specified player would need to retrain in order to get one 
// student of discipline type disciplineTo.  This will depend 
// on what retraining centers, if any, they have a campus at.
//int getExchangeRate (Game g, int player, 
//                     int disciplineFrom, int disciplineTo);

