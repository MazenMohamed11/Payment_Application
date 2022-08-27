#include<stdio.h>
#include<string.h>

#include"server.h"

/*server-side accounts' database global array*/
ST_accountsDB_t accountsDataBase[255] = { {10000.0,RUNNING,"1234567890123456"},
										  {15000.0,RUNNING,"8994765742135987"},
										  {20000.0,BLOCKED,"9864525029684893"},
										  {25000.0,BLOCKED,"1247593754902884"},
										  {30000.0,RUNNING,"5637658304757393"} };

/*server-side accounts' database global array*/
ST_transaction_t transactionDataBase[255] = { 0 };

int refrenceIndex;

/*
* Function Name : recieveTransactionData
* Input : pointer to struct that hold the terminal data
* Return : Error state after check the input data
*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	int flag;
	float trans_amount=transData->terminalData.transAmount;
	flag = isValidAccount(&transData->cardHolderData);
	if (flag == SERVER_OK)
	{
		flag = isBlockedAccount(&refrenceIndex);
		if (flag == SERVER_OK)
		{
			flag = isAmountAvailable(&transData->terminalData, &refrenceIndex);
			if (flag == SERVER_OK)
			{
				flag = APPROVED;
				accountsDataBase[refrenceIndex].balance -= trans_amount;
			}
			else
			{
				flag = DECLINED_INSUFFECIENT_FUND;
			}
		}
		else
		{
			flag = DECLINED_STOLEN_CARD;
		}
	}
	else
	{
		flag = FRAUD_CARD;
	}
	transData->transState = flag;
	return flag;
}

/*
* Function Name : isValidAccount
* Input : pointer to struct that hold the card data
* Return : Error state after check the input data
*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	int i,flag= ACCOUNT_NOT_FOUND;
	for (i = 0; i < 255; i++)
	{
		if (strcmp(accountsDataBase[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0)  //check PAN exist in database
		{
			flag = SERVER_OK;
			refrenceIndex = i;
		}
		else
		{}
	}
	return flag;
}

/*
* Function Name : isBlockedAccount
* Input : pointer to integer that hold the refrence index
* Return : Error state after check the input data
*/
EN_serverError_t isBlockedAccount(int *acountRefrence)
{
	int flag=BLOCKED_ACCOUNT;
	if (accountsDataBase[*acountRefrence].state == RUNNING)
	{
		flag = SERVER_OK;
	}
	else
	{ }
	return flag;
}

/*
* Function Name : isAmountAvailable
* Input : pointer to struct that hold the terminal data & pointer to integer that hold the refrence index  
* Return : Error state after check the input data
*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, int *acountRefrence)
{
	int flag=LOW_BALANCE;
	if (termData->transAmount <= accountsDataBase[*acountRefrence].balance)
	{
		flag = SERVER_OK;
	}
	else
	{ }
	return flag;
}

/*
* Function Name : saveTransaction
* Input : pointer to struct that hold the transaction data
* Return : Error state after check the input data
*/
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	int flag = transData->transState;
	if (flag == APPROVED)
	{
		transData->transactionSequenceNumber++;
	}
	else
	{}
	return flag;
}