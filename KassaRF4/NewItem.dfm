object NewPLU: TNewPLU
  Left = 532
  Top = 182
  ActiveControl = ECode
  BorderIcons = [biSystemMenu, biHelp]
  BorderStyle = bsDialog
  Caption = 'New Item'
  ClientHeight = 327
  ClientWidth = 238
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 36
    Top = 24
    Width = 25
    Height = 13
    Caption = 'Code'
  end
  object Label2: TLabel
    Left = 33
    Top = 52
    Width = 28
    Height = 13
    Caption = 'Name'
  end
  object Label3: TLabel
    Left = 37
    Top = 80
    Width = 24
    Height = 13
    Caption = 'Price'
  end
  object Label4: TLabel
    Left = 6
    Top = 108
    Width = 55
    Height = 13
    Caption = 'Department'
  end
  object Label5: TLabel
    Left = 32
    Top = 136
    Width = 29
    Height = 13
    Caption = 'Group'
  end
  object Label6: TLabel
    Left = 43
    Top = 164
    Width = 18
    Height = 13
    Caption = 'Tax'
  end
  object Label7: TLabel
    Left = 22
    Top = 192
    Width = 39
    Height = 13
    Caption = 'Quantity'
  end
  object Label8: TLabel
    Left = 36
    Top = 220
    Width = 25
    Height = 13
    Caption = 'Flags'
  end
  object ECode: TMaskEdit
    Left = 68
    Top = 20
    Width = 121
    Height = 21
    EditMask = '99999999999999;1; '
    MaxLength = 14
    TabOrder = 0
    Text = '              '
  end
  object EName: TMaskEdit
    Left = 68
    Top = 48
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object EPrice: TMaskEdit
    Left = 68
    Top = 76
    Width = 121
    Height = 21
    EditMask = '9999999.99;1; '
    MaxLength = 10
    TabOrder = 2
    Text = '       .  '
  end
  object EDep: TMaskEdit
    Left = 68
    Top = 104
    Width = 121
    Height = 21
    EditMask = '99;0; '
    MaxLength = 2
    TabOrder = 3
  end
  object EGrp: TMaskEdit
    Left = 68
    Top = 132
    Width = 121
    Height = 21
    EditMask = '99;0; '
    MaxLength = 2
    TabOrder = 4
  end
  object ETax: TMaskEdit
    Left = 68
    Top = 160
    Width = 121
    Height = 21
    EditMask = '9;0; '
    MaxLength = 1
    TabOrder = 5
  end
  object EQty: TMaskEdit
    Left = 68
    Top = 188
    Width = 121
    Height = 21
    EditMask = '999999.999;1; '
    MaxLength = 10
    TabOrder = 6
    Text = '      .   '
  end
  object EFlg: TMaskEdit
    Left = 68
    Top = 216
    Width = 121
    Height = 21
    EditMask = '999;0; '
    MaxLength = 3
    TabOrder = 7
    OnChange = EFlgChange
  end
  object btnOK: TButton
    Left = 32
    Top = 268
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 8
  end
  object btnCancel: TButton
    Left = 128
    Top = 268
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 9
  end
end
