//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <conio.h>

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
    imgPlayer1->Picture->LoadFromFile("Rock.jpg");
    imgPlayer2->Picture->LoadFromFile("Rock.jpg");
    // imgPlayer1->Picture = NULL;
    // imgPlayer2->Picture = NULL;
	srand ( time ( 0 ) );
    txtStart->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuAboutClick(TObject *Sender)
{
    Application->MessageBox(
		"�������\n\r"
		 "\t�ҧ��� �ѭ��Ѱ\t�ʹ���\n\r" \
		 "\t�ҧ��� �á��\t�ح��\n\r" \
		 "\t��� ǧȸ�\t\t��ó���\n\r",
		"��� ��� �غ (Pao Ying Chup)",
        MB_OK + MB_ICONINFORMATION);
}

//---------------------------------------------------------------------------
/*
	Truth table of Pao Ying Chup
	
	Result			Rock		Scissors		Paper
	-------------------------------------------------------
	Rock			Equal(0)	Win(1)			Lose(-1)
	
	Scissors		Lose(-1)	Equal(0)		Win(1)

	Paper			Win(1)		Lose(-1)		Equal(0)

*/

// Global variable of Application.

AnsiString Player1 = "A" , Player2 = "B";
int Player1_score = 0 , Player2_score = 0;
int round_game = 10 , count_of_round;

enum { IDLE , STANDBY_2PLAYER , PLAY_2PLAYER , STANDBY_COMP , PLAY_COMP };
enum { NONE , ROCK , SCISSORS , PAPER };
enum { EQU = 0 , WIN = 1, LOSE = -1 };

const int player_result[3][3] = {
	{  EQU   ,  WIN  , LOSE } ,
	{  LOSE  ,  EQU  , WIN } ,
	{  WIN  ,   LOSE , EQU }
};

