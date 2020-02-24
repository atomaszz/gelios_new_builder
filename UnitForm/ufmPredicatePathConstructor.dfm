object fmPredicatePathConstructor: TfmPredicatePathConstructor
  Left = 152
  Top = 145
  Caption = 
    #1040#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1086#1077' '#1092#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1077' '#1074#1086#1079#1084#1086#1078#1085#1099#1093' '#1074#1072#1088#1080#1072#1085#1090#1086#1074' '#1087#1086#1089#1090#1088#1086#1077#1085#1080#1103' '#1089#1091#1087#1077#1088 +
    #1087#1086#1079#1080#1094#1080#1080
  ClientHeight = 500
  ClientWidth = 822
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 822
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object Button3: TButton
      Left = 8
      Top = 8
      Width = 97
      Height = 25
      Action = acRun
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 464
    Width = 822
    Height = 36
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      822
      36)
    object Button1: TButton
      Left = 575
      Top = 6
      Width = 100
      Height = 25
      Action = acOk
      Anchors = [akTop, akRight]
      TabOrder = 0
    end
    object Button2: TButton
      Left = 696
      Top = 6
      Width = 100
      Height = 25
      Action = acCancel
      Anchors = [akTop, akRight]
      TabOrder = 1
    end
    object Button4: TButton
      Left = 9
      Top = 6
      Width = 136
      Height = 25
      Action = acShowPredicate
      TabOrder = 2
    end
  end
  object TabControl: TTabControl
    Left = 0
    Top = 41
    Width = 822
    Height = 369
    Align = alClient
    TabOrder = 2
    OnChange = TabControlChange
    object PageControl2: TPageControl
      Left = 4
      Top = 6
      Width = 814
      Height = 359
      ActivePage = TabSheet3
      Align = alClient
      Style = tsFlatButtons
      TabOrder = 0
      object TabSheet3: TTabSheet
        Caption = #1058#1072#1073#1083#1080#1095#1085#1086#1077' '#1087#1088#1077#1076#1089#1090#1072#1074#1083#1077#1085#1080#1077
        object Splitter1: TSplitter
          Left = 0
          Top = 140
          Width = 806
          Height = 2
          Cursor = crVSplit
          Align = alTop
          ExplicitWidth = 816
        end
        object sgTable: TStringGrid
          Left = 0
          Top = 0
          Width = 806
          Height = 140
          Align = alTop
          ColCount = 3
          DefaultRowHeight = 20
          RowCount = 2
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'Arial'
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
          ParentFont = False
          TabOrder = 0
          OnSelectCell = sgTableSelectCell
          ColWidths = (
            64
            64
            640)
          RowHeights = (
            20
            20)
        end
        object sgTableItems: TStringGrid
          Left = 0
          Top = 142
          Width = 806
          Height = 186
          Align = alClient
          ColCount = 6
          DefaultRowHeight = 20
          RowCount = 2
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'Arial'
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
          ParentFont = False
          TabOrder = 1
          ColWidths = (
            64
            64
            331
            64
            64
            64)
        end
      end
      object TabSheet4: TTabSheet
        Caption = #1042#1085#1091#1090#1088#1077#1085#1085#1077#1077' '#1087#1088#1077#1076#1089#1090#1072#1074#1083#1077#1085#1080#1077
        ImageIndex = 1
        object REText: TRichEdit
          Left = 0
          Top = 0
          Width = 806
          Height = 328
          Align = alClient
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          ScrollBars = ssBoth
          TabOrder = 0
          WordWrap = False
          Zoom = 100
        end
      end
    end
  end
  object pnlOzenk: TPanel
    Left = 0
    Top = 410
    Width = 822
    Height = 54
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 3
    Visible = False
    object Label1: TLabel
      Left = 10
      Top = 8
      Width = 96
      Height = 13
      Caption = #1054#1094#1077#1085#1082#1072' '#1084#1086#1097#1085#1086#1089#1090#1080':'
    end
    object Label2: TLabel
      Left = 10
      Top = 36
      Width = 153
      Height = 13
      Caption = #1054#1094#1077#1085#1082#1072' '#1090#1088#1091#1076#1086#1077#1084#1082#1086#1089#1090#1080'  ('#1084#1089#1077#1082'):'
    end
    object edPower: TEdit
      Left = 184
      Top = 5
      Width = 89
      Height = 21
      Color = clBtnFace
      TabOrder = 0
    end
    object edWork: TEdit
      Left = 184
      Top = 33
      Width = 89
      Height = 21
      Color = clBtnFace
      ReadOnly = True
      TabOrder = 1
    end
  end
  object ActionList1: TActionList
    Left = 528
    Top = 89
    object acRun: TAction
      Caption = #1057#1092#1086#1088#1084#1080#1088#1086#1074#1072#1090#1100
      OnExecute = acRunExecute
    end
    object acShowPredicate: TAction
      Caption = #1055#1086#1082#1072#1079#1072#1090#1100' '#1084#1086#1076#1077#1083#1100
      OnExecute = acShowPredicateExecute
      OnUpdate = acShowPredicateUpdate
    end
    object acOk: TAction
      Caption = #1055#1088#1080#1085#1103#1090#1100
      OnExecute = acOkExecute
      OnUpdate = acOkUpdate
    end
    object acCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1072
      OnExecute = acCancelExecute
    end
  end
end
