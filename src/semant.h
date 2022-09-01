#ifndef SEMANT_H
#define SEMANT_H

/* @Note:
   We want to implement some basic semantic checker. In this case it will consist of:
   - Basic type checking
   - Check if a variable is in scope

   ### Type Checking
   Type checking needs to be done both for expressions (binop, unop, assignments) and function arguments.

   ### Scopes
   We need to have a global scope (function declarations for now only) and a local scope (within functions and blocks).
   So for type checking we need a 
 */

typedef enum
{
    BUILTIN_INT,
    BUILTIN_FLOAT,
    BUILTIN_STRING,
    BUILTIN_UNIT,
} Sem_Builtin_Type;

typedef enum
{
    TYPE_KIND_BUILTIN,
    TYPE_KIND_ALIAS,
    TYPE_KIND_STRUCT,
    TYPE_KIND_ENUM,
    TYPE_KIND_FUNCTION
} Sem_Type_Kind;

typedef struct Sem_Type Sem_Type;

typedef struct Sem_Type_Alias Sem_Type_Alias;
struct Sem_Type_Alias
{
    String* alias_name;
    Sem_Type* aliased_type;
};

struct Sem_Type
{
    Sem_Type_Kind kind;

    union
    {
        Sem_Builtin_Type builtin;
        Sem_Type_Alias alias;
    };
};

typedef struct Sem_Variable_Info Sem_Variable_Info;
struct Sem_Variable_Info
{
    String* name;
    Sem_Type type_info;
};

typedef struct Sem_Variable_Key Sem_Variable_Key;
struct Sem_Variable_Key
{
    String* key;
    u32 hash;
};

typedef struct Sem_Variable_Table Sem_Variable_Table;
struct Sem_Variable_Table
{
    Sem_Variable_Key*  keys;
    Sem_Variable_Info* entries;

    i32 count;
    i32 capacity;
};

#define SEM_TABLE_MAX_LOAD 0.75f

typedef struct Sem_Scope_Handle Sem_Scope_Handle;
struct Sem_Scope_Handle
{
    i32 handle;
};

#define SEM_HANDLE_VALID(h) (h.handle != -1)

typedef struct Sem_Scope Sem_Scope;
struct Sem_Scope
{
    Sem_Scope_Handle parent_handle;
    
    Sem_Variable_Table table;
};

typedef struct Sem_Checker Sem_Checker;
struct Sem_Checker
{
    struct
    {
        Sem_Scope* scopes;
        i32 count;
        i32 capacity;
    } scope_list;

    Sem_Scope_Handle current_scope;
    
    b32 had_error; // @Incomplete: Replace with an enum for different results, maybe bit flags?
};

#endif
