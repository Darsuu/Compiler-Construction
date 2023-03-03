#include "grammarDef.h"
#include "linkedlist.h"
#include "lexerDef.h"
#include <stdlib.h>
#include <stdio.h>

RULE** table;

void printNT(NT term){
	switch(term){
	case 0: printf("<program>"); break; 
	case 1: printf("<moduleDeclarations>"); break; 
	case 2: printf("<moduleDeclaration>"); break; 
	case 3: printf("<otherModules>"); break; 
    case 4: printf("<driverModule>"); break;         
    case 5: printf("<module>"); break; 
    case 6: printf("<ret>"); break; 
    case 7: printf("<input_plist>"); break; 
    case 8: printf("<input_plist2>"); break; 
    case 9: printf("<output_plist>"); break; 
    case 10: printf("<output_plist2>"); break; 
    case 11: printf("<dataType>"); break; 
    case 12: printf("<arr_range>"); break;         
    case 13: printf("<arr_index>"); break; 
    case 14: printf("<num_or_id>"); break; 
    case 15: printf("<type>"); break; 
    case 16: printf("<moduleDef>"); break; 
    case 17: printf("<statements>"); break; 
    case 18: printf("<statement>"); break; 
    case 19: printf("<ioStmt>"); break; 
    case 20: printf("<boolVal>"); break;         
    case 21: printf("<print_var>"); break; 
    case 22: printf("<which_ID>"); break; 
    case 23: printf("<for_range>"); break; 
    case 24: printf("<for_index>"); break; 
    case 25: printf("<for_index2>"); break; 
    case 26: printf("<for_sign, >"); break; 
    case 27: printf("<iterativeStmt>"); break; 
    case 28: printf("<default_stmt>"); break;         
    case 29: printf("<value>"); break; 
    case 30: printf("<caseStmts>"); break; 
    case 31: printf("<caseStmts2>"); break; 
    case 32: printf("<conditionalStmt>"); break; 
    case 33: printf("<declareStmt>"); break; 
    case 34: printf("<relationalOp>"); break; 
    case 35: printf("<logicalOp>"); break; 
    case 36: printf("<Term8>"); break; 
    case 37: printf("<AnyTerm>"); break; 
    case 38: printf("<Term7>"); break; 
    case 39: printf("<abExpr>"); break; 
    case 40: printf("<uni_op>"); break;         
    case 41: printf("<new_NT>"); break; 
    case 42: printf("<U>"); break; 
    case 43: printf("<high_op>"); break; 
    case 44: printf("<low_op>"); break; 
    case 45: printf("<factor>"); break; 
    case 46: printf("<factor2>"); break; 
    case 47: printf("<exprIndex>"); break; 
    case 48: printf("<exprIndex2>"); break; 
    case 49: printf("<arrExpr>"); break; 
    case 50: printf("<arrExpr2>"); break; 
    case 51: printf("<arrTerm>"); break; 
    case 52: printf("<arrTerm2>"); break; 
    case 53: printf("<arrFactor>"); break;         
    case 54: printf("<term2>"); break; 
    case 55: printf("<term>"); break; 
    case 56: printf("<arithmeticExpr2>"); break; 
    case 57: printf("<arithmeticExpr>"); break; 
    case 58: printf("<expression>"); break; 
    case 59: printf("<idList2>"); break; 
    case 60: printf("<idList>"); break; 
    case 61: printf("<con_var>"); break; 
    case 62: printf("<optional>"); break; 
    case 63: printf("<moduleReuseStmt>"); break; 
    case 64: printf("<lvalueARRStmt>"); break; 
    case 65: printf("<lvalueIDStmt>"); break; 
    case 66: printf("<sign>"); break; 
    case 67: printf("<whichStmt>"); break; 
    case 68: printf("<assignmentStmt>"); break; 
    case 69: printf("<simpleStmt>"); break; 
    
	default: printf("<unknown>"); break; 
	}
}

