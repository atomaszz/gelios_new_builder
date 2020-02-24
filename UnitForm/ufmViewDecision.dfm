object fmViewDecision: TfmViewDecision
  Left = 282
  Top = 131
  Caption = #1056#1077#1096#1077#1085#1080#1077' '#1079#1072#1076#1072#1095#1080
  ClientHeight = 516
  ClientWidth = 916
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 475
    Width = 916
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      916
      41)
    object Button1: TButton
      Left = 983
      Top = 7
      Width = 91
      Height = 29
      Action = acClose
      Anchors = [akTop, akRight]
      ModalResult = 1
      TabOrder = 0
    end
    object Button2: TButton
      Left = 5
      Top = 7
      Width = 262
      Height = 29
      Action = acShowResult
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 175
    Width = 916
    Height = 300
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 1
    object bvVert: TBevel
      Left = 273
      Top = 1
      Width = 1
      Height = 298
      Align = alLeft
      Shape = bsLeftLine
    end
    object Panel5: TPanel
      Left = 1
      Top = 1
      Width = 272
      Height = 298
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      object Panel6: TPanel
        Left = 0
        Top = 0
        Width = 272
        Height = 30
        Align = alTop
        Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
      end
      object Panel7: TPanel
        Left = 0
        Top = 30
        Width = 272
        Height = 268
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 1
        object Label1: TLabel
          Left = 6
          Top = 5
          Width = 167
          Height = 16
          Caption = #1042#1080#1076' '#1079#1072#1076#1072#1095#1080' '#1086#1087#1090#1080#1084#1080#1079#1072#1094#1080#1080
        end
        object Label7: TLabel
          Left = 6
          Top = 87
          Width = 87
          Height = 16
          Caption = #1054#1075#1088#1072#1085#1080#1095#1077#1085#1080#1103
        end
        object Label8: TLabel
          Left = 6
          Top = 170
          Width = 178
          Height = 16
          Caption = #1047#1085#1072#1095#1077#1085#1080#1103' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1086#1074' '
        end
        object Bevel2: TBevel
          Left = 9
          Top = 25
          Width = 49
          Height = 49
        end
        object Bevel3: TBevel
          Left = 73
          Top = 25
          Width = 49
          Height = 49
        end
        object Bevel4: TBevel
          Left = 144
          Top = 25
          Width = 50
          Height = 49
        end
        object Bevel5: TBevel
          Left = 208
          Top = 25
          Width = 50
          Height = 49
        end
        object Bevel1: TBevel
          Left = 9
          Top = 112
          Width = 49
          Height = 50
        end
        object Label11: TLabel
          Left = 6
          Top = 219
          Width = 181
          Height = 16
          Caption = #1042#1088#1077#1084#1103' '#1085#1072#1093#1086#1078#1076#1077#1085#1080#1103' '#1088#1077#1096#1077#1085#1080#1103
        end
        object Bevel6: TBevel
          Left = 218
          Top = 34
          Width = 50
          Height = 50
        end
        object edVid1: TEdit
          Left = 9
          Top = 26
          Width = 256
          Height = 20
          BorderStyle = bsNone
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 0
          Text = 'edVid1'
        end
        object edVid2: TEdit
          Left = 9
          Top = 57
          Width = 256
          Height = 19
          BorderStyle = bsNone
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 1
          Text = 'edVid2'
        end
        object edOgr1: TEdit
          Left = 9
          Top = 108
          Width = 256
          Height = 20
          BorderStyle = bsNone
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 2
          Text = 'edOgr1'
        end
        object edOgr2: TEdit
          Left = 9
          Top = 138
          Width = 256
          Height = 20
          BorderStyle = bsNone
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 3
          Text = 'edOgr2'
        end
        object edKoef: TEdit
          Left = 9
          Top = 190
          Width = 256
          Height = 20
          BorderStyle = bsNone
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 4
          Text = 'edKoef'
        end
        object edTime: TEdit
          Left = 9
          Top = 239
          Width = 256
          Height = 21
          BorderStyle = bsNone
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 5
          Text = 'edTime'
        end
      end
    end
    object Panel8: TPanel
      Left = 274
      Top = 1
      Width = 641
      Height = 298
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        641
        298)
      object Label4: TLabel
        Left = 7
        Top = 43
        Width = 14
        Height = 26
        Caption = 'B'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -23
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel
        Left = 7
        Top = 84
        Width = 14
        Height = 26
        Caption = 'T'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -23
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 7
        Top = 127
        Width = 14
        Height = 26
        Caption = 'V'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -23
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 9
        Top = 164
        Width = 202
        Height = 16
        Caption = #1057#1086#1089#1090#1072#1074' '#1086#1087#1090#1080#1084#1072#1083#1100#1085#1086#1075#1086' '#1088#1077#1096#1077#1085#1080#1103
      end
      object Label3: TLabel
        Left = 9
        Top = 245
        Width = 169
        Height = 16
        Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074':'
      end
      object Label9: TLabel
        Left = 9
        Top = 267
        Width = 216
        Height = 16
        Caption = #1091#1076#1086#1074#1083#1077#1090#1074#1086#1088#1103#1102#1097#1080#1093' '#1086#1075#1088#1072#1085#1080#1095#1077#1085#1080#1103#1084
      end
      object Label10: TLabel
        Left = 418
        Top = 267
        Width = 41
        Height = 16
        Caption = #1086#1073#1097#1077#1077
      end
      object Panel9: TPanel
        Left = 0
        Top = 0
        Width = 641
        Height = 30
        Align = alTop
        Caption = #1054#1087#1090#1080#1084#1072#1083#1100#1085#1086#1077' '#1088#1077#1096#1077#1085#1080#1077
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
      end
      object edT: TEdit
        Left = 27
        Top = 87
        Width = 754
        Height = 24
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edB: TEdit
        Left = 27
        Top = 46
        Width = 754
        Height = 24
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object edV: TEdit
        Left = 26
        Top = 129
        Width = 755
        Height = 24
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object StaticText1: TStaticText
        Left = 229
        Top = 266
        Width = 81
        Height = 20
        AutoSize = False
        BorderStyle = sbsSunken
        Caption = 'StaticText1'
        TabOrder = 4
      end
      object StaticText2: TStaticText
        Left = 466
        Top = 266
        Width = 80
        Height = 20
        AutoSize = False
        BorderStyle = sbsSunken
        Caption = 'StaticText1'
        TabOrder = 5
      end
      object edOptSostav: TEdit
        Left = 9
        Top = 191
        Width = 772
        Height = 24
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
      end
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 916
    Height = 175
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 916
      Height = 32
      Align = alTop
      BevelOuter = bvLowered
      Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' '#1072#1083#1100#1090#1077#1088#1085#1072#1090#1080#1074' ('#1073#1077#1079' '#1091#1095#1077#1090#1072' '#1086#1075#1088#1072#1085#1080#1095#1077#1085#1080#1081')'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
    object sgAlternative: TStringGrid
      Left = 0
      Top = 32
      Width = 916
      Height = 143
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
      OnDrawCell = sgAlternativeDrawCell
    end
  end
  object ActionList1: TActionList
    Left = 488
    Top = 40
    object acClose: TAction
      Caption = #1047#1099#1082#1088#1099#1090#1100
      OnExecute = acCloseExecute
    end
    object acShowResult: TAction
      Caption = #1055#1086#1082#1072#1079#1072#1090#1100' '#1088#1077#1096#1077#1085#1080#1077
      OnExecute = acShowResultExecute
    end
  end
end
