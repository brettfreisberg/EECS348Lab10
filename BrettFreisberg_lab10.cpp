//For input/output
#include <iostream>
//For file stuff
#include <fstream>
//For string stuff
#include <string>
//Typing shortcut
using namespace std;

//Function to check if the string fits the +/-A.B format
bool checkDouble(const string& string2) {
    //Check if the string is empty
    if (string2.empty()) return false;

    //Set i to 0 to check +/-
    int i = 0;
    //Check +/- and go to next character
    if (string2[i] == '+' || string2[i] == '-') i++;

    //Booleans for comparisons
    bool hasPeriod = false;
    bool hasDigitsBefore = false;
    bool hasDigitsAfter = false;

    //Check all the characters
    for (; i < (int)string2.size(); i++) {
        //Set character2 to current string character
        char character2 = string2[i];
        //If the character is a digit
        if (isdigit(character2)) {
            //Check if a period has been seen, the digit is before
            if (!hasPeriod) hasDigitsBefore = true;
            //Else, digit is after
            else hasDigitsAfter = true;
        }
            //Check for period
            else if (character2 == '.') {
                //Check for two periods
                if (hasPeriod) return false;
                //Has a period so set to true
                hasPeriod = true;
            } else {
                //For if the character isn't valid
                return false;
            }
    }
    //If there is no period, there are just digits
    if (!hasPeriod) return hasDigitsBefore;
    //If there is a period, there is digits on both sides of the period
    return hasDigitsBefore && hasDigitsAfter;
}

//Funciton to take out sign for math
string takeSign(const string& string2) {
    //Check if string is empty
    if (string2.empty()) return string2;
    //Check if + or -
    if (string2[0] == '+' || string2[0] == '-') return string2.substr(1);
    //Return if not + or -
    return string2;
}
//Function to return the sign
int returnSign(const string& string2) {
    //If negative sign, is negative
    if (!string2.empty() && string2[0] == '-') return -1;
    //Else, return positive since it has ot be positive
    return +1;
}

//Function to remove leading zeroes
string removeZeroes(string string2) {
    //Remove leading 0
    while (string2.size() > 1 && string2[0] == '0') string2.erase(string2.begin());
    //Return without leading 0
    return string2;
}

//Split decimal and integer
void decimalSplit(const string& number, string& integerPart, string& decimalPart) {
    //Find period
    size_t period = number.find('.');
    //If there is no decimal
    if (period == string::npos) {
        //Set to number
        integerPart = number;
        //Set decimal part to nothing
        decimalPart = "";
    //Otherwise, there is a decimal
    } else {
        //Set integer part
        integerPart = number.substr(0, period);
        //Set decimal part
        decimalPart = number.substr(period + 1);
    }
}

//Function to add positive strings
string addPositive(string a, string b) {
    //Declare string of a and b ints and decimals
    string aInteger, aDecimal, bInteger, bDecimal;
    //Split numbers a and b into integer and decimal
    decimalSplit(a, aInteger, aDecimal);
    decimalSplit(b, bInteger, bDecimal);


    //Make fraction part equal sizes
    while(aDecimal.size() < bDecimal.size()) aDecimal += '0';
    while(bDecimal.size() < aDecimal.size()) bDecimal += '0';

    //Declare decimal result part
    string decimalResult = "";
    //Declare carryNumber integer
    int carryNumber = 0;

    //Add decimal part from right to left
    for (int i = (int)aDecimal.size() - 1; i >= 0; i--) {
        //Add number
        int sum = (aDecimal[i] - '0') + (bDecimal[i] - '0') + carryNumber;
        //Gets the carry number if there is one
        carryNumber = sum / 10;
        //Puts decimal part back together.
        decimalResult.insert(decimalResult.begin(), '0' + (sum % 10));
    }

    //Declare variables for math
    int intA = (int)aInteger.size() - 1;
    int intB = (int)bInteger.size() - 1;
    //Delcare integer result
    string integerResult = "";
    //Add integer part
    while (intA >= 0 || intB >= 0 || carryNumber) {
        //Declare variables for math
        int da = (intA >= 0) ? (aInteger[intA] - '0') : 0;
        int db = (intB >= 0) ? (bInteger[intB] - '0') : 0;
        //Add the integer with carry number
        int sum = da + db + carryNumber;
        //Find if there is a carry number
        carryNumber = sum/10;
        //Add carry number
        integerResult.insert(integerResult.begin(), '0' + (sum % 10));
        //Decrement to next part
        intA--; intB--;
    }

    //Remove trailing zeroes
    while (!decimalResult.empty() && decimalResult.back() == '0') decimalResult.pop_back();

    //Remove leading zeroes
    string result = removeZeroes(integerResult);
    //If there is a decimal
    if (!decimalResult.empty())
        //Add decimal to result
        result += "." + decimalResult;

    //Return result
    return result;
}

//For comparing positive strings
int comparePositiveStrings(string a, string b) {
    //Declare variables
    string aInteger, aDecimal, bInteger, bDecimal;
    //Split numbers
    decimalSplit(a, aInteger, aDecimal);
    decimalSplit(b, bInteger, bDecimal);

    //Remove leading zeroes
    aInteger = removeZeroes(aInteger);
    bInteger = removeZeroes(bInteger);

    //Get sign of result
    if (aInteger.size() > bInteger.size()) return 1;
    if (aInteger.size() < bInteger.size()) return -1;
    if (aInteger > bInteger) return 1;
    if (aInteger < bInteger) return -1;

    //Compare decimals
    while (aDecimal.size() < bDecimal.size()) aDecimal += '0';
    while (bDecimal.size() < aDecimal.size()) bDecimal += '0';

    //Get sign
    if (aDecimal > bDecimal) return 1;
    if (aDecimal < bDecimal) return -1;
    return 0;
}

