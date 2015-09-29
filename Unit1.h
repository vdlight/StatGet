//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------



class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTreeView *TreeView1;
private:	// User declarations
AnsiString rawHTML;
void bnla(void);
void deleteStr(AnsiString startStr, AnsiString endStr);
bool isWhiteSpace(char c);
bool isBadChar(char c);
bool tagIsNewParent(AnsiString str);

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void test(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
