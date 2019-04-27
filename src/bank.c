#include "bank.h"


/* returns 0 if bank_account status is size_t flag,
	1 if it is not, and
		-1 if bank_account is NULL */
int bank_account_is_status(account_t *account, status_type flag)
{
	if (account == NULL)
		return -1;
	switch (flag)
	{
		case BANK_OBJECT_BLOCKED:
		{
			if(account->status== BANK_OBJECT_BLOCKED)
				return EXIT_SUCCESS;
			break;
		}
		case BANK_OBJECT_DELETED:
		{
			if (account->status == BANK_OBJECT_DELETED)
				return EXIT_SUCCESS;
			break;
		}
		case BANK_OBJECT_EMPTY:
		{
			if (account->status == BANK_OBJECT_EMPTY)
				return EXIT_SUCCESS;
			break;
		}
		case BANK_OBJECT_NULL:
		{
			if (account->status == BANK_OBJECT_NULL)
				return EXIT_SUCCESS;
			break;
		}
		case BANK_OBJECT_INIT:
		{
			if (account->status == BANK_OBJECT_INIT)
				return EXIT_SUCCESS;
			break;
		}
		default:
			break;
	}

	return EXIT_FAILURE;

}

int bank_account_set_status(account_t* account, status_type flag)
{
	if(account==NULL)
	{
		fprintf(stderr, "error bank_account_set_status\n");
		return EXIT_FAILURE;
	}
	account->status=flag;

	return EXIT_SUCCESS;
}
/*returns 0 if bank_account is shared between two,
	and 1 if not, and -1 if bank_account is NULL or EMPTY*/
int bank_account_is_shared(account_t *account)
{
	if (account == NULL)
		return -1;

	if(account->account_type==BANK_ACCOUNT_SHARED)
	{
		return EXIT_SUCCESS;
	}
	if (account->account_type == BANK_ACCOUNT_INDIVIDUAL)
		return EXIT_FAILURE;

	return -1;
}

/* returns 0 if bank_account is
	of type "size_t flag" and 1 if not
	-1 if NULL */
int bank_account_is_type(account_t *account, bank_account_type flag)
{
	if (account == NULL)
		return -1;
	switch (flag)
	{
	case BANK_ACCOUNT_LDD:
	{
		if (account->bank_account_type == BANK_ACCOUNT_LDD)
			return EXIT_SUCCESS;
		break;
	}
	case BANK_ACCOUNT_LIVRETA:
	{
		if (account->bank_account_type == BANK_ACCOUNT_LIVRETA)
			return EXIT_SUCCESS;
		break;
	}
	case BANK_ACCOUNT_PEL:
	{
		if (account->bank_account_type == BANK_ACCOUNT_PEL)
			return EXIT_SUCCESS;
		break;
	}
	case BANK_ACCOUNT_COURANT:
	{
		if (account->bank_account_type == BANK_ACCOUNT_COURANT)
			return EXIT_SUCCESS;
		break;
	}
	case BANK_ACCOUNT_LIVRETJEUNE:
	{
		if (account->bank_account_type == BANK_ACCOUNT_LIVRETJEUNE)
			return EXIT_SUCCESS;
		break;
	}
	default:
		break;
	}

	return EXIT_FAILURE;
}

/* generates a new uuid and add it to the bank_account
	then returns it, to replace uuid that exists use
		bank_account_set_uuid_new */
char* bank_account_set_uuid(account_t *account)
{
	if(account->status==BANK_OBJECT_NULL)
	{
		uuid_gen(account->uuid_account);
		uuid_gen(account->uuid_activity);

		account->status=BANK_OBJECT_EMPTY;

		return account->uuid_account;
	}else
	{
		fprintf(stderr, "error bank_account_set_uuid\n");
		return NULL;
	}
}

/* generates a new uuid and replaces bank_account's uuid if it has one
	returns 0 for success, and it
	returns 1 for failure i.e bank_account doesnt have a uuid */
int bank_account_set_uuid_new(account_t *account)
{
	if (account->status == BANK_OBJECT_EMPTY)
	{
		uuid_gen(account->uuid_account);
		return EXIT_SUCCESS;
	}
	else
	{
		fprintf(stderr, "error bank_account_set_uuid_new\n");
		return EXIT_FAILURE;
	}
}

/*sets the type of bank_account to
	size_t flag if not already set
	returns 0 success
		returns 1 failure i.e bank_account has type*/
int bank_account_set_type(account_t *account, bank_account_type type)
{
	if(account->bank_account_type==BANK_ACCOUNT_EMPTY)
	{
		switch (type)
		{
		case BANK_ACCOUNT_LDD:
		{
			account->bank_account_type = BANK_ACCOUNT_LDD;
			return EXIT_SUCCESS;

		}
		case BANK_ACCOUNT_LIVRETA:
		{
			account->bank_account_type = BANK_ACCOUNT_LIVRETA;
			return EXIT_SUCCESS;

		}
		case BANK_ACCOUNT_PEL:
		{
			account->bank_account_type = BANK_ACCOUNT_PEL;
			return EXIT_SUCCESS;
		}
		case BANK_ACCOUNT_COURANT:
		{
			account->bank_account_type = BANK_ACCOUNT_COURANT;
			return EXIT_SUCCESS;

		}
		case BANK_ACCOUNT_LIVRETJEUNE:
		{
			account->bank_account_type = BANK_ACCOUNT_LIVRETJEUNE;
			return EXIT_SUCCESS;

		}
		default:
			break;
		}
	}
	fprintf(stderr, "error bank_account_set_type\n");
	return EXIT_FAILURE;
}



/* Makes the individual_t
	passed as argument holder of bank_account
		if not already has one
		returns 0 on success
		return 1 on failure
			i.e account has a holder already */
