unit ConnectionParams;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Mask;

type
  TFormConnectionParams = class(TForm)
    LabelLogNum: TLabel;
    LabelUser: TLabel;
    LabelPassword: TLabel;
    ButtonOK: TButton;
    ButtonCancel: TButton;
    ELogNum: TEdit;
    EUser: TEdit;
    EPassword: TEdit;
	private
		{ Private declarations }
	public
		{ Public declarations }
	end;

implementation

{$R *.DFM}

end.
