#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <Ctype.h>
#include <conio.h>



//Start of Struct declaration

typedef struct player {
	char playerName[100];
	int score;
	struct player* next;
}playerdat;
typedef struct gameQ{
	double gAns;
	int gNum1, gNum2;
	char gOp;
}gameQ;

//end



//Start of function declaration

int gameBD(); 	//game by difficulty
double calc(double a, double b, int op);
int mathRand(int min, int max);
char mathOp(int op);// math Operator
int levelMenu();
void fileAppend (char *name , long hashP, int score);
gameQ gameGen(int op,int diff);
double ansCheck (char *p);
playerdat player;
long hashFunction (char *p);
void leaderboardFRILL (); //leaderboard File Reader Into linked List
void sMenu (); //starting menu
//end



//Start of linked list operation and creation

playerdat* tail=NULL;
playerdat* head=NULL;

playerdat* createNode (char *p , int score){
	playerdat* newNode = (playerdat*)malloc (sizeof(playerdat));
	strcpy (newNode->playerName, p);
	newNode->score=score;
	newNode->next=NULL;
	return newNode;
}

void pushT(playerdat* newNode){
	tail->next=newNode;
	tail=newNode;
	tail->next=NULL;
}

void pushH(playerdat* newNode){
	newNode->next=head;
	head=newNode; 
}

void pushByValue (char *p, int score){
//		puts ("check early pBV b4 createNode");
	playerdat* newNode = createNode (p,score);
//			puts ("check early pBV after createnode");
	if (head==NULL){
//			puts ("check head null pre");
		head=tail=newNode;
//			puts ("check head null after");
	}else if (score > head->score){
//			puts ("check push head pre");
		pushH(newNode);
//			puts ("check push head after");
	}else if (score < tail->score){
		printf ("%d and tail score of %d \n",score, tail->score);
//			puts ("check push tail pre");
		pushT (newNode);
//				puts ("check push tail after");
	}else {
//			puts ("check else pre");
		playerdat* temp = head;
   		if (temp->score == score){
			newNode->next=temp->next;
			temp->next=newNode;
		return;
		}
		while (score < temp->next->score){
			temp = temp->next;
//				puts ("check else after");
		}
		newNode->next= temp->next;
		temp->next=newNode;
	}
//		puts ("check end pBV");
}

	//Start of subgroup leaderboard linked list functions
	
	void leaderboardFRILL(){
			puts ("check in early FRILL");
		FILE* fp = fopen ("playerdata.txt","r");
		if (fp == NULL){
			return;
		}
		int tempScore;
		long arbPass;
		char tempName[100];
			puts ("check in middle before pBV FRILL");
		while (fscanf (fp,"%[^#]#%ld#%d\n",tempName,&arbPass,&tempScore)==3){
				puts ("check filescan repeat");
			pushByValue (tempName,tempScore);
		}
		
		
		
		fclose (fp);
			puts ("check in end of FRILL");
		return;
	}
	
	//subgroup end
	
//end



//Start of input validation

 double ansCheck (char *p){
	char *end;
	if (*p== '\0'){
		return LONG_MIN;
	}
	long double value =strtod(p,&end);
	if (*end == '\0'){
		return value;
	}else{
		return LONG_MIN;
	}
}

//end



//Start of Pre-entrty

void Register () {
	system("cls");
    char userN[100];
    char userP[100];
    long hashedP;
    printf ("Insert your username >> ");
    scanf ("%[^\n]",userN);getchar();
    do {
    printf ("Insert your password (minimal 8 charcters) >> ");
    scanf ("%s",userP);getchar();
    if (strlen(userP )<8){
        printf ("Invalid Password\n");
    }
    }while (strlen(userP)<8);
    hashedP = hashFunction (userP);
    fileAppend (userN, hashedP,0);
    return;
    getchar();
}

