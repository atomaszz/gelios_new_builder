//---------------------------------------------------------------------------

#ifndef opim_fH
#define opim_fH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.TabNotBk.hpp>
#include "uCommonGraph.h"
#include "uDischargedMassiv.h"

//---------------------------------------------------------------------------
class Topt_sadacha : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TImageList *ImageList2;
	TBevel *Bevel1;
	TCheckBox *CheckBox1;
	TLabel *Label1;
	TImage *Image1;
	TLabel *Label2;
	TImage *Image2;
	TLabel *Label31;
	TLabel *Label32;
	TBevel *Bevel2;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TCheckBox *CheckBox7;
	TCheckBox *CheckBox8;
	TCheckBox *CheckBox9;
	TButton *btShowGridSovm;
	TBevel *Bevel3;
	TTabbedNotebook *TabbedNotebook1;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *Edit4;
	TEdit *Edit5;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *Edit6;
	TEdit *Edit7;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TEdit *Edit8;
	TEdit *Edit9;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TEdit *Edit10;
	TEdit *Edit11;
	TEdit *Edit12;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label26;
	TLabel *Label28;
	TLabel *Label30;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TLabel *Label25;
	TLabel *Label27;
	TLabel *Label29;
	TEdit *Edit13;
	TEdit *Edit14;
	TEdit *Edit15;
	TLabel *Label3;
	TPanel *Panel1;
	TButton *Button1;
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall CheckBox4Click(TObject *Sender);
	void __fastcall CheckBox5Click(TObject *Sender);
	void __fastcall CheckBox6Click(TObject *Sender);
	void __fastcall CheckBox7Click(TObject *Sender);
	void __fastcall CheckBox8Click(TObject *Sender);
	void __fastcall CheckBox9Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Edit4Exit(TObject *Sender);
	void __fastcall Edit5Exit(TObject *Sender);
	void __fastcall Edit6Exit(TObject *Sender);
	void __fastcall Edit7Exit(TObject *Sender);
	void __fastcall Edit8Exit(TObject *Sender);
	void __fastcall Edit9Exit(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Edit10Exit(TObject *Sender);
	void __fastcall Edit11Exit(TObject *Sender);
	void __fastcall Edit12Exit(TObject *Sender);
	void __fastcall Edit13Exit(TObject *Sender);
	void __fastcall Edit14Exit(TObject *Sender);
	void __fastcall Edit15Exit(TObject *Sender);
	void __fastcall TabbedNotebook1Change(TObject *Sender, int NewTab, bool &AllowChange);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Edit2Exit(TObject *Sender);
	void __fastcall Edit3Exit(TObject *Sender);
	void __fastcall btShowGridSovmClick(TObject *Sender);

private:	// User declarations
        int f_TypeMetod;
        void CheckCol();
        void LoadData();
        void SaveData();
public:		// User declarations
	__fastcall Topt_sadacha(TComponent* Owner);
        short type_sadacha; //выбранный тип задачи оптимизации
        short type_ogr;     //выбранный тип ограничений
        bool can_list;
        int type_char;
        AnsiString c1,c2,c3;     //коэффициенты, нужные для задач 4-6
        AnsiString Bd,Td,Vd;     //коэффициенты, нужные для задач 1-3
        TDynamicArray *MassWork;
        TDischargedMassiv *OptSovm;
        double Rate;
        //получение картинки задачи в зависимости от выбора
		void _fastcall what_sadacha_check(int i);
		//отображение выблранной задачи в предикатной модели
		AnsiString  make_sadacha();
		AnsiString  make_ogrsovm();
		int __fastcall exit_proverka_simb(TEdit *Edit);
		int __fastcall exit_proverka_0_1(TEdit *Edit);
		int __fastcall exit_proverka_1_1(TEdit *Edit);
		int __fastcall exit_proverka_b_0(TEdit *Edit);

		void all_visible_false(void);
		void __fastcall ydal(int k);
		void InitData();
		int get_type_metod();
		void set_type_metod(int typ);
		int type_t_v();
		bool InOgrSovm(int ATFE_ID);

};
//---------------------------------------------------------------------------
extern PACKAGE Topt_sadacha *opt_sadacha;
//---------------------------------------------------------------------------
#endif
