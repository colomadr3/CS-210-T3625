#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <ios>
#include <limits>

using namespace std;

void header1() {
	//Header title and formatting for Input menu
	cout << setfill('*') << setw(34) << "" << endl;
	cout << setw(11) << "" << " Data Input " << setw(11) << "" << endl;
	cout << setfill(' ');
}

void header2() {
	//Header title and formatting for "Without Monthly Deposits" screen
	cout << "     Balance and Interest Without Additional Monthly Deposits     " << endl;
	cout << setfill('=') << setw(66) << "" << endl << setfill(' ');
	cout << "  Year" << setw(25) << right << "Year End Balance" << setw(30) << right << "Year End Earned Interest" << endl;
	cout << setfill('-') << setw(66) << "" << endl << setfill(' ');
}

void header3() {
	//Header title and formatting for "With Montly Deposits" screen
	cout << "      Balance and Interest With Additional Monthly Deposits      " << endl;
	cout << setfill('=') << setw(66) << "" << endl << setfill(' ');
	cout << "  Year" << setw(25) << right << "Year End Balance" << setw(30) << right << "Year End Earned Interest" << endl;
	cout << setfill('-') << setw(66) << "" << endl << setfill(' ');
}

void dataOutput(double t_invest, int t_interest, int t_years) {
	//Function that calculates interest and outputs yearly results WITHOUT monthly deposits
	//Function Overloading
	
	//Variables initialize to the interest data at the end of the first month 
	double rate = ((t_interest / 100.00) / 12);
	double total = t_invest;
	double interest = total * rate;
	double closing = total + interest;
	double interestEarned = interest;
	int numMonths = t_years * 12;
	
	//Stringstream variables used to append '$' to amounts when displaying output
	stringstream formatClosing;
	stringstream formatInterestEarned;

	//Loop to calculate monthly interest and totals
	//'j' starts at 2 because the first month has already been calculated
	for (int j = 2; j <= numMonths; ++j) {
		total = closing;
		interest = total * rate;
		closing = total + interest;
		interestEarned = interestEarned + interest;

		//If statement that converts the data into strings to be outputted every 12th iteration (1 year = 12 months)
		if ((j % 12) == 0) {
			//Converts data into strings and adds a '$' in the front
			formatClosing << "$" << fixed << setprecision(2) << closing;
			formatInterestEarned << "$" << fixed << setprecision(2) << interestEarned;

			//Outputs the converted strings to the screen
			cout << setw(6) << right << (j / 12) << setw(25) << right << formatClosing.str() << setw(30) << formatInterestEarned.str() << endl << endl;
			
			//Clears variables for next set of iterations
			interestEarned = 0;
			formatClosing.str("");
			formatInterestEarned.str("");
		}
	}

}

void dataOutput(double t_invest, double t_deposit, int t_interest, int t_years) {
	//Function that calculates interest and outputs yearly results WITH monthly deposits
	//Function Overloading

	//Variables initialize to the interest data at the end of the first month 
	double rate = ((t_interest / 100.00) / 12);
	double total = t_invest + t_deposit;
	double interest = total * rate;
	double closing = total + interest;
	double interestEarned = interest;
	int numMonths = t_years * 12;

	//Stringstream variables used to append '$' to amounts when displaying output
	stringstream formatClosing;
	stringstream formatInterestEarned;

	//Loop to calculate monthly interest and totals
	//'j' starts at 2 because the first month has already been calculated
	for (int j = 2; j <= numMonths; ++j) {
		total = closing + t_deposit; //Montly Deposit added to total
		interest = total * rate;
		closing = total + interest;
		interestEarned = interestEarned + interest;
		
		//If statement that converts the data into strings to be outputted every 12th iteration (1 year = 12 months)
		if ((j % 12) == 0) {
			//Converts data into strings and adds a '$' in the front
			formatClosing << "$" << fixed << setprecision(2) << closing;
			formatInterestEarned << "$" << fixed << setprecision(2) << interestEarned;

			//Outputs the converted strings to the screen
			cout << setw(6) << right << (j / 12) << setw(25) << right << formatClosing.str() << setw(30) << formatInterestEarned.str() << endl << endl;
			
			//Clears variables for next set of iterations
			interestEarned = 0;
			formatClosing.str("");
			formatInterestEarned.str("");
		}
	}

}

