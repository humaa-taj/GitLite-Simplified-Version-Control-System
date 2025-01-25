#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include<filesystem>
namespace fs = std::filesystem;
class String {
public:
    char* s;
    String() {
        //s = NULL;
        s = new char[1];
        s[0] = '\0';
    }// default constructor
    char* getdata() {
        return s;
    }
    String(const char* str) {
        int count = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            count++;
        }
        s = new char[count + 1];
        for (int i = 0; i < count; i++) {
            s[i] = str[i];
        }
        s[count] = '\0';
    }
    //String::String(int x) {
    //	s = new char[1];
    //	s[0] = '\0';
    //}

    String(int x)
    {
        s = new char[x + 1];
        for (int i = 0; i < x; ++i)
        {
            s[i] = '\0';
        }
        s[x] = '\0';
    }

    String(const String& copy) {

        int l = 0;

        for (int i = 0; copy.s[i] != '\0'; i++) {

            l++;

        }

        s = new char[l + 1];

        for (int i = 0; i < l; i++) {
            s[i] = copy.s[i];
        }
        s[l] = '\0';
    }


    const char& operator[](int i) const
    {

        int l;
        l = 0;
        while (s[l] != '\0') {
            l++;
        }

        bool check = (i < 0) ? true : false;

        if (check) {
            i = l + i;
        }
        bool flag = false;
        if (i >= 0 && i < l)
        {
            return s[i];
        }

        else
        {
            flag = true;
        }
        if (true)
        {
            return '\0';
        }
    }
    char& operator[](int i)
    {

        int l;
        l = 0;
        while (s[l] != '\0') {
            l++;
        }

        bool check = (i < 0) ? true : false;

        if (check) {
            i = l + i;
        }
        bool flag = false;
        if (i >= 0 && i < l)
        {
            return s[i];
        }

        else
        {
            flag = true;
        }
        if (true)
        {
            char c = '\0';
            return c;
        }
    }

    int stringSize()
    {
        if (s == nullptr)
        {
            return 0;
        }
        int i = 0;
        while (s[i] != '\0') {
            i++;
        }
        return i;
    }
    //Arithmetic Operators

    String operator+(const String& str)
    {
        String obj;

        int counter1 = 0, counter2 = 0;
        /*for (int i = 0; s[i] != '\0'; i++) {
            counter1++;
        }*/
        counter1 = this->stringSize();

        for (int i = 0; str.s[i] != '\0'; i++) {
            counter2++;
        }
        obj.s = new char[counter1 + counter2 + 1];
        for (int i = 0; i < counter1; i++) {
            obj.s[i] = s[i];
        }
        for (int i = counter1, j = 0; i < counter1 + counter2 + 1; j++, i++) {
            obj.s[i] = str[j];
        }
        obj.s[counter1 + counter2] = '\0';
        //obj.s = new temp[]
        return obj;

    }

    String operator+(char str)
    {
        String obj;
        if (this->s[0] == '\0') {
            obj.s = new char[2];
            obj.s[0] = str;
            obj.s[1] = '\0';
            return obj;
        }
        int counter1 = 0, counter2 = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            counter1++;
        }
        obj.s = new char[counter1 + 2];
        for (int i = 0; i < counter1; i++) {
            obj.s[i] = s[i];
        }
        obj.s[counter1] = str;
        obj.s[counter1 + 1] = '\0';
        return obj;
    }

    String operator+(const char* str)
    {
        int counter1 = 0, counter2 = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            counter1++;
        }
        char* temp = new char[counter1 + 1];
        for (int i = 0; i < counter1; i++) {
            temp[i] = s[i];
        }
        temp[counter1] = '\0';
        for (int i = 0; str[i] != '\0'; i++) {
            counter2++;
        }
        delete s;
        s = NULL;
        s = new char[counter1 + counter2 + 1];
        for (int i = 0, j = 0; i < counter1 + counter2; i++) {
            if (i < counter1)
                s[i] = temp[i];
            if (i == counter1)
                s[i] = str[j++];
            if (i > counter1) {
                s[i] = str[j++];
            }
        }
        s[counter1 + counter2] = '\0';
        delete temp;
        return *this;
    }


    String operator-(const String& substr) {
        //removes the substr from the String
            //if substr exist 
        int occur = 0;
        bool check = false;
        bool stop = false;
        int subStrLength = 0;
        for (int i = 0; substr.s[i] != '\0'; i++) {
            subStrLength++;
        }
        int strLength = 0, correct = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            strLength++;
        }
        char* temp = new char[strLength + 1];
        for (int i = 0; i < strLength; i++) {
            temp[i] = s[i];
        }
        temp[strLength] = '\0';
        for (int i = 0, z = 0; i < strLength; i++) {
            if (s[i] == substr.s[0]) {

                correct++;
                for (int j = i + 1, k = 1; k < subStrLength; j++, k++) {
                    if (substr.s[k] == s[j])
                    {
                        correct++;
                    }

                }
                if (correct == subStrLength) {
                    for (int x = i, y = 0; y < subStrLength; y++, x++) {
                        temp[x] = '1';
                    }
                    stop = true;
                    occur++;
                }

            }
            if (stop)
                i += correct;
            correct = 0;

        }
        delete s;
        s = NULL;
        int size = strLength - subStrLength * occur;
        s = new char[size + 1];
        for (int i = 0, j = 0; i < size, j < strLength; j++) {
            if (temp[j] != '1') {
                s[i++] = temp[j];
            }
        }
        s[size] = '\0';
        delete temp;
        return *this;

    }




    String operator-(const char* str) {
        ////removes the str from the String
        bool check = false;
        bool stop = false;
        int subStrLength = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            subStrLength++;
        }


        int strLength = 0, correct = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            strLength++;
        }
        char* temp = new char[strLength + 1];
        for (int i = 0; i < strLength; i++) {
            temp[i] = s[i];
        }
        temp[strLength] = '\0';
        int occur = 0;
        for (int i = 0, z = 0; i < strLength; i++) {
            if (s[i] == str[0]) {

                correct++;
                for (int j = i + 1, k = 1; k < subStrLength; j++, k++) {
                    if (str[k] == s[j])
                    {
                        correct++;
                    }

                }
                if (correct == subStrLength) {
                    for (int x = i, y = 0; y < subStrLength; y++, x++) {
                        temp[x] = '1';
                    }
                    stop = true;
                    occur++;
                }

            }
            if (stop)
                i += correct;
            correct = 0;

        }
        delete s;
        s = NULL;
        int size = strLength - subStrLength * occur;
        s = new char[size + 1];
        for (int i = 0, j = 0; i < size, j < strLength; j++) {
            if (temp[j] != '1') {
                s[i++] = temp[j];
            }
        }
        s[size] = '\0';
        delete temp;
        return *this;


    }

    String operator-(const char& str) {
        ////removes all occurrences of char from the String
        int strLength = 0, correct = 0, strLen = 0, starCount = 0;

        for (int i = 0; s[i] != '\0'; i++) {
            strLength++;
        }
        char* temp = new char[strLength + 1];
        for (int i = 0; i < strLength; i++) {
            temp[i] = s[i];
        }
        temp[strLength] = '\0';
        for (int i = 0; i < strLength; i++)
        {
            if (temp[i] == str) {

                temp[i] = '*';
                starCount++;
            }
        }

        delete s;
        s = NULL;
        int c = 0;
        int size = strLength - starCount + 1;
        //cout << "Size " << size << endl;
        s = new char[size];
        for (int i = 0, j = 0; i < strLength; i++) {
            if (temp[i] != '*') {
                s[j++] = temp[i];
                c++;
            }
        }

        s[size - 1] = '\0';

        delete[]temp;
        return *this;

    }
    String CharPtrTostring(char* ptr)
    {
        int size = 0;
        String obj;
        if (ptr == nullptr) {
            return obj;
        }
        for (int i = 0; ptr[i] != '\0'; i++) {
            size++;
        }
        obj.s = new char[size + 1];
        for (int i = 0; i < size; i++) {
            obj.s[i] = ptr[i];
        }
        obj.s[size] = '\0';
        return obj;

    }
    //Udhaar Function
    int operator()(char c) const
    {

        for (int i = 0; ; ++i)
        {
            if (s[i] == '\0') {
                break;
            }
            if (s[i] == c)
            {
                return i;
            }
        }
        return -1;
    }


    //Udhaar Function

    int operator()(const String& t) const
    {
        int length = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            length++;
        }
        for (int i = 0; s[i] != '\0'; ++i)
        {
            if (s[i] == t.s[0])
            {
                return i;
            }

        }

        return -1;
    }


    //Udhaar Function
    int operator()(const char* str) const
    {
        int length = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            length++;
        }
        for (int i = 0; s[i] != '\0'; ++i)
        {
            if (s[i] == str[0])
            {
                return i;
            }

        }
        return -1;
    }


    //EXCEPTION
    ///*operator int()
    //{
    //	int length = 0;
    //	for (int i = 0; s[i] != '\0'; i++)
    //	{
    //		length++;
    //	}
    //	return length;


    //}*/
    bool operator!() {
        if (s[0] == '\0')
            return 1;
        else
            return 0;
    }

    bool operator==(String str) {
        // returns true if two Strings are equal
        int strLength = 0;
        int secondStrLength = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            strLength++;
        }
        for (int i = 0; str.s[i] != '\0'; i++) {
            secondStrLength++;
        }
        if (strLength != secondStrLength) {
            return false;
        }
        bool check = true;
        for (int i = 0; i < strLength; i++) {
            if (s[i] != str.s[i]) {
                check = false;
                break;
            }
        }
        if (check) {
            return true;
        }
        else
            return false;
    }

    bool operator==(const char* str) {
        // returns true if the c-string is equal to the String
        int strLength = 0;
        int secondStrLength = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            strLength++;
        }
        for (int i = 0; str[i] != '\0'; i++) {
            secondStrLength++;
        }
        if (strLength != secondStrLength) {
            return false;
        }
        bool check = true;
        for (int i = 0; i < strLength; i++) {
            if (s[i] != str[i]) {
                check = false;
                break;
            }
        }
        if (check) {
            return true;
        }
        else
            return false;
    }



    //bool operator>(const char* str) const
    //{



    //	const char* current = this->s; // Assuming s holds the string data.

    //	while (*current != '\0' && *str != '\0') {
    //		if (*current > *str) {
    //			return true; // Current string is greater
    //		}
    //		else if (*current < *str) {
    //			return false; // Input string is greater
    //		}
    //		++current;
    //		++str;
    //	}

    //	// If we reach here, one string is a prefix of the other.
    //	// The longer string is considered greater.
    //	return (*current != '\0');
    //}


    String& operator=(const String& str)
    {
        // copies one String to another
        int secondStrLength = 0;
        for (int i = 0; str.s[i] != '\0'; i++) {
            secondStrLength++;
        }
        delete s;
        s = NULL;
        s = new char[secondStrLength + 1];
        for (int i = 0; str.s[i] != '\0'; i++) {
            s[i] = str.s[i];
        }
        s[secondStrLength] = '\0';
        return *this;
    }
    String& operator=(char* str) {

        // copies one c-string to another
        int secondStrLength = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            secondStrLength++;
        }
        delete s;
        s = NULL;
        s = new char[secondStrLength + 1];
        for (int i = 0; str[i] != '\0'; i++) {
            s[i] = str[i];
        }
        s[secondStrLength] = '\0';
        return *this;
    }
    String& operator=(const char* str) {

        // copies one c-string to another
        int secondStrLength = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            secondStrLength++;
        }
        delete s;
        s = NULL;
        s = new char[secondStrLength + 1];
        for (int i = 0; str[i] != '\0'; i++) {
            s[i] = str[i];
        }
        s[secondStrLength] = '\0';
        return *this;
    }
    String& operator=(char c) {
        // Assuming single character handling
        if (this->stringSize() != 1)
        {
            delete[] s;
            s = new char[2] {c, '\0'};

        }
        else
        {
            s[0] = c;
        }
        return *this;
    }
    ~String() {
        delete s;
        s = nullptr;
    }// destructor
    friend std::ostream& operator<<(std::ostream& output, const String& str);
    friend std::istream& operator>>(std::istream& input, String& str);
    int stringToInt()
    {

        int size = stringSize();
        int weight = 1;
        int total = 0;
        for (int i = size - 1; i >= 0; i--) {
            int a = s[i] - '0';
            a = a * weight;
            total += a;
            weight = weight * 10;
        }
        //cout << "NUM" << total << endl;
        return total;
    }

    // Reads a line from a file into a buffer
    bool mygetline(std::ifstream& file, char* buffer, int bufferSize) {
        char ch;
        int i = 0;

        while (file.get(ch)) {  // Continue reading characters
            if (ch == '\n') {   // Stop at a newline
                break;
            }
            if (i < bufferSize - 1) {  // Avoid exceeding buffer size
                buffer[i++] = ch;
            }
        }
        buffer[i] = '\0';  // Null-terminate the string
        return i > 0 || !file.eof();  // Return true if anything was read
    }
    bool empty() {
        return s == NULL;
    }
    char back() {
        int size = stringSize();
        return s[size - 1];
    }
    void clear() {
        delete s;
        s = nullptr;
        s = new char[1];
        s[0] = '\0';
    }
    char* constCharPointer()
    {
        return s;
    }
    String substr(int start, int end) {
        bool copy = false;
        String temp;
        for (int i = 0; i < end; i++) {
            if (i == start) {
                copy = true;
            }
            if (copy) {
                temp = temp + s[i];
            }
        }
        temp = temp + '\0';
        return temp;
    }
    String substr(int start) {
        String temp; bool copy = false;
        for (int i = 0; s[i] != '\0'; i++) {
            if (i == start) {
                copy = true;
            }
            if (copy) {
                temp = temp + s[i];
            }
        }
        temp = temp + '\0';
        return temp;
    }
    //char& operator[](size_t index) {
    //	if (index >= stringSize()) {
    //		throw std::out_of_range("Index out of range");
    //	}
    //	return s[index]; // Assuming s is your internal character array
    //}

    //const char& operator[](size_t index) const {
    //	if (index >= stringSize()) {
    //		throw std::out_of_range("Index out of range");
    //	}
    //	return s[index];
    //}
    // 



    bool getline(std::ifstream& file, String& buffer)
    {
        buffer = "";
        char ch;
        int i = 0;

        while (file.get(ch)) {  // Continue reading characters
            if (ch == '\n' || ch == '\0') {   // Stop at a newline
                break;
            }
            //if (i < bufferSize - 1) {  // Avoid exceeding buffer size
            buffer = buffer + ch;
            i++;
            //}
        }
        buffer = buffer + '\0';  // Null-terminate the string
        if (i > 0 || !file.eof())
            return true;  // Return true if anything was read
        else if (file.eof())
            return false;


    }
    bool operator>(const char* rhs) const
    {
        if (rhs == NULL)
        {
            if (s)
            {
                return true;
            }
            return false;
        }
        int i = 0;

        while (s[i] != '\0' && *rhs != '\0') {
            if (s[i] > *rhs) {
                return true; // lhs is greater
            }
            else if (s[i] < *rhs) {
                return false; // rhs is greater
            }
            i++;;
            ++rhs; // Move to the next character
        }
        // If one string is a prefix of the other, the longer string is greater
        return *rhs == '\0' && s[i] != '\0';
    }
    bool operator>(String rhs)
    {
        if (this->stringSize() > rhs.stringSize()) {
            return true;
        }
        if (this->stringSize() < rhs.stringSize()) {
            return false;
        }
        if (rhs.s[0] == '\0')
        {
            if (s[0] == '\0')
            {
                return false;
            }
            return true;
        }
        int i = 0;

        while (s[i] != '\0' && rhs[i] != '\0') {
            if (s[i] > rhs[i]) {
                return true; // lhs is greater
            }
            else if (s[i] < rhs[i]) {
                return false; // rhs is greater
            }
            i++;;
            //rhs; // Move to the next character
        }
        // If one string is a prefix of the other, the longer string is greater
        return rhs[i] == '\0' && s[i] != '\0';
    }
    bool operator<(const char* rhs) const {
        if (rhs == NULL)
        {
            if (s)
            {
                return true;
            }
            return false;
        }
        int i = 0;

        while (s[i] != '\0' && *rhs != '\0') {
            if (s[i] < *rhs) {
                return true; // lhs is greater
            }
            else if (s[i] > *rhs) {
                return false; // rhs is greater
            }
            i++;;
            ++rhs; // Move to the next character
        }
        // If one string is a prefix of the other, the longer string is greater
        return *rhs == '\0' && s[i] != '\0';
    }
    bool operator<(String rhs) {
        if (rhs.s[0] == '\0')
        {
            if (s[0] == '\0')
            {
                return false;
            }
            return true;
        }
        if (this->stringSize() > rhs.stringSize())
        {
            return false;
        }
        if (this->stringSize() < rhs.stringSize())
        {
            return true;
        }
        int i = 0;

        while (s[i] != '\0' && rhs[i] != '\0') {
            if (s[i] < rhs.s[i]) {
                return true; // lhs is greater
            }
            else if (s[i] > rhs.s[i]) {
                return false; // rhs is greater
            }
            i++;;
            //rhs; // Move to the next character
        }
        // If one string is a prefix of the other, the longer string is greater
        return rhs[i] == '\0' && s[i] != '\0';
    }
};
//ostream& operator<<(ostream& output, const String& str);
//istream& operator>>(istream& input, String& str);

