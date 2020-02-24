object FmSetup: TFmSetup
  Left = 513
  Top = 199
  BorderStyle = bsDialog
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 279
  ClientWidth = 402
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 402
    Height = 238
    ActivePage = TabSheet1
    Align = alClient
    HotTrack = True
    TabOrder = 0
    OnChange = PageControl1Change
    object TabSheet1: TTabSheet
      Caption = #1054#1073#1097#1080#1077
      object Label1: TLabel
        Left = 64
        Top = 17
        Width = 71
        Height = 13
        Caption = #1064#1080#1088#1080#1085#1072' '#1089#1077#1090#1082#1080
      end
      object shpFon: TShape
        Left = 8
        Top = 98
        Width = 49
        Height = 22
        OnMouseUp = shpFonMouseUp
      end
      object Label3: TLabel
        Left = 72
        Top = 102
        Width = 167
        Height = 13
        Caption = #1062#1074#1077#1090' '#1092#1086#1085#1072' '#1086#1082#1085#1072' '#1087#1088#1086#1077#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103
      end
      object Label4: TLabel
        Left = 72
        Top = 131
        Width = 103
        Height = 13
        Caption = #1062#1074#1077#1090' '#1090#1086#1095#1082#1080' '#1085#1072' '#1089#1077#1090#1082#1077
      end
      object shpPixel: TShape
        Left = 8
        Top = 127
        Width = 49
        Height = 22
        OnMouseUp = shpPixelMouseUp
      end
      object edStepPixel: TEdit
        Left = 8
        Top = 13
        Width = 49
        Height = 21
        TabOrder = 0
        Text = '5'
        OnExit = edStepPixelExit
      end
      object cbPaintPixels: TCheckBox
        Left = 8
        Top = 48
        Width = 127
        Height = 17
        Caption = #1056#1080#1089#1086#1074#1072#1090#1100' '#1089#1077#1090#1082#1091
        TabOrder = 1
        OnClick = cbPaintPixelsClick
      end
      object GroupBox1: TGroupBox
        Left = 8
        Top = 158
        Width = 265
        Height = 49
        Caption = #1051#1080#1085#1080#1103' '#1086#1073#1088#1072#1084#1083#1077#1085#1080#1103
        TabOrder = 2
        object Label2: TLabel
          Left = 216
          Top = 20
          Width = 25
          Height = 13
          Caption = #1062#1074#1077#1090
        end
        object shpFrameLineColor: TShape
          Left = 160
          Top = 15
          Width = 49
          Height = 22
          OnMouseUp = shpFrameLineColorMouseUp
        end
        object cbDrawFrameLine: TCheckBox
          Left = 12
          Top = 19
          Width = 81
          Height = 17
          Caption = #1056#1080#1089#1086#1074#1072#1090#1100
          TabOrder = 0
          OnClick = cbDrawFrameLineClick
        end
      end
      object cbSectionBarAlternativeColor: TCheckBox
        Left = 8
        Top = 71
        Width = 295
        Height = 17
        Caption = #1040#1083#1090#1077#1088#1085#1072#1090#1080#1074#1085#1099#1081' '#1092#1086#1085' '#1089#1077#1082#1094#1080#1080' '#1074#1099#1073#1086#1088#1072' '#1058#1060#1057
        TabOrder = 3
        OnClick = cbSectionBarAlternativeColorClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1058#1060#1057
      ImageIndex = 1
      object shpLineColor: TShape
        Left = 8
        Top = 37
        Width = 49
        Height = 22
        OnMouseUp = shpLineColorMouseUp
      end
      object Label5: TLabel
        Left = 64
        Top = 42
        Width = 58
        Height = 13
        Caption = #1062#1074#1077#1090' '#1083#1080#1085#1080#1080
      end
      object shpBrushColor: TShape
        Left = 8
        Top = 101
        Width = 49
        Height = 22
        OnMouseUp = shpBrushColorMouseUp
      end
      object Label6: TLabel
        Left = 64
        Top = 106
        Width = 70
        Height = 13
        Caption = #1062#1074#1077#1090' '#1079#1072#1083#1080#1074#1082#1080
      end
      object pbFont: TPaintBox
        Left = 8
        Top = 136
        Width = 73
        Height = 41
        OnPaint = pbFontPaint
      end
      object Label7: TLabel
        Left = 172
        Top = 11
        Width = 68
        Height = 13
        Caption = #1058#1080#1087' '#1092#1083#1072#1078#1082#1086#1074
      end
      object Label8: TLabel
        Left = 172
        Top = 42
        Width = 68
        Height = 13
        Caption = #1062#1074#1077#1090' '#1092#1083#1072#1078#1082#1072
      end
      object shpColorLeave: TShape
        Left = 336
        Top = 37
        Width = 49
        Height = 22
        OnMouseUp = shpColorLeaveMouseUp
      end
      object Label9: TLabel
        Left = 172
        Top = 67
        Width = 132
        Height = 13
        Caption = #1062#1074#1077#1090' '#1074#1099#1073#1088#1072#1085#1085#1086#1075#1086' '#1092#1083#1072#1078#1082#1072
      end
      object shpColorEnter: TShape
        Left = 336
        Top = 63
        Width = 49
        Height = 22
        OnMouseUp = shpColorEnterMouseUp
      end
      object shpFrameColorTFE: TShape
        Left = 336
        Top = 89
        Width = 49
        Height = 22
        OnMouseUp = shpFrameColorTFEMouseUp
      end
      object Label10: TLabel
        Left = 172
        Top = 93
        Width = 112
        Height = 13
        Caption = #1062#1074#1077#1090' '#1074#1099#1073#1088#1072#1085#1085#1086#1081' '#1058#1060#1045
      end
      object shpFrameColorTFS: TShape
        Left = 336
        Top = 115
        Width = 49
        Height = 22
        OnMouseUp = shpFrameColorTFSMouseUp
      end
      object Label11: TLabel
        Left = 172
        Top = 119
        Width = 112
        Height = 13
        Caption = #1062#1074#1077#1090' '#1074#1099#1073#1088#1072#1085#1085#1086#1081' '#1058#1060'C'
      end
      object Label12: TLabel
        Left = 172
        Top = 146
        Width = 152
        Height = 13
        Caption = #1062#1074#1077#1090' '#1058#1060#1045' '#1089'  '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1072#1084#1080
      end
      object shpHaveChildColor: TShape
        Left = 336
        Top = 141
        Width = 49
        Height = 22
        OnMouseUp = shpHaveChildColorMouseUp
      end
      object cbBoldTFELine: TCheckBox
        Left = 8
        Top = 8
        Width = 153
        Height = 17
        Caption = #1059#1090#1086#1083#1097#1077#1085#1085#1099#1077' '#1083#1080#1085#1080#1080
        TabOrder = 0
        OnClick = cbBoldTFELineClick
      end
      object cbBrushTFE: TCheckBox
        Left = 8
        Top = 72
        Width = 153
        Height = 17
        Caption = #1047#1072#1083#1080#1074#1082#1072
        TabOrder = 1
        OnClick = cbBrushTFEClick
      end
      object btFont: TButton
        Left = 88
        Top = 144
        Width = 75
        Height = 25
        Caption = #1064#1088#1080#1092#1090
        TabOrder = 2
        OnClick = btFontClick
      end
      object cbxFlagType: TComboBox
        Left = 264
        Top = 8
        Width = 121
        Height = 21
        Style = csDropDownList
        TabOrder = 3
        OnChange = cbxFlagTypeChange
        Items.Strings = (
          #1056#1086#1084#1073
          #1054#1082#1088#1091#1078#1085#1086#1089#1090#1100
          #1050#1074#1072#1076#1088#1072#1090)
      end
    end
    object TabSheet3: TTabSheet
      Caption = #1040#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1099
      ImageIndex = 2
      object shpAltFlagColor: TShape
        Left = 205
        Top = 5
        Width = 49
        Height = 22
        OnMouseUp = shpAltFlagColorMouseUp
      end
      object Label13: TLabel
        Left = 12
        Top = 10
        Width = 68
        Height = 13
        Caption = #1062#1074#1077#1090' '#1092#1083#1072#1078#1082#1072
      end
      object Label14: TLabel
        Left = 12
        Top = 35
        Width = 132
        Height = 13
        Caption = #1062#1074#1077#1090' '#1074#1099#1073#1088#1072#1085#1085#1086#1075#1086' '#1092#1083#1072#1078#1082#1072
      end
      object shpAltEnterFlagColor: TShape
        Left = 205
        Top = 32
        Width = 49
        Height = 22
        OnMouseUp = shpAltEnterFlagColorMouseU
      end
      object shpAltArrowColor: TShape
        Left = 205
        Top = 59
        Width = 49
        Height = 22
        OnMouseUp = shpAltArrowColorMouseUp
      end
      object Label15: TLabel
        Left = 12
        Top = 63
        Width = 69
        Height = 13
        Caption = #1062#1074#1077#1090' '#1089#1090#1088#1077#1083#1082#1080
      end
      object Label16: TLabel
        Left = 12
        Top = 91
        Width = 128
        Height = 13
        Caption = #1062#1074#1077#1090' '#1074#1099#1073#1088#1072#1085#1085#1086#1081' '#1089#1090#1088#1077#1083#1082#1080
      end
      object shpAltEnterArrowColor: TShape
        Left = 205
        Top = 87
        Width = 49
        Height = 22
        OnMouseUp = shpAltEnterArrowColorMouseUp
      end
      object shpAltLineColor: TShape
        Left = 205
        Top = 115
        Width = 49
        Height = 22
        OnMouseUp = shpAltLineColorMouseUp
      end
      object Label17: TLabel
        Left = 12
        Top = 119
        Width = 58
        Height = 13
        Caption = #1062#1074#1077#1090' '#1083#1080#1085#1080#1081
      end
      object shpAltEnabledFlagColor: TShape
        Left = 205
        Top = 144
        Width = 49
        Height = 22
        OnMouseUp = shpAltEnabledFlagColorMouseUp
      end
      object Label19: TLabel
        Left = 12
        Top = 149
        Width = 166
        Height = 13
        Caption = #1062#1074#1077#1090' '#1079#1072#1073#1083#1086#1082#1080#1088#1086#1074#1072#1085#1085#1086#1075#1086' '#1092#1083#1072#1078#1082#1072
      end
      object cbCanModifyPenWidth: TCheckBox
        Left = 12
        Top = 183
        Width = 204
        Height = 17
        Alignment = taLeftJustify
        Caption = #1056#1072#1079#1088#1077#1096#1072#1090#1100' '#1091#1090#1086#1083#1097#1077#1085#1080#1077' '#1083#1080#1085#1080#1081
        TabOrder = 0
        OnClick = cbCanModifyPenWidthClick
      end
      object GroupBox2: TGroupBox
        Left = 267
        Top = 7
        Width = 124
        Height = 132
        Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1080#1095#1077#1089#1082#1080#1077
        TabOrder = 1
        object shpAltParamLineColor: TShape
          Left = 60
          Top = 19
          Width = 50
          Height = 22
          OnMouseUp = shpAltParamLineColorMouseUp
        end
        object Label20: TLabel
          Left = 8
          Top = 24
          Width = 32
          Height = 13
          Caption = #1051#1080#1085#1080#1103
        end
        object GroupBox3: TGroupBox
          Left = 3
          Top = 52
          Width = 118
          Height = 76
          Caption = #1047#1072#1083#1080#1074#1082#1072
          TabOrder = 0
          object Label21: TLabel
            Left = 7
            Top = 44
            Width = 25
            Height = 13
            Caption = #1062#1074#1077#1090
          end
          object shpAltParamShapeColor: TShape
            Left = 57
            Top = 40
            Width = 49
            Height = 22
            OnMouseUp = shpAltParamShapeColorMouseUp
          end
          object cbAltParamShapeColorEnable: TCheckBox
            Left = 7
            Top = 20
            Width = 104
            Height = 13
            Caption = #1047#1072#1076#1077#1081#1089#1090#1074#1086#1074#1072#1090#1100
            TabOrder = 0
            OnClick = cbAltParamShapeColorEnableClick
          end
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = #1057#1087#1088#1072#1074#1082#1072
      ImageIndex = 3
      object Label18: TLabel
        Left = 7
        Top = 15
        Width = 136
        Height = 13
        Caption = #1055#1091#1090#1100' '#1082' '#1089#1087#1088#1072#1074#1086#1095#1085#1086#1084#1091' '#1092#1072#1081#1083#1091
      end
      object edHelp: TEdit
        Left = 7
        Top = 35
        Width = 338
        Height = 21
        TabOrder = 0
        OnExit = edHelpExit
      end
      object btHelp: TButton
        Left = 351
        Top = 35
        Width = 40
        Height = 20
        Caption = ' ... '
        TabOrder = 1
        OnClick = btHelpClick
      end
      object btHelpDefault: TButton
        Left = 7
        Top = 60
        Width = 176
        Height = 20
        Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
        TabOrder = 2
        OnClick = btHelpDefaultClick
      end
    end
    object tsActions: TTabSheet
      Caption = #1044#1077#1081#1089#1090#1074#1080#1103
      ImageIndex = 4
      object Label22: TLabel
        Left = 8
        Top = 152
        Width = 215
        Height = 13
        Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1072#1103' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1086' '#1076#1077#1081#1089#1090#1074#1080#1080' '
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 394
        Height = 118
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object sgActions: TStringGrid
          Left = 0
          Top = 0
          Width = 394
          Height = 118
          Align = alClient
          ColCount = 3
          DefaultRowHeight = 18
          FixedCols = 0
          RowCount = 2
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing]
          TabOrder = 0
          OnDrawCell = sgActionsDrawCell
          OnSelectCell = sgActionsSelectCell
          ColWidths = (
            134
            64
            64)
        end
      end
      object cbKey: TComboBox
        Left = 219
        Top = 36
        Width = 118
        Height = 21
        Style = csDropDownList
        TabOrder = 1
        OnExit = cbKeyExit
      end
      object cbMenu: TCheckBox
        Left = 195
        Top = 86
        Width = 59
        Height = 13
        Caption = #1042' '#1084#1077#1085#1102
        TabOrder = 2
        OnExit = cbMenuExit
      end
      object cbxShift: TCheckBox
        Left = 8
        Top = 128
        Width = 80
        Height = 17
        Caption = 'Shift'
        TabOrder = 3
      end
      object cbxCtrl: TCheckBox
        Left = 160
        Top = 128
        Width = 80
        Height = 17
        Caption = 'Ctrl'
        TabOrder = 4
      end
      object cbxAlt: TCheckBox
        Left = 312
        Top = 128
        Width = 80
        Height = 17
        Caption = 'Alt'
        TabOrder = 5
        OnClick = cbxShiftClick
      end
      object mmHint: TMemo
        Left = 8
        Top = 172
        Width = 377
        Height = 33
        Color = clBtnFace
        ReadOnly = True
        TabOrder = 6
      end
    end
    object tsView: TTabSheet
      Caption = #1054#1082#1085#1086' '#1088#1077#1096#1077#1085#1080#1103
      ImageIndex = 5
      object Label23: TLabel
        Left = 12
        Top = 10
        Width = 255
        Height = 13
        Caption = #1062#1074#1077#1090' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1099' '#1087#1086#1076#1093#1086#1076#1103#1097#1077#1081' '#1087#1086' '#1086#1075#1088#1072#1085#1080#1095#1077#1085#1080#1103#1084
      end
      object shpVwColorAlt: TShape
        Left = 309
        Top = 5
        Width = 49
        Height = 22
        OnMouseUp = shpVwColorAltMouseUp
      end
      object Label24: TLabel
        Left = 12
        Top = 35
        Width = 270
        Height = 13
        Caption = #1062#1074#1077#1090' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1099' '#1085#1077' '#1087#1086#1076#1093#1086#1076#1103#1097#1077#1081' '#1087#1086' '#1086#1075#1088#1072#1085#1080#1095#1077#1085#1080#1103#1084
      end
      object shpVwColorBadAlt: TShape
        Left = 309
        Top = 32
        Width = 49
        Height = 22
        OnMouseUp = shpVwColorBadAltMouseUp
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 238
    Width = 402
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Button1: TButton
      Left = 232
      Top = 8
      Width = 75
      Height = 25
      Action = acOK
      TabOrder = 0
    end
    object Button2: TButton
      Left = 320
      Top = 8
      Width = 75
      Height = 25
      Action = acCancel
      TabOrder = 1
    end
  end
  object CDG: TColorDialog
    Left = 352
    Top = 240
  end
  object FDG: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Left = 404
    Top = 251
  end
  object OPD: TOpenDialog
    Left = 316
    Top = 211
  end
  object ImgList: TImageList
    Left = 276
    Top = 227
    Bitmap = {
      494C010101000400100010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000840000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000084000000840000008400000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008400000084000000840000008400000084000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000084
      0000008400000084000000000000008400000084000000840000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008400000084
      0000008400000000000000000000000000000084000000840000008400000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008400000084
      0000000000000000000000000000000000000000000000840000008400000084
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008400000000
      0000000000000000000000000000000000000000000000000000008400000084
      0000008400000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000084
      0000008400000084000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008400000084000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000084000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFF000000000000FFFF000000000000
      FFFF000000000000FDFF000000000000F8FF000000000000F07F000000000000
      E23F000000000000C71F000000000000CF8F000000000000DFC7000000000000
      FFE3000000000000FFF3000000000000FFFB000000000000FFFF000000000000
      FFFF000000000000FFFF00000000000000000000000000000000000000000000
      000000000000}
  end
  object ActionList1: TActionList
    Left = 348
    Top = 16
    object acOK: TAction
      Caption = #1055#1088#1080#1085#1103#1090#1100
      OnExecute = acOKExecute
    end
    object acCancel: TAction
      Caption = #1054#1090#1084#1077#1085#1072
      ShortCut = 27
      OnExecute = acCancelExecute
    end
  end
end
