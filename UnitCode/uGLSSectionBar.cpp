//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGLSSectionBar.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void DrawRect(TCanvas *Canvas, TRect R, bool Raised )
{
  if (Raised)
    DrawEdge(Canvas->Handle, &R, EDGE_RAISED , BF_RECT | BF_SOFT);
  else
    DrawEdge(Canvas->Handle, &R,  EDGE_SUNKEN , BF_RECT | BF_SOFT);
}


// ======= TSectionBarBaseItem =======================

__fastcall TSectionBarBaseItem::TSectionBarBaseItem(TCollection* Collection):TCollectionItem(Collection)
{
   InitProperties();
   Changed();
}


void TSectionBarBaseItem::InitProperties()
{
   FCaption = "";
   FVisible = true;
   FEnabled = true;
}


__fastcall  TSectionBarBaseItem::~TSectionBarBaseItem()
{
   TSectionBarBaseCollection *C;
   C = dynamic_cast<TSectionBarBaseCollection*>(Collection);
   if (C) C->Changed();
}


void __fastcall TSectionBarBaseItem::Assign(TPersistent *Source)
{
   TSectionBarBaseItem* C;
   TCollectionItem::Assign(Source);
   C = dynamic_cast<TSectionBarBaseItem*>(Source);
   if (C)
   {
      Caption = C->Caption;
      Visible = C->Visible;
      Enabled = C->Enabled;
      Tag = C->Tag;

   }
}

void TSectionBarBaseItem::Changed()
{
   TSectionBarBaseCollection *C;
   C = dynamic_cast<TSectionBarBaseCollection*>(Collection);
   if (C) C->Changed();
}


String __fastcall TSectionBarBaseItem::GetDisplayName()
{
   return Caption;
}


void __fastcall TSectionBarBaseItem::SetVisible(bool AVisible)
{
   if (AVisible != FVisible)
   {
     FVisible = AVisible;
     Changed();
   }
}


void __fastcall TSectionBarBaseItem::SetEnabled(bool AEnabled)
{
   if (AEnabled != FEnabled)
   {
     FEnabled = AEnabled;
     Changed();
   }
}


void __fastcall TSectionBarBaseItem::SetCaption(String ACaption)
{
   if (ACaption != FCaption)
   {
     FCaption = ACaption;
     Changed();
   }
}


void __fastcall TSectionBarBaseItem::SetTag(const int Value)
{
   if (FTag != Value)
   {
     FTag = Value;
     Changed();
   }
}


// ======= TSectionBarBaseCollection =======================
__fastcall TSectionBarBaseCollection::TSectionBarBaseCollection(TCollectionItemClass ItemClass):TCollection(ItemClass)
{
}

void TSectionBarBaseCollection::ButtonChanging(TSectionBarButton *NewButton)
{

}


void TSectionBarBaseCollection::ButtonChanged(TSectionBarButton *NewButton)
{

}



// ======= TSectionBarButton =======================

void  TSectionBarButton::InitProperties()
{
   TSectionBarBaseItem::InitProperties();
   Caption = "Новая кнопка";
   FSelected = false;
   FDown = false;
   FTag1 = 0;
   FTag2 = 0;
   FImageIndex = -1;
}

void __fastcall TSectionBarButton::Assign(TPersistent *Source)
{
   TSectionBarButton *C;
   TSectionBarBaseItem::Assign(Source);
   C = dynamic_cast<TSectionBarButton*>(Source);
   if (C)
   {
     ImageIndex = C->ImageIndex;
     Selected   = C->Selected;
   }
}

void __fastcall  TSectionBarButton::SetImageIndex(int AImageIndex)
{
   if (AImageIndex != FImageIndex)
   {
     FImageIndex = AImageIndex;
     Changed();
   }
}

void __fastcall  TSectionBarButton::SetSelected(const bool Value)
{
  TSectionBarButton *LastSelected;
  TSectionBarButtons  *SBB;
  TSectionBarSections *SBS;
  if ( (Value) && (!Enabled)) return;
  if ( ( Value != FSelected ) && (Collection))
  {
    SBB = dynamic_cast<TSectionBarButtons*>(Collection);
    SBS = dynamic_cast<TSectionBarSections*>(SBB->FSection->Collection);
    if ( (Value) && (SBB->FSection) && (SBB->FSection->Collection) && (SBS->FSectionBar) )
    {
       LastSelected = SBS->FSectionBar->Selected;
       if  ( LastSelected ) LastSelected->Selected = false;
    }
    else
      SBB->ButtonChanging( this );

    FSelected = Value;
    if (FSelected) MakeVisible();

  if ( (FSelected) && ( Collection ) )
   SBB->ButtonChanged( this );
   Changed();
  }
}

void __fastcall  TSectionBarButton::SetDown(const bool Value)
{
  TSectionBarButton *LastDown;
  TSectionBarButtons  *SBB;
  TSectionBarSections *SBS;
  if ( (Value) && (!Enabled)) return;
  if ( ( Value != FDown ) && (Collection))
  {
    SBB = dynamic_cast<TSectionBarButtons*>(Collection);
    SBS = dynamic_cast<TSectionBarSections*>(SBB->FSection->Collection);
    if ( (Value) && (SBB->FSection) && (SBB->FSection->Collection) && (SBS->FSectionBar) )
    {
       LastDown = SBS->FSectionBar->Down;
       if  ( LastDown ) LastDown->Down = false;
    }
    else
      SBB->ButtonChanging( this );

    FDown = Value;
    if (FDown) MakeVisible();

  if ( (FDown) && ( Collection ) )
   SBB->ButtonChanged( this );
   Changed();
  }
}


