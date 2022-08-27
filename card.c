#include<stdio.h>
#include<string.h>

#include"card.h"

/*
* Function Name : getCardHolderName
* Input : pointer to struct that hold the card data
* Return : Error state after check the input data
*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	int flag,j,i=0;
	printf("Enter The Card Holder Name : \n");
	gets(cardData->cardHolderName);
	i = strlen(cardData->cardHolderName);
	if (i <= 24 && i >= 20)   // Check Name Correct size
	{
		for (j = 0; cardData->cardHolderName[j] != NULL; j++)
		{
			if ( cardData->cardHolderName[j] >= 'A' && cardData->cardHolderName[j] <= 'Z')  // Check correct input by check range from Ascii  
			{
				flag = CARD_OK;
			}
			else
			{
				flag = WRONG_NAME;
			}
		}
	}
	else
	{
		 flag = WRONG_NAME;
	}
	return flag;
}

/*
* Function Name : getCardExpiryDate
* Input : pointer to struct that hold the card data
* Return : Error state after check the input data
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	int flag,i=0;
	printf("Enter The Card Expiry Date : MM/YY \n");
	gets(cardData->cardExpirationDate);
	i = strlen(cardData->cardExpirationDate);
	if (i == 5)                                   // Check Expiry date Correct size
	{
		if ((cardData->cardExpirationDate[0] >= '0' && cardData->cardExpirationDate[0] <= '9') 
			&& (cardData->cardExpirationDate[1] >= '0' && cardData->cardExpirationDate[1] <= '9')
			&& (cardData->cardExpirationDate[3] >= '0' && cardData->cardExpirationDate[3] <= '9')
			&& (cardData->cardExpirationDate[4] >= '0' && cardData->cardExpirationDate[4] <= '9')
			&& (cardData->cardExpirationDate[2] >= '/'))            // Check correct input by check range from Ascii
		{
			flag = CARD_OK;
		}
		else
		{
			flag = WRONG_EXP_DATE;
		}
	}
	else
	{
		flag = WRONG_EXP_DATE;
	}
	return flag;
}

/*
* Function Name : getCardPAN
* Input : pointer to struct that hold the card data
* Return : Error state after check the input data
*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	int flag, j, i = 0;
	printf("Enter The Primary Account Number : \n");
	gets(cardData->primaryAccountNumber);
	i = strlen(cardData->primaryAccountNumber);
	if (i >= 16 && i <= 19)                                  // Check PAN Correct size
	{
		for (j = 0; cardData->primaryAccountNumber[j] != NULL; j++)
		{
			if (cardData->primaryAccountNumber[j] >= '0' && cardData->primaryAccountNumber[j] <= '9') // Check correct input by check range from Ascii
			{
				flag = CARD_OK;
			}
			else
			{
				flag = WRONG_PAN;
			}
		}
	}
	else
	{
		flag = WRONG_PAN;
	}
	return flag;
}