ostream& operator<<(ostream& output, const String& str) {
    if (str.s == NULL) {
        output << "";
        return output;
    }
    else
    {
        output << str.s;

        return output;
    }


}
#include <stack>

istream& operator>>(istream& input, String& str) {
    str.s = new char[100];
    input >> str.s;
    str.s = str.s;
    return input;
}

const char* to_String(int num)
{
    // Handle the case where num is zero
    if (num == 0) {
        char* result = new char[2]; // "0" + null terminator
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    bool isNegative = (num < 0); // Check if the number is negative
    if (isNegative) {
        num = -num; // Convert to positive for processing
    }

    char buffer[12]; // Temporary buffer for digits (int max is 10 digits + sign + null terminator)
    int index = 0;

    // Extract digits and store in reverse order
    while (num > 0) {
        buffer[index++] = '0' + (num % 10); // Convert digit to char
        num /= 10;                         // Remove the last digit
    }

    // Add the negative sign if needed
    if (isNegative) {
        buffer[index++] = '-';
    }

    // Null-terminate the String
    buffer[index] = '\0';

    // Reverse the String to get the correct order
    std::reverse(buffer, buffer + index);

    // Allocate memory dynamically for the result
    char* result = new char[index + 1];
    //std::strcpy(result, buffer);
    strcpy_s(result, sizeof(result), buffer);
    return result;
}



//#pragma once
//#include <fstream>
//#include<filesystem>
//#include"String.h"
//#include <iostream>
//using namespace std;
//namespace fs = std::filesystem;

class AVLTree
{
public:
    String root;

    // Helper function to fetch a specific line from a file
    String fetchLine(String filePath, int lineNumber)
    {
        // String temp = filePath;

       // const char* path = filePath.constCharPointer();
        ifstream file(filePath.constCharPointer());

        if (!file)
            return "NULL";

        //String line;
        char line[1024]{ '\0' };
        for (int i = 1; i <= lineNumber && filePath.mygetline(file, line, 1024); i++)
        {
            if (i == lineNumber)
                return line;
        }
        return "NULL";
    }


    void updateLine(String& filePath, int lineNumber, const char* content)
    {
        const char* tempFilePath = "temp_file.txt"; // Temporary file to store updated content
        const char* path = filePath.constCharPointer();
        ifstream file(path);
        ofstream tempFile(tempFilePath);

        if (!file.is_open() || !tempFile.is_open())
        {
            //  cerr << "Error opening file!" << endl;
            return;
        }

        //String line;
        char line[1024]{ '\0' };
        int currentLine = 1;
        bool lineUpdated = false;

        while (filePath.mygetline(file, line, 1024)) {
            if (currentLine == lineNumber)
            {
                tempFile << content << endl;
                lineUpdated = true;
            }
            else {
                tempFile << line << endl;
            }
            currentLine++;
        }

        file.close();
        tempFile.close();
        try
        {
            std::filesystem::remove(path);
            std::filesystem::rename(tempFilePath, path);
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        }
    }




    // Helper function to get node's key from the file
    String getKey(String filePath) {
        return fetchLine(filePath, 1);
    }

    // Helper function to get height from the file
    int getHeight(String filePath)
    {
        String line = fetchLine(filePath, 5);
        if (line == "NULL")
        {
            return 0;
        }
        else
            return line.stringToInt();
    }

    // Helper function to set the height in the file
    void setHeight(String& filePath, int height) {
        updateLine(filePath, 5, to_String(height));
    }

    // Helper function to calculate balance factor
    int getBalance(String& filePath) {
        String leftPath = fetchLine(filePath, 3);
        String rightPath = fetchLine(filePath, 4);
        return getHeight(leftPath) - getHeight(rightPath);
    }


    String rightRotate(String yPath) {
        String xPath = fetchLine(yPath, 3);
        String T2Path = fetchLine(xPath, 4);

        // Perform rotation
        updateLine(xPath, 4, yPath.constCharPointer());
        updateLine(yPath, 3, T2Path.constCharPointer());

        if (!(T2Path == "NULL")) updateLine(T2Path, 2, yPath.constCharPointer()); // Update T2's parent

        // Update parent pointers
        String yParentPath = fetchLine(yPath, 2);
        updateLine(xPath, 2, yParentPath.constCharPointer());
        updateLine(yPath, 2, xPath.constCharPointer());

        // Update parent's reference to the rotated node
        if (!(yParentPath == "NULL"))
        {
            if (fetchLine(yParentPath, 3) == yPath) {
                updateLine(yParentPath, 3, xPath.constCharPointer());
            }
            else if (fetchLine(yParentPath, 4) == yPath) {
                updateLine(yParentPath, 4, xPath.constCharPointer());
            }
        }

        // Update heights
        setHeight(yPath, 1 + max(getHeight(fetchLine(yPath, 3)), getHeight(fetchLine(yPath, 4))));


        setHeight(xPath, 1 + max(getHeight(fetchLine(xPath, 3)), getHeight(fetchLine(xPath, 4))));

        return xPath;
    }

    String leftRotate(String xPath) {
        String yPath = fetchLine(xPath, 4);
        String T2Path = fetchLine(yPath, 3);

        // Perform rotation
        updateLine(yPath, 3, xPath.constCharPointer());
        updateLine(xPath, 4, T2Path.constCharPointer());

        if (!(T2Path == "NULL")) updateLine(T2Path, 2, xPath.constCharPointer()); // Update T2's parent

        // Update parent pointers
        String xParentPath = fetchLine(xPath, 2);
        updateLine(yPath, 2, xParentPath.constCharPointer());
        updateLine(xPath, 2, yPath.constCharPointer());

        // Update parent's reference to the rotated node
        if (!(xParentPath == "NULL")) {
            if (fetchLine(xParentPath, 3) == xPath) {
                updateLine(xParentPath, 3, yPath.constCharPointer());
            }
            else if (fetchLine(xParentPath, 4) == xPath) {
                updateLine(xParentPath, 4, yPath.constCharPointer());
            }
        }

        // Update heights
        setHeight(xPath, 1 + max(getHeight(fetchLine(xPath, 3)), getHeight(fetchLine(xPath, 4))));
        setHeight(yPath, 1 + max(getHeight(fetchLine(yPath, 3)), getHeight(fetchLine(yPath, 4))));

        return yPath;
    }

    //deletefile(String )


    String insert(String& nodePath, String key, String& parentPath)
    {
        if (nodePath == "NULL")
        {
            // Create a new file for the node
            const char* keyPath = key.constCharPointer();
            ofstream newFile(keyPath);
            newFile << key << endl;       // Key
            newFile << parentPath << endl; // Parent (set to provided parent path)
            newFile << "NULL" << endl;    // Left child
            newFile << "NULL" << endl;    // Right child
            newFile << "1" << endl;       // Height
            return key;                   // Return the path of the new node
        }

        String currentKey = getKey(nodePath);
        if (key < currentKey) {
            String leftPath = fetchLine(nodePath, 3);
            String newLeft = insert(leftPath, key, nodePath); // Pass current node as parent
            updateLine(nodePath, 3, newLeft.constCharPointer());                // Update left child
        }
        else if (key > currentKey) {
            String rightPath = fetchLine(nodePath, 4);
            String newRight = insert(rightPath, key, nodePath); // Pass current node as parent
            updateLine(nodePath, 4, newRight.constCharPointer());                 // Update right child
        }
        else {
            return nodePath; // Key already exists, do nothing
        }

        // Update height of the current node
        setHeight(nodePath, 1 + max(getHeight(fetchLine(nodePath, 3)), getHeight(fetchLine(nodePath, 4))));

        // Balance the AVL tree
        int balance = getBalance(nodePath);
        if (balance > 1 && key < getKey(fetchLine(nodePath, 3))) {
            return rightRotate(nodePath);
        }
        if (balance < -1 && key > getKey(fetchLine(nodePath, 4))) {
            return leftRotate(nodePath);
        }
        if (balance > 1 && key > getKey(fetchLine(fetchLine(nodePath, 3), 4))) {
            updateLine(nodePath, 3, leftRotate(fetchLine(nodePath, 3)).constCharPointer());
            return rightRotate(nodePath);
        }
        if (balance < -1 && key < getKey(fetchLine(fetchLine(nodePath, 4), 3))) {
            updateLine(nodePath, 4, rightRotate(fetchLine(nodePath, 4)).constCharPointer());
            return leftRotate(nodePath);
        }

        return nodePath;
    }
    String insertIterative(String nodePath, String key, String parentPath)
    {
        String parentNode = "NULL";
        String currentNode = nodePath;

        // Step 1: Traverse the tree to find the appropriate position for the new key
        while (!(currentNode == "NULL"))
        {
            parentNode = currentNode;
            String currentKey = getKey(currentNode);

            if (key < currentKey) {
                currentNode = fetchLine(currentNode, 3); // Move to the left child
            }
            else if (key > currentKey) {
                currentNode = fetchLine(currentNode, 4); // Move to the right child
            }
            else {
                return nodePath; // Key already exists, return the root path
            }
        }

        // Step 2: Create the new node
        const char* keyPath = key.constCharPointer();
        ofstream newFile(keyPath);
        newFile << key << endl;         // Key
        newFile << parentNode << endl;  // Parent
        newFile << "NULL" << endl;      // Left child
        newFile << "NULL" << endl;      // Right child
        newFile << "1" << endl;         // Height
        newFile.close();
        String newNodePath = key;

        // Step 3: Link the new node to its parent
        if (!(parentNode == "NULL"))
        {
            String parentKey = getKey(parentNode);
            if (key < parentKey)
            {
                updateLine(parentNode, 3, newNodePath.constCharPointer()); // Link as left child
            }
            else
            {
                updateLine(parentNode, 4, newNodePath.constCharPointer()); // Link as right child
            }
        }
        else
        {
            return newNodePath; // Tree was empty; return new node as root
        }

        // Step 4: Update heights and balance the tree iteratively
        currentNode = parentNode;
        while (!(currentNode == "NULL"))
        {
            // Update the height of the current node
            setHeight(currentNode, 1 + max(getHeight(fetchLine(currentNode, 3)), getHeight(fetchLine(currentNode, 4))));

            // Check balance factor
            int balance = getBalance(currentNode);

            // Perform rotations if needed
            if (balance > 1) {
                if (key < getKey(fetchLine(currentNode, 3))) {
                    // Left Left case
                    currentNode = rightRotate(currentNode);
                }
                else {
                    // Left Right case
                    String leftChild = fetchLine(currentNode, 3);
                    updateLine(currentNode, 3, leftRotate(leftChild).constCharPointer());
                    currentNode = rightRotate(currentNode);
                }
            }
            else if (balance < -1)
            {
                if (key > getKey(fetchLine(currentNode, 4))) {
                    // Right Right case
                    currentNode = leftRotate(currentNode);
                }
                else {
                    // Right Left case
                    String rightChild = fetchLine(currentNode, 4);
                    updateLine(currentNode, 4, rightRotate(rightChild).constCharPointer());
                    currentNode = leftRotate(currentNode);
                }
            }

            // Update parent node's links if rotations occur
            if (!(currentNode == "NULL")) {
                parentNode = fetchLine(currentNode, 2);
                if (!(parentNode == "NULL")) {
                    if (fetchLine(parentNode, 3) == currentNode) {
                        updateLine(parentNode, 3, currentNode.constCharPointer());
                    }
                    else if (fetchLine(parentNode, 4) == currentNode) {
                        updateLine(parentNode, 4, currentNode.constCharPointer());
                    }
                }
                else {
                    nodePath = currentNode; // Update root if needed
                }
            }

            // Move up the tree
            currentNode = parentNode;
        }

        return nodePath;
    }

    // Rebalance the tree
    String rebalance(String node)
    {

        if (!(node == "NULL"))
        {
            setHeight(node, 1 + max(getHeight(fetchLine(node, 3)), getHeight(fetchLine(node, 4))));
        }

        // Check balance factor
        int balance = getBalance(node);

        // Perform rotations if needed
        if (balance > 1)
        {
            String s = fetchLine(node, 3);
            String k = getKey(s);
            if (getBalance(s) < 0)
            {
                // Left Left case
                // if cant reolve error undo chnages like storing in String and then returning in fetch

                updateLine(k, 3, leftRotate(s).constCharPointer());
            }
            return rightRotate(node);

        }
        else if (balance < -1)
        {
            String s = fetchLine(node, 4);
            String k = getKey(s);
            if (getBalance(s) > 0)
            {
                // Left Left case
                updateLine(k, 3, rightRotate(s).constCharPointer());
            }
            return   leftRotate(node);
        }


        return node;
    }

    // Find the in-order predecessor (maximum value in the left subtree)
    String findPredecessor(String node)
    {
        String current = fetchLine(node, 4);
        while (!(current == "NULL") && !(fetchLine(current, 3) == "NULL"))
        {
            current = fetchLine(current, 3);
        }
        return current;
    }

    // Deletion of a node from the AVL tree
    String& deleteNode(String key)
    {
        if (root == "NULL")
        {
            String s = "NULL";
            return s; // Key not found
        }

        stack<String> path; // Stack to track the path to the root
        String current = root;
        String keyOfcurrent;
        String leftOfcurrent;
        String rightOfcurrent;

        // Step 1: Perform standard BST delete and track the path
        while (!(current == "NULL") && !(current == key))
        {
            keyOfcurrent = getKey(current);
            leftOfcurrent = fetchLine(current, 3);
            rightOfcurrent = fetchLine(current, 4);
            path.push(current);
            if (key < keyOfcurrent)
            {
                current = fetchLine(current, 3); // Move to the left child
                keyOfcurrent = leftOfcurrent;
            }
            else
            {
                current = fetchLine(current, 4); // Move to the left child
                keyOfcurrent = rightOfcurrent;
            }
        }

        if ((current == "NULL"))
        {
            std::cerr << "Key not found in the tree.\n";
            return root;
        }
        keyOfcurrent = getKey(current);
        leftOfcurrent = fetchLine(current, 3);
        rightOfcurrent = fetchLine(current, 4);

        // Handle node with one or no child
        if ((leftOfcurrent == "NULL") || (rightOfcurrent == "NULL"))
        {
            String replacement = (!(leftOfcurrent == "NULL")) ? leftOfcurrent : rightOfcurrent;
            if (!path.empty())
            {
                String parent = path.top();
                String leftofparent = fetchLine(parent, 3);
                String rightofparent = fetchLine(parent, 4);

                if (leftofparent == current)
                {

                    updateLine(parent, 3, replacement.constCharPointer());
                    leftofparent = replacement;
                }
                else
                {

                    updateLine(parent, 4, replacement.constCharPointer());
                    rightofparent = replacement;
                }

            }
            else
            {
                root = replacement; // If root is being deleted

            }
            //delete current;
            //deleteFile(replacement);
            std::filesystem::remove(current.constCharPointer());
            //return root;

        }
        else
        {

            // Node with two children: Replace with in-order predecessor
            String predecessor = findPredecessor(current);
            String predecessorKey = getKey(predecessor);

            keyOfcurrent = predecessorKey;
            String par = fetchLine(current, 2);
            String lef = fetchLine(current, 3);
            String rig = fetchLine(current, 4);
            if (rig == predecessorKey)
            {
                rig = "NULL";
            }
            String col = fetchLine(current, 5);


            String caller;
            ofstream write_in(current.constCharPointer());
            ifstream write_from(predecessor.constCharPointer());
            String data1;
            int linenum = 1;
            while (caller.getline(write_from, data1))
            {
                if (linenum == 1)
                {
                    write_in << data1 << endl;
                }
                if (linenum == 2)
                {
                    write_in << par << endl;
                }
                if (linenum == 3)
                {
                    write_in << lef << endl;
                }
                if (linenum == 4)
                {
                    write_in << rig << endl;
                }
                if (linenum == 5)
                {
                    write_in << col << endl;
                }
                if (linenum > 5)
                    write_in << data1 << endl;
                linenum++;
            }

            write_in.close();
            write_from.close();
            deleteNode(predecessorKey); // Delete the predecessor
            // remname current file as predecessor 
            filesystem::rename(current.constCharPointer(), predecessor.constCharPointer());
            // fetch parent from precdessor and open that file and replace current to predecessor 
            String ParentofdeletedFile = fetchLine(predecessor, 2);
            if (ParentofdeletedFile == "NULL")
            {
                root = predecessor;
                ofstream file("Root.txt");
                file << predecessor;
                file.close();

            }
            if (fetchLine(ParentofdeletedFile, 3) == current)
            {
                updateLine(ParentofdeletedFile, 3, predecessor.constCharPointer());
            }
            else  if (fetchLine(ParentofdeletedFile, 4) == current)
            {
                updateLine(ParentofdeletedFile, 4, predecessor.constCharPointer());
            }
            String lc = fetchLine(predecessor, 2);
            String rc = fetchLine(predecessor, 3);
            updateLine(lc, 2, predecessor.constCharPointer());
            updateLine(rc, 2, predecessor.constCharPointer());


        }

        // Step 2: Fix balance factors iteratively up to the root
        while (!path.empty())
        {
            String node = path.top();
            path.pop();
            node = rebalance(node);

            if (!path.empty())
            {
                String parent = path.top();
                if (fetchLine(parent, 3) == node)
                {
                    updateLine(parent, 3, node.constCharPointer());
                }
                else
                {
                    updateLine(parent, 4, node.constCharPointer());
                }
            }
            else
            {
                root = node; // Update root when we reach the top
            }
        }

        return root;
    }




    //// Display the AVL tree (inorder traversal)
    //void display(const String& nodePath, int space = 0, int COUNT = 10) {
    //    if (nodePath == "NULL") return;
    //
    //    space += COUNT;
    //    display(fetchLine(nodePath, 4), space);
    //
    //    cout << endl;
    //    for (int i = COUNT; i < space; i++) cout << " ";
    //    cout << getKey(nodePath) << endl;
    //
    //    display(fetchLine(nodePath, 3), space);
    //}
    //void displayIterative(const String& nodePath)
    //{
    //    stack<String> nodeStack;
    //    String current = nodePath;
    //
    //    while (!nodeStack.empty() || !(current=="NULL")) {
    //        while (!(current=="NULL")) {
    //            nodeStack.push(current);
    //            current = fetchLine(current, 4); // Move to left child
    //        }
    //
    //        current = nodeStack.top();
    //        nodeStack.pop();
    //        cout << getKey(current) << endl;
    //
    //        current = fetchLine(current, 3); // Move to right child
    //    }
    //}
    void displayIterativeS() {
        stack<pair<String, int>> nodeStack; // Stack holds the node path and its depth
        String current = root;
        int depth = 0;

        while (!nodeStack.empty() || !(current == "NULL")) {
            while (!(current == "NULL")) {
                nodeStack.push({ current, depth });
                depth++;
                current = fetchLine(current, 4); // Move to left child
            }

            auto [node, level] = nodeStack.top(); // Unpack node and depth
            nodeStack.pop();

            // Print the key with indentation based on depth
            for (int i = 0; i < level; ++i) cout << "    "; // 4 spaces for each level
            cout << getKey(node) << " (" << fetchLine(node, 5) << ")" << endl; // Display key and color

            current = fetchLine(node, 3); // Move to right child
            depth = level + 1;
        }
    }

    void processColumn(int columnIndex, const char* filename, String folder)
    {
        ifstream file(filename);
        if (!file) {
            cout << "Error: File could not be opened!" << endl;
            return;
        }


        String strObj;
        int bufferSize = 500;
        char buffer[500]{ '\0' };
        strObj.mygetline(file, buffer, bufferSize);
        //String folder;

        int counter = 0;


        String line;
        int lineNumber = 1;


        while (strObj.mygetline(file, buffer, bufferSize))
        {


            lineNumber++;

            String cell;
            bool inQuotes = false;
            counter = 0;
            // Parse the line manually, handling quoted Strings
            int i = 0;
            while (buffer[i] != '\0')
            {
                if (buffer[i] == '"' && (cell.empty() || cell.back() != '\\'))
                {
                    inQuotes = !inQuotes;
                }
                else if (buffer[i] == ',' && !inQuotes)
                {
                    //columns.push_back(cell);
                    counter++;
                    if (counter - columnIndex == 1) {
                        break;
                    }
                    cell.clear();
                }
                else
                {
                    cell = cell + buffer[i];
                }
                i++;
            }
            int j = 0;
            while (cell[j] != '\0')
            {
                if (cell[j] == ' ' || cell[j] == '/' || cell[j] == '\\' || cell[j] == '-') {
                    cell[j] = '_';
                }
                j++;
            }

            String folder2 = folder;
            String folderPath = folder2 + "/";
            String fileName = cell + ".txt";
            String selectedCell = folderPath + fileName;
            // cout << "file name: " << selectedCell << endl;

            root = insertIterative(root, selectedCell, "");
            ofstream file("Root.txt");
            file << root;
            file.close();
            // cout << lineNumber << endl;
             ///////////////////////////////////////////////////////
            ofstream outFile(selectedCell.constCharPointer(), ios::app);
            if (outFile)
            {
                outFile << lineNumber << ":" << buffer << endl;
                outFile.close();
            }
            else
            {
                cout << "Error: Could not create file for " << selectedCell << endl;
            }
        }
        file.close();


    }


};

//#pragma once
//#include <iostream>
//#include <fstream>
//#include<filesystem>
//#include"String.h"
//
//using namespace std;
//namespace fs = std::filesystem;
class RBTree
{
public:
    String root;
    String caller;
    bool check_field(String field)
    {
        const char* fixedFields[5] = { "key", "parent", "left", "right", "color" };

        // Iterate through each fixed field
        for (int i = 0; i < 5; i++) {
            bool isMatch = true;

            // Compare characters manually
            for (int j = 0; field[j] != '\0' || fixedFields[i][j] != '\0'; j++) {
                // If characters mismatch or lengths mismatch
                if (field[j] != fixedFields[i][j]) {
                    isMatch = false;
                    break;
                }
            }

            // If a match is found
            if (isMatch) {
                return true;
            }
        }

        return false; // No match found
    }



    // Function to append or update specific fields in a file
    void appendToFile(String filePath, String field, String value, bool overwrite = false) {
        if (field == "root")
        {
            //ofstream outFile(filePath, ios::trunc); // Always overwrite the root file
            //outFile << "root:" << value << endl;
            //outFile.close();
            root = value;
            return;
        }

        bool check = check_field(field);
        if (!check)
        {
            ofstream file(filePath.constCharPointer(), ios::app); // Open in append mode
            file << value << endl;            // Append the line data
            file.close();
            return;
        }

        String tempFilePath = "temp.txt";// Temporary file
        ofstream tempFile(tempFilePath.constCharPointer());        // Open temp file for writing
        ifstream file(filePath.constCharPointer());                // Open original file for reading

        if (!file.is_open() || !tempFile.is_open())
        {

            return;
        }
        String line;
        bool fieldUpdated = false; // Track if the field has been updated

        // Process each line in the original file
        while (caller.getline(file, line)) {

            int pos = -1;
            for (int i = 0; i < line.stringSize(); ++i) {
                if (line[i] == ':') {
                    pos = i;
                    break;
                }
            }
            if (pos != -1) {
                String key = line.substr(0, pos);
                String val = line.substr(pos + 1);
                if (key == field) {
                    tempFile << key << ":" << value << endl;
                }
                else {
                    tempFile << line << endl;
                }

            }
        }

        file.close();
        tempFile.close();

        fs::remove(filePath.constCharPointer());
        fs::rename(tempFilePath.constCharPointer(), filePath.constCharPointer());

    }

    // Function to read a specific field from a file
    String readFromFile(String filePath, String field)
    {
        if (filePath == "NULL") {
            return "NULL";
        }
        if (field == "root") {
            return root;
        }

        ifstream file(filePath.constCharPointer());
        String line;
        while (caller.getline(file, line)) {
            int pos = -1;
            for (int i = 0; i < line.stringSize(); ++i) {
                if (line[i] == ':') {
                    pos = i;
                    break;
                }
            }
            if (pos != -1) {
                String key = line.substr(0, pos);
                String value = line.substr(pos + 1);
                if (key == field) {
                    file.close();
                    return value;
                }
            }
        }
        file.close();
        return "NULL";
    }


    // Function to update the root's color to black
    void updateRoot(String rootPath)
    {
        appendToFile(rootPath, "color", "BLACK", true);
    }

    void leftRotate(String xPath)
    {
        String yPath = readFromFile(xPath, "right");

        // Update x->right = y->left
        appendToFile(xPath, "right", readFromFile(yPath, "left"), true);
        if (!(readFromFile(yPath, "left") == "NULL")) {
            appendToFile(readFromFile(yPath, "left"), "parent", xPath, true);
        }

        // Update y->parent = x->parent
        appendToFile(yPath, "parent", readFromFile(xPath, "parent"), true);
        if (readFromFile(xPath, "parent") == "NULL") {
            appendToFile("ROOT", "root", yPath, true);
        }
        else if (xPath == readFromFile(readFromFile(xPath, "parent"), "left")) {
            appendToFile(readFromFile(xPath, "parent"), "left", yPath, true);
        }
        else {
            appendToFile(readFromFile(xPath, "parent"), "right", yPath, true);
        }

        // Update y->left = x
        appendToFile(yPath, "left", xPath, true);
        appendToFile(xPath, "parent", yPath, true);
    }

    void rightRotate(String yPath)
    {
        String xPath = readFromFile(yPath, "left");

        // Update y->left = x->right
        appendToFile(yPath, "left", readFromFile(xPath, "right"), true);
        if (!(readFromFile(xPath, "right") == "NULL")) {
            appendToFile(readFromFile(xPath, "right"), "parent", yPath, true);
        }

        // Update x->parent = y->parent
        appendToFile(xPath, "parent", readFromFile(yPath, "parent"), true);
        if (readFromFile(yPath, "parent") == "NULL") {
            appendToFile("ROOT", "root", xPath, true);
        }
        else if (yPath == readFromFile(readFromFile(yPath, "parent"), "left")) {
            appendToFile(readFromFile(yPath, "parent"), "left", xPath, true);
        }
        else {
            appendToFile(readFromFile(yPath, "parent"), "right", xPath, true);
        }

        // Update x->right = y
        appendToFile(xPath, "right", yPath, true);
        appendToFile(yPath, "parent", xPath, true);
    }


    // Function to balance the tree after insertion
    void balanceTree(String nodePath)
    {
        String currentNode = nodePath;

        while (readFromFile(readFromFile(currentNode, "parent"), "color") == "RED") {
            String parentNode = readFromFile(currentNode, "parent");
            String grandParentNode = readFromFile(parentNode, "parent");

            if (parentNode == readFromFile(grandParentNode, "left")) {
                String uncleNode = readFromFile(grandParentNode, "right");

                // Case 1: Uncle is red
                if (!(uncleNode == "NULL") && readFromFile(uncleNode, "color") == "RED") {
                    appendToFile(parentNode, "color", "BLACK", true);
                    appendToFile(uncleNode, "color", "BLACK", true);
                    appendToFile(grandParentNode, "color", "RED", true);
                    currentNode = grandParentNode;

                }
                else {
                    // Case 2: Node is right child
                    if (currentNode == readFromFile(parentNode, "right")) {
                        currentNode = parentNode;
                        leftRotate(currentNode);
                        parentNode = readFromFile(currentNode, "parent");
                    }

                    // Case 3: Node is left child
                    appendToFile(parentNode, "color", "BLACK", true);
                    appendToFile(grandParentNode, "color", "RED", true);
                    rightRotate(grandParentNode);
                }
            }
            else {
                String uncleNode = readFromFile(grandParentNode, "left");

                // Case 1: Uncle is red
                if (!(uncleNode == "NULL") && readFromFile(uncleNode, "color") == "RED") {
                    appendToFile(parentNode, "color", "BLACK", true);
                    appendToFile(uncleNode, "color", "BLACK", true);
                    appendToFile(grandParentNode, "color", "RED", true);
                    currentNode = grandParentNode;
                }
                else {
                    // Case 2: Node is left child
                    if (currentNode == readFromFile(parentNode, "left")) {
                        currentNode = parentNode;
                        rightRotate(currentNode);
                        parentNode = readFromFile(currentNode, "parent");
                    }

                    // Case 3: Node is right child
                    appendToFile(parentNode, "color", "BLACK", true);
                    appendToFile(grandParentNode, "color", "RED", true);
                    leftRotate(grandParentNode);
                }
            }
        }

        appendToFile(readFromFile("ROOT", "root"), "color", "BLACK", true);
    }

    void insertNodeWithLineData(String& key, String folderPath, String& lineData)
    {
        String newNodePath = folderPath;

        // Check if the file already exists

        ifstream checkFile(newNodePath.constCharPointer());
        bool isNewFile = !checkFile.good(); // Check if the file exists
        checkFile.close();

        if (!isNewFile) {
            //// If the file exists, append only the line data and retain the previous data
            //ofstream file(newNodePath.constCharPointer(), ios::app); // Open in append mode
            //file << lineData << endl;            // Append the line data
            //file.close();
            return; // Exit the function as we don't need to process further
        }

        // If the file is new, create it with a consistent format
        ofstream file(newNodePath.constCharPointer(), ios::trunc);
        file << "key:" << key << endl;
        file << "parent:NULL" << endl;
        file << "left:NULL" << endl;
        file << "right:NULL" << endl;
        file << "color:RED" << endl;
        // file << lineData << endl; // Add the line data for the first time
        file.close();

        // Handle tree logic (check root and update parent/child relationships)
        if (readFromFile("ROOT", "root") == "NULL")
        {
            appendToFile("ROOT", "root", newNodePath, true); // Set root path
            updateRoot(newNodePath);                        // Update root color to BLACK
            return;
        }

        // Standard BST insertion logic
        String currentPath = readFromFile("ROOT", "root");
        String parentPath = "NULL";

        while (!(currentPath == "NULL")) {
            String currentKey = readFromFile(currentPath, "key");
            parentPath = currentPath;

            if (key < currentKey)
            {
                currentPath = readFromFile(currentPath, "left");
            }
            else
            {
                currentPath = readFromFile(currentPath, "right");
            }
        }

        // Update parent information in the new node
        appendToFile(newNodePath, "parent", parentPath, true);

        String c_key = readFromFile(parentPath, "key");

        // Update the parent's left or right child
        if (key < c_key)
        {
            appendToFile(parentPath, "left", newNodePath, true);
        }
        else
        {
            appendToFile(parentPath, "right", newNodePath, true);
        }

        // Balance the tree after insertion
        balanceTree(newNodePath);
    }




    void processColumn(int columnIndex, String filename, String folderPath)
    {
        ifstream file(filename.constCharPointer());
        if (!file) {
            cout << "Error: File could not be opened!" << endl;
            return;
        }
        String strObj;
        int bufferSize = 500;
        char buffer[500]{ '\0' };
        strObj.mygetline(file, buffer, bufferSize);
        //String folder;

        int counter = 0;


        String line;
        int lineNumber = 1;


        while (strObj.mygetline(file, buffer, bufferSize))
        {

            String cell;
            bool inQuotes = false;
            counter = 0;
            // Parse the line manually, handling quoted Strings
            int i = 0;
            while (buffer[i] != '\0')
            {
                if (buffer[i] == '"' && (cell.empty() || cell.back() != '\\'))
                {
                    inQuotes = !inQuotes;
                }
                else if (buffer[i] == ',' && !inQuotes)
                {
                    //columns.push_back(cell);
                    counter++;
                    if (counter - columnIndex == 1) {
                        break;
                    }
                    cell.clear();
                }
                else
                {
                    cell = cell + buffer[i];
                }
                i++;
            }
            int j = 0;
            while (cell[j] != '\0')
            {
                if (cell[j] == ' ' || cell[j] == '/' || cell[j] == '\\' || cell[j] == '-') {
                    cell[j] = '_';
                }
                j++;
            }
            String dat = to_String(lineNumber);
            String data1 = dat + ":";
            String data = data1 + buffer;
            String folder2 = folderPath + '/';
            String key2 = cell + ".txt";
            String key = folder2 + key2;
            insertNodeWithLineData(cell, key, data);
            ofstream outFile(key.constCharPointer(), ios::app);
            if (outFile)
            {
                outFile << lineNumber << ":" << buffer << endl;
                outFile.close();
            }
            else
            {
                cout << "Error: Could not create file for " << key << endl;
            }

            lineNumber++; // Move to the next line

        }
        file.close();
    }



    String BSTreplace(String nodePath)
    {
        String leftChild = readFromFile(nodePath, "left");

        if (!(leftChild == "NULL"))
        {
            String temp = leftChild;
            while (!(readFromFile(temp, "right") == "NULL")) {
                temp = readFromFile(temp, "right");
            }
            return temp;
        }

        return readFromFile(nodePath, "right");
    }


    // Function to fix double black violation
    void fixDoubleBlack(String nodePath)
    {
        if (nodePath == readFromFile("ROOT", "root")) return;


        String parent = readFromFile(nodePath, "parent");
        String sibling = (nodePath == readFromFile(parent, "left")) ? readFromFile(parent, "right") : readFromFile(parent, "left");

        if (sibling == "NULL")
        {
            // No sibling, push double black up
           // nodePath = parent;
            fixDoubleBlack(parent);
        }
        else
        {
            if (readFromFile(sibling, "color") == "RED")
            {
                // Sibling is red
                appendToFile(sibling, "color", "BLACK", true);
                appendToFile(parent, "color", "RED", true);
                if (sibling == readFromFile(parent, "left"))
                {
                    rightRotate(parent);
                }
                else
                {
                    leftRotate(parent);
                }
                fixDoubleBlack(nodePath);
            }


            else
            {
                // Sibling is black
                if (readFromFile(readFromFile(sibling, "left"), "color") == "RED"
                    ||
                    readFromFile(readFromFile(sibling, "right"), "color") == "RED")
                {
                    // At least one red child
                    if (!(readFromFile(sibling, "left") == "NULL") && readFromFile(readFromFile(sibling, "left"), "color") == "RED")
                    {
                        if (sibling == readFromFile(parent, "left"))
                        {
                            appendToFile(readFromFile(sibling, "left"), "color", readFromFile(sibling, "color"), true);
                            appendToFile(sibling, "color", readFromFile(parent, "color"), true);

                            rightRotate(parent);
                        }
                        else
                        {
                            appendToFile(readFromFile(sibling, "left"), "color", readFromFile(parent, "color"), true);
                            rightRotate(sibling);
                            leftRotate(parent);

                        }

                    }
                    else
                    {

                        if (sibling == readFromFile(parent, "left"))
                        {
                            appendToFile(readFromFile(sibling, "right"), "color", readFromFile(parent, "color"), true);
                            // appendToFile(sibling, "color", readFromFile(parent, "color"), true);
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else
                        {
                            appendToFile(readFromFile(sibling, "right"), "color", readFromFile(sibling, "color"), true);
                            appendToFile(sibling, "color", readFromFile(parent, "color"), true);

                            leftRotate(parent);
                        }
                    }
                    appendToFile(parent, "color", "BLACK", true);

                }
                else
                {
                    // Sibling has two black children
                    appendToFile(sibling, "color", "RED", true);
                    if (readFromFile(parent, "color") == "BLACK")
                    {
                        fixDoubleBlack(parent);
                    }
                    else
                    {
                        appendToFile(parent, "color", "BLACK", true);

                    }
                }
            }
        }

    }


    void deleteNode(String nodePath)
    {

        String replacement = BSTreplace(nodePath);
        String parent = readFromFile(nodePath, "parent");
        bool uvBlack = ((replacement == "NULL" || readFromFile(replacement, "color") == "BLACK") && readFromFile(nodePath, "color") == "BLACK");

        if (replacement == "NULL")
        {

            if (nodePath == readFromFile("ROOT", "root"))
            {
                appendToFile("ROOT", "root", "NULL", true);
            }
            else
            {

                if (uvBlack)
                {
                    fixDoubleBlack(nodePath);
                }
                else
                {
                    String sibling = (nodePath == readFromFile(parent, "left")) ? readFromFile(parent, "right") : readFromFile(parent, "left");

                    if (!(sibling == "NULL"))
                    {
                        appendToFile(sibling, "color", "RED", true);
                    }
                }
                // Update parent pointers
                if (nodePath == readFromFile(parent, "left")) {
                    appendToFile(parent, "left", "NULL", true);
                }
                else
                {
                    appendToFile(parent, "right", "NULL", true);
                }
            }
            fs::remove(nodePath.constCharPointer()); // Delete the node file
            return; // Exit loop after handling leaf
        }

        if (readFromFile(nodePath, "left") == "NULL" || readFromFile(nodePath, "right") == "NULL")
        {
            // Node has one child
            if (nodePath == readFromFile("ROOT", "root"))
            {
                appendToFile(replacement, "parent", "NULL", true); // Replacement becomes the root
                appendToFile("ROOT", "root", replacement, true);
                appendToFile(replacement, "color", "BLACK", true); // Root must always be black
            }
            else
            {
                // Update parent's child pointer to replacement
                if (nodePath == readFromFile(parent, "left"))
                {
                    appendToFile(parent, "left", replacement, true);
                }
                else
                {
                    appendToFile(parent, "right", replacement, true);
                }
                fs::remove(nodePath.constCharPointer()); // Delete the node file
                appendToFile(replacement, "parent", parent, true);

                if (uvBlack)
                {
                    fixDoubleBlack(replacement); // Fix double black if required
                }
                else
                {
                    appendToFile(replacement, "color", "BLACK", true); // Recolor replacement
                }
            }

            return;
        }
        String par = readFromFile(nodePath, "parent");
        String lef = readFromFile(nodePath, "left");
        String rig = readFromFile(nodePath, "right");
        String col = readFromFile(nodePath, "color");

        /*   if (lef == replacement)
           {
               lef = "NULL";
           }*/

        ofstream write_in(nodePath.constCharPointer());
        ifstream write_from(replacement.constCharPointer());
        String data1;
        int linenum = 1;
        while (caller.getline(write_from, data1))
        {
            if (linenum == 1)
            {
                write_in << data1 << endl;
            }
            if (linenum == 2)
            {
                write_in << "parent:" << par << endl;
            }
            if (linenum == 3)
            {
                write_in << "left:" << lef << endl;
            }
            if (linenum == 4)
            {
                write_in << "right:" << rig << endl;
            }
            if (linenum == 5)
            {
                write_in << "color:" << col << endl;
            }
            if (linenum > 5)
                write_in << data1 << endl;
            linenum++;
        }

        write_in.close();
        write_from.close();

        deleteNode(replacement);
        fs::rename(nodePath.constCharPointer(), replacement.constCharPointer());
        String prt = readFromFile(replacement, "parent");
        if (prt == "NULL") {
            appendToFile("ROOT", "root", replacement, true);
        }

        if (nodePath == readFromFile(prt, "left"))
        {
            appendToFile(prt, "left", replacement, true);
        }
        else if (nodePath == readFromFile(prt, "right"))
        {
            appendToFile(prt, "right", replacement, true);
        }
        String lc = readFromFile(replacement, "left");
        String rc = readFromFile(replacement, "right");
        appendToFile(lc, "parent", replacement.constCharPointer(), true);
        appendToFile(rc, "parent", replacement.constCharPointer(), true);


    }

    void displayIterativeS() {
        stack<pair<String, int>> nodeStack; // Stack holds the node path and its depth
        String current = root;
        int depth = 0;

        while (!nodeStack.empty() || !(current == "NULL")) {
            while (!(current == "NULL")) {
                nodeStack.push({ current, depth });
                depth++;
                current = readFromFile(current, "right"); // Move to left child
            }

            auto [node, level] = nodeStack.top(); // Unpack node and depth
            nodeStack.pop();

            // Print the key with indentation based on depth
            for (int i = 0; i < level; ++i) cout << "    "; // 4 spaces for each level
            cout << readFromFile(node, "key") << " (" << readFromFile(node, "color") << ")" << endl; // Display key and color

            current = readFromFile(node, "left"); // Move to right child
            depth = level + 1;
        }
    }


};

//#pragma once
//#include <fstream>
//#include<filesystem>
//#include"String.h"
//#include <iostream>
//using namespace std;
//namespace fs = std::filesystem;





long long int getHash(String& val)
{
    int i = 0;
    unsigned long long product = 1;

    // Iterate through the string until '\0'
    while (val[i] != '\0') {
        product += static_cast<unsigned int>(val[i]); // Multiply ASCII values of characters
        i++;
    }
    product %= 1000;



    return product;
}

String processFiles(stack<String>& fileStack, String folderPath)
{
    int level = 0;

    while (fileStack.size() > 1) {

        stack<String> nextStack;

        // Print the current stack for debugging
        stack<String> tempStack = fileStack; // Copy to print and keep original intact
        while (!tempStack.empty()) {
            //   std::cout << tempStack.top() << " ";
            tempStack.pop();
        }


        // Process pairs of files
        while (fileStack.size() > 1) {
            // Pop two files from the stack
            String file1 = fileStack.top();
            fileStack.pop();
            String file2 = fileStack.top();
            fileStack.pop();

            // Create a new file by concatenating their names
            String newFileName = file1 + file2;
            newFileName = newFileName + ".txt";
            String newFilePath = folderPath + '/';
            newFilePath = newFilePath + newFileName;
            String open = folderPath + '/';
            open = open + file1;
            open = open + ".txt";
            // Open files for reading and writing
            //folderPath + '/' + file1 + ".txt"
            std::ifstream inputFile1(open.constCharPointer());
            open = "";
            open = folderPath + '/';
            open = open + file2;
            open = open + ".txt";
            std::ifstream inputFile2(open.constCharPointer());
            std::ofstream newFile(newFilePath.constCharPointer());

            if (inputFile1 && inputFile2 && newFile) {
                String temp = file1;
                // Concatenate contents of the two files into the new file
                newFile << '\n';
                newFile << temp + ".txt" << '\n';
                temp = file2;
                newFile << temp + ".txt" << '\n';
            }
            else {
                std::cerr << "Error opening files for processing: "
                    << file1 << " or " << file2 << "\n";
                return "";
            }

            inputFile1.close();
            inputFile2.close();
            newFile.close();

            // Open children files in append mode and write the parent path
            open = folderPath + '/' + file1 + ".txt";
            std::ofstream child1(open.constCharPointer(), std::ofstream::app);
            if (!child1.is_open()) {
                std::cerr << "COULD NOT OPEN CHILD 1: " << file1 << ".txt" << std::endl;
            }
            else {
                child1 << file2 << '\n';
                child1 << newFileName << '\n';
            }
            child1.close();
            open = folderPath + "/" + file2 + ".txt";
            std::ofstream child2(open.constCharPointer(), std::ofstream::app);
            if (!child2.is_open()) {
                std::cerr << "COULD NOT OPEN CHILD 2: " << file2 << ".txt" << std::endl;
            }
            else {
                child2 << file1 << '\n';
                child2 << newFileName << '\n';
            }
            child2.close();

            // Push the new file name onto the next stack
            nextStack.push(file1 + file2);
        }

        // If there's one file left unpaired, move it to the next level
        if (!fileStack.empty()) {
            nextStack.push(fileStack.top());
            fileStack.pop();
        }

        // Replace the current stack with the next stack
        fileStack = nextStack;
        ++level;
    }

    // Print the final result
    if (!fileStack.empty())
    {
        //  std::cout << "Final file: " << fileStack.top() << std::endl;
        return fileStack.top();
    }
    return "";

}
void makeMerkleTree(String folderName)
{
    if (!fs::exists("merkleTree")) {
        fs::create_directory("merkleTree");
    }
    int counter = 0;
    stack<String> merkleLeafStack;
    try {
        // Check if the directory exists
        if (fs::exists(folderName.constCharPointer()) && fs::is_directory(folderName.constCharPointer())) {
            std::cout << "Files in directory \"" << folderName.constCharPointer() << "\":\n";

            // Iterate through the directory and process files
            for (const auto& entry : fs::directory_iterator(folderName.constCharPointer())) {
                if (fs::is_regular_file(entry.path())) {
                    // Use the full path for opening the file
                    std::ifstream inputFile(entry.path());

                    if (!inputFile.is_open()) {
                        std::cerr << "Could not open file: " << entry.path() << '\n';
                        continue; // Skip this file and move to the next
                    }
                    else {
                        // cout << "OPENED " << entry.path() << endl;
                    }

                    char buffer[1024] = { '\0' };
                    String caller;
                    while (counter < 5) {
                        caller.mygetline(inputFile, buffer, 1024);
                        counter++;
                    }
                    String s;
                    while (caller.mygetline(inputFile, buffer, 1024)) {
                        int i = 0;
                        while (buffer[i] != '\0') {
                            //std::cout << buffer[i];

                            s = s + buffer[i];
                            i++;
                        }
                        // cout << s;
                        // std::cout << '\n';
                    }


                    int temp = getHash(s);
                    //  cout << "TEMP " << temp << endl;
                    String hashFileName = "merkleTree/";
                    hashFileName = hashFileName + to_String(temp);
                    String hashFileTempName = to_String(temp);
                    hashFileName = hashFileName + ".txt";

                    ofstream outFile(hashFileName.constCharPointer());

                    outFile << entry.path().string() << '\n';
                    outFile << '\n' << '\n';


                    inputFile.close(); // Close the file after processing
                    outFile.close();
                    ofstream currentFile(entry.path().string(), ofstream::app);
                    if (!currentFile.is_open()) {
                        // cout << "COULDNT OPEN " << entry.path().string() << endl;
                    }
                    currentFile << hashFileName << '\n';
                    //   cout << "HASH FILE NAME " << hashFileName << endl;
                    merkleLeafStack.push(hashFileTempName);
                }
                // cout << "--------------------------------------------" << endl;
                counter = 0;
            }
        }
        else {
            std::cerr << "The specified path is not a directory or does not exist.\n";
        }
    }

    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    processFiles(merkleLeafStack, "merkleTree");
}


