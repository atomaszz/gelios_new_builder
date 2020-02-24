//---------------------------------------------------------------------------

#ifndef redact_fH
#define redact_fH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include <Tabnotbk.hpp>
#include <Graphics.hpp>
#include "uBaseShape.h"
//---------------------------------------------------------------------------
class Tredact_char : public TForm
{
__published:	// IDE-managed Components
        TBevel *Bevel2;
        TButton *Button6;
        TButton *Button7;
        TEdit *Edit1;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label24;
        TEdit *Edit13;
        TTabbedNotebook *TabbedNotebook1;
        TEdit *Edit2;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *Edit3;
        TLabel *Label7;
        TEdit *Edit4;
        TBevel *Bevel1;
        TBevel *Bevel3;
        TLabel *Label8;
        TEdit *Edit6;
        TLabel *Label9;
        TEdit *Edit5;
        TEdit *Edit8;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *Edit7;
        TBevel *Bevel4;
        TLabel *Label13;
        TEdit *Edit9;
        TLabel *Label14;
        TEdit *Edit10;
        TEdit *Edit12;
        TLabel *Label16;
        TLabel *Label17;
        TEdit *Edit11;
        TBevel *Bevel6;
        TEdit *Edit14;
        TLabel *Label27;
        TLabel *Label1;
        TComboBox *ComboBox1;
        TBevel *Bevel5;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label28;
        TLabel *Label29;
        TEdit *Edit15;
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TImage *Image6;
        TEdit *Edit16;
        TEdit *Edit17;
        TEdit *Edit18;
        TEdit *Edit19;
        TEdit *Edit20;
        TEdit *Edit21;
        TEdit *Edit22;
        TEdit *Edit23;
        TEdit *Edit24;
        TEdit *Edit25;
        TEdit *Edit26;
        TEdit *Edit27;
        TEdit *Edit28;
        TEdit *Edit29;
        TEdit *Edit30;
        TEdit *Edit31;
        TEdit *Edit32;
        TLabel *Label21;
        TImage *Image9;
        TEdit *Edit34;
        TLabel *Label25;
        TLabel *Label30;
        TBevel *Bevel7;
        TLabel *Label31;
        TLabel *Label32;
        TEdit *Edit36;
        TEdit *Edit37;
        TEdit *Edit38;
        TEdit *Edit39;
        TEdit *Edit40;
        TEdit *Edit41;
        TEdit *Edit42;
        TEdit *Edit43;
        TEdit *Edit44;
        TEdit *Edit45;
        TEdit *Edit46;
        TEdit *Edit47;
        TEdit *Edit48;
        TEdit *Edit49;
        TEdit *Edit50;
        TEdit *Edit51;
        TEdit *Edit52;
        TEdit *Edit53;
        TLabel *Label33;
        TLabel *Label34;
        TLabel *Label35;
        TLabel *Label36;
        TLabel *Label37;
        TLabel *Label38;
        TEdit *Edit54;
        TEdit *Edit55;
        TEdit *Edit56;
        TEdit *Edit57;
        TEdit *Edit58;
        TEdit *Edit59;
        TLabel *Label39;
        TLabel *Label40;
        TBevel *Bevel8;
        TLabel *Label41;
        TLabel *Label42;
        TEdit *Edit68;
        TEdit *Edit67;
        TEdit *Edit66;
        TEdit *Edit65;
        TEdit *Edit64;
        TEdit *Edit63;
        TLabel *Label43;
        TLabel *Label44;
        TEdit *Edit69;
        TEdit *Edit70;
        TEdit *Edit71;
        TEdit *Edit72;
        TEdit *Edit73;
        TEdit *Edit74;
        TEdit *Edit80;
        TEdit *Edit79;
        TEdit *Edit78;
        TEdit *Edit77;
        TEdit *Edit76;
        TEdit *Edit75;
        TLabel *Label45;
        TLabel *Label46;
        TLabel *Label47;
        TLabel *Label48;
        TEdit *Edit81;
        TEdit *Edit82;
        TEdit *Edit83;
        TEdit *Edit84;
        TEdit *Edit85;
        TEdit *Edit86;
        TLabel *Label49;
        TImage *Image10;
        TImage *Image11;
        TImage *Image12;
        TImage *Image13;
        TImage *Image14;
        TImage *Image15;
        TImage *Image19;
        TImage *Image20;
        TImage *Image21;
        TImage *Image22;
        TImage *Image23;
        TImage *Image24;
        TLabel *Label15;
        TLabel *Label50;
        TLabel *Label10;
        TLabel *Label51;
        TLabel *Label52;
        TImage *Image7;
        TLabel *Label53;
        TEdit *Edit33;
        TImage *Image8;
        TLabel *Label54;
        TEdit *Edit35;
        TButton *Button1;
        TButton *Button2;
        TBevel *Bevel9;
        TLabel *Label4;
        TEdit *Edit60;
        TEdit *Edit61;
        TEdit *Edit62;
        TEdit *Edit87;
        TEdit *Edit88;
        TEdit *Edit89;
        TEdit *Edit91;
        TLabel *Label58;
        TLabel *Label59;
        TLabel *Label60;
        TLabel *Label61;
        TLabel *Label26;
        TLabel *Label56;
        TLabel *Label57;
        TComboBox *ComboBox2;
        TBevel *Bevel10;
        TComboBox *ComboBox3;
        TLabel *Label62;
        TEdit *Edit90;
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Edit2Exit(TObject *Sender);
        void __fastcall Edit6Exit(TObject *Sender);
        void __fastcall Edit5Exit(TObject *Sender);
        void __fastcall Edit9Exit(TObject *Sender);
        void __fastcall Edit10Exit(TObject *Sender);
        void __fastcall Edit3Exit(TObject *Sender);
        void __fastcall Edit4Exit(TObject *Sender);
        void __fastcall Edit8Exit(TObject *Sender);
        void __fastcall Edit7Exit(TObject *Sender);
        void __fastcall Edit12Exit(TObject *Sender);
        void __fastcall Edit11Exit(TObject *Sender);
        void __fastcall TabbedNotebook1Change(TObject *Sender, int NewTab,
          bool &AllowChange);
        void __fastcall Edit15Exit(TObject *Sender);
        void __fastcall Edit16Exit(TObject *Sender);
        void __fastcall Edit17Exit(TObject *Sender);
        void __fastcall Edit18Exit(TObject *Sender);
        void __fastcall Edit19Exit(TObject *Sender);
        void __fastcall Edit20Exit(TObject *Sender);
        void __fastcall Edit21Exit(TObject *Sender);
        void __fastcall Edit22Exit(TObject *Sender);
        void __fastcall Edit23Exit(TObject *Sender);
        void __fastcall Edit24Exit(TObject *Sender);
        void __fastcall Edit25Exit(TObject *Sender);
        void __fastcall Edit26Exit(TObject *Sender);
        void __fastcall Edit27Exit(TObject *Sender);
        void __fastcall Edit28Exit(TObject *Sender);
        void __fastcall Edit29Exit(TObject *Sender);
        void __fastcall Edit30Exit(TObject *Sender);
        void __fastcall Edit31Exit(TObject *Sender);
        void __fastcall Edit32Exit(TObject *Sender);
        void __fastcall Edit36Exit(TObject *Sender);
        void __fastcall Edit37Exit(TObject *Sender);
        void __fastcall Edit38Exit(TObject *Sender);
        void __fastcall Edit39Exit(TObject *Sender);
        void __fastcall Edit40Exit(TObject *Sender);
        void __fastcall Edit41Exit(TObject *Sender);
        void __fastcall Edit42Exit(TObject *Sender);
        void __fastcall Edit43Exit(TObject *Sender);
        void __fastcall Edit44Exit(TObject *Sender);
        void __fastcall Edit45Exit(TObject *Sender);
        void __fastcall Edit46Exit(TObject *Sender);
        void __fastcall Edit47Exit(TObject *Sender);
        void __fastcall Edit48Exit(TObject *Sender);
        void __fastcall Edit49Exit(TObject *Sender);
        void __fastcall Edit50Exit(TObject *Sender);
        void __fastcall Edit51Exit(TObject *Sender);
        void __fastcall Edit52Exit(TObject *Sender);
        void __fastcall Edit53Exit(TObject *Sender);
        void __fastcall Edit54Exit(TObject *Sender);
        void __fastcall Edit55Exit(TObject *Sender);
        void __fastcall Edit56Exit(TObject *Sender);
        void __fastcall Edit57Exit(TObject *Sender);
        void __fastcall Edit58Exit(TObject *Sender);
        void __fastcall Edit59Exit(TObject *Sender);
        void __fastcall Edit63Exit(TObject *Sender);
        void __fastcall Edit64Exit(TObject *Sender);
        void __fastcall Edit65Exit(TObject *Sender);
        void __fastcall Edit66Exit(TObject *Sender);
        void __fastcall Edit67Exit(TObject *Sender);
        void __fastcall Edit68Exit(TObject *Sender);
        void __fastcall Edit69Exit(TObject *Sender);
        void __fastcall Edit70Exit(TObject *Sender);
        void __fastcall Edit71Exit(TObject *Sender);
        void __fastcall Edit72Exit(TObject *Sender);
        void __fastcall Edit73Exit(TObject *Sender);
        void __fastcall Edit74Exit(TObject *Sender);
        void __fastcall Edit75Exit(TObject *Sender);
        void __fastcall Edit76Exit(TObject *Sender);
        void __fastcall Edit77Exit(TObject *Sender);
        void __fastcall Edit78Exit(TObject *Sender);
        void __fastcall Edit79Exit(TObject *Sender);
        void __fastcall Edit80Exit(TObject *Sender);
        void __fastcall Edit81Exit(TObject *Sender);
        void __fastcall Edit82Exit(TObject *Sender);
        void __fastcall Edit83Exit(TObject *Sender);
        void __fastcall Edit84Exit(TObject *Sender);
        void __fastcall Edit85Exit(TObject *Sender);
        void __fastcall Edit86Exit(TObject *Sender);
        void __fastcall Edit91Exit(TObject *Sender);
        void __fastcall Edit89Exit(TObject *Sender);
        void __fastcall Edit88Exit(TObject *Sender);
        void __fastcall Edit87Exit(TObject *Sender);
        void __fastcall Edit62Exit(TObject *Sender);
        void __fastcall Edit61Exit(TObject *Sender);
        void __fastcall Edit60Exit(TObject *Sender);
private:	// User declarations
  bool f_Can_list;
  int f_Type_Char;
  TParamAlternativeItem* f_PAItem;
  TBaseShape* f_TFE;
public:		// User declarations

