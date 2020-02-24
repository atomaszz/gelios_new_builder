object frmPredicateView: TfrmPredicateView
  Left = 174
  Top = 129
  Caption = #1055#1088#1077#1076#1080#1082#1072#1090#1085#1072#1103' '#1084#1086#1076#1077#1083#1100
  ClientHeight = 402
  ClientWidth = 788
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 383
    Width = 788
    Height = 19
    Panels = <>
    ExplicitTop = 393
    ExplicitWidth = 796
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 788
    Height = 25
    ButtonHeight = 19
    ButtonWidth = 91
    Caption = 'ToolBar1'
    List = True
    ShowCaptions = True
    TabOrder = 1
    ExplicitWidth = 796
    object ToolButton1: TToolButton
      Left = 0
      Top = 0
      Action = acSave
      AutoSize = True
    end
    object ToolButton3: TToolButton
      Left = 64
      Top = 0
      Action = acLoadDopPrav
      AutoSize = True
    end
    object ToolButton4: TToolButton
      Left = 119
      Top = 0
      Action = acAll
      AutoSize = True
    end
    object ToolButton2: TToolButton
      Left = 209
      Top = 0
      Action = acExit
      AutoSize = True
    end
  end
  object PC: TPageControl
    Left = 0
    Top = 25
    Width = 788
    Height = 358
    ActivePage = tsStruct
    Align = alClient
    HotTrack = True
    TabOrder = 2
    ExplicitWidth = 796
    ExplicitHeight = 368
    object tsStruct: TTabSheet
      Caption = #1057#1090#1088#1091#1082#1090#1091#1088#1072
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object REStruct: TRichEdit
        Left = 0
        Top = 0
        Width = 788
        Height = 340
        Align = alClient
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        Zoom = 100
      end
    end
    object tsRab: TTabSheet
      Caption = #1056#1072#1073#1086#1095#1072#1103' '#1086#1087#1077#1088#1072#1094#1080#1103
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object RERab: TRichEdit
        Left = 0
        Top = 0
        Width = 788
        Height = 340
        Align = alClient
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        Zoom = 100
      end
    end
    object tsControlRab: TTabSheet
      Caption = #1050#1086#1085#1090#1088#1086#1083#1100' '#1088#1072#1073#1086#1090#1086#1089#1087#1086#1089#1086#1073#1085#1086#1089#1090#1080
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object REControlRab: TRichEdit
        Left = 0
        Top = 0
        Width = 788
        Height = 340
        Align = alClient
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        Zoom = 100
      end
    end
    object tsControlFunc: TTabSheet
      Caption = #1060#1091#1085#1082#1094#1080#1086#1085#1072#1083#1100#1085#1099#1081' '#1082#1086#1085#1090#1088#1086#1083#1100
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object REControlFunc: TRichEdit
        Left = 0
        Top = 0
        Width = 788
        Height = 340
        Align = alClient
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        Zoom = 100
      end
    end
    object tsCheckCondition: TTabSheet
      Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1091#1089#1083#1086#1074#1080#1103
      ImageIndex = 4
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object RECheckCondition: TRichEdit
        Left = 0
        Top = 0
        Width = 788
        Height = 340
        Align = alClient
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        Zoom = 100
      end
    end
    object tsOptZadacha: TTabSheet
      Caption = #1047#1072#1076#1072#1095#1072' '#1086#1087#1090#1080#1084#1080#1079#1072#1094#1080#1080
      ImageIndex = 6
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object REOptZadacha: TRichEdit
        Left = 0
        Top = 0
        Width = 788
        Height = 340
        Align = alClient
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        Zoom = 100
      end
    end
    object tsDopPrav: TTabSheet
      Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1087#1088#1072#1074#1080#1083#1072
      ImageIndex = 5
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object REDopPrav: TRichEdit
        Left = 0
        Top = 0
        Width = 788
        Height = 340
        Align = alClient
        ParentFont = False
        PlainText = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
        Zoom = 100
      end
    end
  end
  object SDG: TSaveDialog
    Left = 160
    Top = 80
  end
  object ActionList1: TActionList
    Left = 472
    Top = 128
    object acSave: TAction
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      ShortCut = 16467
      OnExecute = acSaveExecute
    end
    object acExit: TAction
      Caption = #1047#1072#1082#1088#1099#1090#1100
      ShortCut = 16465
      OnExecute = acExitExecute
    end
    object acLoadDopPrav: TAction
      Caption = #1054#1090#1082#1088#1099#1090#1100
      ShortCut = 16463
      OnExecute = acLoadDopPravExecute
      OnUpdate = acLoadDopPravUpdate
    end
    object acAll: TAction
      Caption = #1055#1086#1083#1085#1072#1103' '#1084#1086#1076#1077#1083#1100
      ShortCut = 16454
      OnExecute = acAllExecute
    end
  end
  object OD: TOpenDialog
    Left = 196
    Top = 109
  end
end
