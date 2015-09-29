//---------------------------------------------------------------------------

#ifndef treeH
#define treeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TtreeForm : public TForm
{
__published:	// IDE-managed Components
	TTreeView *TreeView1;
	TMemo *Memo1;
private:	// User declarations
public:		// User declarations
	__fastcall TtreeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TtreeForm *treeForm;
//---------------------------------------------------------------------------
#endif
