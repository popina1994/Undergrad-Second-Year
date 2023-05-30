#ifndef _ERROR_H_
#define _ERROR_H_

#include <exception>
#include <string>

using namespace std;

class ErrorReading : public exception{
    int line, pos;
    string fileName;
public:
    ErrorReading(int _line, int _pos, const string& _fileName);
    void WritePosition() const;
};

class Bad_Number : public ErrorReading {
public:
    
	Bad_Number(int _line, int _pos, const string& _fileName);
    const char* what() const  override;
};

class Bad_Sign : public ErrorReading {
public:
	Bad_Sign(int _line, int _pos, const string& _fileName);
    const char* what() const  override;
};

class Bad_Assigment : public ErrorReading {
public:
	Bad_Assigment(int _line, int _pos, const string& _fileName);
    const char* what() const  override;
};

class Bad_File_Name : public exception {
    string fileName;
public:
    Bad_File_Name(const string&);
    const char* what() const  override;
    const string& GetFileName() const;
};

#endif // _Error_h_
