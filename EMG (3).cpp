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
	int gNum1, gNum2, gNum3;
	char gOp1, gOp2;
	int back;
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
void FRILL (); // File Reader Into linked List
void h2P();
void h2PDS ();
void h2POp();
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

void popAll(){
	if (head == NULL)return;
	
	playerdat* curr= head;
	while (curr!=NULL){
		playerdat* temp = curr;
		curr= curr->next;
		free(temp);
	}
	head=NULL;
}

	//Start of subgroup leaderboard linked list functions
	
	void FRILL(){
//			puts ("check in early FRILL");
		FILE* fp = fopen ("playerdata.txt","r");
		if (fp == NULL){
			return;
		}
		int tempScore;
		long arbPass;
		char tempName[100];
//			puts ("check in middle before pBV FRILL");
		while (fscanf (fp,"%[^#]#%ld#%d\n",tempName,&arbPass,&tempScore)==3){
//				puts ("check filescan repeat");
			pushByValue (tempName,tempScore);
		}
		
		
		
		fclose (fp);
//			puts ("check in end of FRILL");
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

void clearArr (char arr[],int N){
	for (int i=0; i  < N ; i++){
		arr[i]='\0';
	}
}

void Register () {
	system("cls");
    char userN[100];
    char userP[100];
    clearArr (userN,(sizeof(userN)/sizeof(userN[0])));
    clearArr (userP,(sizeof(userP)/sizeof(userP[0])));
    long hashedP;
    int nameWrong = 1;
    char tempN[100];
    clearArr(tempN,sizeof(tempN)/sizeof(tempN[0]));
    long tempP;
    int tempS;

   do{
  	  FILE *fp = fopen ("playerdata.txt","r");	
    	printf ("Insert your username (0\\ to return) >> ");
    	scanf ("%[^\n]",userN);getchar();
    	system("cls");
    	if (strcmp (userN,"0\\") == 0)return;
    	if (fp != NULL){
    		while (fscanf(fp,"%[^#]#%ld#%d\n",tempN,&tempP,&tempS)==3){
    		if (strcmp (userN,tempN)==0){
    			nameWrong = 1;
    			printf ("Username taken \n");
    			break;
			}else{
				nameWrong =0;
				strcpy (tempN,"");
				tempP=0;
				tempS=0;
			}
		}
	}else{
		nameWrong =0;
		strcpy (tempN,"");
		tempP=0;
		tempS=0;
	}
//		printf ("%s  %ld %d",tempN,tempP,tempS);
	fclose (fp);
	}while (nameWrong ==1);

	
	do {
    printf ("Insert your password (minimal 8 charcters) (0\\ to return) >> ");
    scanf ("%s",userP);getchar();
    if (strcmp (userP,"0\\") == 0)return;
    if (strlen(userP )<8){
        printf ("Invalid Password\n");
    }
    }while (strlen(userP)<8);
    hashedP = hashFunction (userP);
    fileAppend (userN, hashedP,0);
    return;
    getchar();
}

int login() {
	
	char userN[101],userP[100];
	system ("cls");
	int wrong= 0;
	FILE* fp;
	fp= fopen("playerdata.txt","r");
	if (fp == NULL){
		printf (" no player :< pls register, press anything to return");
		getch();
		return 1;
	}
	fclose (fp);
	long tempP;
	char tempN[100];
	int tempS;
	do{
	fp= fopen("playerdata.txt","r");
		for(int i=0;i<sizeof(userN)/sizeof(userN[0]);i++){
			userN[i] = '\0';
		}
		printf ("Insert your username >> ");
		scanf ("%[^\n]",userN);getchar();
		if (strcmp (userN,"0\\")==0){
			return 1;
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
//				fp= fopen("playerdata.txt","r"); <<<<----- here wrong pls fix || future orvin here ?????
					
			}
		}
//			printf ("%s\n",tempN);
//			printf ("%lld\n",tempP);
//			printf ("%d\n",tempS);
	fclose (fp);
		
		if (wrong == 1){
			system("cls");
			printf ("username not found ( 0\\ to return;)\n");
		}

	}while (wrong == 1);
	do{
	
		printf("Insert your password >>");
		scanf ("%s",userP);
		if (strcmp (userP,"0\\")==0){
			return 1 ;
		}
		if (hashFunction(userP)==tempP){
			printf ("herzlich willkommen herr %s",tempN);
			player.score=tempS;
			wrong =0;
		}else {
			system("cls");
			wrong =1;
			printf ("Wrong Password (0\\ to return)\n");
		}
	}while (wrong ==1);
	strcpy (player.playerName,tempN);
	player.score=tempS;
	getchar();    getchar();
	return 3;
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
//		printf ("temp Name : %s \t player name : %s",tempN,player.playerName);
//		printf (" %d\n\n score nya %d score playernya %d",strcmp(tempN,player.playerName),score,player.score);
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
	int wrong = 0;
	FRILL();
	playerdat* curr=head;
	system("cls");
//	while (curr->next!=NULL||curr!=NULL){
//		playerdat* temp= curr;
//		curr=curr->next;
//		free(temp);
//		temp=NULL;
//	}

	int i=1;

char slct [5];
	do{
		i=1;
		system("cls");
		for (int i =0;i<5;i++)slct[i]='\0';
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
		printf ("\n input \"0\" to return\n>>>> ");fgets(slct,sizeof(slct),stdin);
		switch (slct[0]){
			case '0': popAll(); return; break;
			default: wrong=1; break;
		}
	}while (wrong == 1);
	
}

