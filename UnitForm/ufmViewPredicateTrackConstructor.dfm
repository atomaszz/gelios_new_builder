object fmViewPredicateTrackConstructor: TfmViewPredicateTrackConstructor
  Left = 227
  Top = 173
  Caption = #1055#1086#1089#1083#1077#1076#1086#1074#1072#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1086#1073#1093#1086#1076#1072
  ClientHeight = 440
  ClientWidth = 681
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 145
    Width = 681
    Height = 4
    Cursor = crVSplit
    Align = alTop
    Beveled = True
    ExplicitWidth = 689
  end
  object Panel1: TPanel
    Left = 0
    Top = 405
    Width = 681
    Height = 35
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object Button1: TButton
      Left = 450
      Top = 6
      Width = 100
      Height = 25
      Action = acOk
      TabOrder = 0
    end
    object Button2: TButton
      Left = 571
      Top = 6
      Width = 100
      Height = 25
      Action = acCancel
      TabOrder = 1
    end
  end
  object Panel5: TPanel
    Left = 0
    Top = 0
    Width = 681
    Height = 145
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object sgBase: TStringGrid
      Left = 0
      Top = 0
      Width = 681
      Height = 145
      Align = alClient
      ColCount = 4
      DefaultRowHeight = 20
      FixedCols = 0
      RowCount = 2
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
      ParentFont = False
      TabOrder = 0
      OnDblClick = sgBaseDblClick
      OnDrawCell = sgBaseDrawCell
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 149
    Width = 681
    Height = 256
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object Panel3: TPanel
      Left = 0
      Top = 25
      Width = 681
      Height = 231
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
      object sgResult: TStringGrid
        Left = 0
        Top = 0
        Width = 681
        Height = 231
        Align = alClient
        ColCount = 4
        DefaultRowHeight = 20
        FixedCols = 0
        RowCount = 2
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
        ParentFont = False
        TabOrder = 0
        OnDrawCell = sgResultDrawCell
      end
    end
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 681
      Height = 25
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object ToolBar1: TToolBar
        Left = 0
        Top = 2
        Width = 681
        Height = 23
        Align = alBottom
        ButtonHeight = 21
        ButtonWidth = 37
        Caption = 'ToolBar1'
        EdgeInner = esNone
        EdgeOuter = esNone
        ShowCaptions = True
        TabOrder = 0
        object ToolButton1: TToolButton
          Left = 0
          Top = 0
          Action = acDown
        end
        object ToolButton2: TToolButton
          Left = 37
          Top = 0
          Action = acUp
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 576
    Top = 293
    object acUp: TAction
      Caption = #1042#1074#1077#1088#1093
      OnExecute = acUpExecute
      OnUpdate = acUpUpdate
    end
    object acDown: TAction
      Caption = #1042#1085#1080#1079
      OnExecute = acDownExecute
      OnUpdate = acDownUpdate
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
