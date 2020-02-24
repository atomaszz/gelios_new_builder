//---------------------------------------------------------------------------

#ifndef uLEControlH
#define uLEControlH
//---------------------------------------------------------------------------
const WM_LE_MOUSEENTER = WM_USER + 3001;
const WM_LE_MOUSELEAVE = WM_USER + 3002;

class TLEControl
{
   private:
     void *f_Source;
     int f_Id;
     HWND f_WndHandler;
     TControl* f_UnderControl;
     int f_Left, f_Top, f_Width, f_Height;
     bool f_Enter;
     bool f_Active;
   public:
      TLEControl();
      bool React(TPoint APoint);
      __property void* Source = {read = f_Source, write = f_Source};
      __property int Id = {read = f_Id, write = f_Id};
      __property HWND WndHandler = {read = f_WndHandler, write  = f_WndHandler};
      __property TControl* UnderControl = {read = f_UnderControl, write = f_UnderControl};
      __property int Left = {read = f_Left, write  = f_Left};
      __property int Top = {read = f_Top, write  = f_Top};
      __property int Width = {read = f_Width, write  = f_Width};
      __property int Height = {read = f_Height, write  = f_Height};
      __property bool Enter = {read = f_Enter};
      __property bool Active = {read = f_Active, write = f_Active};

};

#endif