        __fastcall Tredact_char(TComponent* Owner);
        //функция проверки правильности ввода характеристик
        int  check_table();

        //проверка правильности ввода значений типа float
        int  Exit_Edit(TEdit *E);

        //сохранение вероятностных параметров
        void save_char_prop();
        //сохранение нечетких параметров
        void save_char_fuzzy();
        void show_char_prop();
        void show_char_fuzzy();

        //установка недоступности редактирования нечетких характеристик
        void enable_false(int type);
       //установка доступности редактирования нечетких характеристик
        void enable_true(int type);

        //проверка того, чтобы нижняя граница была меньше по значению чем верхняя
        int  compare_char_fuzzy();
        int exit_proverka_0_1(TEdit *Edit);

        __property int Type_Char = {read = f_Type_Char, write = f_Type_Char};
        __property TParamAlternativeItem* PAItem = {read = f_PAItem, write =  f_PAItem};
        __property TBaseShape* TFE = {read = f_TFE, write = f_TFE};
        __property bool Can_list = {read = f_Can_list, write = f_Can_list};


};
void ShowParamAlternativeEditor(TBaseShape* ATFE, TParamAlternativeItem* AItem,  int AType_Char, bool ACan_list);
//---------------------------------------------------------------------------
extern PACKAGE Tredact_char *redact_char;
//---------------------------------------------------------------------------
#endif
