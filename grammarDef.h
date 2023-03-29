/*
Group No. : 42
ID: 2020A7PS1214P	Name: Darshan Abhaykumar
ID: 2020A7PS0970P	Name: Debjit Kar
ID:2020A7PS0986P	Name: Nidhish Parekh
*/
#ifndef GRAMMARDEF_H
#define GRAMMARDEF_H
#include "lexerDef.h"

#define RULE_COUNT 20//
#define NT_COUNT 79//

typedef enum {
	program,
	moduleDeclarations,
    moduleDeclaration,
	otherModules,
	driverModule,
	module,
	ret,
	input_plist,
	input_plist2, 
	output_plist,
	output_plist2,
	dataType,
	arr_range,
    arr_index,
	num_or_id,
	type,
	moduleDef,
	statements,
	statement,
	ioStmt,
    boolVal,
	print_var,
	which_ID,
	for_range,
    for_index,
    for_index2,
    for_sign,  
	iterativeStmt,
	default_stmt,
	value,
	caseStmts,
	caseStmts2,
	conditionalStmt,
	declareStmt,
	relationalOp,
	logicalOp,
	Term8,
	AnyTerm,
	Term7,
	abExpr,
	uni_op,
	new_NT,
	U,
	high_op,
	low_op,
	factor,
	factor2,
	exprIndex,
    exprIndex2,
	arrExpr,
	arrExpr2,
	arrTerm,
	arrTerm2,
	arrFactor,
	term2,
	term,
	arithmeticExpr2,
	arithmeticExpr,
	expression,
	idList2,
	idList,
    con_var,
	optional,
	moduleReuseStmt,
	lvalueARRStmt,
	lvalueIDStmt,
	sign,
	whichStmt,
	assignmentStmt,
	simpleStmt,
	actual_para_list,
	actual_para_list2,
	Term9,
	K
} NT;

#endif

