/**
 @file example.c
 @author James Gregson (james.gregson@gmail.com)
 @brief example usage of the expression parser, see expression_parser.h for license details. demonstrates using the variable and function callbacks, as well as direct initialization of the data structures and customized error handling.
*/
#include<stdio.h>
#include<string.h>
#include"expression_parser.h"

/**
 @brief user-defined variable callback function. see expression_parser.h for more details.
 @param[in] user_data pointer to any user-defined state data that is required, none in this case
 @param[in] name name of the variable to look up the value of
 @param[out] value output point to double that holds the variable value on completion
 @return true if the variable exists and the output value was set, false otherwise
*/
int variable_callback( void *user_data, const char *name, double *value ){
	// look up the variables by name
	if( strcmp( name, "var0" ) == 0 ){
		// set return value, return true
		*value = 0.0;
		return PARSER_TRUE;
	} else if( strcmp( name, "var1" ) == 0 ){
		// set return value, return true
		*value = 1.0;
		return PARSER_TRUE;
	} else if( strcmp( name, "var2" ) == 0 ){
		// set return value, return true
		*value = 2.0;
		return PARSER_TRUE;
	} else if( strcmp( name, "var3" ) == 0 ){
		// set return value, return true
		*value = 3.0;
		return PARSER_TRUE;
	}
	// failed to find variable, return false
	return PARSER_FALSE;
}

/**
 @brief user-defined function callback. see expression_parser.h for more details.
 @param[in] user_data input pointer to any user-defined state variables needed.  in this case, this pointer is the maximum number of arguments allowed to the functions (as a contrived example usage).
 @param[in] name name of the function to evaluate
 @param[in] num_args number of arguments that were parsed in the function call
 @param[in] args list of parsed arguments
 @param[out] value output evaluated result of the function call
 @return true if the function exists and was evaluated successfully with the result stored in value, false otherwise.
*/
int function_callback( void *user_data, const char *name, const int num_args, const double *args, double *value ){
	int i, max_args;
	double tmp;
	
	// example to show the user-data parameter, sets the maximum number of
	// arguments allowed for the following functions from the user-data function
	max_args = *((int*)user_data);
	
	if( strcmp( name, "max_value") == 0 && num_args >= 2 && num_args <= max_args ){
		// example 'maximum' function, returns the largest of the arguments, this and 
		// the min_value function implementation below allow arbitrary number of arguments
		tmp = args[0];
		for( i=1; i<num_args; i++ ){
			tmp = args[i] >= tmp ? args[i] : tmp;
		}
		// set return value and return true
		*value = tmp;
		return PARSER_TRUE;
	} else if( strcmp( name, "min_value" ) == 0 && num_args >= 2 && num_args <= max_args ){
		// example 'minimum' function, returns the smallest of the arguments
		tmp = args[0];
		for( i=1; i<num_args; i++ ){
			tmp = args[i] <= tmp ? args[i] : tmp;
		}
		// set return value and return true
		*value = tmp;
		return PARSER_TRUE;
	} 
	
	// failed to evaluate function, return false
	return PARSER_FALSE;
}

int main( void ){
	double value;
	int num_arguments = 3;
	const char *expr0 = "max_value( var0, var1, var2 )";
	const char *expr1 = "max_value( var0, var1, var2, var3 )";
	const char *expr2 = "2^3 + 2.0 - 8.0";
	const char *expr3 = "5.0*( max_value( var0, max_value( var1, var2 ) )/2 + min_value( var1, var2, var3 )/2 )";
	parser_data pd;
	
	// should succeed, and print results. the success or failure of the expression parser
	// can be tested by testing the return value for equality with itself, which always 
	// fails for nan (Not a Number), provided strict floating point behaviour is followed
	// by the compiler.
	value = parse_expression_with_callbacks( expr0, variable_callback, function_callback, &num_arguments );
	if( value == value )
		printf( "%s = %f\n\n", expr0, value );
	else 
		printf( "\n" );
	
	// should fail, since too many arguments are being passed
	num_arguments = 2;
	value = parse_expression_with_callbacks( expr0, variable_callback, function_callback, &num_arguments );
	if( value == value )
		printf( "%s = %f\n\n", expr0, value );
	else
		printf( "\n" );
	
	// increase the number of arguments, and now pass 4, should succeed
	num_arguments = 4;
	value = parse_expression_with_callbacks( expr1, variable_callback, function_callback, &num_arguments );
	if( value == value )
		printf( "%s = %f\n\n", expr1, value );
	else
		printf( "\n" );

	// parse and expression with no variables or functions
	value = parse_expression( expr2 );
	if( value == value )
		printf( "%s = %f\n\n", expr2, value );
	else
		printf("\n");
	
	// parse expr3, initializing the data structures from scratch (no malloc/free)
	// and handling the errors directly from the calling code, rather than allowing the 
	// parser to print errors directly.
	num_arguments = 2;
	parser_data_init( &pd, expr3, variable_callback, function_callback, &num_arguments );
	value = parser_parse( &pd );
	if( pd.error == NULL )
		printf( "%s = %f\n\n", expr3, value );
	else 
		printf( "CUSTOM ERROR HANDLING: %s\n\n", pd.error );
	
	// repeat the previous test, with the number of arguments increased to avoid
	// the error
	num_arguments = 3;
	parser_data_init( &pd, expr3, variable_callback, function_callback, &num_arguments );
	value = parser_parse( &pd );
	if( pd.error == NULL )
		printf( "%s = %f\n\n", expr3, value );
	else 
		printf( "CUSTOM ERROR HANDLING: %s\n", pd.error );
	
	
	return 0;
}