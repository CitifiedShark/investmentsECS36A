#include <stdio.h>
#include <math.h>

/*
This program helps us evaluate whether it would be more worth it for the user to 
1. Pay the minimum monthly payment and invest at the same time
2. Or pay off the loan first, and then invest

1. Ask the user for input on information such as their current loan amount, expected annual return of investment, current age, etc.
2. Turn the input into more usable forms (total months from now to retirement)
3. Calculate the amount of money that would be in the retirement accounts from the two methods
4. Display the values to the user to let them decide what option is best
*/
double payMinAndInvest(double loanVal, double monthlyLoanInterest, double minMonthlyLoanPayment, double retirementPayment, int numMonths, double monthlyROR) {
    double retirementAccount = 0;
    double monthlyInvestment = retirementPayment - minMonthlyLoanPayment;
/*
This function calculates the retirement account if we pay the minimum payment and invest at the same time
@retirementAccount: is the amount invested in the retirement account
@loanVal: is the loan amount owed
@monthlyLoanInterest: is the amount of monthly interest on the loan
@minMonthlyLoanPayment: is the minimum monthly payment needed for the loan
@retirementPayment: is the amount we will invest into the retirement account
@numMonths: are the number of months we will be investing into the retirement account
@monthlyROR: is the expected monthly return of investment in the retirement account
@returns the amount in the retirementAccount by retirement
*/
    for (int i=0; i < numMonths; i++) {
        retirementAccount = retirementAccount * (1 + monthlyROR);
        if (loanVal <= 0) {
            /* If loan is paid off, invest the full amount */
            retirementAccount += retirementPayment;
        } else {
            /* Add interest to loan */
            loanVal = loanVal * (1 + monthlyLoanInterest);
          
            if (minMonthlyLoanPayment > loanVal) {
                /* If payment exceeds remaining loan, invest the excess */
                double excess = minMonthlyLoanPayment - loanVal;
                retirementAccount += monthlyInvestment + excess;
                loanVal = 0;
            }    
            else {
                /* Make minimum payment and investment */
                loanVal -= minMonthlyLoanPayment;
                retirementAccount += monthlyInvestment;
            }
        }
    } 

    if (loanVal > 0) {
        retirementAccount -= loanVal;
    }
    
    return retirementAccount;
}

double payLoanThenInvest(double loanVal, double monthlyLoanInterest, double retirementPayment, int numMonths, double monthlyROR) {
    double retirementAccount = 0;
/*
This function calculates the retirement account if we pay off the loan and then fully invest
@retirementAccount: is the amount invested in the retirement account
@loanVal: is the loan amount owed
@monthlyLoanInterest: is the amount of monthly interest on the loan
@minMonthlyLoanPayment: is the minimum monthly payment needed for the loan
@retirementPayment: is the amount we will at first use to help pay off the loan, then use for investment in the retirement account
@numMonths: are the number of months we will be investing into the retirement account
@monthlyROR: is the expected monthly return of investment in the retirement account
@returns the amount in the retirementAccount by retirement
*/
    for (int i = 0; i < numMonths; i++) {
        if (loanVal <= 0) {
            retirementAccount = retirementAccount * (1 + monthlyROR);
            retirementAccount += retirementPayment;
        } else {
            /* Add interest to loan */
            loanVal = loanVal * (1 + monthlyLoanInterest);
           
            if (retirementPayment > loanVal) {
                /* If payment exceeds remaining loan, invest the excess */
                double excess = retirementPayment - loanVal;
                retirementAccount = retirementAccount * (1 + monthlyROR);
                retirementAccount += excess;
                loanVal = 0;
            }
           else {
                /* Make full payment towards loan */
                loanVal -= retirementPayment;
            }
        }
    }
    if (loanVal > 0) {
        retirementAccount -= loanVal;
    }

    return retirementAccount;
}

double displayCalculationsPayMin(double payMinAndInvestRetirement, double payLoanThenInvestRetirement) {
/*
This function displays the amount that would be in the retirement accounts if the user would make more by making the minimum payments
@payMinAndInvestRetirement: is the retirement account value if we payed the minimum payment and invested at the same time
@payLoanThenInvestRetirement: is the retirement account value if we fully paid off the loan then started investing
@returns 0 for completion
*/
    printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");

    printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you paid off your loan before investing.\n", payMinAndInvestRetirement, payLoanThenInvestRetirement);

    return 0;
}

