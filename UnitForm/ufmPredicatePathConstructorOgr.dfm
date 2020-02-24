object fmPredicatePathConstructorOgr: TfmPredicatePathConstructorOgr
  Left = 355
  Top = 293
  BorderStyle = bsDialog
  Caption = #1054#1075#1088#1072#1085#1080#1095#1077#1085#1080#1103
  ClientHeight = 243
  ClientWidth = 336
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 10
    Top = 15
    Width = 145
    Height = 16
    Caption = #1044#1086#1087#1091#1089#1090#1080#1084#1099#1081' '#1087#1088#1086#1094#1077#1085#1090': '
  end
  object Label3: TLabel
    Left = 315
    Top = 16
    Width = 12
    Height = 16
    Caption = '%'
  end
  object Label2: TLabel
    Left = 10
    Top = 51
    Width = 220
    Height = 16
    Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1086' '#1076#1086#1087#1091#1089#1090#1080#1084#1086#1077' '#1082#1086#1083'-'#1074#1086':'
  end
  object Button1: TButton
    Left = 233
    Top = 202
    Width = 94
    Height = 31
    Action = acCancel
    TabOrder = 0
  end
  object Button2: TButton
    Left = 128
    Top = 202
    Width = 95
    Height = 31
    Action = acOk
    TabOrder = 1
  end
  object edPercent: TEdit
    Left = 236
    Top = 12
    Width = 70
    Height = 24
    TabOrder = 2
    Text = '100'
  end
  object edCount: TEdit
    Left = 236
    Top = 48
    Width = 90
    Height = 24
    TabOrder = 3
    Text = '1000'
  end
  object gbOzenk: TGroupBox
    Left = 10
    Top = 79
    Width = 316
    Height = 114
    Caption = #1054#1094#1077#1085#1082#1072
    TabOrder = 4
    object lblMaxOpt: TLabel
      Left = 10
      Top = 86
      Width = 245
      Height = 16
      Caption = #1052#1072#1082#1089'. '#1082#1086#1083'-'#1074#1086' '#1086#1087#1090#1080#1084#1072#1083#1100#1085#1099#1093' '#1074#1072#1088#1080#1072#1085#1090#1086#1074
    end
    object cbOzenk: TCheckBox
      Left = 10
      Top = 25
      Width = 296
      Height = 21
      Caption = #1055#1088#1086#1080#1079#1074#1086#1076#1080#1090#1100' '#1086#1094#1077#1085#1082#1091
      TabOrder = 0
      OnClick = cbOzenkClick
    end
    object edMaxOpt: TEdit
      Left = 266
      Top = 84
      Width = 40
      Height = 24
      TabOrder = 1
      Text = '1'
    end
    object cbExclude: TCheckBox
      Left = 10
      Top = 54
      Width = 296
      Height = 21
      Caption = #1048#1089#1082#1083#1102#1095#1072#1090#1100' '#1086#1076#1080#1085#1072#1082#1086#1074#1099#1077' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1099
      TabOrder = 2
      OnClick = cbOzenkClick
    end
  end
  object ActionList1: TActionList
    Left = 136
    Top = 7
    object acCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1072
      ShortCut = 27
      OnExecute = acCancelExecute
    end
    object acOk: TAction
      Caption = #1055#1091#1089#1082
      OnExecute = acOkExecute
    end
  end
end
