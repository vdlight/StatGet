//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
#include<iostream>

#include<fstream>

//#include<cstring>

#include<wininet.h>



//#include <string>

//using namespace std;

__fastcall TForm1::TForm1(TComponent* Owner)  : TForm(Owner) {
	ofstream output;

	setlocale(LC_ALL, "3C");

	output.open("test.txt");

	if (!output.is_open()) {
		int a = 2;
	}

	HINTERNET connect = InternetOpen(String("MyBrowser").c_str(),INTERNET_OPEN_TYPE_PRECONFIG,NULL, NULL, 0);

	if(!connect){
		std::cout <<"Connection Failed or Syntax error";
	}

	HINTERNET OpenAddress = InternetOpenUrl(connect,String("http://stats.swehockey.se/Game/Events/246404").c_str(), NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE|INTERNET_FLAG_KEEP_CONNECTION, 0);



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


	bnla();
}

void TForm1::bnla(void) {
	int startPos;
	int endPos;
    ofstream output;


 /*	deleteStr("<script>", "</script>");
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
	output.close();*/

	// för lag och slutresultat, sök efter <TITLE> och </TITLE>, där imellan står det lag och reultat
	// för skott. sök efter shots. sedan "(" och ")", där står skotten för varje per

	test();
	/*
	// sök efter period. backa till taggen
	int searchPos = rawHTML.Pos("period");
	int lastSearchPos;
	startPos = searchPos;
	endPos = searchPos;
	AnsiString readStr;

	while(rawHTML[--startPos] != '>');
	startPos++; // start is char after searched one
	while(rawHTML[++endPos] != '<');

	readStr = rawHTML.SubString(startPos, endPos-startPos);


	if (readStr.AnsiCompare("1st period") == 0) {

	}
	else if (readStr.AnsiCompare("2nd period") == 0) {

	}
	else if (readStr.AnsiCompare("3rd period") == 0) {
		// händelser sker, från o med nästa rad.
		// sök slut på rad
		lastSearchPos = searchPos;
		searchPos = rawHTML.SubString(lastSearchPos, rawHTML.Length()).Pos("</tr>");
		lastSearchPos = searchPos + 4;
//		searchPos = rawHTML.SubString()


	}




	// 3rd period = tredje osv..
	// sök efter period. backa till taggen
	// 2rd period = spara pos, så jag vet att vi bytt period
	// sök efter period. backa till taggen
	// 1st period = spara pos, så jag vet att vi bytt period



	// sök efter nästa rad <tr>
	// sök efter nästa "<td" > ska vara tid  t.ex 60:00
	// sök efter nästa "<td" > ska vara händelse t.ex GK Out
		// om datat innehåller PP1 PP2 SH1 SH2 EQ, ENG så är det mål
			// sök efter nästa "<td" > ska vara lag. tex KAL
			// sök efter nästa "<td" > ska vara spelare


  */

}
void TForm1::test(void) {
	int parentNode = 0;
	int nodeCnt = 0;
	int treeDepthParents[50] = {0};
    int currentParent = 0;
	TreeView1->Items->Clear();

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
	TreeView1->Items->Add(NULL, "HTML Base");
	buff = rawHTML;

	// raw html har felet
//  1414 P
//	1415 i
//	1416 t
//	1417 e
//	1418 å  funkar ej

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
					if (isWhiteSpace(data[data.Length()]) || isBadChar(data.Length())) {
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

			currentNode = TreeView1->Items->AddChild(TreeView1->Items->Item[treeDepthParents[currentParent]], tag.c_str());
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

bool TForm1::isWhiteSpace(char c) {
	if (c == char(0xA0) || c == char(0x20)) {
		return true;
	}
	return false;
}bool TForm1::isBadChar(char c) {	if (c == '\r' || c == '\n' || c == char(0xC2)) {
		return true;
	}
	return false;
}bool TForm1::tagIsNewParent(AnsiString str) {	if (str.AnsiCompare("td") == 0 || str.AnsiCompare("div") == 0		|| str.AnsiCompare("h1") == 0 || str.AnsiCompare("h2") == 0		|| str.AnsiCompare("h3") == 0 || str.AnsiCompare("strong") == 0		|| str.AnsiCompare("span") == 0 || str.AnsiCompare("th") == 0) {		return false;	}	return true;}

void TForm1::deleteStr(AnsiString startStr, AnsiString endStr) {
	int startPos;
	int endPos;
	int startStrLen;
	int endStrLen;

  //	rawHTML = "abcdefg hij klmnop";
   //	startStr = "cd";
   //	endStr = "m";

	while(0 != (startPos = rawHTML.Pos(startStr))) {

		startStrLen = startStr.Length();
		endStrLen = endStr.Length();

		endPos = rawHTML.SubString(startPos+startStrLen, rawHTML.Length()).Pos(endStr);


		AnsiString debug1 = rawHTML.SubString(startPos, endPos);

		rawHTML.Delete(startPos, startStr.Length() + endPos + endStr.Length()-1);
	}
}
