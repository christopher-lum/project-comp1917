 1	
     2	/*
     3	 * Run Game
     4	 *  
     5	 * by Knowledge_Island_Lachlan_Gareth_Chris_Akila_Kae 
     6	 * last updated 15/05/2016
     7	 *
     8	 * The Run Game for knowledge island using only user input
     9	 *
    10	 */
    11	
    12	#include <stdio.h>
    13	#include <stdlib.h>
    14	#include <assert.h>
    15	#include <string.h>
    16	
    17	#include "Game.h"
    18	
    19	#define WINNING_KPI 150
    20	
    21	int rollDice (void);
    22	int spinoffAction(void);
    23	void printActions(Game g, int currentPlayer);
    24	int VictoryCheck(Game g, int currentPlayer);
    25	
    26	int main (int argc, char * argv[]){
    27	
    28	    int dice[19] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    29	    int disciplines[19] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
    30	                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
    31	                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
    32	                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
    33	                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
    34	    Game g = newGame (disciplines, dice);
    35	    
    36	    action nextAction;
    37	    
    38	    int currentPlayer;
    39	    int diceValue;
    40	    int actionCode;
    41	    char *destination = "";
    42	    int passed = FALSE;
    43	    int gameNotOver = TRUE;
    44	
    45	    while (gameNotOver) {
    46	        
    47	        printf("Please enter a dice value\n");
    48	        scanf("%d", &diceValue);
    49	        throwDice(g, diceValue);
    50	
    51	        currentPlayer = getWhoseTurn(g);
    52	        printActions(g, currentPlayer);
    53	
    54	        while (!passed && gameNotOver) {
    55	
    56	        printf("Please enter your action code: ");
    57	        scanf("%d", &actionCode);
    58	        
    59	        if (actionCode == BUILD_CAMPUS || actionCode == BUILD_GO8 || actionCode == OBTAIN_ARC) {
    60	            nextAction.actionCode = actionCode;
    61	            printf("Please enter your destination: ");
    62	            scanf("%s", destination);
    63	            strcat(destination, "\0");
    64	            strcpy(nextAction.destination, destination);
    65	            if (isLegalAction(g, nextAction)) {
    66	                makeAction(g, nextAction);
    67	            } else {
    68	                printf("Please enter a legal path and ensure you have enough resources\n");
    69	            }
    70	        } else if (actionCode == RETRAIN_STUDENTS) {
    71	            nextAction.actionCode = actionCode;
    72	            printf("Please enter your discipline from: ");
    73	            scanf("%d", &nextAction.disciplineFrom);
    74	            printf("Please enter your discipline to: ");
    75	            scanf("%d", &nextAction.disciplineTo);
    76	            if (isLegalAction(g, nextAction)) {
    77	                makeAction(g, nextAction);
    78	            } else {
    79	                printf("Please enter a legal exchange!\n");
    80	            }
    81	        } else if (actionCode == START_SPINOFF) {
    82	            nextAction.actionCode = spinoffAction();
    83	            if (isLegalAction(g, nextAction)) {
    84	                makeAction(g, nextAction);
    85	            } else {
    86	                printf("Please ensure you have enough resources!\n");
    87	            }
    88	        } else if (actionCode == PASS) {
    89	            nextAction.actionCode = actionCode;
    90	            passed = TRUE;
    91	        } else {
    92	            printf("Please enter a valid action!\n");
    93	        }
    94	        gameNotOver = !VictoryCheck(g, currentPlayer);
    95	        
    96	        }
    97	        
    98	    }
    99	
   100	    printActions(g, UNI_A);
   101	    printActions(g, UNI_B);
   102	    printActions(g, UNI_C);
   103	    disposeGame(g);
   104	          
   105	}
   106	
   107	
   108	//two die roll function - addition of two random numbers between and inclusive from 1-6
   109	int rollDice (void){
   110	    
   111	    int diceOne;
   112	    int diceTwo;
   113	    int diceTotal;
   114	    
   115	    diceOne = rand() % 7 + 1;
   116	    diceTwo = rand() % 7 + 1;
   117	    
   118	    diceTotal = diceOne+diceTwo;
   119	    
   120	    return diceTotal;
   121	}
   122	
   123	int VictoryCheck(Game g, int currentPlayer) {
   124	    int answer = FALSE;
   125	    if (getKPIpoints(g, currentPlayer) >= WINNING_KPI) {
   126	        answer = TRUE;
   127	    }
   128	    return answer;
   129	}
   130	
   131	//spinoff function - 2/3 publication 1/3 ip patent
   132	int spinoffAction(void) {
   133	    
   134	    int spinoffTotal;
   135	    int returnTotal;
   136	    
   137	    spinoffTotal = rand() % 3 + 1;
   138	    
   139	    if(spinoffTotal == 1) {
   140	        returnTotal = OBTAIN_IP_PATENT;
   141	    }else {
   142	        returnTotal = OBTAIN_PUBLICATION;
   143	    }
   144	    return returnTotal;
   145	}
   146	
   147	//statistics as required
   148	void printActions(Game g, int currentPlayer){
   149	    printf("*** Turn %d ***\n", getTurnNumber(g));
   150	    printf("*** It is now player %d's turn\n", currentPlayer);
   151	    printf("##The current player's KPI value is %d##\n", getKPIpoints(g, currentPlayer));
   152	    printf("##The current player's ARC grant value is %d##\n", getARCs(g, currentPlayer));
   153	    printf("##The current player's GO8 campus value is %d##\n", getGO8s(g, currentPlayer));
   154	    printf("##The current player's Campuses value is %d##\n", getCampuses(g, currentPlayer));
   155	    printf("##The current player's IP value is %d##\n",  getIPs(g, currentPlayer));
   156	    printf("##The current player's Publication value is %d##\n", getPublications(g, currentPlayer));
   157	    printf("##The current player's THD value is %d##\n", getStudents(g, currentPlayer, STUDENT_THD));
   158	    printf("##The current player's BPS value is %d##\n", getStudents(g, currentPlayer, STUDENT_BPS));
   159	    printf("##The current player's BQN value is %d##\n", getStudents(g, currentPlayer, STUDENT_BQN));
   160	    printf("##The current player's MJ value is %d##\n",  getStudents(g, currentPlayer, STUDENT_MJ));
   161	    printf("##The current player's MTV value is %d##\n", getStudents(g, currentPlayer, STUDENT_MTV));
   162	    printf("##The current player's MMONEY value is %d##\n", getStudents(g, currentPlayer, STUDENT_MMONEY));
   163	}
