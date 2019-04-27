#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <time.h>
#include <ctype.h>
#include "bank.h"
#include "jsonbank.h"
// #define EMPLOYEES_LOGIN 0x0122
// #define EMPLOYEE_RESET_LOGIN 0x222
#define ACCOUNTS_PRINTING 0X322
#define EMPLOYEE_LOGIN 0x422
#define EMPLOYEES_DATA 0x522
#define EMPLOYEES_DATA 0x622

void free_login(login_t* login)
{
	memset(&(login->login_key[0]), 0, strlen(login->login_key));
	memset(&(login->login_id[0]), 0, strlen(login->login_id));
	login->status=BANK_OBJECT_NULL;
	if(login->uuid!=NULL)
	{
		memset(&(login->uuid[0]), 0, strlen(login->uuid));
	}
}

void free_individual(individual_t* individual)
{
	memset(&(individual->uuid[0]), 0, strlen(individual->uuid));
	memset(&(individual->birthdate[0]), 0, strlen(individual->birthdate));
	memset(&(individual->joineddate[0]), 0, strlen(individual->joineddate));
	memset(&(individual->mobile_phone[0]), 0, strlen(individual->mobile_phone));
	memset(&(individual->home_phone[0]), 0, strlen(individual->home_phone));

	free(individual->address_no1);
	free(individual->address_no2);
	free(individual->city);
	free(individual->email);
	free(individual->firstname);
	free(individual->lastname);
	individual->status=BANK_OBJECT_NULL;
	individual->agency=NULL;
	individual->bank_account[0]=NULL;
	individual->bank_account[1] = NULL;
	individual->bank_account[2] = NULL;
	individual->bank_account[3] = NULL;
	individual->login=NULL;
	individual->next=NULL;

	individual->zip_code=0;

}

void free_agency(agency_t* agency)
{
	free(agency->agency_address);

	memset(&(agency->uuid_agency[0]), 0, strlen(agency->uuid_agency));
	memset(&(agency->agency_code[0]), 0, strlen(agency->agency_code));
	memset(&(agency->agency_id[0]), 0, strlen(agency->agency_id));
	agency->state=NULL;
	agency->employees=NULL;
	agency->individuals=NULL;
	agency->logins=NULL;
	agency->bank_accounts=NULL;
	agency->next=NULL;

	agency->status=BANK_OBJECT_NULL;
}


void free_state(state_t* state)
{
	// memset(&(state->uuid_state[0]), 0, strlen(state->uuid_state));
	// memset(&(state->state_code[0]), 0, strlen(state->state_code));
	// state->status=BANK_OBJECT_NULL;
	state->agencies=NULL;
	// state->zip_code=0;
	// state->next=NULL;

}
void clear()
{
	char c;
	while (((c = getchar()) != '\n') )//&& (c != EOF) && (c != '\0'))
		;
}


