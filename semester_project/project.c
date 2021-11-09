// header function declaration
#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 3000000000

// Visitor Node Structure
typedef struct visitor
{
	char name[20]; //visitor's name
	int code; //visitor's code - randomly assigned
	int day; //Date visited
	int phone_num; //visitor's phone number
	int residence; //visitor's residence code
	float temperature; //visitor's temperature;
	int check1; //travel abroad status in the last two week
	int check2; //Personal information consent status
	struct visitor* next; //Pointer pointing to the next node (used in the list)
	struct visitor* prev; //Pointer pointing to all nodes (used in the list)
	struct visitor* hnext; //Pointer on the hashtable pointing to the next node
}Visitor;

// Visitor List Structure
typedef struct list
{
	Visitor* H; //Header (first)
	Visitor* T; //Tail (End)
	int len; //the number of visitors
}List;

//Residence Hashtables
typedef struct Hash {
	char name[9]; //Residence Name
	Visitor *hash_H; //Visitor Structure Pointer for Chaining
}Hash;

// a first greeting
void hello()
{
	printf("\n------------------------------------------------------------------------------\n");
	printf("\t\tHello, Welcome to Seoul, the capital of Korea!!!\n");
	printf("\tAs the Covid-19 virus spreads, we must make an entry list.\n");
	printf("\t\t\tPlease enter your information\n");
	printf("------------------------------------------------------------------------------\n\n");
}

// A menu to choose whether you are a visitor or manager
void mode_menu()
{
	printf("\n--------Select MODE---------\n");
	printf("\t1. Visitor\n"); // If you press one, you're a visitor.
	printf("\t2. Manager\n"); // If you press two, you are an administrator.
	printf("----------------------------\n\n");
}

// Administrator Only Menu
void manager_menu()
{
	printf("\n----------------------Manager menu-----------------------\n");
	printf("\t1. Registration of visitors\n"); //registration of visitors
	printf("\t2. Modify visitor information\n"); //Modify visitor information
	printf("\t3. Delete visitor information\n"); //Delete Visitor
	printf("\t4. View all visitor informations\n"); //View all visitors
	printf("\t5. Search Visitor Information\n"); //Find a specific visitor
	printf("\t0. Log-out\n"); // Log out of Admin Mode
	printf("---------------------------------------------------------\n\n");
}

// visitor menu (register, edit) menu
void visitor_menu()
{
	printf("\n---------------Visitor Menu---------------\n");
	printf("\t1. Enter my information\n"); //registration of visitors
	printf("\t2. Modifying my information\n"); //Modify visitor information
	printf("------------------------------------------\n\n");
}

//Residential Information Output Menu
void residence_menu(char region[][9])
{
	printf("\n\t*********Code of Administrative divisions of Seoul*********\n");
	for (int i = 0; i < 26; i++)
		printf("\t\t\t\t%d. %s\n", i, region[i]);
	printf("\t************************************************************\n\n");
}

// Last greeting after running the program
void bye()
{
	printf("\n\n------------------------------------------------------------------------------------------------\n");
	printf("\t\tThank you for visiting Seoul and following the Covid-19 virus rules.\n");
	printf("\t** The information you filled in will be deleted in two weeks!!! **\n");
	printf("\t\tLet's all cheer up until the end of the Covid-19 virus.\n");
	printf("\t\t\t\tHave a nice day\n");
	printf("------------------------------------------------------------------------------------------------\n\n");
}

// Initializing Visitor Information Node
void initGuest(Visitor** V)
{
	srand((unsigned int)time(NULL)); //random number generating function

	(*V) = (Visitor*)malloc(sizeof(Visitor)); //visitor node dynamic allocation
	(*V)->code = (rand() % MAX) + 1; //Randomly assign visitor code
	(*V)->day = 0; //Reset visit date to zero
	(*V)->phone_num = 0; //Reset phone number to zero
	(*V)->temperature = 0.0; //Initializing Visitor's Temperature to 0.0
	(*V)->check1 = 0; //Initializing Overseas Experience Status to Zero
	(*V)->check2 = 0; //Reset privacy status to zero
	(*V)->prev = NULL; //Initialize the pointer pointing to the entire node as a NULL
	(*V)->next = NULL; //Reset pointer pointing to next node to NULL
	(*V)->hnext = NULL; //Initialize pointer pointing to the next node on the hashtable to NULL
}