void __fastcall  TSectionBarButton::SetEnabled(bool AEnabled)
{
   if ( (Selected) && (!AEnabled)) return;
   TSectionBarBaseItem::SetEnabled(AEnabled);
}

void __fastcall  TSectionBarButton::SetVisible(bool AVisible)
{
   if ( (Selected) && (!AVisible)) return;
   TSectionBarBaseItem::SetVisible(AVisible);
}

void TSectionBarButton::MakeVisible()
{
   TSectionBarSection *Section;
   TGLSSectionBar *Bar;
   int I;
   Section = (dynamic_cast<TSectionBarButtons*>(Collection))->FSection;
   Section->Active = true;
   if (Section->Active)
   {
     if (Index < Section->TopButton)
       Section->TopButton = Index;
     else
     {
       Bar = (dynamic_cast<TSectionBarSections*>(Section->Collection))->FSectionBar;
       I = Bar->LastFullVisible();
       while (( I < Index ) && (Section->TopButton < Index))
       {
         Section->TopButton = Section->TopButton + 1;
         I = Bar->LastFullVisible();
       }
     }
  }
}


// ======= TSectionBarButtons ======================
__fastcall TSectionBarButtons::TSectionBarButtons(TSectionBarSection *Section):TSectionBarBaseCollection( __classid(TSectionBarButton) )
{
   FSection = Section;
}


TSectionBarButton* TSectionBarButtons::Add()
{
   Changed();
   return static_cast<TSectionBarButton*>(TCollection::Add());
}

void TSectionBarButtons::ButtonChanging(TSectionBarButton* NewButton)
{
   TSectionBarSections* C;
   TSectionBarBaseCollection::ButtonChanging(NewButton);
   if ( (FSection) && ( FSection->Collection ))
   {
     C = dynamic_cast<TSectionBarSections*>(FSection->Collection);
     if (C) C->ButtonChanging(NewButton);
  }
}

void TSectionBarButtons::ButtonChanged(TSectionBarButton* NewButton)
{
   TSectionBarSections* C;
   TSectionBarBaseCollection::ButtonChanged(NewButton);
   if ( (FSection) && ( FSection->Collection ))
   {
     C = dynamic_cast<TSectionBarSections*>(FSection->Collection);
     if (C) C->ButtonChanged(NewButton);
   }
}

void TSectionBarButtons::Changed()
{
   if ( FSection )  FSection->Changed();
}

TSectionBarButton* __fastcall TSectionBarButtons::GetItem(int Index)
{
   return static_cast<TSectionBarButton*>(TCollection::GetItem(Index));
}

TPersistent* __fastcall TSectionBarButtons::GetOwner(void)
{
   return FSection;
}

void __fastcall TSectionBarButtons::SetItem(int Index, TSectionBarButton* Value)
{
   TCollection::SetItem( Index, Value );
   Changed();
}



// ======= TSectionBarSection =======================
void TSectionBarSection::InitProperties()
{
   TSectionBarBaseItem::InitProperties();
   FButtons =  new TSectionBarButtons( this );
   FTopButton = -1;
   Caption = "Новая секция";
   if (Collection->Count == 1)  Active = true;
}

__fastcall TSectionBarSection::~TSectionBarSection()
{
   delete FButtons;
}

void  __fastcall TSectionBarSection::SetButtons(TSectionBarButtons  *Value)
{
  FButtons->Assign(Value);
}

void __fastcall TSectionBarSection::SetIndex(int Value)
{
   TCollectionItem::SetIndex(Value);
   Changed();
}

void __fastcall TSectionBarSection::Assign(TPersistent *Source)
{
  TSectionBarSection* C;
  TSectionBarBaseItem::Assign(Source);
  C = dynamic_cast<TSectionBarSection*>(Source);
  if (C)
  {
    Active = C->Active;
    Buttons->Assign(C->Buttons);
  }
}


void TSectionBarSection::Changed()
{
  if  ( Buttons->Count == 0 )
  {
     FTopButton = -1;
  }
  else
  {
    if ( FTopButton < 0 )  FTopButton = 0;
  }
  TSectionBarBaseItem::Changed();
}

int TSectionBarSection::VisibleCount(int StartFrom)
{
  int i;
  int Res = 0;
  for (i = StartFrom; i <=  Buttons->Count -1; i++)
  {
    if (Buttons->Items[i]->Visible)  Res++;
  }
  return Res;
}

bool TSectionBarSection::NextVisible(int &ButtonNo)
{
   do ButtonNo++;
   while (!((ButtonNo >= Buttons->Count ) || ( Buttons->Items[ButtonNo]->Visible)));
   return ( ButtonNo < Buttons->Count );
}

void  __fastcall TSectionBarSection::SetTopButton(int ATopButton)
{
   if ( ATopButton < 0) ATopButton = 0;
   if ( ATopButton >= Buttons->Count) ATopButton =  Buttons->Count - 1;
   if (FTopButton != ATopButton)
   {
      FTopButton = ATopButton;
      Changed();
   }
}

void  __fastcall TSectionBarSection::SetActive(bool const Value)
{
   TSectionBarSections *C;
   if (Value != FActive)
   {
     if ( (Value) && (!Active) && (Enabled) )
     {
       C = dynamic_cast<TSectionBarSections*>(Collection);
       if ( Collection )
         C->ActiveItem = this;
       FActive = (C->ActiveItem == this);
       Changed();
     }
     else
     FActive = false;
   }
}


void __fastcall TSectionBarSection::SetEnabled(bool AEnabled)
{
   TSectionBarSections *C;
   TSectionBarButtons  *B;
   if ( (Collection) && (!AEnabled) )
   {
      C = dynamic_cast<TSectionBarSections*>(Collection);
      B = dynamic_cast<TSectionBarButtons*>(C->FSectionBar->Selected->Collection);
      if ( (C->FSectionBar->Selected) && (B->FSection == this)) return;
   }
   TSectionBarBaseItem::SetEnabled(AEnabled);
}


