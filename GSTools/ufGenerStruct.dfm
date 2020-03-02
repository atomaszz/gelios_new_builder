object fmToolGenerStruct: TfmToolGenerStruct
  Left = 0
  Top = 0
  Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103' '#1089#1090#1088#1091#1082#1090#1091#1088#1099' '#1080#1079' '#1086#1095#1077#1088#1077#1076#1080
  ClientHeight = 586
  ClientWidth = 1001
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
    Top = 545
    Width = 1001
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      1001
      41)
    object acptBtn: TButton
      Left = 907
      Top = 6
      Width = 82
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1055#1088#1080#1085#1103#1090#1100
      TabOrder = 0
      OnClick = acptBtnClick
    end
    object extBtn: TButton
      Left = 818
      Top = 6
      Width = 83
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 1
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 1001
    Height = 304
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 1001
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
    end
    object Panel2: TPanel
      Left = 723
      Top = 32
      Width = 278
      Height = 272
      Align = alRight
      TabOrder = 1
      object Panel8: TPanel
        Left = 1
        Top = 230
        Width = 276
        Height = 41
        Align = alBottom
        Caption = 'Panel8'
        TabOrder = 0
        object addWorkBtn: TButton
          Left = 183
          Top = 11
          Width = 82
          Height = 25
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 0
          OnClick = addWorkBtnClick
        end
        object delWorkBtn: TButton
          Left = 5
          Top = 11
          Width = 83
          Height = 25
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 1
        end
        object editWorkBtn: TButton
          Left = 94
          Top = 11
          Width = 82
          Height = 25
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
        end
      end
      object PageControl3: TPageControl
        Left = 1
        Top = 1
        Width = 276
        Height = 229
        ActivePage = TabSheet5
        Align = alClient
        Style = tsFlatButtons
        TabOrder = 1
        OnChange = PageControl3Change
        object TabSheet5: TTabSheet
          Caption = #1056#1072#1073'. '#1086#1087#1077#1088#1072#1094#1080#1103
          object Panel9: TPanel
            Left = 0
            Top = 0
            Width = 268
            Height = 198
            Align = alClient
            TabOrder = 0
            object Label1: TLabel
              Left = 6
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
              Left = 6
              Top = 105
              Width = 179
              Height = 13
              Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' 1-'#1086#1081' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1099':'
            end
            object CheckBoxAloneCheck: TCheckBox
              Left = 6
              Top = 159
              Width = 177
              Height = 17
              Caption = #1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1082#1086#1085#1090#1088#1086#1083#1100
              TabOrder = 0
            end
            object editNumAlter: TEdit
              Left = 144
              Top = 67
              Width = 51
              Height = 21
              Enabled = False
              TabOrder = 1
            end
            object editBeforeOperation: TEdit
              Left = 6
              Top = 27
              Width = 191
              Height = 21
              TabOrder = 2
            end
            object editFirstAlterName: TEdit
              Left = 6
              Top = 124
              Width = 188
              Height = 21
              Enabled = False
              TabOrder = 3
            end
          end
        end
        object TabSheet6: TTabSheet
          Caption = #1040#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1072
          ImageIndex = 1
          object Label7: TLabel
            Left = 6
            Top = 6
            Width = 52
            Height = 13
            Caption = #1053#1072#1079#1074#1072#1085#1080#1077':'
          end
          object Label8: TLabel
            Left = 6
            Top = 60
            Width = 78
            Height = 13
            Caption = #1042#1077#1088#1086#1103#1090#1085#1086#1089#1090#1100' B:'
          end
          object Label9: TLabel
            Left = 6
            Top = 106
            Width = 143
            Height = 13
            Caption = #1042#1077#1088#1086#1103#1090#1085#1086#1089#1090#1100' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1077' T:'
          end
          object Label10: TLabel
            Left = 6
            Top = 152
            Width = 137
            Height = 13
            Caption = #1047#1072#1090#1088#1072#1090#1099' '#1085#1072' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1077' V:'
          end
          object Label15: TLabel
            Left = 150
            Top = 6
            Width = 68
            Height = 13
            Caption = #8470' '#1086#1087#1077#1088#1072#1094#1080#1080':'
          end
          object textNumeWorkOper: TLabel
            Left = 224
            Top = 6
            Width = 35
            Height = 13
            Caption = '_____'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object editNameAlter: TEdit
            Left = 6
            Top = 27
            Width = 191
            Height = 21
            TabOrder = 0
          end
          object editB: TEdit
            Left = 6
            Top = 79
            Width = 191
            Height = 21
            TabOrder = 1
          end
          object editT: TEdit
            Left = 6
            Top = 125
            Width = 191
            Height = 21
            TabOrder = 2
          end
          object editV: TEdit
            Left = 6
            Top = 171
            Width = 191
            Height = 21
            TabOrder = 3
          end
        end
      end
    end
    object PageControl2: TPageControl
      Left = 0
      Top = 32
      Width = 723
      Height = 272
      ActivePage = TabSheet3
      Align = alClient
      Style = tsFlatButtons
      TabOrder = 2
      OnChange = PageControl2Change
      ExplicitLeft = -1
      ExplicitTop = 26
      object TabSheet3: TTabSheet
        Caption = #1056#1072#1073#1086#1095#1080#1077' '#1086#1087#1077#1088#1072#1094#1080#1080
        object sgWorkOperation: TStringGrid
          Left = 0
          Top = 0
          Width = 715
          Height = 241
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
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goRowSelect]
          ParentFont = False
          TabOrder = 0
        end
      end
      object TabSheet4: TTabSheet
        Caption = #1040#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1099
        ImageIndex = 1
      end
    end
  end
  object Panel5: TPanel
    Left = 0
    Top = 304
    Width = 1001
    Height = 241
    Align = alBottom
    BevelOuter = bvNone
    Constraints.MinWidth = 550
    TabOrder = 2
    object Panel6: TPanel
      Left = 0
      Top = 0
      Width = 1001
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
    end
    object Panel7: TPanel
      Left = 723
      Top = 32
      Width = 278
      Height = 209
      Align = alRight
      TabOrder = 1
      object Panel10: TPanel
        Left = 1
        Top = 167
        Width = 276
        Height = 41
        Align = alBottom
        Caption = 'Panel8'
        TabOrder = 0
        object addControlBtn: TButton
          Left = 182
          Top = 11
          Width = 82
          Height = 25
          Caption = #1044#1086#1073#1072#1074#1080#1090#1100
          TabOrder = 0
        end
        object delControlBtn: TButton
          Left = 5
          Top = 11
          Width = 83
          Height = 25
          Caption = #1059#1076#1072#1083#1080#1090#1100
          TabOrder = 1
        end
        object editControlBtn: TButton
          Left = 94
          Top = 11
          Width = 82
          Height = 25
          Caption = #1048#1079#1084#1077#1085#1080#1090#1100
          TabOrder = 2
        end
      end
      object PageControl4: TPageControl
        Left = 1
        Top = 1
        Width = 276
        Height = 166
        ActivePage = TabSheet7
        Align = alClient
        Style = tsFlatButtons
        TabOrder = 1
        OnChange = PageControl4Change
        object TabSheet7: TTabSheet
          Caption = #1050#1086#1085#1090#1088#1086#1083#1100
          object Label4: TLabel
            Left = 6
            Top = 65
            Width = 133
            Height = 13
            Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074':'
          end
          object Label5: TLabel
            Left = 6
            Top = 6
            Width = 142
            Height = 13
            Caption = #1050#1086#1085#1090#1088#1086#1083#1080#1088#1091#1077#1084#1099#1077' '#1086#1087#1077#1088#1072#1094#1080#1080':'
          end
          object Label6: TLabel
            Left = 6
            Top = 91
            Width = 179
            Height = 13
            Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' 1-'#1086#1081' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1099':'
          end
          object editCheckOperation: TEdit
            Left = 6
            Top = 25
            Width = 200
            Height = 21
            TabOrder = 0
          end
          object editNumCheckAlter: TEdit
            Left = 142
            Top = 61
            Width = 59
            Height = 21
            Enabled = False
            TabOrder = 1
          end
          object editFirstNameAlter: TEdit
            Left = 6
            Top = 110
            Width = 198
            Height = 21
            Enabled = False
            TabOrder = 2
          end
        end
        object TabSheet8: TTabSheet
          Caption = #1040#1083#1100#1090#1077#1088#1088#1085#1072#1090#1080#1074#1072
          ImageIndex = 1
          ExplicitLeft = 5
          ExplicitTop = 25
          object Label11: TLabel
            Left = 6
            Top = 60
            Width = 97
            Height = 13
            Caption = #1042#1077#1088#1086#1103#1090#1085#1086#1089#1090#1100' '#1055'_11:'
          end
          object Label12: TLabel
            Left = 6
            Top = 6
            Width = 52
            Height = 13
            Caption = #1053#1072#1079#1074#1072#1085#1080#1077':'
          end
          object Label13: TLabel
            Left = 6
            Top = 115
            Width = 129
            Height = 13
            Caption = #1042#1077#1088#1086#1103#1090#1085#1086#1089#1090#1100' '#1088#1072#1073#1086#1090#1086#1089'-'#1090#1080':'
          end
          object Label14: TLabel
            Left = 6
            Top = 87
            Width = 97
            Height = 13
            Caption = #1042#1077#1088#1086#1103#1090#1085#1086#1089#1090#1100' '#1055'_00:'
          end
          object Label16: TLabel
            Left = 150
            Top = 6
            Width = 68
            Height = 13
            Caption = #8470' '#1086#1087#1077#1088#1072#1094#1080#1080':'
          end
          object Label17: TLabel
            Left = 224
            Top = 6
            Width = 35
            Height = 13
            Caption = '_____'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object editP11: TEdit
            Left = 109
            Top = 55
            Width = 88
            Height = 21
            TabOrder = 0
          end
          object editNameCheckAlter: TEdit
            Left = 6
            Top = 25
            Width = 191
            Height = 21
            TabOrder = 1
          end
          object editPDiagn: TEdit
            Left = 141
            Top = 111
            Width = 55
            Height = 21
            TabOrder = 2
          end
          object editP00: TEdit
            Left = 109
            Top = 84
            Width = 88
            Height = 21
            TabOrder = 3
          end
        end
      end
    end
    object PageControl1: TPageControl
      Left = 0
      Top = 32
      Width = 723
      Height = 209
      ActivePage = TabSheet1
      Align = alClient
      Style = tsFlatButtons
      TabOrder = 2
      OnChange = PageControl1Change
      object TabSheet1: TTabSheet
        Caption = #1054#1087#1077#1088#1072#1094#1080#1080' '#1082#1086#1085#1090#1088#1086#1083#1103
        object sgControlOperation: TStringGrid
          Left = 0
          Top = 0
          Width = 715
          Height = 178
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
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goColSizing, goRowSelect]
          ParentFont = False
          TabOrder = 0
        end
      end
      object TabSheet2: TTabSheet
        Caption = #1040#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074#1099
        ImageIndex = 1
      end
    end
  end
end