//Initializing Visitor Information List
void initList(List** L)
{
	// space allocation of visitor lists
	(*L) = (List*)malloc(sizeof(List));

	// Allocate the header space to indicate the start of the visitor list.
	(*L)->H = (Visitor*)malloc(sizeof(Visitor));
	// Allocate the tail space to indicate the end of the visitor list.
	(*L)->T = (Visitor*)malloc(sizeof(Visitor));

	(*L)->H->prev = NULL; // Header's previous is NULL
	(*L)->T->next = NULL; // Tail's next is NULL
	(*L)->H->next = (*L)->T; // Header's next connect to Tail
	(*L)->T->prev = (*L)->H; // Tail's previous connect to Header

	(*L)->len = 0; //Initialize the length of the list to zero
}

//Hashtable initialization
void init_Hash(Hash *R, char region[][9])
{
	for (int i = 0; i < 26; i++)
	{
		//Dynamic assignment of visor nodes on hashtables
		R[i].hash_H = (Visitor*)malloc(sizeof(Visitor));
		//Initialize next pointer on the visor node of the hashtable to NULL
		R[i].hash_H->hnext = NULL;
		//Store residence information on hashtables
		strcpy(R[i].name, region[i]);
	}
}

//MERGE SORT
//function of splitting structure for merge sort
void mg_partition(Visitor *H, Visitor **L1, Visitor **L2, int N)
{
	Visitor *p = H;
	(*L1) = H; //L1 from the beginning of H
	for (int i = 0; i < (N / 2) - 1; i++)
		p = p->next; //Move H to (N/2-1)th
	(*L2) = p->next; //Store the next node of the moved node in L2
	p->next = NULL;
	//Without this condition, there is no ending, and it continues to spin infinitely.
}

//Sort by Visit Date
Visitor* merge1(List *L, Visitor **L1, Visitor **L2)
{
	Visitor *SH, *p;
	//SH is the header of the sorted list, 
	//p is the role of connecting SH header determination
	Visitor *l1 = *L1, *l2 = *L2;

	//header determination
	if (l1->day <= l2->day)
	{
		SH = l1;
		l1 = l1->next;
		p = SH;
	}
	else
	{
		SH = l2;
		l2 = l2->next;
		p = SH;
	}

	//To sort in ascending order in SH:
	while ((l1 != NULL) && (l2 != NULL))
	{
		if (l1 == L->T || l2 == L->T) break;

		if (l1->day <= l2->day)
		{
			p->next = l1;
			if (l1->next != L->T)
				l1 = l1->next;
			p = p->next;
		}
		else
		{
			p->next = l2;
			if (l2->next != L->T)
				l2 = l2->next;
			p = p->next;
		}
	}
	//Insert remaining unaligned nodes into SH in turn
	while (l1 != NULL)
	{
		if (l1 == L->T) break; //Conditional statement to prevent TAIL of the list
		p->next = l1;
		p = l1; //The role of putting l1 in p and then moving it to be put in.
		l1 = l1->next;
	}
	while (l2 != NULL)
	{
		if (l2 == L->T) break; //Conditional statement to prevent TAIL of the list
		p->next = l2;
		p = l2; //The role of putting l2 in p and then moving it to be put in.
		l2 = l2->next;
	}
	return SH;
}
void mergeSort1(List *L, Visitor **H, int N)
{
	Visitor *L1, *L2; //L1 and L2 contain the address of the partitioned H
	Visitor *p = (*H);

	if (N > 1) //This condition must be written because 1 number of lists is the minimum unit.
	{
		mg_partition(p, &L1, &L2, N); //split list

		if (N % 2 == 0) //N is even
		{
			mergeSort1(L, &L1, N / 2);
			mergeSort1(L, &L2, N / 2);
		}
		else //N is odd
		{
			mergeSort1(L, &L1, N / 2);
			mergeSort1(L, &L2, (N / 2) + 1);
		}
		(*H) = merge1(L, &L1, &L2); //Merge
	}
}

