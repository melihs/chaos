#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Symbol Symbol;
enum Type { BOOL, NUMBER, STRING, ANY, ARRAY, DICT, VOID };
enum ValueType { V_BOOL, V_INT, V_FLOAT, V_STRING, V_VOID };
enum Role { DEFAULT, PARAM, CALL_PARAM };

#include "errors.h"
#include "utilities/helpers.h"
#if !defined(_WIN32) && !defined(_WIN64) && !defined(__CYGWIN__)
#include "utilities/shell.h"
#endif
#include "functions/function.h"

typedef struct Symbol {
    unsigned long long int id;
    char *name;
    char *secondary_name;
    enum Type type;
    enum Type secondary_type;
    union Value {
        bool b;
        long long int i;
        char *s;
        long double f;
    } value;
    short int sign;
    enum ValueType value_type;
    struct Symbol* previous;
    struct Symbol* next;
    struct Symbol** children;
    unsigned int children_count;
    char *key;
    struct _Function* scope;
    unsigned short int recursion_depth;
    enum Role role;
    struct _Function* param_of;
} Symbol;

Symbol* symbol_cursor;
Symbol* start_symbol;
Symbol* end_symbol;
unsigned long long int symbol_id_counter;

Symbol* complex_mode;
unsigned int symbol_counter;

Symbol* addSymbol(char *name, enum Type type, union Value value, enum ValueType value_type);
Symbol* updateSymbol(char *name, enum Type type, union Value value, enum ValueType value_type);
void removeSymbolByName(char *name);
void removeSymbol(Symbol* symbol);
void freeSymbol(Symbol* symbol);
Symbol* getSymbol(char *name);
Symbol* deepCopySymbol(Symbol* symbol, enum Type type, char *key);
Symbol* deepCopyComplex(char *name, Symbol* symbol);
char* getSymbolValueString(char *name);
long double getSymbolValueFloat(char *name);
bool getSymbolValueBool(char *name);
long long int getSymbolValueInt(char *name);
char* getSymbolValueString_NullIfNotString(Symbol* symbol);
long long int getSymbolValueInt_ZeroIfNotInt(Symbol* symbol);
void printSymbolValue(Symbol* symbol, bool is_complex);
void printSymbolValueEndWith(Symbol* symbol, char *end);
void printSymbolValueEndWithNewLine(Symbol* symbol);
bool isDefined(char *name);
void addSymbolToComplex(Symbol* symbol);
void printSymbolTable();
void addSymbolBool(char *name, bool b);
void updateSymbolBool(char *name, bool b);
Symbol* addSymbolInt(char *name, long long int i);
void updateSymbolInt(char *name, long long int i);
void addSymbolFloat(char *name, long double f);
void updateSymbolFloat(char *name, long double f);
Symbol* addSymbolString(char *name, char *s);
void updateSymbolString(char *name, char *s);
void addSymbolArray(char *name);
Symbol* createCloneFromSymbolByName(char *clone_name, enum Type type, char *name, enum Type extra_type);
Symbol* createCloneFromComplexElement(char *clone_name, enum Type type, char *name, unsigned long long int symbol_id, enum Type extra_type);
Symbol* createCloneFromSymbol(char *clone_name, enum Type type, Symbol* symbol, enum Type extra_type);
Symbol* updateSymbolByClonning(char *clone_name, Symbol* symbol);
Symbol* updateSymbolByClonningName(char *clone_name, char *name);
Symbol* updateSymbolByClonningComplexElement(char *clone_name, char *name, unsigned long long int symbol_id);
bool isComplexIllegal(enum Type type);
void finishComplexMode(char *name, enum Type type);
Symbol* getArrayElement(char *name, long long int i);
void cloneSymbolToComplex(char *name, char *key);
Symbol* getComplexElement(char *name, long long int i, char *key);
Symbol* getComplexElementBySymbolId(char *name, unsigned long long symbol_id);
void updateComplexElement(char *name, unsigned long long symbol_id, enum Type type, union Value value);
void updateComplexElementBool(char* name, unsigned long long symbol_id, bool b);
void updateComplexElementInt(char* name, unsigned long long symbol_id, long long int i);
void updateComplexElementFloat(char* name, unsigned long long symbol_id, long double f);
void updateComplexElementString(char* name, unsigned long long symbol_id, char *s);
void updateComplexElementSymbol(char* name, unsigned long long symbol_id, char* source_name);
void removeComplexElement(char *name, unsigned long long symbol_id);
void addSymbolDict(char *name);
void addSymbolAnyString(char *name, char *s);
void addSymbolAnyInt(char *name, long long int i);
void addSymbolAnyFloat(char *name, long double f);
void addSymbolAnyBool(char *name, bool b);
Symbol* getDictElement(char *name, char *key);
_Function* getCurrentScope();
Symbol* getSymbolFunctionParameter(char *name);
void freeAllSymbols();
Symbol* assignByTypeCasting(Symbol* clone_symbol, Symbol* symbol);
Symbol* createSymbolWithoutValueType(char *name, enum Type type);
void removeSymbolsByScope(_Function* scope);
long long int incrementThenAssign(char *name, short int i);
long long int assignThenIncrement(char *name, short int i);
char* getTypeName(long long int i);
char* getValueTypeName(long long int i);

#endif
