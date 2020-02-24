object fmTrackShow: TfmTrackShow
  Left = 212
  Top = 166
  Caption = #1061#1086#1076' '#1088#1077#1096#1077#1085#1080#1103
  ClientHeight = 435
  ClientWidth = 678
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 678
    Height = 29
    ButtonHeight = 21
    ButtonWidth = 62
    Caption = 'ToolBar1'
    ShowCaptions = True
    TabOrder = 0
    object ToolButton1: TToolButton
      Left = 0
      Top = 0
      Action = acTrackAccept
    end
    object ToolButton2: TToolButton
      Left = 62
      Top = 0
      Action = acTrackCheck
    end
    object ToolButton4: TToolButton
      Left = 124
      Top = 0
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      DropdownMenu = pmCreateTrack
      ImageIndex = 0
    end
    object ToolButton3: TToolButton
      Left = 186
      Top = 0
      Action = acCancel
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 416
    Width = 678
    Height = 19
    Panels = <>
  end
  object PageControl: TPageControl
    Left = 0
    Top = 29
    Width = 678
    Height = 387
    ActivePage = tsTable
    Align = alClient
    TabOrder = 2
    OnChange = PageControlChange
    object tsTable: TTabSheet
      Caption = #1042' '#1074#1080#1076#1077' '#1090#1072#1073#1083#1080#1094#1099
      object sgModel: TStringGrid
        Left = 0
        Top = 0
        Width = 670
        Height = 359
        Align = alClient
        ColCount = 4
        DefaultRowHeight = 20
        FixedCols = 0
        RowCount = 2
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Arial'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
        ParentFont = False
        TabOrder = 0
        OnDrawCell = sgModelDrawCell
        ColWidths = (
          102
          108
          92
          226)
      end
    end
    object tsPredicate: TTabSheet
      Caption = #1042#1085#1091#1090#1088#1077#1085#1085#1077#1077' '#1087#1088#1077#1076#1089#1090#1072#1074#1083#1077#1085#1080#1077
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object REPredicate: TRichEdit
        Left = 0
        Top = 0
        Width = 670
        Height = 359
        Align = alClient
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
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
  object ActionList1: TActionList
    Left = 556
    Top = 85
    object acTrackAccept: TAction
      Caption = #1055#1088#1080#1085#1103#1090#1100
      OnExecute = acTrackAcceptExecute
    end
    object acTrackCheck: TAction
      Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100
      OnExecute = acTrackCheckExecute
    end
    object acCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1072
      ShortCut = 27
      OnExecute = acCancelExecute
    end
    object acCreateManual: TAction
      Caption = #1042' '#1088#1091#1095#1085#1086#1084' '#1088#1077#1078#1080#1084#1077
      OnExecute = acCreateManualExecute
    end
    object acCreateAuto: TAction
      Caption = #1042' '#1072#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1086#1084' '#1088#1077#1078#1080#1084#1077
      OnExecute = acCreateAutoExecute
    end
  end
  object pmCreateTrack: TPopupMenu
    Left = 420
    Top = 141
    object N1: TMenuItem
      Action = acCreateManual
    end
    object N2: TMenuItem
      Action = acCreateAuto
    end
  end
end