//sort by name
Visitor* merge2(List *L, Visitor **L1, Visitor **L2)
{
	Visitor *SH, *p; //SH is the header of the sorted list, 
					 //p is the role of connecting SH
	Visitor *l1 = *L1, *l2 = *L2;

	//header determination
	if (strcmp(l1->name, l2->name) == -1)
	{
		SH = l1;
		l1 = l1->next;
		p = SH;
	}
	else
	{
		SH = l2;
		l2 = l2->next;
		p = SH;
	}

	//To sort in ascending order in SH:
	while ((l1 != NULL) && (l2 != NULL))
	{
		if (l1 == L->T || l2 == L->T) break;

		if (strcmp(l1->name, l2->name) == -1 || strcmp(l1->name, l2->name) == 0)
		{
			p->next = l1;
			if (l1->next != L->T)
				l1 = l1->next;
			p = p->next;
		}
		else
		{
			p->next = l2;
			if (l2->next != L->T)
				l2 = l2->next;
			p = p->next;
		}
	}
	//Insert remaining unaligned nodes into SH in turn
	while (l1 != NULL)
	{
		if (l1 == L->T) break; //Conditional statement to prevent TAIL of the list
		p->next = l1;
		p = l1; //The role of putting l1 in p and then moving it to be put in.
		l1 = l1->next;
	}
	while (l2 != NULL)
	{
		if (l2 == L->T) break; //Conditional statement to prevent TAIL of the list
		p->next = l2;
		p = l2; //The role of putting l2 in p and then moving it to be put in.
		l2 = l2->next;
	}
	return SH;
}
void mergeSort2(List *L, Visitor **H, int N)
{
	Visitor *L1, *L2; //L1 and L2 contain the address of the partitioned H
	Visitor *p = (*H);

	if (N > 1) //This condition must be written because 1 number of lists is the minimum unit.
	{
		mg_partition(p, &L1, &L2, N); //split list

		if (N % 2 == 0) //N is even
		{
			mergeSort2(L, &L1, N / 2);
			mergeSort2(L, &L2, N / 2);
		}
		else //N is odd
		{
			mergeSort2(L, &L1, N / 2);
			mergeSort2(L, &L2, (N / 2) + 1);
		}
		(*H) = merge2(L, &L1, &L2); //Merge
	}
}

//Output results for specific visitor
void show_info(Visitor *v, char region[][9])
{
	printf("\n*********************Visitor Information************************\n");
	printf("\tPerson who visited : %s\n", v->name);
	printf("\tVisitor code : %d\n", v->code);
	printf("\t==>Please remember this code for modify your info.\n");
	printf("\tVisited day : %d\n", v->day);
	printf("\tPhone numbr : %d\n", v->phone_num);
	printf("\tResidence : %s\n", region[v->residence]);
	printf("\tBody temperature : %.2f\n", v->temperature);
	printf("\tOverseas travel status : NO\n");
	printf("\tPersonal information consent status : YES\n");
	printf("**************************************************************\n\n");
}

//Output all visitor information
void print_all(List *L, char region[][9])
{
	Visitor *p = L->H;
	int cnt = 1;
	p = p->next;
	while (p != L->T)
	{
		printf("\ninfo %d", cnt);
		show_info(p, region);
		cnt++;
		p = p->next;
	}
}

//Outputs all visitor information by name
void print_byname(List *L, char region[][9])
{
	Visitor *tmp = L->H->next;
	//Use merge sort to sort by name
	mergeSort2(L, &(L->H->next), L->len);
	//TAIL of the list after alignment and the end of the sorted list
	while (tmp->next != NULL)
		tmp = tmp->next;
	L->T->prev = tmp;
	tmp->next = L->T;

	print_all(L, region); //All information output
}