void __fastcall TSectionBarSection::SetVisible(bool AVisible)
{
   TSectionBarSections *C;
   TSectionBarButtons  *B;
   if ( (Collection) && (!AVisible) )
   {
      C = dynamic_cast<TSectionBarSections*>(Collection);
      B = dynamic_cast<TSectionBarButtons*>(C->FSectionBar->Selected->Collection);
      if ( (C->FSectionBar->Selected) && (B->FSection == this)) return;
   }
   TSectionBarBaseItem::SetEnabled(AVisible);
}


// ======= TSectionBarSections ======================
__fastcall TSectionBarSections::TSectionBarSections(TGLSSectionBar* SectionBar):TSectionBarBaseCollection( __classid(TSectionBarSection))
{
   FSectionBar = SectionBar;
   ActiveItem = NULL;
}

TSectionBarSection* TSectionBarSections::Add()
{
   Changed();
   return static_cast<TSectionBarSection*>(TCollection::Add());
}


void TSectionBarSections::ButtonChanging(TSectionBarButton *NewButton)
{
   TSectionBarBaseCollection::ButtonChanging(NewButton);
   if ( FSectionBar ) FSectionBar->ButtonChanging( NewButton );
}

void TSectionBarSections::ButtonChanged(TSectionBarButton *NewButton)
{
   FSectionBar->ButtonChanged( NewButton );
}

void TSectionBarSections::Changed()
{
   if (FSectionBar)  FSectionBar->Invalidate();
}

TSectionBarSection* __fastcall TSectionBarSections::GetItem(int Index)
{
   return static_cast<TSectionBarSection*>(TCollection::GetItem(Index));
}

TPersistent* __fastcall TSectionBarSections::GetOwner(void)
{
   return FSectionBar;
}

void __fastcall TSectionBarSections::SetItem(int Index, TSectionBarSection* Value)
{
   TCollection::SetItem( Index, Value );
   Changed();
}

int TSectionBarSections::VisibleCount()
{
   int i;
   int Res = 0;
   for (i = 0; i <= Count -1 ; i++)
     if (Items[i]->Visible) Res++;
   return Res;
}


void TSectionBarSections::SetActiveItem(TSectionBarSection* AActiveItem)
{
   TSectionBarSection *Item;
   if (AActiveItem != FActiveItem)
   {
     Item = FActiveItem;
     if (Item) Item->Active = false;
     FActiveItem = AActiveItem;
     Changed();
   }
}


// ======= TGLSSectionBar =======================
_fastcall TGLSSectionBar::TGLSSectionBar(TComponent* AOwner):TCustomControl(AOwner)
{
   int Index;
   DesktopFont = true;
   FTmpBitmap = new Graphics::TBitmap;
   FSections =  new TSectionBarSections( this );
   FHeaderHeight = 17;//19;
   FButtonHeight = -1;
   FSectionHeaderPressed = -1;
   FButtonPressed = -1;
   FLastHintSection = -1;
   FLastHintButton = -1;
   FUnderlineTextNum = -1;
   FEnterButton = -1;
   ControlStyle = ControlStyle << csOpaque;
   Width = 100;
   Align = alLeft;
   FApplyDown = false;
   FDown = NULL;
   FOnLeftMouseDown = NULL;
   FOnRightMouseDown = NULL;
   FOnButtonApplyDown = NULL;

   for (Index = fiHeader; Index <= fiButtonUnderline; Index++)  FFonts[Index] = NULL;
   ReCreateFonts();
   Width = 100;
}

void __fastcall  TGLSSectionBar::Assign(TPersistent *Source)
{
  TGLSSectionBar* C;
  TCustomControl::Assign(Source);
  C = dynamic_cast<TGLSSectionBar*>(Source);
  if ( C )
  {
    Sections->Assign(C->Sections);
    Images = C->Images;
  }
}

__fastcall TGLSSectionBar::~TGLSSectionBar()
{
  FDestroying = TRUE;
  delete FSections;
  delete FTmpBitmap;
  DestroyFonts();
}


void __fastcall TGLSSectionBar::Loaded(void)
{
   TCustomControl::Loaded();
   FStoredHint = Hint;
}

void __fastcall TGLSSectionBar::Notification(Classes::TComponent* AComponent, Classes::TOperation Operation)
{
  if ( (Operation == opRemove) && (AComponent == FImages) )
  {
     FImages = NULL;
     Invalidate();
  }
}

void __fastcall TGLSSectionBar::SetActiveSection(TSectionBarSection* ASection)
{
   Sections->ActiveItem = ASection;
}

TSectionBarSection* __fastcall TGLSSectionBar::GetActiveSection()
{
   return (dynamic_cast<TSectionBarSection*>(Sections->ActiveItem));
}

void TGLSSectionBar::ButtonChanging( TSectionBarButton *NewButton )
{
   bool AllowChange;
   if (FDestroying) return;
   AllowChange = true;
   if (FOnChanging)
     FOnChanging(this, Selected, NewButton, AllowChange );
   if (!AllowChange) Abort();
}

void TGLSSectionBar::ButtonChanged( TSectionBarButton *NewButton)
{
   if (FDestroying) return;
   FSelected = NewButton;
   FDown = NewButton;
   if ( FOnChanged )
     FOnChanged( this, Selected );
}

void TGLSSectionBar::Changed()
{
}

