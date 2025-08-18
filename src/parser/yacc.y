%{
#include "ast.h"
#include "yacc.tab.h"
#include <iostream>
#include <memory>
#include <limits.h>
#include <set>
#include <unordered_map>
std::unordered_map<std::string, std::string> alias_map;
std::unordered_map<std::string, std::string> pam_saila;

int yylex(YYSTYPE *yylval, YYLTYPE *yylloc,void *yyscanner);

void yyerror(YYLTYPE *locp, void *yyscanner , const char* s) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
}

using namespace ast;
%}

// request a pure (reentrant) parser
%define api.pure full
// enable location in error handler
%locations
// enable verbose syntax error message
%define parse.error verbose
// 为了支持多线程的lex sqb 7.9
%param {void *yyscanner}

// keywords
%token SHOW TABLES CREATE TABLE DROP DESC INSERT INTO VALUES DELETE FROM ASC ORDER BY
WHERE UPDATE SET SELECT INT CHAR FLOAT INDEX AND JOIN EXIT HELP TXN_BEGIN TXN_COMMIT TXN_ABORT TXN_ROLLBACK ORDER_BY ENABLE_NESTLOOP ENABLE_SORTMERGE
INNER LEFT RIGHT FULL SEMI ON MAX MIN SUM AVG COUNT AS GROUP HAVING LIMIT EXPLAIN
LOAD OFF OUTPUT_FILE
// non-keywords
%token LEQ NEQ GEQ T_EOF

// type-specific tokens
%token <sv_str> IDENTIFIER VALUE_STRING VALUE_PATH
%token <sv_int> VALUE_INT
%token <sv_float> VALUE_FLOAT
%token <sv_bool> VALUE_BOOL

// added keywords
%token STATIC_CHECKPOINT CRASH ANTI

// specify types for non-terminal symbol
%type <sv_node> stmt dbStmt ddl dml txnStmt setStmt sysStmt io_stmt
%type <sv_field> field
%type <sv_fields> fieldList
%type <sv_type_len> type
%type <sv_comp_op> op
%type <sv_expr> expr
%type <sv_val> value
%type <sv_vals> valueList
%type <sv_str> tbName colName tbNameWithAlias alias fileName
%type <sv_strs> tableList colNameList
%type <sv_col> col aggCol
%type <sv_cols> colList selector optGroupByClause
%type <sv_set_clause> setClause
%type <sv_set_clauses> setClauses
%type <sv_cond> condition
%type <sv_conds> whereClause optWhereClause optHavingClause
%type <sv_orderby>  order_clause
%type <sv_orderbys> opt_order_clause order_clauses
%type <sv_orderby_dir> opt_asc_desc
%type <join_type_dir> join_type    /*yfs0527, 参考sv_orderby_dir*/
%type <sv_join_expr> join_expr
%type <sv_join_exprs> join_exprs join_exprss
%type <sv_setKnobType> set_knob_type
%type <sv_int> limit_clause

%%
start:
        stmt ';'
    {
        parse_tree = $1;
        YYACCEPT;
    }
    |   HELP
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
    |   EXIT
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
    |   T_EOF
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
    |  io_stmt
    {
        parse_tree = $1;
        YYACCEPT;
    }

    ;

stmt:
        dbStmt
    |   ddl
    |   dml
    |   txnStmt
    |   setStmt
    |   sysStmt
    ;

txnStmt:
        TXN_BEGIN
    {
        $$ = std::make_shared<TxnBegin>();
    }
    |   TXN_COMMIT
    {
        $$ = std::make_shared<TxnCommit>();
    }
    |   TXN_ABORT
    {
        $$ = std::make_shared<TxnAbort>();
    }
    | TXN_ROLLBACK
    {
        $$ = std::make_shared<TxnRollback>();
    }
    | CREATE STATIC_CHECKPOINT
    {
        $$ = std::make_shared<CreateCheckPoint>();
    }
    ;

dbStmt:
        SHOW TABLES
    {
        $$ = std::make_shared<ShowTables>();
    }
    |  SHOW INDEX FROM tbName
    {
        $$ = std::make_shared<ShowIndex>($4);
    }
    |  EXPLAIN dml
    {
        if(auto select = std::dynamic_pointer_cast<SelectStmt>($2)){
            select->need_explain = true;
            $$ = select;
        }
    }
    |   LOAD fileName INTO tbName
    {
         $$ = std::make_shared<LoadStmt>($2, $4);
    }
    ;

setStmt:
        SET set_knob_type '=' VALUE_BOOL
    {
        $$ = std::make_shared<SetStmt>($2, $4);
    }
    ;

sysStmt:
       CRASH
    {
        $$ = std::make_shared<CrashStmt>();
    }
    ;

io_stmt:
        SET OUTPUT_FILE ON
    {
        $$ = std::make_shared<IoEnable>(true);
    }
    |   SET OUTPUT_FILE OFF
    {
        $$ = std::make_shared<IoEnable>(false);
    }
    ;