//Output all visitor information sorted by visit date
void print_bydate(List *L, char region[][9])
{
	Visitor *tmp = L->H->next;
	//Use merge sort to sort by visit date
	mergeSort1(L, &(L->H->next), L->len);
	//TAIL of the list after alignment and the end of the sorted list
	while (tmp->next != NULL)
		tmp = tmp->next;
	L->T->prev = tmp;
	tmp->next = L->T;

	print_all(L, region); //All information output
}

//Outputs all visitor information in order of region code
void print_byregion(Hash *R, char region[][9])
{
	int i;
	Visitor *tmp, *p;
	for (i = 0; i < 26; i++)
	{
		tmp = R[i].hash_H;
		printf("\n\n%s\n", R[i].name);

		//Mark no visitors in areas without information
		if (tmp->hnext == NULL)
		{
			printf("NO Visitors!!!!\n\n");
			continue;
		}

		//Information output for areas with visitor information
		p = tmp->hnext;
		while (p != NULL)
		{
			show_info(p, region);
			p = p->hnext;
		}
	}
}


//Find Results
//Find Visitor Information by Visitor Code
Visitor* search_bycode(List *L, int code_num)
{
	Visitor *p = L->H;

	//Compare Visitor Code with Original Code entered when Modifying
	while (p != L->T)
	{
		if (code_num == p->code) //If it's the same as the original code,
			return p; //Return the Visitor Structure Address
		p = p->next;
	}

	p = L->H; //Return header pointer if code information is missing
	return p;
}

//Find and print visor information by name
void search_byname(List *L, char *search_name, char region[][9])
{
	Visitor *p = L->H;
	int cnt = 1;

	if (p->next == L->T) //If the visitor list is empty
	{
		printf("\n\n\tNo visitors!!\n\n"); //Mark no visitors
		return; //function termination
	}

	while (p != L->T) // If there are visitors
	{
		if (strcmp(p->name, search_name) == 0) //If it's the same name you're looking for,
		{
			printf("info %d", cnt);
			show_info(p, region); //information output
			cnt++;
		}
		p = p->next; // Move to next node
	}

	if (cnt == 0) //When there is no visitor with the name you are looking for.
		printf("\tNo visitors with the name entered!!!\n\n"); //Mark that no information is available

}

//Find Visitor Information by Date
void search_byday(List *L, int search_day, char region[][9])
{
	Visitor *p = L->H;
	int cnt = 1;

	if (p->next == L->T) // If the visitor list is empty
	{
		printf("\n\n\tNo visitors!!\n\n"); //Print out no visitors
		return; //function termination
	}

	while (p != L->T) //If there is a visitor
	{
		if (p->day == search_day) //Find visitors with the same date and visit date you want to find
		{
			printf("info %d", cnt);
			show_info(p, region); //Visitor Information Output
			cnt++;
		}
		p = p->next; // Move to next node
	}

	if (cnt == 0) //If you don't have a visitor on the date you're looking for,
		printf("\tNo one visited on the date entered!!!\n\n"); //Mark that no information is available
}

//Find Visitors by Region
void search_byregion(Hash *R, int search_region, char region[][9])
{
	Visitor *tmp = R[search_region].hash_H, *p;

	if (tmp->hnext == NULL) //In case there are no visitors to the area you are looking for
	{
		printf("\n\n\tNo visitor in %s!!!\n\n", region[search_region]); //Mark no visitors
		return;
	}

	p = tmp->hnext;
	while (p != NULL) //If there is a visitor
	{
		show_info(p, region); //visitor output in the area
		p = p->hnext; //Move to next hash node
	}
}