void __fastcall TGLSSectionBar::WMMouseMove(TWMMouseMove& Msg )
{
   int Section, Button;
   bool InTextArea;
   bool repaints = false;
   String S, S1, S2, S3;
   int I, J, K, MaxLen;
   MouseInButton(Msg.XPos, Msg.YPos, Section, Button, InTextArea);
   J = FUnderlineTextNum;
   if (InTextArea)
     FUnderlineTextNum = Button;
   else
     FUnderlineTextNum = -1;



   if (J != FUnderlineTextNum)
   {
//     if ( (FUnderlineTextNum >= 0) &&
//        ( !(Sections->Items[Section]->Buttons->Items[FUnderlineTextNum]->Selected)))
     if ( FUnderlineTextNum >= 0 )
       Cursor = crHandPoint;
     else
       Cursor = crDefault;
     repaints = true;
   }

   K = FEnterButton;
   FEnterButton = Button;
   repaints = repaints || (K != FEnterButton);

   if (repaints) Invalidate();

   if ( (Section != FLastHintSection ) || ( Button != FLastHintButton ) )
   {
     FLastHintSection = Section;
     FLastHintButton = Button;
     S = "";
     if ( ( Button >=0 ) &&
          ( Sections->Items[Section]->Buttons->Items[Button]->Hint.Length()) > 0 )
     {
          S = Sections->Items[Section]->Buttons->Items[Button]->Hint;
     }
     else
     if ( ( Section >=0 ) && ( ( Sections->Items[Section]->Hint.Length() ) > 0) )
     {
        switch (Button)
        {
           case MOUSE_BELOW_BUTTONS: S = ""; break;
           case MOUSE_NOT_IN_BUTTON:
             {
               S = Sections->Items[Section]->Hint;
               if ( (!Sections->Items[Section]->Active) && (Sections->Items[Section]->Buttons->Count > 0) )
               {
                  S1 = "";
                  S2 = "";
                  MaxLen = 0;
                  for (I = 0; I <= Sections->Items[Section]->Buttons->Count - 1; I++)
                  {
                     S3 = Sections->Items[Section]->Buttons->Items[I]->Caption;
                     S1 = S1 + S3 + ", ";
                     S2 = S2 + 0x13 + S3;
                     if (S3.Length() > MaxLen) MaxLen = S3.Length();
                  }
                  S3.SetLength(MaxLen);
                  memset(S3.c_str(), '-', MaxLen);
                  S1[S1.Length() - 1] = ' ';
                  S = S + 0x13 + S3 + S2 + '|' + S1;

               }
               break;
             }

        }
     }
     if  (S.Length() != 0) Hint = S;
         else Hint = FStoredHint;
   }
   DefaultHandler(&Msg);

}

void _fastcall TGLSSectionBar::WMLButtonDown(TWMLButtonDown& Msg) //message WM_LBUTTONDOWN;
{
   int  Section, Button;
   bool InTextArea;
   TSectionBarSection *C;
   if (MouseInButton( Msg.XPos, Msg.YPos, Section, Button, InTextArea ))
   {
    SetCapture(Handle);
    FMousePressed = TRUE;
    if ( Sections->Count <= 0 ) return;
    if ( Sections->Items[Section]->Active )
    {
      if ( ( ( Button >= 0 ) && (Sections->Items[Section]->Buttons->Items[Button]->Enabled ) ) ||
        ( Button == MOUSE_IN_UP_SCROLL ) || ( Button == MOUSE_IN_DN_SCROLL ) )
      {
         FButtonPressed = Button;
         if ( (FApplyDown) && ( Button != MOUSE_IN_UP_SCROLL ) && ( Button != MOUSE_IN_DN_SCROLL ) )
         {
            bool IsApplyDown = true;
            if (FOnButtonApplyDown)
               FOnButtonApplyDown(this, Sections->Items[Section]->Buttons->Items[Button], mbLeft, IsApplyDown);
            if (IsApplyDown)
              Sections->Items[Section]->Buttons->Items[Button]->Down = !Sections->Items[Section]->Buttons->Items[Button]->Down;
         }
         C =  dynamic_cast<TSectionBarSection*>(Sections->ActiveItem);
         if ( ( Button == MOUSE_IN_UP_SCROLL ) &&
            ( FButtonPressed == MOUSE_IN_UP_SCROLL ))
            C->TopButton = C->TopButton - 1;

        if (( Button == MOUSE_IN_DN_SCROLL ) &&
           ( FButtonPressed == MOUSE_IN_DN_SCROLL ))
           C->TopButton = C->TopButton + 1;
      }
    }
    if ( ( Section >=0 ) && ( !Sections->Items[Section]->Active ) &&( Sections->Items[Section]->Enabled ))
      FSectionHeaderPressed = Section;

    if (FOnLeftMouseDown)
     FOnLeftMouseDown(this);
    Invalidate();
   }
   DefaultHandler(&Msg);
}


void __fastcall TGLSSectionBar::WMLButtonDblClick(TWMMButtonDblClk& Msg)// message WM_LBUTTONDBLCLK;
{
   int Section, Button;
   bool InTextArea;
   TSectionBarSection *C;
   if ( MouseInButton( Msg.XPos, Msg.YPos, Section, Button, InTextArea ) )
   {
      FMousePressed = true;
      if (Sections->Count <= 0) return;
      if ( Sections->Items[Section]->Active )
      {
        if ( ( ( Button >= 0 ) && (Sections->Items[Section]->Buttons->Items[Button]->Enabled ) ) ||
          ( Button == MOUSE_IN_UP_SCROLL ) || ( Button == MOUSE_IN_DN_SCROLL ) )
        {
           FButtonPressed = Button;
           C =  dynamic_cast<TSectionBarSection*>(Sections->ActiveItem);
           if ( ( Button == MOUSE_IN_UP_SCROLL ) &&
              ( FButtonPressed == MOUSE_IN_UP_SCROLL ))
              C->TopButton = C->TopButton - 1;

          if (( Button == MOUSE_IN_DN_SCROLL ) &&
             ( FButtonPressed == MOUSE_IN_DN_SCROLL ))
             C->TopButton = C->TopButton + 1;
        }
      }
   }
}


