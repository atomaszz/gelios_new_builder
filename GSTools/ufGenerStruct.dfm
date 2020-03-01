object fmToolGenerStruct: TfmToolGenerStruct
  Left = 0
  Top = 0
  Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103' '#1089#1090#1088#1091#1082#1090#1091#1088#1099' '#1080#1079' '#1086#1095#1077#1088#1077#1076#1080
  ClientHeight = 523
  ClientWidth = 550
  Color = clBtnFace
  Constraints.MinHeight = 420
  Constraints.MinWidth = 550
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 482
    Width = 550
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitTop = 542
    ExplicitWidth = 930
    DesignSize = (
      550
      41)
    object Button3: TButton
      Left = 315
      Top = 6
      Width = 100
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1055#1088#1080#1085#1103#1090#1100
      TabOrder = 0
      OnClick = Button3Click
      ExplicitLeft = 708
    end
    object Button4: TButton
      Left = 434
      Top = 6
      Width = 100
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 1
      ExplicitLeft = 827
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 550
    Height = 270
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 834
    ExplicitHeight = 203
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 550
      Height = 32
      Align = alTop
      BevelOuter = bvLowered
      Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' '#1088#1072#1073#1086#1095#1080#1093' '#1086#1087#1077#1088#1072#1094#1080#1081
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      ExplicitWidth = 916
    end
    object sgWorkOperation: TStringGrid
      Left = 0
      Top = 32
      Width = 272
      Height = 238
      Align = alClient
      ColCount = 1
      DefaultRowHeight = 18
      FixedCols = 0
      RowCount = 1
      FixedRows = 0
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing]
      ParentFont = False
      TabOrder = 1
      ExplicitTop = 26
      ExplicitWidth = 570
      ExplicitHeight = 236
    end
    object Panel2: TPanel
      Left = 272
      Top = 32
      Width = 278
      Height = 238
      Align = alRight
      TabOrder = 2
      ExplicitLeft = 516
      ExplicitTop = 38
      ExplicitHeight = 236
      object Panel8: TPanel
        Left = 1
        Top = 196
        Width = 276
        Height = 41
        Align = alBottom
        Caption = 'Panel8'
        TabOrder = 0
        ExplicitTop = 189
        object addBtn: TButton
          Left = 6
          Top = 11
          Width = 82
          Height = 25
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 0
        end
        object delBtn: TButton
          Left = 182
          Top = 11
          Width = 83
          Height = 25
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 1
        end
        object editBtn: TButton
          Left = 94
          Top = 11
          Width = 82
          Height = 25
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
        end
      end
      object Panel9: TPanel
        Left = 1
        Top = 1
        Width = 276
        Height = 195
        Align = alClient
        TabOrder = 1
        ExplicitLeft = 0
        ExplicitTop = 49
        ExplicitHeight = 167
        object Label1: TLabel
          Left = 5
          Top = 70
          Width = 133
          Height = 13
          Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074':'
        end
        object Label2: TLabel
          Left = 6
          Top = 6
          Width = 148
          Height = 13
          Caption = #1055#1088#1077#1076#1096#1077#1089#1090#1074#1091#1102#1097#1080#1077' '#1086#1087#1077#1088#1072#1094#1080#1080':'
        end
        object Label3: TLabel
          Left = 5
          Top = 105
          Width = 179
          Height = 13
          Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' 1-'#1086#1081' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1099':'
        end
        object CheckBox1: TCheckBox
          Left = 5
          Top = 159
          Width = 177
          Height = 17
          Caption = #1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1082#1086#1085#1090#1088#1086#1083#1100
          TabOrder = 0
        end
        object Edit1: TEdit
          Left = 144
          Top = 67
          Width = 51
          Height = 21
          Enabled = False
          TabOrder = 1
        end
        object Edit2: TEdit
          Left = 5
          Top = 27
          Width = 191
          Height = 21
          TabOrder = 2
        end
        object edPercent: TEdit
          Left = 5
          Top = 124
          Width = 244
          Height = 21
          Enabled = False
          TabOrder = 3
        end
        object Button1: TButton
          Left = 212
          Top = 85
          Width = 37
          Height = 29
          Caption = '....'
          TabOrder = 4
        end
      end
    end
  end
  object Panel5: TPanel
    Left = 0
    Top = 270
    Width = 550
    Height = 212
    Align = alBottom
    BevelOuter = bvNone
    Constraints.MinWidth = 550
    TabOrder = 2
    ExplicitTop = 256
    ExplicitWidth = 1009
    object Panel6: TPanel
      Left = 0
      Top = 0
      Width = 550
      Height = 32
      Align = alTop
      BevelOuter = bvLowered
      Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' '#1086#1087#1077#1088#1072#1094#1080#1081' '#1082#1086#1085#1090#1088#1086#1083#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      ExplicitWidth = 930
    end
    object sgControlOperation: TStringGrid
      Left = 0
      Top = 32
      Width = 272
      Height = 180
      Align = alClient
      ColCount = 1
      DefaultRowHeight = 18
      FixedCols = 0
      RowCount = 1
      FixedRows = 0
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing]
      ParentFont = False
      TabOrder = 1
      ExplicitLeft = -6
      ExplicitTop = 26
      ExplicitWidth = 570
    end
    object Panel7: TPanel
      Left = 272
      Top = 32
      Width = 278
      Height = 180
      Align = alRight
      TabOrder = 2
      ExplicitLeft = 652
      ExplicitHeight = 241
    end
  end
end