void login() {
	char userN[101],userP[100];
	system ("cls");
	int wrong;
	FILE* fp;
	fp= fopen("playerdata.txt","r");
	if (fp == NULL){
		printf (" no player :< pls register");
		return;
	}
	long tempP;
	char tempN[100];
	int tempS;
	do{
		for(int i=0;i<sizeof(userN)/sizeof(userN[0]);i++){
			userN[i] = '\0';
		}
		printf ("Insert your username >> ");
		scanf ("%[^\n]",userN);getchar();
		if (strcmp (userN,"0\\")==0){
			return;
		}
		while (fscanf(fp,"%[^#]#%ld#%d\n",tempN,&tempP,&tempS)==3){
		
			if (strcmp(userN,tempN)==0){
				wrong =  0;
				break;
			}else {
				wrong =1;
				strcpy (tempN,"");
				tempP=0;
				tempS=0;
//				fclose (fp);
//				fp= fopen("playerdata.txt","r"); <<<<----- here wrong pls fix
					
			}
		}
			printf ("%s\n",tempN);
			printf ("%lld\n",tempP);
			printf ("%d\n",tempS);
		if (wrong == 1){
			printf ("username not found ( 0\\ to return;)\n");
		}
	}while (wrong == 1);
	do{

		printf("Insert your password >>");
		scanf ("%s",userP);
		if (strcmp (userP,"0\\")==0){
			return;
		}
		if (hashFunction(userP)==tempP){
			printf ("herzlich willkommen herr %s",tempN);
			player.score=tempS;
			wrong =0;
		}
		if (wrong ==1){
			printf ("Wrong Password (0\\ to return)\n");
		}
	}while (wrong ==1);
	strcpy (player.playerName,tempN);
	player.score=tempS;
	getchar();    getchar();
	return;
}

long hashFunction (char *p){
    long temp=0;
    long h=5381;
    while ( temp = *p++){
        h = (h<<5)+h+temp;
    }
    return h;
}

//end



// Start of file processing

void fileWriter (char *name , long hashP, int score){
	FILE *fp;
	fp = fopen ("playerdata.txt","w");
	fprintf (fp, "%s#%lld#%d\n",name,hashP,score);
	fclose (fp);
}

void fileAppend (char *name , long hashP, int score){
	FILE *fp;
	fp = fopen ("playerdata.txt","a");
	if (fp == NULL){
		fileWriter (name,hashP,score);
	}else {
		fprintf (fp, "%s#%lld#%d\n",name,hashP,score);
	}
	fclose (fp);
}

void fileCopyWriter (char *name , long hashP, int score){
	FILE *fp;
	fp = fopen ("playerdatatemp.txt","w");
	fprintf (fp, "%s#%lld#%d\n",name,hashP,score);
	fclose (fp);
}

void fileCopyAppend (char *name , long hashP, int score){
	FILE *fp;
	fp = fopen ("playerdatatemp.txt","a");
	if (fp == NULL){
		fileWriter (name,hashP,score);
	}else {
		fprintf (fp, "%s#%lld#%d\n",name,hashP,score);
	}
	fclose (fp);
}

void fileCopyr(){
	FILE *fp;
	char tempN[100];
	long tempP;
	int tempS;
	int i=0;
	fp = fopen ("playerdata.txt","r");
	if (fp == NULL){
		return;
	}else {
		while (fscanf(fp,"%[^#]#%ld#%d\n",tempN,&tempP,&tempS)==3){
			if (i==0){
				fileCopyWriter(tempN,tempP,tempS);
				i++;
			}else{			
				fileCopyAppend(tempN,tempP,tempS);
			}
		}
	}
	fclose (fp);
	return;
}

void filePaster(int score){
	char tempN[100];
	long tempP;
	int tempS;
	FILE* fpr;
	int i = 0;
	fpr = fopen ("playerdatatemp.txt","r");
	while (fscanf(fpr,"%[^#]#%ld#%d\n",tempN,&tempP,&tempS)==3){
		printf ("temp Name : %s \t player name : %s",tempN,player.playerName);
		printf (" %d\n\n score nya %d score playernya %d",strcmp(tempN,player.playerName),score,player.score);
		if (i==0){
			if (strcmp(tempN,player.playerName)==0){
				fileWriter(tempN,tempP,score);
			}else {
				fileWriter(tempN,tempP,tempS);
			}
		i++;
		}else{
			if (strcmp(tempN,player.playerName)==0){
				fileAppend(tempN,tempP,score);
			}else {
				fileAppend(tempN,tempP,tempS);
			}
			
		}
	}
	fclose (fpr);
	return;
}