void __fastcall TGLSSectionBar::WMLButtonUp(TWMLButtonUp& Msg )
{
   int Section, Button;
   bool InTextArea;

   if (FMousePressed)
   {
     ReleaseCapture();
     FMousePressed = false;
     if (MouseInButton( Msg.XPos, Msg.YPos, Section, Button, InTextArea ))
     {
        if (Sections->Count <= 0) return;
        if (Section == FSectionHeaderPressed)  Sections->Items[Section]->Active = true;
        if ( ( Button >= 0 ) && ( Button == FButtonPressed ))
        {
          try
          {
            Sections->Items[Section]->Buttons->Items[Button]->Selected = true;
          }
          __finally{};
        }
     }
     Invalidate();
   }
   FButtonPressed = -1;
   FSectionHeaderPressed = -1;
   DefaultHandler(&Msg);
}


void __fastcall TGLSSectionBar::WMRButtonDown(TWMRButtonDown& Msg) //message WM_RBUTTONDOWN;
{
   int  Section, Button;
   bool InTextArea;
   TSectionBarSection *C;
   if (MouseInButton( Msg.XPos, Msg.YPos, Section, Button, InTextArea ))
   {
    SetCapture(Handle);
    FMousePressed = TRUE;
    if ( Sections->Count <= 0 ) return;
    if ( Sections->Items[Section]->Active )
    {
      if ( ( ( Button >= 0 ) && (Sections->Items[Section]->Buttons->Items[Button]->Enabled ) ) ||
        ( Button == MOUSE_IN_UP_SCROLL ) || ( Button == MOUSE_IN_DN_SCROLL ) )
      {
         FButtonPressed = Button;
         if ( (FApplyDown) && ( Button != MOUSE_IN_UP_SCROLL ) && ( Button != MOUSE_IN_DN_SCROLL ) )
         {
            bool IsApplyDown = true;
            if (FOnButtonApplyDown)
              FOnButtonApplyDown(this, Sections->Items[Section]->Buttons->Items[Button], mbRight, IsApplyDown);
            if (IsApplyDown)
              Sections->Items[Section]->Buttons->Items[Button]->Down = !Sections->Items[Section]->Buttons->Items[Button]->Down;
         }
         C =  dynamic_cast<TSectionBarSection*>(Sections->ActiveItem);
         if ( ( Button == MOUSE_IN_UP_SCROLL ) &&
            ( FButtonPressed == MOUSE_IN_UP_SCROLL ))
            C->TopButton = C->TopButton - 1;

        if (( Button == MOUSE_IN_DN_SCROLL ) &&
           ( FButtonPressed == MOUSE_IN_DN_SCROLL ))
           C->TopButton = C->TopButton + 1;
      }
    }
    if ( ( Section >=0 ) && ( !Sections->Items[Section]->Active ) &&( Sections->Items[Section]->Enabled ))
      FSectionHeaderPressed = Section;
    if (FOnRightMouseDown)
     FOnRightMouseDown(this);

    Invalidate();
   }
   DefaultHandler(&Msg);
}

void __fastcall TGLSSectionBar::WMRButtonUp(TWMRButtonUp& Msg ) //message WM_RBUTTONUP;
{
   int Section, Button;
   bool InTextArea;

   if (FMousePressed)
   {
     ReleaseCapture();
     FMousePressed = false;
     if (MouseInButton( Msg.XPos, Msg.YPos, Section, Button, InTextArea ))
     {
        if (Sections->Count <= 0) return;
        if (Section == FSectionHeaderPressed)  Sections->Items[Section]->Active = true;
        if ( ( Button >= 0 ) && ( Button == FButtonPressed ))
        {
          try
          {
            Sections->Items[Section]->Buttons->Items[Button]->Selected = true;
          }
          __finally{};
        }
     }
     Invalidate();
   }
   FButtonPressed = -1;
   FSectionHeaderPressed = -1;
   DefaultHandler(&Msg);



//   DefaultHandler(&Msg);
}


void __fastcall TGLSSectionBar::WMMouseLeave(TMessage& Msg)
{
   if (FEnterButton >=0 )
   {
      FEnterButton = -1;
      Invalidate();
   }
  // DefaultHandler(&Msg);
}

int  TGLSSectionBar::LastFullVisible()
{
   int Section, Button;
   int Y;
   int ActiveBottom;
   int Result = -1;
   TRect R;

   Button = -1;
   if ((ActiveSection) && (ActiveSection->Buttons->Count > 0 ))
   {
      Section = 0;
      Y = 0;
      if (Sections->Count == 0) return (Result);
      while (!Sections->Items[Section]->Active)
      {
        if (Sections->Items[Section]->Visible) Y += FHeaderHeight;
        Section++;
        if (Section >= Sections->Count) return (Result);
      }
      Y += FHeaderHeight;
      Button = ActiveSection->TopButton;
      ActiveBottom = Height - 4 - ( Sections->VisibleCount() - 1 ) * FHeaderHeight + Y - FHeaderHeight;
      do
      {
		 DrawButton( ActiveSection->Index, Button, Y, ActiveBottom, true, R );
         if (Y <= ActiveBottom) Button++;
      }while(!(( Y >= ActiveBottom ) || ( Button >= ActiveSection->Buttons->Count )));


   }
   Result =  Button - 1;
   return Result;
}


