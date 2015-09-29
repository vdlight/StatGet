//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "tree.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmainFrm *mainFrm;
//---------------------------------------------------------------------------
#include<iostream>
#include<fstream>

//#include<cstring>
#include<wininet.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>

//#include <string>

//using namespace std;

#define VERSION_GEN 	1
#define VERSION_VER		0

__fastcall TmainFrm::TmainFrm(TComponent* Owner)  : TForm(Owner) {
    this->Caption = "TAIF Stat v." + AnsiString(VERSION_GEN) + "." + AnsiString(VERSION_VER);

}

void TmainFrm::bnla(void) {
	int startPos;
	int endPos;
    ofstream output;
}




void  TmainFrm::findInfo(void) {
	// Team

	int i = 0;
	int startPos, endPos;
	TTreeNode* node;

	PeriodGoals->Clear();
	penaltys->Clear();

//	AnsiString title;
	for(i = 0; i < treeForm->TreeView1->Items->Count; i++) {
		node = treeForm->TreeView1->Items[0].Item[i];
		if (AnsiString(node->Text).Pos("title") != 0) {
			startPos = node->Text.Pos(":")+2;
			endPos = node->Text.Pos("-")-1;
			homeTeam->Text = node->Text.SubString(startPos, endPos-startPos);

			startPos = node->Text.Pos("-")+2;
			endPos = node->Text.Pos("(")-1;
			awayTeam->Text = node->Text.SubString(startPos, endPos-startPos);
			i++;

			startPos = endPos + 2 ;
			resultat->Text = node->Text.SubString(startPos, node->Text.Length()-startPos);
			break;
		}
	}




//	AnsiString teams;
	for(; i < treeForm->TreeView1->Items->Count; i++) {
		node = treeForm->TreeView1->Items[0].Item[i];
		if (AnsiString(node->Text).Pos("h2:") != 0) {
			startPos = node->Text.Pos(":")+2;
			endPos = node->Text.Pos("-")-1;
			homeTeamFull->Text = node->Text.SubString(startPos, endPos-startPos);

			startPos = node->Text.Pos("-")+2;
			endPos = node->Text.Length()+1;
			awayTeamFull->Text = node->Text.SubString(startPos, endPos-startPos);
			i++;
			break;
		}
	}

//	AnsiString date;
	int cnt;
    for(; i < treeForm->TreeView1->Items->Count; i++) {
		node = treeForm->TreeView1->Items[0].Item[i];
		if (AnsiString(node->Text).Pos("h3:") != 0) {
			startPos = node->Text.Pos(":")+2;
			date->Text = node->Text.SubString(startPos, 10);
			i++;
			break;
		}
	}


//	AnsiString homeShots;
	for(; i < treeForm->TreeView1->Items->Count; i++) {
		node = treeForm->TreeView1->Items[0].Item[i];
		if (AnsiString(node->Text).Pos("(") != 0) {
			startPos = node->Text.Pos(("("))+1;
			endPos = node->Text.Pos(")") ;
			homeShots->Text =node->Text.SubString(startPos, endPos-startPos);
			i++;
			break;
		}
	}

//	AnsiString awayShots;
	cnt = 0;
	for(; i < treeForm->TreeView1->Items->Count; i++) {
		node = treeForm->TreeView1->Items[0].Item[i];
		if (AnsiString(node->Text).Pos("(") != 0) {
			cnt++;
			if (cnt > 1) {
				startPos = node->Text.Pos(("("))+1;
				endPos = node->Text.Pos(")") ;
				awayShots->Text =node->Text.SubString(startPos, endPos-startPos);

				i++;
				break;
			}
		}
	}

	TListItem  *goal;
	AnsiString nodeText;
	int goalScoreIdx;

	// kanske straffar?
	goalScoreIdx = 0;
	for(; i < treeForm->TreeView1->Items->Count; i++) {
		node = treeForm->TreeView1->Items[0].Item[i];
		nodeText = node->Text;

		if (nodeText.Pos("Missed") != 0 || nodeText.Pos("Scored") != 0) {
			goalScoreIdx = i;
		}
		else if (nodeText.Pos("period") != 0 || nodeText.Pos("Overtime") != 0 ) {
			break; // inga fler straffar, dags för perioder
		}

		AnsiString tmp;
		int pos;

		if (goalScoreIdx) {
			// add goal
			// mål/miss
			goal = penaltys->Items->Add() ;
			nodeText = treeForm->TreeView1->Items[0].Item[goalScoreIdx]->Text;
			startPos = nodeText.Pos(":")+2;
			endPos = nodeText.Length()+1;
			goal->Caption = nodeText.SubString(startPos, endPos-startPos);
			// resultat
			nodeText = treeForm->TreeView1->Items[0].Item[goalScoreIdx+1]->Text;
			startPos = nodeText.Pos(":") + 2;
			endPos = nodeText.Length()+1;
			tmp = nodeText.SubString(startPos, endPos-startPos);

			while (pos = tmp.Pos(" ") != 0) {
				pos = tmp.Pos(" ");
				tmp.Delete(pos, 1);
			}
			goal->SubItems->Add(tmp);
			// lag
			nodeText = treeForm->TreeView1->Items[0].Item[goalScoreIdx+2]->Text;
			startPos = nodeText.Pos(":") + 2;
			endPos = nodeText.Length()+1;
			goal->SubItems->Add(nodeText.SubString(startPos, endPos-startPos));
			// Straffläggare
			nodeText = treeForm->TreeView1->Items[0].Item[goalScoreIdx+4]->Text;
			startPos = nodeText.Pos(":") + 2;
			endPos = nodeText.Length()+1;
			goal->SubItems->Add(nodeText.SubString(startPos, endPos-startPos));

			goalScoreIdx = 0;
		}
	}



	AnsiString periodX;

	goalScoreIdx = 0;
	for(; i < treeForm->TreeView1->Items->Count; i++) {
		node = treeForm->TreeView1->Items[0].Item[i];
		nodeText = node->Text;

		// när GK In läses, är vi färdiga
		// när period läses, hoppar vi till nästa. löser sig själv
		if(isGoalTeamStat(nodeText)) {
			goalScoreIdx = i;
		}
		else if (goalScoreIdx != 0) {
			if (nodeText.Pos("tr") != 0) { // tr, new action
				// add goal
				// tid
				goal = PeriodGoals->Items->Add() ;
				nodeText = treeForm->TreeView1->Items[0].Item[goalScoreIdx-1]->Text;
				startPos = nodeText.Pos(":")+2;
				endPos = nodeText.Length()+1;
				goal->Caption = nodeText.SubString(startPos, endPos-startPos);
				// Res
				nodeText = treeForm->TreeView1->Items[0].Item[goalScoreIdx]->Text;
				startPos = nodeText.Pos(":") + 2;
				endPos = nodeText.Pos("(")-1;
				goal->SubItems->Add(nodeText.SubString(startPos, endPos-startPos));
				// Stat
				startPos = nodeText.Pos("(") + 1;
				endPos = nodeText.Length();

				AnsiString tmp;
				tmp = nodeText.SubString(startPos, endPos-startPos);
				if (treeForm->TreeView1->Items[0].Item[goalScoreIdx+1]->Text.Pos("ENG") != 0) {
				 tmp += " ENG";
				 goalScoreIdx++; //offset for ENG tagg
				}
				goal->SubItems->Add(tmp);


				// Team
				nodeText = treeForm->TreeView1->Items[0].Item[goalScoreIdx+1]->Text;
				startPos = nodeText.Pos(":")+2;
				endPos = nodeText.Length()+1;

				goal->SubItems->Add(nodeText.SubString(startPos, endPos-startPos));
				// Mål
				nodeText = treeForm->TreeView1->Items[0].Item[goalScoreIdx+2]->Text;
				startPos = nodeText.Pos(":") + 2;
				endPos = nodeText.Length()+1;

				tmp = nodeText.SubString(startPos, endPos-startPos);
				if (nodeText.Pos("(") != 0) {      // några målgörare har målstats i samma tag, bort!
					endPos = nodeText.Pos("(") -1;
				}

				goal->SubItems->Add(nodeText.SubString(startPos, endPos-startPos));
				tmp = nodeText.SubString(startPos, endPos-startPos);
				// Ass1
				int assCnt = 0;
				for (int j = 3; j < 15; j++) {
					nodeText = treeForm->TreeView1->Items[0].Item[goalScoreIdx+j]->Text;
					if (nodeText.Pos("Pos.") != 0) { // positive part found, no more assists for goal
						if (assCnt == 0) {
							goal->SubItems->Add("N/A");
							goal->SubItems->Add("N/A");
						}
						else if (assCnt == 1) {
							goal->SubItems->Add("N/A");
						}
					}
					else if (nodeText.Pos("div") != 0) {
	                    assCnt++;
						startPos = nodeText.Pos(":")+2;
						endPos = nodeText.Length()+1;
						goal->SubItems->Add(nodeText.SubString(startPos, endPos-startPos));
					}
				}
				goalScoreIdx = 0;
			}
		}
	}
}