int main(int argc, char *argv[])
{
	bank_t* data=bank();

	int ag_code, st_code;
	bank_json_parse_bank(data, 0, 0);


	char id[11], pass[11], *decoded;

	static state_t *state;
	static agency_t *agency;
	static individual_t *individual;
	static login_t *login;

	while(1)
	{


		printf("\n Enter q to quit or any other key to continue...");

		if (getchar() == 'q')
		{
			free(data);
			return 0;
		}

		while(1)
		{

			do
			{
				system("clear");
				printf("--------------------------------------------------\n");
				printf("--------------------EMPLOYEES LOGIN PAGE------------------\n");
				printf("\nEnter user ID:");

			} while (!scanf("%s", id));

			do
			{

				printf("\nEnter password:");

			} while (!scanf("%s", pass));

			decoded = login_id_decoder(id);

			if (decoded == NULL)
			{
				system("clear");
				printf("\nWRONG user ID or password\n");
				printf("Please try again!\n");
			}
			else
			{
				ag_code = atoi(decoded) / 100;
				st_code = atoi(decoded) % 100;

				printf("\nPlease wait...\n");
				state = bank_get_state_n(data, 1, st_code);

				if (state != NULL)
				{
					printf("\nPlease wait...\n");

					bank_json_parse_state(state, 0, 0, 0);

					printf("\nPlease wait...\n");

					agency = bank_state_get_agency_n(state, 1, ag_code);

					if (agency == NULL)
					{
						system("clear");
						printf("\nWRONG user ID or password\n");
						printf("Please try again!\n");

						free_state(state);
					}
					else
					{
						printf("\nPlease wait...\n");

						bank_json_parse_agency(agency, EMPLOYEE_LOGIN, 0, 0);

						if (bank_agency_get_logins(agency) != NULL)
						{
							login = bank_login();

							bank_login_set_key(login, pass);

							bank_login_set_id(login, id);

							login_t *results;

							printf("\nPlease wait...\n");

							if (!(results = bank_login_authenticate(bank_agency_get_logins(agency), login)))
							{
								system("clear");
								printf("\nWRONG user ID or password\n");
								printf("Please try again!\n");

								free_login(login);
								free_agency(agency);
								free_state(state);
								free(decoded);
							}
							else
							{
								system("clear");

								printf("---------------------------EMPLOYEE-----------------------\n");
								printf("Login Validated!\n");

								individual = bank_individual(BANK_ACCOUNT_EMPTY);

								bank_individual_set_login(individual, results);

								bank_individual_set_agency(individual, agency);

								printf("\nPlease wait...\n");

								bank_agency_free_logins(agency);

								bank_individual_set_status(individual, BANK_OBJECT_INIT);

								printf("\nPlease wait...\n");

								bank_json_parse_individual(individual, 1, JSON_ALLOW_NUL);

								break;
							}
						}
					}
				}
				else
				{
					system("clear");
					printf("\nWRONG user ID or password\n");
					printf("Please try again!\n");
					free(decoded);
				}
			}
		}
		unsigned int userchoice = 0;
		while (1)
		{
			clear();
			printf("\n---------------------------EMPLOYEE-----------------------\n");
			printf("\nEnter 1, 2, 3 or 4 to enter the correspondant menu or l to logout:\n\n");
			printf("1- Edit your personal informations\n");
			printf("2- View you personal informations\n");
			printf("3- View your bank accounts\n");
			printf("4- Export bank accounts activity in a CSV format\n");
			printf("5- Reset your password\n");

			do
			{
				userchoice = getchar();
				clear();
			} while ((userchoice > '5' || userchoice < '1') && userchoice != 'l');

			system("clear");

			switch (userchoice)
			{
			case '1':
				break;
			case '2':
				break;
			case '3':
				//bank account type
				switch (individual->bank_account[0]->bank_account_type)
				{
				case BANK_ACCOUNT_LDD:
					printf("\n\t---LDD---\n");
					break;
				case BANK_ACCOUNT_LIVRETJEUNE:
					printf("\n\t---Livretjeune---\n");
					break;
				case BANK_ACCOUNT_LIVRETA:
					printf("\n\t---LivretA---\n");
					break;
				case BANK_ACCOUNT_COURANT:
					printf("\n\t---Livretjeune---\n");

					break;
				case BANK_ACCOUNT_PEL:
					printf("\n\t---PEL---\n");
					break;
				default:
					break;
				}

				printf("\niban: %s\n", individual->bank_account[0]->iban);

				printf("\nbalance= %lf euros\n", individual->bank_account[0]->account_balance);

				printf("\nbank account number: %s\n", individual->bank_account[0]->account_no);

				//account type
				switch (individual->bank_account[0]->account_type)
				{
				case BANK_ACCOUNT_INDIVIDUAL:
					printf("\naccount type: AN INDIVIDUAL BANK ACCOUNT\n");
					break;
				case BANK_ACCOUNT_SHARED:
					printf("\naccount type: A SHARED BANK ACCOUNT\n");
					break;
				default:
					break;
				}

				printf("\naddress line 1: %s\n", individual->address_no1);

				printf("\naddress line 2: %s\n", individual->address_no2);

				printf("\nbirthdate: %.2s/%.2s/%.4s\n", individual->birthdate, individual->birthdate + 2, individual->birthdate + 4);

				printf("\ncity: %s\n", individual->city);

				printf("\nemail: %s\n", individual->email);

				printf("\nfirstname: %s\n", individual->firstname);

				printf("\nlastname: %s\n", individual->lastname);

				printf("\nemployee since: %s\n", individual->joineddate);

				printf("\nEnter any key to exit this view...");
				getchar();


				break;

			case '4':
				break;
			case '5':
				break;
			case 'q':

				free_login(login);
				free_individual(individual);
				free_agency(agency);
				free_state(state);
				free(bank);

				break;

			default:

				printf("Good Bye...\n");
				free_login(login);

				free_agency(agency);
				free_state(state);
				break;
			}
			if(userchoice=='l')
			{
				break;
			}
		}
	}



	return 0;
}