void clearScrn() {
	//Function that clears the screen
	cout << "\033[2J\033[1;1H";
}

int main() {
	string continueLoop = "Yes";
	int i;

	//Vector variables to hold input indicators/data
	vector<string> inputNames(4);
	inputNames.at(0) = "Initial Investment Amount.";
	inputNames.at(1) = "Monthly Deposit.";
	inputNames.at(2) = "Annual Interest.";
	inputNames.at(3) = "Number of Years.";
	vector<double> inputData(4);

	header1();

	//Initial Menu display
	cout << "Initial Investment Amount:" << endl << "Monthly Deposit:" << endl << "Annual Interest:" << endl << "Number of Years:" << endl;
	//Prompts user to continue - keystroke advances program
	system("pause");

	//Loop allows user to try more calculations
	while (continueLoop == "Yes" || continueLoop == "yes") {
		clearScrn();

		//Loop to clear vector element for next iteration
		for (i = 0; i < 4; ++i) {
			inputData.at(i) = 0.00;
		}

		//Loop to take in user input and stores them in 'inputData' vector
		for (i = 0; i < 4; ++i) {
			header1();

			//cout uses 'inputNames' vector to indicate to the user which input is expected 
			cout << "Initial Investment Amount:  $" << fixed << setprecision(2) << inputData.at(0) << endl << "Monthly Deposit:  $" << inputData.at(1) << endl
				<< "Annual Interest:  %" << static_cast<int>(inputData.at(2)) << endl << "Number of Years:  " << static_cast<int>(inputData.at(3)) << endl
				<< "Please enter " << inputNames.at(i) << endl;

			//Exception-handling construct to check user input 
			try {
				cin >> inputData.at(i);
				if (cin.fail()) { //'inputData' vector accepts double - Entering character/string will cause a failbit 
					throw runtime_error("Input is invalid. You did not enter a number");
				}
				clearScrn();
			}

			//Handler will output error message, clear cin, and ignore input upto the newline character 
			catch (runtime_error& excpt) {
				cout << excpt.what() << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				goto ending;//Jump statement to restart input loop
			}
		}

		//Menu screen outputing user's inputs
		//Prompts user to continue
		header1();
		cout << "Initial Investment Amount:  $" << inputData.at(0) << endl << "Monthly Deposit:  $" << inputData.at(1) << endl
			<< "Annual Interest:  %" << static_cast<int>(inputData.at(2)) << endl << "Number of Years:  " << static_cast<int>(inputData.at(3)) << endl;
		system("pause");
		clearScrn();

		//Function calls to calculate interest amounts and outputs data
		//'dataOutput' Functions are overloaded
		header2();
		dataOutput(inputData.at(0), static_cast<int>(inputData.at(2)), static_cast<int>(inputData.at(3)));
		header3();
		dataOutput(inputData.at(0), inputData.at(1), static_cast<int>(inputData.at(2)), static_cast<int>(inputData.at(3)));

		ending:
		continueLoop = "";
		//Loop asks user if they would like to try more calculations
		//Checks user input for validity
		cout << "Would you like to calculate different amounts? Yes or No" << endl;

		//Exception-handling construct to check user input
		try {
			cin >> continueLoop;
			if (continueLoop != "yes" && continueLoop != "Yes" && continueLoop != "No" && continueLoop != "no") {//True if continueLoop is not 'Yes' or 'No' - capitalization is factored in
				throw runtime_error("Input is invalid.");
			}
		}

		//Handler will output error message, clear cin, and ignore input upto the newline character
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			goto ending;//Jump statement to restart input loop
		}

	}
	return 0;
}