bool TmainFrm::isGoalTeamStat(AnsiString str) {
	if (str.Pos("EQ") != 0 ||
		str.Pos("PP1") != 0 ||
		str.Pos("SH1") != 0 ||
		str.Pos("PP2") != 0 ||
		str.Pos("SH2") != 0 ||
		str.Pos("PS") != 0) {
		return true;
	}

    return false;
}


void TmainFrm::GenerateTree(void) {
	int parentNode = 0;
	int nodeCnt = 0;
	int treeDepthParents[50] = {0};
    int currentParent = 0;
	treeForm->TreeView1->Items->Clear();

	// find next tag
	int pos;
	int start =0 ;
	bool endSign;
	int startPos;
	int endPos;
	AnsiString tag = "";
	AnsiString buff;
	bool tagNameEnded;
	TTreeNode* currentNode;

	// First child and its children
	treeForm->TreeView1->Items->Add(NULL, "HTML Base");
	buff = rawHTML;

	currentParent = 0;
	treeDepthParents[currentParent] = 0;
	bool modified;
	bool dataErased;
	bool endRowFound = true;

	// find next tag
	while (0 != (startPos = buff.Pos("<"))) {
		endPos = startPos;
		startPos++;
		tag = "";
		tagNameEnded = false;


		// if data exists on tag
		AnsiString data ="";
		if (startPos > 2 && nodeCnt > 0) {
			AnsiString data = buff.SubString(1, startPos-2);
			dataErased = false;

			do {
				modified = false;
				if (isWhiteSpace(data[1]) || isBadChar(data[1])) {
					if (data.Length() == 1) {
						dataErased = true;
					}
					data.Delete(1,1);
					modified = true;
				}
			}while(!dataErased && modified);

			if (!dataErased) {
				do {
					modified = false;
					int b = data.Length();
					if (isWhiteSpace(data[data.Length()]) || isBadChar(data[data.Length()])) {
						if (data.Length() == 1) {
							dataErased = true;
						}
						data.Delete(data.Length(),1);
						modified = true;
					}
				}while (!dataErased && modified);
			}

			if (!dataErased) {
				do {
					modified = false;
					for (int i = 1; i <= data.Length(); i++) {
						if (isBadChar(data[i])) {
							if (data.Length() == 1) {
								dataErased = true;
							}
							data.Delete(i, 1);
							i--;
							modified = true;
						}
						else if(isWhiteSpace(data[i]) && i > 1) {
							if (isWhiteSpace(data[i-1])) {
								if (data.Length() == 1) {
									dataErased = true;
								}

								data.Delete(i, 1);
								i--;
								modified = true;
							}
						}
					}
				}while(modified && !dataErased);

				if (!dataErased) {
					currentNode->Text = currentNode->Text + ": " + data;
				}
			}
		}

		while (buff[++endPos] != '>') {
			if (buff[endPos] != '/') {
				if (buff[endPos] == ' ') {
					tagNameEnded = true;
				}

				if (!tagNameEnded) {
					tag += buff[endPos];
                }

			}
		}
		endSign = buff[startPos] == '/';

		if (!endSign) {
			if (tag.AnsiCompare("tr") == 0) {
				if (!endRowFound) {
					// make end row, code missed that apparently
					currentParent--;
				}
				endRowFound = false;
			}

			currentNode = treeForm->TreeView1->Items->AddChild(treeForm->TreeView1->Items->Item[treeDepthParents[currentParent]], tag.c_str());
			nodeCnt++;
			if (tagIsNewParent(tag)) {
				currentParent++;
				treeDepthParents[currentParent] = nodeCnt;
			}

		}
		else {
			if (tag.AnsiCompare("tr") == 0) {
				endRowFound = true;
			}

			if (tagIsNewParent(tag)) {
				currentParent--;
			}
		}

		buff.Delete(1,endPos);
   	}
}