bool TGLSSectionBar::MouseInButton(int X, int Y, int  &Section, int &Button, bool &InTextArea)
{
 int YCoord, YCoord1;
 bool Found;
 int I;
 int ActiveBottom;
 TRect TextArea;
 bool Result = false;
 InTextArea = FALSE;
 Section = MOUSE_IN_FRAME;
 Button = MOUSE_NOT_IN_BUTTON;
 if (( X <= 2 ) || ( Y <= 2 ) ||
    ( X >= Width - 2 ) || ( Y >= Height - 2 )) return (Result);
 Result = true;
 YCoord = 2;
 do
 {
  if (Sections->Count == 0) return (Result);
  do
  {
   if (Section >=  Sections->Count - 1 )
   {
    Section =  Sections->Count - 1;
    return (Result);
   }
   Section++;
  }while(!(Sections->Items[ Section ]->Visible));
  YCoord+= FHeaderHeight;
  if (Sections->Items[Section]->Active)
  {
   YCoord1 = YCoord;
   ActiveBottom = Height - 4 - ( Sections->VisibleCount() - 1 ) * FHeaderHeight + YCoord - FHeaderHeight;
   if (Y >= YCoord)
   {
    I = ActiveSection->TopButton;
    Found = false;
    while (( I < ActiveSection->Buttons->Count ) && ( I >= 0 ) &&
          ( YCoord1 <= ActiveBottom ) & (!Found) )
    {
	 DrawButton( ActiveSection->Index, I, YCoord1, ActiveBottom, true, TextArea );
	 if ( (!Found) && ( YCoord1 >= Y ))
     {
      Button = I;
      Found = true;
      InTextArea = PtInRect(&TextArea, Point(X, Y));
     }
     I++;
    }
    if (!Found)
      Button = MOUSE_BELOW_BUTTONS;
    if (ActiveSection->TopButton > 0)
     if (PtInRect(&TRect(Bounds( Width - ScrollBtnSize -
      ScrollBtnOffset - 3, YCoord + ScrollBtnOffset, ScrollBtnSize,
      ScrollBtnSize )),  Point( X, Y )))
      Button = MOUSE_IN_UP_SCROLL;
    if ( Button >= 0 )
    {
     if (PtInRect( &TRect(Bounds( Width - ScrollBtnSize -
      ScrollBtnOffset - 3, ActiveBottom - ScrollBtnSize -
      ScrollBtnOffset, ScrollBtnSize, ScrollBtnSize )), Point( X, Y )))
      Button = MOUSE_IN_DN_SCROLL;
    }
   }
   YCoord = ActiveBottom;
  }
 }while (!( Y <= YCoord ));
 if (!Sections->Items[Section]->Active)
   Button = MOUSE_NOT_IN_BUTTON;
 return (Result);
}


void TGLSSectionBar::DrawScrollButton(TRect R, bool Up)
{
  TPoint points[3];

  FillRect(  FTmpBitmap->Canvas->Handle, &R,  (HBRUSH)(COLOR_BTNFACE+1));
  if ( (FMousePressed) &&
  ( ( ( FButtonPressed == MOUSE_IN_UP_SCROLL ) && Up ) ||
    ( ( FButtonPressed == MOUSE_IN_DN_SCROLL ) && (!Up) ) ) )
   DrawRect( FTmpBitmap->Canvas, R, false );
  else
   DrawRect( FTmpBitmap->Canvas, R, true );
  FTmpBitmap->Canvas->Brush->Color = clActiveCaption;
  FTmpBitmap->Canvas->Pen->Color = clBtnText;
  if (Up)
  {
    points[0] = Point( R.Left + 5, R.Bottom - 6);
    points[1] = Point( R.Left + (R.Right - R.Left) / 2, R.Top + 5);
    points[2] = Point( R.Right - 5, R.Bottom - 6);
  }
  else
  {
    points[0] = Point( R.Left + 5, R.Top + 6);
    points[1] = Point( R.Left + (R.Right - R.Left) / 2, R.Bottom - 5);
    points[2] = Point( R.Right - 5, R.Top + 6);
  }
  FTmpBitmap->Canvas->Polygon(points, 2);
}

