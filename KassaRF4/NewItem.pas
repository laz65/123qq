unit NewItem;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Mask;

type
  TNewPLU = class(TForm)
    ECode: TMaskEdit;
    Label1: TLabel;
    EName: TMaskEdit;
    Label2: TLabel;
    EPrice: TMaskEdit;
    Label3: TLabel;
    EDep: TMaskEdit;
    Label4: TLabel;
    EGrp: TMaskEdit;
    Label5: TLabel;
    ETax: TMaskEdit;
    Label6: TLabel;
    EQty: TMaskEdit;
    Label7: TLabel;
    EFlg: TMaskEdit;
    Label8: TLabel;
    btnOK: TButton;
    btnCancel: TButton;
    procedure EFlgChange(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
  private
		{ Private declarations }
	public
		{ Public declarations }
	end;

var
	NewPLU: TNewPLU;

implementation

{$R *.DFM}

procedure TNewPLU.EFlgChange(Sender: TObject);
var
	flg:longint;
begin
	if EFlg.Modified then begin
		try
			flg:=strtoint(EFlg.Text);
		except
			flg:=0;
		end;
		if not ((0<=flg) and (flg<=255)) then
			ShowMessage('Поле флагов должно содержать значение в диапазоне 0..255');
	end;
end;

procedure TNewPLU.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
var
	i,z:integer;
begin
	CanClose:=False;
	z:=length(ECode.Text);
	if z>0 then begin
		for i:=1 to z do begin
			if ECode.Text[i]<>' ' then begin
				CanClose:=True;
				Break;
			end;
		end;
	end;
	if not CanClose then
		ShowMessage('Нужно ввести хотя-бы код товара');
end;

end.
