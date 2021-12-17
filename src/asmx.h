// asmx.h - copyright 1998-2009 Bruce Tomlin

#ifndef _ASMX_H_
#define _ASMX_H_

#define MAX_BYTSTR  1024    // size of bytStr[]

#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// a few useful typedefs
typedef unsigned char  bool;    // define a bool type
enum { FALSE = 0, TRUE = 1 };
#define maxStrLength    256
typedef char Str255[maxStrLength];       // generic string type

#define maxOpcdLen  11          // max opcode length (for building opcode table)
typedef char OpcdStr[maxOpcdLen+1];
struct OpcdRec
{
    OpcdStr         name;       // opcode name
    short           typ;        // opcode type
    unsigned long   parm;       // opcode parameter
};
typedef struct OpcdRec *OpcdPtr;

// CPU option flags
enum
{
    OPT_ATSYM     = 0x01,   // allow symbols to start with '@'
    OPT_DOLLARSYM = 0x02,   // allow symbols to start with '$'
};

void *AddAsm(char *name,        // assembler name
              int (*DoCPUOpcode) (int typ, int parm),
              int (*DoCPULabelOp) (int typ, int parm, char *labl),
              void (*PassInit) (void) );
void AddCPU(void *as,           // assembler for this CPU
            char *name,         // uppercase name of this CPU
            int index,          // index number for this CPU
            int endian,         // assembler endian
            int addrWid,        // assembler 32-bit
            int listWid,        // listing width
            int wordSize,       // addressing word size in bits
            int opts,           // option flags
            struct OpcdRec opcdTab[]); // assembler opcode table

// assembler endian, address width, and listing hex width settings
// 0 = little endian, 1 = big endian, -1 = undefined endian
enum { UNKNOWN_END = -1, LITTLE_END, BIG_END };
enum { ADDR_16, ADDR_24, ADDR_32 };
enum { LIST_16, LIST_24 }; // Note: ADDR_24 and ADDR_32 should always use LIST_24

// special register numbers for FindReg/GetReg
enum
{
    reg_EOL = -2,   // -2
    reg_None,       // -1
};

// opcode constants
// it's stupid that "const int" isn't good enough for these:
#define o_Illegal 0x0100
#define o_LabelOp 0x1000
#define o_EQU (o_LabelOp + 0x100)

void Error(char *message);
void Warning(char *message);
void DefSym(char *symName, unsigned long val, bool setSym, bool equSym);
int GetWord(char *word);
bool Expect(char *expected);
bool Comma();
bool RParen();
void EatIt();
void IllegalOperand();
void MissingOperand();
void BadMode();
int FindReg(const char *regName, const char *regList);
int GetReg(const char *regList);
int CheckReg(int reg);
int Eval(void);
void CheckByte(int val);
void CheckStrictByte(int val);
void CheckWord(int val);
void CheckStrictWord(int val);
int EvalByte(void);
int EvalBranch(int instrLen);
int EvalWBranch(int instrLen);
int EvalLBranch(int instrLen);
void DoLabelOp(int typ, int parm, char *labl);

void InstrClear(void);
void InstrAddB(unsigned char b);
void InstrAddX(unsigned long op);
void InstrAddW(unsigned short w);
void InstrAdd3(unsigned long l);
void InstrAddL(unsigned long l);

void InstrB(unsigned char b1);
void InstrBB(unsigned char b1, unsigned char b2);
void InstrBBB(unsigned char b1, unsigned char b2, unsigned char b3);
void InstrBBBB(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4);
void InstrBBBBB(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned char b5);
void InstrBW(unsigned char b1, unsigned short w1);
void InstrBBW(unsigned char b1, unsigned char b2, unsigned short w1);
void InstrBBBW(unsigned char b1, unsigned char b2, unsigned char b3, unsigned short w1);
void InstrX(unsigned long op);
void InstrXB(unsigned long op, unsigned char b1);
void InstrXBB(unsigned long op, unsigned char b1, unsigned char b2);
void InstrXBBB(unsigned long op, unsigned char b1, unsigned char b2, unsigned char b3);
void InstrXBBBB(unsigned long op, unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4);
void InstrXW(unsigned long op, unsigned short w1);
void InstrXBW(unsigned long op, unsigned char b1, unsigned short w1);
void InstrXBWB(unsigned long op, unsigned char b1, unsigned short w1, unsigned char b2);
void InstrXWW(unsigned long op, unsigned short w1, unsigned short w2);
void InstrX3(unsigned long op, unsigned long l1);
void InstrW(unsigned short w1);
void InstrWW(unsigned short w1, unsigned short w2);
void InstrWL(unsigned short w1, unsigned long l1);
void InstrL(unsigned long l1);
void InstrLL(unsigned long l1, unsigned long l2);

//char * ListStr(char *l, char *s);
char * ListByte(char *p, unsigned char b);
//char * ListWord(char *p, unsigned short w);
//char * ListLong(char *p, unsigned long l);
//char * ListAddr(char *p,unsigned long addr);
//char * ListLoc(unsigned long addr);

// various internal variables used by the assemblers
extern  bool            errFlag;            // TRUE if error occurred this line
extern  int             pass;               // Current assembler pass
extern  char           *linePtr;            // pointer into current line
extern  int             instrLen;           // Current instruction length (negative to display as long DB)
extern  Str255          line;               // Current line from input file
extern  char           *linePtr;            // pointer into current line
extern  unsigned long          locPtr;             // Current program address
extern  int             instrLen;           // Current instruction length (negative to display as long DB)
extern  unsigned char          bytStr[MAX_BYTSTR]; // Current instruction / buffer for long DB statements
extern  bool            showAddr;           // TRUE to show LocPtr on listing
extern  int             endian;             // 0 = little endian, 1 = big endian, -1 = undefined endian
extern  bool            evalKnown;          // TRUE if all operands in Eval were "known"
extern  int             curCPU;             // current CPU index for current assembler
extern  Str255          listLine;           // Current listing line
extern  int             hexSpaces;          // flags for spaces in hex output for instructions
extern  int             listWid;            // listing width: LIST_16, LIST_24

#endif // _ASMX_H_