//end



//Leaderboard code

void leaderboard (){
	playerdat* curr=head;
//	while (curr->next!=NULL||curr!=NULL){
//		playerdat* temp= curr;
//		curr=curr->next;
//		free(temp);
//		temp=NULL;
//	}

	int i=1;
	puts ("check preFRILL");
	leaderboardFRILL();
	puts ("check postFRILL");
	curr=head;
	if (curr== NULL){
		puts ("Leaderbioar empy");
	}else{
	
		while (curr->next!=NULL){
			printf ("no: %d, nama : %s, score: %d\n",i,curr->playerName,curr->score);
			curr=curr->next;
			i++;
//			Sleep(1000);

		}
			
		printf ("no: %d, nama : %s, score: %d\n",i,curr->playerName,curr->score);

	}
}

//end
//start of game

void gameScreen (){
	system ("cls");
	fileCopyr();
	gameQ gSQ;
		gSQ.gAns=0;
		gSQ.gNum1=0;
		gSQ.gNum2=0;
	long ans=-1;
	int fail,ansWrongState;
	int lvl,failstate=0;
	int valid=1;
	int tempCurrTime,tempStartTime;
	 double jwban;
	long long timeStart=(long long)time(NULL);
	long long timer=10;
	char difficulty [100];
	int arbtempi;
	char inpArr[100];
	for (arbtempi=0;arbtempi<sizeof(inpArr)/sizeof(inpArr[0]);arbtempi++){
		inpArr[arbtempi]='\0';
	}
	inpArr[0]= '\0';
	int diff,score,index;
	index=0;

	score = 0;
	timer++;
	lvl = levelMenu();
	diff = gameBD();	
	switch (diff){
		case 1:strcpy(difficulty,"Easy");break;
		case 2:strcpy(difficulty,"Medium");break;
		case 3:strcpy(difficulty,"Hard");break;
		case 4:strcpy(difficulty,"Expert");break;
		case 5:strcpy(difficulty,"Sandbox");break;
	}

	if (diff == 5) timer = LONG_MAX;
	gSQ = gameGen(lvl,diff);
	while (failstate == 0){
		system ("cls");
		int timeNow = (long long)time(NULL);
		if ((timeNow-timeStart)>=1){
			timer--;
			timeStart=timeNow;
			printf ("%lld\n",timer);
			if (timer<1){		
				printf ("times up boy time to die\n");
				if (score>player.score){
					printf ("New Record of %d from %d", score, player.score);
					filePaster(score);
				}else{
					filePaster(player.score);	
				}
				puts ("Press any key to return\n\n");
				getch();
				Sleep(1000);
				return;
				
			}
		}
		printf ("%s\t\t%d\t\t%lld\n\n",difficulty,score,timer);
		printf ("%d\t\t%c\t\t%d\n\n",gSQ.gNum1,gSQ.gOp,gSQ.gNum2);
		
		printf (">> %s",inpArr);
		if (_kbhit()){
			char temp = getch();
			if (temp == '\b'){
				if(index >0){
					inpArr[index-1]='\0';
					index--;
				}
			}else if (temp == '\r'){
				jwban = ansCheck (inpArr);

				if (jwban == LONG_MIN){
					valid=0;
					tempStartTime= time (NULL);
					
				}else {
					printf ("\n\n%lld",jwban);
					ans = jwban;
					if (jwban != gSQ.gAns){
						timer = timer-5;
						ansWrongState =1;
						tempStartTime= time (NULL);
					}else{
						score = score +10;
						gSQ = gameGen(lvl,diff);
					}
				}
				for (arbtempi=0;arbtempi<sizeof(inpArr)/sizeof(inpArr[0]);arbtempi++){
					inpArr[arbtempi]='\0';
				}
				index =0;
			}else{
				inpArr[index]=temp;
				index++;
			}
		}
		
			gameGen(lvl,diff);
		if (valid == 0){
			printf ("\n Invalid Number!");
			int tempCurrTime = time(NULL);
			if ((tempCurrTime-tempStartTime)==2){
				valid =1;
			}
			
		}
		if (ansWrongState == 1){
			printf ("\n Wrong answer!");
		//	printf ("\n Wrong answer! your answer was % lf correct is %lf",jwban,gSQ.gAns);
			int tempCurrTime = time(NULL);
			if ((tempCurrTime-tempStartTime)==2){
				ansWrongState =0;
			}
			
		}

	}
	return;
}