bool TmainFrm::isWhiteSpace(char c) {
	if (c == char(0xA0) || c == char(0x20)) {
		return true;
	}
	return false;
}bool TmainFrm::isBadChar(char c) {	if (c == '\r' || c == '\n' || c == char(0xC2)) {
		return true;
	}
	return false;
}bool TmainFrm::tagIsNewParent(AnsiString str) {	if (str.AnsiCompare("td") == 0 || str.AnsiCompare("div") == 0		|| str.AnsiCompare("h1") == 0 || str.AnsiCompare("h2") == 0		|| str.AnsiCompare("h3") == 0 || str.AnsiCompare("strong") == 0		|| str.AnsiCompare("span") == 0 || str.AnsiCompare("th") == 0		|| str.AnsiCompare("link") == 0		|| str.AnsiCompare("meta") == 0) {		return false;	}	return true;}

void TmainFrm::deleteStr(AnsiString startStr, AnsiString endStr) {
	int startPos;
	int endPos;
	int startStrLen;
	int endStrLen;

  //	rawHTML = "abcdefg hij klmnop";
   //	startStr = "cd";
   //	endStr = "m";

   /*
  	deleteStr("<script>", "</script>");
	deleteStr("<link", "/>");
	deleteStr("<meta", "/>");
	deleteStr("style=\"", "\"");
	deleteStr("align=\"", "\"");
	deleteStr("rowspan=\"", "\"");
	deleteStr("colspan=\"", "\"");
	deleteStr("width=\"", "\"");
	deleteStr("border=\"", "\"");


		output.open("Moddat2.txt");
	output << rawHTML.c_str();
	output.close();


 */

	while(0 != (startPos = rawHTML.Pos(startStr))) {

		startStrLen = startStr.Length();
		endStrLen = endStr.Length();

		endPos = rawHTML.SubString(startPos+startStrLen, rawHTML.Length()).Pos(endStr);


		AnsiString debug1 = rawHTML.SubString(startPos, endPos);

		rawHTML.Delete(startPos, startStr.Length() + endPos + endStr.Length()-1);
	}
}