//For if there is a negative number
string subtractStrings(string a, string b) {
    //Declare variables
    string aInteger, aDecimal, bInteger, bDecimal;
    //Split numbers
    decimalSplit(a, aInteger, aDecimal);
    decimalSplit(b, bInteger, bDecimal);

    //Make numbers euqal size
    while (aDecimal.size() < bDecimal.size()) aDecimal += '0';
    while (bDecimal.size() < aDecimal.size()) bDecimal += '0';

    //Declare decimalResult
    string decimalResult = "";
    //Declare borrow for subtraction
    int borrow = 0;

    //Subtract decimal side from right to left
    for (int i = (int)aDecimal.size() - 1; i >= 0; i--) {
        //Declare variables for math
        int da = aDecimal[i] - '0' - borrow;
        int db = bDecimal[i] - '0';
        //If number needs to borrow 10
        if (da < db) {
            da += 10;
            borrow = 1;
        //Else, the number doesn't need to borrow
        } else borrow = 0;
        //Subtract
        int difference = da - db;
        //Put decimal part back together
        decimalResult.insert(decimalResult.begin(), '0' + difference);
    }

    //Declare int varibles for math
    int intA = (int)aInteger.size() - 1;
    int intB = (int)bInteger.size() - 1;
    //Declare integerResult
    string integerResult = "";
    //Add integer part
    while (intA >= 0 || intB >= 0) {
        //Declare variables for math
        int da = (intA >= 0) ? aInteger[intA] - '0' : 0;
        int db = (intB >= 0) ? bInteger[intB] - '0' : 0;
        //Subtract borrow if the number before borrowed
        da -= borrow;
        //If the number needs to borrow
        if (da < db) {
            da += 10;
            borrow = 1;
        //If the number doesn't need to borrow
        } else borrow = 0;
        //Subtract and account for borrow
        int difference = da - db;
        integerResult.insert(integerResult.begin(), '0' + difference);
        //Decrement
        intA--; intB--;
    }

    //Remove trailing zeroes
    while (!decimalResult.empty() && decimalResult.back() == '0') decimalResult.pop_back();
    integerResult = removeZeroes(integerResult);

    //Add decimal part back
    string result = integerResult;
    if (!decimalResult.empty())
        result += "." + decimalResult;

    //If result is zero, return 0
    if (result.empty()) result = "0";
    return result;
}

//Function to add the strings together
string addStrings(string a, string b) {
    //Create an integer for the sign of a
    int signA = returnSign(a);
    //Create an integer for the sign of b
    int signB = returnSign(b);

    //Grab the sign of a
    a = takeSign(a);
    //Grab the sign of b
    b = takeSign(b);

    //Declare result and sign
    string result;
    int resultSign = +1;

    //For same sign addition
    if (signA == signB) {
        //Add same sign
        result = addPositive(a, b);
        //Set sign
        resultSign = signA;
    //For not same sign addition
    } else {
        //Declare compare string result
        int comparePositiveString = comparePositiveStrings(a, b);
        //If compare is equal to 0
        if (comparePositiveString == 0) {
            //Set result to 0
            result = "0";
            //Set sign to Positive
            resultSign = +1;
        //If more than 0
        } else if (comparePositiveString > 0) {
            //Set result to subtracted strings
            result = subtractStrings(a, b);
            //Set sign to the correct sign
            resultSign = signA;
        //Otherwise
        } else {
            //Ser result to subtracted strings
            result = subtractStrings(b, a);
            //Set to the correct sign
            resultSign = signB;
        }
    }

    //If result is 0, return the result
    if (result == "0") return result;
    //If negative sign, switch sign to negative.
    if (resultSign == -1) result = "-" + result;
    //Return result
    return result;
}

//Main
int main() {
    //Have user enter file
    cout << "Enter file name: ";
    //declare fileName string
    string fileName;
    //Set the user input to fileName
    cin >> fileName;

    //Read file
    ifstream inputFile(fileName);
    //For if there is an error
    if (!inputFile) {
        //Print error message
        cerr << "Cannot open file\n";
        return 1;
    }

    //Declare string a and b
    string a, b;
    //While reading file
    while (inputFile >> a >> b) {
        //Message to make sure numbers are read
        cout << "Checking: " << a << " , " << b << endl;

        //Declare and check valid numbers
        bool validA = checkDouble(a);
        bool validB = checkDouble(b);

        //If a number is valid
        if (!validA || !validB) {
            //Print for invalid number and which number/numbers is invalid
            cout << "Invalid number(s): ";
            if (!validA) cout << a << " ";
            if (!validB) cout << b << " ";
            cout << endl << "-----------------------------------\n";
            //Move on
            continue;
        }

        //Add string if valid
        string sum = addStrings(a, b);
        //Print result of addition
        cout << a << " + " << b << " = " << sum << endl;
        cout << "-----------------------------------\n";
    }

    //Close file
    inputFile.close();
    //End program
    return 0;
}