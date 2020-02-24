object fmPredicateFull: TfmPredicateFull
  Left = 192
  Top = 103
  Caption = #1055#1088#1077#1076#1074#1072#1088#1080#1090#1077#1083#1100#1085#1099#1081' '#1087#1088#1086#1089#1084#1086#1090#1088' '#1087#1086#1083#1085#1086#1081' '#1087#1088#1077#1076#1080#1082#1072#1090#1085#1086#1081' '#1084#1086#1076#1077#1083#1080
  ClientHeight = 435
  ClientWidth = 710
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 710
    Height = 35
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      710
      35)
    object Label1: TLabel
      Left = 177
      Top = 10
      Width = 26
      Height = 13
      Caption = #1062#1077#1083#1100
    end
    object edZel: TEdit
      Left = 216
      Top = 6
      Width = 319
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
    end
    object STResult: TEdit
      Left = 542
      Top = 6
      Width = 164
      Height = 21
      Anchors = [akTop, akRight]
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object Button1: TButton
      Left = 6
      Top = 5
      Width = 155
      Height = 25
      Action = acRun
      TabOrder = 2
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 401
    Width = 710
    Height = 34
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      710
      34)
    object Button2: TButton
      Left = 606
      Top = 4
      Width = 98
      Height = 25
      Action = acExit
      Anchors = [akTop, akRight]
      TabOrder = 0
    end
  end
  object REModel: TRichEdit
    Left = 0
    Top = 35
    Width = 710
    Height = 366
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    PlainText = True
    ScrollBars = ssBoth
    TabOrder = 2
    WordWrap = False
    Zoom = 100
  end
  object ActionList1: TActionList
    Left = 512
    Top = 56
    object acRun: TAction
      Caption = #1048#1085#1090#1077#1088#1087#1088#1077#1090#1080#1088#1086#1074#1072#1090#1100' (F9)'
      ShortCut = 120
      OnExecute = acRunExecute
      OnUpdate = acRunUpdate
    end
    object acExit: TAction
      Caption = #1042#1099#1093#1086#1076
      ShortCut = 27
      OnExecute = acExitExecute
    end
  end
end
