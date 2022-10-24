#include <stdio.h>
#include "App.h"
ST_terminalData_t terminal;
ST_cardData_t card;
ST_transaction_t transData;
void main()
{
	appStart();
}

void appStart(void)
{
	//Card
	if ((getCardHolderName(&card) == OK) && (getCardExpiryDate(&card) == OK) &&
		(getCardPAN(&card) == OK))
	{
		transData.cardHolderData = card;
		//Terminal
		
		getTransactionDate(&terminal);
		
		terminal.maxTransAmount = (float)10000;
		
		if ((isValidCardPAN(&card) == TERMINAL_OK ) && (isCardExpired(card, terminal) == TERMINAL_OK)
			&& (getTransactionAmount(&terminal) == TERMINAL_OK) && (isBelowMaxAmount(&terminal) == TERMINAL_OK))
		{
			transData.terminalData = terminal;
			//server
			recieveTransactionData(&transData);
		}
		
	}
}
