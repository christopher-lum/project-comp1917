
     1	/*
     2	 *  Mr Robber. is almost as completely useless as  Mr. Pass
     3	 *  This AI makes really bad moves!
     4	 *  When they have enough students they start a spin off.
     5	 *  Except when there is enough to trade to get a spinoff they will.
     6	 *  Otherwise they pass
     7	 *  
     8	 * Gareth / Chris AI group 
     9	 * last updated 17/05/2016
    10	 *
    11	 */
    12	
    13	
    14	#include <stdio.h>
    15	#include <stdlib.h>
    16	#include <assert.h>
    17	
    18	#include "Game.h"
    19	#include "mechanicalTurk.h"
    20	
    21	#define SPINOFF_BPS 0
    22	#define SPINOFF_BQN 0
    23	#define SPINOFF_MTV 1
    24	#define SPINOFF_MMONEY 1
    25	#define SPINOFF_MJ 1
    26	
    27	#define GENERAL_EXCHANGE 3
    28	
    29	void checkExchanges(int *extra, int *needs, int has, int wants, int exchange);
    30	
    31	action decideAction (Game g) {
    32	
    33	    action nextAction;
    34	
    35	    int currentPlayer = getWhoseTurn(g); 
    36	    
    37	    if ( currentPlayer != NO_ONE ) {
    38	
    39	        int sMJ = (getStudents(g, getWhoseTurn(g), STUDENT_MJ));
    40	        int sMTV = (getStudents(g, getWhoseTurn(g), STUDENT_MTV));
    41	        int sMMONEY = (getStudents(g, getWhoseTurn(g), STUDENT_MMONEY));
    42	        int sBQN = (getStudents(g, getWhoseTurn(g), STUDENT_BQN));
    43	        int sBPS = (getStudents(g, getWhoseTurn(g), STUDENT_BPS));
    44	/*
    45	        int exBPSBQN = getExchangeRate(g), getWhoseTurn(g), STUDENT_BPS, STUDENT_BQN);
    46	        int exBPSMMONEY = getExchangeRate(g), getWhoseTurn(g), STUDENT_BPS, STUDENT_MMONEY);
    47	        int exBPSMTV = getExchangeRate(g), getWhoseTurn(g), STUDENT_BPS, STUDENT_MTV);
    48	        int exBPSMJ = getExchangeRate(g), getWhoseTurn(g), STUDENT_BPS, STUDENT_MJ);
    49	        int exBQNMMONEY = getExchangeRate(g), getWhoseTurn(g), STUDENT_BQN, STUDENT_MMONEY);
    50	        int exBQNMTV = getExchangeRate(g), getWhoseTurn(g), STUDENT_BQN, STUDENT_MTV);
    51	        int exBQNMJ = getExchangeRate(g), getWhoseTurn(g), STUDENT_BQN, STUDENT_MJ);
    52	        int exMMONEYMTV = getExchangeRate(g), getWhoseTurn(g), STUDENT_MMONEY,  STUDENT_MTV);
    53	        int exMMONEYMJ = getExchangeRate(g), getWhoseTurn(g), STUDENT_MMONEY, STUDENT_MJ);
    54	        int exMTVMJ = getExchangeRate(g), getWhoseTurn(g), STUDENT_MTV, STUDENT_MJ);
    55	*/
    56	        int needsAction = 1;
    57	        
    58	        //General Building Structure
    59	        //Building SPINOFFs
    60	        
    61	    
    62	        int extraBPS = 0, extraBQN = 0, extraMTV = 0, extraMMONEY = 0, extraMJ = 0;
    63	        int needsBPS = 0, needsBQN = 0, needsMTV = 0, needsMMONEY = 0, needsMJ = 0;
    64	        checkExchanges(&extraBPS, &needsBPS, sBPS, SPINOFF_BPS, GENERAL_EXCHANGE);
    65	        checkExchanges(&extraBQN, &needsBQN, sBQN, SPINOFF_BQN, GENERAL_EXCHANGE);
    66	        checkExchanges(&extraMTV, &needsMTV, sMTV, SPINOFF_MTV, GENERAL_EXCHANGE);
    67	        checkExchanges(&extraMMONEY, &needsMMONEY, sMMONEY, SPINOFF_MMONEY, GENERAL_EXCHANGE);
    68	        checkExchanges(&extraMJ, &needsMJ, sMJ, SPINOFF_MJ, GENERAL_EXCHANGE);
    69	
    70	        //printf("extra %d, needs %d\n", extraBPS + extraBQN + extraMTV + extraMMONEY + extraMJ, needsBPS + needsBQN + needsMTV + needsMMONEY + needsMJ);
    71	        if (needsAction) {
    72	        printf("Retrain Students?\n");
    73	        if (extraBPS + extraBQN + extraMTV + extraMMONEY + extraMJ >= needsBPS + needsBQN + needsMTV + needsMMONEY + needsMJ && needsBPS + needsBQN + needsMTV + needsMMONEY + needsMJ != 0) {
    74	            nextAction.actionCode = RETRAIN_STUDENTS;
    75	            if (extraMMONEY > 0) {
    76	                nextAction.disciplineFrom = STUDENT_MMONEY;
    77	                if (needsMTV > 0) {
    78	                    nextAction.disciplineTo = STUDENT_MTV;
    79	                } else if (needsMJ > 0) {
    80	                    nextAction.disciplineTo = STUDENT_MJ;
    81	                } else if (needsBQN > 0) {
    82	                    nextAction.disciplineTo = STUDENT_BQN;
    83	                } else if (needsBPS > 0) {
    84	                    nextAction.disciplineTo = STUDENT_BPS;
    85	                }
    86	            } else if (extraMTV > 0) {
    87	                nextAction.disciplineFrom = STUDENT_MTV;
    88	                if (needsMMONEY > 0) {
    89	                    nextAction.disciplineTo = STUDENT_MMONEY;
    90	                } else if (needsMJ > 0) {
    91	                    nextAction.disciplineTo = STUDENT_MJ;
    92	                } else if (needsBQN > 0) {
    93	                    nextAction.disciplineTo = STUDENT_BQN;
    94	                } else if (needsBPS > 0) {
    95	                    nextAction.disciplineTo = STUDENT_BPS;
    96	                }
    97	            } else if (extraMJ > 0) {
    98	                nextAction.disciplineFrom = STUDENT_MJ;
    99	                if (needsMTV > 0) {
   100	                    nextAction.disciplineTo = STUDENT_MTV;
   101	                } else if (needsMMONEY > 0) {
   102	                    nextAction.disciplineTo = STUDENT_MMONEY;
   103	                } else if (needsBQN > 0) {
   104	                    nextAction.disciplineTo = STUDENT_BQN;
   105	                } else if (needsBPS > 0) {
   106	                    nextAction.disciplineTo = STUDENT_BPS;
   107	                }
   108	            } else if (extraBQN > 0) {
   109	                nextAction.disciplineFrom = STUDENT_BQN;
   110	                if (needsMTV > 0) {
   111	                    nextAction.disciplineTo = STUDENT_MTV;
   112	                } else if (needsMJ > 0) {
   113	                    nextAction.disciplineTo = STUDENT_MJ;
   114	                } else if (needsMMONEY > 0) {
   115	                    nextAction.disciplineTo = STUDENT_MMONEY;
   116	                } else if (needsBPS > 0) {
   117	                    nextAction.disciplineTo = STUDENT_BPS;
   118	                }
   119	            } else if (extraBPS > 0) {
   120	                nextAction.disciplineFrom = STUDENT_BPS;
   121	                printf("%d, %d, %d, %d", needsMTV, needsMJ, needsBQN, needsMMONEY);
   122	                if (needsMTV > 0) {
   123	                    nextAction.disciplineTo = STUDENT_MTV;
   124	                } else if (needsMJ > 0) {
   125	                    nextAction.disciplineTo = STUDENT_MJ;
   126	                } else if (needsBQN > 0) {
   127	                    nextAction.disciplineTo = STUDENT_BQN;
   128	                } else if (needsMMONEY > 0) {
   129	                    nextAction.disciplineTo = STUDENT_MMONEY;
   130	                }
   131	            }
   132	            printf("Yes\n");
   133	            printf("Retraining from %d to %d\n", nextAction.disciplineFrom, nextAction.disciplineTo);
   134	            needsAction = 0;
   135	        } else {
   136	            printf("No\n");
   137	        }
   138	        }
   139	
   140	        if (needsAction) {
   141	        printf("start a spinoff?\n");
   142	        action testAction;
   143	        testAction.actionCode = START_SPINOFF;
   144	        if (isLegalAction(g, testAction)){
   145	            nextAction.actionCode = START_SPINOFF;
   146	            needsAction = 0;
   147	            printf("Yes\n");
   148	        } else {
   149	            printf("No\n");
   150	        }
   151	        }
   152	        
   153	
   154	
   155	        //Trading off loose MMONEY and MTV so they don't go do THDs
   156	  
   157	  
   158	
   159	        extraMTV = 0;
   160	        extraMMONEY = 0;
   161	        needsMTV = 0;
   162		needsMMONEY = 0;
   163	
   164	        checkExchanges(&extraMTV, &needsMTV, sMTV, 0, GENERAL_EXCHANGE);
   165	        checkExchanges(&extraMMONEY, &needsMMONEY, sMMONEY, 0, GENERAL_EXCHANGE);
   166	        if (needsAction) {
   167	        printf("enact THD prevention scheme?\n");
   168	        if ((extraMTV != 0 || extraMMONEY != 0)) {
   169	            nextAction.actionCode = RETRAIN_STUDENTS;
   170	            if (extraMMONEY > 0) {
   171	                nextAction.disciplineFrom = STUDENT_MMONEY;
   172	                nextAction.disciplineTo = STUDENT_MJ;
   173	            } else if (extraMTV > 0) {
   174	                nextAction.disciplineFrom = STUDENT_MTV;
   175			nextAction.disciplineTo = STUDENT_MJ;
   176	            }
   177	            printf("yes, good riddance!\n");
   178	            needsAction = 0;
   179	        } else {
   180	            printf("no\n");
   181	        }
   182	        }
   183	
   184	        //Otherwise pass
   185	        if (needsAction) {
   186	            printf("PASS!\n");
   187	            nextAction.actionCode = PASS;
   188	        }
   189	    }
   190	
   191	    return nextAction;
   192	}
   193	
   194	void checkExchanges(int *extra, int *needs, int has, int wants, int exchange) {
   195	    if (has - wants >= 0) {
   196	        *extra += (int)((has - wants)/exchange);
   197	    } else {
   198	        *needs -= (has - wants);
   199	    }
   200	}
