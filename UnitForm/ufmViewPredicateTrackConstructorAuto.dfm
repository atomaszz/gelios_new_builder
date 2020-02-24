object fmViewPredicateTrackConstructorAuto: TfmViewPredicateTrackConstructorAuto
  Left = 255
  Top = 162
  Caption = #1055#1086#1089#1083#1077#1076#1086#1074#1072#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1086#1073#1093#1086#1076#1072
  ClientHeight = 372
  ClientWidth = 687
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
  object Panel1: TPanel
    Left = 0
    Top = 337
    Width = 687
    Height = 35
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      687
      35)
    object Button1: TButton
      Left = 460
      Top = 6
      Width = 100
      Height = 25
      Action = acOk
      Anchors = [akTop, akRight]
      TabOrder = 0
    end
    object Button2: TButton
      Left = 581
      Top = 6
      Width = 100
      Height = 25
      Action = acCancel
      Anchors = [akTop, akRight]
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 687
    Height = 41
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 1
    object Label1: TLabel
      Left = 96
      Top = 13
      Width = 115
      Height = 13
      Caption = #1044#1086#1087#1091#1089#1090#1080#1084#1099#1081' '#1087#1088#1086#1094#1077#1085#1090': '
    end
    object Label2: TLabel
      Left = 320
      Top = 13
      Width = 116
      Height = 13
      Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1086#1077' '#1082#1086#1083'-'#1074#1086':'
    end
    object edPercent: TEdit
      Left = 216
      Top = 10
      Width = 73
      Height = 21
      TabOrder = 0
      Text = '100'
    end
    object Button3: TButton
      Left = 8
      Top = 6
      Width = 75
      Height = 25
      Action = acRun
      TabOrder = 1
    end
    object edCount: TEdit
      Left = 443
      Top = 10
      Width = 73
      Height = 21
      TabOrder = 2
      Text = '1000'
    end
  end
  object TabControl: TTabControl
    Left = 0
    Top = 41
    Width = 687
    Height = 296
    Align = alClient
    TabOrder = 2
    OnChange = TabControlChange
    object REPredicate: TRichEdit
      Left = 4
      Top = 6
      Width = 679
      Height = 286
      Align = alClient
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
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
  object ActionList1: TActionList
    Left = 624
    Top = 88
    object acRun: TAction
      Caption = #1055#1091#1089#1082
      OnExecute = acRunExecute
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
