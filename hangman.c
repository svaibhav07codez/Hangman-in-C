/* PROJECT AGENDA: To create a program to play Hangman */
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>


void displdboard();		//TO DISPLAY LEADERBOARD
void boardcheck();		//TO CHECK IF USER GOT HIGHSCORE
void instruct();		//TO PROVIDE INSTRUCTIONS ON GAMEPLAY
void play();			//TO PLAY THE GAME
void hangman(int try);	//TO DISPLAY THE HANGMAN
int scorekeep(char *str, int guess);	//TO FIND THE SCORE FOR A WORD(GUESSED CORRECTLY)
int fileopener(char *wordlist[]);		//TO OPEN THE PROPER FILE CONTAINING WORDSET
void wordadder();						//TO WRITE NEW WORDS INTO THE FILES CONTAINING WORDLIST
void borders();							//TO DRAW BORDERS FOR EACH SCREEN

struct player            //STRUCTURE TO STORE THE DETAILS OF A PLAYER
{
	char name[20];
	int rank;
	int score;
	char topic[40];
};

int gword=0; 		//NO. OF GUESSED WORDS
int topicfile=0; 	//THE WORDFILE WHICH IS CURRENTLY OPEN
int quit=0;			//FLAG VALUE TO QUIT

void main(){		//THE MAIN FUNCTION
	char opt;
	char aopt;
	int gd = DETECT, gm, i;   //initalising graphics driver, graphics mode
	int x,y;

	clrscr();
   	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");		//opening the graphics header
	settextjustify(CENTER_TEXT, CENTER_TEXT);		//setting text alignment
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(RED);
    outtextxy(getmaxx()/2, getmaxy()/2, "WELCOME TO PLAY HANGMAN!");		//to display the text in the middle of the screen
    delay(3000);
    cleardevice();
    closegraph();

	borders();

	textcolor(CYAN);
	gotoxy(35,2);
	cprintf("Hangman Game");
	gotoxy(35,7);
	textcolor(GREEN);
	cprintf("Developed by:");
	textcolor(MAGENTA);
	gotoxy(28,9);
	cprintf("Nara Vikram Venkatapathi");
	gotoxy(30,10);
	cprintf("Vishakan Subramanian");
	gotoxy(32,11);
	cprintf("Vaibhav Sankaran");
	delay(4000);

	textcolor(LIGHTGRAY);
	textbackground(BLACK);

	menupos:
	do{				//menu driven program
		clrscr();
		borders();
		gotoxy(25,5);
		printf("Welcome to Play Hangman!");
		gotoxy(25,7);
		printf("Enter 1 to Play");
		gotoxy(25,8);
		printf("Enter 2 to View Instructions");
		gotoxy(25,9);
		printf("Enter 3 to View Leaderboard");
		gotoxy(25,10);
		printf("Enter 4 to Edit Word List(Admin Only)");
		gotoxy(25,11);
		printf("Enter 0 to Exit");
		gotoxy(25,12);
		scanf(" %s",&opt);
		switch(opt){
			case '1':
					play();
					break;
			case '2':
					instruct();
					clrscr();
					break;
			case '3':
					displdboard();
					break;
			case '4':
					wordadder();
					break;
			case '0':
					gotoxy(30,22);
					printf("Thank you!");
					gotoxy(26,23);
					printf("Do come again!");
					delay(1000);
					break;
			default:
					gotoxy(25,20);
					printf("Invalid Input.");
		}
	}while(opt!='0');
}