ddl:
        CREATE TABLE tbName '(' fieldList ')'
    {
        $$ = std::make_shared<CreateTable>($3, $5);
    }
    |   DROP TABLE tbName
    {
        $$ = std::make_shared<DropTable>($3);
    }
    |   DESC tbName
    {
        $$ = std::make_shared<DescTable>($2);
    }
    |   CREATE INDEX tbName '(' colNameList ')'
    {
        $$ = std::make_shared<CreateIndex>($3, $5);
    }
    |   DROP INDEX tbName '(' colNameList ')'
    {
        $$ = std::make_shared<DropIndex>($3, $5);
    }
    ;

dml:
        INSERT INTO tbName VALUES '(' valueList ')'
    {
        $$ = std::make_shared<InsertStmt>($3, $6);
    }
    |   DELETE FROM tbName optWhereClause
    {
        $$ = std::make_shared<DeleteStmt>($3, $4);
    }
    |   UPDATE tbName SET setClauses optWhereClause
    {
        $$ = std::make_shared<UpdateStmt>($2, $4, $5);
    }
    |   SELECT selector FROM tableList optWhereClause optGroupByClause optHavingClause opt_order_clause limit_clause
    {
        $$ = std::make_shared<SelectStmt>($2, $4, $5, $6, $7, $8, $9);
    }
    |   SELECT selector FROM join_exprss optWhereClause optGroupByClause optHavingClause opt_order_clause limit_clause
    {
        /*$$ = std::make_shared<SelectStmt>($2, $4, $5, $6);*/
        /*必须要把所有表名赋值给SelectStmt的tabs，后面需要用*/
        auto sel_stmt = std::make_shared<SelectStmt>($2, $4, $5, $6, $7, $8, $9);
        std::set<std::string> tab_set;
        for (const auto &join_expr : $4) {
            if (join_expr) {
                tab_set.insert(join_expr->left);
                tab_set.insert(join_expr->right);
            }
        }
        sel_stmt->tabs.assign(tab_set.begin(), tab_set.end());
        $$ = sel_stmt;
    }
    ;

limit_clause:
    LIMIT VALUE_INT
    {
        $$ = $2;
    }
    |   /* epsilon */
    {
        $$ = INT_MAX;
    }
    ;

optGroupByClause:
        /* empty */
    {
        $$ = {};
    }
    |   GROUP BY colList
    {
        $$ = $3;
    }
    ;

optHavingClause:
        /* epsilon */ { /* ignore*/ }
    |   HAVING whereClause
    {
        $$ = $2;
    }
    ;   
    

fieldList:
        field
    {
        $$ = std::vector<std::shared_ptr<Field>>{$1};
    }
    |   fieldList ',' field
    {
        $$.push_back($3);
    }
    ;

colNameList:
        colName
    {
        $$ = std::vector<std::string>{$1};
    }
    | colNameList ',' colName
    {
        $$.push_back($3);
    }
    ;

field:
        colName type
    {
        $$ = std::make_shared<ColDef>($1, $2);
    }
    ;