void TGLSSectionBar::DrawButton( int SectionNumber, int ButtonNumber, int &Y, int YMax, bool CalcOnly, TRect &TextArea)
{
  int BtnHeight;
  int TxtHeight;
  int iTop;
  String S;
  TBrushStyle OldBrush;
  TColor OldPenColor;
  bool DrawPressed;

  if (Sections->Items[SectionNumber]->Buttons->Items[ButtonNumber]->Visible)
  {
    S = Sections->Items[SectionNumber]->Buttons->Items[ButtonNumber]->Caption;
     // if ( ActiveSection->Buttons->Items[ButtonNumber]->Selected)
     // {
     //   SelectFont(fiButtonSelected);
     // } else
        {
         if (Sections->Items[SectionNumber]->Buttons->Items[ ButtonNumber ]->Enabled)
         {
           if (FUnderlineTextNum == ButtonNumber)
             SelectFont(fiButtonUnderline);
           else
             SelectFont(fiButton);
         } else
          SelectFont(fiButtonDisabled);
        }
    TextArea = Bounds(0, ImageHeight + TextOffset + VFrameOffset + Y,
	  this->Width - HFrameOffset * 2 - 6, 0);
	TxtHeight = DrawText(FTmpBitmap->Canvas->Handle,
	  S.c_str(), -1, &TextArea, DT_CENTER | DT_WORDBREAK | DT_CALCRECT);
    TextArea.Left = (this->Width - TextArea.Right) / 2 - 2;
    TextArea.Right = TextArea.Left + TextArea.Right + 2;

    BtnHeight = ImageHeight + 2 * VFrameOffset + TextOffset + TxtHeight;
    iTop = Y;
    Y+= BtnHeight;

    if (!CalcOnly)
    {
		DrawPressed = false;
        if (FMousePressed && ( ButtonNumber == FButtonPressed ))
        {
          DrawRect(FTmpBitmap->Canvas,
            Bounds( 4, iTop + VFrameOffset - 2,  Width - 8,
            ImageHeight + 4), FALSE);
          DrawPressed = true;
        }
        if ( (ButtonNumber ==  FEnterButton) && !DrawPressed)
        {
           OldBrush = FTmpBitmap->Canvas->Brush->Style;
           OldPenColor = FTmpBitmap->Canvas->Pen->Color;
           FTmpBitmap->Canvas->Brush->Style = bsClear;
           FTmpBitmap->Canvas->Pen->Color =  clActiveCaption;

           FTmpBitmap->Canvas->Rectangle( Bounds( 6, iTop + VFrameOffset ,  Width - 12,
            ImageHeight ));

           FTmpBitmap->Canvas->Brush->Style = OldBrush;
           FTmpBitmap->Canvas->Pen->Color = OldPenColor;

        }
        if ( Sections->Items[SectionNumber]->Buttons->Items[ButtonNumber]->Down)
        {
          DrawRect(FTmpBitmap->Canvas,
            Bounds( 4, iTop + VFrameOffset - 2,  Width - 8,
            ImageHeight + 4), FALSE);
        }

		if (AlternativeColor)
		  SetBkColor(FTmpBitmap->Canvas->Handle, ColorToRGB(clAppWorkSpace));
		else
		  SetBkColor(FTmpBitmap->Canvas->Handle, ColorToRGB(clInfoBk));

		if ( ( Images ) &&
		   ( Sections->Items[SectionNumber]->Buttons->Items[ ButtonNumber ]->ImageIndex >= 0 ) &&
           ( Sections->Items[SectionNumber]->Buttons->Items[ ButtonNumber ]->ImageIndex < Images->Count ) )
          Images->Draw( FTmpBitmap->Canvas, ( Width - ImageWidth ) / 2, VFrameOffset + iTop,
             Sections->Items[SectionNumber]->Buttons->Items[ ButtonNumber ]->ImageIndex, true );
        DrawText(FTmpBitmap->Canvas->Handle,  S.c_str() , -1, &TextArea, DT_CENTER | DT_WORDBREAK );
    }
  }
}

void  TGLSSectionBar::DrawSection(int SectionNumber, TRect R)
{
	TRect R1, RText, TextArea;
    int I;
	int Y;
    R1 = R;
	R1.Bottom = R1.Top + FHeaderHeight;
	RText = R1;
	FillRect(FTmpBitmap->Canvas->Handle, &R1, (HBRUSH)(COLOR_BTNFACE+1));
    SetBkColor(FTmpBitmap->Canvas->Handle, ColorToRGB(clBtnFace));
	if (!Sections->Items[SectionNumber]->Enabled)
	  SelectFont(fiHeaderDisabled);
	else
	if ( ( Selected ) &&
        ((dynamic_cast<TSectionBarButtons*>(Selected->Collection))->FSection->Index == SectionNumber) )
      SelectFont(fiHeaderBold);
    else
	  SelectFont(fiHeader);
	DrawText(FTmpBitmap->Canvas->Handle, Sections->Items[SectionNumber]->Caption.c_str(),
	  -1, &RText, DT_SINGLELINE | DT_CENTER | DT_TOP);
    if (!( FMousePressed && ( SectionNumber == FSectionHeaderPressed ) ))
	  DrawEdge(FTmpBitmap->Canvas->Handle, &R1, EDGE_RAISED, BF_RECT | BF_SOFT | BF_ADJUST);
    R.Top += FHeaderHeight;
	if ( R.Top == R.Bottom) return;

	if (AlternativeColor)
	  FillRect(FTmpBitmap->Canvas->Handle, &R, (HBRUSH)(COLOR_APPWORKSPACE + 1));
	else
	  FillRect(FTmpBitmap->Canvas->Handle, &R, (HBRUSH)(COLOR_INFOBK + 1));

	//	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 224)); ////clYellow
	//	FillRect(FTmpBitmap->Canvas->Handle, &R, brush);
	//	DeleteObject(brush);




	Y = R.Top;
    I = Sections->Items[SectionNumber]->TopButton;
	while (( I < Sections->Items[SectionNumber]->Buttons->Count ) &&
          ( I >= 0 ) &&
          ( Y <= R.Bottom ))
    {

     DrawButton( SectionNumber, I, Y, R.Bottom, false, TextArea );
     I++;
    }
    if ( Sections->Items[SectionNumber]->TopButton > 0 )
    {
     // Можно прокрутить вверх
     R1 = Bounds( Width - ScrollBtnSize -  ScrollBtnOffset - 3,
       R.Top + ScrollBtnOffset, ScrollBtnSize, ScrollBtnSize );
     DrawScrollButton( R1, true );
    }
    if ( Y > R.Bottom)
    {
     // Все кнопки не поместились, рисуем кнопку прокрутки вниз
      R1 = Bounds( Width - ScrollBtnSize - ScrollBtnOffset - 3,
      R.Bottom - ScrollBtnSize - ScrollBtnOffset, ScrollBtnSize , ScrollBtnSize );
      DrawScrollButton( R1, false );
    } else {}
}

