object fmOzenkView: TfmOzenkView
  Left = 387
  Top = 260
  BorderStyle = bsDialog
  Caption = #1054#1094#1077#1085#1082#1080
  ClientHeight = 98
  ClientWidth = 283
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 10
    Top = 12
    Width = 96
    Height = 13
    Caption = #1054#1094#1077#1085#1082#1072' '#1084#1086#1097#1085#1086#1089#1090#1080':'
  end
  object Label2: TLabel
    Left = 10
    Top = 40
    Width = 150
    Height = 13
    Caption = #1054#1094#1077#1085#1082#1072' '#1090#1088#1091#1076#1086#1077#1084#1082#1086#1089#1090#1080' ('#1084#1089#1077#1082'):'
  end
  object edPower: TEdit
    Left = 176
    Top = 9
    Width = 97
    Height = 21
    Color = clBtnFace
    TabOrder = 0
  end
  object edWork: TEdit
    Left = 176
    Top = 37
    Width = 97
    Height = 21
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 1
  end
  object Button1: TButton
    Left = 199
    Top = 68
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 2
  end
end
