object fmPredicatePathView: TfmPredicatePathView
  Left = 108
  Top = 121
  Caption = #1052#1077#1090#1086#1076' '#1087#1086#1089#1090#1088#1086#1077#1085#1080#1103' '#1089#1091#1087#1077#1088#1087#1086#1079#1080#1094#1080#1080
  ClientHeight = 403
  ClientWidth = 850
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object PageControl1: TPageControl
    Left = 0
    Top = 24
    Width = 850
    Height = 379
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1054#1089#1085#1086#1074#1085#1086#1081' '#1084#1077#1090#1086#1076
      object PageControl2: TPageControl
        Left = 0
        Top = 0
        Width = 842
        Height = 348
        ActivePage = TabSheet3
        Align = alClient
        Style = tsFlatButtons
        TabOrder = 0
        object TabSheet3: TTabSheet
          Caption = #1058#1072#1073#1083#1080#1095#1085#1086#1077' '#1087#1088#1077#1076#1089#1090#1072#1074#1083#1077#1085#1080#1077
          object Splitter1: TSplitter
            Left = 0
            Top = 172
            Width = 834
            Height = 4
            Cursor = crVSplit
            Align = alTop
            ExplicitWidth = 844
          end
          object sgBase: TStringGrid
            Left = 0
            Top = 0
            Width = 834
            Height = 172
            Align = alTop
            ColCount = 3
            DefaultRowHeight = 20
            RowCount = 2
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -17
            Font.Name = 'Arial'
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
            ParentFont = False
            TabOrder = 0
            OnSelectCell = sgBaseSelectCell
            ColWidths = (
              64
              64
              640)
            RowHeights = (
              20
              20)
          end
          object sgBaseItems: TStringGrid
            Left = 0
            Top = 176
            Width = 834
            Height = 138
            Align = alClient
            ColCount = 6
            DefaultRowHeight = 20
            RowCount = 2
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -17
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
          object REBase: TRichEdit
            Left = 0
            Top = 0
            Width = 834
            Height = 314
            Align = alClient
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -18
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
    object TabSheet2: TTabSheet
      Caption = #1058#1077#1082#1091#1097#1080#1081' '#1084#1077#1090#1086#1076
      ImageIndex = 1
      object PageControl3: TPageControl
        Left = 0
        Top = 0
        Width = 842
        Height = 348
        ActivePage = tsUsedGrid
        Align = alClient
        Style = tsFlatButtons
        TabOrder = 0
        OnChange = PageControl3Change
        OnChanging = PageControl3Changing
        object tsUsedGrid: TTabSheet
          Caption = #1058#1072#1073#1083#1080#1095#1085#1086#1077' '#1087#1088#1077#1076#1089#1090#1072#1074#1083#1077#1085#1080#1077
          object Splitter2: TSplitter
            Left = 0
            Top = 172
            Width = 834
            Height = 4
            Cursor = crVSplit
            Align = alTop
            ExplicitWidth = 835
          end
          object sgUsed: TStringGrid
            Left = 0
            Top = 0
            Width = 834
            Height = 172
            Align = alTop
            ColCount = 3
            DefaultRowHeight = 20
            RowCount = 2
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -17
            Font.Name = 'Arial'
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
            ParentFont = False
            TabOrder = 0
            OnSelectCell = sgUsedSelectCell
            ColWidths = (
              64
              64
              650)
          end
          object sgUsedItems: TStringGrid
            Left = 0
            Top = 176
            Width = 732
            Height = 138
            Align = alClient
            ColCount = 6
            DefaultRowHeight = 20
            RowCount = 2
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -17
            Font.Name = 'Arial'
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
            ParentFont = False
            TabOrder = 1
            ColWidths = (
              64
              64
              309
              64
              64
              64)
          end
          object Panel1: TPanel
            Left = 732
            Top = 176
            Width = 102
            Height = 138
            Align = alRight
            BevelOuter = bvNone
            TabOrder = 2
            object Button1: TButton
              Left = 16
              Top = 8
              Width = 75
              Height = 25
              Action = acUp
              TabOrder = 0
            end
            object Button2: TButton
              Left = 16
              Top = 40
              Width = 75
              Height = 25
              Action = acDown
              TabOrder = 1
            end
          end
        end
        object tsUsedEdit: TTabSheet
          Caption = #1042#1085#1091#1090#1088#1077#1085#1085#1077#1077' '#1087#1088#1077#1076#1089#1090#1072#1074#1083#1077#1085#1080#1077
          ImageIndex = 1
          object REUsed: TRichEdit
            Left = 0
            Top = 0
            Width = 834
            Height = 314
            Align = alClient
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -18
            Font.Name = 'Courier New'
            Font.Style = []
            ParentFont = False
            ScrollBars = ssBoth
            TabOrder = 0
            WordWrap = False
            Zoom = 100
          end
        end
      end
    end
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 850
    Height = 24
    AutoSize = True
    ButtonHeight = 24
    ButtonWidth = 254
    Caption = 'ToolBar1'
    EdgeInner = esNone
    EdgeOuter = esNone
    ShowCaptions = True
    TabOrder = 1
    object ToolButton1: TToolButton
      Left = 0
      Top = 0
      Action = acCreate
      AutoSize = True
    end
    object ToolButton2: TToolButton
      Left = 258
      Top = 0
      Action = acShowPredicate
      AutoSize = True
    end
    object ToolButton4: TToolButton
      Left = 383
      Top = 0
      Action = acOk
      AutoSize = True
    end
    object ToolButton5: TToolButton
      Left = 449
      Top = 0
      Action = acCancel
      AutoSize = True
    end
  end
  object ActionList1: TActionList
    Left = 548
    Top = 64
    object acOk: TAction
      Caption = #1055#1088#1080#1085#1103#1090#1100
      OnExecute = acOkExecute
    end
    object acCancel: TAction
      Caption = #1047#1072#1082#1088#1099#1090#1100
      OnExecute = acCancelExecute
    end
    object acCreate: TAction
      Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100' '#1074' '#1072#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1086#1084' '#1088#1077#1078#1080#1084#1077
      OnExecute = acCreateExecute
      OnUpdate = acCreateUpdate
    end
    object acShowPredicate: TAction
      Caption = #1055#1086#1082#1072#1079#1072#1090#1100' '#1084#1086#1076#1077#1083#1100
      OnExecute = acShowPredicateExecute
    end
    object acUp: TAction
      Caption = #1042#1074#1077#1088#1093
      OnExecute = acUpExecute
    end
    object acDown: TAction
      Caption = #1042#1085#1080#1079
      OnExecute = acDownExecute
    end
  end
end