void instruct(){		//to display instructions
	clrscr();
	borders();
	gotoxy(20,5);
	printf("Here are the instructions for the game:");
	gotoxy(5,7);
	printf("You get 5 chances to guess the given word correctly.");
	gotoxy(5,8);
	printf("If you use all 5 guesses,you lose the game.");
	gotoxy(5,9);
	printf("Points are awarded based on the length of the given word.");
	gotoxy(5,10);
	printf("Long words give more points whereas short words carry lesser points.");
	gotoxy(5,11);
	printf("You will keep playing till you make an incorrect guess.");
	gotoxy(5,12);
	printf("However, you may also quit with your current score if you wish to.");
	gotoxy(5,13);
	printf("High scores will earn a chance to display your name on the Leaderboard.");
	gotoxy(25,15);
	printf("So, what are you waiting for?");
	gotoxy(5,16);
	printf("Do you have what it takes to get yourself a place on the Leaderboard?");
	gotoxy(20,20);
	printf("Enter any key to go back to main screen.");
	getch();
}

void play(){
		char *wordlist[400],givenwords[400][50];  //list of words
		int nowords,randword;  //no of words in list, and random word finder
		char word[40],guess,temp[40],disp[40],prev[40],cont,contopt; //variables
		int try=5,score=0;		//score and guesses left
		int wlen,r,rpos[15];	//string related variables
		int i,j,k,flag,s=0,sub=0;			//looping variables

		playpos:
		nowords=fileopener(wordlist);		//getting list of words from the file
		if(nowords==0)
			exit(0);

		contplaypos:

		try=5;
		srand(time(NULL));   			//generating a random index
		randword=rand()%nowords;
		strcpy(word,wordlist[randword]);
		strupr(word);
		for(i=0;i<=gword;i++){			//checking if the word has already been given in the round
			if(strcmp(word,givenwords[i])==0)
				goto playpos;			//reading another word if so
		}
		strcpy(givenwords[gword],word);	//appending that word to given words
		gword++;	//setting the guess word as that random word from the wordlist

		if(gword==nowords){				//if user has guessed all the words in the file correctly
				clrscr();
				gotoxy(20,10);
				printf("You have got the maximum possible score!");
				goto maxpos;

		}

		wlen=strlen(word);
		sub=0;
		for(i=0;i<wlen;i++){ //generating the display word array
			disp[i]='_';
			if(!(isalpha(word[i]))){
				disp[i]=word[i];
			}
			else
				sub++;
		}
		disp[i]='\0';  //ending the disp word

		i=0;j=0;

		while(try!=0){  //running a loop till there are tries left
					clrscr();
					borders();
					gotoxy(35,3);
					printf("Gameplay");
					gotoxy(20,7);
					printf("The word has %d characters.",sub);
					gotoxy(5,10);
					printf("Your word is: ");
					gotoxy(5,12);
					for(s=0;s<wlen;s++)
						printf(" %c",disp[s]); //printing with space
						//printing the word(as far as user has guessed)
					guesspos:
					gotoxy(9,14);
					printf("Guess a letter: ");
					scanf("%s",&guess);
					guess=toupper(guess);
					if(guess<'A'||guess>'Z'){  //if invalid input
						gotoxy(10,20);
						printf("Invalid input. Enter a letter only.       ");
						goto guesspos;
					}
					else{
						for(k=0;k<i;k++){
							if(prev[k]==guess){			//if user has already guessed that letter
								gotoxy(10,20);
								printf("You have already guessed that letter.");
								gotoxy(10,21);
								printf("Try something new.");
								goto guesspos;
							}
						}

						prev[i]=guess;  //appending to previously guessed characters
						i++;
						flag=0;

						for(j=0;j<wlen;j++){   //checking if guessed char is in word
							if(guess==word[j]){
								disp[j]=word[j];    //appending to disp array
								flag++;
							}
						}
						if(flag!=0){		//if correct guess
							gotoxy(10,20);
							printf("Your guess was correct!                 ");
							if(strcmp(disp,word)==0){
								gotoxy(10,20);
								printf("                                    ");  //clearing previous text
								score+=scorekeep(word,try);		//appending score
								gotoxy(12,18);
								printf("You have guessed the word correctly!");
								gotoxy(5,20);
								printf("The word was %s",disp);
								gotoxy(5,21);
								printf("Your current score is: %d",score);	//displaying score
								playagain:
								gotoxy(5,22);
								printf("Do you wish to continue playing?(Y/N)");
								scanf(" %c",&contopt);
								if(toupper(contopt)=='Y')
									goto contplaypos;
								else if(toupper(contopt)=='N')
									goto exitpos;
								else{
									gotoxy(25,23);
									printf("Invalid option.");
									goto playagain;
								}
							}
						}
						else{
							gotoxy(25,14);
							printf("Oops!Your guess was incorrect!");
							try--;
							hangman(try);
							gotoxy(25,16);
							printf("You have %d tries left.",try);
						}

					}

		}
		if(try==0){		//pass score to leaderboard, display final score
			borders();
			gotoxy(25,16);
			printf("                               ");		//erasing previous text
			gotoxy(35,5);
			printf("GAME OVER!");
			gotoxy(15,8);
			printf("You have lost all your guesses!");
			gotoxy(15,10);
			printf("The word was %s",word);
			gotoxy(35,12);
			printf("Well played!");
		}
		maxpos:
		gotoxy(15,15);
		printf("Your final score was %d",score);
		boardcheck(score);		//checking if user got a highscore
		askpos:
		gotoxy(15,20);
		printf("Do you wish to play again?(Y/N) ");		//if user wishes to play again
		scanf("%s",&cont);
		cont=toupper(cont);
		if(cont=='Y'){
			goto playpos;
		}
		else if(cont=='N'){		//if user decides to quit
			gotoxy(30,23);
			printf("Thank you!      ");
			getch();
			exit(0);
		}
		else{		//invalid input
			gotoxy(30,23);
			printf("Invalid Input.");
			goto askpos;
		}
		exitpos:
			getch();

}

