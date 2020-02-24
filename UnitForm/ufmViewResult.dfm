object fmViewResult: TfmViewResult
  Left = 189
  Top = 107
  Caption = #1055#1088#1086#1089#1084#1086#1090#1088' '#1088#1077#1096#1077#1085#1080#1103
  ClientHeight = 461
  ClientWidth = 719
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 120
  TextHeight = 16
  object StatusBar1: TStatusBar
    Left = 0
    Top = 442
    Width = 719
    Height = 19
    Panels = <>
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 719
    Height = 27
    ButtonHeight = 24
    ButtonWidth = 222
    Caption = 'ToolBar1'
    ShowCaptions = True
    TabOrder = 1
    object ToolButton1: TToolButton
      Left = 0
      Top = 0
      Action = acSaveResult
      AutoSize = True
    end
    object ToolButton4: TToolButton
      Left = 80
      Top = 0
      Action = acShowParam
      AutoSize = True
    end
    object ToolButton2: TToolButton
      Left = 306
      Top = 0
      Width = 8
      Caption = 'ToolButton2'
      ImageIndex = 0
      Style = tbsSeparator
    end
    object ToolButton3: TToolButton
      Left = 314
      Top = 0
      Action = acClose
      AutoSize = True
    end
  end
  object pnlView: TPanel
    Left = 0
    Top = 27
    Width = 695
    Height = 395
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    OnResize = pnlViewResize
    object pbView: TPaintBox
      Left = 0
      Top = 0
      Width = 695
      Height = 395
      Align = alClient
      OnMouseDown = pbViewMouseDown
      OnMouseUp = pbViewMouseUp
      OnPaint = pbViewPaint
      ExplicitWidth = 705
      ExplicitHeight = 408
    end
  end
  object sbX: TScrollBar
    Left = 0
    Top = 422
    Width = 719
    Height = 20
    Align = alBottom
    PageSize = 0
    TabOrder = 3
    OnChange = sbXChange
  end
  object sbY: TScrollBar
    Left = 695
    Top = 27
    Width = 24
    Height = 395
    Align = alRight
    Kind = sbVertical
    PageSize = 0
    TabOrder = 4
    OnChange = sbYChange
  end
  object SaveDLG: TSaveDialog
    Filter = #1041#1080#1085#1072#1088#1085#1099#1081' '#1092#1072#1081#1083' (*.gls)|*.gls|XML '#1092#1072#1081#1083' (*.xml)|*.xml'
    Left = 366
    Top = 136
  end
  object ActionList1: TActionList
    Left = 544
    Top = 93
    object acSaveResult: TAction
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      OnExecute = acSaveResultExecute
    end
    object acClose: TAction
      Caption = #1042#1099#1081#1090#1080
      ShortCut = 27
      OnExecute = acCloseExecute
    end
    object acShowParam: TAction
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1080#1095#1077#1089#1082#1072#1103' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1072
      OnExecute = acShowParamExecute
      OnUpdate = acShowParamUpdate
    end
  end
  object pmMenu: TPopupMenu
    Left = 248
    Top = 163
    object N1: TMenuItem
      Action = acShowParam
    end
  end
end
