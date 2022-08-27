#include<stdio.h>
#include<string.h>

#include"card.h"
#include"terminal.h"
#include"server.h"
#include"app.h"

/*
* Function Name : appStart
* Input : void
* Return : void
*/
void appStart(void)
{
	int flag;
	float maxAmount= MAX_AMOUNT_PER_DAY;
	ST_cardData_t cardData;
	ST_terminalData_t terminalData;
	ST_transaction_t transData;

	/*set maximum amount for a day*/
	flag = setMaxAmount(&terminalData, maxAmount);
	if (flag == TERMINAL_OK)
	{
		/*card stage*/

		flag = getCardHolderName(&cardData);
		while (flag == WRONG_NAME)
		{
			printf("Wrong Name Format, Please Try Again :\n");
			flag = getCardHolderName(&cardData);
		}
		flag = getCardExpiryDate(&cardData);
		while (flag == WRONG_EXP_DATE)
		{
			printf("Wrong Expiry Date Format, Please Try Again :\n");
			flag = getCardExpiryDate(&cardData);
		}
		flag = getCardPAN(&cardData);
		while (flag == WRONG_PAN)
		{
			printf("Wrong PAN Format, Please Try Again :\n");
			flag = getCardPAN(&cardData);
		}

		/*terminal stage*/


		flag = getTransactionDate(&terminalData);
		while (flag == WRONG_DATE)
		{
			printf("Wrong Date Format, Please Try Again :\n");
			flag = getTransactionDate(&terminalData);
		}
		flag = isCardExpired(&cardData, &terminalData);
		if (flag == TERMINAL_OK)
		{
			flag = getTransactionAmount(&terminalData);
			while (flag == INVALID_AMOUNT)
			{
				printf("Invalid Amount, Please Try Again :\n");
				flag = getTransactionAmount(&terminalData);
			}
			flag = isBelowMaxAmount(&terminalData);
			while (flag == EXCEED_MAX_AMOUNT)
			{
				printf("Exceed Max Amount for a day, Please Try Again :\n");
				/*enter a new valid transaction amount*/
				flag = getTransactionAmount(&terminalData);
				while (flag == INVALID_AMOUNT)
				{
					printf("Invalid Amount, Please Try Again :\n");
					flag = getTransactionAmount(&terminalData);
				}
				/*check is below max amount for day*/
				flag = isBelowMaxAmount(&terminalData);
			}

			/* server stage */
			transData.cardHolderData = cardData;
			transData.terminalData = terminalData;

			flag = recieveTransactionData(&transData);
			if (flag == DECLINED_INSUFFECIENT_FUND)
			{
				printf("Transaction Filled , Insuffecient Fund !!");
			}
			else if (flag == DECLINED_STOLEN_CARD)
			{
				printf("Transaction Filled , Stolen Card !!");
			}
			else if (flag == FRAUD_CARD)
			{
				printf("Transaction Filled , Fraud Card !!");
			}
			else
			{
				flag = saveTransaction(&transData);
				if (flag == APPROVED)
				{
					printf("Transaction completed successfully");
				}
				else
				{
					printf("Transaction Saving Filled, Try again later");
				}
			}
		}
		else
		{
			printf("The Card Expired !!\n");
		}
	}
	else
	{
		printf("Invalid Max Amount\n");
	}
}

int main(void)
{
	appStart();
}