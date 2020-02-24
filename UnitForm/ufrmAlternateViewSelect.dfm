object frmAlternateViewSelect: TfrmAlternateViewSelect
  Left = 63
  Top = 107
  Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1091
  ClientHeight = 442
  ClientWidth = 866
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyUp = FormKeyUp
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnlMain: TPanel
    Left = 0
    Top = 383
    Width = 866
    Height = 40
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object Button1: TButton
      Left = 6
      Top = 8
      Width = 100
      Height = 25
      Action = acOk
      TabOrder = 0
    end
    object Button2: TButton
      Left = 114
      Top = 8
      Width = 100
      Height = 25
      Action = acCancel
      TabOrder = 1
    end
  end
  object SBar: TStatusBar
    Left = 0
    Top = 423
    Width = 866
    Height = 19
    Panels = <>
  end
  object sbX: TScrollBar
    Left = 0
    Top = 366
    Width = 866
    Height = 17
    Align = alBottom
    Max = 0
    PageSize = 0
    TabOrder = 2
    OnChange = sbXChange
  end
  object sbY: TScrollBar
    Left = 853
    Top = 0
    Width = 13
    Height = 366
    Align = alRight
    Kind = sbVertical
    Max = 0
    PageSize = 0
    TabOrder = 3
    OnChange = sbYChange
  end
  object TabControl: TTabControl
    Left = 0
    Top = 0
    Width = 853
    Height = 366
    Align = alClient
    TabOrder = 4
    OnChange = TabControlChange
    object pnlShow: TPanel
      Left = 4
      Top = 6
      Width = 845
      Height = 356
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
      OnResize = pnlShowResize
      object pbShow: TPaintBox
        Left = 0
        Top = 0
        Width = 845
        Height = 356
        Align = alClient
        OnPaint = pbShowPaint
        ExplicitWidth = 853
        ExplicitHeight = 367
      end
    end
  end
  object ActionList1: TActionList
    Left = 516
    Top = 94
    object acOk: TAction
      Caption = #1054#1082
      OnExecute = acOkExecute
      OnUpdate = acOkUpdate
    end
    object acCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1072
      OnExecute = acCancelExecute
    end
    object acCheckDoubles: TAction
      Caption = #1055#1088#1086#1074#1077#1088#1082#1072
      OnExecute = acCheckDoublesExecute
      OnUpdate = acCheckDoublesUpdate
    end
  end
end
