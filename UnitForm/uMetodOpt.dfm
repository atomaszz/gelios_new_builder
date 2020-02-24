object FmMetodOpt: TFmMetodOpt
  Left = 293
  Top = 185
  BorderStyle = bsDialog
  Caption = #1052#1077#1090#1086#1076' '#1086#1087#1090#1080#1084#1080#1079#1072#1094#1080#1080
  ClientHeight = 204
  ClientWidth = 247
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
    Left = 7
    Top = 6
    Width = 32
    Height = 13
    Caption = #1052#1077#1090#1086#1076
  end
  object lblPribl: TLabel
    Left = 8
    Top = 136
    Width = 134
    Height = 13
    Caption = #1055#1088#1080#1073#1083#1080#1078#1077#1085#1085#1086#1077' '#1088#1077#1096#1077#1085#1080#1077' %'
  end
  object cbxMetod: TComboBox
    Left = 6
    Top = 28
    Width = 236
    Height = 21
    Style = csDropDownList
    TabOrder = 0
    OnClick = cbxMetodClick
    Items.Strings = (
      #1058#1086#1095#1085#1086#1075#1086' '#1088#1077#1096#1077#1085#1080#1103
      #1055#1088#1080#1073#1083#1080#1078#1077#1085#1085#1086#1075#1086' '#1088#1077#1096#1077#1085#1080#1103)
  end
  object rgMetod: TRadioGroup
    Left = 6
    Top = 57
    Width = 236
    Height = 65
    ItemIndex = 0
    Items.Strings = (
      #1057#1083#1091#1095#1072#1081#1085#1086#1077' '#1089#1078#1072#1090#1080#1077
      #1057' '#1091#1095#1077#1090#1086#1084' '#1086#1075#1088#1072#1085#1080#1095#1077#1085#1080#1081' '#1085#1072' '#1087#1086#1082#1072#1079#1072#1090#1077#1083#1080)
    TabOrder = 1
  end
  object edPercent: TEdit
    Left = 160
    Top = 132
    Width = 81
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object btCancel: TButton
    Left = 168
    Top = 170
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 3
    OnClick = btCancelClick
  end
  object btOk: TButton
    Left = 80
    Top = 170
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    TabOrder = 4
    OnClick = btOkClick
  end
end
