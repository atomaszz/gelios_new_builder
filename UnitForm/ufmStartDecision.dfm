object fmStartDecision: TfmStartDecision
  Left = 356
  Top = 264
  BorderStyle = bsDialog
  Caption = #1055#1086#1089#1090#1072#1085#1086#1074#1082#1072' '#1079#1072#1076#1072#1095#1080
  ClientHeight = 323
  ClientWidth = 421
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 421
    Height = 81
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object Label3: TLabel
      Left = 8
      Top = 7
      Width = 127
      Height = 13
      Caption = #1042#1080#1076' '#1079#1072#1076#1072#1095#1080' '#1086#1087#1090#1080#1084#1080#1079#1072#1094#1080#1080
    end
    object Bevel1: TBevel
      Left = 0
      Top = 0
      Width = 421
      Height = 81
      Align = alClient
    end
    object Edit1: TEdit
      Left = 8
      Top = 24
      Width = 361
      Height = 17
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      Text = 'Edit1'
    end
    object Edit5: TEdit
      Left = 8
      Top = 48
      Width = 361
      Height = 17
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      Text = 'Edit1'
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 119
    Width = 421
    Height = 163
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Label4: TLabel
      Left = 8
      Top = 9
      Width = 66
      Height = 13
      Caption = #1054#1075#1088#1072#1085#1080#1095#1077#1085#1080#1103
    end
    object Label5: TLabel
      Left = 8
      Top = 86
      Width = 135
      Height = 13
      Caption = #1047#1085#1072#1095#1077#1085#1080#1103' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1086#1074' '
    end
    object Label6: TLabel
      Left = 8
      Top = 136
      Width = 83
      Height = 13
      Caption = #1058#1080#1087' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
    end
    object Bevel2: TBevel
      Left = 0
      Top = 0
      Width = 421
      Height = 163
      Align = alClient
    end
    object Edit3: TEdit
      Left = 85
      Top = 32
      Width = 289
      Height = 17
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      Text = 'Edit1'
    end
    object Edit2: TEdit
      Left = 85
      Top = 8
      Width = 289
      Height = 17
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      Text = 'Edit1'
    end
    object Edit7: TEdit
      Left = 84
      Top = 56
      Width = 289
      Height = 17
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
      Text = 'Edit1'
    end
    object Edit4: TEdit
      Left = 8
      Top = 104
      Width = 361
      Height = 17
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
      Text = 'Edit4'
    end
    object Edit6: TEdit
      Left = 102
      Top = 135
      Width = 273
      Height = 17
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
      Text = 'Edit6'
    end
  end
  object pnPribl: TPanel
    Left = 0
    Top = 81
    Width = 421
    Height = 38
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    object Label7: TLabel
      Left = 11
      Top = 12
      Width = 134
      Height = 13
      Caption = #1055#1088#1080#1073#1083#1080#1078#1077#1085#1085#1086#1077' '#1088#1077#1096#1077#1085#1080#1077' %'
    end
    object edPercent: TEdit
      Left = 160
      Top = 8
      Width = 249
      Height = 21
      TabOrder = 0
      Text = '0'
      OnExit = edPercentExit
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 282
    Width = 421
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 3
    object Button1: TButton
      Left = 2
      Top = 8
      Width = 100
      Height = 25
      Action = acStart
      TabOrder = 0
    end
    object Button3: TButton
      Left = 314
      Top = 8
      Width = 100
      Height = 25
      Action = acCancel
      TabOrder = 1
    end
    object Button2: TButton
      Left = 106
      Top = 8
      Width = 100
      Height = 25
      Action = acTrack
      TabOrder = 2
    end
    object Button4: TButton
      Left = 210
      Top = 8
      Width = 100
      Height = 25
      Action = acOzenka
      TabOrder = 3
    end
  end
  object ActionList1: TActionList
    Left = 320
    Top = 127
    object acStart: TAction
      Caption = #1053#1072#1081#1090#1080' '#1088#1077#1096#1077#1085#1080#1077
      ShortCut = 13
      OnExecute = acStartExecute
    end
    object acCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1072
      ShortCut = 27
      OnExecute = acCancelExecute
    end
    object acTrack: TAction
      Caption = #1061#1086#1076' '#1088#1077#1096#1077#1085#1080#1103
      OnExecute = acTrackExecute
    end
    object acOzenka: TAction
      Caption = #1054#1094#1077#1085#1082#1072
      OnExecute = acOzenkaExecute
      OnUpdate = acOzenkaUpdate
    end
  end
end
