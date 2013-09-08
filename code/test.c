/**
 @file test.c
 @author James Gregson (james.gregson@gmail.com)
 @brief test suite for the expression parser, see expression_parser.h for more information and license terms.
 */
#include<math.h>
#include<stdio.h>
#include<string.h>

#include"expression_parser.h"

/**
 @brief macro for checking the correctness of the parser. parses the input expression in C using the preprocessor and with the parser using preprocessor stringification and compares the results. if the results are within PARSER_BOOLEAN_EQUALITY_THRESHOLD of each other, the result is assumed correct.  note that the expression argument must be parsable in C from the calling scope, i.e. if variables and functions are used, they must be defined where this macro is called from or a compile error will result.
*/
#define parser_check( result, expr ) { \
                                       double c_value, p_value; \
                                       c_value = (double) expr; \
                                       p_value = parse_expression( #expr ); \
                                       printf("  '%s'\n", #expr ); \
                                       if( fabs( c_value - p_value ) > PARSER_BOOLEAN_EQUALITY_THRESHOLD ){ \
                                           *result = PARSER_FALSE; \
										   printf("         C: %f\n", c_value ); \
                                           printf("    Parsed: %f\n", p_value ); \
                                       } \
                                     }
/**
 @brief macro for checking the correctness of the parser. parses the input expression in C using the preprocessor and with the parser using preprocessor stringification and compares the results. if the results are within PARSER_BOOLEAN_EQUALITY_THRESHOLD of each other, the result is assumed correct.  note that the expression argument must be parsable in C from the calling scope, i.e. if variables and functions are used, they must be defined where this macro is called from or a compile error will result.
 */
#define parser_check_with_callbacks( result, expr, user_vars, user_fncs, user_data ) { \
                                                                                       double c_value, p_value; \
                                                                                       c_value = (double) expr; \
                                                                                       p_value = parse_expression_with_callbacks( #expr, user_vars, user_fncs, user_data ); \
                                                                                       printf("  '%s'\n", #expr ); \
																					   if( fabs( c_value - p_value ) > PARSER_BOOLEAN_EQUALITY_THRESHOLD ){ \
                                                                                           *result = PARSER_FALSE; \
																					       printf("         C: %f\n", c_value ); \
                                                                                           printf("    Parsed: %f\n", p_value ); \
																					  } \
																					}
/**
 @brief macro for checking the correctness of the parser. parses the input expression in C using the preprocessor and with the parser using preprocessor stringification and compares the results. if the results are within PARSER_BOOLEAN_EQUALITY_THRESHOLD of each other, the result is assumed correct.  note that the expression argument must be parsable in C from the calling scope, i.e. if variables and functions are used, they must be defined where this macro is called from or a compile error will result.
 */
#define parser_check_boolean( result, expr ) { \
                                               double c_value, p_value; \
                                               c_value = (double) expr; \
                                               p_value = parse_expression( #expr ); \
	                                           printf("  '%s'\n", #expr ); \
                                               if( fabs( c_value - p_value ) > PARSER_BOOLEAN_EQUALITY_THRESHOLD ){ \
                                                   *result = PARSER_FALSE; \
                                                   printf("         C: %f\n", c_value ); \
                                                   printf("    Parsed: %f\n", p_value ); \
											   } \
                                             }
/**
 @brief test that the boolean unary not operation works correctly.
*/
void run_boolean_not_tests(){
	int result = 1;
	printf("Testing boolean not:\n");
	parser_check_boolean( &result, 0.0 );
	parser_check_boolean( &result, 2.0 );
	parser_check_boolean( &result, !0.0 );
	parser_check_boolean( &result, !3.0 );
	printf( "%s\n\n", result ? "passed" : "failed" );
}

/**
 @brief test that the boolean comparison operations, i.e. ==, <, >=, etc. work correctly
*/
void run_boolean_comparison_tests(){
	int result = 1;
	printf("Testing boolean comparisons:\n");
	parser_check_boolean( &result, 2.0 == 3.0 );
	parser_check_boolean( &result, 2.0 == 2.0 );
	parser_check_boolean( &result, 2.0 != 2.0 );
	parser_check_boolean( &result, 2.0 != 3.0 );
	parser_check_boolean( &result, 2.0 <  3.0 );
	parser_check_boolean( &result, 3.0 <  2.0 );
	parser_check_boolean( &result, 2.0 >  3.0 );
	parser_check_boolean( &result, 3.0 >  2.0 ); 
	parser_check_boolean( &result, 2.0 <= 2.0 );
	parser_check_boolean( &result, 2.0 <= 3.0 );
	parser_check_boolean( &result, 3.0 <= 2.0 );
	parser_check_boolean( &result, 2.0 >= 2.0 );
	parser_check_boolean( &result, 2.0 >= 3.0 );
	parser_check_boolean( &result, 3.0 >= 2.0 );
	printf( "%s\n\n", result ? "passed" : "failed" );
}

/**
 @brief test that the boolean logical tests, i.e. && and ||, work correctly
*/
void run_boolean_logical_tests(){
	int result = 1;
	printf("Testing boolean logical operations:\n" );
	parser_check_boolean( &result, 2.0 && 3.0 );
	parser_check_boolean( &result, 2.0 && 0.0 );
	parser_check_boolean( &result, 0.0 && 3.0 );
	parser_check_boolean( &result, 0.0 && 0.0 );
	parser_check_boolean( &result, 2.0 || 3.0 );
	parser_check_boolean( &result, 2.0 || 0.0 );
	parser_check_boolean( &result, 0.0 || 3.0 );
	parser_check_boolean( &result, 0.0 || 0.0 );
	printf( "%s\n\n", result ? "passed" : "failed" );
}

/**
 @brief test that expressions with compound boolean expression work correctly and match the same expression as computed in C.  note that many compilers (e.g. llvm and gcc) may give compiler warnings about these expressions due to cascaded || and && operations.
*/
void run_boolean_compound_tests(){
	int result = 1;
	printf("Testing boolean expressions:\n" );
	parser_check_boolean( &result, 2.0 > 3.0 && 2.0 == 2.0 );
	parser_check_boolean( &result, 3.0 > 2.0 && 2.0 == 2.0 );
	parser_check_boolean( &result, 3.0 > 2.0 || 1.0 == 0.0 );
	parser_check_boolean( &result, 3.0 < 2.0 || 1.0 != 0.0 );
	parser_check_boolean( &result, 3.0 < 2.0 || 1.0 == 1.0 && 2.0 <= 3.0 );
	parser_check_boolean( &result, 3.0 < 2.0 || 1.0 != 1.0 && 2.0 <= 3.0 || 0.0 );
	parser_check_boolean( &result, 3.0 < 2.0 || 1.0 != 1.0 && 2.0 <= 3.0 || 1.0 );
	parser_check( &result, (3.0<2.0)*5.0 + (3.0>=2.0)*6.0 );
	parser_check( &result, (3.0>=2.0)*5.0 + (3.0<2.0)*6.0 );
	
	parser_check_boolean( &result, !(2.0 > 3.0 && 2.0 == 2.0) );
	parser_check_boolean( &result, 3.0 > 2.0 && !(2.0 == 2.0) );
	parser_check_boolean( &result, 3.0 > !2.0 || 1.0 == 0.0 );
	parser_check_boolean( &result, 3.0 < 2.0 || 1.0 != !0.0 );
	parser_check_boolean( &result, !(3.0 < 2.0) || 1.0 == 1.0 && 2.0 <= 3.0 );
	parser_check_boolean( &result, 3.0 < 2.0 || 1.0 != 1.0 && 2.0 <= 3.0 || ! 0.0 );
	parser_check_boolean( &result, 3.0 < 2.0 || 1.0 != 1.0 && 2.0 <= 3.0 || !1.0 );
	parser_check( &result, (3.0<2.0)*5.0 + (3.0>=2.0)*6.0 );
	parser_check( &result, (3.0>=2.0)*5.0 + (3.0<2.0)*6.0 );
	parser_check( &result, (1.0)*5.0 + (!1.0)*6.0 );
	parser_check( &result, (!1.0)*5.0 + (1.0)*6.0 );
	printf( "%s\n\n", result ? "passed" : "failed" );	
}

/** 
    @brief test function for malformed inputs, to be sure that they throw errors appropriately. Note that there are lots of examples of counter-intuitive expressions that evaluate 'correctly', e.g. 1 + + -3 = -2.0 due to the binding of unary + and - operators.
*/
void run_bad_input_tests(){
    parse_expression( "1 **/ 34 " ); // from Brian Palmer, 04-06-2013
    parse_expression( "6.0 (6.0)" );
}

/**
 @brief implementation of a user-defined function for testing
*/
double user_func_0(){
	return 10.0;
}

/**
 @brief implementation of a user-defined function for testing
*/
double user_func_1( double x ){
	return fabs(x);
}

/**
 @brief implementation of a user-defined funtion for testing
*/
double user_func_2( double x, double y ){
	return sqrt( x*x + y*y );
}

/**
 @brief implementation of a user-defined function for testing
*/
double _user_func_3( double x, double y, double z ){
	return sqrt( x*x + y*y + z*z );
}

/**
 @brief implementation of a user-defined function for testing
*/
double user_func_4( double x, double y, double z, double q ){
	return sqrt( x*x + y*y + z*z + q*q );
}

/**
 @brief user-function callback for the parser. reads name of function to be called and checks the number of arguments before calling the appropriate function. returns true if function was called successfully, false otherwise.
 @param[in] user_data pointer to (arbitrary) user-defined data that may be needed by the callback functions. not used for this example.
 @param[in] name name of the function to execute
 @param[in] num_args the number of arguments that were supplied in the function call
 @param[out] value the return argument, which should contain the functions evaluated value on return if the evaluation was successful.
 @return true if the function was evaluated successfully, false otherwise
*/
int user_fnc_cb( void *user_data, const char *name, const int num_args, const double *args, double *value ){
	if( strcmp( name, "user_func_0" ) == 0 && num_args == 0 ){
		*value = user_func_0();
		return PARSER_TRUE;
	} else if( strcmp( name, "user_func_1" ) == 0 && num_args == 1 ){
		*value = user_func_1( args[0] );
		return PARSER_TRUE;
	} else if( strcmp( name, "user_func_2" ) == 0 && num_args == 2 ){
		*value = user_func_2( args[0], args[1] );
		return PARSER_TRUE;
	} else if( strcmp( name, "_user_func_3" ) == 0 && num_args == 3 ){
		*value = _user_func_3( args[0], args[1], args[2] );
		return PARSER_TRUE;
	}
	return PARSER_FALSE;
}

/**
 @brief user-variable callback for the parser. reads the name of the variable and sets the appropriate value in the return argument. returns true if the variable exists and the return value set, false otherwise.
 @param[in] user_data pointer to (arbitrary) user-defined state data that may be needed by the callback functions
 @param[in] name name of the variable to lookup the value for
 @param[out] value output argument that should contain the variable value on return, if the evaluation is successful.
 @return true if the variable exists and the return argument was successfully set, false otherwise
*/
int user_var_cb( void *user_data, const char *name, double *value ){
	if( strcmp( name, "a" ) == 0 ){
		*value = 1.0;
		return PARSER_TRUE;
	} else if( strcmp( name, "b0" ) == 0 ){
		*value = 2.0;
		return PARSER_TRUE;
	} else if( strcmp( name, "_variable_6__" ) == 0 ){
		*value = 5.0;
		return PARSER_TRUE;
	}
	return PARSER_FALSE;
}

/**
 @brief test function for the user-defined functions and variables
*/
void test_user_functions_and_variables(){
	double a = 1.0;
	double b0 = 2.0;
	double b12 = 6.0;
	double _variable_6__ = 5.0;	
	int result = 1;
	
	// tests of user-defined variables in isolation
	result = PARSER_TRUE;
	printf("Testing user-defined variables:\n");
	parser_check_with_callbacks( &result, a,             user_var_cb, NULL, NULL );
	parser_check_with_callbacks( &result, b0,            user_var_cb, NULL, NULL );
	parser_check_with_callbacks( &result, _variable_6__, user_var_cb, NULL, NULL );
	printf( "%s\n\n", result ? "passed" : "failed" );		
		
	// tests of user-defined functions in isolation
	result = PARSER_TRUE;
	printf("Testing user-defined functions:\n");
	parser_check_with_callbacks( &result, user_func_0(),                                  NULL, user_fnc_cb, NULL );
	parser_check_with_callbacks( &result, user_func_1( user_func_0() ),                   NULL, user_fnc_cb, NULL );
	parser_check_with_callbacks( &result, user_func_2( user_func_1(2.0), user_func_0() ), NULL, user_fnc_cb, NULL );
	parser_check_with_callbacks( &result, _user_func_3( 1.0, 2.0, 3.0 ),                  NULL, user_fnc_cb, NULL ); 
	printf( "%s\n\n", result ? "passed" : "failed" );		
	
	// now try mixing and matching
	result = PARSER_TRUE;
	printf("Testing user-defined functions AND variables:\n");
	parser_check_with_callbacks( &result, _user_func_3( user_func_0(), user_func_2( a, b0 ), user_func_1( _variable_6__ ) ), user_var_cb, user_fnc_cb, NULL );
	printf( "%s\n\n", result ? "passed" : "failed" );		
	
	// the following test failure behavior when functions/variables are referenced, but no callbacks
	// are provided, or when those callbacks do not handle the called function/variable properly, e.g.
	// when the functions are not defined, when the number of arguments is wrong, etc.
	printf("\n\nTesting function error behaviour, this SHOULD fail because no function callback is set!\n" );
	parser_check_with_callbacks( &result, user_func_0(), NULL, NULL, NULL );
	
	printf("\n\nTesting function error behaviour, this SHOULD fail because the function callback does not define the function!\n" );
	parser_check_with_callbacks( &result, user_func_4(1.0, 2.0, 3.0, 4.0), NULL, user_fnc_cb, NULL );
	
	printf( "\n\nTesting variable error behaviour, this SHOULD fail because no variable callback is set!\n" );
	parser_check_with_callbacks( &result, a, NULL, NULL, NULL );
	
	printf( "\n\nTesting variable error behaviour, this SHOULD fail because the variable callback does not define the variable!\n" );
	parser_check_with_callbacks( &result, b12, NULL, NULL, NULL );

    // check that some bad inputs fail
    printf("\n\nTesting malformed inputs, these SHOULD fail because they are invalid expression strings!\n");
    run_bad_input_tests();
    
	printf("\n\n");
}

/**
 @brief runs a series of tests, printing the results to stdout.
*/
int main( void ){
    
    run_bad_input_tests();
    
	run_boolean_not_tests();
	run_boolean_comparison_tests();
	run_boolean_logical_tests();
	run_boolean_compound_tests();
	test_user_functions_and_variables();	
	return 0;
}