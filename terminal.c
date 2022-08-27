#include<stdio.h>
#include<string.h>

#include"card.h"
#include"terminal.h"

/*
* Function Name : getTransactionDate
* Input : two pointer to struct that hold the terminal data
* Return : Error state after check the input data
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	int flag,i = 0;
	printf("Enter The Today Date :  DD/MM/YYYY \n");
	gets(termData->transactionDate);
	i = strlen(termData->transactionDate);
	if (i == 10)                                   // Check Expiry date Correct size
	{
		if ((termData->transactionDate[0] >= '0' && termData->transactionDate[0] <= '9')
			&& (termData->transactionDate[1] >= '0' && termData->transactionDate[1] <= '9')
			&& (termData->transactionDate[3] >= '0' && termData->transactionDate[3] <= '9')
			&& (termData->transactionDate[4] >= '0' && termData->transactionDate[4] <= '9')
			&& (termData->transactionDate[6] >= '0' && termData->transactionDate[6] <= '9')
			&& (termData->transactionDate[7] >= '0' && termData->transactionDate[7] <= '9')
			&& (termData->transactionDate[8] >= '0' && termData->transactionDate[8] <= '9')
			&& (termData->transactionDate[9] >= '0' && termData->transactionDate[9] <= '9')
			&& (termData->transactionDate[2] >= '/')
			&& (termData->transactionDate[5] >= '/'))            // Check correct input by check range from Ascii
		{
			flag = TERMINAL_OK;
		}
		else
		{
			flag = WRONG_DATE;
		}
	}
	else
	{
		flag = WRONG_DATE;
	}
	return flag;
}

/*
* Function Name : isCardExpired
* Input : two pointer to struct that hold the card data and terminal data
* Return : Error state after check the input data
*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	int flag;
	if (cardData->cardExpirationDate[3] > termData->transactionDate[8])
	{
		flag = TERMINAL_OK;
	}
	else if (cardData->cardExpirationDate[3] < termData->transactionDate[8])
	{
		flag = EXPIRED_CARD;
	}
	else
	{
		if (cardData->cardExpirationDate[4] > termData->transactionDate[9])
		{
			flag = TERMINAL_OK;
		}
		else if (cardData->cardExpirationDate[4] < termData->transactionDate[9])
		{
			flag = EXPIRED_CARD;
		}
		else
		{
			if (cardData->cardExpirationDate[0] > termData->transactionDate[3])
			{
				flag = TERMINAL_OK;
			}
			else if (cardData->cardExpirationDate[0] < termData->transactionDate[3])
			{
				flag = EXPIRED_CARD;
			}
			else
			{
				if (cardData->cardExpirationDate[1] > termData->transactionDate[4])
				{
					flag = TERMINAL_OK;
				}
				else if (cardData->cardExpirationDate[1] < termData->transactionDate[4])
				{
					flag = EXPIRED_CARD;
				}
				else
				{
					flag = TERMINAL_OK;
				}

			}
		}

	}
	return flag;
}

/*
* Function Name : getTransactionAmount
* Input : two pointer to struct that hold the terminal data
* Return : Error state after check the input data
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	int flag;
	printf("Enter The Transiction Amount : \n");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
	{
		flag = INVALID_AMOUNT;
	}
	else
	{
		flag = TERMINAL_OK;
	}
	return flag;
}

/*
* Function Name : isBelowMaxAmount
* Input : two pointer to struct that hold the terminal data
* Return : Error state after check the input data
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	int flag;
	if (termData->maxTransAmount >= termData->transAmount)
	{
		flag = TERMINAL_OK;
	}
	else
	{
		flag = EXCEED_MAX_AMOUNT;
	}
	return flag;
}

/*
* Function Name : isBelowMaxAmount
* Input : pointer to struct that hold the terminal data && Maximum terminal transiction amount
* Return : Error state after check the input data
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData,float maxAmount)
{
	int flag;
	if (maxAmount <= 0)
	{
		flag = INVALID_MAX_AMOUNT;
	}
	else
	{
		termData->maxTransAmount = maxAmount;
		flag = TERMINAL_OK;
	}
	return flag;
}