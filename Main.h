//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------



class TmainFrm : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TButton *init;
	TButton *Button1;
	TEdit *homeTeamFull;
	TEdit *homeTeam;
	TEdit *awayTeamFull;
	TListView *PeriodGoals;
	TEdit *awayTeam;
	TMainMenu *MainMenu1;
	TMenuItem *tree;
	TEdit *awayShots;
	TEdit *homeShots;
	TEdit *statsAddress;
	TEdit *date;
	TButton *genFiles;
	TListView *penaltys;
	TCheckBox *practiceGame;
	TEdit *round;
	TEdit *resultat;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall initClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall treeClick(TObject *Sender);
	void __fastcall genFilesClick(TObject *Sender);
private:	// User declarations
AnsiString rawHTML;
void bnla(void);
void deleteStr(AnsiString startStr, AnsiString endStr);
void findInfo(void);
bool isWhiteSpace(char c);
bool isBadChar(char c);
bool tagIsNewParent(AnsiString str);
bool isGoalTeamStat(AnsiString str);

public:		// User declarations
	__fastcall TmainFrm(TComponent* Owner);
	void GenerateTree(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TmainFrm *mainFrm;
//---------------------------------------------------------------------------
#endif
