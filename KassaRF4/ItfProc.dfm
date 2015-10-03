object ProcItfForm: TProcItfForm
  Left = 227
  Top = 132
  BorderIcons = [biSystemMenu, biHelp]
  BorderStyle = bsDialog
  Caption = #1055#1088#1086#1094#1077#1076#1091#1088#1099' '#1080' '#1080#1085#1090#1077#1088#1092#1077#1081#1089#1099
  ClientHeight = 453
  ClientWidth = 688
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
    Width = 688
    Height = 257
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object PageCtrl: TPageControl
      Left = 0
      Top = 0
      Width = 588
      Height = 257
      ActivePage = pgIHcFReg
      Align = alLeft
      TabOrder = 0
      object pgIHcFReg: TTabSheet
        Caption = 'IHcFReg'
        OnShow = pgIHcFRegShow
        object pcIHcFReg: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgOplata
          Align = alClient
          TabOrder = 0
          object pcgSmenBegin: TTabSheet
            Caption = 'SmenBegin'
            OnShow = pcgSmenBeginShow
            object Label3: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgBegChk: TTabSheet
            Caption = 'BegChk'
            ImageIndex = 1
            OnShow = pcgBegChkShow
            object Label4: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgEndChk: TTabSheet
            Caption = 'EndChk'
            ImageIndex = 2
            OnShow = pcgEndChkShow
            object Label5: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgVoidChk: TTabSheet
            Caption = 'VoidChk'
            ImageIndex = 3
            OnShow = pcgVoidChkShow
            object Label6: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgCopyChk: TTabSheet
            Caption = 'CopyChk'
            ImageIndex = 4
            OnShow = pcgCopyChkShow
            object Label7: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgVoidLast: TTabSheet
            Caption = 'VoidLast'
            ImageIndex = 5
            OnShow = pcgVoidLastShow
            object Label8: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgTextComment: TTabSheet
            Caption = 'TextComment'
            ImageIndex = 6
            OnShow = pcgTextCommentShow
            object Label9: TLabel
              Left = 132
              Top = 44
              Width = 30
              Height = 13
              Caption = #1058#1077#1082#1089#1090
              FocusControl = meTextCommentComment
            end
            object meTextCommentComment: TMaskEdit
              Left = 172
              Top = 40
              Width = 121
              Height = 21
              TabOrder = 0
            end
          end
          object pcgBinComment: TTabSheet
            Caption = 'BinComment'
            ImageIndex = 7
            OnShow = pcgBinCommentShow
            object Label10: TLabel
              Left = 60
              Top = 32
              Width = 80
              Height = 13
              Caption = #1048#1076#1077#1085#1090#1080#1092#1080#1082#1072#1090#1086#1088
              FocusControl = meBinCommentID
            end
            object Label11: TLabel
              Left = 100
              Top = 56
              Width = 41
              Height = 13
              Caption = #1044#1072#1085#1085#1099#1077
              FocusControl = meBinCommentBComment
            end
            object meBinCommentID: TMaskEdit
              Left = 148
              Top = 28
              Width = 121
              Height = 21
              EditMask = '999;0; '
              MaxLength = 3
              TabOrder = 0
            end
            object meBinCommentBComment: TMaskEdit
              Left = 148
              Top = 52
              Width = 121
              Height = 21
              TabOrder = 1
            end
          end
          object pcgProd: TTabSheet
            Caption = 'Prod'
            ImageIndex = 8
            OnShow = pcgProdShow
            object Label12: TLabel
              Left = 108
              Top = 40
              Width = 57
              Height = 13
              Caption = #1050#1086#1076' '#1090#1086#1074#1072#1088#1072
              FocusControl = meProdID
            end
            object Label13: TLabel
              Left = 140
              Top = 64
              Width = 26
              Height = 13
              Caption = #1062#1077#1085#1072
              FocusControl = meProdCena
            end
            object Label14: TLabel
              Left = 108
              Top = 88
              Width = 59
              Height = 13
              Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086
              FocusControl = meProdKol
            end
            object Label15: TLabel
              Left = 136
              Top = 112
              Width = 31
              Height = 13
              Caption = #1054#1090#1076#1077#1083
              FocusControl = meProdDep
            end
            object Label16: TLabel
              Left = 132
              Top = 136
              Width = 35
              Height = 13
              Caption = #1043#1088#1091#1087#1087#1072
              FocusControl = meProdGrp
            end
            object meProdID: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              EditMask = '99999999999999;0; '
              MaxLength = 14
              TabOrder = 0
            end
            object meProdCena: TMaskEdit
              Left = 168
              Top = 60
              Width = 121
              Height = 21
              TabOrder = 1
            end
            object meProdKol: TMaskEdit
              Left = 168
              Top = 84
              Width = 121
              Height = 21
              TabOrder = 2
            end
            object meProdDep: TMaskEdit
              Left = 168
              Top = 108
              Width = 121
              Height = 21
              EditMask = '99;0; '
              MaxLength = 2
              TabOrder = 3
            end
            object meProdGrp: TMaskEdit
              Left = 168
              Top = 132
              Width = 121
              Height = 21
              EditMask = '99;0; '
              MaxLength = 2
              TabOrder = 4
            end
          end
          object pcgVoidProd: TTabSheet
            Caption = 'VoidProd'
            ImageIndex = 9
            OnShow = pcgVoidProdShow
            object Label17: TLabel
              Left = 108
              Top = 40
              Width = 57
              Height = 13
              Caption = #1050#1086#1076' '#1090#1086#1074#1072#1088#1072
              FocusControl = meVoidProdID
            end
            object meVoidProdID: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              EditMask = '99999999999999;0; '
              MaxLength = 14
              TabOrder = 0
            end
          end
          object pcgOplata: TTabSheet
            Caption = 'Oplata'
            ImageIndex = 10
            OnShow = pcgOplataShow
            object Label18: TLabel
              Left = 108
              Top = 40
              Width = 59
              Height = 13
              Caption = #1050#1086#1076' '#1086#1087#1083#1072#1090#1099
              FocusControl = meOplataID
            end
            object Label19: TLabel
              Left = 92
              Top = 64
              Width = 74
              Height = 13
              Caption = #1057#1091#1084#1084#1072' '#1086#1087#1083#1072#1090#1099
              FocusControl = meOplataSum
            end
            object Label20: TLabel
              Left = 104
              Top = 88
              Width = 63
              Height = 13
              Caption = #1050#1086#1076' '#1082#1083#1080#1077#1085#1090#1072
              FocusControl = meOplataCode
            end
            object meOplataID: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              EditMask = '9;0; '
              MaxLength = 1
              TabOrder = 0
            end
            object meOplataSum: TMaskEdit
              Left = 168
              Top = 60
              Width = 121
              Height = 21
              TabOrder = 1
            end
            object meOplataCode: TMaskEdit
              Left = 168
              Top = 84
              Width = 121
              Height = 21
              EditMask = '9999999999;0; '
              MaxLength = 10
              TabOrder = 2
            end
          end
          object pcgInOut: TTabSheet
            Caption = 'InOut'
            ImageIndex = 11
            OnShow = pcgInOutShow
            object Label21: TLabel
              Left = 108
              Top = 40
              Width = 59
              Height = 13
              Caption = #1050#1086#1076' '#1086#1087#1083#1072#1090#1099
              FocusControl = meInOutID
            end
            object Label22: TLabel
              Left = 56
              Top = 64
              Width = 110
              Height = 13
              Caption = #1057#1091#1084#1084#1072' '#1074#1085#1086#1089#1072'/'#1074#1099#1085#1086#1089#1072
              FocusControl = meInOutSum
            end
            object meInOutID: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              EditMask = '9;0; '
              MaxLength = 1
              TabOrder = 0
            end
            object meInOutSum: TMaskEdit
              Left = 168
              Top = 60
              Width = 121
              Height = 21
              TabOrder = 1
            end
          end
          object pcgNacSkd: TTabSheet
            Caption = 'NacSkd'
            ImageIndex = 12
            OnShow = pcgNacSkdShow
            object Label23: TLabel
              Left = 60
              Top = 40
              Width = 105
              Height = 13
              Caption = #1042#1080#1076' '#1089#1082#1080#1076#1082#1080'/'#1085#1072#1094#1077#1085#1082#1080
              FocusControl = meNacSkdID
            end
            object Label24: TLabel
              Left = 44
              Top = 64
              Width = 120
              Height = 13
              Caption = #1057#1091#1084#1084#1072' '#1089#1082#1080#1076#1082#1080'/'#1085#1072#1094#1077#1085#1082#1080
              FocusControl = meNacSkdSum
            end
            object Label25: TLabel
              Left = 36
              Top = 88
              Width = 129
              Height = 13
              Caption = #1055#1088#1086#1094#1077#1085#1090' '#1089#1082#1080#1076#1082#1080'/'#1085#1072#1094#1077#1085#1082#1080
              FocusControl = meNacSkdPrc
            end
            object meNacSkdID: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              EditMask = '9;0; '
              MaxLength = 1
              TabOrder = 0
            end
            object meNacSkdSum: TMaskEdit
              Left = 168
              Top = 60
              Width = 121
              Height = 21
              EditMask = '9999999.99;1; '
              MaxLength = 10
              TabOrder = 1
              Text = '       .  '
            end
            object meNacSkdPrc: TMaskEdit
              Left = 168
              Top = 84
              Width = 121
              Height = 21
              EditMask = '99.9999;1; '
              MaxLength = 7
              TabOrder = 2
              Text = '  .    '
            end
          end
        end
      end
      object pgIHcFRegFull: TTabSheet
        Caption = 'IHcFRegFull'
        ImageIndex = 17
        OnShow = pgIHcFRegFullShow
        object pcIHcFRegFull: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgFullProd
          Align = alClient
          TabOrder = 0
          object pcgFullProd: TTabSheet
            Caption = 'FullProd'
            OnShow = pcgFullProdShow
            object Label69: TLabel
              Left = 108
              Top = 16
              Width = 57
              Height = 13
              Caption = #1050#1086#1076' '#1090#1086#1074#1072#1088#1072
              FocusControl = meFullProdCode
            end
            object Label70: TLabel
              Left = 140
              Top = 40
              Width = 26
              Height = 13
              Caption = #1062#1077#1085#1072
              FocusControl = meFullProdPrice
            end
            object Label71: TLabel
              Left = 108
              Top = 64
              Width = 59
              Height = 13
              Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086
              FocusControl = meFullProdQty
            end
            object Label72: TLabel
              Left = 136
              Top = 88
              Width = 31
              Height = 13
              Caption = #1054#1090#1076#1077#1083
              FocusControl = meFullProdDep
            end
            object Label73: TLabel
              Left = 132
              Top = 112
              Width = 35
              Height = 13
              Caption = #1043#1088#1091#1087#1087#1072
              FocusControl = meFullProdGrp
            end
            object Label74: TLabel
              Left = 136
              Top = 136
              Width = 31
              Height = 13
              Alignment = taRightJustify
              Caption = #1053#1072#1083#1086#1075
            end
            object Label75: TLabel
              Left = 90
              Top = 160
              Width = 76
              Height = 13
              Alignment = taRightJustify
              Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
            end
            object meFullProdCode: TMaskEdit
              Left = 168
              Top = 12
              Width = 121
              Height = 21
              EditMask = '99999999999999;0; '
              MaxLength = 14
              TabOrder = 0
            end
            object meFullProdPrice: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              EditMask = '9999999.99;1; '
              MaxLength = 10
              TabOrder = 1
              Text = '       .  '
            end
            object meFullProdQty: TMaskEdit
              Left = 168
              Top = 60
              Width = 121
              Height = 21
              EditMask = '999999.999;1; '
              MaxLength = 10
              TabOrder = 2
              Text = '      .   '
            end
            object meFullProdDep: TMaskEdit
              Left = 168
              Top = 84
              Width = 121
              Height = 21
              EditMask = '99;0; '
              MaxLength = 2
              TabOrder = 3
            end
            object meFullProdGrp: TMaskEdit
              Left = 168
              Top = 108
              Width = 121
              Height = 21
              EditMask = '99;0; '
              MaxLength = 2
              TabOrder = 4
            end
            object meFullProdTax: TMaskEdit
              Left = 168
              Top = 132
              Width = 121
              Height = 21
              EditMask = '9;0; '
              MaxLength = 1
              TabOrder = 5
            end
            object meFullProdName: TMaskEdit
              Left = 168
              Top = 156
              Width = 121
              Height = 21
              TabOrder = 6
            end
          end
        end
      end
      object pgIHcFRegEx: TTabSheet
        Caption = 'IHcFRegEx'
        ImageIndex = 17
        OnShow = pgIHcFRegExShow
        object pcIHcFRegEx: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgFullNac
          Align = alClient
          TabOrder = 0
          object pcg2FullProd: TTabSheet
            Caption = 'FullProd'
            OnShow = pcg2FullProdShow
            object Label60: TLabel
              Left = 108
              Top = 16
              Width = 57
              Height = 13
              Caption = #1050#1086#1076' '#1090#1086#1074#1072#1088#1072
              FocusControl = me2FullProdCode
            end
            object Label61: TLabel
              Left = 140
              Top = 40
              Width = 26
              Height = 13
              Caption = #1062#1077#1085#1072
              FocusControl = me2FullProdPrice
            end
            object Label62: TLabel
              Left = 108
              Top = 64
              Width = 59
              Height = 13
              Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086
              FocusControl = me2FullProdQty
            end
            object Label78: TLabel
              Left = 136
              Top = 88
              Width = 31
              Height = 13
              Caption = #1054#1090#1076#1077#1083
              FocusControl = me2FullProdDep
            end
            object Label79: TLabel
              Left = 132
              Top = 112
              Width = 35
              Height = 13
              Caption = #1043#1088#1091#1087#1087#1072
              FocusControl = me2FullProdGrp
            end
            object Label80: TLabel
              Left = 136
              Top = 136
              Width = 31
              Height = 13
              Alignment = taRightJustify
              Caption = #1053#1072#1083#1086#1075
            end
            object Label84: TLabel
              Left = 90
              Top = 160
              Width = 76
              Height = 13
              Alignment = taRightJustify
              Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
            end
            object me2FullProdCode: TMaskEdit
              Left = 168
              Top = 12
              Width = 121
              Height = 21
              EditMask = '99999999999999;0; '
              MaxLength = 14
              TabOrder = 0
            end
            object me2FullProdPrice: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              EditMask = '9999999.99;1; '
              MaxLength = 10
              TabOrder = 1
              Text = '       .  '
            end
            object me2FullProdQty: TMaskEdit
              Left = 168
              Top = 60
              Width = 121
              Height = 21
              EditMask = '999999.999;1; '
              MaxLength = 10
              TabOrder = 2
              Text = '      .   '
            end
            object me2FullProdDep: TMaskEdit
              Left = 168
              Top = 84
              Width = 121
              Height = 21
              EditMask = '99;0; '
              MaxLength = 2
              TabOrder = 3
            end
            object me2FullProdGrp: TMaskEdit
              Left = 168
              Top = 108
              Width = 121
              Height = 21
              EditMask = '99;0; '
              MaxLength = 2
              TabOrder = 4
            end
            object me2FullProdTax: TMaskEdit
              Left = 168
              Top = 132
              Width = 121
              Height = 21
              EditMask = '9;0; '
              MaxLength = 1
              TabOrder = 5
            end
            object me2FullProdName: TMaskEdit
              Left = 168
              Top = 156
              Width = 121
              Height = 21
              TabOrder = 6
            end
          end
          object pcgFullNac: TTabSheet
            Caption = 'FullNac'
            ImageIndex = 1
            OnShow = pcgFullNacShow
            object Label81: TLabel
              Left = 60
              Top = 40
              Width = 105
              Height = 13
              Caption = #1042#1080#1076' '#1089#1082#1080#1076#1082#1080'/'#1085#1072#1094#1077#1085#1082#1080
              FocusControl = meFullNacID
            end
            object Label82: TLabel
              Left = 44
              Top = 64
              Width = 120
              Height = 13
              Caption = #1057#1091#1084#1084#1072' '#1089#1082#1080#1076#1082#1080'/'#1085#1072#1094#1077#1085#1082#1080
              FocusControl = meFullNacSum
            end
            object Label83: TLabel
              Left = 36
              Top = 88
              Width = 129
              Height = 13
              Alignment = taRightJustify
              Caption = #1055#1088#1086#1094#1077#1085#1090' '#1089#1082#1080#1076#1082#1080'/'#1085#1072#1094#1077#1085#1082#1080
              FocusControl = meFullNacPrc
            end
            object Label85: TLabel
              Left = 92
              Top = 112
              Width = 73
              Height = 13
              Alignment = taRightJustify
              Caption = #1053#1086#1084#1077#1088' '#1079#1072#1087#1080#1089#1080
            end
            object Label86: TLabel
              Left = 134
              Top = 136
              Width = 31
              Height = 13
              Alignment = taRightJustify
              Caption = #1053#1072#1083#1086#1075
            end
            object meFullNacID: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              EditMask = '9;0; '
              MaxLength = 1
              TabOrder = 0
            end
            object meFullNacSum: TMaskEdit
              Left = 168
              Top = 60
              Width = 121
              Height = 21
              EditMask = '9999999999999.99;1; '
              MaxLength = 16
              TabOrder = 1
              Text = '             .  '
            end
            object meFullNacPrc: TMaskEdit
              Left = 168
              Top = 84
              Width = 121
              Height = 21
              EditMask = '99.9999;1; '
              MaxLength = 7
              TabOrder = 2
              Text = '  .    '
            end
            object meFullNacRec: TMaskEdit
              Left = 168
              Top = 108
              Width = 121
              Height = 21
              TabOrder = 3
            end
            object meFullNacTax: TMaskEdit
              Left = 168
              Top = 132
              Width = 121
              Height = 21
              TabOrder = 4
            end
          end
          object pcgSubtotal: TTabSheet
            Caption = 'Subtotal'
            ImageIndex = 2
            OnShow = pcgSubtotalShow
            object Label87: TLabel
              Left = 51
              Top = 28
              Width = 91
              Height = 13
              Alignment = taRightJustify
              Caption = #1057#1091#1084#1084#1072' '#1087#1088#1086#1084#1080#1090#1086#1075#1072
            end
            object lSubtotalSum: TLabel
              Left = 160
              Top = 28
              Width = 6
              Height = 13
              Caption = '0'
            end
          end
        end
      end
      object pgIHcPayOff: TTabSheet
        Caption = 'IHcPayOff'
        ImageIndex = 8
        OnShow = pgIHcPayOffShow
        object pcIHcPayOff: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgPayOff
          Align = alClient
          TabOrder = 0
          object pcgPayOff: TTabSheet
            Caption = 'PayOff'
            OnShow = pcgPayOffShow
            object Label40: TLabel
              Left = 111
              Top = 40
              Width = 51
              Height = 13
              Alignment = taRightJustify
              Caption = #1042#1080#1076' '#1076#1077#1085#1077#1075
            end
            object Label41: TLabel
              Left = 124
              Top = 64
              Width = 34
              Height = 13
              Caption = #1057#1091#1084#1084#1072
            end
            object mePayOffID: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              TabOrder = 0
            end
            object mePayOffSum: TMaskEdit
              Left = 168
              Top = 60
              Width = 121
              Height = 21
              TabOrder = 1
            end
          end
        end
      end
      object pgIHcComment: TTabSheet
        Caption = 'IHcComment'
        ImageIndex = 9
        OnShow = pgIHcCommentShow
        object pcIHcComment: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgOpenComment
          Align = alClient
          TabOrder = 0
          object pcgOpenComment: TTabSheet
            Caption = 'OpenComment'
            OnShow = pcgOpenCommentShow
            object Label42: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgCloseComment: TTabSheet
            Caption = 'CloseComment'
            ImageIndex = 1
            OnShow = pcgCloseCommentShow
            object Label43: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgPrintComment: TTabSheet
            Caption = 'PrintComment'
            ImageIndex = 2
            OnShow = pcgPrintCommentShow
            object Label44: TLabel
              Left = 60
              Top = 40
              Width = 102
              Height = 13
              Alignment = taRightJustify
              Caption = #1058#1077#1082#1089#1090' '#1082#1086#1084#1084#1077#1085#1090#1072#1088#1080#1103
            end
            object mePrintCommentComment: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              TabOrder = 0
            end
          end
        end
      end
      object pgIHcForm: TTabSheet
        Caption = 'IHcForm'
        ImageIndex = 10
        OnShow = pgIHcFormShow
        object pcIHcForm: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgOpenForm
          Align = alClient
          TabOrder = 0
          object pcgOpenForm: TTabSheet
            Caption = 'OpenForm'
            OnShow = pcgOpenFormShow
            object Label45: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgCancelForm: TTabSheet
            Caption = 'CancelForm'
            ImageIndex = 1
            OnShow = pcgCancelFormShow
            object Label46: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgCloseForm: TTabSheet
            Caption = 'CloseForm'
            ImageIndex = 2
            OnShow = pcgCloseFormShow
            object Label47: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgPrintOnForm: TTabSheet
            Caption = 'PrintOnForm'
            ImageIndex = 3
            OnShow = pcgPrintOnFormShow
            object Label48: TLabel
              Left = 74
              Top = 40
              Width = 88
              Height = 13
              Alignment = taRightJustify
              Caption = #1058#1077#1082#1089#1090' '#1076#1083#1103' '#1087#1077#1095#1072#1090#1080
            end
            object mePrintOnFormComment: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              TabOrder = 0
            end
          end
        end
      end
      object pgIHcReport: TTabSheet
        Caption = 'IHcReport'
        ImageIndex = 11
        OnShow = pgIHcReportShow
        object pcIHcReport: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgPrintReport
          Align = alClient
          TabOrder = 0
          object pcgPrintReport: TTabSheet
            Caption = 'PrintReport'
            OnShow = pcgPrintReportShow
            object Label49: TLabel
              Left = 92
              Top = 40
              Width = 70
              Height = 13
              Alignment = taRightJustify
              Caption = #1053#1086#1084#1077#1088' '#1086#1090#1095#1077#1090#1072
            end
            object mePrintReportNumReport: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              TabOrder = 0
            end
          end
        end
      end
      object pgIHcClrAllPLU: TTabSheet
        Caption = 'IHcClrAllPLU'
        ImageIndex = 1
        OnShow = pgIHcClrAllPLUShow
        object pcIHcClrAllPLU: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgClrAllPLU
          Align = alClient
          TabOrder = 0
          object pcgClrAllPLU: TTabSheet
            Caption = 'ClrAllPLU'
            OnShow = pcgClrAllPLUShow
            object Label26: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
        end
      end
      object pgIHcProgTransaction: TTabSheet
        Caption = 'IHcProgTransaction'
        ImageIndex = 2
        OnShow = pgIHcProgTransactionShow
        object pcIHcProgTransaction: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgProgClose
          Align = alClient
          TabOrder = 0
          object pcgProgEnter: TTabSheet
            Caption = 'pcgProgEnter'
            OnShow = pcgProgEnterShow
            object Label27: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgProgClose: TTabSheet
            Caption = 'pcgProgClose'
            ImageIndex = 1
            OnShow = pcgProgCloseShow
            object Label28: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
        end
      end
      object pgIHcSqueeze: TTabSheet
        Caption = 'IHcSqueeze'
        ImageIndex = 3
        OnShow = pgIHcSqueezeShow
        object pcIHcSqueeze: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgSqueeze
          Align = alClient
          TabOrder = 0
          object pcgSqueeze: TTabSheet
            Caption = 'Squeeze'
            OnShow = pcgSqueezeShow
            object Label29: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
        end
      end
      object pgIHcSound: TTabSheet
        Caption = 'IHcSound'
        ImageIndex = 4
        OnShow = pgIHcSoundShow
        object pcIHcSound: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgOutTone
          Align = alClient
          TabOrder = 0
          object pcgOutTone: TTabSheet
            Caption = 'OutTone'
            OnShow = pcgOutToneShow
            object Label1: TLabel
              Left = 56
              Top = 28
              Width = 73
              Height = 13
              Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100
            end
            object Label2: TLabel
              Left = 87
              Top = 56
              Width = 42
              Height = 13
              Caption = #1063#1072#1089#1090#1086#1090#1072
            end
            object meOutToneLen: TMaskEdit
              Left = 144
              Top = 24
              Width = 121
              Height = 21
              EditMask = '99999;0; '
              MaxLength = 5
              TabOrder = 0
            end
            object meOutToneTone: TMaskEdit
              Left = 144
              Top = 52
              Width = 121
              Height = 21
              EditMask = '99999;0; '
              MaxLength = 5
              TabOrder = 1
            end
          end
        end
      end
      object pgIHcDisplay: TTabSheet
        Caption = 'IHcDisplay'
        ImageIndex = 5
        OnShow = pgIHcDisplayShow
        object pcIHcDisplay: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgOutScr
          Align = alClient
          TabOrder = 0
          object pcgOutScr: TTabSheet
            Caption = 'OutScr'
            OnShow = pcgOutScrShow
            object Label30: TLabel
              Left = 76
              Top = 32
              Width = 72
              Height = 13
              Caption = #1053#1086#1084#1077#1088' '#1089#1090#1088#1086#1082#1080
              FocusControl = meOutScrRow
            end
            object Label31: TLabel
              Left = 112
              Top = 56
              Width = 36
              Height = 13
              Caption = #1057#1090#1088#1086#1082#1072
              FocusControl = meOutScrScr2
            end
            object meOutScrRow: TMaskEdit
              Left = 152
              Top = 28
              Width = 121
              Height = 21
              EditMask = '9;0; '
              MaxLength = 1
              TabOrder = 0
            end
            object meOutScrScr2: TMaskEdit
              Left = 152
              Top = 52
              Width = 121
              Height = 21
              TabOrder = 1
            end
          end
        end
      end
      object pgIHcPeripherals: TTabSheet
        Caption = 'IHcPeripherals'
        ImageIndex = 6
        OnShow = pgIHcPeripheralsShow
        object pcIHcPeripherals: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgPutInfo
          Align = alClient
          TabOrder = 0
          object pcgPutInfo: TTabSheet
            Caption = 'PutInfo'
            OnShow = pcgPutInfoShow
            object Label32: TLabel
              Left = 76
              Top = 40
              Width = 60
              Height = 13
              Caption = #1059#1089#1090#1088#1086#1081#1089#1090#1074#1086
              FocusControl = mePutInfoID
            end
            object Label33: TLabel
              Left = 96
              Top = 64
              Width = 41
              Height = 13
              Caption = #1044#1072#1085#1085#1099#1077
              FocusControl = mePutInfoInfo
            end
            object mePutInfoID: TMaskEdit
              Left = 140
              Top = 36
              Width = 121
              Height = 21
              TabOrder = 0
            end
            object mePutInfoInfo: TMaskEdit
              Left = 140
              Top = 60
              Width = 121
              Height = 21
              TabOrder = 1
            end
          end
        end
      end
      object pgIHcReadCOM: TTabSheet
        Caption = 'IHcReadCOM'
        ImageIndex = 16
        OnShow = pgIHcReadCOMShow
        object pcIHcReadCOM: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgReadCOM
          Align = alClient
          TabOrder = 0
          object pcgReadCOM: TTabSheet
            Caption = 'ReadCOM'
            OnShow = pcgReadCOMShow
            object Label76: TLabel
              Left = 109
              Top = 60
              Width = 33
              Height = 13
              Alignment = taRightJustify
              Caption = #1052#1072#1089#1082#1072
            end
            object Label77: TLabel
              Left = 101
              Top = 80
              Width = 41
              Height = 13
              Alignment = taRightJustify
              Caption = #1044#1072#1085#1085#1099#1077
            end
            object lReadCOMLine: TLabel
              Left = 160
              Top = 80
              Width = 8
              Height = 13
              Caption = 'O'
            end
            object lReadCOMID: TLabel
              Left = 160
              Top = 60
              Width = 8
              Height = 13
              Caption = 'O'
            end
            object Label59: TLabel
              Left = 82
              Top = 28
              Width = 60
              Height = 13
              Alignment = taRightJustify
              Caption = #1059#1089#1090#1088#1086#1081#1089#1090#1074#1086
            end
            object meReadCOMKind: TMaskEdit
              Left = 156
              Top = 24
              Width = 121
              Height = 21
              TabOrder = 0
            end
          end
        end
      end
      object pgIHcExtTables: TTabSheet
        Caption = 'IHcExtTables'
        ImageIndex = 13
        OnShow = pgIHcExtTablesShow
        object pcIHcExtTables: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgBackupExtTables
          Align = alClient
          TabOrder = 0
          object pcgClearExtTables: TTabSheet
            Caption = 'ClearExtTables'
            OnShow = pcgClearExtTablesShow
            object Label51: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgBackupExtTables: TTabSheet
            Caption = 'BackupExtTables'
            ImageIndex = 1
            OnShow = pcgBackupExtTablesShow
            object Label52: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgRecalcCRC: TTabSheet
            Caption = 'RecalcCRC'
            ImageIndex = 2
            OnShow = pcgRecalcCRCShow
            object Label53: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgRestoreExtTables: TTabSheet
            Caption = 'RestoreExtTables'
            ImageIndex = 3
            OnShow = pcgRestoreExtTablesShow
            object Label54: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgVerifyExtTables: TTabSheet
            Caption = 'VerifyExtTables'
            ImageIndex = 4
            OnShow = pcgVerifyExtTablesShow
            object Label55: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
          object pcgWriteTable: TTabSheet
            Caption = 'WriteTable'
            ImageIndex = 5
            OnShow = pcgWriteTableShow
            object Label56: TLabel
              Left = 36
              Top = 40
              Width = 126
              Height = 13
              Alignment = taRightJustify
              Caption = #1048#1076#1077#1085#1090#1080#1092#1080#1082#1072#1090#1086#1088' '#1090#1072#1073#1083#1080#1094#1099
            end
            object Label57: TLabel
              Left = 118
              Top = 64
              Width = 44
              Height = 13
              Alignment = taRightJustify
              Caption = #1055#1086#1079#1080#1094#1080#1103
            end
            object Label58: TLabel
              Left = 96
              Top = 88
              Width = 66
              Height = 13
              Alignment = taRightJustify
              Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103
            end
            object meWriteTableTable: TMaskEdit
              Left = 168
              Top = 36
              Width = 121
              Height = 21
              TabOrder = 0
            end
            object meWriteTablePos: TMaskEdit
              Left = 168
              Top = 60
              Width = 121
              Height = 21
              TabOrder = 1
            end
            object meWriteTableInfo: TMaskEdit
              Left = 168
              Top = 84
              Width = 121
              Height = 21
              TabOrder = 2
            end
          end
        end
      end
      object pgIHcGetDriverInfo: TTabSheet
        Caption = 'IHcGetDriverInfo'
        ImageIndex = 7
        OnShow = pgIHcGetDriverInfoShow
        object Label34: TLabel
          Left = 114
          Top = 28
          Width = 28
          Height = 13
          Alignment = taRightJustify
          Caption = 'Name'
        end
        object Label35: TLabel
          Left = 46
          Top = 48
          Width = 96
          Height = 13
          Alignment = taRightJustify
          Caption = 'TextCommentHeight'
        end
        object Label36: TLabel
          Left = 49
          Top = 68
          Width = 93
          Height = 13
          Alignment = taRightJustify
          Caption = 'TextCommentWidth'
        end
        object Label37: TLabel
          Left = 68
          Top = 88
          Width = 74
          Height = 13
          Alignment = taRightJustify
          Caption = 'PLUCodeWidth'
        end
        object Label38: TLabel
          Left = 65
          Top = 108
          Width = 77
          Height = 13
          Alignment = taRightJustify
          Caption = 'PLUNameWidth'
        end
        object Label39: TLabel
          Left = 73
          Top = 128
          Width = 69
          Height = 13
          Alignment = taRightJustify
          Caption = 'MaxPLUCount'
        end
        object lGDIName: TLabel
          Left = 160
          Top = 28
          Width = 3
          Height = 13
        end
        object lGDITextCommentHeight: TLabel
          Left = 160
          Top = 48
          Width = 3
          Height = 13
        end
        object lGDITextCommentWidth: TLabel
          Left = 160
          Top = 68
          Width = 3
          Height = 13
        end
        object lGDIPLUCodeWidth: TLabel
          Left = 160
          Top = 88
          Width = 3
          Height = 13
        end
        object lGDIPLUNameWidth: TLabel
          Left = 160
          Top = 108
          Width = 3
          Height = 13
        end
        object lGDIMaxPLUCount: TLabel
          Left = 160
          Top = 128
          Width = 3
          Height = 13
        end
      end
      object pgIHcPLUFlags: TTabSheet
        Caption = 'IHcPLUFlags'
        ImageIndex = 15
        OnShow = pgIHcPLUFlagsShow
        object Label63: TLabel
          Left = 80
          Top = 28
          Width = 62
          Height = 13
          Alignment = taRightJustify
          Caption = 'MutablePrice'
        end
        object Label64: TLabel
          Left = 96
          Top = 48
          Width = 46
          Height = 13
          Alignment = taRightJustify
          Caption = 'Fractional'
        end
        object Label65: TLabel
          Left = 58
          Top = 68
          Width = 84
          Height = 13
          Alignment = taRightJustify
          Caption = 'RestrictedAmount'
        end
        object Label66: TLabel
          Left = 113
          Top = 88
          Width = 29
          Height = 13
          Alignment = taRightJustify
          Caption = 'Quota'
        end
        object Label67: TLabel
          Left = 98
          Top = 108
          Width = 44
          Height = 13
          Alignment = taRightJustify
          Caption = 'Singleton'
        end
        object Label68: TLabel
          Left = 105
          Top = 128
          Width = 37
          Height = 13
          Alignment = taRightJustify
          Caption = 'OnForm'
        end
        object lPLUFlagsOnForm: TLabel
          Left = 160
          Top = 128
          Width = 8
          Height = 13
          Caption = 'O'
        end
        object lPLUFlagsSingleton: TLabel
          Left = 160
          Top = 108
          Width = 8
          Height = 13
          Caption = 'O'
        end
        object lPLUFlagsQuota: TLabel
          Left = 160
          Top = 88
          Width = 8
          Height = 13
          Caption = 'O'
        end
        object lPLUFlagsRestrictedAmount: TLabel
          Left = 160
          Top = 68
          Width = 8
          Height = 13
          Caption = 'O'
        end
        object lPLUFlagsFractional: TLabel
          Left = 160
          Top = 48
          Width = 8
          Height = 13
          Caption = 'O'
        end
        object lPLUFlagsMutablePrice: TLabel
          Left = 160
          Top = 28
          Width = 8
          Height = 13
          Caption = 'O'
        end
      end
      object pgIHcRestart: TTabSheet
        Caption = 'IHcRestart'
        ImageIndex = 12
        OnShow = pgIHcRestartShow
        object pcIHcRestart: TPageControl
          Left = 0
          Top = 0
          Width = 580
          Height = 229
          ActivePage = pcgRestart
          Align = alClient
          TabOrder = 0
          object pcgRestart: TTabSheet
            Caption = 'pcgRestart'
            OnShow = pcgRestartShow
            object Label50: TLabel
              Left = 240
              Top = 93
              Width = 92
              Height = 13
              Alignment = taCenter
              Caption = 'Without parameters'
            end
          end
        end
      end
    end
    object Panel3: TPanel
      Left = 588
      Top = 0
      Width = 100
      Height = 257
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      object btnCancel: TButton
        Left = 12
        Top = 40
        Width = 75
        Height = 25
        Cancel = True
        Caption = 'Close'
        ModalResult = 2
        TabOrder = 0
      end
      object btnExecute: TButton
        Left = 12
        Top = 72
        Width = 75
        Height = 25
        Caption = 'Execute'
        Default = True
        TabOrder = 1
        OnClick = btnExecuteClick
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 257
    Width = 688
    Height = 196
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object m1: TMemo
      Left = 0
      Top = 0
      Width = 688
      Height = 196
      Align = alClient
      TabOrder = 0
    end
  end
end