//end
//start of game

int pauseMenu(){
	char slct[10];
	int wrong;
	int x;
	do{
		system("cls");
		clearArr (slct,sizeof(slct)/sizeof(slct[0]));
		printf ("GAME PAUSED\n");
		printf ("\n=================\n");
		printf ("1. RESUME\t2.EXIT\t\t3.HOW TO PLAY\n");
		if (wrong == 2)printf("Invalid input \n");
		wrong=0;
		printf (">>>");
		fgets (slct,sizeof(slct),stdin);
		switch (slct[0]){
			case '1':x=1;break;
			case '2':x=2;break;
			case '3':h2P();wrong=1;break;
			default : wrong =2;break;
		}
		if (strchr(slct,'\n')== NULL){
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
		slct[strcspn(slct, "\n")] = '\0';
		
	}while (wrong != 0);
	return x;
}

void h2POp (){
	int page =1;
	int MAXPAGE = 5;
	int back =0;
	char slct;
	int wrong=0;
	do{
		system("cls");
		switch (page){
			case 1 :
				printf("\nLevels\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("Level: ADDITION\n");
				printf ("-	This level only has adding operations in the questions.\n");
				printf ("-	Find the sum with the correct mathematical algorithm and input the value of the final answer.\n");
				break;
			case 2 :
				printf("\nLevels\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("Level: SUBTRACTION\n");
				printf ("-	This level only has subtracting operations in the questions.\n");
				printf ("-	Find the difference with the correct mathematical algorithm and input the value of the final answer.\n");
				break;
			case 3 :
				printf("\nLevels\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("Level: MULTIPLICATION\n");
				printf ("-	This level only has multiplying operations in the questions.\n");
				printf ("-	Find the product of the numbers with the correct mathematical algorithm and input the value of the final answer.\n");
				break;
			case 4 :
				printf("\nLevels\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("Level: DIVISION\n");
				printf ("-	This level only has dividing operations in the questions.\n");
				printf ("-	Find the quotient of the numbers with the correct mathematical algorithm and input the value of the final answer.\n");
				break;
			case 5 :
				printf("\nLevels\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("Level: MIXED\n");
				printf ("-	This level has all adding, subtracting, multiplying, and dividing operations in the questions.\n");
				printf ("-	Calculate the final answer using the correct mathematical algorithm, then input the final answer. \n");
				printf ("-	multiplying and dividing are done before adding and subtracting.\n");
				break;
			default : break;
		}
		printf ("=======================\n");
		if(wrong ==1) printf ("invalid input (input is A, D or 0)\n");
		printf ("Prev page [A] | Next page [D] | Back [0]\n >>> ");
		if (back != 1)slct = getch();
		if (slct == 'A'||slct == 'a'){
			wrong =0;
			if (page <= 1)page = 1;
			if (page > 1)page--;
		}else if (slct =='D'||slct == 'd'){
			wrong=0;
			if (page >= MAXPAGE )page =  MAXPAGE ;
			if(page <MAXPAGE)page++;
		}else if (slct == '0'){
			page =0;
			back = 1;
		}else{
			wrong =1;
		}
	}while (back != 1 );
	return;
}

void h2PDS(){
		int page =1;
	int MAXPAGE = 5;
	int back =0;
	char slct;
	int wrong=0;
	do{
		system("cls");
		switch (page){
			case 1 :
				printf("\nDifficulties & Operators\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("Difficulty: EASY \n");
				printf ("-	Two integers, one mathematical operator.\n");
				printf ("-	The numbers are always positive and round.\n");
				printf ("-	The integers in the questions are from 1 to 10.\n");
				printf ("-	Every question you answer correctly will add 5 to your score.\n");
				break;
			case 2 :
				printf("\nDifficulties & Operators\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("Difficulty: MEDIUM \n");
				printf ("-	Two integers, one mathematical operator.\n");
				printf ("-	The numbers in the questions are still positive and round, but the answer may be negative or decimal.\n");
				printf ("-	For decimal answers, round it to the first two decimals. \n");
				printf ("-	The integers in the questions are from 1 to 50 for Addition, Subtraction, and Division and 1 to 20 for Multiplication.\n");
				printf ("-	Every question you answer correctly will add 20 to your score.\n");
				break;
			case 3 :
				printf("\nDifficulties & Operators\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("Difficulty: HARD \n");
				printf ("-	Two integers, one mathematical operator.\n");
				printf ("-	The numbers in the questions are no longer always positive but still round.\n");
				printf ("-	The integers in the questions are from -50 to 100 for Addition and Subtraction, -20 to 30 for Multiplication, and -20 to 100 for Division. \n");
				printf ("-	Every question you answer correctly will add 30 to your score.\n");
				break;
			case 4 :
				printf("\nDifficulties & Operators\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("Difficulty: EXPERT \n");
				printf ("-	Three integers, two mathematical operators.\n");
				printf ("-	The numbers in the questions range from -50 to 50 regardless of the operator.\n");
				printf ("-	The integers in the questions are from 1 to 10.\n");
				printf ("-	Every question you answer correctly will add 50 to your score.\n");
				break;
			case 5 :
				printf("\nDifficulties & Operators\n");
				printf ("Page %d\n", page);
				printf ("=======================\n");
				printf("-	Difficulty: SANDBOX \n");
				printf ("-	Two integers, one mathematical operator.\n");
				printf ("-	Then numbers in the questions range from 1 to 10 regardless of the operator. \n");
				printf ("-	This difficulty has no timer and won't affect your score.\n");
				break;
			default : break;
		}
		printf ("=======================\n");
		if(wrong ==1) printf ("invalid input (input is A, D or 0)\n");
		printf ("Prev page [A] | Next page [D] | Back [0]\n >>> ");
		if (back != 1)slct = getch();
		if (slct == 'A'||slct == 'a'){
			wrong =0;
			if (page <= 1)page = 1;
			if (page > 1)page--;
		}else if (slct =='D'||slct == 'd'){
			wrong=0;
			if (page >= MAXPAGE )page =  MAXPAGE ;
			if(page <MAXPAGE)page++;
		}else if (slct == '0'){
			page =0;
			back = 1;
		}else{
			wrong =1;
		}
	}while (back != 1 );
	return;
}

void h2PGM(){

	int back =0;
	char slct;
	int wrong=0;
	do{
		system("cls");
		printf("\nGame Mechanics\n");
		printf ("=======================\n");
		printf("HOW TO PLAY\n");
		printf ("-	Calculate the answer before the timer runs out.\n");
		printf ("-	Input the numbers based on your answer, then ppress Enter to submit.\n");
		printf ("-	There are 4 operators, 5 levels, and 5 difficulties.\n");
		printf ("-	For decimals, use period (.) for the separator\n");
		printf ("-	Round the decimals to the first two decimal digits.\n");
		printf ("=======================\n");
		if(wrong ==1) printf ("invalid input (input is 0)\n");
		printf ("Back [0]\n >>> ");
		if (back != 1)slct = getch();
		 if (slct == '0'){
			back = 1;
		}else{
			wrong =1;
		}
	}while (back != 1 );
	return;
}

void h2P(){
	
	char slct [10];
	int wrong = 0,stop = 0; 
	
	do{
			system ("cls");
	
		printf ("\n HOW TO PLAY\n");
		printf ("=======================\n");
		printf("\n1. Game Mechanics");
		printf("\n2. Operators");
		printf("\n3. Difficulties & Sandbox");
		printf("\n4. Return");
		if (wrong ==1)printf("\n\n invalid selection\n");
		wrong = 0;
		printf("\n >>> ");
		fgets(slct,sizeof(slct),stdin);
		switch (slct[0]){
			case '1':h2PGM();break;
			case '2':h2POp();break;
			case '3':h2PDS();break;
			case '4': stop = 1; return ;break;
			default: stop = 0; wrong = 1; break;
		}
	}while (stop == 0);
}

void gameScreen (){
	system ("cls");
	fileCopyr();
	gameQ gSQ;
		gSQ.gAns=0;
		gSQ.gNum1=0;
		gSQ.gNum2=0;
		gSQ.gNum3=0;
	long ans=-1;
	int fail,ansWrongState;
	int lvl,failstate=0;
	int valid=1;
	int scorePlus;
	int tempCurrTime,tempStartTime;
	 double jwban;
	long long timeStart=(long long)time(NULL);
	long long timer=120;
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
	if (lvl ==6)return;
	diff = gameBD();	
	if (diff == 6)return;
	switch (diff){
		case 1:strcpy(difficulty,"Easy");scorePlus=5;break;
		case 2:strcpy(difficulty,"Medium");scorePlus=20;break;
		case 3:strcpy(difficulty,"Hard");scorePlus=30;break;
		case 4:strcpy(difficulty,"Expert");scorePlus=50;break;
		case 5:strcpy(difficulty,"Sandbox");scorePlus=0;break;
	}

	if (diff == 5) timer = LONG_MAX;
	gSQ = gameGen(lvl,diff);
	int back=0;
	while (failstate == 0&& back!=2){
		system ("cls");
		int timeNow = (long long)time(NULL);
		if ((timeNow-timeStart)>=1){
			timer--;
			timeStart=timeNow;
			printf ("%lld\n",timer);
			if (timer<1){		
				//printf ("times up boy time to die\n");
				if (score>player.score){
					printf ("New Record of %d from %d\n", score, player.score);
					filePaster(score);
				}else{
					printf ("Congrats %s, you got: %d , current High Score: %d\n",player.playerName,score, player.score);
					filePaster(player.score);	
				}
				Sleep(1000);
				puts ("\n\nPress any key to return\n\n");
				getch();
				
				return;
				
			}
		}
		printf ("%s\t\t%d\t\t%lld\n\n",difficulty,score,timer);
		switch (diff){
			case 1:
			case 2:
			case 3:
			case 5:
				printf ("%d\t\t%c\t\t%d\n\n",gSQ.gNum1,gSQ.gOp1,gSQ.gNum2);
				break;
			case 4:
				printf ("%d\t\t%c\t\t%d\t\t%c\t\t%d\n\n",gSQ.gNum1,gSQ.gOp1,gSQ.gNum2,gSQ.gOp2,gSQ.gNum3);
				break;
		}
		
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
						score += scorePlus;
						gSQ = gameGen(lvl,diff);
					}
				}
				for (arbtempi=0;arbtempi<sizeof(inpArr)/sizeof(inpArr[0]);arbtempi++){
					inpArr[arbtempi]='\0';
				}
				index =0;
			}else if(temp == '\e'){
				back = pauseMenu();
				
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	char slct[10];
	int wrong=0,x;
	do{
		clearArr(slct,sizeof(slct)/sizeof(slct[0]));
		
		system ("cls");
		printf("Choose Level (1 - 5)\n");
		printf("1. Basic Additon\n");
		printf("2. Basic Subtraction\n");
		printf("3. Basic Multiplication\n");
		printf("4. Basic Division\n");
		printf("5. Mixed\n");
		printf("6. return\n");
		if (wrong==1) printf ("Wrong input\n");
		wrong=0;
		printf (">>");
	
		fgets (slct,sizeof(slct),stdin);
		switch (slct[0]){
			case '1':x=1;break;
			case '2':x=2;break;
			case '3':x=3;break;
			case '4':x=4;break;
			case '5':x=5;break;
			case '6':x=6;break;
			default : wrong =1;break;
		}
				if (strchr(slct,'\n')== NULL){
				int c;
				while ((c = getchar()) != '\n' && c != EOF);

		}
			slct[strcspn(slct, "\n")] = '\0';

	} while (wrong==1);
	return x;
}



int gameBD(){	
	char slct[10];
	int wrong=0,x;
	do{

		clearArr(slct,sizeof(slct)/sizeof(slct[0]));
		system ("cls");
		printf ("1. Easy\n");
		printf ("2. Medium\n");
		printf ("3. Hard\n");
		printf ("4. Expert\n");
		printf ("5. Sandbox\n");
		printf ("6. Return\n");
		if (wrong==1) printf ("Wrong input\n");
		wrong =0;
		printf (">>");
	
		fgets (slct,sizeof(slct),stdin);
		switch (slct[0]){
			case '1':x=1;break;
			case '2':x=2;break;
			case '3':x=3;break;
			case '4':x=4;break;
			case '5':x=5;break;
			case '6':x=6;break;
			default : wrong =1;break;
		}
		if (strchr(slct,'\n')== NULL){
		int c;
		while ((c = getchar()) != '\n' && c != EOF);

		}
		slct[strcspn(slct, "\n")] = '\0';

	} while (wrong==1);
	return x;
}

gameQ gameGen(int op, int diff){
	gameQ gGQ;
	
	int num1=0, num2=0, num3=0, op1=0,op2=0;
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
		//RNG interval increased and reaches negative
		case 3:if(op == 1 || op == 2){
				num1 = mathRand(-50, 100);
				num2 = mathRand(-50, 100);
				op1 = op;
			} else if (op == 3){
				num1 = mathRand(-20, 30);
				num2 = mathRand(-20, 30);	
				op1 = op;		
			} else if (op == 4){
				num1 = mathRand(-20, 100);
				num2 = mathRand(-10, 30);
				op1 = op;
				if (num2 == 0){
					num2 += mathRand(1, 5);
				}
			} else if (op == 5){
				op1 = mathRand(1,4);
				if(op1 == 1 || op1 == 2){
					num1 = mathRand(-50, 100);
					num2 = mathRand(-50, 100);
				} else if (op1 == 3){
					num1 = mathRand(-20, 30);
					num2 = mathRand(-20, 30);		
				} else if (op1 == 4){
					num1 = mathRand(-20, 100);
					num2 = mathRand(-10, 30);
					if (num2 == 0){
						num2 += mathRand(1, 5);
					}
				}
			}break;
		
		//Expert:
		//3 num 2 op
		//same Interval regardles the lvl
		case 4:
			num1 = mathRand(-50, 50);
			num2 = mathRand(-50, 50);
			num3 = mathRand(-50, 50);
			if(op != 5){
				op1 = op;
				op2 = op;
			} else if (op == 5){
				op1 = mathRand(1,4);
				op2 = mathRand(1,4);
			}break;
		
		//Sandbox
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
	switch (diff){
		case 1:
		case 2:
		case 3:
		case 5:
			gGQ.gOp1 =mathOp(op1);
			gGQ.gNum1 =num1;
			gGQ.gNum2 =num2;
			gGQ.gAns=calc(num1, num2, op1);
			break;
		case 4:
			gGQ.gOp1 = mathOp(op1);
			gGQ.gOp2 = mathOp(op2);
			gGQ.gNum1 = num1;
			gGQ.gNum2 = num2;
			gGQ.gNum3 = num3;
			if ((op1==3)||(op1==4)){
				//num1 (*)(/) num2 (+)(-)(*)(/) num3
				gGQ.gAns = calc(num1, num2, op1);
				gGQ.gAns = calc(gGQ.gAns, num3, op2);
			}else if((op2==3)||(op2==4)){
				//num1 (+)(-) num2 (*)(/) num3
				gGQ.gAns = calc(num2, num3, op2);
				gGQ.gAns = calc(num1, gGQ.gAns, op1);
			}else{
				//num1 (+)(-) num2 (+)(-) num3
				gGQ.gAns = calc(num1, num2, op1);
				gGQ.gAns = calc(gGQ.gAns, num3, op2);
			}break;
	}
	return gGQ;
}

void playerLogOut (){
	popAll();
	for (int i = 0 ; i< (sizeof(player.playerName)/sizeof(player.playerName[0]));i++){
		player.playerName[i]='\0';
	}
	player.score=0;
}

int postEntryMenu(){
	int state=0;
	char slct[10];
	do{
		
		system ("cls");
		for (int i =0;i<5;i++)slct[i]='\0';
		printf ("WELCOME TO ELEMENTARY MATH GAME %s \n",player.playerName);
		printf ("\n=================================\n");
		printf ("1. Play\n");
		printf ("2. How to play\n");
		printf ("3. Leaderboard\n");
		printf ("4. Logout\n");
		printf ("5. Exit and Logout\n");
		if (state == 2)printf ("\nIncorrect input (1 to 5)\n");
		printf (" >>>>>>>> ");
	
		fgets(slct,sizeof(slct),stdin);
		

		switch (slct[0]){
			case '1':state = 3;break; // to game
			case '2':state = 4; break; // how to play
			case '3':state = 1;break; 	// to leaderboard
			case '4':state = 5; break; // to logout
			case '5':state =0;break; // to logout and exit
			default:state = 2; break;
		}
		if (strchr(slct,'\n')== NULL){
			int c;
			while (c != '\n'&& c != EOF){
				c= getchar();
			}
		}
		slct[strcspn(slct, "\n")] = '\0';
		switch (state){
			case 1:leaderboard();break;
			case 2:break;
			case 3:gameScreen();break;
			case 4:h2P();break;
			case 5:playerLogOut();return 1; break;
			case 0:playerLogOut();return 0;break;
			default:break;
		}
	}while(state != 0);
		
	return 1;
}

void preEntryMenu (){
	int state=0;
	char slct[10];
	do{
		
		system ("cls");
		for (int i =0;i<5;i++)slct[i]='\0';
		printf ("WELCOME TO ELEMENTARY MATH GAME %s\n",player.playerName);
		printf ("\n=================================\n");
		printf ("1. Login\n");
		printf ("2. Register\n");
		printf ("3. Leaderboard\n");
		printf ("4. How to play\n");
		printf ("5. Exit\n");
		if (state == 2)printf ("\nIncorrect input (1 to 5)\n");
		printf (" >>>>>>>> ");
	
		fgets(slct,sizeof(slct),stdin);
		

		switch (slct[0]){
			case '1':state =login();break;
			case '2':state =1;Register();break;
			case '3':state = 1;leaderboard();break;
			case '4':state = 1;h2P(); break;
			case '5':state =0;/*exitMenu()*/break;
			default:state = 2; break;
		}
		if (strchr(slct,'\n')== NULL){
			int c;
			while (c != '\n'&& c != EOF){
				c= getchar();
			}
		}
		slct[strcspn(slct, "\n")] = '\0';
		if (state == 3) {
			state = postEntryMenu();

		}
	}while(state != 0);
		
	return;
}

int main(){
	srand(time(NULL));

////	int lvl;
//	Register ();
//	login();
////	getchar();
////	lvl = levelMenu();
////	gameGen(lvl);
//	gameScreen();
//	leaderboard();
preEntryMenu();
	return 0;
}


// catatan: buat bisa return pas mau maen (keknya harus ganti sistem gamescree kan tadinya milih difficulty didalem, biar bisa back taro luar)