//end



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//Start of GUI

void sMenu () {
	printf ("Elementary Math Gayme\n");
	printf ("1. Login\n");
	printf ("2. Register\n");
	printf ("3. Leaderboard\n");
	printf ("4.	How to play\n");
	printf ("5.	About us\n");
	printf ("6. Exit\n");
	
}

//End of GUI



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EPSILON 0.000000001


double calc(double a, double b, int op){
	double ans;
	if (op == 1){						// op = 1 -> penjumlahan
		ans = a + b;
	}else if (op == 2){					// op = 2 -> pengurangan
		ans = a - b;
	}else if (op == 3){					// op = 3 -> perkalian
		ans = a * b;
	}else if (op == 4){					// op = 4 -> pembagian
		ans = a / b;
		ans = round(ans * 100) / 100;	// membulatkan ke 2 digit desimal
	}
	return ans;
}

// random number (integer) generator
int mathRand(int min, int max){
	return ((rand()%(max - min + 1)) + min);
}

char mathOp(int op){
	char oP;
	switch (op){
		case 1:
			oP = '+';
			break;
		case 2:
			oP = '-';
			break;
		case 3:
			oP = '*';
			break;
		case 4:
			oP = '/';
			break;
		default:
			break;
	}
	return oP;
}

int levelMenu(){
	system ("cls");
	int lvl;
	printf("Choose Level (1 - 5)\n");
	printf("1. Basic Additon\n");
	printf("2. Basic Subtraction\n");
	printf("3. Basic Multiplication\n");
	printf("4. Basic Division\n");
	printf("5. Mixed\n");
	printf(">> ");
	scanf("%d", &lvl);
	return lvl;
}

//void gameCase(int lvl){
//	switch (lvl){
//		case 1:
//			break;
//		case 2:
//			break;
//		case 3:
//			break;
//		case 4:
//			break;
//		case 5:
//			break;
//		default:
//			break;
//	}
//	return;
//}
int gameBD(){
	system ("cls");
	int x;
	int slct, wrong;
	printf ("1. Easy\n");
	printf ("2. Medium\n");
	printf ("3. Hard\n");
	printf ("4. Expert\n");
	printf ("5. Sandbox\n");
	printf (">>");
	do{
		scanf ("%d",&slct);
		switch (slct){
			case 1:x=1;break;
			case 2:x=2;break;
			case 3:x=3;break;
			case 4:x=4;break;
			case 5:x=5;break;
			default: wrong =1;break;
		}
	} while (wrong==1);
	return x;
}