int state = IDLE;
int p1,p2;

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuPlayer12Click(TObject *Sender)
{
    AnsiString number;

    Player1 = InputBox("�����蹤���� 1","��سҡ�͡���ͧ͢�س ?",Player1);
    txtPlayer1->Caption = Player1;
    txtPlayer_1->Caption = Player1;
    Player2 = InputBox("�����蹤���� 2","��سҡ�͡���ͧ͢�س ?",Player2);
    txtPlayer2->Caption = Player2;
    txtPlayer_2->Caption = Player2;
    number = InputBox("�Ӷ��","�ӹǹ��  ?",round_game);
	round_game = number.ToInt();
    txtGameCount->Caption = round_game;

	state = STANDBY_2PLAYER;
	imgPlayer1->Picture = NULL;
	imgPlayer2->Picture = NULL;
    Player1_score = Player2_score = 0;
	count_of_round = 1;
	txtGameCount->Caption = count_of_round;
    txtStart->Visible = true;
    return;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuNewPlayComputerClick(TObject *Sender)
{
	AnsiString number;

    Player1 = InputBox("���ͼ�����","��سҡ�͡���ͧ͢�س ?",Player1);
    txtPlayer1->Caption = Player1;
    txtPlayer_1->Caption = Player1;
	Player2 = "Computer";
    txtPlayer2->Caption = Player2;
    txtPlayer_2->Caption = Player2;

	number = InputBox("�Ӷ��","�ӹǹ��  ?",round_game);
	round_game = number.ToInt();
    txtGameCount->Caption = round_game;	
	state = STANDBY_COMP;
	imgPlayer1->Picture = NULL;
	imgPlayer2->Picture = NULL;
    Player1_score = Player2_score = 0;
	count_of_round = 1;
	txtGameCount->Caption = count_of_round;
    txtStart->Visible = true;
    return;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmuHowPlayClick(TObject *Sender)
{
    Application->MessageBox(
		"�����蹤���� 1\n\r�� 'Q' �����͡ ��͹\n\r��  'A' �����͡ �����\n\r�� 'Z' �����͡ ��д��\n\r\n\r"
		"�����蹤���� 2 \n\r�� '9' �����͡ ��͹\n\r��  '6' �����͡ �����\n\r�� '3' �����͡ ��д��\n\r"
		, "�Ըա�����" ,
		MB_OK + MB_ICONINFORMATION);

    return;
}

//---------------------------------------------------------------------------
    int __fastcall TfrmMain::PlayerResult(int py1,int py2)
    {
    	int result;
        AnsiString ans;

		result = player_result [py1-1][py2-1];
		if ( result == WIN )
			Player1_score++;
		ans = Player1 + " : " + IntToStr( Player1_score );
		txtPlayer1->Caption = ans;

		result = player_result [py2-1][py1-1];
		if ( result == WIN )
			Player2_score++;
		ans = Player2 + " : " + IntToStr( Player2_score );
            txtPlayer2->Caption = ans;

		txtGameCount->Caption = count_of_round;
		if ( count_of_round >= round_game ) {

            txtStart->Visible = false;
			if ( Player1_score == Player2_score ) {
				Application->MessageBox( "���͡ѹ" , "��ػ" ,
					MB_OK + MB_ICONINFORMATION );
			} else {
				if ( Player1_score > Player2_score ) {
					ans = Player1 + " ���.";
					Application->MessageBox( ans.c_str() , "��ػ",
						MB_OK + MB_ICONINFORMATION );
				} else {
					ans = Player2 + " ���.";
					Application->MessageBox( ans.c_str() , "��ػ",
						MB_OK + MB_ICONINFORMATION );
				}
			}

            // Clear picture
			imgPlayer1->Picture = NULL;
			imgPlayer2->Picture = NULL;
			state = IDLE;
			return 0;
		}

		count_of_round ++;
        return 1;
    }
//---------------------------------------------------------------------------
#define     ENTER_KEY       (13)

void __fastcall TfrmMain::FormKeyPress(TObject *Sender, char &Key)
{
    char k;
    AnsiString ans;
    unsigned r;

    k = Key;
    switch ( state ) {
    // Idle mode
	case IDLE :
		break;
    // Standby mode of 2player
    case STANDBY_2PLAYER :
        switch ( k ) {
        case ' ' :
        case ENTER_KEY :
            imgPlayer1->Picture->LoadFromFile("Start.jpg");
            imgPlayer2->Picture->LoadFromFile("Start.jpg");
            state = PLAY_2PLAYER;
            p1 = p2 = NONE;
            txtStart->Visible = false;
            break;
        }
        break;

    // Player1 and Plyer2 play.
    case PLAY_2PLAYER :
		switch ( k ) {
		case 'Q' :
		case 'q' :
			p1 = ROCK;
			break;
		case 'A' :
		case 'a' :
			p1 = SCISSORS;
			break;
		case 'Z' :
		case 'z' :
			p1 = PAPER;
			break;
		case '9' :
			p2 = ROCK;
			break;
		case '6' :
			p2 = SCISSORS;
			break;
		case '3' :
			p2 = PAPER;
			break;
		default :
			return;
		}

        if ( p1 && p2 ) {
            txtStart->Visible = true;
			// Display Player1
			switch ( p1 ) {
			case ROCK :
				imgPlayer1->Picture->LoadFromFile("Rock.jpg");
				break;
			case SCISSORS :
				imgPlayer1->Picture->LoadFromFile("Scissors.jpg");
				break;
			case PAPER :
				imgPlayer1->Picture->LoadFromFile("Paper.jpg");
				break;
			}
			// Display Player2
			switch( p2 ) {
			case ROCK :
				imgPlayer2->Picture->LoadFromFile("Rock.jpg");
				break;
			case SCISSORS :
				imgPlayer2->Picture->LoadFromFile("Scissors.jpg");
				break;
			case PAPER :
				imgPlayer2->Picture->LoadFromFile("Paper.jpg");
				break;
			}

			state = STANDBY_2PLAYER;
			PlayerResult ( p1 , p2 );
        }
        break;

    // Standby mode of play with computer
	case STANDBY_COMP :
		switch ( k ) {
		case ' ' :
        case ENTER_KEY :
            imgPlayer1->Picture->LoadFromFile("Start.jpg");
            imgPlayer2->Picture->LoadFromFile("Start.jpg");
            state = PLAY_COMP;
			p1 = NONE;
            txtStart->Visible = false;
			break;
		}
		break;

    // Play with Computer
	case PLAY_COMP :
		switch ( k ) {
		case 'Q' :
		case 'q' :
		case '9' :
			imgPlayer1->Picture->LoadFromFile("Rock.jpg");
			p1 = ROCK;
			break;
		case 'A' :
		case 'a' :
		case '6' :
			imgPlayer1->Picture->LoadFromFile("Scissors.jpg");
			p1 = SCISSORS;
			break;
		case 'Z' :
		case 'z' :
		case '3' :
			imgPlayer1->Picture->LoadFromFile("Paper.jpg");
			p1 = PAPER;
			break;
		default :
			return;
		}

        txtStart->Visible = true;
        // Randomize
        p2 = ( rand () % 3 ) + ROCK;

		switch ( p2 ) {
		case ROCK :
			imgPlayer2->Picture->LoadFromFile("Rock.jpg");
			break;
		case SCISSORS :
			imgPlayer2->Picture->LoadFromFile("Scissors.jpg");
			break;
		case PAPER :
			imgPlayer2->Picture->LoadFromFile("Paper.jpg");
			break;
		}

		state = STANDBY_COMP;
		PlayerResult ( p1 , p2 );
		break;

    default :
        return;
    }
    return;
}
//---------------------------------------------------------------------------

