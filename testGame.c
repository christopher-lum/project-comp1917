1	//
     2	//    By Group Knowledge_Island_Lachlan_Gareth_Chris_Akila_Kae
     3	//    Date: 08/05/2016
     4	//
     5	
     6	#include <stdio.h>
     7	#include <stdlib.h>
     8	#include <assert.h>
     9	#include <math.h>
    10	#include "Game.h"
    11	
    12	void StartTests();
    13	void GameOneTest();
    14	
    15	int main (int argc, char* argv[]) {
    16	    
    17	    StartTests();
    18	    GameOneTest();
    19	    
    20	    return EXIT_SUCCESS;
    21	}
    22	
    23	void StartTests () {
    24	    
    25	    int disciplines[19] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ,
    26	        STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV,
    27	        STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN,
    28	        STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ,
    29	        STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
    30	    int dice[19] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    31	    
    32	    Game g = newGame (disciplines, dice);
    33	    
    34	    
    35	    assert(getExchangeRate (g, UNI_A, STUDENT_BQN, STUDENT_MMONEY) == 2);
    36	    assert(getExchangeRate (g, UNI_B, STUDENT_BQN, STUDENT_MMONEY) == 2);
    37	    assert(getExchangeRate (g, UNI_C, STUDENT_BQN, STUDENT_MMONEY) == 2);
    38	    
    39	    //Ensures each university have a set 3 x BPS, 3 x B?, 1 x MTV, 1 x MJ, 1 x M$, and no ThD students at the start
    40	    assert(getStudents (g, UNI_A, STUDENT_THD) == 0);
    41	    assert(getStudents (g, UNI_A, STUDENT_BPS) == 3);
    42	    assert(getStudents (g, UNI_A, STUDENT_BQN) == 1);
    43	    assert(getStudents (g, UNI_A, STUDENT_MJ) == 1);
    44	    assert(getStudents (g, UNI_A, STUDENT_MTV) == 1);
    45	    assert(getStudents (g, UNI_A, STUDENT_MMONEY) == 1);
    46	    
    47	    assert(getStudents (g, UNI_B, STUDENT_MMONEY) == 1);
    48	    assert(getStudents (g, UNI_B, STUDENT_THD) == 0);
    49	    assert(getStudents (g, UNI_B, STUDENT_BPS) == 3);
    50	    assert(getStudents (g, UNI_B, STUDENT_BQN) == 1);
    51	    assert(getStudents (g, UNI_B, STUDENT_MJ) == 1);
    52	    assert(getStudents (g, UNI_B, STUDENT_MTV) == 1);
    53	    
    54	    assert(getStudents (g, UNI_C, STUDENT_THD) == 0);
    55	    assert(getStudents (g, UNI_C, STUDENT_BPS) == 3);
    56	    assert(getStudents (g, UNI_C, STUDENT_BQN) == 1);
    57	    assert(getStudents (g, UNI_C, STUDENT_MJ) == 1);
    58	    assert(getStudents (g, UNI_C, STUDENT_MTV) == 1);
    59	    assert(getStudents (g, UNI_C, STUDENT_MMONEY) == 1);
    60	    
    61	    //Ensures each university have no publications at the start
    62	    assert(getPublications (g, UNI_A) == 0);
    63	    assert(getPublications (g, UNI_B) == 0);
    64	    assert(getPublications (g, UNI_C) == 0);
    65	    
    66	    //Ensures each university have no IP patents at the start
    67	    assert(getIPs (g, UNI_A) == 0);
    68	    assert(getIPs (g, UNI_B) == 0);
    69	    assert(getIPs (g, UNI_C) == 0);
    70	    
    71	    //Ensures each university begin with 2 campuses
    72	    assert(getCampuses (g, UNI_A) == 2);
    73	    assert(getCampuses (g, UNI_B) == 2);
    74	    assert(getCampuses (g, UNI_C) == 2);
    75	    
    76	    //Ensures each university have no GO8's at the start
    77	    assert(getGO8s (g, UNI_A) == 0);
    78	    assert(getGO8s (g, UNI_B) == 0);
    79	    assert(getGO8s (g, UNI_C) == 0);
    80	    
    81	    //Ensures each university have no ARC grants at the start
    82	    assert(getARCs (g, UNI_A) == 0);
    83	    assert(getARCs (g, UNI_B) == 0);
    84	    assert(getARCs (g, UNI_C) == 0);
    85	    
    86	    //Ensures each university begin with a set 20 KPI points
    87	    assert(getKPIpoints (g, UNI_A) == 20);
    88	    assert(getKPIpoints (g, UNI_B) == 20);
    89	    assert(getKPIpoints (g, UNI_C) == 20);
    90	    
    91	    //Ensures the turn number at the start is set to no-one
    92	    assert(getWhoseTurn (g) == NO_ONE);
    93	    
    94	    
    95	    assert(getTurnNumber (g) == -1);
    96	    
    97	    //Ensures no-one has the most publications
    98	    assert(getMostPublications (g) == NO_ONE);
    99	    
   100	    //Ensures no-one has the most ARCS
   101	    assert(getMostARCs (g) == NO_ONE);
   102	    
   103	    //ensures region - input arrays have been interpruted correctly
   104	    int i = 0;
   105	    while (i < 19) {
   106	        assert(getDiceValue (g, i) == dice[i]);
   107	        assert(getDiscipline (g, i) == disciplines[i]);
   108	        i++;
   109	    }
   110	    
   111	    //Campuses - tests for locations of various campuses amongst the board
   112	    assert(getCampus(g, "") == UNI_A);
   113	    assert(getCampus(g, "RRLRL") == UNI_C);
   114	    assert(getCampus(g, "LRLRL") == UNI_B);
   115	    assert(getCampus(g, "RRLRLRRLRL") == UNI_B);
   116	    assert(getCampus(g, "LRLRLLRLRL") == UNI_C);
   117	    assert(getCampus(g, "RRRLRLRLRLR") == UNI_A);
   118	    //Empty - tests for vacant vertexes on the board and ensure they are not occupied
   119	    assert(getCampus(g, "RRLRR") == VACANT_VERTEX);
   120	    assert(getCampus(g, "LRLLRLRL") == VACANT_VERTEX);
   121	    //Illegal Paths
   122	    assert(getCampus(g, "RL") == VACANT_VERTEX);
   123	    assert(getCampus(g, "LRLRLLRLRRRRR") == VACANT_VERTEX);
   124	    
   125	    //ensure there are no starting arcs by mistake
   126	    assert(getARC(g, "R") == VACANT_ARC);
   127	    assert(getARC(g, "L") == VACANT_ARC);
   128	    assert(getARC(g, "RRRLRLRLRLR") == VACANT_ARC);
   129	    assert(getARC(g, "RRRLRLRLRLRR") == VACANT_ARC);
   130	    
   131	    disposeGame (g);
   132	    
   133	}
   134	
   135	void GameOneTest() {
   136	    int disciplines[19] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ,
   137	        STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV,
   138	        STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN,
   139	        STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ,
   140	        STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   141	    int dice[19] = {9,10,8,12,6,5,3,7,3,11,4,6,4,7,9,2,8,10,5};
   142	    
   143	    Game g = newGame (disciplines, dice);
   144	    
   145	    throwDice (g, 6);
   146	    
   147	    assert(getTurnNumber (g) == 0);
   148	    
   149	    // when a 6 is rolled A should get an MJ
   150	    assert(getStudents (g, UNI_A, STUDENT_MJ) == 2);
   151	    
   152	    action a = {START_SPINOFF, "R", STUDENT_BQN, STUDENT_MMONEY};
   153	
   154	    assert(isLegalAction (g, a) == 1);
   155	    
   156	    makeAction (g, a);
   157	    
   158	    //If a SPIN_OFF is called there will be an IP or pub but not both
   159	    assert(  (getIPs(g, UNI_A) == 1 || getPublications(g, UNI_A) == 1) && !(getIPs(g, UNI_A) == 1 && getPublications(g, UNI_A) == 1)  );
   160	
   161	    action b = { OBTAIN_ARC, "R", STUDENT_BQN, STUDENT_MMONEY };
   162	    assert(isLegalAction (g, b) == 1);
   163	    makeAction (g, b);
   164	    
   165	    //switch back to UNI_A's turn
   166	    throwDice (g, 1);
   167	    throwDice (g, 1);
   168	    throwDice (g, 7);
   169	    
   170	    //since a 7 was rolled, UNI_A collected a MTV which was then converted to a THD.
   171	    assert(getStudents (g, UNI_A, STUDENT_MTV) == 0);
   172	    assert(getStudents (g, UNI_A, STUDENT_THD) == 1);
   173	    
   174	    // Could use a few more turns
   175	}
