#include "Card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	char name[25] = { NULL };
	printf("Enter the cardholder's name: ");
	gets(name);
	if (strlen(name) > 24 || strlen(name) < 20 || name == NULL)
	{
		printf("Name is incorrect \n");
		return WRONG_NAME;
	}
	else {
		strcpy(cardData->cardHolderName,name);
		printf("Name accepted \n");
		return OK;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	char Date[6] = { NULL };
	printf("Enter the card's expiration date \n The format of the expiration date is MM/YY \n");
	gets(Date);
	if (strlen(Date) != 5 || Date == NULL)
	{
		printf("Expiration Date is incorrect \n");
		return WRONG_EXP_DATE;
	}
	else {
		if (strchr(Date,   '/') != NULL)
		{
			char DateHolder[6] = { NULL };
			strcpy(DateHolder, Date);
			char* MM = strtok(DateHolder, "/");
			char* YY = strtok(NULL, "\0");
			if (atoi(MM) <= 12 && atoi(MM) > 0 && strlen(YY) == 2)
			{
				strcpy(cardData->cardExpirationDate, Date);
				return OK;
			}
			else
			{
				printf("Expiration Date is incorrect \n");
				return WRONG_EXP_DATE;
			}
		}
		else
		{
			printf("Expiration Date is incorrect \n");
			return WRONG_EXP_DATE;
		}
		
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	char PAN[20] = { NULL };
	printf("Enter the card's PAN \n");
	gets(PAN);
	if (strlen(PAN) >19 ||strlen(PAN)<16 || PAN == NULL)
	{
		printf("PAN is incorecct \n");
		return WRONG_PAN;
	}
	else {
		strcpy(cardData->primaryAccountNumber, PAN);
		return OK;
	}
}