type:
        INT
    {
        $$ = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
    |   CHAR '(' VALUE_INT ')'
    {
        $$ = std::make_shared<TypeLen>(SV_TYPE_STRING, $3);
    }
    |   FLOAT
    {
        $$ = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
    ;

valueList:
        value
    {
        $$ = std::vector<std::shared_ptr<Value>>{$1};
    }
    |   valueList ',' value
    {
        $$.push_back($3);
    }
    ;

value:
        VALUE_INT
    {
        $$ = std::make_shared<IntLit>($1);
    }
    |   VALUE_FLOAT
    {
        $$ = std::make_shared<FloatLit>($1);
    }
    |   VALUE_STRING
    {
        $$ = std::make_shared<StringLit>($1);
    }
    |   VALUE_BOOL
    {
        $$ = std::make_shared<BoolLit>($1);
    }
    ;

condition:
        col op expr
    {
        $$ = std::make_shared<BinaryExpr>($1, $2, $3);
    }
    ;

optWhereClause:
        /* epsilon */ { /* ignore*/ }
    |   WHERE whereClause
    {
        $$ = $2;
    }
    ;

whereClause:
        condition 
    {
        $$ = std::vector<std::shared_ptr<BinaryExpr>>{$1};
    }
    |   whereClause AND condition
    {
        $$.push_back($3);
    }
    ;

col:
        tbName '.' colName
    {
        $$ = std::make_shared<Col>($1, $3);
    }
    |   colName
    {
        $$ = std::make_shared<Col>("", $1);
    }
    |   aggCol
    {
        $$ = $1;
    }
    ;

colList:
        col
    {
        $$ = std::vector<std::shared_ptr<Col>>{$1};
    }
    |   colList ',' col
    {
        $$.push_back($3);
    }
    ;

op:
        '='
    {
        $$ = SV_OP_EQ;
    }
    |   '<'
    {
        $$ = SV_OP_LT;
    }
    |   '>'
    {
        $$ = SV_OP_GT;
    }
    |   NEQ
    {
        $$ = SV_OP_NE;
    }
    |   LEQ
    {
        $$ = SV_OP_LE;
    }
    |   GEQ
    {
        $$ = SV_OP_GE;
    }
    ;

expr:
        value
    {
        $$ = std::static_pointer_cast<Expr>($1);
    }
    |   col
    {
        $$ = std::static_pointer_cast<Expr>($1);
    }
    ;

setClauses:
        setClause
    {
        $$ = std::vector<std::shared_ptr<SetClause>>{$1};
    }
    |   setClauses ',' setClause
    {
        $$.push_back($3);       /*我怎么感觉这里写错了？难道不应该把setClauses先赋值给$$吗？而且setClause也不应该是vector而应该是ptr*/
    }
    ;

setClause:
        colName '=' value
    {
        $$ = std::make_shared<SetClause>($1, $3);
    }
    |   colName '=' colName value
    {
        $$ = std::make_shared<SetClause>($1, $4, true);
    }
    |   colName '=' colName '+' value
    {
        $$ = std::make_shared<SetClause>($1, $5, true);
    }
    ;

selector:
        '*'
    {
        $$ = {};
    }
    |   colList
    ;

aggCol:
        MAX '(' col ')' AS alias
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_MAX, $6));
    }
    |   MIN '(' col ')' AS alias
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_MIN, $6));
    }
    |   SUM '(' col ')' AS alias
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_SUM, $6));
    }
    |   AVG '(' col ')' AS alias
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_AVG, $6));
    }
    |   COUNT '(' col ')' AS alias
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_COUNT, $6));
    }
    |   COUNT '(' '*' ')' AS alias
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, $6));
    }
    |   MAX '(' col ')'
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_MAX, ""));
    }
    |   MIN '(' col ')' 
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_MIN, ""));
    }
    |   SUM '(' col ')'
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_SUM, ""));
    }
    |   AVG '(' col ')'
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_AVG, ""));
    }
    |   COUNT '(' col ')'
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>($3->tab_name, $3->col_name, AGG_COUNT, ""));
    }
    |   COUNT '(' '*' ')'
    {
        $$ = std::static_pointer_cast<Col>(std::make_shared<AggCol>("", "*", AGG_COUNT, ""));
    }
    ;

tableList:
        tbNameWithAlias
    {
        $$ = std::vector<std::string>{$1};
    }
    |   tableList ',' tbNameWithAlias
    {
        $$.push_back($3);
    }
    /*|   tableList JOIN tbName */
    /*{                         */
    /*    $$.push_back($3);     */
    /*}   yfs0604:  这里会和自己定义的join冲突，所以注释掉好了  */
    ;

tbNameWithAlias:        /*这里多做的一个步骤只是把别名存在映射里*/
        tbName
    {
        $$ = $1;
    }
    |   tbName alias
    {
        alias_map[$2] = $1;
        pam_saila[$1] = $2;
        $$ = $1;
    }

join_exprss:
    tbNameWithAlias join_exprs
    {
        $$ = $2;
        for (auto& join_expr : $$) {
            join_expr->left = $1;
        }
    }


join_exprs:
        join_expr
    {
        $$ = std::vector<std::shared_ptr<JoinExpr>>{$1};
    }
    |   join_exprs join_expr
    {
        $$.push_back($2);
    }

join_expr:
        join_type tbNameWithAlias ON whereClause
    {
        $$ = std::make_shared<JoinExpr>("", $2, $4, $1);
    }

join_type:      /*yfs0527*/
        JOIN   { $$ = INNER_JOIN; }
    |   INNER JOIN   { $$ = INNER_JOIN; }
    |   LEFT JOIN   { $$ = LEFT_JOIN; }
    |   RIGHT JOIN   { $$ = RIGHT_JOIN; }
    |   FULL JOIN   { $$ = FULL_JOIN; }
    |   SEMI JOIN   { $$ = SEMI_JOIN; }
    |   ANTI JOIN  {$$=ANTI_JOIN;}
    ;


opt_order_clause:
    ORDER BY order_clauses
    { 
        $$ = $3; 
    }
    |   /* epsilon */ { /* ignore*/ }
    ;

order_clauses:
    order_clause
    {
        $$ = std::vector<std::shared_ptr<OrderBy>>{$1};
    }
    |   order_clauses ',' order_clause
    {
        $$.push_back($3);
    }
    ;

order_clause:
      col  opt_asc_desc
    { 
        $$ = std::make_shared<OrderBy>($1, $2);
    }
    ;   

opt_asc_desc:
    ASC          { $$ = OrderBy_ASC;     }
    |  DESC      { $$ = OrderBy_DESC;    }
    |            { $$ = OrderBy_ASC; }
    ;    

set_knob_type:
    ENABLE_NESTLOOP { $$ = EnableNestLoop; }
    |   ENABLE_SORTMERGE { $$ = EnableSortMerge; }
    ;

tbName: IDENTIFIER;

colName: IDENTIFIER;

alias: IDENTIFIER;

fileName: VALUE_PATH;
%%