void __fastcall TmainFrm::Timer1Timer(TObject *Sender)
{
//	if (!init) {

}
//---------------------------------------------------------------------------

void __fastcall TmainFrm::initClick(TObject *Sender)
{

	ofstream output;

//	setlocale(LC_ALL, "3C");

	output.open("test.txt");

	if (!output.is_open()) {
		int a = 2;
	}

	HINTERNET connect = InternetOpen(String("MyBrowser").c_str(),INTERNET_OPEN_TYPE_PRECONFIG,NULL, NULL, 0);

	if(!connect){
		std::cout <<"Connection Failed or Syntax error";
	}

	HINTERNET OpenAddress = InternetOpenUrl(connect,statsAddress->Text.c_str(), NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE|INTERNET_FLAG_KEEP_CONNECTION, 0);



	if ( !OpenAddress ) {
		DWORD ErrorNum = GetLastError();
		std::cout << "Failed to open URL \nError No: "<<ErrorNum;
		InternetCloseHandle(connect);
	}

	char DataReceived[4096];
	DWORD NumberOfBytesRead = 0;

	rawHTML = "";
	while(InternetReadFile(OpenAddress, DataReceived, 4096, &NumberOfBytesRead) && NumberOfBytesRead ) {
		output << AnsiString(DataReceived).c_str();
//		rawHTML += DataReceived;


	int nSize = ::MultiByteToWideChar(CP_UTF8, 0, DataReceived, NumberOfBytesRead + 1, NULL, 0);
	if (nSize)
	{
		LPWSTR lpszText = new WCHAR[nSize];
		// Convert UTF-8 string to wide string
		::MultiByteToWideChar(CP_UTF8, 0, DataReceived, NumberOfBytesRead, lpszText, nSize);
		// Terminate string. buffer may be not NULL terminated.
		lpszText[nSize - 1] = L'\0';
	//	MessageBoxW(NULL, lpszText, L"Check", MB_OK);
		rawHTML += lpszText;
		delete [] lpszText;
	}




	}

	InternetCloseHandle(OpenAddress);
	InternetCloseHandle(connect);
	output.close();

	GenerateTree();

}
//---------------------------------------------------------------------------

void __fastcall TmainFrm::Button1Click(TObject *Sender)
{
	findInfo();
}
//---------------------------------------------------------------------------

void __fastcall TmainFrm::treeClick(TObject *Sender)
{
	treeForm->Visible = !treeForm->Visible;
}
//---------------------------------------------------------------------------