void buildGrammar(){
    table = (RULE**) malloc(NT_COUNT*sizeof(RULE*));
    for(int i = 0; i<NT_COUNT; i++)
    {
        table[i] = (RULE*) malloc(RULE_COUNT*sizeof(RULE));
    }
    // NT lhs;
    NT rhs;
    token terminal;

    table[program][0] = createNewRule(program,0);
    addTermToRule(table[program][0],terminal,moduleDeclarations,1);
    addTermToRule(table[program][0],terminal,otherModules,1);
    addTermToRule(table[program][0],terminal,driverModule,1);
    addTermToRule(table[program][0],terminal,otherModules,1);

    table[moduleDeclarations][0] = createNewRule(moduleDeclarations,1);
    addTermToRule(table[moduleDeclarations][0],terminal,moduleDeclaration,1);
    addTermToRule(table[moduleDeclarations][0],terminal,moduleDeclarations,1);

    table[moduleDeclarations][1] = createNewRule(moduleDeclarations,2);
    addTermToRule(table[moduleDeclarations][1],EPSILON,rhs,0); 
    
    table[moduleDeclaration][0] = createNewRule(moduleDeclaration,3);
    addTermToRule(table[moduleDeclaration][0],DECLARE,rhs,0);
    addTermToRule(table[moduleDeclaration][0],MODULE,rhs,0);
    addTermToRule(table[moduleDeclaration][0],ID,rhs,0);
    addTermToRule(table[moduleDeclaration][0],SEMICOL,rhs,0);

    table[otherModules][0] = createNewRule(otherModules,4);
    addTermToRule(table[otherModules][0],terminal,module,1);
    addTermToRule(table[otherModules][0],terminal,otherModules,1);

    table[otherModules][1] = createNewRule(otherModules,5);
    addTermToRule(table[otherModules][1],EPSILON,rhs,0); 


    table[driverModule][0] = createNewRule(driverModule,6);
    addTermToRule(table[driverModule][0],DRIVERDEF,rhs,0);
    addTermToRule(table[driverModule][0],DRIVER,rhs,0);
    addTermToRule(table[driverModule][0],PROGRAM,rhs,0);
    addTermToRule(table[driverModule][0],DRIVERENDDEF,rhs,0);
    addTermToRule(table[driverModule][0],terminal,moduleDef,1);

    table[module][0] = createNewRule(module,7);
    addTermToRule(table[module][0],DEF,rhs,0);
    addTermToRule(table[module][0],MODULE,rhs,0);
    addTermToRule(table[module][0],ID,rhs,0);
    addTermToRule(table[module][0],ENDDEF,rhs,0);
    addTermToRule(table[module][0],TAKES,rhs,0);
    addTermToRule(table[module][0],INPUT,rhs,0);
    addTermToRule(table[module][0],SQBO,rhs,0);
    addTermToRule(table[module][0],terminal,input_plist,1);
    addTermToRule(table[module][0],SQBC,rhs,0);
    addTermToRule(table[module][0],SEMICOL,rhs,0);
    addTermToRule(table[module][0],terminal,ret,1);
    addTermToRule(table[module][0],terminal,moduleDef,1);

    table[ret][0] = createNewRule(ret,8);
    addTermToRule(table[ret][0],RETURNS,rhs,0);
    addTermToRule(table[ret][0],SQBO,rhs,0);
    addTermToRule(table[ret][0],terminal,output_plist,1);
    addTermToRule(table[ret][0],SQBC,rhs,0);
    addTermToRule(table[ret][0],SEMICOL,rhs,0);

    table[ret][1] = createNewRule(ret,9);
    addTermToRule(table[ret][1],EPSILON,rhs,0); 


    table[input_plist][0] = createNewRule(input_plist,10);
    addTermToRule(table[input_plist][0],ID,rhs,0);
    addTermToRule(table[input_plist][0],COLON,rhs,0);
    addTermToRule(table[input_plist][0],terminal,dataType,1);
    addTermToRule(table[input_plist][0],terminal,input_plist2,1);

    table[input_plist2][0] = createNewRule(input_plist2,11);
    addTermToRule(table[input_plist2][0],COMMA,rhs,0);
    addTermToRule(table[input_plist2][0],ID,rhs,0);
    addTermToRule(table[input_plist2][0],COLON,rhs,0);
    addTermToRule(table[input_plist2][0],terminal,dataType,1);
    addTermToRule(table[input_plist2][0],terminal,input_plist2,1);

    table[input_plist2][1] = createNewRule(input_plist2,12);
        addTermToRule(table[input_plist2][1],EPSILON,rhs,0); 


    table[output_plist][0] = createNewRule(output_plist,13);
    addTermToRule(table[output_plist][0],ID,rhs,0);
    addTermToRule(table[output_plist][0],COLON,rhs,0);
    addTermToRule(table[output_plist][0],terminal,type,1);
    addTermToRule(table[output_plist][0],terminal,output_plist2,1);

    table[output_plist2][0] = createNewRule(output_plist2,14);
    addTermToRule(table[output_plist2][0],COMMA,rhs,0);
    addTermToRule(table[output_plist2][0],ID,rhs,0);
    addTermToRule(table[output_plist2][0],COLON,rhs,0);
    addTermToRule(table[output_plist2][0],terminal,type,1);
    addTermToRule(table[output_plist2][0],terminal,output_plist2,1);

    table[output_plist2][1] = createNewRule(output_plist2,15);
        addTermToRule(table[output_plist2][1],EPSILON,rhs,0); 

    
    table[dataType][0] = createNewRule(dataType,16);
    addTermToRule(table[dataType][0],INTEGER,rhs,0);

    table[dataType][1] = createNewRule(dataType,17);
    addTermToRule(table[dataType][1],REAL,rhs,0);

    table[dataType][2] = createNewRule(dataType,18);
    addTermToRule(table[dataType][2],BOOLEAN,rhs,0);

    table[dataType][3] = createNewRule(dataType,19);
    addTermToRule(table[dataType][3],ARRAY,rhs,0);
    addTermToRule(table[dataType][3],SQBO,rhs,0);
    addTermToRule(table[dataType][3],terminal,arr_range,1);
    addTermToRule(table[dataType][3],SQBC,rhs,0);
    addTermToRule(table[dataType][3],OF,rhs,0);
    addTermToRule(table[dataType][3],terminal,type,1);

    table[arr_range][0] = createNewRule(arr_range,20);
    addTermToRule(table[arr_range][0],terminal,arr_index,1);
    addTermToRule(table[arr_range][0],RANGEOP,rhs,0);
    addTermToRule(table[arr_range][0],terminal,arr_index,1);

    table[type][0] = createNewRule(type,21);
    addTermToRule(table[type][0],INTEGER,rhs,0);

    table[type][1] = createNewRule(type,22);
    addTermToRule(table[type][1],REAL,rhs,0);

    table[type][2] = createNewRule(type,23);
    addTermToRule(table[type][2],BOOLEAN,rhs,0);

    table[moduleDef][0] = createNewRule(moduleDef,24);
    addTermToRule(table[moduleDef][0],START,rhs,0);
    addTermToRule(table[moduleDef][0],terminal,statements,1);
    addTermToRule(table[moduleDef][0],END,rhs,0);

    table[statements][0] = createNewRule(statements,25);
    addTermToRule(table[statements][0],terminal,statement,1);    
    addTermToRule(table[statements][0],terminal,statements,1);

    table[statements][1] = createNewRule(statements,26);
        addTermToRule(table[statements][1],EPSILON,rhs,0); 


    table[statement][0] = createNewRule(statement,27);
    addTermToRule(table[statement][0],terminal,ioStmt,1); 

    table[statement][1] = createNewRule(statement,28);
    addTermToRule(table[statement][1],terminal,simpleStmt,1); 

    table[statement][2] = createNewRule(statement,29);
    addTermToRule(table[statement][2],terminal,declareStmt,1); 

    table[statement][3] = createNewRule(statement,30);
    addTermToRule(table[statement][3],terminal,conditionalStmt,1); 

    table[statement][4] = createNewRule(statement,31);
    addTermToRule(table[statement][4],terminal,iterativeStmt,1); 

    table[ioStmt][0] = createNewRule(ioStmt,32);
    addTermToRule(table[ioStmt][0],GET_VALUE,rhs,0);
    addTermToRule(table[ioStmt][0],BO,rhs,0);
    addTermToRule(table[ioStmt][0],ID,rhs,0);
    addTermToRule(table[ioStmt][0],BC,rhs,0);
    addTermToRule(table[ioStmt][0],SEMICOL,rhs,0);

    table[ioStmt][1] = createNewRule(ioStmt,33);
    addTermToRule(table[ioStmt][1],PRINT,rhs,0);
    addTermToRule(table[ioStmt][1],BO,rhs,0);
    addTermToRule(table[ioStmt][1],terminal,print_var,1);  
    addTermToRule(table[ioStmt][1],BC,rhs,0);
    addTermToRule(table[ioStmt][1],SEMICOL,rhs,0);

    table[boolVal][0] = createNewRule(boolVal,34);
    addTermToRule(table[boolVal][0],TRUE,rhs,0);

    table[boolVal][1] = createNewRule(boolVal,35);
    addTermToRule(table[boolVal][1],FALSE,rhs,0);
    
    table[print_var][0] = createNewRule(print_var,36);
    addTermToRule(table[print_var][0],ID,rhs,0);
    addTermToRule(table[print_var][0],terminal,which_ID,1); 

    table[print_var][1] = createNewRule(print_var,37);
    addTermToRule(table[print_var][1],NUM,rhs,0);

    table[print_var][2] = createNewRule(print_var,38);
    addTermToRule(table[print_var][2],RNUM,rhs,0);
 
    table[print_var][2] = createNewRule(print_var,39);
    addTermToRule(table[print_var][2],terminal,boolVal,1);

    table[which_ID][0] = createNewRule(which_ID,40);
    addTermToRule(table[which_ID][0],SQBO,rhs,0);
    addTermToRule(table[which_ID][0],terminal,num_or_id,1);
    addTermToRule(table[which_ID][0],SQBC,rhs,0);

    table[which_ID][1] = createNewRule(which_ID,41);
        addTermToRule(table[which_ID][1],EPSILON,rhs,0); 


    table[simpleStmt][0] = createNewRule(simpleStmt,42);
    addTermToRule(table[simpleStmt][0],terminal,assignmentStmt,1);

    table[simpleStmt][1] = createNewRule(simpleStmt,43);
    addTermToRule(table[simpleStmt][1],terminal,moduleReuseStmt,1);

    table[assignmentStmt][0] = createNewRule(assignmentStmt,44);
    addTermToRule(table[assignmentStmt][0],ID,rhs,0);
    addTermToRule(table[assignmentStmt][0],terminal,whichStmt,1);
    
    table[whichStmt][0] = createNewRule(whichStmt,45);
    addTermToRule(table[whichStmt][0],terminal,lvalueIDStmt,1);

    table[whichStmt][1] = createNewRule(whichStmt,46);
    addTermToRule(table[whichStmt][1],terminal,lvalueARRStmt,1);

    table[lvalueIDStmt][0] = createNewRule(lvalueIDStmt,47);
    addTermToRule(table[lvalueIDStmt][0],ASSIGNOP,rhs,0);
    addTermToRule(table[lvalueIDStmt][0],terminal,expression,1);
    addTermToRule(table[lvalueIDStmt][0],SEMICOL,rhs,0);

    table[lvalueARRStmt][0] = createNewRule(lvalueARRStmt,48);
    addTermToRule(table[lvalueARRStmt][0],SQBO,rhs,0);
    addTermToRule(table[lvalueARRStmt][0],terminal,exprIndex,1);
    addTermToRule(table[lvalueARRStmt][0],SQBC,rhs,0);
    addTermToRule(table[lvalueARRStmt][0],ASSIGNOP,rhs,0);
    addTermToRule(table[lvalueARRStmt][0],terminal,expression,1);
    addTermToRule(table[lvalueARRStmt][0],SEMICOL,rhs,0);

    table[arr_index][0] = createNewRule(arr_index,49);
    addTermToRule(table[arr_index][0],terminal,sign,1);
    addTermToRule(table[arr_index][0],terminal,num_or_id,1);

    table[num_or_id][0] = createNewRule(num_or_id,50);
    addTermToRule(table[num_or_id][0],NUM,rhs,0);

    table[num_or_id][1] = createNewRule(num_or_id,51);
    addTermToRule(table[num_or_id][1],ID,rhs,0);
    
    table[sign][0] = createNewRule(sign,52);
    addTermToRule(table[sign][0],PLUS,rhs,0);

    table[sign][1] = createNewRule(sign,53);
    addTermToRule(table[sign][1],MINUS,rhs,0);

    table[sign][2] = createNewRule(sign,54);
        addTermToRule(table[sign][2],EPSILON,rhs,0); 
 

    table[moduleReuseStmt][0] = createNewRule(moduleReuseStmt,55);
    addTermToRule(table[moduleReuseStmt][0],terminal,optional,1);
    addTermToRule(table[moduleReuseStmt][0],USE,rhs,0);
    addTermToRule(table[moduleReuseStmt][0],MODULE,rhs,0);
    addTermToRule(table[moduleReuseStmt][0],ID,rhs,0);
    addTermToRule(table[moduleReuseStmt][0],WITH,rhs,0);
    addTermToRule(table[moduleReuseStmt][0],PARAMETERS,rhs,0);
    addTermToRule(table[moduleReuseStmt][0],terminal,factor,1);
    addTermToRule(table[moduleReuseStmt][0],SEMICOL,rhs,0);

    table[factor][0] = createNewRule(factor,56);
    addTermToRule(table[factor][0],NUM,rhs,0);

    table[factor][1] = createNewRule(factor,57);
    addTermToRule(table[factor][1],RNUM,rhs,0);

    table[factor][2] = createNewRule(factor,58);
    addTermToRule(table[factor][2],terminal,boolVal,1);

    table[factor][3] = createNewRule(factor,59);
    addTermToRule(table[factor][3],ID,rhs,0);
    addTermToRule(table[factor][3],terminal,factor2,1);

    table[factor][4] = createNewRule(factor,84);
    addTermToRule(table[factor][4],BO,rhs,0);
    addTermToRule(table[factor][4],terminal,abExpr,1);
    addTermToRule(table[factor][4],BC,rhs,0);

    table[factor2][0] = createNewRule(factor2,60);
    addTermToRule(table[factor2][0],SQBO,rhs,0);
    addTermToRule(table[factor2][0],terminal,exprIndex,1);
    addTermToRule(table[factor2][0],SQBC,rhs,0);

    table[factor2][1] = createNewRule(factor2,61);
        addTermToRule(table[factor2][1],EPSILON,rhs,0); 


    table[optional][0] = createNewRule(optional,62);
    addTermToRule(table[optional][0],SQBO,rhs,0);
    addTermToRule(table[optional][0],terminal,idList,1);
    addTermToRule(table[optional][0],SQBC,rhs,0);
    addTermToRule(table[optional][0],ASSIGNOP,rhs,0);

    table[optional][1] = createNewRule(optional,63);
        addTermToRule(table[optional][1],EPSILON,rhs,0); 


    table[idList][0] = createNewRule(idList,64);
    addTermToRule(table[idList][0],ID,rhs,0);
    addTermToRule(table[idList][0],terminal,idList2,1);

    table[idList2][0] = createNewRule(idList2,65);
    addTermToRule(table[idList2][0],COMMA,rhs,0);
    addTermToRule(table[idList2][0],ID,rhs,0);
    addTermToRule(table[idList2][0],terminal,idList2,1);

    table[idList2][1] = createNewRule(idList2,66);
        addTermToRule(table[idList2][1],EPSILON,rhs,0); 


    table[expression][0] = createNewRule(expression,67);
    addTermToRule(table[expression][0],terminal,abExpr,1);

    table[expression][1] = createNewRule(expression,68);
    addTermToRule(table[expression][1],terminal,U,1);

    table[U][0] = createNewRule(U,69);
    addTermToRule(table[U][0],terminal,uni_op,1);
    addTermToRule(table[U][0],terminal,new_NT,1);

    table[new_NT][0] = createNewRule(new_NT,70);
    addTermToRule(table[new_NT][0],BO,rhs,0);
    addTermToRule(table[new_NT][0],terminal,arithmeticExpr,1);
    addTermToRule(table[new_NT][0],BC,rhs,0);

    table[new_NT][1] = createNewRule(new_NT,71);
    addTermToRule(table[new_NT][1],terminal,con_var,1);

    table[uni_op][0] = createNewRule(uni_op,72);
    addTermToRule(table[uni_op][0],PLUS,rhs,0);

    table[uni_op][1] = createNewRule(uni_op,73);
    addTermToRule(table[uni_op][1],MINUS,rhs,0);

    table[abExpr][0] = createNewRule(abExpr,74);
    addTermToRule(table[abExpr][0],terminal,AnyTerm,1);
    addTermToRule(table[abExpr][0],terminal,Term7,1);

    table[Term7][0] = createNewRule(Term7,75);
    addTermToRule(table[Term7][0],terminal,logicalOp,1);
    addTermToRule(table[Term7][0],terminal,AnyTerm,1);
    addTermToRule(table[Term7][0],terminal,Term7,1);

    table[Term7][1] = createNewRule(Term7,76);
        addTermToRule(table[Term7][1],EPSILON,rhs,0); 


    table[AnyTerm][0] = createNewRule(AnyTerm,77);
    addTermToRule(table[AnyTerm][0],terminal,arithmeticExpr,1);
    addTermToRule(table[AnyTerm][0],terminal,Term8,1);

    table[AnyTerm][1] = createNewRule(AnyTerm,78);
    addTermToRule(table[AnyTerm][1],terminal,boolVal,1);

    table[Term8][0] = createNewRule(Term8,79);
    addTermToRule(table[Term8][0],terminal,relationalOp,1);
    addTermToRule(table[Term8][0],terminal,arithmeticExpr,1);

    table[Term8][1] = createNewRule(Term8,80);
        addTermToRule(table[Term8][1],EPSILON,rhs,0); 

    
    table[con_var][0] = createNewRule(con_var,81);
    addTermToRule(table[con_var][0],ID,rhs,0);

    table[con_var][1] = createNewRule(con_var,82);
    addTermToRule(table[con_var][1],NUM,rhs,0);

    table[con_var][2] = createNewRule(con_var,83);
    addTermToRule(table[con_var][2],RNUM,rhs,0);

    table[arithmeticExpr][0] = createNewRule(arithmeticExpr,85);
    addTermToRule(table[arithmeticExpr][0],terminal,term,1);
    addTermToRule(table[arithmeticExpr][0],terminal,arithmeticExpr2,1);

    table[arithmeticExpr2][0] = createNewRule(arithmeticExpr2,86);
    addTermToRule(table[arithmeticExpr2][0],terminal,low_op,1);
    addTermToRule(table[arithmeticExpr2][0],terminal,term,1);
    addTermToRule(table[arithmeticExpr2][0],terminal,arithmeticExpr2,1);

    table[arithmeticExpr2][1] = createNewRule(arithmeticExpr2,87);
        addTermToRule(table[arithmeticExpr2][1],EPSILON,rhs,0); 


    table[term][0] = createNewRule(term,88);
    addTermToRule(table[term][0],terminal,factor,1);
    addTermToRule(table[term][0],terminal,term2,1);

    table[term2][0] = createNewRule(term2,89);
    addTermToRule(table[term2][0],terminal,high_op,1);
    addTermToRule(table[term2][0],terminal,factor,1);
    addTermToRule(table[term2][0],terminal,term2,1);

    table[term2][1] = createNewRule(term2,90);
        addTermToRule(table[term2][1],EPSILON,rhs,0); 


    table[exprIndex][0] = createNewRule(exprIndex,91);
    addTermToRule(table[exprIndex][0],terminal,sign,1);
    addTermToRule(table[exprIndex][0],terminal,exprIndex2,1);

    table[exprIndex][1] = createNewRule(exprIndex,92);
    addTermToRule(table[exprIndex][1],terminal,arrExpr,1);

    table[exprIndex2][0] = createNewRule(exprIndex2,93);
    addTermToRule(table[exprIndex2][0],terminal,num_or_id,1);

    table[exprIndex2][1] = createNewRule(exprIndex2,94);
    addTermToRule(table[exprIndex2][1],BO,rhs,0);
    addTermToRule(table[exprIndex2][1],terminal,arrExpr,1);
    addTermToRule(table[exprIndex2][1],BC,rhs,0);

    table[arrExpr][0] = createNewRule(arrExpr,95);
    addTermToRule(table[arrExpr][0],terminal,arrTerm,1);
    addTermToRule(table[arrExpr][0],terminal,arrExpr2,1);

    table[arrExpr2][0] = createNewRule(arrExpr2,96);
    addTermToRule(table[arrExpr2][0],terminal,low_op,1);
    addTermToRule(table[arrExpr2][0],terminal,arrTerm,1);
    addTermToRule(table[arrExpr2][0],terminal,arrExpr2,1);

    table[arrExpr2][1] = createNewRule(arrExpr2,97);
        addTermToRule(table[arrExpr2][1],EPSILON,rhs,0); 


    table[arrTerm][0] = createNewRule(arrTerm,98);
    addTermToRule(table[arrTerm][0],terminal,arrFactor,1);
    addTermToRule(table[arrTerm][0],terminal,arrTerm2,1);

    table[arrTerm2][0] = createNewRule(arrTerm2,99);
    addTermToRule(table[arrTerm2][0],terminal,high_op,1);
    addTermToRule(table[arrTerm2][0],terminal,arrFactor,1);
    addTermToRule(table[arrTerm2][0],terminal,arrTerm2,1);

    table[arrTerm2][1] = createNewRule(arrTerm2,100);
        addTermToRule(table[arrTerm2][1],EPSILON,rhs,0); 


    table[arrFactor][0] = createNewRule(arrFactor,101);
    addTermToRule(table[arrFactor][0],ID,rhs,0);

    table[arrFactor][1] = createNewRule(arrFactor,102);
    addTermToRule(table[arrFactor][1],NUM,rhs,0);

    table[arrFactor][2] = createNewRule(arrFactor,103);
    addTermToRule(table[arrFactor][2],terminal,boolVal,1);

    table[arrFactor][3] = createNewRule(arrFactor,104);
    addTermToRule(table[arrFactor][3],BO,rhs,0);
    addTermToRule(table[arrFactor][3],terminal,arrExpr,1);
    addTermToRule(table[arrFactor][3],BC,rhs,0);

    table[low_op][0] = createNewRule(low_op,105);
    addTermToRule(table[low_op][0],PLUS,rhs,0);

    table[low_op][1] = createNewRule(low_op,106);
    addTermToRule(table[low_op][1],MINUS,rhs,0);

    table[high_op][0] = createNewRule(high_op,107);
    addTermToRule(table[high_op][0],MUL,rhs,0);

    table[high_op][1] = createNewRule(high_op,108);
    addTermToRule(table[high_op][1],DIV,rhs,0);

    table[logicalOp][0] = createNewRule(logicalOp,109);
    addTermToRule(table[logicalOp][0],AND,rhs,0);

    table[logicalOp][1] = createNewRule(logicalOp,110);
    addTermToRule(table[logicalOp][1],OR,rhs,0);

    table[relationalOp][0] = createNewRule(relationalOp,111);
    addTermToRule(table[relationalOp][0],LT,rhs,0);

    table[relationalOp][1] = createNewRule(relationalOp,112);
    addTermToRule(table[relationalOp][1],LE,rhs,0);

    table[relationalOp][2] = createNewRule(relationalOp,113);
    addTermToRule(table[relationalOp][2],GT,rhs,0);

    table[relationalOp][3] = createNewRule(relationalOp,114);
    addTermToRule(table[relationalOp][3],GE,rhs,0);

    table[relationalOp][4] = createNewRule(relationalOp,115);
    addTermToRule(table[relationalOp][4],EQ,rhs,0);

    table[relationalOp][5] = createNewRule(relationalOp,116);
    addTermToRule(table[relationalOp][5],NE,rhs,0);

    table[declareStmt][0] = createNewRule(declareStmt,117);
    addTermToRule(table[declareStmt][0],DECLARE,rhs,0);
    addTermToRule(table[declareStmt][0],terminal,idList,1);
    addTermToRule(table[declareStmt][0],COLON,rhs,0);
    addTermToRule(table[declareStmt][0],terminal,dataType,1);
    addTermToRule(table[declareStmt][0],SEMICOL,rhs,0);

    table[conditionalStmt][0] = createNewRule(conditionalStmt,118);
    addTermToRule(table[conditionalStmt][0],SWITCH,rhs,0);
    addTermToRule(table[conditionalStmt][0],BO,rhs,0);
    addTermToRule(table[conditionalStmt][0],ID,rhs,0);
    addTermToRule(table[conditionalStmt][0],BC,rhs,0);
    addTermToRule(table[conditionalStmt][0],START,rhs,0);
    addTermToRule(table[conditionalStmt][0],terminal,caseStmts,1);
    addTermToRule(table[conditionalStmt][0],terminal,default_stmt,1);
    addTermToRule(table[conditionalStmt][0],END,rhs,0);

    table[caseStmts][0] = createNewRule(caseStmts,119);
    addTermToRule(table[caseStmts][0],CASE,rhs,0);
    addTermToRule(table[caseStmts][0],terminal,value,1);
    addTermToRule(table[caseStmts][0],COLON,rhs,0);
    addTermToRule(table[caseStmts][0],terminal,statements,1);
    addTermToRule(table[caseStmts][0],BREAK,rhs,0);
    addTermToRule(table[caseStmts][0],SEMICOL,rhs,0);
    addTermToRule(table[caseStmts][0],terminal,caseStmts2,1);

    table[caseStmts2][0] = createNewRule(caseStmts2,120);
    addTermToRule(table[caseStmts2][0],CASE,rhs,0);
    addTermToRule(table[caseStmts2][0],terminal,value,1);
    addTermToRule(table[caseStmts2][0],COLON,rhs,0);
    addTermToRule(table[caseStmts2][0],terminal,statements,1);
    addTermToRule(table[caseStmts2][0],BREAK,rhs,0);
    addTermToRule(table[caseStmts2][0],SEMICOL,rhs,0);
    addTermToRule(table[caseStmts2][0],terminal,caseStmts2,1);

    table[caseStmts2][1] = createNewRule(caseStmts2,121);
        addTermToRule(table[caseStmts2][1],EPSILON,rhs,0); 


    table[value][0] = createNewRule(value,122);
    addTermToRule(table[value][0],NUM,rhs,0);

    table[value][1] = createNewRule(value,123);
    addTermToRule(table[value][1],TRUE,rhs,0);

    table[value][2] = createNewRule(value,124);
    addTermToRule(table[value][2],FALSE,rhs,0);

    table[default_stmt][0] = createNewRule(default_stmt,125);
    addTermToRule(table[default_stmt][0],DEFAULT,rhs,0);
    addTermToRule(table[default_stmt][0],COLON,rhs,0);
    addTermToRule(table[default_stmt][0],terminal,statements,1);
    addTermToRule(table[default_stmt][0],BREAK,rhs,0);
    addTermToRule(table[default_stmt][0],SEMICOL,rhs,0);

    table[default_stmt][1] = createNewRule(default_stmt,126);
        addTermToRule(table[default_stmt][1],EPSILON,rhs,0); 


    table[iterativeStmt][0] = createNewRule(iterativeStmt,127);
    addTermToRule(table[iterativeStmt][0],FOR,rhs,0);
    addTermToRule(table[iterativeStmt][0],BO,rhs,0);
    addTermToRule(table[iterativeStmt][0],ID,rhs,0);
    addTermToRule(table[iterativeStmt][0],IN,rhs,0);
    addTermToRule(table[iterativeStmt][0],terminal,for_range,1);
    addTermToRule(table[iterativeStmt][0],BC,rhs,0);
    addTermToRule(table[iterativeStmt][0],START,rhs,0);
    addTermToRule(table[iterativeStmt][0],terminal,statements,1);
    addTermToRule(table[iterativeStmt][0],END,rhs,0);

    table[iterativeStmt][1] = createNewRule(iterativeStmt,128);
    addTermToRule(table[iterativeStmt][1],WHILE,rhs,0);
    addTermToRule(table[iterativeStmt][1],BO,rhs,0);
    addTermToRule(table[iterativeStmt][1],terminal,abExpr,1);
    addTermToRule(table[iterativeStmt][1],BC,rhs,0);
    addTermToRule(table[iterativeStmt][1],START,rhs,0);
    addTermToRule(table[iterativeStmt][1],terminal,statements,1);
    addTermToRule(table[iterativeStmt][1],END,rhs,0);

    table[for_range][0] = createNewRule(for_range,129);
    addTermToRule(table[for_range][0],terminal,for_index,1);
    addTermToRule(table[for_range][0],RANGEOP,rhs,0);
    addTermToRule(table[for_range][0],terminal,for_index,1);

    table[for_index][0] = createNewRule(for_index,130);
    addTermToRule(table[for_index][0],terminal,for_sign,1);
    addTermToRule(table[for_index][0],terminal,for_index2,1);

    table[for_index2][0] = createNewRule(for_index2,131);
    addTermToRule(table[for_index2][0],NUM,rhs,0);

    table[for_sign][0] = createNewRule(for_sign,132);
    addTermToRule(table[for_sign][0],PLUS,rhs,0);

    table[for_sign][1] = createNewRule(for_sign,133);
    addTermToRule(table[for_sign][1],MINUS,rhs,0);

    table[for_sign][2] = createNewRule(for_sign,134);
    addTermToRule(table[for_sign][2],EPSILON,rhs,0); 
}