double displayCalculationsPayRetire(double payMinAndInvestRetirement, double payLoanThenInvestRetirement, double retirementPayment) {
/*
This function displays the amount that would be in the retirement accounts if the user would make more by paying off the loan then investing
@payMinAndInvestRetirement: is the retirement account value if we payed the minimum payment and invested at the same time
@payLoanThenInvestRetirement: is the retirement account value if we fully paid off the loan then started investing
@retirementPayment: is the payment that will be used to help pay off the loan, then for investing
@returns 0 for completion
*/
    printf("You should apply all $%.2lf towards your loan before making any investments.\n", retirementPayment);

    printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you only made minimum payments.\n", payLoanThenInvestRetirement, payMinAndInvestRetirement);

    return 0;
}

int main() {
    char percentSymbol;

    double loanVal;
    double annualLoanInterest;
    double minMonthlyLoanPayment, retirementPayment;
    int currAge, retireAge;
    double annualROR;

    double monthlyLoanInterest, monthlyROR;
    double numYears, numMonths;

    double payMinAndInvestRetirement, payLoanThenInvestRetirement;
/*
This function organizes the programs
1. asks for the user's inputs
2. Makes the inputs more usable
3. Calculates total retirement accounts
4. Then displays the two different retirement values
*/
    /* Ask for the user's inputs */
    do {
        printf("Enter how much you owe in loans: ");
        scanf(" %lf", &loanVal);
    } while(loanVal < 0);
    do {
        printf("Enter the annual interest rate of the loans: ");
        scanf(" %lf", &annualLoanInterest);
        scanf("%c", &percentSymbol);
        if (percentSymbol == '%') {
            annualLoanInterest = annualLoanInterest / 100;
        } else if ((percentSymbol == '\n') && (annualLoanInterest >= 0)) {
            break;
        }
    } while((annualLoanInterest < 0) && (percentSymbol != '%'));
    do {
        printf("Enter your minimum monthly loan payment: ");
        scanf(" %lf", &minMonthlyLoanPayment);
    } while(minMonthlyLoanPayment < 0);
    do {
        printf("Enter how much money you will be putting towards loans/retirement each month: ");
        scanf(" %lf", &retirementPayment);
    } while(retirementPayment < minMonthlyLoanPayment);
    do {
        printf("Enter your current age: ");
        scanf(" %d", &currAge);
    } while(currAge < 0);
    do {
        printf("Enter the age you plan to retire at: ");
        scanf(" %d", &retireAge);
    } while(retireAge < currAge);
    do {
        percentSymbol = 0;
        printf("Enter your predicted annual rate of return: ");
        scanf(" %lf", &annualROR);
        scanf("%c", &percentSymbol);
        if (percentSymbol == '%') {
            annualROR = annualROR / 100;
        } else if ((annualROR >= 0) && (percentSymbol == '\n')){
            break;
        }
    } while((annualROR < 0) && (percentSymbol != '%'));
    
    /* Make inputs more usable */
    monthlyLoanInterest = annualLoanInterest / 12.0;
    monthlyROR = annualROR / 12.0;

    numYears = retireAge - currAge;
    numMonths = numYears * 12;    

    /* Calculate total retirement accounts */
    payMinAndInvestRetirement = payMinAndInvest(loanVal, monthlyLoanInterest, minMonthlyLoanPayment, retirementPayment, numMonths, monthlyROR);
    payLoanThenInvestRetirement = payLoanThenInvest(loanVal, monthlyLoanInterest, retirementPayment, numMonths, monthlyROR);
    
    /* Display the calculations*/
    if (payMinAndInvestRetirement >= payLoanThenInvestRetirement) {
        displayCalculationsPayMin(payMinAndInvestRetirement, payLoanThenInvestRetirement);
    } else {
        displayCalculationsPayRetire(payMinAndInvestRetirement, payLoanThenInvestRetirement, retirementPayment);
    }
    

    return 0;
}