void displdboard(){				//to display the leaderboard
	FILE *fp;
	struct player p;
	int nrec=0;
	//tempfun();
	clrscr();
	borders();
	fp=fopen("details.txt","rb");
	gotoxy(35,5);
	printf("Leaderboard");
	gotoxy(10,7);
	printf("Rank\t|\tName\t|\tScore\t|\tTopic");
	while(!feof(fp)&&(nrec<10)){			//printing first 10 records
		fscanf(fp,"%d %s %d %[^\n]",&p.rank,p.name,&p.score,p.topic);
		gotoxy(10,7+nrec);
		printf("%d\t|\t%s\t|\t%d\t|\t%s",p.rank,p.name,p.score,p.topic);
		nrec++;
	}
	fclose(fp);
	if(!quit){		//to go back to main menu if game hasnt yet started
		gotoxy(17,20);
		printf("Press any key to go back to Main Menu");
		getch();
	}
}

void boardcheck(int score){

	FILE *f1,*f2;		//required variables
	struct player p,t;
	int n,i=0,flag=0,count=0;
	f1=fopen("details.txt","rb");
	f2=fopen("temp.txt","wb");

	p.score=score;
	switch(topicfile){ //checking for played topic and appending appropriate string
			case 1:
				strcpy(p.topic,"Countries & Cities");
				break;
			case 2:
				strcpy(p.topic,"Science Words");
				break;
			case 3:
				strcpy(p.topic,"Sports Words");
				break;
			case 4:
				strcpy(p.topic,"Famous Personalities");
				break;
			case 5:
				strcpy(p.topic,"Movies");
				break;
			}

	while(!feof(f1)){	 //reading contents from details.txt
		if(count>=10)		//checking if no. of records entered is less than 10
			break;
		fscanf(f1,"%d %s %d %[^\n]",&t.rank,t.name,&t.score,t.topic);
		if(t.score>p.score){		//if existing record score is greater than user's score
			fprintf(f2,"\n%d %s %d %s",t.rank,t.name,t.score,t.topic);	//writing to new file
			count++;
		}
		else if(t.score==p.score){		//if both scores are equal
			gotoxy(20,14);
			printf("You have got a highscore!");
			gotoxy(15,15);
			printf("Enter your details for the Hall of Fame!");
			gotoxy(20,17);
			printf("Enter Name: ");
			scanf("%s",p.name);
			i=0;
			flag=1;
			p.rank=t.rank;				//giving him same rank as previous record
			fprintf(f2,"\n%d %s %d %s",p.rank,p.name,p.score,p.topic);
			count++;
			gotoxy(5,18);
			printf("Congratulations!Your name was successfully added to the Hall of Fame!");
			break;		//breaking out of while loop
		}
		else{		//if user's score is greater than existing record's
			gotoxy(20,14);
			printf("You have got a highscore!");
			gotoxy(15,15);
			printf("Enter your details for the Hall of Fame!");
			gotoxy(20,17);
			printf("Enter Name: ");
			scanf("%s",p.name);
			flag=1;
			count++;
			p.rank=t.rank;		//giving him a rank that is +1 of the previous record
			i=1;
			flag=1;
			fprintf(f2,"\n%d %s %d %s",p.rank,p.name,p.score,p.topic);
			gotoxy(5,18);
			printf("Congratulations!Your name was successfully added to the Hall of Fame!");
			break;		//breaking out of while loop
		}
	}
	t.rank+=i;		//increasing rank based on previous if-else if-else working
	if(count<10){		//checking if no. of records entered is less than 10
		fprintf(f2,"\n%d %s %d %s",t.rank,t.name,t.score,t.topic);		//going back to the else/elseif satisfied record and writing it
		count++;
	}
	while(t.rank<=9){		//writing the remaining records to new file, till 10 records
		if(count>10)
			break;
		fscanf(f1,"%d %s %d %[^\n]",&t.rank,t.name,&t.score,t.topic);
		t.rank+=1;					//increasing the others ranks by 1
		fprintf(f2,"\n%d %s %d %s",t.rank,t.name,t.score,t.topic);
		count++;
	}				//i.e last pre-existing record will be deleted here
	fclose(f1);
	fclose(f2);
	remove("details.txt");
	rename("temp.txt","details.txt");
	if(flag){
		gotoxy(15,19);
		printf("Press any key to view the leaderboard!");		//viewing the leaderboard
		getch();
		clrscr();
		quit++;
		displdboard();
		gotoxy(25,23);
		printf("Press any key to exit.");
		getch();
		exit(0);
	}
}

