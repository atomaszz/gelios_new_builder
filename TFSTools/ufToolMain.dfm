object fmToolMain: TfmToolMain
  Left = 158
  Top = 104
  Caption = #1057#1091#1087#1077#1088#1087#1086#1079#1080#1094#1080#1103' '#1092#1091#1085#1082#1094#1080#1086#1085#1072#1083#1100#1085#1086#1081' '#1089#1077#1090#1080
  ClientHeight = 562
  ClientWidth = 684
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
  object Splitter1: TSplitter
    Left = 0
    Top = 300
    Width = 684
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 35
    ExplicitWidth = 301
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 684
    Height = 35
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 680
    object Button1: TButton
      Left = 8
      Top = 5
      Width = 100
      Height = 25
      Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100
      TabOrder = 0
      OnClick = Button1Click
    end
    object Panel8: TPanel
      Left = 128
      Top = 2
      Width = 265
      Height = 30
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 1
      object Button2: TButton
        Left = 5
        Top = 4
        Width = 100
        Height = 23
        Caption = #1055#1086#1080#1089#1082
        TabOrder = 0
        OnClick = Button2Click
      end
      object edTransit: TEdit
        Left = 111
        Top = 5
        Width = 146
        Height = 21
        TabOrder = 1
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 303
    Width = 684
    Height = 218
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = 8
    ExplicitTop = 297
    ExplicitWidth = 680
    object Splitter2: TSplitter
      Left = 433
      Top = 0
      Height = 218
      Align = alRight
      ExplicitLeft = 96
      ExplicitTop = 128
      ExplicitHeight = 100
    end
    object Panel4: TPanel
      Left = 436
      Top = 0
      Width = 248
      Height = 218
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitLeft = 432
      ExplicitTop = 112
      object Panel5: TPanel
        Left = 0
        Top = 0
        Width = 248
        Height = 23
        Align = alTop
        BevelOuter = bvNone
        Caption = #1056#1072#1073#1086#1095#1080#1077' '#1086#1087#1077#1088#1072#1094#1080#1080
        TabOrder = 0
      end
      object mmRo: TMemo
        Left = 0
        Top = 23
        Width = 248
        Height = 195
        Align = alClient
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 1
        WordWrap = False
        ExplicitLeft = 51
        ExplicitTop = 37
      end
    end
    object Panel6: TPanel
      Left = 0
      Top = 0
      Width = 433
      Height = 218
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      ExplicitLeft = 175
      ExplicitTop = 104
      ExplicitWidth = 218
      object Panel7: TPanel
        Left = 0
        Top = 0
        Width = 433
        Height = 23
        Align = alTop
        BevelOuter = bvNone
        Caption = #1064#1072#1075#1080' '#1091#1082#1088#1091#1087#1085#1077#1085#1080#1103
        TabOrder = 0
        ExplicitLeft = 24
        ExplicitTop = 88
        ExplicitWidth = 218
      end
      object mmStep: TMemo
        Left = 0
        Top = 23
        Width = 433
        Height = 195
        Align = alClient
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 1
        WordWrap = False
        ExplicitLeft = 48
        ExplicitTop = 47
        ExplicitWidth = 429
      end
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 35
    Width = 684
    Height = 265
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = 16
    ExplicitTop = 8
    ExplicitWidth = 680
    ExplicitHeight = 225
    object mmSource: TMemo
      Left = 0
      Top = 0
      Width = 684
      Height = 265
      Align = alClient
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      ExplicitLeft = 40
      ExplicitTop = 3
      ExplicitWidth = 680
      ExplicitHeight = 167
    end
  end
  object Panel9: TPanel
    Left = 0
    Top = 521
    Width = 684
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitTop = 560
    ExplicitWidth = 680
    DesignSize = (
      684
      41)
    object Button3: TButton
      Left = 460
      Top = 9
      Width = 100
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1055#1088#1080#1085#1103#1090#1100
      TabOrder = 0
      ExplicitLeft = 456
    end
    object Button4: TButton
      Left = 577
      Top = 9
      Width = 100
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 1
      ExplicitLeft = 573
    end
  end
end