//Add Visitors
void addVisitor(List *L, Hash *R, char region[][9])
{
	int flag = 0, status = 0;
	//state=0 is still less input, status=-1 is inappropriate, status=1 is appropriate
	Visitor *tmp = L->H;
	Visitor *v = (Visitor*)malloc(sizeof(Visitor)); initGuest(&v); //dynamic assignment of visitor nodes to add

	while (1)
	{ //Terminate repeating statements if the content of the booker is entered correctly

	  //visitor's name
		printf("Please Enter your Name : "); scanf("%s", v->name);	// Visitor name

																	//Date visited
		while (1)
		{
			printf("Please enter today's date : "); scanf("%d", &(v->day)); //Visited day
			if (v->day < 20200101) //Display warning message if visit date is before 1 January 2020
			{
				printf("\n\n\tHandle information after January 1, 2020.\n");
				printf("\tPlease enter information after January 1, 2020.\n\n\n");
				continue;
			}
			else break;
		}

		//Enter the phone number
		printf("Please enter your phone number : "); scanf("%d", &(v->phone_num));

		//Enter Residence Information
		while (1)
		{
			printf("Where do you live?\n");
			residence_menu(region); //Residential Code Menu Output
			printf("Region-code : ");	scanf("%d", &(v->residence)); //Enter Residence Code
			if (v->residence<0 || v->residence>26) //If the range of the residence code is not correct,
			{
				printf("\n\n\tThe code is out of range!!\n"); //Warning Statement Output
				printf("\tCode is a number from 0 to 26.\n");
				printf("\tPlease re-enter the number of region-code.\n\n\n");
				continue;
			}
			else break;
		}

		// Entering Body Temperature Information
		while (1)
		{
			printf("Please enter your temperature : "); scanf("%f", &(v->temperature));
			if (v->temperature >= 35.0 && v->temperature <= 37.2) //If the range of body temperature is appropriate,
				break; //exit repeating statement
			else if (v->temperature >= 37.3 && v->temperature < 40) //If the range of body temperature is high
			{
				printf("\n\n\tYour temperature is too high!\n"); //Print out a warning and deny entry
				printf("\tTherefore, I refuse to visit today.\n");
				printf("\tI recommend you to visit the hosipital.\n");
				printf("\tYour information entered is deleted now!\n");
				status = -1;
				break;
			}
			else //If the range of body temperature is not appropriate,
			{
				printf("\n\n\t\t\tInput Error!\n"); //Show warning statement that range is not appropriate
				printf("\tA person's body temperature is higher than 35 degrees!\n");
				printf("\t\tPlease re-enter your body temperature.\n\n\n");
				continue;
			}
		}
		// You cannot enter if your body temperature is high.
		if (status == -1)
		{
			free(v);
			return;
		}

		//Entering overseas travel history
		while (1) { //Do you have any history of traveling abroad for the last two weeks?
			printf("\nHave you traveled abroad for the last 2 weeks?\n");
			printf("\t0. YES \t\t1. NO\n");
			printf("Status : ");  scanf("%d", &(v->check1)); printf("\n");


			if (v->check1 == 0) { //No admittance if you have a history of overseas travel
				printf("\n\n\tIf you have been abroad for the last 2 weeks, you have to do self-price for 2 weeks.\n");
				printf("\tTherefore, I refuse to visit today.\n");
				printf("\tI recommend you to visit the hosipital.\n");
				printf("\tYour information entered is deleted now!\n\n");
				free(v);
				return;
			}
			else if (v->check1 == 1) break; //Admission if no overseas travel history is available
			else //Output warning statement when entering invalid numbers
			{
				printf("\n\n\tInput error!!\n");
				printf("\tPlease re-enter.\n\n\n");
				continue;
			}
		}

		//Enter status of personal information consent
		while (1)
		{
			printf("\nDo you agree to collect and use personal information?\n");
			printf("\t1. YES \t\t0. NO\n");
			printf("Status : ");  scanf("%d", &(v->check2)); printf("\n");

			if (v->check2 == 0) //If you don't agree to personal information, you won't be admitted.
			{
				printf("\n\tIf you don't agree, you can't enter.\n");
				printf("Return to the initialization plane.\n");
				status = -1;
				break;
			}
			else if (v->check2 == 1) //Final admission if personal information is agreed
			{
				status = 1;
				break;
			}
			else //If an invalid number is entered, print the warning statement and re-enter it
			{
				printf("\n\n\tInput error!!\n");
				printf("\tPlease re-enter.\n\n\n");
				continue;
			}
		}
		if (status == -1) //If you don't agree to personal information, you won't be admitted.
		{
			free(v);
			return;
		}

		show_info(v, region); //Output entered information

							  //Check whether the input is correct or not
		printf("Is the information history correct?\n");
		printf("If correct, enter 1. If you want to type again, enter 0. "); scanf("%d", &flag);   printf("\n");

		if (flag == 0) //If the information entered is incorrect, re-enter it
			continue;
		else //Add if the information entered is correct
		{
			//Add to Visitor List
			while (tmp != L->T)
				tmp = tmp->next;
			v->next = tmp;
			v->prev = tmp->prev;
			(tmp->prev)->next = v;
			tmp->prev = v;

			L->len++;

			//Add to Hashtables
			Visitor *temp = R[v->residence].hash_H;
			if (temp->hnext == NULL)
				temp->hnext = v;
			else
			{
				v->hnext = temp->hnext;
				temp->hnext = v;
			}
			break; // End Full Repetition
		}
	}

	//Output a confirmation message that registration is complete
	printf("\n\n\tResistration completed!!\n");
	printf("\tThank you for following!!\n\n");
}