void hangman(int try){

	int i, j, gd = DETECT, gm;
	clrscr();
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	setcolor(WHITE);
	setbkcolor(BLACK);

	line(250,300,400,300);     //base
	line (250,100,250,300);    //pole
	line (250,100,330,100);    //stand

	printf("\n\t\t\tYou have %d guesses left.",try);
	switch(try){
			case 4:
				printf("\n\n\t\t\tThe rope has been drawn!");
				line (330,100,330,150);    //rope
				break;
			case 3:
				printf("\n\n\t\t\tThe face has been drawn!");
				line (330,100,330,150);    //rope
				circle(330,170,20);        //face
				circle(320,165,3);         //eyes
				circle(340,165,3);         //eyes
				arc(330,175,210,330,7);    //smile
				break;
			case 2:
				printf("\n\n\t\t\tThe body has been drawn!");
				line (330,100,330,150);    //rope
				circle(330,170,20);        //face
				circle(320,165,3);         //eyes
				circle(340,165,3);         //eyes
				line (330,190,330,250);    //body
				arc(330,175,210,330,7);    //smile
				break;
			case 1:
				printf("\n\n\t\t\tThe arms have been drawn!");
				line (330,100,330,150);    //rope
				circle(330,170,20);        //face
				circle(320,165,3);         //eyes
				circle(340,165,3);         //eyes
				line (330,190,330,250);    //body
				arc(330,175,210,330,7);    //smile
				line (330,200,375,215);    //arm right
				line (330,200,275,215);    //arm left
				break;
			case 0:
				printf("\n\n\t\t\tThe legs have been drawn!");
				line (330,100,330,150);    //rope
				circle(330,170,20);        //face
				circle(320,165,3);         //eyes
				circle(340,165,3);         //eyes
				line (330,190,330,250);    //body
				arc(330,180,10,160,7);     //sad
				line (330,200,375,215);    //arm right
				line (330,200,285,215);    //arm left
				line (330,250,375,275);    //leg right
				line (330,250,285,275);    //leg left
				break;
	}

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tPress any key to continue.");
	while(!getch())
		delay(200);

	closegraph();
}

