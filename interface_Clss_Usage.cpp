#include<string_view>
#include<cmath>
class FileErrorLog;
class IErrorLog
{
public:
	virtual bool openLog( std::string_view fileName ) = 0;
	virtual bool closeLog() = 0;
	virtual bool writeError( std::string_view erroMessage ) = 0;
	//make a virtual destructor in case we delete an IErrorLog pointer,
	// so the proper derived destructor is called
	//destructor is not made pure virtual
	virtual ~IErrorLog(){ }
};

// Write some generic code that uses IErrorLog
// If reefernce to IErrorLog used in function code 
// any derived class with its specific implemntation can be passed now.
// Derived classs should conform to IError log interface
double mySqrt( double value, IErrorLog& log )
{
	if (value < 0.0)
	{
		log.writeError( "tried to take square root of value less than 0" );
		return 0.0;
	}
	else
	{
		return std::sqrt( value );
	}
}
int main()
{
	return 0;
}