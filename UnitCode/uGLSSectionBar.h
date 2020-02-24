//---------------------------------------------------------------------------

#ifndef uGLSSectionBarH
#define uGLSSectionBarH
//---------------------------------------------------------------------------
const int ImageHeight = 50;
const int ImageWidth = 80;
const int VFrameOffset = 3;
const int HFrameOffset = 3;
const int TextOffset  = 3;
const int ScrollBtnSize = 20;
const int ScrollBtnOffset = 3;

const int  MOUSE_IN_FRAME = -1;
const int  MOUSE_NOT_IN_BUTTON = -1;
const int  MOUSE_IN_UP_SCROLL = -2;
const int  MOUSE_IN_DN_SCROLL = -3;
const int  MOUSE_BELOW_BUTTONS = -4;

const int  NO_REDRAW = -1;
const int  REDRAW_ALL = -2;


class TSectionBarButton;
class TSectionBarSection;
class TGLSSectionBar;

class TSectionBarBaseItem:  public TCollectionItem
{
  private:
	String  FHint;
	String  FCaption;
	bool FVisible;
	bool FEnabled;
	int FTag;
	void __fastcall SetCaption(String ACaption);
	virtual void __fastcall SetTag(const int Value);

  protected:
	String __fastcall GetDisplayName();
	virtual void __fastcall SetVisible(bool AVisible);
	virtual void __fastcall SetEnabled(bool AEnabled);
	virtual void Changed();
	virtual void InitProperties();

  public:
	void __fastcall  Assign(TPersistent *Source);
	__fastcall virtual TSectionBarBaseItem(TCollection* Collection);
	__fastcall virtual ~TSectionBarBaseItem();

  __published:
	__property bool Visible = {read = FVisible, write = SetVisible, default = true};
	__property bool Enabled = {read = FEnabled, write = SetEnabled, default = true};
	__property String Caption = {read = FCaption , write = SetCaption};
	__property int Tag = {read = FTag, write = SetTag, default  = 0};
	__property String Hint = {read = FHint, write = FHint};
};


class TSectionBarBaseCollection: public  TCollection
{
   public:
     virtual void ButtonChanging(TSectionBarButton *NewButton);
     virtual void ButtonChanged(TSectionBarButton *NewButton);
     virtual void Changed() = 0;
     __fastcall TSectionBarBaseCollection(TCollectionItemClass ItemClass);
};


class TSectionBarButton: public TSectionBarBaseItem
{
   private:
     bool FSelected;
     bool FDown;
     int  FImageIndex;
     int  FTag1, FTag2;
     void __fastcall  SetImageIndex(int AImageIndex);
     void __fastcall  SetSelected(const bool Value);
     void __fastcall  SetDown(const bool Value);

   protected:
     void __fastcall  SetVisible(bool AVisible);
     void __fastcall  SetEnabled(bool AEnabled);
     void InitProperties();

   public:
     void __fastcall Assign(TPersistent *Source);
     void MakeVisible();

  __published:
    __property int  ImageIndex = {read = FImageIndex, write = SetImageIndex};
    __property bool Selected = {read = FSelected, write = SetSelected, default = false};
    __property bool Down = {read = FDown, write = SetDown, default = false};
    __property int Tag1 = {read = FTag1, write = FTag1};
    __property int Tag2 = {read = FTag2, write = FTag2};


};


class TSectionBarButtons: public  TSectionBarBaseCollection
{
   private:
     TSectionBarButton* __fastcall GetItem(int Index);
     void __fastcall SetItem(int Index, TSectionBarButton* Value);

   protected:
     DYNAMIC TPersistent* __fastcall GetOwner(void);

   public:
     void ButtonChanging(TSectionBarButton* NewButton);
     void ButtonChanged(TSectionBarButton* NewButton);
     void Changed();
     TSectionBarSection *FSection;
     __fastcall TSectionBarButtons(TSectionBarSection *Section);
     TSectionBarButton* Add();
     __property TSectionBarButton* Items[int Index] = { read =  GetItem, write = SetItem};
};