//Modify visitor -> Use visitor code
void editVisitor(List *L, char region[][9])
{
	Visitor *tmp = L->H;
	int code_num, flag, status = 0;

	if (tmp->next == L->T) //If the visitor list is empty
	{
		printf("\n\n\tNo visitors!!\n\n"); //Warning Statement Output
		return; //function termination
	}

	while (1)
	{
		printf("\nEnter the visitor code : "); scanf("%d", &code_num); //Enter Code Information

		Visitor *p = search_bycode(L, code_num); //Verify that you have information about the code entered

		if (p == L->H) //if code is incorrect
		{
			printf("\n\n\tThe code you entered does not exist.\n");
			printf("\tPlease check again.\n");
		}
		else //Only name, number, and body temperature can be modified if entered correctly
		{
			while (1)
			{ //Terminate repeating statements if the content of the booker is entered correctly

				printf("\n\tHELLO, \" %s \" visitor!\n", p->name);
				printf("\tYou can only modify your name, phone number, and body temperature.\n\n");

				//Re-enter Visitor Name
				printf("Please Enter your Name : "); scanf("%s", p->name);

				//Re-enter Phone Number
				printf("Please enter your phone number : "); scanf("%d", &(p->phone_num));

				//body temperature re-entry
				while (1)
				{
					printf("Please enter your temperature : "); scanf("%f", &(p->temperature));
					if (p->temperature >= 35.0 && p->temperature <= 37.2) //If the body temperature range is appropriate,
						break; //Complete Input
					else if (p->temperature >= 37.3 && p->temperature < 40) //When the body temperature is high,
					{
						printf("\n\n\tYour temperature is too high!\n");
						printf("\tTherefore, I refuse to visit today.\n");
						printf("\tI recommend you to visit the hosipital.\n");
						printf("\tYour information entered is deleted now!\n");
						status = -1;
						break;
					} //admission denied
					else //If the body temperature range is inadequate,
					{
						printf("\n\n\t\t\tInput Error!\n");
						printf("\tA person's body temperature is higher than 35 degrees!\n");
						printf("\t\tPlease re-enter your temperature.\n\n\n");
						continue;
					} //Re-enter
				}
				// You cannot enter if your body temperature is high.
				if (status == -1)
				{
					free(p); //Delete entered information
					return;
				}

				show_info(p, region); //Output entered information

									  //Check whether the input is correct or not
				printf("Is the information history correct?\n");
				printf("If correct, enter 1. If you want to type again, enter 0. "); scanf("%d", &flag);   printf("\n");

				if (flag == 0) //If re-entering
					continue; //Return to the beginning of the iteration to re-enter from the beginning
				else //If the information entered is correct
					break; // End Full Repetition
			}

			//Print out a statement that the information has been modified
			printf("\n\n\tThe information has been modified successfully!!\n\n");
		}
		break;
	}
}


