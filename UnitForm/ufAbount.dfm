object fAbount: TfAbount
  Left = 362
  Top = 314
  BorderStyle = bsDialog
  Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
  ClientHeight = 163
  ClientWidth = 355
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 18
    Top = 10
    Width = 319
    Height = 23
    Alignment = taCenter
    AutoSize = False
    Caption = #1043#1069#1057' '#1048#1053#1058#1045#1051#1051#1045#1050#1058' 3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    WordWrap = True
  end
  object lblVersion2: TLabel
    Left = 240
    Top = 58
    Width = 56
    Height = 16
    Caption = #1042#1077#1088#1089#1080#1103':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object lblBuild2: TLabel
    Left = 240
    Top = 78
    Width = 56
    Height = 16
    Caption = #1057#1073#1086#1088#1082#1072':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Bevel1: TBevel
    Left = -2
    Top = 117
    Width = 360
    Height = 8
    Shape = bsBottomLine
  end
  object lblVersion: TLabel
    Left = 312
    Top = 58
    Width = 24
    Height = 16
    Caption = '2.0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object lblBuild: TLabel
    Left = 312
    Top = 78
    Width = 8
    Height = 16
    Caption = '1'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 240
    Top = 104
    Width = 77
    Height = 14
    Caption = #1053#1043#1058#1059' 2019'#1075'.'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Button1: TButton
    Left = 272
    Top = 132
    Width = 75
    Height = 25
    Action = acOk
    TabOrder = 0
  end
  object ActionList1: TActionList
    Left = 104
    Top = 72
    object acOk: TAction
      Caption = #1047#1072#1082#1088#1099#1090#1100
      ShortCut = 27
      OnExecute = acOkExecute
    end
  end
end