void __fastcall TmainFrm::genFilesClick(TObject *Sender)
{
	ofstream out;
//	ifstream in;
//	char temp[256];
//
//	in.open("script.txt");
	out.open("matchScript.jsx");

	AnsiString tmp;

	out << "#target photoshop" << std::endl << std::endl;

	if (practiceGame->Checked) {
		out << "var headline = \"" << AnsiString("Träningsmatch").c_str() << "\"\;" <<std::endl;
	}
	else {
    	out << "var headline = \"Omgång " << AnsiString(round->Text).c_str() << "\"\;" << std::endl;
	}

	out << "var matchDate = \"" << AnsiString(date->Text).c_str() << "\"\;" << std::endl;
	//	var result = "4-5";
	out << "var result = \"" << AnsiString(resultat->Text).c_str() << "\";" << std::endl;

	out << "var awayTeamShort = \"" << AnsiString(awayTeam->Text).c_str() << "\"\;" << std::endl;
	out << "var awayTeamName = \"" << AnsiString(awayTeamFull->Text).c_str() << "\"\;" <<std::endl;
	out << "var homeTeamShort = \"" << AnsiString(homeTeam->Text).c_str() << "\"\;" << std::endl;
	out << "var homeTeamName = \"" << AnsiString(homeTeamFull->Text).c_str() << "\"\;" <<std::endl;

	// cunt periods
	int periods = 0;
	int start = 1;
	tmp = awayShots->Text;
	int pos;

	AnsiString periodStr[4] = {"period1", "period2", "period3", "period4"};
    int periodTimeLimit[4] ={0, 20, 40, 60};

	while(pos = tmp.SubString(1, tmp.Length()).Pos(":") != 0) {
		pos = tmp.SubString(1, tmp.Length()).Pos(":");
		periods++;
		tmp.Delete(1,pos);
	}

	if (penaltys->Items->Count == 0) {
		periods++; // om det är straffar så räknas det som extra period, därav ska jag inte plussa upp
    }

	out << "var periods = \"" << periods << "\"\;" <<std::endl;

	AnsiString awayTeamShots = "";
	tmp = awayShots->Text;
	while(tmp.Pos(":") != 0) {
		pos = tmp.Pos(":");
		awayTeamShots += tmp.SubString(1, pos-1) += "\", \"" ;
		tmp.Delete(1, pos);
	}
	awayTeamShots += tmp.SubString(1, tmp.Length());

	AnsiString homeTeamShots = "";

	tmp = homeShots->Text;
	while(tmp.Pos(":") != 0) {
		pos = tmp.Pos(":");
		homeTeamShots += tmp.SubString(1, pos-1) += "\", \"" ;
		tmp.Delete(1, pos);
	}
	homeTeamShots += tmp.SubString(1, tmp.Length());

	out << "var homeShots = new Array(\"" << homeTeamShots.c_str() << "\");" <<std::endl;
	out << "var awayShots = new Array(\"" << awayTeamShots.c_str() << "\");" <<std::endl;


	AnsiString period1_goal_time = "";
	AnsiString period1_goal_teamStat = "";
	AnsiString period1_goal = "";
	AnsiString period1_goal_team = "";
	AnsiString period1_goal_scorer = "";
	AnsiString period1_goal_ass1 = "";
	AnsiString period1_goal_ass2 = "";
	bool period1_first = true;

	AnsiString period2_goal_time = "";
	AnsiString period2_goal_teamStat = "";
	AnsiString period2_goal = "";
	AnsiString period2_goal_team = "";
	AnsiString period2_goal_scorer = "";
	AnsiString period2_goal_ass1 = "";
	AnsiString period2_goal_ass2 = "";
	bool period2_first = true;

	AnsiString period3_goal_time = "";
	AnsiString period3_goal_teamStat = "";
	AnsiString period3_goal = "";
	AnsiString period3_goal_team = "";
	AnsiString period3_goal_scorer = "";
	AnsiString period3_goal_ass1 = "";
	AnsiString period3_goal_ass2 = "";
	bool period3_first = true;

	AnsiString period4_goal_time = "";
	AnsiString period4_goal_teamStat = "";
	AnsiString period4_goal = "";
	AnsiString period4_goal_team = "";
	AnsiString period4_goal_scorer = "";
	AnsiString period4_goal_ass1 = "";
	AnsiString period4_goal_ass2 = "";
	bool period4_first = true;

	AnsiString startStr = "\"";

	tmp = PeriodGoals->Items->Item[0]->Caption.SubString(1, PeriodGoals->Items->Item[0]->Caption.Pos(":")-1);
	if (PeriodGoals->Items->Count > 0) {
		if (AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->Caption.SubString(1, PeriodGoals->Items->Item[0]->Caption.Pos(":")-1)).AnsiCompare("60") > 0) {
			period4_first = false;
			period4_goal_time += startStr + PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->Caption;
			period4_goal += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[0]);
			period4_goal_teamStat += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[1]);
			period4_goal_team += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[2]).AnsiCompare(AnsiString(homeTeam->Text)) == 0 ? AnsiString("\"h") : AnsiString("\"b");
			period4_goal_scorer += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[3]);
			period4_goal_ass1 += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[4]);
			period4_goal_ass2 += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[5]);
		}
		else if (AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->Caption.SubString(1, PeriodGoals->Items->Item[0]->Caption.Pos(":")-1)).AnsiCompare("40") > 0) {
			period3_first = false;
			period3_goal_time += startStr + PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->Caption;
			period3_goal += startStr +  AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[0]);
			period3_goal_teamStat += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[1]);
			period3_goal_team += startStr +  AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[2]).AnsiCompare(AnsiString(homeTeam->Text)) == 0 ? AnsiString("\"h") : AnsiString("\"b");
			period3_goal_scorer += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[3]);
			period3_goal_ass1 += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[4]);
			period3_goal_ass2 += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[5]);
		}
		else if (AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->Caption.SubString(1, PeriodGoals->Items->Item[0]->Caption.Pos(":")-1)).AnsiCompare("20") > 0) {
			period2_first = false;
			period2_goal_time += startStr + PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->Caption;
			period2_goal += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[0]);
			period2_goal_teamStat += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[1]);
			period2_goal_team += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[2]).AnsiCompare(AnsiString(homeTeam->Text)) == 0 ? AnsiString("\"h") : AnsiString("\"b");
			period2_goal_scorer += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[3]);
			period2_goal_ass1 += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[4]);
			period2_goal_ass2 += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[5]);
		}
		else {
			period1_first = false;
			period1_goal_time += startStr + PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->Caption;
			period1_goal += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[0]);
			period1_goal_teamStat += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[1]);

			period1_goal_team += startStr;
			if(AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[2]).AnsiCompare(AnsiString(homeTeam->Text)) == 0) {
				period1_goal_team += AnsiString("h");
			}
			else {
				period1_goal_team += AnsiString("b");
            }


			period1_goal_scorer += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[3]);
			period1_goal_ass1 += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[4]);
			period1_goal_ass2 += startStr + AnsiString(PeriodGoals->Items->Item[PeriodGoals->Items->Count-1]->SubItems->Strings[5]);
		}
	}

	for(int goalIdx = PeriodGoals->Items->Count-2; goalIdx >= 0; goalIdx--) {
		  if (AnsiString(PeriodGoals->Items->Item[goalIdx]->Caption.SubString(1, PeriodGoals->Items->Item[0]->Caption.Pos(":")-1)).AnsiCompare("60") > 0) {
			if (false == period4_first) {
				period4_goal_time += "\", \"";
				period4_goal += "\", \"";
				period4_goal_teamStat += "\", \"";
				period4_goal_team += "\", \"";
				period4_goal_scorer += "\", \"";
				period4_goal_ass1 += "\", \"";
				period4_goal_ass2 += "\", \"";
			}
			else {
				period4_goal_time += startStr;
				period4_goal += startStr;
				period4_goal_teamStat += startStr;
				period4_goal_team += startStr;
				period4_goal_scorer += startStr;
				period4_goal_ass1 += startStr;
				period4_goal_ass2 += startStr;
			}
			period4_first = false;

			period4_goal_time += PeriodGoals->Items->Item[goalIdx]->Caption;
			period4_goal +=  AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[0]);
			period4_goal_teamStat +=  AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[1]);
			period4_goal_team += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[2]).AnsiCompare(AnsiString(homeTeam->Text)) == 0 ? "h" : "b";
			period4_goal_scorer += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[3]);
			period4_goal_ass1 +=  AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[4]);
			period4_goal_ass2 += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[5]);
		}
		else if (AnsiString(PeriodGoals->Items->Item[goalIdx]->Caption.SubString(1, PeriodGoals->Items->Item[0]->Caption.Pos(":")-1)).AnsiCompare("40") > 0) {
			if (false == period3_first) {
				period3_goal_time += "\", \"";
				period3_goal += "\", \"";
				period3_goal_teamStat += "\", \"";
				period3_goal_team += "\", \"";
				period3_goal_scorer += "\", \"";
				period3_goal_ass1 += "\", \"";
				period3_goal_ass2 += "\", \"";
			}
			else {
				period3_goal_time += startStr;
				period3_goal += startStr;
				period3_goal_teamStat += startStr;
				period3_goal_team += startStr;
				period3_goal_scorer += startStr;
				period3_goal_ass1 += startStr;
				period3_goal_ass2 += startStr;
			}
			period3_first = false;

			period3_goal_time += PeriodGoals->Items->Item[goalIdx]->Caption;
			period3_goal +=AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[0]);
			period3_goal_teamStat += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[1]);
			period3_goal_team += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[2]).AnsiCompare(AnsiString(homeTeam->Text)) == 0 ? "h" : "b";
			period3_goal_scorer += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[3]);
			period3_goal_ass1 += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[4]);
			period3_goal_ass2 += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[5]);
		}
		else if (AnsiString(PeriodGoals->Items->Item[goalIdx]->Caption.SubString(1, PeriodGoals->Items->Item[0]->Caption.Pos(":")-1)).AnsiCompare("20") > 0) {
		if (false == period2_first) {
				period2_goal_time += "\", \"";
				period2_goal += "\", \"";
				period2_goal_teamStat += "\", \"";
				period2_goal_team += "\", \"";
				period2_goal_scorer += "\", \"";
				period2_goal_ass1 += "\", \"";
				period2_goal_ass2 += "\", \"";
			}
			else {
				period2_goal_time += startStr;
				period2_goal += startStr;
				period2_goal_teamStat += startStr;
				period2_goal_team += startStr;
				period2_goal_scorer += startStr;
				period2_goal_ass1 += startStr;
				period2_goal_ass2 += startStr;
			}
			period2_first = false;

			period2_goal_time += PeriodGoals->Items->Item[goalIdx]->Caption;
			period2_goal += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[0]);
			period2_goal_teamStat += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[1]);
			period2_goal_team += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[2]).AnsiCompare(AnsiString(homeTeam->Text)) == 0 ? "h" : "b";
			period2_goal_scorer += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[3]);
			period2_goal_ass1 += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[4]);
			period2_goal_ass2 += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[5]);
		}
		else {
			if (false == period1_first) {
				period1_goal_time += "\", \"";
				period1_goal += "\", \"";
				period1_goal_teamStat += "\", \"";
				period1_goal_team += "\", \"";
				period1_goal_scorer += "\", \"";
				period1_goal_ass1 += "\", \"";
				period1_goal_ass2 += "\", \"";
			}
			else {
				period1_goal_time += startStr;
				period1_goal += startStr;
				period1_goal_teamStat += startStr;
				period1_goal_team += startStr;
				period1_goal_scorer += startStr;
				period1_goal_ass1 += startStr;
				period1_goal_ass2 += startStr;
			}
			period1_first = false;
			period1_goal_time += PeriodGoals->Items->Item[goalIdx]->Caption;
			period1_goal += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[0]);
			period1_goal_teamStat += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[1]);
			period1_goal_team += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[2]).AnsiCompare(AnsiString(homeTeam->Text)) == 0 ? "h" : "b";
			period1_goal_scorer += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[3]);
			period1_goal_ass1 += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[4]);
			period1_goal_ass2 += AnsiString(PeriodGoals->Items->Item[goalIdx]->SubItems->Strings[5]);
		}
	}

	if (!period1_first) {
		period1_goal_time += startStr;
		period1_goal += startStr;
		period1_goal_teamStat += startStr;
		period1_goal_team += startStr;
		period1_goal_scorer += startStr;
		period1_goal_ass1 += startStr;
		period1_goal_ass2 += startStr;
	}

	if (!period2_first) {
		period2_goal_time += startStr;
		period2_goal += startStr;
		period2_goal_teamStat += startStr;
		period2_goal_team += startStr;
		period2_goal_scorer += startStr;
		period2_goal_ass1 += startStr;
		period2_goal_ass2 += startStr;
	}

	if (!period3_first) {
		period3_goal_time += startStr;
		period3_goal += startStr;
		period3_goal_teamStat += startStr;
		period3_goal_team += startStr;
		period3_goal_scorer += startStr;
		period3_goal_ass1 += startStr;
		period3_goal_ass2 += startStr;
	}

	if (!period4_first) {
		period4_goal_time += startStr;
		period4_goal += startStr;
		period4_goal_teamStat += startStr;
		period4_goal_team += startStr;
		period4_goal_scorer += startStr;
		period4_goal_ass1 += startStr;
		period4_goal_ass2 += startStr;
	}

	AnsiString penaltys_stat = "";
	AnsiString penaltys_res = "";
	AnsiString penaltys_team = "";
	AnsiString penaltys_scorer = "";

	bool firstPenalty = true;

	for(int goalIdx = penaltys->Items->Count-1; goalIdx >= 0; goalIdx--) {
		if (!firstPenalty) {
			penaltys_stat += "\", \"";
			penaltys_res  += "\", \"";
			penaltys_team  += "\", \"";
			penaltys_scorer += "\", \"";
		}
		else {
			penaltys_stat += "\"";
			penaltys_res  += "\"";
			penaltys_team  += "\"";
			penaltys_scorer += "\"";
		}
		firstPenalty = false;
		penaltys_stat += AnsiString(penaltys->Items->Item[goalIdx]->Caption).AnsiCompare("Missed") == 0 ? AnsiString("Miss") : AnsiString("Mål");
		penaltys_res += AnsiString(penaltys->Items->Item[goalIdx]->SubItems->Strings[0]);
		penaltys_team += AnsiString(penaltys->Items->Item[goalIdx]->SubItems->Strings[1]).AnsiCompare(AnsiString(homeTeam->Text)) == 0 ? AnsiString("h") : AnsiString("b");
		penaltys_scorer += AnsiString(penaltys->Items->Item[goalIdx]->SubItems->Strings[2]);
	}

	if(!firstPenalty) {
    	penaltys_stat += "\"";
		penaltys_res  += "\"";
		penaltys_team  += "\"";
		penaltys_scorer += "\"";
    }

	out << std::endl;
	out << "var period1_goal_time = new Array(" << period1_goal_time.c_str() << ");" << std::endl;
	out << "var period1_goal_teamStat = new Array(" <<  period1_goal_teamStat.c_str() << ");" << std::endl;
	out << "var period1_goal= new Array(" << period1_goal.c_str() << ");" << std::endl;
	out << "var period1_goal_team = new Array(" << period1_goal_team.c_str() << ");" << std::endl;
	out << "var period1_scorer = new Array(" << period1_goal_scorer.c_str() << ");" << std::endl;
	out << "var period1_ass1 = new Array(" << period1_goal_ass1.c_str() << ");" << std::endl;
	out << "var period1_ass2 = new Array(" << period1_goal_ass2.c_str() << ");" << std::endl;

	out << std::endl;
	out << "var period2_goal_time = new Array(" << period2_goal_time.c_str() << ");" << std::endl;
	out << "var period2_goal_teamStat = new Array(" <<  period2_goal_teamStat.c_str() << ");" << std::endl;
	out << "var period2_goal= new Array(" << period2_goal.c_str() << ");" << std::endl;
	out << "var period2_goal_team = new Array(" << period2_goal_team.c_str() << ");" << std::endl;
	out << "var period2_scorer = new Array(" << period2_goal_scorer.c_str() << ");" << std::endl;
	out << "var period2_ass1 = new Array(" << period2_goal_ass1.c_str() << ");" << std::endl;
	out << "var period2_ass2 = new Array(" << period2_goal_ass2.c_str() << ");" << std::endl;

	out << std::endl;
	out << "var period3_goal_time = new Array(" << period3_goal_time.c_str() << ");" << std::endl;
	out << "var period3_goal_teamStat = new Array(" <<  period3_goal_teamStat.c_str() << ");" << std::endl;
	out << "var period3_goal= new Array(" << period3_goal.c_str() << ");" << std::endl;
	out << "var period3_goal_team = new Array(" << period3_goal_team.c_str() << ");" << std::endl;
	out << "var period3_scorer = new Array(" << period3_goal_scorer.c_str() << ");" << std::endl;
	out << "var period3_ass1 = new Array(" << period3_goal_ass1.c_str() << ");" << std::endl;
	out << "var period3_ass2 = new Array(" << period3_goal_ass2.c_str() << ");" << std::endl;

	out << std::endl;
	out << "var period4_goal_time = new Array(" << period4_goal_time.c_str() << ");" << std::endl;
	out << "var period4_goal_teamStat = new Array(" <<  period4_goal_teamStat.c_str() << ");" << std::endl;
	out << "var period4_goal= new Array(" << period4_goal.c_str() << ");" << std::endl;
	out << "var period4_goal_team = new Array(" << period4_goal_team.c_str() << ");" << std::endl;
	out << "var period4_scorer = new Array(" << period4_goal_scorer.c_str() << ");" << std::endl;
	out << "var period4_ass1 = new Array(" << period4_goal_ass1.c_str() << ");" << std::endl;
	out << "var period4_ass2 = new Array(" << period4_goal_ass2.c_str() << ");" << std::endl;


	// TODO, period statistik skriver åt fel hål. börjar med det senaste och sist det första.
	// skriv om kod till length som första sen 0 som sista

   out << std::endl;

   out << "var penalties_stat = new Array(" << penaltys_stat.c_str() << ");" << std::endl;
   out << "var penalties_res = new Array(" << penaltys_res.c_str() << ");" << std::endl;
   out << "var penalties_team = new Array(" << penaltys_team.c_str() << ");" << std::endl;
   out << "var penalties_scorer = new Array(" << penaltys_scorer.c_str() << ");" << std::endl;

    out << std::endl << std::endl;


