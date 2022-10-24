#include "Terminal.h"



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	time_t t;
	time(&t);
	struct tm MachineTime = *localtime(&t);
	sprintf(termData->transactionDate, "%d/%02d/%d", MachineTime.tm_mday, MachineTime.tm_mon + 1, MachineTime.tm_year + 1900);

	return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	//extracting dates from card
	char* MM = strtok(cardData.cardExpirationDate, "/");
	char* YY = strtok(NULL, "\0");
	//machine date
	time_t t;
	t = time(NULL);
	struct tm MachineTime = *localtime(&t);
	// date compare
	if (atoi(YY) < MachineTime.tm_year - 100)
	{
		printf("Expired card");
		return EXPIRED_CARD;
	}
	else if ((atoi(YY) == MachineTime.tm_year - 100 )&&(atoi(MM) < MachineTime.tm_mon + 1) )
	{
		printf("Expired card");
		return EXPIRED_CARD;
	}
	else if ((atoi(YY) == MachineTime.tm_year - 100) && (atoi(MM) >= MachineTime.tm_mon + 1))
	{
		return TERMINAL_OK;
	}
	else if (atoi(YY) > MachineTime.tm_year - 100) 
	{
		return TERMINAL_OK;	
	}
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	char CheckSum = 0;
	uint8_t *PAN = _strrev(cardData->primaryAccountNumber);
	uint16_t num = 0;
	for (char i = 0; i < strlen(cardData->primaryAccountNumber); i++)
	{
		num = PAN[i] - '0';
		if ((i % 2) && i!=0)
		{
			if (num*2 >= 10)
			{
				CheckSum += (1 + ((num * 2) - 10));
			}
			else
			{
				CheckSum += num*2;
			}
		}
		else
		{
			CheckSum += num;
		}
	}
	if (!(CheckSum % 10))
	{
		return TERMINAL_OK;
	}
	else
	{
		printf("invalid card PAN \n");
		return INVALID_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	float TAmount = 0;
	printf("Enter the transaction Amount:\n");
	scanf("%f", &TAmount);
	if (TAmount <= 0) 
	{
		printf("invalid amount \n");
		return INVALID_AMOUNT;
	}
	else
	{
		termData->transAmount = TAmount;
		printf("the amount you entered is %f \n", termData->transAmount);
		return TERMINAL_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		printf("this exceeds the maximum allowed value \n");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	float MaxTAmount = 0;
	printf("Enter the maximum transaction amount:\n");
	scanf("%f", &MaxTAmount);
	if (MaxTAmount <= 0)
	{
		printf("invalid value");
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		termData->maxTransAmount = MaxTAmount;
		printf("max transaction amount set at %f \n ", termData->maxTransAmount);
		return TERMINAL_OK;
	}
}