gameQ gameGen(int op, int diff){
	gameQ gGQ;
	
	int num1=0, num2=0, op1=0;
	switch (diff){
		//Easy: no decimal, always positive
		case 1:if(op == 1 || op == 2){
				num1 = mathRand(1, 10);
				num2 = mathRand(1, 10);
				op1 = op;
				if ((op==2) && (num1<num2)){
					//switch value
					num1 = num1+num2;
					num2 = num1-num2;
					num1 = num1-num2;
				}
			} else if (op == 3){
				num1 = mathRand(1, 10);
				num2 = mathRand(1, 10);	
				op1 = op;		
			} else if (op == 4){
				num1 = mathRand(1, 10);
				num2 = mathRand(1, 10);
				num1 = num1 + num2 - (num1%num2);
				op1 = op;
			} else if (op == 5){
				op1 = mathRand(1,4);
				if(op1 == 1 || op1 == 2){
					num1 = mathRand(1, 10);
					num2 = mathRand(1, 10);
					if ((op==2) && (num1<num2)){
						//switch value
						num1 = num1+num2;
						num2 = num1-num2;
						num1 = num1-num2;
					}
				} else if (op1 == 3){
					num1 = mathRand(1, 10);
					num2 = mathRand(1, 10);		
				} else if (op1 == 4){
					num1 = mathRand(1, 10);
					num2 = mathRand(1, 10);
					num1 = num1 + num2 - (num1%num2);
				}
			}break;
			
		//Medium:
		//interval RNG increased
		//negative ans unlocked in subtraction
		//devision ans not always round, up to 1st 2 dec
		case 2:if(op == 1 || op == 2){
				num1 = mathRand(1, 50);
				num2 = mathRand(1, 50);
				op1 = op;
			} else if (op == 3){
				num1 = mathRand(1, 20);
				num2 = mathRand(1, 15);	
				op1 = op;		
			} else if (op == 4){
				num1 = mathRand(1, 50);
				num2 = mathRand(1, 20);
				op1 = op;
			} else if (op == 5){
				op1 = mathRand(1,4);
				if(op1 == 1 || op1 == 2){
					num1 = mathRand(1, 50);
					num2 = mathRand(1, 50);
				} else if (op1 == 3){
					num1 = mathRand(1, 20);
					num2 = mathRand(1, 15);		
				} else if (op1 == 4){
					num1 = mathRand(1, 50);
					num2 = mathRand(1, 20);
				}
			}break;
			
		//Hard:
		//RNG interval increased
		case 3:if(op == 1 || op == 2){
				num1 = mathRand(1, 100);
				num2 = mathRand(1, 100);
				op1 = op;
			} else if (op == 3){
				num1 = mathRand(1, 30);
				num2 = mathRand(1, 30);	
				op1 = op;		
			} else if (op == 4){
				num1 = mathRand(1, 100);
				num2 = mathRand(1, 30);
				op1 = op;
			} else if (op == 5){
				op1 = mathRand(1,4);
				if(op1 == 1 || op1 == 2){
					num1 = mathRand(1, 100);
					num2 = mathRand(1, 100);
				} else if (op1 == 3){
					num1 = mathRand(1, 30);
					num2 = mathRand(1, 30);		
				} else if (op1 == 4){
					num1 = mathRand(1, 100);
					num2 = mathRand(1, 30);
				}
			}break;
		
		//Expert:
		//3 num 2 op
		case 4:if(op == 1 || op == 2){
				num1 = mathRand(1, 10);
				num2 = mathRand(1, 10);
				op1 = op;
			} else if (op == 3){
				num1 = mathRand(1, 10);
				num2 = mathRand(1, 10);	
				op1 = op;		
			} else if (op == 4){
				num1 = mathRand(1, 10);
				num2 = mathRand(1, 10);
				op1 = op;
			} else if (op == 5){
				op1 = mathRand(1,4);
				if(op1 == 1 || op1 == 2){
					num1 = mathRand(1, 10);
					num2 = mathRand(1, 10);
				} else if (op1 == 3){
					num1 = mathRand(1, 10);
					num2 = mathRand(1, 10);		
				} else if (op1 == 4){
					num1 = mathRand(1, 10);
					num2 = mathRand(1, 10);
				}
			}break;
		case 5:if(op == 1 || op == 2){
				num1 = mathRand(1, 10);
				num2 = mathRand(1, 10);
				op1 = op;
			} else if (op == 3){
				num1 = mathRand(1, 10);
				num2 = mathRand(1, 10);	
				op1 = op;		
			} else if (op == 4){
				num1 = mathRand(1, 10);
				num2 = mathRand(1, 10);
				op1 = op;
			} else if (op == 5){
				op1 = mathRand(1,4);
				if(op1 == 1 || op1 == 2){
					num1 = mathRand(1, 10);
					num2 = mathRand(1, 10);
				} else if (op1 == 3){
					num1 = mathRand(1, 10);
					num2 = mathRand(1, 10);		
				} else if (op1 == 4){
					num1 = mathRand(1, 10);
					num2 = mathRand(1, 10);
				}
			}break;


		}// make game by difficulty by using switch case 
		gGQ.gOp =mathOp(op1);
		gGQ.gNum1 =num1;
		gGQ.gNum2 =num2;
		gGQ.gAns=calc(num1, num2, op1);
		
	return gGQ;
}

int main(){
	srand(time(NULL));
//	int lvl;
	Register ();
	login();
//	getchar();
//	lvl = levelMenu();
//	gameGen(lvl);
	gameScreen();
	leaderboard();
	return 0;
}