//	FileExists("scriptBase.txt");
	treeForm->Memo1->Lines->LoadFromFile("scriptBase.jsx");


	for(int i = 0; i < treeForm->Memo1->Lines->Count; i++) {
		out << AnsiString(treeForm->Memo1->Lines->Strings[i]).c_str() << std::endl;
	}
	out.close();

}
//---------------------------------------------------------------------------



/*
swestat länkar för test. TAIF hemmamatcher tidigare
http://stats.swehockey.se/Game/Events/206712  x
http://stats.swehockey.se/Game/Events/206724  x  Kumla fungerar inte i straffsumeringen
http://stats.swehockey.se/Game/Events/206736
http://stats.swehockey.se/Game/Events/206748
http://stats.swehockey.se/Game/Events/206760
http://stats.swehockey.se/Game/Events/206766
http://stats.swehockey.se/Game/Events/206788
http://stats.swehockey.se/Game/Events/206799
http://stats.swehockey.se/Game/Events/206838

http://stats.swehockey.se/Game/Events/246271
http://stats.swehockey.se/Game/Events/246294





TODO

fungerar iteration av straff när det ändrar ordning efter tre vardera
Kontrollera alla Lag logos, att det finns med jämfört mot det som står i swestat  (kumla fungerar inte i straffsumeringen)

// TODO när jag hinner
Kontrollera att det är svenska överallt i grafiken som rendreras
Kolla upp while satserna, verkar inte fungera med while (pos = substring.Pos(";") != 0)
Resultatet, det hämtas inte från swestat, får skrivas in manuellt än så länge.

vad händer om det är mer än tio straffar, eller mer än sju mål. Måste skapa en ny och fixa antar jag.
fundera på om straff mål ska stå straff 1,2,3... eller 1,1,2,2,3,3..
hantera taif bortamatcher
strukturera upp efter funktioner


// TODO, färdigt
summering av straff skrivs utan att det finns straffar att skriva
Skottstatestik, är ett för mycket mellanslag (.-..) tror jag det var
Justera upp "Summary period x" så det blir centrerat.
Justera upp färgerna i summary texten
Fixa till färgmarkeringen av skottstatestik och centrerat
Gulmarkering  straffsummeringen
Gulmarkering för spelare, se till att gula punkten också.
Fixa straffgrafik
fixa straffsumering
Alla tomma arrayer får inte vara new array = (""), måste vara new array()
Resulatata, finns inte med i ruta i progg, så får skriva det manuellt i kod.
Resultatdata, hämta från title texten
Skrivs ibland en tom bild, utan namngivning, vad är det ?
Släck alla lager som ska hanteras av script


*/
