#include "Server.h"

ST_accountsDB_t AccountsArray[255] = { {5000,"0815140962588407968",Running},{16214,"2381562731040136691",Blocked},{8324,"9192131290829163208",Running},
									   {6000,"4351351550540798503",Running},{3241,"7532732710553965991",Running}};

ST_transaction_t TransactionArray[255] = { 0 };

uint8_t AccountArrayPos = 0;
uint32_t TransactionSequenceNumber = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if ((isValidAccount(&transData->cardHolderData) == SERVER_OK) && isAmountAvailable(&transData->terminalData) == SERVER_OK 
		&& AccountsArray[AccountArrayPos].AccState == Running)
	{
		AccountsArray[AccountArrayPos].balance -= transData->terminalData.transAmount;
		printf("new account balance: %d \n", (int) AccountsArray[AccountArrayPos].balance);
		transData->transState = SERVER_OK;
		printf("Sucessful transaction \n");
		saveTransaction(transData);
		AccountArrayPos = 0;
		return APPROVED;
	}
	else if(isValidAccount(&transData->cardHolderData) != SERVER_OK)
	{
		printf("This account is invalid");
		saveTransaction(transData);
		AccountArrayPos = 0;
		return DECLINED_STOLEN_CARD;
	}
	else if (isAmountAvailable(&transData->terminalData) != SERVER_OK)
	{
		printf("Low Funds");
		saveTransaction(transData);
		AccountArrayPos = 0;
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (AccountsArray[AccountArrayPos].AccState == Blocked) 
	{
		printf("Blocked account");
		return DECLINED_STOLEN_CARD;
	}
	

}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	for (AccountArrayPos; AccountArrayPos < 5; AccountArrayPos++)
	{
		if (!strcmp(cardData->primaryAccountNumber, AccountsArray[AccountArrayPos].primaryAccountNumber))
		{
			return SERVER_OK;
		}
	}
	return DECLINED_STOLEN_CARD;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount > AccountsArray[AccountArrayPos].balance)
	{
		return LOW_BALANCE;
	}
	else
	{
		return SERVER_OK;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	
	TransactionArray[TransactionSequenceNumber].cardHolderData = transData->cardHolderData;
	TransactionArray[TransactionSequenceNumber].terminalData = transData->terminalData;
	TransactionArray[TransactionSequenceNumber].transState = transData->transState;
	transData->transactionSequenceNumber = TransactionSequenceNumber++;
	return SERVER_OK;
}