int bank_account_set_holder(account_t *account, individual_t *holder)
{
	if (account == NULL )//|| account->status!=BANK_OBJECT_INIT || account->account_type == BANK_ACCOUNT_SHARED)
	{
		fprintf(stderr, "error bank_account_set_holder(1)\n");
		return EXIT_FAILURE;
	}
	if (account->account_holder[0] == NULL && account->account_holder[1] == NULL)
	{

		if(bank_individual_set_account(holder, account))
			return EXIT_FAILURE;

		account->account_holder[0]=holder;

		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_account_set_holder(2)\n");
	return EXIT_FAILURE;
}

/*Creates a new empty individual_t as a holder of bank_account and returns it
	if it fails it returns NULL */
individual_t* bank_account_set_new_holder(account_t *account)
{
	if (account == NULL || account->account_type == BANK_ACCOUNT_SHARED)
	{
		return NULL;
	}
	if (account->account_holder[0] == NULL && account->account_holder[1] == NULL)
	{
		account->account_holder[0]=bank_individual(BANK_ACCOUNT_INDIVIDUAL);

		if (!bank_individual_set_account(account->account_holder[0], account))
			return NULL;

		return account->account_holder[0];
	}
	fprintf(stderr, "error bank_account_set_new_holder\n");
	return NULL;
}


individual_t* bank_account_shared_set_new_holder(account_t *account)
{
	if (account == NULL || account->account_type!=BANK_ACCOUNT_SHARED)
	{
		fprintf(stderr, "error bank_account_shared_set_new_holder\n");
		return NULL;
	}
	if(account->account_holder[0]==NULL)
	{
		account->account_holder[0] = bank_individual(BANK_ACCOUNT_SHARED);

		if (bank_individual_set_account(account->account_holder[0], account))
			return NULL;

		return account->account_holder[0];
	}
	else
		if (account->account_holder[1] == NULL)
		{
			account->account_holder[1] = bank_individual(BANK_ACCOUNT_SHARED);

			if (bank_individual_set_account(account->account_holder[1], account))
				return NULL;

			return account->account_holder[1];
		}

	return NULL;
}

/* Adds a second holder for bank_account
	only if it is a shared account and has one holder already
		returns 0 on success
			1 on failure */
int bank_account_shared_set_holder(account_t *account, individual_t *holder)
{
	if (account == NULL || account->account_type != BANK_ACCOUNT_SHARED)
	{
		fprintf(stderr, "error bank_account_shared_set_holder(1)\n");
		return EXIT_FAILURE;
	}
	if (account->account_holder[0] == NULL)
	{

		if(bank_individual_set_account(holder, account))
		{
			fprintf(stderr, "error bank_account_shared_set_holder(2)\n");
			return EXIT_FAILURE;
		}

		account->account_holder[0] = holder;

		return EXIT_SUCCESS;
	}
	if (account->account_holder[1] == NULL)
	{
		if (bank_individual_set_account(holder, account))
		{
			fprintf(stderr, "error bank_account_shared_set_holder(3)\n");
			return EXIT_FAILURE;
		}

		account->account_holder[1] = holder;

		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_account_shared_set_holder(4)\n");
	return EXIT_FAILURE;
}


/*returns an empty bank account */
account_t* bank_account(bank_account_type type, account_type flag)
{
	account_t* account=(account_t*)calloc(1, sizeof(account_t));

	if(type>=BANK_ACCOUNT_EMPTY && type<=BANK_ACCOUNT_COURANT)
		account->bank_account_type=type;
	else
	{
		account->bank_account_type = BANK_ACCOUNT_EMPTY;
	}

	if(flag==BANK_ACCOUNT_INDIVIDUAL || flag==BANK_ACCOUNT_SHARED)
		account->account_type = flag;
	else
	{
		account->bank_account_type =BANK_ACCOUNT_NONE;
	}

	account->account_balance=0;

	account->status=BANK_OBJECT_NULL;

	account->account_holder[0]=NULL;
	account->account_holder[1]=NULL;

	return account;

}



agency_t* bank_account_get_agency(account_t *account)
{
	if (account == NULL || account->status == BANK_OBJECT_EMPTY || account->agency == NULL)
	{
		fprintf(stderr, "error bank_account_get_agency\n");
		return NULL;
	}
	return account->agency;
}

int bank_account_set_agency(account_t *account, agency_t* agency)
{
	if(account==NULL || agency==NULL || account->status!=BANK_OBJECT_EMPTY || agency->status==BANK_OBJECT_NULL)
	{
		fprintf(stderr, "error bank_account_set_agency\n");
		return EXIT_FAILURE;
	}

	account->agency=agency;
	return EXIT_SUCCESS;
}

int bank_account_remove_agency(account_t *account)
{
	if(account==NULL)
	{
		fprintf(stderr, "error bank_account_remove_agency\n");
		return EXIT_FAILURE;
	}

	account->agency= NULL;
	return EXIT_SUCCESS;
}

individual_t** bank_account_shared_get_holder(account_t *account)
{
	if (account == NULL || account->account_type != BANK_ACCOUNT_SHARED || account->account_holder == NULL)
	{
		fprintf(stderr, "error bank_account_shared_get_holder\n");
		return NULL;
	}
	return account->account_holder;
}

individual_t* bank_account_get_holder(account_t *account)
{
	if (account == NULL || account->account_type == BANK_ACCOUNT_SHARED || account->account_holder == NULL)
	{
		fprintf(stderr, "error bank_account_get_holder\n");
		return NULL;
	}
	return account->account_holder[0];
}




char* bank_account_get(account_t *account, size_t flag)
{
	char *res=malloc(11*sizeof(char));
	if (account == NULL || account->status == BANK_OBJECT_NULL || account->status == BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_account_get\n");
		return NULL;
	}
	switch(flag)
	{
		case BANK_ACCOUNT_UUID:
		{
			return account->uuid_account;
		}
		case BANK_ACCOUNT_OPERATIONS_UUID:
		{
			return account->uuid_activity;
		}
		case BANK_ACCOUNT_BALANCE:
		{
			sprintf(res, "%lf",  account->account_balance);
			return res;
		}
		case BANK_ACCOUNT_NO:
		{
			return ((account->iban)+13);
		}
		case BANK_ACCOUNT_IBAN:
			return account->iban;
		default:
			return NULL;

	}
}


/*bank_account has to be already in an agency
	for it to be able to get an IBAN and Account_no
	this function generates the appropriate IBAN and account_no for
	this bank_account */
int bank_account_set_iban(account_t *account)
{
	if(account->status!=BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_account_set_iban\n");
		return EXIT_FAILURE;
	}
	else
	{
		if(!strcpy(account->iban, iban_gen(account->agency->agency_id, account->agency->state->state_code)))
		{
			fprintf(stderr, "error bank_account_set_iban(2)\n");
			return EXIT_FAILURE;
		}

		sprintf(account->account_no, "%.11s",account->iban+14);

		account->account_no[11] = '\0';

		account->status=BANK_OBJECT_INIT;

		return EXIT_SUCCESS;
	}
}

int bank_account_money_depot(account_t *account, double money_amount, char currency)
{
	if (account == NULL || account->status != BANK_OBJECT_INIT || money_amount == 0)
	{
		fprintf(stderr, "error bank_account_money_depot\n");
		return EXIT_FAILURE;
	}

	switch (currency)
	{
	case 'E':
	{
		account->account_balance += money_amount;
		return EXIT_SUCCESS;
	}
	case '$':
	{
		account->account_balance += (money_amount * DOLLAR_TO_EURO);
		return EXIT_SUCCESS;
	}
	default:
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}

/*--------------------------------INDIVIDUAL--------------------------------*/

individual_t* bank_individual(size_t flag)
{
	individual_t* individual=(individual_t*)calloc(1, sizeof(individual_t));
	individual->status=BANK_OBJECT_NULL;
	switch(flag)
	{
		case BANK_ACCOUNT_SHARED:
		{
			individual->flag=BANK_ACCOUNT_SHARED;
			return individual;
		}
		case BANK_ACCOUNT_INDIVIDUAL:
		{
			individual->flag = BANK_ACCOUNT_INDIVIDUAL;
			return individual;
		}
		default:
			return individual;

	}
}




/*returns the status of an individual
	1 if false
	0 if true
	*/
int bank_individual_is_status(individual_t *individual, size_t status)
{
	if(individual->status==status)
		return 0;

	else
		return 1;
}

int bank_individual_set_status(individual_t* individual, status_type flag)
{
	if (individual == NULL)
	{
		fprintf(stderr, "error bank_individual_set_status\n");
		return EXIT_FAILURE;
	}
	individual->status = flag;

	return EXIT_SUCCESS;
}

char* bank_individual_set_uuid(individual_t *individual)
{
	if(individual->status==BANK_OBJECT_NULL)
	{
		uuid_gen(individual->uuid);

		individual->status=BANK_OBJECT_EMPTY;

		return individual->uuid;
	}
	fprintf(stderr, "error bank_individual_set_uuid\n");
	return NULL;
}

int bank_individual_set_sex(individual_t *individual, char sex)
{
	if (individual == NULL || individual->status != BANK_OBJECT_EMPTY )
	{
		fprintf(stderr, "error bank_individual_set_sex\n");
		return EXIT_FAILURE;
	}

	individual->sex = sex;
	return EXIT_SUCCESS;
}

int bank_individual_set_firstname(individual_t *individual, char* firstname)
{
	if(individual==NULL || individual->status!=BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_individual_set_firstname\n");
		return EXIT_FAILURE;
	}

	individual->firstname= (char*)calloc(strlen(firstname)+1, sizeof(char));

	strcpy(individual->firstname, firstname);

	return EXIT_SUCCESS;
}
int bank_individual_set_lastname(individual_t *individual, char *lastname)
{
	if (individual == NULL || individual->status != BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_individual_set_lastname\n");
		return EXIT_FAILURE;
	}
	individual->lastname = (char *)calloc(strlen(lastname) + 1, sizeof(char));

	strcpy(individual->lastname, lastname);

	return EXIT_SUCCESS;
}

int bank_individual_set_birthdate(individual_t *individual, char *birthdate)
{
	if (individual == NULL || individual->status != BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_individual_set_birthdate\n");
		return EXIT_FAILURE;
	}

	strcpy(individual->birthdate, birthdate);
	return EXIT_SUCCESS;
}
int bank_individual_set_email(individual_t *individual, char *email)
{
	if (individual == NULL || ( individual->status != BANK_OBJECT_INIT && individual->status != BANK_OBJECT_EMPTY))
	{
		fprintf(stderr, "error bank_individual_set_email\n");
		return EXIT_FAILURE;
	}

	if(individual->email!=NULL)
	{
		memset(&(individual->email[0]),0, strlen(individual->email));

		free((individual->email));
	}
	individual->email = (char *)calloc(strlen(email) + 1, sizeof(char));

	strcpy(individual->email, email);

	return EXIT_SUCCESS;
}

int bank_individual_set_address_no1(individual_t *individual, char *address_no1)
{
	if (individual == NULL || (individual->status != BANK_OBJECT_INIT && individual->status != BANK_OBJECT_EMPTY))
	{
		fprintf(stderr, "error bank_individual_set_address_no1\n");
		return EXIT_FAILURE;
	}
	if (individual->address_no1 != NULL)
	{
		memset(&(individual->address_no1[0]), 0, strlen(individual->address_no1));

		free((individual->address_no1));
	}

	individual->address_no1 = (char *)calloc(strlen(address_no1) + 1, sizeof(char));

	strcpy(individual->address_no1, address_no1);

	return EXIT_SUCCESS;
}

int bank_individual_set_address_no2(individual_t *individual, char *address_no2)
{
	if (individual == NULL || (individual->status != BANK_OBJECT_INIT && individual->status != BANK_OBJECT_EMPTY))
	{
		fprintf(stderr, "error bank_individual_set_address_no2\n");
		return EXIT_FAILURE;
	}

	if (individual->address_no2 != NULL)
	{
		memset(&(individual->address_no2[0]), 0, strlen(individual->address_no2));

		free((individual->address_no2));
	}

	individual->address_no2 = (char *)calloc(strlen(address_no2) + 1, sizeof(char));

	strcpy(individual->address_no2, address_no2);

	return EXIT_SUCCESS;
}

int bank_individual_set_city(individual_t *individual, char *city)
{
	if (individual == NULL || (individual->status != BANK_OBJECT_INIT && individual->status != BANK_OBJECT_EMPTY))
	{
		fprintf(stderr, "error bank_individual_set_city\n");
		return EXIT_FAILURE;
	}
	if (individual->city != NULL)
	{
		memset(&(individual->city[0]), 0, strlen(individual->city));

		free((individual->city));
	}
	individual->city = (char *)calloc(strlen(city) + 1, sizeof(char));

	strcpy(individual->city, city);

	return EXIT_SUCCESS;
}

int bank_individual_set_zipcode(individual_t *individual, int zipcode)
{
	if (individual == NULL || (individual->status != BANK_OBJECT_INIT && individual->status != BANK_OBJECT_EMPTY))
	{
		fprintf(stderr, "error bank_individual_set_zipcode\n");
		return EXIT_FAILURE;
	}

	individual->zip_code=zipcode;

	return EXIT_SUCCESS;
}

int bank_individual_set_mobilephone(individual_t *individual, char* mobile_phone)
{
	if (individual == NULL || (individual->status != BANK_OBJECT_INIT && individual->status != BANK_OBJECT_EMPTY))
	{
		fprintf(stderr, "error bank_individual_set_mobilephone\n");
		return EXIT_FAILURE;
	}

	strcpy(individual->mobile_phone , mobile_phone);
	return EXIT_SUCCESS;
}

int bank_individual_set_home_phone(individual_t *individual, char *home_phone)
{
	if (individual == NULL || (individual->status != BANK_OBJECT_INIT && individual->status != BANK_OBJECT_EMPTY))
	{
		fprintf(stderr, "error bank_individual_set_home_phone\n");
		return EXIT_FAILURE;
	}

	strcpy(individual->home_phone, home_phone);
	return EXIT_SUCCESS;
}
int bank_individual_set_idcard(individual_t *individual, char *id_card_no)
{
	if (individual == NULL || (individual->status != BANK_OBJECT_INIT && individual->status != BANK_OBJECT_EMPTY))
	{
		fprintf(stderr, "error bank_individual_set_idcard\n");
		return EXIT_FAILURE;
	}
	if (individual->id_card_no != NULL)
	{
		memset(&(individual->id_card_no[0]), 0, strlen(individual->id_card_no));

		free((individual->id_card_no));
	}
	individual->id_card_no = (char *)calloc(strlen(id_card_no) + 1, sizeof(char));

	strcpy(individual->id_card_no, id_card_no);

	return EXIT_SUCCESS;
}
int bank_individual_set_joindate(individual_t *individual, char* date)
{
	if (individual == NULL || individual->status != BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_individual_set_joindate\n");
		return EXIT_FAILURE;
	}

	strcpy(individual->joineddate, date);

	return EXIT_SUCCESS;
}

int bank_individual_has_account(individual_t *individual)
{
	if (individual->bank_account[0] != NULL && (individual->flag == BANK_ACCOUNT_SHARED || individual->flag == BANK_ACCOUNT_INDIVIDUAL))
		return EXIT_SUCCESS;
	return EXIT_FAILURE;
}


char* bank_individual_set_uuid_new(individual_t *individual, char* uuid)
{
	if(individual!=NULL)
	{
		strcpy(individual->uuid, uuid);

		individual->status=BANK_OBJECT_EMPTY;

		return individual->uuid;
	}
	fprintf(stderr, "error bank_individual_set_uuid_new\n");
	return NULL;
}


int bank_individual_set_account(individual_t *individual, account_t *account)
{
	if (individual->flag == BANK_ACCOUNT_SHARED)
	{
		if (account->account_type== BANK_ACCOUNT_SHARED && individual->bank_account[0]==NULL)
		{
			if(!bank_agency_account_add(account))
				return EXIT_FAILURE;

			individual->bank_account[0]=account;

			return EXIT_SUCCESS;
		}
		if (account->account_type== BANK_ACCOUNT_SHARED && individual->bank_account[0]!=NULL)
		{
			return EXIT_FAILURE;
		}

	}

	individual->flag=account->account_type;

	int i;

	for(i=0;i<4;i++)
	{
		if(individual->bank_account[i]==NULL)
		{
			individual->bank_account[i]=account;
			return EXIT_SUCCESS;
		}
	}
	fprintf(stderr, "error bank_individual_set_account\n");
	return EXIT_FAILURE;
}


account_t* bank_individual_set_new_empty_account(individual_t *individual)
{
	if(individual->flag==BANK_ACCOUNT_SHARED && individual->bank_account[0]==NULL)
	{
		individual->bank_account[0] = bank_account(BANK_ACCOUNT_EMPTY, BANK_ACCOUNT_SHARED);
		individual->bank_account[0]->account_holder[0]=individual;
	}

	int i;

	for (i = 0; i < 4; i++)
	{
		if (individual->bank_account[i] == NULL)
		{
			individual->bank_account[i] = bank_account(BANK_ACCOUNT_EMPTY, BANK_ACCOUNT_INDIVIDUAL);

			return individual->bank_account[i];
		}
	}
	fprintf(stderr, "error bank_individual_set_new_empty_account\n");
	return NULL;
}


int bank_individual_set_login(individual_t *individual, login_t *login)
{
	if(individual->login==NULL && login->status==BANK_LOGIN_ENCRYPTED)
	{
		login_t* login_new=bank_login();
		login_new->status=BANK_LOGIN_ENCRYPTED;
		strcpy(login_new->login_id,login->login_id);
		strcpy(login_new->login_key,login->login_key);

		if(login->uuid!=NULL)
		{

			strcpy(individual->uuid, login->uuid);
		}

		individual->login=login_new;
		individual->status = BANK_OBJECT_INIT;

		memset(&(login->login_key[0]), 0, strlen(login->login_key));
		memset(&(login->login_id[0]), 0, strlen(login->login_id));



		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_individual_set_login\n");
	return EXIT_FAILURE;
}


login_t* bank_individual_set_new_login(individual_t *individual, char* pass)
{
	if(individual->login!=NULL || individual->agency==NULL)
	{
		fprintf(stderr, "error bank_individual_set_new_login\n");
		return NULL;
	}

	login_t *login=bank_login_generate(individual->agency);

	bank_login_set_key(login, pass);

	encrypt_login_pass(login);

	individual->login=login;

	individual->status=BANK_OBJECT_INIT;

	memset(&(pass[0]), 0, strlen(pass));

	return login;

}


int bank_individual_authenticate_login(login_t* login_private, login_t *login)
{
	if (login_private == NULL || login->status == BANK_LOGIN_ENCRYPTED)
	{
		fprintf(stderr, "error bank_individual_authenticate_login\n");
		return EXIT_FAILURE;
	}

	if(validate_login(login_private, login))
		return EXIT_FAILURE;

	memset(&(login->login_key[0]), 0, strlen(login->login_key));
	memset(&(login->login_id[0]), 0, strlen(login->login_id));

	return EXIT_SUCCESS;
}


int bank_individual_reset_login(individual_t *individual, login_t *login, char* newpass)
{
	if(bank_individual_authenticate_login(individual->login, login))
		return EXIT_FAILURE;

	if (bank_login_set_key(individual->login, newpass))
		return EXIT_FAILURE;


	if(encrypt_login_pass(individual->login))
		return EXIT_FAILURE;

	memset(&(login->login_key[0]), 0, strlen(login->login_key));
	memset(&(login->login_id[0]), 0, strlen(login->login_id));
	memset(&(newpass[0]), 0, strlen(newpass));

	return EXIT_SUCCESS;
}



char* bank_individual_get(individual_t *individual, size_t flag)
{
	if(individual==NULL)
	{
		fprintf(stderr, "error bank_individual_get\n");
		return NULL;
	}
	switch(flag)
	{
		case BANK_INDIVIDUAL_UUID:
		{
			return individual->uuid;

		}
		case BANK_INDIVIDUAL_SEX:
		{
			return &(individual->sex);
		}
		case BANK_INDIVIDUAL_LASTNAME:
		{
			return individual->lastname;
		}
		case BANK_INDIVIDUAL_FIRSTNAME:
		{
			return individual->firstname;
		}
		case BANK_INDIVIDUAL_BIRTHDATE:
		{
			return individual->birthdate;
		}
		case BANK_INDIVIDUAL_EMAIL:
		{
			return individual->email;
		}
		case BANK_INDIVIDUAL_ADDRESSE_1:
		{
			return individual->address_no1;
		}
		case BANK_INDIVIDUAL_ADDRESSE_2:
		{
			return individual->address_no2;
		}
		case BANK_INDIVIDUAL_CITY:
		{
			return individual->city;
		}
		case BANK_INDIVIDUAL_ZIPCODE:
		{
			char *zip=malloc(6*sizeof(char));
			sprintf(zip, "%05d", individual->zip_code);
			return zip;
		}
		case BANK_INDIVIDUAL_MOBILE:
		{
			return individual->mobile_phone;
		}
		case BANK_INDIVIDUAL_HOME:
		{
			return individual->home_phone;
		}
		case BANK_INDIVIDUAL_ID_CARD:
		{
			return individual->id_card_no;
		}
		case BANK_INDIVIDUAL_JOIN_DATE:
		{
			return individual->joineddate;
		}
		default:
			break;
	}
	fprintf(stderr, "error bank_individual_get\n");
	return NULL;
}




/*if individual_t has more than one
	it returns the one of type flag*/
account_t* bank_individual_get_account(individual_t *individual, bank_account_type type)
{
	if(individual->bank_account!=NULL && individual->status!=BANK_OBJECT_INIT)
	{
		if(type==0)
		{
			return individual->bank_account[0];
		}
		int i;
		for(i=0; i<4; i++)
		{
			if(individual->bank_account[i]->bank_account_type==type)
			{
				return individual->bank_account[i];
			}
		}
	}
	fprintf(stderr, "error bank_individual_get_account\n");
	return NULL;
}




login_t* bank_individual_get_login(individual_t *individual)
{
	if(individual!=NULL && individual->status==BANK_OBJECT_INIT)
	{
		return individual->login;
	}
	fprintf(stderr, "error bank_individual_get_login\n");
	return NULL;
}


int bank_individual_set_agency(individual_t *individual, agency_t* agency)
{
	if(individual==NULL )//|| individual->status==BANK_OBJECT_NULL || agency==NULL || agency->status!=BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_individual_set_agency\n");
		return EXIT_FAILURE;
	}

	individual->agency=agency;

	return EXIT_SUCCESS;
}
int bank_individual_remove_agency(individual_t *individual)
{
	if(individual==NULL)
	{
		fprintf(stderr, "error bank_individual_remove_agency\n");
		return EXIT_FAILURE;
	}

	individual->agency=NULL;

	return EXIT_SUCCESS;
}
agency_t* bank_individual_get_agency(individual_t *individual)
{
	if (individual != NULL && individual->agency!=NULL)
	{
		return individual->agency;
	}

	fprintf(stderr, "error bank_individual_get_agency\n");
	return NULL;
}

individual_t *bank_search_individual(agency_t *agency, char *firstname, char *lastname, char *birthdate)
{
	if (agency == NULL || agency->individuals == NULL || agency->status != BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error search_individual\n");
		return NULL;
	}
	individual_t *iter = agency->individuals;

	do
	{
		if (strcmp(iter->firstname, firstname) == 0)
		{
			if (strcmp(iter->lastname, lastname) == 0)
			{
				if (bank_json_parse_individual(iter, 0, 0))
				{
					fprintf(stderr, "error search_individual (1)");
					return NULL;
				}

				if (strcmp(iter->birthdate, birthdate) == 0)
				{
					return iter;
				}
			}
		}
		iter = iter->next;

	} while (iter != NULL);

	return NULL;
}

/* -------------------------------------EMPLOYEES-------------------------------*/


employee_t* bank_employee(employee_position position)
{
	employee_t *employee= (employee_t*)calloc(1, sizeof(employee_t));
	employee->status=BANK_OBJECT_EMPTY;
	employee->position=position;

	return employee;
}

int bank_employee_is_position(employee_t *employee, employee_position position)
{
	switch(position)
	{
		case BANK_EMPLOYEE_ADVISOR:
		{
			if(employee->position==BANK_EMPLOYEE_ADVISOR)
			{
				return EXIT_SUCCESS;
			}
			break;
		}
		case BANK_EMPLOYEE_MANAGER:
		{
			if (employee->position == BANK_EMPLOYEE_MANAGER)
			{
				return EXIT_SUCCESS;
			}
			break;
		}
		case BANK_EMPLOYEE_ASSISTANT:
		{
			if (employee->position == BANK_EMPLOYEE_ASSISTANT)
			{
				return EXIT_SUCCESS;
			}
			break;
		}
		case BANK_EMPLOYEE_UKNOWN_POSITION:
		{
			if (employee->position == BANK_EMPLOYEE_UKNOWN_POSITION)
			{
				return EXIT_SUCCESS;
			}
			break;
		}
		default:
			return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}


int bank_employee_is_status(employee_t *employee, status_type flag)
{
	switch (flag)
	{
	case BANK_OBJECT_BLOCKED:
	{
		if (employee->status == BANK_OBJECT_BLOCKED)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	case BANK_OBJECT_DELETED:
	{
		if (employee->status == BANK_OBJECT_DELETED)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	case BANK_OBJECT_EMPTY:
	{
		if (employee->status == BANK_OBJECT_EMPTY)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	case BANK_OBJECT_INIT:
	{
		if (employee->status == BANK_OBJECT_INIT)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	case BANK_OBJECT_NULL:
	{
		if (employee->status == BANK_OBJECT_NULL)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	default:
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}



// char* bank_employee_set_uuid(employee_t *employee)
// {
// 	if (employee->status == BANK_OBJECT_NULL)
// 	{
// 		uuid_gen(employee->uuid_employee);

// 		employee->status = BANK_OBJECT_EMPTY;

// 		return employee->uuid_employee;
// 	}
// 	else
// 	{
// 		fprintf(stderr, "error bank_employee_set_uuid\n");
// 		return NULL;
// 	}
// }



// int bank_employee_set_uuid_new(employee_t *employee)
// {
// 	if (employee->status == BANK_OBJECT_EMPTY)
// 	{
// 		uuid_gen(employee->uuid_employee);
// 		return EXIT_SUCCESS;
// 	}
// 	else
// 	{
// 		fprintf(stderr, "error bank_employee_set_uuid_new\n");
// 		return EXIT_FAILURE;
// 	}
// }

int bank_employee_set_individual(employee_t *employee, individual_t* individual)
{
	if (employee == NULL || employee->status != BANK_OBJECT_EMPTY|| individual==NULL || individual->status!= BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_employee_set_individual\n");
		return EXIT_FAILURE;
	}
	employee->personal_data=individual;
	employee->status=BANK_OBJECT_INIT;
	return EXIT_SUCCESS;
}
int bank_employee_set_login(employee_t *employee, login_t *login)
{
	if(employee==NULL || employee->status!=BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_employee_set_login\n");
		return EXIT_FAILURE;
	}
	return bank_individual_set_login(employee->personal_data, login);
}


login_t* bank_employee_set_new_login(employee_t *employee, char* pass)
{
	if (employee == NULL || employee->status != BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_employee_set_new_login\n");
		return NULL;
	}
	login_t* login=bank_individual_set_new_login(employee->personal_data, pass);


	return login;
}



int bank_employee_reset_login(employee_t *employee, login_t *login, char* newpass)
{
	if (employee == NULL || employee->status != BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_employee_reset_login\n");
		return EXIT_FAILURE;
	}
	int res= bank_individual_reset_login(employee->personal_data, login, newpass);
	employee->personal_data->login->status=BANK_LOGIN_EMP;

	return res;
}



int bank_employee_authenticate_login(employee_t *employee, login_t *login)
{
	if (employee == NULL || employee->status != BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_employee_authenticate_login\n");
		return EXIT_FAILURE;
	}
	return bank_individual_authenticate_login(employee->personal_data->login, login);
}

int bank_employee_set_agency(employee_t* employee, agency_t *agency)
{
	if (employee == NULL || employee->status != BANK_OBJECT_INIT || agency == NULL || agency->status != BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_employee_set_agency\n");

		return EXIT_FAILURE;
	}

	employee->agency=agency;
	return EXIT_SUCCESS;
}


int bank_employee_remove_agency(employee_t *employee)
{
	if(employee==NULL)
	{
		fprintf(stderr, "error bank_employee_remove_agency\n");

		return EXIT_FAILURE;
	}
	employee->agency=NULL;
	return EXIT_SUCCESS;
}
/* -------------------------------------LOGIN-------------------------------*/

login_t* bank_login()
{
	login_t *login = (login_t *)calloc(1, sizeof(login_t));
	login->status=BANK_OBJECT_NULL;

	return login;
}

login_t* bank_login_generate(agency_t *agency)
{
	login_t *login = bank_login();

	int code[4];

	code[0] = atoi(agency->agency_code) / 10;
	code[1] = atoi(agency->agency_code) % 10;
	code[2] = atoi(agency->state->state_code) / 10;
	code[3] = atoi(agency->state->state_code) % 10;

	strcpy(login->login_id, login_id_generator(code));

	return login;
}

int bank_login_set_key(login_t* login, char* key)
{
	if( login!=NULL)
	{

		strcpy(login->login_key, key);
		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_login_set_key\n");
	return EXIT_FAILURE;
}

int bank_login_set_status(login_t* login, status_type flag)
{
	if(login==NULL)
	{
		return EXIT_FAILURE;
	}

	login->status=flag;

	return EXIT_SUCCESS;
}
int bank_login_set_id(login_t* login, char* id)
{
	if (login != NULL)
	{
		strcpy(login->login_id, id);
		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_login_set_id\n");
	return EXIT_FAILURE;
}





login_t* bank_login_authenticate(login_t* list, login_t* login)
{
	if(list== NULL || login==NULL)
	{
		fprintf(stderr, "error bank_login_authenticate: NULL arg, aborting\n");
		abort();
		exit(EXIT_FAILURE);
	}

	login_t* private=list;

	while(private!=NULL)
	{
		if(!bank_individual_authenticate_login(private, login))
		{
			return private;
		}
		private=private->next;
	}

	return NULL;
}




/* -------------------------------------AGENCY-------------------------------*/


agency_t* bank_agency()
{
	agency_t *agency=(agency_t*)calloc(1, sizeof(agency_t));
	agency->status=BANK_OBJECT_NULL;

	return agency;
}


int bank_agency_is_status(agency_t *agency, status_type flag)
{
	switch (flag)
	{
	case BANK_OBJECT_BLOCKED:
	{
		if (agency->status == BANK_OBJECT_BLOCKED)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	case BANK_OBJECT_DELETED:
	{
		if (agency->status == BANK_OBJECT_DELETED)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	case BANK_OBJECT_EMPTY:
	{
		if (agency->status == BANK_OBJECT_EMPTY)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	case BANK_OBJECT_INIT:
	{
		if (agency->status == BANK_OBJECT_INIT)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	case BANK_OBJECT_NULL:
	{
		if (agency->status == BANK_OBJECT_NULL)
		{
			return EXIT_SUCCESS;
		}
		break;
	}
	default:
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}

char *bank_agency_set_uuid(agency_t *agency)
{
	if (agency->status == BANK_OBJECT_NULL)
	{
		uuid_gen(agency->uuid_agency);

		agency->status = BANK_OBJECT_EMPTY;

		return agency->uuid_agency;
	}
	else
	{
		fprintf(stderr, "error bank_agency_set_uuid\n");
		return NULL;
	}

}

login_t* bank_agency_get_logins(agency_t *agency)
{
	if(agency==NULL || agency->logins==NULL)
	{
		fprintf(stderr, "error bank_agency_get_logins\n");
		return NULL;
	}

	return agency->logins;


}

int bank_agency_free_logins(agency_t *agency)
{
	if(agency==NULL || agency->logins==NULL)
	{
		fprintf(stderr, "error bank_agency_get_logins\n");
		return EXIT_FAILURE;
	}

	login_t* logins=agency->logins;

	while(logins!=NULL)
	{
		login_t* tofree=logins;

		logins=logins->next;

		memset(&(tofree->login_key[0]), 0, strlen(tofree->login_key));
		memset(&(tofree->login_id[0]), 0, strlen(tofree->login_id));

		if (tofree->uuid!=NULL)
		{
			free(tofree->uuid);
		}
		free(tofree);

	}

	return EXIT_SUCCESS;


}
int bank_free_logins(login_t* login)
{
	if(login==NULL)
	{
		fprintf(stderr, "error bank_agency_get_logins\n");
		return EXIT_FAILURE;
	}

	login_t* logins=login;

	while(logins!=NULL)
	{
		login_t* tofree=logins;

		logins=logins->next;

		memset(&(tofree->login_key[0]), 0, strlen(tofree->login_key));
		memset(&(tofree->login_id[0]), 0, strlen(tofree->login_id));

		if (tofree->uuid!=NULL)
		{
			free(tofree->uuid);
		}
		free(tofree);

	}

	return EXIT_SUCCESS;


}

int bank_agency_has_id(agency_t *agency)
{
	if(agency!= NULL && agency->status==BANK_OBJECT_INIT)
	{
		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_agency_has_id\n");
	return EXIT_FAILURE;
}

int bank_agency_set_id(agency_t *agency, char* id)
{
	if (agency != NULL && agency->status == BANK_OBJECT_EMPTY)
	{
		strcpy(agency->agency_id, id);
		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_agency_set_id\n");
	return EXIT_FAILURE;
}

int bank_agency_set_address(agency_t *agency, char* address)
{
	if (agency != NULL && agency->status == BANK_OBJECT_EMPTY)
	{
		agency->agency_address=(char*)calloc(strlen(address)+1, sizeof(char));
		strcpy(agency->agency_address, address);
		agency->status = BANK_OBJECT_INIT;
		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_agency_set_address\n");
	return EXIT_FAILURE;
}

int bank_agency_set_code(agency_t *agency, int agencycode)
{
	if (agency != NULL && agency->status == BANK_OBJECT_EMPTY)
	{


		agency->agency_code[0] = 48 + agencycode / 10;
		agency->agency_code[1] = 48 + agencycode % 10;
		agency->agency_code[2] = '\0';

		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_agency_set_code\n");
	return EXIT_FAILURE;
}


char *bank_agency_get(agency_t *agency, size_t flag)
{
	if(agency==NULL)
	{
		fprintf(stderr, "error bank_agency_get\n");
		return NULL;
	}
	switch(flag)
	{
		case BANK_AGENCY_UUID:
		{
			return agency->uuid_agency;
		}
		case BANK_AGENCY_ID:
		{
			return agency->agency_id;
		}
		case BANK_AGENCY_ADDRESS:
		{
			return agency->agency_address;
		}
		case BANK_AGENCY_CODE:
		{
			return agency->agency_code;
		}
		default:
			break;
	}
	return NULL;
}


individual_t* bank_agency_get_individuals(agency_t *agency)
{
	if(agency->status!=BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_agency_get_individuals\n");
		return NULL;
	}

	return agency->individuals;
}

account_t* bank_agency_get_accounts(agency_t *agency)
{
	if(agency->status!=BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_agency_get_accounts\n");
		return NULL;
	}
	return agency->bank_accounts;
}

employee_t* bank_agency_get_employees(agency_t *agency)
{
	if(agency->status!=BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_agency_get_employees\n");
		return NULL;
	}

	return agency->employees;
}

state_t* bank_agency_get_state(agency_t *agency)
{
	if (agency->status != BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_agency_get_state\n");
		return NULL;
	}

	return agency->state;
}


/* THIS FUNCTIONS WILL BE ONLY AVAILABLE TO PRIVILEGED EMPLOYEE OR ADMINS */

int bank_agency_account_add(account_t *account)
{
	if(account==NULL || account->agency==NULL || account->next!=NULL || account->status!=BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_agency_account_add(0)\n");
		return EXIT_FAILURE;
	}

	account_t* list = account->agency->bank_accounts;

	if(list==NULL)
	{
		account->agency->bank_accounts=account;
		return EXIT_SUCCESS;
	}

	do
	{
		if (strcmp(list->uuid_account, account->uuid_account)==0 || strcmp(list->iban, account->iban)==0)
		{
			fprintf(stderr, "error bank_agency_account_add(2)\n");
			return EXIT_FAILURE;
		}
		list=list->next;
	}while(list!=NULL);

	/*FIFO*/
	account->next=account->agency->bank_accounts;

	account->agency->bank_accounts=account;

	return EXIT_SUCCESS;


}

int bank_agency_individual_add(individual_t *individual)
{
	if(individual==NULL || individual->agency==NULL || individual->next!=NULL || individual->status!=BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_agency_individual_add(1)\n");
		return EXIT_FAILURE;
	}

	individual_t* list = individual->agency->individuals;

	if (list == NULL)
	{
		individual->agency->individuals=individual;
		return EXIT_SUCCESS;
	}

	do
	{
		if (strcmp(list->uuid, individual->uuid)==0 || strcmp(list->id_card_no, individual->id_card_no)==0 || strcmp(list->login->login_id, individual->login->login_id)==0)
		{
			return EXIT_FAILURE;
		}
		list=list->next;
	}while(list!=NULL);

	/*FIFO*/
	individual->next=individual->agency->individuals;

	individual->agency->individuals=individual;

	return EXIT_SUCCESS;


}

int bank_agency_employee_add(employee_t *employee)
{
	if(employee==NULL || employee->agency==NULL || employee->next!=NULL || employee->status!=BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_agency_employee_add\n");

		return EXIT_FAILURE;
	}

	employee_t* list = employee->agency->employees;

	if (list == NULL)
	{
		employee->agency->employees=employee;
		return EXIT_SUCCESS;
	}
	do
	{
		if (strcmp(list->personal_data->uuid, employee->personal_data->uuid)==0)
		{
			return EXIT_FAILURE;
		}
		list=list->next;
	}while(list!=NULL);

	/*FIFO*/
	employee->next=employee->agency->employees;

	employee->agency->employees=employee;

	return EXIT_SUCCESS;


}












/* -----------------------------------STATE-------------------------------*/




state_t* bank_state()
{
	state_t* state=(state_t*)calloc(1, sizeof(state_t));

	state->status=BANK_OBJECT_NULL;

	return state;
}


int bank_state_set_status_empty(state_t* state)
{
	if(state!=NULL)
	{
		state->status=BANK_OBJECT_EMPTY;
		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_state_set_status\n");
	return EXIT_FAILURE;
}
int bank_state_set_status_init(state_t* state)
{
	if(state!=NULL)
	{
		state->status=BANK_OBJECT_INIT;
		return EXIT_SUCCESS;
	}
	fprintf(stderr, "error bank_state_set_status\n");
	return EXIT_FAILURE;
}


char* bank_state_set_uuid(state_t* state)
{

	if (state->status == BANK_OBJECT_NULL)
	{
		uuid_gen(state->uuid_state);

		state->status = BANK_OBJECT_EMPTY;

		return state->uuid_state;
	}
	else
	{
		fprintf(stderr, "error bank_state_set_uuid\n");
		return NULL;
	}
}

int bank_state_set_zipcode(state_t* state, int zipcode)
{
	if(zipcode < 1 || zipcode > 99)
	{
		fprintf(stderr, "error bank_state_set_zipcode(1)\n");
		return EXIT_FAILURE;
	}

	if (state->status == BANK_OBJECT_EMPTY)
	{
		state->zip_code=zipcode;

		return EXIT_SUCCESS;
	}
	else
	{

		fprintf(stderr, "error bank_state_set_zipcode(2)\n");
		return EXIT_FAILURE;
	}
}

int bank_state_set_statecode(state_t* state, int statecode)
{
	if(!(statecode>0 && statecode<100))
	{
		fprintf(stderr, "error bank_state_set_statecode\n");
		return EXIT_FAILURE;
	}

	if (state->status == BANK_OBJECT_EMPTY)
	{

		state->state_code[0]= 48 + statecode / 10;
		state->state_code[1]= 48 + statecode % 10;
		state->state_code[2]= '\0';



		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
}

char *bank_state_get(state_t* state, size_t flag)
{
	if (state == NULL)
	{
		return NULL;
	}
	switch (flag)
	{
	case BANK_STATE_UUID:
	{
		return state->uuid_state;
	}
	case BANK_STATE_ZIPCODE:
	{
		return &(state->zip_code);
	}
	case BANK_STATE_CODE:
	{
		return state->state_code;
	}
	default:
		break;
	}
	return NULL;
}

agency_t* bank_state_get_empty_agency(state_t* state)
{
	if (state == NULL || state->status == BANK_OBJECT_NULL || state->agencies == NULL)
	{
		fprintf(stderr, "error bank_state_get_empty_agency(1)\n");
		return NULL;
	}
	agency_t *agency = state->agencies;

	while (agency->status != BANK_OBJECT_EMPTY)
	{
		if (agency->next == NULL)
		{
			fprintf(stderr, "error bank_state_get_empty_agency(2)\n");
			return NULL;
		}
		agency = agency->next;
	}
	return agency;
}

agency_t* bank_state_get_agencies(state_t* state)
{
	if (state == NULL || state->agencies == NULL)
	{
		fprintf(stderr, "error bank_state_get_agencies\n");

		return NULL;
	}

	return state->agencies;
}

/* option=0 for ID, 1 for CODE ,  else for ADDRESS*/
agency_t *bank_state_get_agency_n(state_t* state, int option, size_t num, char* address)
{
	if (state == NULL)
	{
		fprintf(stderr, "error bank_state_get_agency_n(1)\n");
		return NULL;
	}

	agency_t* agency=state->agencies;

	if (agency == NULL)
	{
		fprintf(stderr, "error bank_state_get_agency_n(2)\n");

		return NULL;
	}

	if(option==0)
	{
		do
		{
			if (atoi(agency->agency_id) == num)
			{
				return agency;
			}
			agency = agency->next;

		} while (agency != NULL);
	}
	if (option == 1)
	{
		do
		{
			if (atoi(agency->agency_code) == num)
			{
				return agency;
			}
			agency = agency->next;

		} while (agency != NULL);
	}else
	{
		do
		{
			if(agency->agency_address!=NULL)
			{
				if (strcmp(agency->agency_address, address) == 0)
				{
					return agency;
				}
			}
			agency = agency->next;

		} while (agency != NULL);
	}


	return NULL;
}
int bank_state_add_agency(state_t* state, agency_t* agency)
{
	if(state==NULL  || agency==NULL || agency->next!=NULL || agency->state!=NULL || agency->status!=BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_state_add_agency\n");
		return EXIT_FAILURE;
	}

	if(state->agencies!=NULL)
	{
		agency->next=state->agencies;
	}

	state->agencies=agency;
	agency->state=state;
	return EXIT_SUCCESS;
}

/*--------------------------------------------------------*/

bank_t* bank()
{
	bank_t* bank=(bank_t*)calloc(1, sizeof(bank_t));

	bank->status=BANK_OBJECT_NULL;
	return bank;
}

void bank_set_status(bank_t* bank, status_type flag)
{

	bank->status=flag;


}

state_t* bank_get_state(bank_t* bank)
{
	if(bank==NULL)
	{
		fprintf(stderr, "error bank_get_state\n");

		return NULL;
	}
	return bank->state;

}
/* option=0 for zip, 1 for code */
state_t* bank_get_state_n(bank_t* bank, int option, size_t num)
{
	if(bank==NULL)
	{
		fprintf(stderr, "error bank_get_state_n(1)\n");
		return NULL;
	}

	state_t* state=bank->state;

	if(state==NULL )
	{
		fprintf(stderr, "error bank_get_state_n(2)\n");

		return NULL;
	}
	if(option==0)
	{
		do
		{
			if (state->zip_code == num)
			{
				return state;
			}
			state = state->next;

		} while (state != NULL);
	}
	else
	{
		do
		{
			if (atoi(state->state_code)== num)
			{
				return state;
			}
			state = state->next;

		} while (state != NULL);
	}



	return state;

}

void bank_add_state(bank_t* data, state_t* state)
{
	if(state==NULL)
	{
		fprintf(stderr, "error bank_add_state\n");

	}
	if(data->state!=NULL)
	{
		state->next = data->state;
	}

	data->state=state;
	data->status=BANK_OBJECT_INIT;

}


/*----------------------ADMIN------------------*/

admin_t* bank_admin()
{
	admin_t* admin= (admin_t*)calloc(1, sizeof(admin_t));

	admin->status=BANK_OBJECT_EMPTY;

	return admin;
}

// char* bank_admin_set_uuid(admin_t* admin)
// {
// 	if (admin->status == BANK_OBJECT_NULL)
// 	{
// 		uuid_gen(admin->uuid_admin);
// 		admin->status = BANK_OBJECT_EMPTY;

// 		return admin->uuid_admin;
// 	}
// 	else
// 	{
// 		fprintf(stderr, "error bank_admin_set_uuid\n");
// 		return NULL;
// 	}
// }


login_t* bank_admin_set_new_login(admin_t* admin, char* pass )
{
	if (admin == NULL || admin->login!=NULL || admin->status != BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_admin_set_new_login\n");
		return NULL;
	}

	login_t* login=bank_login_generate(admin->agency);

	bank_login_set_key(login, pass);

	encrypt_login_pass(login);

	admin->login=login;

	admin->status=BANK_OBJECT_INIT;

	memset(&(pass[0]), 0, strlen(pass));

	return login;
}

int bank_admin_set_login(admin_t* admin, login_t* login)
{
	if (admin == NULL || admin->login!=NULL || login==NULL ||login->status!=BANK_LOGIN_ENCRYPTED)
	{
		fprintf(stderr, "error bank_admin_set_login\n");
		return EXIT_FAILURE;
	}
	login_t *login_new = bank_login();

	login_new->status=BANK_LOGIN_ENCRYPTED;

	strcpy(login_new->login_id, login->login_id);
	strcpy(login_new->login_key, login->login_key);

	memset(&(login->login_key[0]), 0, strlen(login->login_key));
	memset(&(login->login_id[0]), 0, strlen(login->login_id));

	admin->login=login_new;

	admin->status=BANK_OBJECT_INIT;

	return EXIT_SUCCESS;
}

int bank_admin_authenticate_login(admin_t* admin, login_t* login)
{
	if (admin == NULL || login==NULL || admin->login==NULL || admin->status != BANK_OBJECT_INIT || login->status==BANK_LOGIN_ENCRYPTED)
	{
		fprintf(stderr, "error bank_admin_authenticate_login\n");
		return EXIT_FAILURE;
	}


	if(validate_login(admin->login, login))
	{
		return EXIT_FAILURE;
	}

	memset(&(login->login_key[0]), 0, strlen(login->login_key));
	memset(&(login->login_id[0]), 0, strlen(login->login_id));

	return EXIT_SUCCESS;
}

int bank_admin_set_agency(admin_t* admin, agency_t* agency)
{
	if(admin==NULL || agency==NULL || admin->status!=BANK_OBJECT_EMPTY)
	{
		fprintf(stderr, "error bank_admin_set_agency\n");
		return EXIT_FAILURE;
	}

	admin->agency=agency;

	return EXIT_SUCCESS;
}

int bank_admin_set_bank(admin_t* admin, bank_t* bank)
{
	if(admin==NULL || bank==NULL)
	{
		fprintf(stderr, "error bank_admin_set_bank\n");
		return EXIT_FAILURE;
	}

	admin->bank=bank;

	return EXIT_SUCCESS;
}


int bank_admin_add(admin_t* admin_list, admin_t* admin)
{
	if (admin == NULL || admin_list == NULL || admin->next != NULL || admin->status != BANK_OBJECT_INIT || admin_list->status != BANK_OBJECT_INIT)
	{
		fprintf(stderr, "error bank_admin_add\n");

		return EXIT_FAILURE;
	}

	admin_t *list = admin_list;

	if (list->next == NULL)
	{
		admin_list->next = admin;
		return EXIT_SUCCESS;
	}

	do
	{
		if (strcmp(list->login->login_id, admin->login->login_id) == 0 )
		{
			return EXIT_FAILURE;
		}
		list = list->next;
	} while (list != NULL);

	/*FIFO*/
	admin->next= admin_list->next;

	admin_list->next= admin;

	return EXIT_SUCCESS;
}



// Departement init_departement_arg(departement_size_t allocation_size,char* uuid_departement,int code_postale,char* nom_departement,char* hash_code)
// {
// 	epartement departement = (departement)calloc(1, sizeof(struct departement));

// 	departement->uuid_departement = (char *)calloc(allocation_size.uuid_departement, sizeof(char));

// 	departement->code_postale = (char *)calloc(CODE_POSTALE_SIZE, sizeof(char));

// 	departement->nom_departement = (char *)calloc(allocation_size.nom_departement, sizeof(char));

// 	departement->hash_code = (char *)calloc(allocation_size.hash_code, sizeof(char));

// 	strcpy(departement->uuid_departement, uuid_departement);
// 	strcpy(departement->nom_departement, nom_departement);
// 	strcpy(departement->hash_code, hash_code);

// 	sprintf(departement->code_postale, "%05d", code_postale);

// 	return departement;
// }

// lData init_data()
// {
// 	lData data = (lData)calloc(1, sizeof(struct data));

// 	return data;
// }

// Admin init_admin()
// {
// 	Admin admin = (Admin)calloc(1, sizeof(struct admin));

// 	admin->uuid_admin = (char *)calloc(UUID_SIZE, sizeof(char));

// 	admin->next_admin=NULL;

// 	return admin;
// }

// int isEqualdepartement(departement departement1, departement departement2)
// {
// 	if (strcmp(departement1->uuid_departement, departement2->uuid_departement) == 0 && strcmp(departement1->code_postale, departement2->code_postale) == 0 && strcmp(departement1->nom_departement, departement2->nom_departement) == 0 && strcmp(departement1->hash_code, departement2->hash_code) == 0)
// 		return EXIT_SUCCESS;
// 	return EXIT_FAILURE;
// }

// int isEqualAdmin(Admin admin1, Admin admin2)
// {
// 	if (strcmp(admin1->uuid_admin, admin2->uuid_admin))
// 		return EXIT_SUCCESS;
// 	return EXIT_FAILURE;
// }

// int addAgence(lAgence liste_agence, Agence agence)
// {
// 	lAgence var = liste_agence;

// 	while (var!=NULL)
// 	{
// 		if(var->agence!=NULL)
// 		{
// 			if (isEqualAgence((var->agence), agence)==EXIT_SUCCESS)
// 			{
// 				return EXIT_FAILURE;
// 			}

// 		}else
// 		{
// 			var->agence=agence;
// 			return EXIT_SUCCESS;
// 		}
// 		if(var->next_agence==NULL)
// 		{
// 			var->next_agence= init_liste_agence();
// 		}
// 		var=var->next_agence;

// 	}
// 	return EXIT_SUCCESS;
// }

// int adddepartement(lData liste_departement, departement departement)
// {
// 	lData var = liste_departement;

// 	while (var!=NULL)
// 	{
// 		if(var->departement!=NULL)
// 		{
// 			if (isEqualdepartement(var->departement, departement)==EXIT_SUCCESS)
// 			{
// 				return EXIT_FAILURE;
// 			}

// 		}else
// 		{
// 			var->departement=departement;
// 			return EXIT_SUCCESS;
// 		}
// 		if(var->next_departement==NULL)
// 		{
// 			var->next_departement= init_data();
// 		}
// 		var=var->next_departement;

// 	}
// 	return EXIT_SUCCESS;
// }

// int addAdmin(Admin lAdmin, Admin admin)
// {
// 	Admin var = lAdmin;

// 	while (var!=NULL)
// 	{

// 		if (isEqualAdmin(var, admin)==EXIT_SUCCESS)
// 		{
// 			return EXIT_FAILURE;
// 		}

// 		if(var->next_admin==NULL)
// 		{
// 			var->next_admin= admin;
// 		}
// 		var=var->next_admin;

// 	}
// 	return EXIT_SUCCESS;
// }

// lData create_basic_data()
// {

// 	lData Data= init_data(), data=Data;
// 	char** uuid= (char*) calloc (99*UUID_SIZE, sizeof(char));
// 	int rands[99];
// 	int i,j;

// 	for(i=0; i< 99; i++)
// 	{
// 		uuid_gen(uuid[i]);

// 		for(j=0; j<i; j++)
// 		{
// 			if(strcmp(uuid[i], uuid[j])==0)
// 			{
// 				uuid_gen(uuid[i]);
// 				j=0;
// 			}
// 		}
// 	}

// 	for (i = 0; i < 99; i++)
// 	{
// 		rands[i]=(rand() % 100);

// 		for (j = 0; j < i; j++)
// 		{
// 			if (rands[i] == rands[j])
// 			{
// 				rands[i] = (rand() % 100);
// 				j = 0;
// 			}
// 		}
// 	}

// 	for(i=0; i<99; i++)
// 	{
// 		data->departement=create_departement(departement[i], uuid[i], i+1, rands[i]);
// 		data->next_departement=init_data();
// 		data=data->next_departement;
// 	}

// 	free(uuid);

// 	dump_basic_data(Data);
// 	return Data;
// }
// Admin create_admin(Admin liste_admin, char* pass, char *code_agence, char *code_departement)
// {
// 	Admin admin=init_admin();

// 	if(!uuid_gen(admin->uuid_admin))
// 	{
// 		fail("Failed to create a new admin: uuid generator error");
// 		return NULL;
// 	}

// 	admin->login_admin=create_admin_login(pass, code_agence, code_departement);

// 	assert(addAdmin(liste_admin, admin)==EXIT_SUCCESS);

// 	return admin;
// }

// departement create_departement( char* nom_departement, char* uuid, int code_postale, int code_departement)
// {
// 	departement_size_t size;
// 	size.nom_departement=strlen(nom_departement);
// 	char code[2];
// 	code[0]= 48 + code_departement/10;
// 	code[1]= 48 + code_departement % 10;
// 	departement departement= init_departement_arg(size, uuid, code_postale, nom_departement, code );

// 	return departement;

// }

// Agence create_agence(char* uuid, char* indicatif, int code_agence)
// {
// 	Agence agence=init_agence();

// }
/*
Admin new_admin()
{
	Admin admin = init_admin();

	uuid_gen(admin->uuid_admin);

	return admin;
}

departement new_departement(char *nom_departement, char *code_postale)
{
	departement departement = init_departement();

	uuid_gen(departement->uuid_departement);
	strcpy(departement->code_postale, code_postale);
	strcpy(departement->nom_departement, nom_departement);

	return departement;
}

*/