int scorekeep(char *str, int guess){

	int i,len,unicharno=0,score;
	int count[256];
	len=strlen(str);
	for(i=0;i<len;i++){
		count[str[i]]=0;		//assigning the frequency of each characters in the given string as '0'
	}
	for(i=0;i<len;i++){
		if(str[i] !=' ')
			count[str[i]]+=1;	//finding the frequency of each characters in the given string
	}

	for(i=0;i<len;i++){
		if(count[str[i]] >= 1)
			unicharno+=1;		//finding the no. of unique characters in tha string
	}
	score=(len*unicharno*1) + (guess * 2);	//finding the score
	return (score);

	/* FORMULA : [ No. of characters in word * No. of unique characters * base score(-> 1) ]+
		[ No. of guesses left * Base Score(-> 2) ] */
}

int fileopener(char *wordlist[]){
	FILE *fp;
	int i=0,j;
	int opt;

	p:
	clrscr();
	borders();
	gotoxy(30,5);
	printf("Topic Chooser");
	gotoxy(25,7);
	printf("Enter 1 for Countries & Cities");
	gotoxy(25,8);
	printf("Enter 2 for Scientific Words");
	gotoxy(25,9);
	printf("Enter 3 for Sports Words");
	gotoxy(25,10);
	printf("Enter 4 for Famous Personalities");
	gotoxy(25,11);
	printf("Enter 5 for Movies");
	gotoxy(25,12);
	printf("Enter 0 to Quit");
	gotoxy(25,13);
	scanf("%d",&opt);
	switch(opt){			//to open the specific file
		case 1:
			fp=fopen("country.txt","r");
			topicfile=1;
			break;
		case 2:
			fp=fopen("science.txt","r");
			topicfile=2;
			break;
		case 3:
			fp=fopen("sports.txt","r");
			topicfile=3;
			break;
		case 4:
			fp=fopen("person.txt","r");
			topicfile=4;
			break;
		case 5:
			fp=fopen("movies.txt","r");
			topicfile=5;
			break;
		case 0:
			gotoxy(25,18);
			printf("Press any key to exit.");
			getch();
			return i;
		default:
			gotoxy(25,18);
			printf("\nInvalid option!         ");
			goto p;
	}
	if(fp==NULL){
		gotoxy(24,22);
		printf("File not found.");
		exit(0);
	}

	i=0;
	wordlist[i]=(char *)malloc(sizeof(char)*100); 	//allocating memory
	fgets(wordlist[i],50,fp);						//getting the first word in the file
	while(!feof(fp)){								//getting all the words in the file
		i++;
		wordlist[i]=(char *)malloc(sizeof(char)*100);	//allocating memory for the next word
		fgets(wordlist[i],50,fp);						///getting the ith word in the file
	}

	return i;

}

