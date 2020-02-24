object FmGridSovm: TFmGridSovm
  Left = 122
  Top = 104
  Caption = #1058#1072#1073#1083#1080#1094#1072' '#1086#1075#1088#1072#1085#1080#1095#1077#1085#1080#1081' '#1085#1072' '#1089#1086#1074#1084#1077#1089#1090#1080#1084#1086#1089#1090#1100
  ClientHeight = 416
  ClientWidth = 781
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 377
    Width = 781
    Height = 39
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      781
      39)
    object Button1: TButton
      Left = 817
      Top = 5
      Width = 140
      Height = 31
      Action = acCancel
      Anchors = [akTop, akRight]
      TabOrder = 0
    end
    object Button2: TButton
      Left = 634
      Top = 6
      Width = 140
      Height = 31
      Action = acSaveSovm
      Anchors = [akTop, akRight]
      TabOrder = 1
    end
  end
  object sgSovm: TStringGrid
    Left = 0
    Top = 39
    Width = 781
    Height = 338
    Align = alClient
    ColCount = 50
    DefaultColWidth = 40
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goColSizing, goEditing]
    TabOrder = 1
    ExplicitTop = 41
    ExplicitHeight = 336
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 781
    Height = 39
    AutoSize = True
    ButtonHeight = 39
    ButtonWidth = 118
    Caption = 'ToolBar1'
    Images = ImageList1
    ShowCaptions = True
    TabOrder = 2
    object ToolButton1: TToolButton
      Left = 0
      Top = 0
      Action = acGridSovmAdd
      AutoSize = True
    end
    object ToolButton2: TToolButton
      Left = 122
      Top = 0
      Action = acGridSovmDel
      AutoSize = True
    end
  end
  object ImageList1: TImageList
    Left = 472
    Top = 48
  end
  object ActionList1: TActionList
    Left = 600
    Top = 128
    object acGridSovmAdd: TAction
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
      OnExecute = acGridSovmAddExecute
    end
    object acGridSovmDel: TAction
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1090#1088#1086#1082#1091
      OnExecute = acGridSovmDelExecute
    end
    object acSaveSovm: TAction
      Caption = #1055#1088#1080#1085#1103#1090#1100
      OnExecute = acSaveSovmExecute
    end
    object acCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      ShortCut = 27
      OnExecute = acCancelExecute
    end
  end
end
