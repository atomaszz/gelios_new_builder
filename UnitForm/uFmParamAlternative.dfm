object fmParamAlternative: TfmParamAlternative
  Left = 107
  Top = 48
  Caption = #1060#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1080#1095#1077#1089#1082#1080#1093' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074
  ClientHeight = 579
  ClientWidth = 784
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 538
    Width = 784
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 816
    DesignSize = (
      784
      41)
    object Button1: TButton
      Left = 657
      Top = 6
      Width = 119
      Height = 31
      Action = acExit
      Anchors = [akTop, akRight]
      TabOrder = 0
      ExplicitLeft = 689
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 203
    Width = 784
    Height = 335
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 816
    object sgParam: TStringGrid
      Left = 0
      Top = 0
      Width = 784
      Height = 335
      Align = alClient
      ColCount = 1
      DefaultColWidth = 100
      DefaultRowHeight = 18
      FixedCols = 0
      RowCount = 1
      FixedRows = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect]
      TabOrder = 0
      OnDblClick = sgParamDblClick
      ExplicitWidth = 816
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 43
    Width = 784
    Height = 160
    Align = alTop
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    ExplicitWidth = 816
    DesignSize = (
      784
      160)
    object Label1: TLabel
      Left = 261
      Top = 90
      Width = 94
      Height = 16
      Caption = #1058#1080#1087' '#1087#1086#1076#1073#1083#1086#1082#1072':'
      Transparent = True
    end
    object Label13: TLabel
      Left = 261
      Top = 126
      Width = 111
      Height = 16
      Caption = #1058#1080#1087' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074':'
      Transparent = True
    end
    object lbNum: TLabel
      Left = 780
      Top = 18
      Width = -25
      Height = 16
      Alignment = taRightJustify
      Anchors = [akLeft, akTop, akRight]
      Caption = '0'
      Transparent = True
      ExplicitWidth = -15
    end
    object lbCount: TLabel
      Left = 780
      Top = 54
      Width = -25
      Height = 16
      Alignment = taRightJustify
      Anchors = [akLeft, akTop, akRight]
      Caption = '0'
      ExplicitWidth = -15
    end
    object lbType: TLabel
      Left = 780
      Top = 90
      Width = -25
      Height = 16
      Alignment = taRightJustify
      Anchors = [akLeft, akTop, akRight]
      Caption = '0'
      ExplicitWidth = -15
    end
    object lbTypeParam: TLabel
      Left = 780
      Top = 126
      Width = -25
      Height = 16
      Alignment = taRightJustify
      Anchors = [akLeft, akTop, akRight]
      Caption = '0'
      ExplicitWidth = -15
    end
    object Label6: TLabel
      Left = 261
      Top = 18
      Width = 151
      Height = 16
      Caption = #1053#1086#1084#1077#1088' '#1073#1083#1086#1082#1072'-'#1088#1086#1076#1080#1090#1077#1083#1103
      Transparent = True
    end
    object Label7: TLabel
      Left = 261
      Top = 54
      Width = 285
      Height = 16
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1087#1072#1088#1072#1084#1077#1090#1088#1080#1095#1077#1089#1082#1080#1093' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074
      Transparent = True
    end
    object Shape4: TShape
      Left = 254
      Top = 118
      Width = 522
      Height = 31
      Anchors = [akLeft, akTop, akRight]
      Brush.Style = bsClear
      ExplicitWidth = 532
    end
    object Shape1: TShape
      Left = 254
      Top = 82
      Width = 522
      Height = 31
      Anchors = [akLeft, akTop, akRight]
      Brush.Style = bsClear
      ExplicitWidth = 532
    end
    object Shape2: TShape
      Left = 254
      Top = 47
      Width = 522
      Height = 31
      Anchors = [akLeft, akTop, akRight]
      Brush.Style = bsClear
      ExplicitWidth = 532
    end
    object Shape3: TShape
      Left = 254
      Top = 11
      Width = 522
      Height = 31
      Anchors = [akLeft, akTop, akRight]
      Brush.Style = bsClear
      ExplicitWidth = 532
    end
    object Panel4: TPanel
      Left = 5
      Top = 5
      Width = 240
      Height = 149
      BevelInner = bvLowered
      TabOrder = 0
      object pbTfs: TPaintBox
        Left = 2
        Top = 2
        Width = 236
        Height = 145
        Align = alClient
        OnPaint = pbTfsPaint
      end
    end
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 784
    Height = 43
    AutoSize = True
    ButtonHeight = 43
    ButtonWidth = 242
    Caption = 'ToolBar1'
    Images = ImageList1
    ShowCaptions = True
    TabOrder = 3
    ExplicitWidth = 816
    object ToolButton1: TToolButton
      Left = 0
      Top = 0
      Action = acAdd
      AutoSize = True
    end
    object ToolButton2: TToolButton
      Left = 170
      Top = 0
      Action = acDel
      AutoSize = True
    end
    object ToolButton4: TToolButton
      Left = 332
      Top = 0
      Action = acForm
      AutoSize = True
    end
  end
  object ActionList1: TActionList
    Images = ImageList1
    Left = 664
    Top = 8
    object acAdd: TAction
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1091
      ImageIndex = 0
      OnExecute = acAddExecute
    end
    object acDel: TAction
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1091
      OnExecute = acDelExecute
      OnUpdate = acDelUpdate
    end
    object acForm: TAction
      Caption = #1060#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1077' '#1087#1072#1088#1072#1084'. '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074
      OnExecute = acFormExecute
    end
    object acExit: TAction
      Caption = #1042#1099#1093#1086#1076
      ShortCut = 27
      OnExecute = acExitExecute
    end
  end
  object ImageList1: TImageList
    Height = 20
    Width = 20
    Left = 728
  end
end
