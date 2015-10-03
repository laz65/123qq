unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, CPort, CPortTypes, StdCtrls,
  rfUnit, rfReq,
  JvComponentBase, JvTrayIcon, ExtCtrls, JvExExtCtrls, JvShape;

type
  TForm1 = class(TForm)
    Button1: TButton;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    CheckBox5: TCheckBox;
    CheckBox6: TCheckBox;
    CheckBox7: TCheckBox;
    CheckBox8: TCheckBox;
    CheckBox9: TCheckBox;
    CheckBox10: TCheckBox;
    CheckBox11: TCheckBox;
    CheckBox12: TCheckBox;
    CheckBox13: TCheckBox;
    CheckBox14: TCheckBox;
    CheckBox15: TCheckBox;
    CheckBox16: TCheckBox;
    CheckBox17: TCheckBox;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    Button9: TButton;
    Button10: TButton;
    Label1: TLabel;
    Button11: TButton;
    Button13: TButton;
    Button14: TButton;
    Button15: TButton;
    Timer1: TTimer;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Button12: TButton;
    procedure ComPort1RxChar(Sender: TObject; Count: Integer);
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure Button13Click(Sender: TObject);
    procedure Button14Click(Sender: TObject);
    procedure Button15Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button11Click(Sender: TObject);
    procedure JvTrayIcon1DblClick(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ComPort1Error(Sender: TObject; Errors: TComErrors);
    procedure Button12Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure UpdateStatus;
    procedure DisableButtons;
    procedure EnableButtons;
    procedure SetParams;
  end;


  TMainThread = class (TThread)

       constructor Create;
       procedure Execute; override;

  end;


var
  Form1: TForm1;
  MainThread: TMainThread;
  Psw: String;
  
implementation

{$R *.dfm}

procedure TForm1.Button10Click(Sender: TObject);
begin
     rfReport(repGoods, repZ);
end;

procedure TForm1.Button11Click(Sender: TObject);
begin
     ProcessFiles;
end;

procedure TForm1.Button12Click(Sender: TObject);
begin
     SetParams;
end;

procedure TForm1.Button13Click(Sender: TObject);
begin
     DisableButtons;
     LogText('(%)АВТОНОМНЫЙ РЕЖИМ ВКЛЮЧЁН');
     Timer1.Enabled := True;
     Self.Hide;
end;

procedure TForm1.Button14Click(Sender: TObject);
begin
     LogText('(X)АВТОНОМНЫЙ РЕЖИМ ВЫКЛЮЧЁН');
     Timer1.Enabled := False;
     EnableButtons;
end;

procedure TForm1.Button15Click(Sender: TObject);
begin
     rfDoClose;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
     rfGetStatus;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
     rfSetMode(rmWork, Psw);
     UpdateStatus;
     rfLogIn(StrToInt(Edit1.Text));
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
     rfSetMode(rmXmode, Psw);
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
     rfSetMode(rmZmode, Psw);
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
     rfOpenRegister;
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
     rfResetRF;
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
     rfReport(repDaily, repX);
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
     rfReport(repGoods, repX);
end;

procedure TForm1.Button9Click(Sender: TObject);
begin
     rfReport(repDaily, repZ);
end;

procedure TForm1.ComPort1Error(Sender: TObject; Errors: TComErrors);
const Flags: array[ceFrame..ceTxFull] of String =
('ceFrame', 'ceRxParity', 'ceOverrun', 'ceBreak', 'ceIO', 'ceMode', 'ceRxOver',
    'ceTxFull');
var
     ES: String;
     I: TComError;
begin
     ES := '';
     for I := ceFrame to ceTxFull do
         if I in Errors then ES := ES + Flags[I];         
     RaiseError('!!!ОШИБКА РАБОТЫ С COM-ПОРТОМ: '+ES);
end;

procedure TForm1.ComPort1RxChar(Sender: TObject; Count: Integer);
var Buf, S: String;
    i: Integer;
begin
     ComPort1.ReadStr(Buf, Count);
     LogText('!!!НЕОЖИДАННЫЕ ВХОДНЫЕ ДАННЫЕ ИЗ COM-ПОРТА');
     LogText(Buf);
     S := '';
     for i := 1 to Count do
         S := S + IntToHex(Ord(Buf[i]),2) + ' ';
     LogText(S);
end;

procedure TForm1.DisableButtons;
begin
     Button1.Enabled := False;
     Button2.Enabled := False;
     Button3.Enabled := False;
     Button4.Enabled := False;
     Button5.Enabled := False;
     Button6.Enabled := False;
     Button7.Enabled := False;
     Button8.Enabled := False;
     Button9.Enabled := False;
     Button10.Enabled := False;
     Button15.Enabled := False;
end;

procedure TForm1.EnableButtons;
begin
     Button1.Enabled := True;
     Button2.Enabled := True;
     Button3.Enabled := True;
     Button4.Enabled := True;
     Button5.Enabled := True;
     Button6.Enabled := True;
     Button7.Enabled := True;
     Button8.Enabled := True;
     Button9.Enabled := True;
     Button10.Enabled := True;
     Button15.Enabled := True;
end;

procedure IndBusy;
begin
     Form1.DisableButtons;
     Form1.Indicator.Brush.Color := RGB(255,0,0);
     Form1.Indicator.Refresh;
end;

procedure IndDone;
begin
     Form1.EnableButtons;
     Form1.Indicator.Brush.Color := RGB(0,255,0);
     Form1.Indicator.Refresh;
     Form1.UpdateStatus;
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
     LogFile.Free;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
     SetParams;
     FileList := TStringList.Create;
     CurrFile := TStringList.Create;

     CallBackBusy := IndBusy;
     CallBackDone := IndDone;

     Init(ComPort1);

     try
         ComPort1.TriggersOnRxChar := True;
         ComPort1.Open;
     except
     on E: Exception do
          RaiseError('!!! Ошибка открытия COM-порта, либо программа уже запущена. '+E.Message);
     end;
end;

procedure TForm1.JvTrayIcon1DblClick(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
     Self.Show;
end;

procedure TForm1.SetParams;
begin
     WorkFolder := Edit3.Text;
     MoveFolder := Edit4.Text;
     Psw := Edit2.Text;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
     try
         ProcessFiles;
     except
      on E: Exception do
      begin
           Application.MessageBox(PAnsiChar(E.Message), 'Фатальная ошибка', MB_ICONERROR);
           Application.Terminate;
           Halt;
      end;
     end;
end;

procedure TForm1.UpdateStatus;
begin
     CheckBox1.Checked := False;
     CheckBox2.Checked := False;
     CheckBox3.Checked := False;
     CheckBox4.Checked := False;
     CheckBox5.Checked := False;
     CheckBox6.Checked := False;
     CheckBox7.Checked := False;
     CheckBox8.Checked := False;
     CheckBox9.Checked := False;
     CheckBox10.Checked := False;
     CheckBox11.Checked := False;
     CheckBox12.Checked := False;
     CheckBox13.Checked := False;
     CheckBox14.Checked := False;
     CheckBox15.Checked := False;
     CheckBox16.Checked := False;
     CheckBox17.Checked := False;

     if (sts1 and mBit0) <> 0 then CheckBox1.Checked := True;
     if (sts1 and mBit1) <> 0 then CheckBox2.Checked := True;
     if (sts1 and mBit2) <> 0 then CheckBox3.Checked := True;
     if (sts1 and mBit3) <> 0 then CheckBox4.Checked := True;
     if (sts1 and mBit4) <> 0 then CheckBox5.Checked := True;
     if (sts1 and mBit5) <> 0 then CheckBox6.Checked := True;

     if (sts2 and mBit0) <> 0 then CheckBox7.Checked := True;
     if (sts2 and mBit1) <> 0 then CheckBox8.Checked := True;
     if (sts2 and mBit2) <> 0 then CheckBox9.Checked := True;
     if (sts2 and mBit3) <> 0 then CheckBox10.Checked := True;
     if (sts2 and mBit4) <> 0 then CheckBox11.Checked := True;
     if (sts2 and mBit5) <> 0 then CheckBox12.Checked := True;

     if (sts3 and mBit0) <> 0 then CheckBox13.Checked := True;
     if (sts3 and mBit1) <> 0 then CheckBox14.Checked := True;
     if (sts3 and mBit6) <> 0 then CheckBox15.Checked := True;
     if (sts3 and mBit7) <> 0 then CheckBox16.Checked := True;
     if (sts3 and mBit2) <> 0 then CheckBox17.Checked := True;
     if (sts3 and mBit3) <> 0 then CheckBox17.Checked := True;
     if (sts3 and mBit4) <> 0 then CheckBox17.Checked := True;
     if (sts3 and mBit5) <> 0 then CheckBox17.Checked := True;
end;

{ TMainThread }

constructor TMainThread.Create;
begin
     inherited Create(True);
end;

procedure TMainThread.Execute;
begin
     while not Terminated do
     begin
          ListFiles; // Получить список файлов
          if FileList.Count > 0 then // Проверить кол-во
          begin // Обработать первый по списку файл
               ReadFile(FileList.Strings[0]);
               if MoveFile(FileList.Strings[0]) then
                  ProcessRequest;
          end;
          Sleep(1000);
     end;
end;


end.