class TSectionBarSection: public  TSectionBarBaseItem
{
   private:
    bool FActive;
    TSectionBarButtons* FButtons;
    int FTopButton;

    void  __fastcall SetTopButton(int ATopButton);
    void  __fastcall SetButtons(TSectionBarButtons  *Value);
    void  __fastcall SetActive(bool const Value);

  protected:
    void __fastcall SetVisible(bool AVisible);
    void __fastcall SetEnabled(bool AEnabled);
    void __fastcall SetIndex(int Value);
    int VisibleCount(int StartFrom);
    bool NextVisible(int &ButtonNo);

  public:
    void Changed();
    void __fastcall Assign(TPersistent *Source);
    void InitProperties();
    __fastcall ~TSectionBarSection();
    __property int TopButton = {read = FTopButton, write = SetTopButton};

  __published:
    __property bool Active = {read = FActive, write = SetActive};
    __property TSectionBarButtons* Buttons = {read = FButtons, write = SetButtons};
};


class TSectionBarSections: public  TSectionBarBaseCollection
{
   private:
     TSectionBarSection* FActiveItem;
     TSectionBarSection* __fastcall GetItem(int Index);
     void __fastcall SetItem(int Index, TSectionBarSection* Value);
     void SetActiveItem(TSectionBarSection* AActiveItem);

   protected:
     DYNAMIC TPersistent* __fastcall GetOwner(void);
   public:
     TGLSSectionBar* FSectionBar;
     __fastcall TSectionBarSections(TGLSSectionBar* SectionBar);
     void ButtonChanging(TSectionBarButton *NewButton);
     void ButtonChanged(TSectionBarButton *NewButton);
     void Changed();
     TSectionBarSection* Add();
     int VisibleCount();
     __property TSectionBarSection* Items[int Index] = {read = GetItem, write = SetItem};
     __property TSectionBarSection *ActiveItem = {read = FActiveItem, write = SetActiveItem};
};



typedef void __fastcall (__closure *TOnSectionBarChanging)( TGLSSectionBar *Sender,
   TSectionBarButton* OldButton,  TSectionBarButton *NewButton, bool &AllowChange);

typedef void __fastcall (__closure *TOnSectionBarChanged) ( TGLSSectionBar *Sender,
   TSectionBarButton *Button );

typedef void __fastcall (__closure *TOnSectionBarButtonApplyDown) ( TGLSSectionBar *Sender,
   TSectionBarButton *SectionButton, TMouseButton Button,  bool &AllowChange);


enum TFontIndex { fiHeader, fiHeaderBold, fiHeaderDisabled, fiButton, fiButtonDisabled,
  fiButtonSelected, fiButtonUnderline };


class TGLSSectionBar: public TCustomControl
{
   private:
	TFont* FFonts[7];
	bool FDestroying;
	String FStoredHint;
    int FLastHintSection;
    int FLastHintButton;
	Graphics::TBitmap* FTmpBitmap;
    bool FMousePressed;
    int FSectionHeaderPressed;
    int FButtonPressed;
    TSectionBarSections* FSections;
    TImageList* FImages;
    int FHeaderHeight;
    int FButtonHeight;
    TSectionBarButton* FSelected;
    TSectionBarButton* FDown;
    TOnSectionBarChanging FOnChanging;
    TOnSectionBarChanged FOnChanged;
    TNotifyEvent FOnLeftMouseDown;
    TNotifyEvent FOnRightMouseDown;
    TOnSectionBarButtonApplyDown FOnButtonApplyDown;

    int FUnderlineTextNum;
    int FEnterButton;
	bool FApplyDown;
	bool FAlternativeColor;