//Delete visitor -> Delete information that is past a certain period of time
void deleteVisitor(List *L, Hash *R)
{
	Visitor *tmp, *p = L->H;
	int delete_day, cnt = 0, index;

	if (p->next == L->T) //In case there are no visitors
	{
		printf("\n\n\tNo Visitor!!\n"); //Exit after printing no visitors
		return;
	}

	//Delete all information prior to the date entered
	printf("Please enter the date you want to delete ex)2000.10.18 -> 20001018 : "); scanf("%d", &delete_day);

	p = p->next;
	while (p != L->T) {
		if (p->day <= delete_day)
		{
			//Delete from list
			tmp = p; //tmp will be deleted
			p = p->next;
			(tmp->prev)->next = tmp->next;
			(tmp->next)->prev = tmp->prev;

			//Delete from hashtables
			index = tmp->residence;
			Visitor *temp = R[index].hash_H;
			while (temp->hnext != tmp) //temp before tmp node
				temp = temp->hnext;
			if (tmp->hnext == NULL)
				temp->hnext = NULL;
			else
				temp->hnext = tmp->hnext;

			free(tmp); //free tmp
			L->len--; //Reduce the length of the guest list by 1
			cnt++; //Number of Information Deleted Counts
		}
		else
			p = p->next;
	}

	//Output the number of deleted information
	printf("\n\t%d pieces of information are deleted!!\n", cnt);
}