void __fastcall TGLSSectionBar::Paint(void)
{
  TRect R;
  int I;
  int ActHeight;
  int NextTop;

  if ( (FTmpBitmap->Width != Width) ||
     (FTmpBitmap->Height != Height) )
  {
    FTmpBitmap->Width = Width;
    FTmpBitmap->Height = Height;
    FTmpBitmap->Canvas->Font->Assign(Font);
  }
    R = Bounds(0, 0, Width, Height);
    if ( Ctl3D)
      DrawEdge(FTmpBitmap->Canvas->Handle, &R, EDGE_SUNKEN, BF_RECT | BF_MIDDLE);
    else
      DrawEdge(FTmpBitmap->Canvas->Handle, &R, EDGE_RAISED, BF_RECT | BF_FLAT | BF_MIDDLE);
	NextTop = 2;
    for ( I = 0 ; I <= Sections->Count - 1; I++)
    {
      if ( Sections->Items[I]->Visible )
      {
        if (I < ActiveSection->Index)
        {
          R = Bounds( 2, NextTop, Width - 4, FHeaderHeight );
          NextTop+= FHeaderHeight;
        }
        if ( I == ActiveSection->Index)
        {
          ActHeight = Height - 4 - ( Sections->VisibleCount() - 1 )* FHeaderHeight;
          R = Bounds( 2, NextTop, Width - 4, ActHeight );
          NextTop+= ActHeight;
        }
        if ( I > ActiveSection->Index)
		{
          R = Bounds( 2, NextTop, Width - 4, FHeaderHeight );
          NextTop+= FHeaderHeight;
        }
		DrawSection(I, R);
      }
    }
    BitBlt(Canvas->Handle, 0, 0, Width, Height ,
	  FTmpBitmap->Canvas->Handle, 0, 0, cmSrcCopy);
}

void __fastcall TGLSSectionBar::SetSections(TSectionBarSections* Value)
{
   FSections->Assign(Value);
}

void __fastcall TGLSSectionBar::SetSelected(TSectionBarButton* Value)
{
   if (Value) Value->Selected = true;
   else
     FSelected->Selected = false;
}

void __fastcall TGLSSectionBar::SetDown(TSectionBarButton* Value)
{
   if (Value) Value->Down = true;
   else
	 FDown->Down = false;
}


void TGLSSectionBar::SelectFont(TFontIndex Index)
{
  SelectObject(FTmpBitmap->Canvas->Handle, FFonts[Index]->Handle);
  SetTextColor(FTmpBitmap->Canvas->Handle, FFonts[Index]->Color);
}


void __fastcall TGLSSectionBar::WMEraseBkGnd(TWMEraseBkgnd& M )
{
   if ( (FTmpBitmap->Width != Width) || (FTmpBitmap->Height != Height) )
     Paint();
   else
    BitBlt(M.DC, 0, 0, Width, Height, FTmpBitmap->Canvas->Handle, 0, 0, cmSrcCopy);
   M.Result = 1;
}

void __fastcall TGLSSectionBar::WMSetFont(TWMSetFont&  M)
{
  DefaultHandler(&M);
  ReCreateFonts();
  Invalidate();
}

void TGLSSectionBar::DestroyFonts()
{
  int Index;
  for ( Index = fiHeader; Index <= fiButtonUnderline; Index++)
  {
    delete FFonts[Index];
    FFonts[Index] = NULL;
  }
}



void TGLSSectionBar::ReCreateFonts()
{
  int Index;
  DestroyFonts();
  for (Index = fiHeader; Index <= fiButtonUnderline; Index++)
  {
	FFonts[Index] =  new TFont;
    FFonts[Index]->Assign(Font);
    switch (Index)
	{
	  case fiHeader:
	  {
		 FFonts[Index]->Color = clBlack;// clWindowText;
		 FFonts[Index]->Style = TFontStyles();
		 break;
	  }
	  case fiHeaderBold:
	  {
		  FFonts[Index]->Color = clBlack;// clWindowText;
		  FFonts[Index]->Style = TFontStyles() << fsBold;
		  break;
	  }
	  case fiHeaderDisabled:
	  {
		  FFonts[Index]->Color = clGrayText;
		  FFonts[Index]->Style = TFontStyles() << fsBold;
		  break;
	  }
	  case fiButton:
	  {
		  FFonts[Index]->Color = clBlack;// clCaptionText;
		  FFonts[Index]->Style = TFontStyles();
		  break;
	  }
	  case fiButtonDisabled:
	  {
		  FFonts[Index]->Color = clBtnText;
		  FFonts[Index]->Style = TFontStyles();
		  break;
	  }
	  case fiButtonSelected:
	  {
		  FFonts[Index]->Color = clBlack;// clCaptionText;
		  FFonts[Index]->Style = TFontStyles();
		  break;
	  }
	  case fiButtonUnderline:
	  {
		  FFonts[Index]->Color = clBlack;// clCaptionText;
		  FFonts[Index]->Style = TFontStyles() << fsUnderline;
		  break;
	  }
	}
  }
}

void TGLSSectionBar::DownFalse()
{
   int i, j;
   bool repaint = false;
   TSectionBarSection* S;
   TSectionBarButton* B;
   for (i = 0; i <= Sections->Count-1; i++)
   {
     S = Sections->Items[i];
     for (j = 0; j <= S->Buttons->Count-1; j++)
     {
        B = S->Buttons->Items[j];
        if (B->Down)
        {
          repaint = true;
          B->Down = false;
        }
     }
   }
   if (repaint) Invalidate();
}

void __fastcall TGLSSectionBar::SetApplyDown(const bool Value)
{
   TSectionBarSection* S;
   TSectionBarButton* B;
   if (FApplyDown != Value)
   {
      FApplyDown = Value;
      if (!FApplyDown)  DownFalse();
   }
}