void wordadder(){

	FILE *fp;
	char word[40],eword[40];		//variables
	char adminid[10],uid[10];		//user id
	char pass[10],upass[10],c,aopt;		//pass
	int opt,i=0;
	fp=fopen("admin.txt","r");		//opening file containing admin details
	fscanf(fp,"%s",adminid);
	fscanf(fp,"%s",pass);
	clrscr();
	borders();
	gotoxy(30,3);
	printf("Authentication Check");
	gotoxy(25,10);
	printf("Enter user ID: ");
	gotoxy(25,11);
	scanf(" %s",uid);
	gotoxy(25,12);
	printf("Enter password: ");
	gotoxy(25,13);
	while(i<8){			//to hide password with *
		c=getch();
		printf("*");
		upass[i]=c;
		i++;
	}
	upass[i]='\0';
	if(strcmp(adminid,uid)==0){		//validation through strcmp
		if(strcmp(upass,pass)!=0){
			gotoxy(25,16);
			printf("Incorrect password.");
			getch();
			exit(0);
		}
	}
	else{
		gotoxy(25,16);
		printf("Incorrect User ID.");
		getch();
		exit(0);
	}
	fclose(fp);

	p:			//if authenticity of user is confirmed
	clrscr();
	borders();
	gotoxy(25,3);
	printf("Topic Chooser-To Add New Words");
	gotoxy(25,7);
	printf("Enter an option:");
	gotoxy(25,9);
	printf("1 for Countries & Cities");
	gotoxy(25,10);
	printf("2 for Scientific Words");
	gotoxy(25,11);
	printf("3 for Sports Words");
	gotoxy(25,12);
	printf("4 for Famous Personalities");
	gotoxy(25,13);
	printf("5 for Movies");
	gotoxy(25,14);
	scanf("%d",&opt);
	switch(opt){			//to open the specific file in append mode
		case 1:
			fp=fopen("country.txt","a+");
			break;
		case 2:
			fp=fopen("science.txt","a+");
			break;
		case 3:
			fp=fopen("sports.txt","a+");
			break;
		case 4:
			fp=fopen("person.txt","a+");
			break;
		case 5:
			fp=fopen("movies.txt","a+");
			break;
		default:
			printf("\nInvalid option!");
			goto p;
	}
	writepos:
	gotoxy(25,16);
	printf("Enter a word to be added: ");		//getting word
	scanf(" %[^\n]",word);
	gotoxy(25,19);
	printf("                                                  ");		//clearing previous messages
	if(strlen(word)>40){
		gotoxy(25,19);
		printf("Please enter a word less than 40 characters.");
		goto writepos;
	}
	strupr(word);
	fseek(fp,0,SEEK_SET);
	fscanf(fp,"%[^\n]\n",eword);
	//printf("\n%s",eword);
	while(!feof(fp)){		//checking if word already exists in file
		//printf("\n%s",eword);
		fscanf(fp,"%[^\n]\n",eword);
		if(strcmp(eword,word)==0){
			gotoxy(25,19);
			printf("Word already exists!                     ");
			goto writepos;
		}
	}
	fprintf(fp,"\n%s",word);		//writing, if not
	gotoxy(10,20);
	printf("Word successfully written into the file!");
	contpos:
	gotoxy(10,22);
	printf("Do you wish to add another word into a file?(Y/N) ");	//if admin wishes to continue adding words
	scanf(" %s",&aopt);
	if(toupper(aopt)=='Y'){
		fclose(fp);
		goto p;
		}
	else if(toupper(aopt)=='N'){
		fclose(fp);
		gotoxy(20,23);
		printf("Press any key to go back to main menu.");		//to go back to main menu
		getch();
		}
	else{
		gotoxy(25,23);
		printf("Invalid Input!");		//ask input once again
		goto contpos;
		}

}


void borders(){		//to draw the borders for a screen
	int x,y;
	textcolor(YELLOW);
	for(x=1;x<80;x++){			//printing horizontal border
		gotoxy(x,1);
		cprintf("*");
		gotoxy(x,24);
		cprintf("*");
	}
	for(y=1;y<=24;y++){			//printing vertical border
		gotoxy(1,y);
		cprintf("||");
		gotoxy(79,y);
		cprintf("||");
	}
	gotoxy(1,1);
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
}