int main()
{
	char region[26][9] = { "강남구", "강동구", "강북구", "강서구", "관악구",
		"광진구", "구로구", "금천구", "노원구", "도봉구", "동대문구", "동작구",
		"마포구", "서대문구", "서초구", "성동구",	"성북구", "송파구", "양천구",
		"영등포구", "용산구", "은평구", "종로구", "중구", "중랑구", "그 외" };
	//local information
	int mode, visitor_num, manage_num, search_num, search_time, search_reside;
	char search_name[20] = "";
	char id[11] = "byecovid19", pw[14] = "plzbyecovid19"; //Administrator ID and password
	char id_e[11] = "", pw_e[14] = ""; //The ID and password you enter.

	List *L; initList(&L); //Reset Visitor List
	Visitor *tmp;

	Hash R[26];	init_Hash(R, region); //Hashtable initialization

	while (1) //End program on 0 input
	{
		//initial greeting
		hello();

		//mode selection
		mode_menu();
		//Enter whether you are manager or visitor
		printf("Enter Mode number : ");   scanf("%d", &mode); printf("\n");

		//If you are a visitor
		if (mode == 1)
		{
			visitor_menu(); //Visitor menu output
			printf("Select Menu : "); scanf("%d", &visitor_num); //Enter Visitor Menu
			printf("\n");

			if (visitor_num == 1) //Add Visitors
				addVisitor(L, R, region);
			else if (visitor_num == 2) //Visitor Modification
				editVisitor(L, region);
			else //If the value entered is not valid
			{
				printf("\n\t\tInput Error!!\n"); //Warning Statement Output
				printf("\tEnter correct mode number again!!\n\n");
				continue; //Redo
			}
		}

		//If you are an administrator
		else if (mode == 2)
		{
			//Enter Administrator ID and Password
			printf("\nEnter administrator ID : "); scanf("%s", id_e);
			printf("Enter administrator PW : "); scanf("%s", pw_e); printf("\n");

			//If the ID and password you entered are correct
			if (strcmp(id, id_e) == 0 && strcmp(pw, pw_e) == 0)
			{
				printf("\n\t\tLog-in!\n"); //You are logged in!

				while (1) // Administrator mode until you enter 0 to log out
				{
					manager_menu(); //Admin menu
					printf("Select Manager Menu : "); scanf("%d", &manage_num); //menu selection

					if (manage_num == 1) //registration
						addVisitor(L, R, region);

					else if (manage_num == 2)  //modification
						editVisitor(L, region);

					else if (manage_num == 3) //delete
						deleteVisitor(L, R);

					else if (manage_num == 4) //print out all visitors
					{
						tmp = L->H;
						if (tmp->next == L->T) //there are no visitors
						{
							printf("\n\n\tNo visitors!!\n\n");
							continue;
						}
						//Select the order to sort when visitors are present
						printf("\n\t1. Sort by name\n"); printf("\t2. Sort by date\n"); printf("\t3. Sort by residence\n");
						printf("Enter number : "); scanf("%d", &search_num);

						if (search_num == 1) //search by name
						{
							print_byname(L, region);
							printf("\n");
						}
						else if (search_num == 2) //search by date
						{
							print_bydate(L, region);
							printf("\n");
						}
						else if (search_num == 3) //search by residence
						{
							print_byregion(R, region);
							printf("\n");
						}
						else //if input is invalid
						{
							printf("\n\n\t\t\tInput Error!\n"); //Output warning statement and re-enter
							printf("\t\tPlease re-enter menu number.\n\n");
							continue;
						}
					}
					else if (manage_num == 5) //Output specific information only
					{
						tmp = L->H;
						if (tmp->next == L->T) //there are no visitors
						{
							printf("\n\n\tNo visitors!!\n\n"); //Notify No Visitors
							continue;
						}
						// Select the option to look for when visitors are present
						printf("\n\t1. By name\n"); printf("\t2. By date\n"); printf("\t3. By residence code\n");
						printf("Enter number : "); scanf("%d", &search_num);

						if (search_num == 1) //search by name
						{
							printf("Enter the name of the guest you want to find : ");
							scanf("%s", search_name);   printf("\n"); //Enter the name you want to find
							search_byname(L, search_name, region);
							printf("\n");
						}
						else if (search_num == 2) //search by date
						{
							printf("Enter the date you want to find info : ");
							scanf("%d", &search_time);   printf("\n"); //Enter the date you want to find
							search_byday(L, search_time, region);
							printf("\n");
						}
						else if (search_num == 3) //search by residence
						{
							residence_menu(region);
							printf("\nEnter the resident code you want to find info : ");
							scanf("%d", &search_reside);   printf("\n"); //Enter the residence code you want to find
							search_byregion(R, search_reside, region);
							printf("\n");
						}
						else //if input is invalid
						{
							printf("\n\n\t\t\tInput Error!\n"); //Notify Not Valid
							printf("\t\tPlease re-enter menu number.\n\n");
							continue;
						}
					}

					//Log-out
					else if (manage_num == 0) //Log-out
					{
						printf("\n\tLog-out Complete!\n"); //You have been logged out!
						break; //exit repeating statement
					}

					else //if input value is invalid
					{
						printf("\n\t\tInput Error!!\n");
						printf("\tEnter correct mode number again!!\n\n");
						continue;
					}
				}
			}

			//If the ID and password entered are incorrect
			else
			{
				// Notify me that my ID and password are wrong
				printf("\n\tThe administrator's ID and password are incorrect!\n");
				printf("\t\tReturn to Initialization Plane\n\n");
				continue;
			}
		}
		//If 0 is entered, exit program
		else if (mode == 0)
			break;

		//If you enter an incorrect number for Admin & Visitor mode.
		else
		{
			// Notify that you entered it incorrectly
			printf("\n\t\tInput Error!!\n");
			printf("\tEnter correct mode number again!!\n\n");
			continue; //Re-run from the beginning of the repeating statement
		}

		//closing greeting
		bye();
	}

	printf("\n\tProgram ended\n\n"); //Notify me that the program is over
	return 0;
}