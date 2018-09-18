object Form1: TForm1
  Left = 402
  Top = 119
  Width = 1247
  Height = 675
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClick = FormClick
  PixelsPerInch = 96
  TextHeight = 13
  object CoolBar1: TCoolBar
    Left = 0
    Top = 0
    Width = 105
    Height = 161
    Align = alNone
    Bands = <
      item
        Control = RadioGroup1
        ImageIndex = -1
        MinHeight = 97
        Width = 101
      end
      item
        Control = RadioGroup2
        ImageIndex = -1
        MinHeight = 62
        Width = 101
      end>
    Visible = False
    object RadioGroup1: TRadioGroup
      Left = 9
      Top = 0
      Width = 88
      Height = 97
      Align = alTop
      Caption = 'RadioGroup1'
      Items.Strings = (
      'Observation'
      'VP_saturated'
      'Watts to MJ/Int'
      'MJ/Int to Watts'
      'Average'
      'Minimum'
      'Maximum'
      'Total'
      'Positive'
      'First'
      'Last'
      'Count'
      'Count0'
      'Delta'
      TabOrder = 0
      OnClick = RadioGroup1Click
    end
    object RadioGroup2: TRadioGroup
      Left = 9
      Top = 99
      Width = 88
      Height = 62
      Align = alTop
      Caption = 'RadioGroup2'
      Items.Strings = (
        'Display Off'
        'Display Final Value'
        'Display Working Values')
      TabOrder = 1
      OnClick = RadioGroup2Click
    end
  end
end