    void __fastcall SetSections(TSectionBarSections* Value);
    TSectionBarSection* __fastcall GetActiveSection();
    void __fastcall SetActiveSection(TSectionBarSection* ASection);
    void DrawSection(int SectionNumber, TRect R);
    void DrawButton( int SectionNumber, int ButtonNumber, int &Y, int YMax, bool CalcOnly, TRect &TextArea);
    void DrawScrollButton(TRect R, bool Up);
    bool MouseInButton(int X, int Y, int  &Section, int &Button, bool &InTextArea);
    void __fastcall SetSelected(TSectionBarButton* Value);
    void __fastcall SetDown(TSectionBarButton* Value);
    void __fastcall SetApplyDown(const bool Value);
	void SelectFont(TFontIndex Index);
	void ReCreateFonts();
    void DestroyFonts();
    MESSAGE void __fastcall WMEraseBkGnd(TWMEraseBkgnd& M );// message WM_ERASEBKGND;
    MESSAGE void __fastcall WMSetFont(TWMSetFont&  M); //message WM_SETFONT;
    MESSAGE void __fastcall WMMouseMove(TWMMouseMove& Msg ); //message WM_MOUSEMOVE;
    MESSAGE void __fastcall WMLButtonDown(TWMLButtonDown& Msg); //message WM_LBUTTONDOWN;
    MESSAGE void __fastcall WMRButtonDown(TWMRButtonDown& Msg); //message WM_RBUTTONDOWN;
    MESSAGE void __fastcall WMLButtonDblClick(TWMMButtonDblClk& Msg);// message WM_LBUTTONDBLCLK;
    MESSAGE void __fastcall WMLButtonUp(TWMLButtonUp& Msg ); //message WM_LBUTTONUP;
    MESSAGE void __fastcall WMRButtonUp(TWMRButtonUp& Msg ); //message WM_RBUTTONUP;
    MESSAGE void __fastcall WMMouseLeave(TMessage& Msg);// CM_MOUSELEAVE

 protected:
    void __fastcall Paint(void);
    void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
    void __fastcall Loaded(void);


    __property TOnSectionBarChanging OnChanging = {read = FOnChanging, write = FOnChanging};
    __property TOnSectionBarChanged OnChanged = { read = FOnChanged, write = FOnChanged};

 public:

    virtual void ButtonChanging( TSectionBarButton *NewButton );
	virtual void ButtonChanged( TSectionBarButton *NewButton);
	virtual void  Changed();
	void __fastcall  Assign(TPersistent *Source);
	int  LastFullVisible();
	void DownFalse();
	__fastcall TGLSSectionBar(TComponent* AOwner);
	__fastcall ~TGLSSectionBar();
	__property TSectionBarSection* ActiveSection = { read = GetActiveSection, write = SetActiveSection};
	__property TSectionBarButton* Selected =  {read = FSelected, write = SetSelected};
	__property TImageList* Images ={ read = FImages,  write = FImages};
	__property TSectionBarButton* Down =  {read = FDown, write = SetDown};
	__property bool ApplyDown = {read = FApplyDown, write = SetApplyDown};
	__property TNotifyEvent LeftMouseDown  = {read = FOnLeftMouseDown, write = FOnLeftMouseDown};
	__property TNotifyEvent RightMouseDown = {read = FOnRightMouseDown, write = FOnRightMouseDown};
	__property TOnSectionBarButtonApplyDown OnButtonApplyDown = {read = FOnButtonApplyDown, write = FOnButtonApplyDown};
	__property bool AlternativeColor = {read = FAlternativeColor, write = FAlternativeColor};


 __published:
	__property TSectionBarSections *Sections = { read = FSections, write = SetSections};

  BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(WM_ERASEBKGND, TWMEraseBkgnd, WMEraseBkGnd)
	MESSAGE_HANDLER(WM_SETFONT, TWMSetFont, WMSetFont)
	MESSAGE_HANDLER(WM_MOUSEMOVE, TWMMouseMove, WMMouseMove)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, TWMLButtonDown, WMLButtonDown)
	MESSAGE_HANDLER(WM_RBUTTONDOWN, TWMRButtonDown, WMRButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, TWMMButtonDblClk, WMLButtonDblClick)
	MESSAGE_HANDLER(WM_LBUTTONUP, TWMLButtonUp, WMLButtonUp)
	MESSAGE_HANDLER(WM_RBUTTONUP, TWMRButtonUp, WMRButtonUp)
	MESSAGE_HANDLER(CM_MOUSELEAVE, TMessage, WMMouseLeave)
  END_MESSAGE_MAP(TCustomControl);
};


#endif
