#include<stdio.h>// for puts
#include<Windows.h>
#include<excpt.h>

int filter( unsigned int code, struct _EXCEPTION_POINTERS* ep )
{
	puts( " in filter." );
	if (code == EXCEPTION_ACCESS_VIOLATION)
	{
		puts( " caught AV as expected." );
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		puts( "didn't catch AV, unexpected. " );
			return EXCEPTION_CONTINUE_SEARCH;
	};
}



int main()
{
	int* p = 0x0000000; // pointer to NULL
	puts( "hello" );
	__try
	{
		puts( "in try" );
		__try
		{
			puts( " in try " );
			*p = 13; // causes an excess violation
		}
		__finally
		{
			puts( "in finally. termination: " );
			puts( AbnormalTermination() ? "\tabnormal" : "\tnormal" );
		}
	}
	__except (filter( GetExceptionCode(), GetExceptionInformation() ))
	{
		puts( "in except" );
	}
	puts( "world" );
	return 0;
}